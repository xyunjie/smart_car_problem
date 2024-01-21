

#include "ch32v10x_usb.h"
#include "ch32v10x_rcc.h"
#include "ch32v10x_usb_host.h"

#include "zf_systick.h"
#include "zf_usb_cdc.h"
/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2019/10/15
* Description        : Main program body.
*******************************************************************************/
/*
*@Note
模拟自定义USBCDC设备例程：
*/

#include "string.h"

/*Global Variable*/
#define DevEP0SIZE  0x40

/*Device Descriptor*/
const uint8  MyDevDescr[] =
{
        0x12,           //设备描述符长度，18字节
        0x01,           //描述符类型，0x01为设备描述符
        0x10,0x01,      //本设备所使用USB版本协议，因为是小端结构，所以低字节在前，即USB1.1版本为0x10,0x01，USB2.0为0x00,0x02
        0x02,           //类代码，CDC类为0x02，CDC类必须在设备描述符中指定设备类型，即0x02，否则，由于在配置集合中有两个接口，而会被系统误认为一个USB复合设备，从而导致设备工作不正常
        //当指定了设备类型为通信设备类后，子类和所使用的协议都必须指定为0.
        0x00,           //子类代码，当类代码bDeviceClass为0时，下面的子类代码bDeviceSubClass也必须为0。
        0x00,           //设备所使用的协议，协议代码由USB协会规定。当该字段为0时，表示设备不使用类所定义的协议。
        DevEP0SIZE,     //端点0的最大包长，可以取值8、16、32、64，此处为64字节
        0x86,0x1a,      //厂商ID
        0x22,0x57,      //产品设备ID
        0x00,0x01,      //设备版本号
        0x01,           //描述厂商的字符串索引值。当该值为0时，表示没有厂商字符串
        0x02,           //描述产品的字符串索引值。当该值为0时，表示没有产品字符串
        0x03,           //描述设备的序列号字符串索引值。当该值为0时，表示没有序列号字符串
        0x01,           //可能的配置数，通常为1
};

