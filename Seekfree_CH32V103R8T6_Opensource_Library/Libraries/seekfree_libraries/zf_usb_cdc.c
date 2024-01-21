

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
ģ���Զ���USBCDC�豸���̣�
*/

#include "string.h"

/*Global Variable*/
#define DevEP0SIZE  0x40

/*Device Descriptor*/
const uint8  MyDevDescr[] =
{
        0x12,           //�豸���������ȣ�18�ֽ�
        0x01,           //���������ͣ�0x01Ϊ�豸������
        0x10,0x01,      //���豸��ʹ��USB�汾Э�飬��Ϊ��С�˽ṹ�����Ե��ֽ���ǰ����USB1.1�汾Ϊ0x10,0x01��USB2.0Ϊ0x00,0x02
        0x02,           //����룬CDC��Ϊ0x02��CDC��������豸��������ָ���豸���ͣ���0x02���������������ü������������ӿڣ����ᱻϵͳ����Ϊһ��USB�����豸���Ӷ������豸����������
        //��ָ�����豸����Ϊͨ���豸����������ʹ�õ�Э�鶼����ָ��Ϊ0.
        0x00,           //������룬�������bDeviceClassΪ0ʱ��������������bDeviceSubClassҲ����Ϊ0��
        0x00,           //�豸��ʹ�õ�Э�飬Э�������USBЭ��涨�������ֶ�Ϊ0ʱ����ʾ�豸��ʹ�����������Э�顣
        DevEP0SIZE,     //�˵�0��������������ȡֵ8��16��32��64���˴�Ϊ64�ֽ�
        0x86,0x1a,      //����ID
        0x22,0x57,      //��Ʒ�豸ID
        0x00,0x01,      //�豸�汾��
        0x01,           //�������̵��ַ�������ֵ������ֵΪ0ʱ����ʾû�г����ַ���
        0x02,           //������Ʒ���ַ�������ֵ������ֵΪ0ʱ����ʾû�в�Ʒ�ַ���
        0x03,           //�����豸�����к��ַ�������ֵ������ֵΪ0ʱ����ʾû�����к��ַ���
        0x01,           //���ܵ���������ͨ��Ϊ1
};