/* Configration Descriptor */
const uint8  MyCfgDescr[] =
{
        //配置描述符（两个接口）
        0x09,          //配置描述符长度，标准USB配置描述符长度为9字节
        0x02,          //描述符类型，配置描述符为0x02
        0x43,0x00,     //配置描述符集合总长度，67字节
        0x02,          //该配置所支持的接口数，2个接口
        0x01,          //表示该配置的值
        0x00,          //描述该配置的字符串的索引值，0x00表示没有字符串
        0xa0,          //描述设备的一些属性，如供电方式和唤醒等，0xA0表示设备总线供电且支持远程唤醒
        0x32,          //设备需要从总线获取的最大电流量，0x32表示最大电流100ma

        //以下为接口0（CDC接口）描述符，接口描述符不能单独返回，必须附着在配置描述符后一并返回
        0x09,          //接口描述符长度，标准的USB接口描述符长度为9字节
        0x04,          //描述符类型，接口描述符为0x04
        0x00,          //该接口的编号，从0开始，此处为0x00
        0x00,          //该接口的备用编号,通常设置为0
        0x01,          //该接口所使用的端点数，0x01表示使用1个端点。如果该字段为0，则表示没有非0端点，只使用默认的控制端点。CDC接口只使用一个中断输入端点
        0x02,          //该接口所使用的类，0x02为CDC类
        0x02,          //该接口所使用的子类，要实现USB转串口，就必须使用Abstract Control Model（抽象控制模型）子类，它的编号为0x02
        0x01,          //该接口所使用的协议，使用Common AT Commands（通用AT命令）协议
        0x00,          //该接口的字符串的索引值，0x00表示没有字符串


        //以下为类特殊接口描述符
        //功能描述符，主要用来描述接口的功能，功能描述符放在CDC接口（主接口）之后
        //Header Functional Descriptor
        0x05,          //该功能描述符的长度，5个字节
        0x24,          //该描述符的类型，固定位0x24（CS_INTERFACE的编码）
        0x00,          //该描述符子类型
        0x10,0x01,     //USB通信设备协议的版本号。此处为USB1.1

        //管理描述符(没有数据类接口)
        //Call Management Functional Descriptor
        0x05,          //该功能描述符的长度，5个字节
        0x24,          //该描述符的类型，固定位0x24（CS_INTERFACE的编码）
        0x01,          //该描述符子类型
        0x00,          //描述设备的能力，只有最低两位D0和D1有意义，其余位为保留值0。D0为0，表示设备自己不处理调用管理，为1则表示自己处理。
        0x00,          //表示选择用来做调用管理的数据类接口编号，由于不使用数据类接口做调用管理，因而该字段设置为0

        //Abstract Control Management Functional Descriptor  抽象控制管理功能描述符
        0x04,          //该功能描述符的长度，4个字节
        0x24,          //该描述符的类型，固定位0x24（CS_INTERFACE的编码）
        0x02,          //该描述符子类型
        0x02,          //描述设备的能力，其中D7-4位为保留位，设置为0，支持Set_Line_Coding、Set_Control_Line_State、Get_Line_Coding请求和Serial_State通知
                       //D0表示是否支持以下请求：Set_Comm_Feature、Clear_Comm_Feature、Get_Comm_Feature,为1表示支持；
                       //D1位表示是否支持Set_Line_Coding、Set_Control_Line_State、Get_Line_Coding请求和Serial_State通知，为1表示支持
                       //D2为表示是否支持Send_Break，为1表示支持
                       //D3表示是否支持Network_Connection通知，为1表示支持

        //Union Functional Descriptor，至少5字节，他描述一组接口之间的关系可以被当作为一个功能单元来看待，这些接口一个作为主接口，其他作为从接口
        0x05,          //该功能描述符的长度，5个字节
        0x24,          //该描述符的类型，固定位0x24（CS_INTERFACE的编码）
        0x06,          //该描述符子类型
        0x00,          //第四字节为主接口编号，此处为编号为0的CDC接口
        0x01,          //第五字节为第一从接口编号，此处为编号1的数据类接口，本例程只有一个从接口

        //接口0（CDC接口）的端点描述符
        0x07,          //端点描述符长度，7字节
        0x05,          //描述符类型，端点描述符为0x05
        0x81,          //该端点的地址，0x81表示端点1作为输入
        0x03,          //该端点的属性。最低两位D1-0表示该端点的传输类型，0为控制传输，1为等时传输，2为批量传输，3为中断传输
        0x40,0x00,     //该端点支持的最大包长度，64字节
        0xFF,          //端点的查询时间

        //以下为接口1（数据接口）描述符
        //CDC类接口（接口0）是负责管理整个设备的，而真正的串口数据传输是在数据类接口进行的。这里只使用一个数据类接口，编号为1
        0x09,          //接口描述符长度，9字节
        0x04,          //描述符类型，接口描述符为0x04
        0x01,          //该接口的编号，从0开始，此处为0x01
        0x00,          //该接口的备用编号
        0x02,          //该接口所使用的端点数，该接口要使用一对批量传输端点，因而端点数量为2
        0x0a,          //该接口所使用的类，0x0a为CDC数据类
        0x00,          //该接口所使用的子类
        0x00,          //该接口所使用的协议
        0x00,          //该接口的字符串的索引值，0x00表示没有字符串

        //接口1（数据类接口）的端点描述符
        0x07,          //端点描述符长度，7字节
        0x05,          //描述符类型，端点描述符为0x05
        0x02,          //该端点的地址，0x02表示端点2作为输出
        0x02,          //该端点的属性。最低两位D1-0表示该端点的传输类型，0为控制传输，1为等时传输，2为批量传输，3为中断传输
        0x40,0x00,     //该端点支持的最大包长度，64字节
        0x00,          //端点的查询时间，这里对批量端点无效

        0x07,          //端点描述符长度，7字节
        0x05,          //描述符类型，端点描述符为0x05
        0x82,          //该端点的地址，0x82表示端点2作为输入
        0x02,          //该端点的属性。最低两位D1-0表示该端点的传输类型，0为控制传输，1为等时传输，2为批量传输，3为中断传输
        0x40,0x00,     //该端点支持的最大包长度，64字节
        0x00,          //端点的查询时间，这里对批量端点无效
};

const uint8  MyProductIDInfo[] = {0x14,0x03,0x32,0x00,0x30,0x00,0x31,0x00,0x37,0x00,0x2D,0x00,0x32,0x00,0x2D,0x00,0x32,0x00,0x35,0x00};

/* Language Descriptor */
const uint8  MyLangDescr[] = { 0x04, 0x03, 0x09, 0x04 };

/* Manufactor Descriptor */
const uint8  MyManuInfo[] = { 0x0E, 0x03, 'w', 0, 'c', 0, 'h', 0, '.', 0, 'c', 0, 'n', 0 };

/* Product Information */
const uint8  MyProdInfo[] = { 0x0C, 0x03, 'C', 0, 'H', 0, '1', 0, '0', 0, 'x', 0 };

/**********************************************************/
uint8   Ready = 0;
uint8   UsbConfig;
uint8   SetupReqCode;
uint16  SetupReqLen;

//CDC参数
uint8 LineCoding[7]={0x00,0xe1,0x00,0x00,0x00,0x00,0x08};   //初始化波特率为57600，1停止位，无校验，8数据位。

#define  SET_LINE_CODING                0x20            //Configures DTE rate, stop-bits, parity, and number-of-character
#define  GET_LINE_CODING                0x21            //This request allows the host to find out the currently configured line coding.
#define  SET_CONTROL_LINE_STATE         0x22            //This request generates RS-232/V.24 style control signals.
#define  UART_REV_LEN                   0x40            //串口接收缓冲区大小

uint8 Receive_Uart_Buf[UART_REV_LEN];   //串口接收缓冲区
volatile uint8 Uart_Input_Point = 0;    //循环缓冲区写入指针，总线复位需要初始化为0
volatile uint8 Uart_Output_Point = 0;   //循环缓冲区取出指针，总线复位需要初始化为0
volatile uint8 UartByteCount = 0;       //当前缓冲区剩余待取字节数
volatile uint8 USBByteCount = 0;        //代表USB端点接收到的数据
volatile uint8 USBBufOutPoint = 0;      //取数据指针
volatile uint8 UpPoint2_Busy  = 0;      //上传端点是否忙标志

const uint8 *pDescr;

/* Endpoint Buffer */
__attribute__ ((aligned(4))) uint8 EP0_Databuf[64];     //ep0(64)
__attribute__ ((aligned(4))) uint8 EP1_Databuf[64+64];  //ep1_out(64)+ep1_in(64)
__attribute__ ((aligned(4))) uint8 EP2_Databuf[64+64];  //ep2_out(64)+ep2_in(64)

void USBHD_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*******************************************************************************
* Function Name  : Set_USBConfig
* Description    : Set USB clock.
* Input          : None
* Return         : None
*******************************************************************************/
void USBHD_ClockCmd(uint32 RCC_USBCLKSource,FunctionalState NewState)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, NewState);
    EXTEN->EXTEN_CTR |= EXTEN_USBHD_IO_EN;
    RCC_USBCLKConfig(RCC_USBCLKSource);             //USBclk=PLLclk/1.5=48Mhz
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_USBHD,NewState);
}