/* Configration Descriptor */
const uint8  MyCfgDescr[] =
{
        //�����������������ӿڣ�
        0x09,          //�������������ȣ���׼USB��������������Ϊ9�ֽ�
        0x02,          //���������ͣ�����������Ϊ0x02
        0x43,0x00,     //���������������ܳ��ȣ�67�ֽ�
        0x02,          //��������֧�ֵĽӿ�����2���ӿ�
        0x01,          //��ʾ�����õ�ֵ
        0x00,          //���������õ��ַ���������ֵ��0x00��ʾû���ַ���
        0xa0,          //�����豸��һЩ���ԣ��繩�緽ʽ�ͻ��ѵȣ�0xA0��ʾ�豸���߹�����֧��Զ�̻���
        0x32,          //�豸��Ҫ�����߻�ȡ������������0x32��ʾ������100ma

        //����Ϊ�ӿ�0��CDC�ӿڣ����������ӿ����������ܵ������أ����븽����������������һ������
        0x09,          //�ӿ����������ȣ���׼��USB�ӿ�����������Ϊ9�ֽ�
        0x04,          //���������ͣ��ӿ�������Ϊ0x04
        0x00,          //�ýӿڵı�ţ���0��ʼ���˴�Ϊ0x00
        0x00,          //�ýӿڵı��ñ��,ͨ������Ϊ0
        0x01,          //�ýӿ���ʹ�õĶ˵�����0x01��ʾʹ��1���˵㡣������ֶ�Ϊ0�����ʾû�з�0�˵㣬ֻʹ��Ĭ�ϵĿ��ƶ˵㡣CDC�ӿ�ֻʹ��һ���ж�����˵�
        0x02,          //�ýӿ���ʹ�õ��࣬0x02ΪCDC��
        0x02,          //�ýӿ���ʹ�õ����࣬Ҫʵ��USBת���ڣ��ͱ���ʹ��Abstract Control Model���������ģ�ͣ����࣬���ı��Ϊ0x02
        0x01,          //�ýӿ���ʹ�õ�Э�飬ʹ��Common AT Commands��ͨ��AT���Э��
        0x00,          //�ýӿڵ��ַ���������ֵ��0x00��ʾû���ַ���


        //����Ϊ������ӿ�������
        //��������������Ҫ���������ӿڵĹ��ܣ���������������CDC�ӿڣ����ӿڣ�֮��
        //Header Functional Descriptor
        0x05,          //�ù����������ĳ��ȣ�5���ֽ�
        0x24,          //�������������ͣ��̶�λ0x24��CS_INTERFACE�ı��룩
        0x00,          //��������������
        0x10,0x01,     //USBͨ���豸Э��İ汾�š��˴�ΪUSB1.1

        //����������(û��������ӿ�)
        //Call Management Functional Descriptor
        0x05,          //�ù����������ĳ��ȣ�5���ֽ�
        0x24,          //�������������ͣ��̶�λ0x24��CS_INTERFACE�ı��룩
        0x01,          //��������������
        0x00,          //�����豸��������ֻ�������λD0��D1�����壬����λΪ����ֵ0��D0Ϊ0����ʾ�豸�Լ���������ù���Ϊ1���ʾ�Լ�����
        0x00,          //��ʾѡ�����������ù����������ӿڱ�ţ����ڲ�ʹ��������ӿ������ù���������ֶ�����Ϊ0

        //Abstract Control Management Functional Descriptor  ������ƹ�����������
        0x04,          //�ù����������ĳ��ȣ�4���ֽ�
        0x24,          //�������������ͣ��̶�λ0x24��CS_INTERFACE�ı��룩
        0x02,          //��������������
        0x02,          //�����豸������������D7-4λΪ����λ������Ϊ0��֧��Set_Line_Coding��Set_Control_Line_State��Get_Line_Coding�����Serial_State֪ͨ
                       //D0��ʾ�Ƿ�֧����������Set_Comm_Feature��Clear_Comm_Feature��Get_Comm_Feature,Ϊ1��ʾ֧�֣�
                       //D1λ��ʾ�Ƿ�֧��Set_Line_Coding��Set_Control_Line_State��Get_Line_Coding�����Serial_State֪ͨ��Ϊ1��ʾ֧��
                       //D2Ϊ��ʾ�Ƿ�֧��Send_Break��Ϊ1��ʾ֧��
                       //D3��ʾ�Ƿ�֧��Network_Connection֪ͨ��Ϊ1��ʾ֧��

        //Union Functional Descriptor������5�ֽڣ�������һ��ӿ�֮��Ĺ�ϵ���Ա�����Ϊһ�����ܵ�Ԫ����������Щ�ӿ�һ����Ϊ���ӿڣ�������Ϊ�ӽӿ�
        0x05,          //�ù����������ĳ��ȣ�5���ֽ�
        0x24,          //�������������ͣ��̶�λ0x24��CS_INTERFACE�ı��룩
        0x06,          //��������������
        0x00,          //�����ֽ�Ϊ���ӿڱ�ţ��˴�Ϊ���Ϊ0��CDC�ӿ�
        0x01,          //�����ֽ�Ϊ��һ�ӽӿڱ�ţ��˴�Ϊ���1��������ӿڣ�������ֻ��һ���ӽӿ�

        //�ӿ�0��CDC�ӿڣ��Ķ˵�������
        0x07,          //�˵����������ȣ�7�ֽ�
        0x05,          //���������ͣ��˵�������Ϊ0x05
        0x81,          //�ö˵�ĵ�ַ��0x81��ʾ�˵�1��Ϊ����
        0x03,          //�ö˵�����ԡ������λD1-0��ʾ�ö˵�Ĵ������ͣ�0Ϊ���ƴ��䣬1Ϊ��ʱ���䣬2Ϊ�������䣬3Ϊ�жϴ���
        0x40,0x00,     //�ö˵�֧�ֵ��������ȣ�64�ֽ�
        0xFF,          //�˵�Ĳ�ѯʱ��

        //����Ϊ�ӿ�1�����ݽӿڣ�������
        //CDC��ӿڣ��ӿ�0���Ǹ�����������豸�ģ��������Ĵ������ݴ�������������ӿڽ��еġ�����ֻʹ��һ��������ӿڣ����Ϊ1
        0x09,          //�ӿ����������ȣ�9�ֽ�
        0x04,          //���������ͣ��ӿ�������Ϊ0x04
        0x01,          //�ýӿڵı�ţ���0��ʼ���˴�Ϊ0x01
        0x00,          //�ýӿڵı��ñ��
        0x02,          //�ýӿ���ʹ�õĶ˵������ýӿ�Ҫʹ��һ����������˵㣬����˵�����Ϊ2
        0x0a,          //�ýӿ���ʹ�õ��࣬0x0aΪCDC������
        0x00,          //�ýӿ���ʹ�õ�����
        0x00,          //�ýӿ���ʹ�õ�Э��
        0x00,          //�ýӿڵ��ַ���������ֵ��0x00��ʾû���ַ���

        //�ӿ�1��������ӿڣ��Ķ˵�������
        0x07,          //�˵����������ȣ�7�ֽ�
        0x05,          //���������ͣ��˵�������Ϊ0x05
        0x02,          //�ö˵�ĵ�ַ��0x02��ʾ�˵�2��Ϊ���
        0x02,          //�ö˵�����ԡ������λD1-0��ʾ�ö˵�Ĵ������ͣ�0Ϊ���ƴ��䣬1Ϊ��ʱ���䣬2Ϊ�������䣬3Ϊ�жϴ���
        0x40,0x00,     //�ö˵�֧�ֵ��������ȣ�64�ֽ�
        0x00,          //�˵�Ĳ�ѯʱ�䣬����������˵���Ч

        0x07,          //�˵����������ȣ�7�ֽ�
        0x05,          //���������ͣ��˵�������Ϊ0x05
        0x82,          //�ö˵�ĵ�ַ��0x82��ʾ�˵�2��Ϊ����
        0x02,          //�ö˵�����ԡ������λD1-0��ʾ�ö˵�Ĵ������ͣ�0Ϊ���ƴ��䣬1Ϊ��ʱ���䣬2Ϊ�������䣬3Ϊ�жϴ���
        0x40,0x00,     //�ö˵�֧�ֵ��������ȣ�64�ֽ�
        0x00,          //�˵�Ĳ�ѯʱ�䣬����������˵���Ч
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

//CDC����
uint8 LineCoding[7]={0x00,0xe1,0x00,0x00,0x00,0x00,0x08};   //��ʼ��������Ϊ57600��1ֹͣλ����У�飬8����λ��

#define  SET_LINE_CODING                0x20            //Configures DTE rate, stop-bits, parity, and number-of-character
#define  GET_LINE_CODING                0x21            //This request allows the host to find out the currently configured line coding.
#define  SET_CONTROL_LINE_STATE         0x22            //This request generates RS-232/V.24 style control signals.
#define  UART_REV_LEN                   0x40            //���ڽ��ջ�������С

uint8 Receive_Uart_Buf[UART_REV_LEN];   //���ڽ��ջ�����
volatile uint8 Uart_Input_Point = 0;    //ѭ��������д��ָ�룬���߸�λ��Ҫ��ʼ��Ϊ0
volatile uint8 Uart_Output_Point = 0;   //ѭ��������ȡ��ָ�룬���߸�λ��Ҫ��ʼ��Ϊ0
volatile uint8 UartByteCount = 0;       //��ǰ������ʣ���ȡ�ֽ���
volatile uint8 USBByteCount = 0;        //����USB�˵���յ�������
volatile uint8 USBBufOutPoint = 0;      //ȡ����ָ��
volatile uint8 UpPoint2_Busy  = 0;      //�ϴ��˵��Ƿ�æ��־

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

    intflag = R8_USB_INT_FG;         //USB�жϱ�־�Ĵ���

    if( intflag & RB_UIF_TRANSFER )  //USB��������жϱ�־λ
    {
        //R8_USB_INT_ST��USB�ж�״̬�Ĵ���   MASK_UIS_TOKEN���豸ģʽ�£���ǰUSB�������������PID��ʶ   MASK_UIS_ENDP���豸ģʽ�£���ǰUSB��������Ķ˵��
        switch ( R8_USB_INT_ST & ( MASK_UIS_TOKEN | MASK_UIS_ENDP ) )
        {
            //ǰ�����������������ݽӿ�ʹ�ö˵�2���������������
            case UIS_TOKEN_OUT | 2:
                if (R8_USB_INT_FG & RB_U_TOG_OK)                                    //��ͬ�������ݰ���������RB_U_TOG_OK����ǰUSB����DATA0/1ͬ����־ƥ��״̬λ
                {
                    USBByteCount = R8_USB_RX_LEN;                                   //R8_USB_RX_LEN����ǰUSB�˵���յ������ֽ���
                    for(i=0; i<USBByteCount; i++)
                    {
                        pEP2_IN_DataBuf[i] = pEP2_OUT_DataBuf[i];
                    }
                    R8_UEP2_T_LEN = USBByteCount;                                   //R8_UEP2_T_LEN���˵�2���ͳ���
                    R8_UEP2_CTRL = (R8_UEP2_CTRL & ~MASK_UEP_T_RES)| UEP_T_RES_ACK; //MASK_UEP_T_RES���˵�2�ķ�������IN�������Ӧ����
                    R8_USB_INT_FG = RB_UIF_TRANSFER;                                //USB��������жϱ�־λ��д 1 ����
                }
                break;

            case UIS_TOKEN_IN | 2:
                R8_UEP2_CTRL = (R8_UEP2_CTRL & ~MASK_UEP_T_RES) | UEP_T_RES_NAK;
                R8_USB_INT_FG = RB_UIF_TRANSFER;
                break;
            case UIS_TOKEN_SETUP:
                R8_UEP0_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
                len = R8_USB_RX_LEN;

                //��ȡһϵ��������
                if ( len == sizeof( USB_SETUP_REQ ) )
                {
                    SetupReqLen = pSetupReqPak->wLength;
                    SetupReqCode = pSetupReqPak->bRequest;
                    chtype = pSetupReqPak->bRequestType;

                    len = 0;
                    errflag = 0;
                    if ( ( pSetupReqPak->bRequestType & USB_REQ_TYP_MASK ) != USB_REQ_TYP_STANDARD )  //�ж��Ƿ�Ϊ��׼����
                    {
                        //�����Ǳ�׼����
                        switch(SetupReqCode)
                        {
                            case GET_LINE_CODING:         //currently configured
                                pDescr = LineCoding;
                                len = sizeof(LineCoding);
                                len = SetupReqLen >= DEFAULT_ENDP0_SIZE ? DEFAULT_ENDP0_SIZE : SetupReqLen;  // ���δ��䳤��
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
                        //���Ǳ�׼����
                        switch( SetupReqCode )
                        {
                            case USB_GET_DESCRIPTOR:                   //��ȡ������
                            {
                                switch( ((pSetupReqPak->wValue)>>8) )
                                {
                                    case USB_DESCR_TYP_DEVICE:         //�豸������
                                        pDescr = MyDevDescr;
                                        len = MyDevDescr[0];
                                        break;

                                    case USB_DESCR_TYP_CONFIG:         //����������
                                        pDescr = MyCfgDescr;
                                        len = MyCfgDescr[2];
                                        break;

                                    case USB_DESCR_TYP_STRING:         //�ַ���������
                                        switch( (pSetupReqPak->wValue)&0xff )
                                        {
                                            case 1:
                                                pDescr = MyManuInfo;   //������Ϣ
                                                len = MyManuInfo[0];
                                                break;

                                            case 2:
                                                pDescr = MyProdInfo;   //��Ʒ��Ϣ
                                                len = MyProdInfo[0];
                                                break;

                                            case 0:
                                                pDescr = MyLangDescr;  //������Ϣ
                                                len = MyLangDescr[0];
                                                break;

                                            case 3:
                                                pDescr = (PUINT8)( &MyProductIDInfo[0] ); //��Ʒ���к�
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
                                if( ( pSetupReqPak->bRequestType & 0x1F ) == USB_REQ_RECIP_DEVICE )  /* ����豸 */
                                {
                                    if((pSetupReqPak->wValue) == 0x01 )
                                    {
                                       if( MyCfgDescr[ 7 ] & 0x20 )
                                       {
                                           /* ���� */
                                       }
                                       else
                                       {
                                           errflag = 0xFF;                                           /* ����ʧ�� */
                                       }
                                    }
                                    else
                                    {
                                        errflag = 0xFF;                                              /* ����ʧ�� */
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
                                if( ( pSetupReqPak->bRequestType & 0x1F ) == USB_REQ_RECIP_DEVICE )                  /* �����豸 */
                                {
                                    if(( pSetupReqPak->wValue) == 0x01 )
                                    {
                                        if( MyCfgDescr[ 7 ] & 0x20 )
                                        {
                                            ;
                                        }
                                        else
                                        {
                                            errflag = 0xFF;                                        /* ����ʧ�� */
                                        }
                                     }
                                    else
                                     {
                                         errflag = 0xFF;                                           /* ����ʧ�� */
                                     }
                                }
                                else if( ( pSetupReqPak->bRequestType & 0x1F ) == USB_REQ_RECIP_ENDP )                /* ���ö˵� */
                                {
                                    if(( pSetupReqPak->wValue) == 0x00 )
                                    {
                                        switch(pSetupReqPak->wIndex)
                                        {
                                            case 0x82:
                                                    R8_UEP2_CTRL = (R8_UEP2_CTRL & (~RB_UEP_R_TOG)) | UEP_T_RES_STALL;/* ���ö˵�2 IN STALL */
                                                    break;
                                            case 0x02:
                                                    R8_UEP2_CTRL = (R8_UEP2_CTRL & (~RB_UEP_R_TOG)) | UEP_R_RES_STALL;/* ���ö˵�2 OUT Stall */
                                                    break;
                                            case 0x81:
                                                    R8_UEP1_CTRL = (R8_UEP1_CTRL & (~RB_UEP_R_TOG)) | UEP_T_RES_STALL;/* ���ö˵�1 IN STALL */
                                                    break;
                                            case 0x01:
                                                    R8_UEP1_CTRL = (R8_UEP1_CTRL & (~RB_UEP_R_TOG)) | UEP_R_RES_STALL;/* ���ö˵�1 OUT Stall */
                                                    break;
                                            default:
                                                errflag = 0xFF;                              /* ����ʧ�� */
                                                break;
                                        }
                                    }
                                    else
                                    {
                                        errflag = 0xFF;                                      /* ����ʧ�� */
                                    }
                                }
                                else
                                {
                                    errflag = 0xFF;                                          /* ����ʧ�� */
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
                if(SetupReqCode ==SET_LINE_CODING)                      //���ô�������
                {
                    if (R8_USB_INT_FG & RB_U_TOG_OK)
                    {
                        R8_UEP0_T_LEN = 0;
                        R8_UEP0_CTRL |= UEP_R_RES_ACK | UEP_T_RES_ACK;  // ׼���ϴ�0��
                    }
                }
                else
                {
                        R8_UEP0_T_LEN = 0;
                        R8_UEP0_CTRL |= UEP_R_RES_ACK | UEP_T_RES_NAK;  //״̬�׶Σ���IN��ӦNAK
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
//  @brief      USB_CDC����һ�� ������Ҫ��ϵͳƵ����72M����ʹ��
//  @param      *p          Ҫ���͵�����ָ��
//  @param      length      ���Ͷ��ٸ�����( length ��ҪС��64)
//  @return     void
//  Sample usage:
//                  ��Ҫ��ϵͳƵ����72M����ʹ��
//-------------------------------------------------------------------------------------------------------------------
void cdc_send_pack(uint8 *p, uint32 length)
{
    uint32 i = 0;

    for(i=0; i<length; i++)
    {
       pEP2_IN_DataBuf[i] = p[i];
    }
    DevEP2_IN_Deal(length);


//    //�ȴ��������
    while(!(R8_UEP2_CTRL&RB_UEP_T_RES1));

    // bUEP_T_RES1 & bUEP_T_RES0: handshake response type for USB endpoint X transmittal (IN)
    // 00: DATA0 or DATA1 then expecting ACK (ready)
    // 01: DATA0 or DATA1 then expecting no response, time out from host, for non-zero endpoint isochronous transactions
    // 10: NAK (busy)
    // 11: TALL (error)

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ͼ�����ݵ���λ������Ҫ��ϵͳƵ����72M����ʹ��
//  @param      *image          ͼ������
//  @param      length          ���Ͷ��ٸ�����( length ��ҪС��64)
//  @return     void
//  Sample usage:
//                  ��Ҫ��ϵͳƵ����72M����ʹ��
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
//  @brief      USB�豸ȫ���豸��ʼ��,��Ҫ��ϵͳƵ����72M����ʹ��
//  @param      void          ��
//  @return     void
//  Sample usage:
//                  ��Ҫ��ϵͳƵ����72M����ʹ��
//-------------------------------------------------------------------------------------------------------------------
void usb_cdc_init( void )
{
    // ��Ҫ��ϵͳƵ����72M����ʹ��
    // ��Ҫ��ϵͳƵ����72M����ʹ��
    // ��Ҫ��ϵͳƵ����72M����ʹ��
    // �˵㻺������ʼ��
    pEP0_RAM_Addr = EP0_Databuf;
    pEP1_RAM_Addr = EP1_Databuf;
    pEP2_RAM_Addr = EP2_Databuf;
    // ʹ��usbʱ��
    USBHD_ClockCmd(RCC_USBCLKSource_PLLCLK_1Div5,ENABLE);

    // usb�豸��ʼ��
    USB_DeviceInit();
    // ʹ��usb�ж�
    NVIC_EnableIRQ( USBHD_IRQn );

}