/*******************************************************************************
* Function Name  : USB_DevTransProcess
* Description    : USB device transfer process.
* Input          : None
* Return         : None
*******************************************************************************/
void USB_DevTransProcess( void )
{
    UINT8  len, chtype,i;
    UINT8  intflag, errflag = 0;

    intflag = R8_USB_INT_FG;         //USB中断标志寄存器

    if( intflag & RB_UIF_TRANSFER )  //USB传输完成中断标志位
    {
        //R8_USB_INT_ST：USB中断状态寄存器   MASK_UIS_TOKEN：设备模式下，当前USB传输事务的令牌PID标识   MASK_UIS_ENDP：设备模式下，当前USB传输事务的端点号
        switch ( R8_USB_INT_ST & ( MASK_UIS_TOKEN | MASK_UIS_ENDP ) )
        {
            //前面描述符配置中数据接口使用端点2进行数据输入输出
            case UIS_TOKEN_OUT | 2:
                if (R8_USB_INT_FG & RB_U_TOG_OK)                                    //不同步的数据包将丢弃，RB_U_TOG_OK：当前USB传输DATA0/1同步标志匹配状态位
                {
                    USBByteCount = R8_USB_RX_LEN;                                   //R8_USB_RX_LEN：当前USB端点接收的数据字节数
                    for(i=0; i<USBByteCount; i++)
                    {
                        pEP2_IN_DataBuf[i] = pEP2_OUT_DataBuf[i];
                    }
                    R8_UEP2_T_LEN = USBByteCount;                                   //R8_UEP2_T_LEN：端点2发送长度
                    R8_UEP2_CTRL = (R8_UEP2_CTRL & ~MASK_UEP_T_RES)| UEP_T_RES_ACK; //MASK_UEP_T_RES：端点2的发送器对IN事务的响应控制
                    R8_USB_INT_FG = RB_UIF_TRANSFER;                                //USB传输完成中断标志位，写 1 清零
                }
                break;

            case UIS_TOKEN_IN | 2:
                R8_UEP2_CTRL = (R8_UEP2_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_NAK;
                R8_USB_INT_FG = RB_UIF_TRANSFER;
                break;
            case UIS_TOKEN_SETUP:
                R8_UEP0_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
                len = R8_USB_RX_LEN;

                //获取一系列描述符
                if ( len == sizeof( USB_SETUP_REQ ) )
                {
                    SetupReqLen = pSetupReqPak->wLength;
                    SetupReqCode = pSetupReqPak->bRequest;
                    chtype = pSetupReqPak->bRequestType;

                    len = 0;
                    errflag = 0;
                    if ( ( pSetupReqPak->bRequestType & USB_REQ_TYP_MASK ) != USB_REQ_TYP_STANDARD )  //判断是否为标准请求
                    {
                        //若不是标准请求
                        switch(SetupReqCode)
                        {
                            case GET_LINE_CODING:         //currently configured
                                pDescr = LineCoding;
                                len = sizeof(LineCoding);
                                len = SetupReqLen >= DEFAULT_ENDP0_SIZE ? DEFAULT_ENDP0_SIZE : SetupReqLen;  // 本次传输长度
                                memcpy(pEP0_DataBuf,pDescr,len);
                                pDescr += len;
                                break;
                            case SET_CONTROL_LINE_STATE:  //0x22  generates RS-232/V.24 style control signals
                                break;
                            case SET_LINE_CODING:         //0x20  Configure
                                break;
                            default:
                                errflag = 0xFF;
                        }
                    }
                    else
                    {
                        //若是标准请求
                        switch( SetupReqCode )
                        {
                            case USB_GET_DESCRIPTOR:                   //获取描述符
                            {
                                switch( ((pSetupReqPak->wValue)>>8) )
                                {
                                    case USB_DESCR_TYP_DEVICE:         //设备描述符
                                        pDescr = MyDevDescr;
                                        len = MyDevDescr[0];
                                        break;

                                    case USB_DESCR_TYP_CONFIG:         //配置描述符
                                        pDescr = MyCfgDescr;
                                        len = MyCfgDescr[2];
                                        break;

                                    case USB_DESCR_TYP_STRING:         //字符串描述符
                                        switch( (pSetupReqPak->wValue)&0xff )
                                        {
                                            case 1:
                                                pDescr = MyManuInfo;   //厂商信息
                                                len = MyManuInfo[0];
                                                break;

                                            case 2:
                                                pDescr = MyProdInfo;   //产品信息
                                                len = MyProdInfo[0];
                                                break;

                                            case 0:
                                                pDescr = MyLangDescr;  //语言信息
                                                len = MyLangDescr[0];
                                                break;

                                            case 3:
                                                pDescr = (PUINT8)( &MyProductIDInfo[0] ); //产品序列号
                                                len = sizeof( MyProductIDInfo );
                                                break;

                                            default:
                                                errflag = 0xFF;
                                                break;
                                        }
                                        break;

                                    default :
                                        errflag = 0xff;
                                        break;
                                }

                                if( SetupReqLen>len )   SetupReqLen = len;
                                len = (SetupReqLen >= DevEP0SIZE) ? DevEP0SIZE : SetupReqLen;
                                memcpy( pEP0_DataBuf, pDescr, len );
                                pDescr += len;
                            }
                                break;

                            case USB_SET_ADDRESS:
                                SetupReqLen = (pSetupReqPak->wValue)&0xff;
                                break;

                            case USB_GET_CONFIGURATION:
                                pEP0_DataBuf[0] = UsbConfig;
                                if ( SetupReqLen > 1 ) SetupReqLen = 1;
                                break;

                            case USB_SET_CONFIGURATION:
                                UsbConfig = (pSetupReqPak->wValue)&0xff;
                                break;

                            case USB_CLEAR_FEATURE:
                                if( ( pSetupReqPak->bRequestType & 0x1F ) == USB_REQ_RECIP_DEVICE )  /* 清除设备 */
                                {
                                    if((pSetupReqPak->wValue) == 0x01 )
                                    {
                                       if( MyCfgDescr[ 7 ] & 0x20 )
                                       {
                                           /* 唤醒 */
                                       }
                                       else
                                       {
                                           errflag = 0xFF;                                           /* 操作失败 */
                                       }
                                    }
                                    else
                                    {
                                        errflag = 0xFF;                                              /* 操作失败 */
                                     }
                                }
                                else if ( ( pSetupReqPak->bRequestType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_ENDP )
                                {
                                    switch( (pSetupReqPak->wIndex)&0xff )
                                    {
                                        case 0x82:
                                            R8_UEP2_CTRL = (R8_UEP2_CTRL & ~( RB_UEP_T_TOG|MASK_UEP_T_RES )) | UEP_T_RES_NAK;
                                            break;

                                        case 0x02:
                                            R8_UEP2_CTRL = (R8_UEP2_CTRL & ~( RB_UEP_R_TOG|MASK_UEP_R_RES )) | UEP_R_RES_ACK;
                                            break;

                                        case 0x81:
                                            R8_UEP1_CTRL = (R8_UEP1_CTRL & ~( RB_UEP_T_TOG|MASK_UEP_T_RES )) | UEP_T_RES_NAK;
                                            break;

                                        case 0x01:
                                            R8_UEP1_CTRL = (R8_UEP1_CTRL & ~( RB_UEP_R_TOG|MASK_UEP_R_RES )) | UEP_R_RES_ACK;
                                            break;

                                        default:
                                            errflag = 0xFF;
                                            break;

                                    }
                                }
                                else    errflag = 0xFF;
                                break;

                            case USB_SET_FEATURE:                                          /* Set Feature */
                                if( ( pSetupReqPak->bRequestType & 0x1F ) == USB_REQ_RECIP_DEVICE )                  /* 设置设备 */
                                {
                                    if(( pSetupReqPak->wValue) == 0x01 )
                                    {
                                        if( MyCfgDescr[ 7 ] & 0x20 )
                                        {
                                            ;
                                        }
                                        else
                                        {
                                            errflag = 0xFF;                                        /* 操作失败 */
                                        }
                                     }
                                    else
                                     {
                                         errflag = 0xFF;                                           /* 操作失败 */
                                     }
                                }
                                else if( ( pSetupReqPak->bRequestType & 0x1F ) == USB_REQ_RECIP_ENDP )                /* 设置端点 */
                                {
                                    if(( pSetupReqPak->wValue) == 0x00 )
                                    {
                                        switch(pSetupReqPak->wIndex)
                                        {
                                            case 0x82:
                                                    R8_UEP2_CTRL = (R8_UEP2_CTRL & (~RB_UEP_R_TOG)) | UEP_T_RES_STALL;/* 设置端点2 IN STALL */
                                                    break;
                                            case 0x02:
                                                    R8_UEP2_CTRL = (R8_UEP2_CTRL & (~RB_UEP_R_TOG)) | UEP_R_RES_STALL;/* 设置端点2 OUT Stall */
                                                    break;
                                            case 0x81:
                                                    R8_UEP1_CTRL = (R8_UEP1_CTRL & (~RB_UEP_R_TOG)) | UEP_T_RES_STALL;/* 设置端点1 IN STALL */
                                                    break;
                                            case 0x01:
                                                    R8_UEP1_CTRL = (R8_UEP1_CTRL & (~RB_UEP_R_TOG)) | UEP_R_RES_STALL;/* 设置端点1 OUT Stall */
                                                    break;
                                            default:
                                                errflag = 0xFF;                              /* 操作失败 */
                                                break;
                                        }
                                    }
                                    else
                                    {
                                        errflag = 0xFF;                                      /* 操作失败 */
                                    }
                                }
                                else
                                {
                                    errflag = 0xFF;                                          /* 操作失败 */
                                }
                                break;

                            case USB_GET_INTERFACE:
                                pEP0_DataBuf[0] = 0x00;
                                if ( SetupReqLen > 1 ) SetupReqLen = 1;
                                break;

                            case USB_GET_STATUS:
                                pEP0_DataBuf[0] = 0x00;
                                pEP0_DataBuf[1] = 0x00;
                                if ( SetupReqLen > 2 ) SetupReqLen = 2;
                                break;

                            default:
                                errflag = 0xff;
                                break;
                        }
                    }
                }
                else    errflag = 0xff;

                if( errflag == 0xff)
                {
                    R8_UEP0_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_STALL | UEP_T_RES_STALL;
                }
                else
                {
                    if( chtype & 0x80 )
                    {
                        len = (SetupReqLen>DevEP0SIZE) ? DevEP0SIZE : SetupReqLen;
                        SetupReqLen -= len;
                    }
                    else  len = 0;

                    R8_UEP0_T_LEN = len;
                    R8_UEP0_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;
                }
                break;

            case UIS_TOKEN_IN:
                switch( SetupReqCode )
                {
                    case USB_GET_DESCRIPTOR:
                        len = SetupReqLen >= DevEP0SIZE ? DevEP0SIZE : SetupReqLen;
                        memcpy( pEP0_DataBuf, pDescr, len );
                        SetupReqLen -= len;
                        pDescr += len;
                        R8_UEP0_T_LEN = len;
                        R8_UEP0_CTRL ^= RB_UEP_T_TOG;
                        break;

                    case USB_SET_ADDRESS:
                        R8_USB_DEV_AD = (R8_USB_DEV_AD&RB_UDA_GP_BIT) | SetupReqLen;
                        R8_UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
                        break;

                    default:
                        R8_UEP0_T_LEN = 0;
                        R8_UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
                        break;

                }
                break;

            case UIS_TOKEN_OUT:
                if(SetupReqCode ==SET_LINE_CODING)                      //设置串口属性
                {
                    if (R8_USB_INT_FG & RB_U_TOG_OK)
                    {
                        R8_UEP0_T_LEN = 0;
                        R8_UEP0_CTRL |= UEP_R_RES_ACK | UEP_T_RES_ACK;  // 准备上传0包
                    }
                }
                else
                {
                        R8_UEP0_T_LEN = 0;
                        R8_UEP0_CTRL |= UEP_R_RES_ACK | UEP_T_RES_NAK;  //状态阶段，对IN响应NAK
                }
                break;

            case UIS_TOKEN_OUT | 1:
                break;

            case UIS_TOKEN_IN | 1:
                R8_UEP1_T_LEN = 0;
                R8_UEP1_CTRL = (R8_UEP1_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_NAK;
                break;

            default :
                break;
        }
        R8_USB_INT_FG = RB_UIF_TRANSFER;
    }
    else if( intflag & RB_UIF_BUS_RST )
    {
        R8_USB_DEV_AD = 0;
        R8_UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
        R8_UEP1_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK | RB_UEP_AUTO_TOG;
        R8_UEP2_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK | RB_UEP_AUTO_TOG;
        R8_USB_INT_FG |= RB_UIF_BUS_RST;
    }
    else if( intflag & RB_UIF_SUSPEND )
    {
        if ( R8_USB_MIS_ST & RB_UMS_SUSPEND ) {;}
        else{;}
        R8_USB_INT_FG = RB_UIF_SUSPEND;
    }
    else
    {
        R8_USB_INT_FG = intflag;
    }
}


/*******************************************************************************
* Function Name  : DevEP1_OUT_Deal
* Description    : Deal device Endpoint 1 OUT.
* Input          : l: Data length.
* Return         : None
*******************************************************************************/
void DevEP1_OUT_Deal( uint8 l )
{
    ;
}

/*******************************************************************************
* Function Name  : DevEP2_OUT_Deal
* Description    : Deal device Endpoint 2 OUT.
* Input          : l: Data length.
* Return         : None
*******************************************************************************/
void DevEP2_OUT_Deal( uint8 l )
{
    ;
}

/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB exception.
* Input          : None
* Return         : None
*******************************************************************************/
void USBHD_IRQHandler (void)
{
    USB_DevTransProcess();
}







//-------------------------------------------------------------------------------------------------------------------
//  @brief      USB_CDC发送一个 包，需要在系统频率在72M下面使用
//  @param      *p          要发送的数据指针
//  @param      length      发送多少个数据( length 需要小于64)
//  @return     void
//  Sample usage:
//                  需要在系统频率在72M下面使用
//-------------------------------------------------------------------------------------------------------------------
void cdc_send_pack(uint8 *p, uint32 length)
{
    uint32 i = 0;

    for(i=0; i<length; i++)
    {
       pEP2_IN_DataBuf[i] = p[i];
    }
    DevEP2_IN_Deal(length);


//    //等待发送完成
    while(!(R8_UEP2_CTRL&RB_UEP_T_RES1));

    // bUEP_T_RES1 & bUEP_T_RES0: handshake response type for USB endpoint X transmittal (IN)
    // 00: DATA0 or DATA1 then expecting ACK (ready)
    // 01: DATA0 or DATA1 then expecting no response, time out from host, for non-zero endpoint isochronous transactions
    // 10: NAK (busy)
    // 11: TALL (error)

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      发送图像数据到上位机，需要在系统频率在72M下面使用
//  @param      *image          图像数组
//  @param      length          发送多少个数据( length 需要小于64)
//  @return     void
//  Sample usage:
//                  需要在系统频率在72M下面使用
//-------------------------------------------------------------------------------------------------------------------
void seekfree_sendimg_usb_cdc(uint8 *image, uint32 length)
{
    uint8 send_buffer[4] = {0x00,0xff,0x01,0x01};
    cdc_send_pack(send_buffer, 4);

    while(length)
    {
        if(length > 63)
        {
            cdc_send_pack(image, 63);
            image += 63;
            length -= 63;
        }
        else
        {
            cdc_send_pack(image, length);
            length = 0;
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      USB设备全速设备初始化,需要在系统频率在72M下面使用
//  @param      void          空
//  @return     void
//  Sample usage:
//                  需要在系统频率在72M下面使用
//-------------------------------------------------------------------------------------------------------------------
void usb_cdc_init( void )
{
    // 需要在系统频率在72M下面使用
    // 需要在系统频率在72M下面使用
    // 需要在系统频率在72M下面使用
    // 端点缓冲区初始化
    pEP0_RAM_Addr = EP0_Databuf;
    pEP1_RAM_Addr = EP1_Databuf;
    pEP2_RAM_Addr = EP2_Databuf;
    // 使能usb时钟
    USBHD_ClockCmd(RCC_USBCLKSource_PLLCLK_1Div5,ENABLE);

    // usb设备初始化
    USB_DeviceInit();
    // 使能usb中断
    NVIC_EnableIRQ( USBHD_IRQn );

}
