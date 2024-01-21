/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library 即（CH32V307VCT6 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是CH32V307VCT6 开源库的一部分
*
* CH32V307VCT6 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MounRiver Studio V1.8.1
* 适用平台          CH32V307VCT6
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期                                      作者                             备注
* 2022-09-15        大W            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "smotor.h"
#include "imgproc.h"
#include "motor.h"
#include "electro.h"
#include "bluetooth.h"

void init();

int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 144MHz
//    debug_init();                                                             // 初始化默认 Debug UART
    // 此处编写用户代码 例如外设初始化代码等
    init();
    uint8 status = bluetooth_ch9141_init();

//    gpio_init(D4, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // 初始化 LED1 输出 默认高电平 推挽输出模式
    if(bluetooth_ch9141_init())                                                 // 判断是否通过初始化
    {
        while(1)                                                                // 初始化失败就在这进入死循环
        {
            gpio_toggle_level(D7);                                            // 翻转 LED 引脚输出电平 控制 LED 亮灭
            system_delay_ms(100);                                               // 短延时快速闪灯表示异常
        }
    }
    bluetooth_ch9141_send_byte('\r');
    bluetooth_ch9141_send_byte('\n');
    bluetooth_ch9141_send_string("SEEKFREE ch9141 demo.\r\n");                  // 初始化正常 输出测试信息
    Get_Adc_Price();
    type = WAIT;
    int displayImageStatus = gpio_get_level(D1);
    t1 = gpio_get_level(E6);
    t2 = gpio_get_level(E5);
    t3 = gpio_get_level(E4);

    s1 = gpio_get_level(E3);
    s2 = gpio_get_level(E2);
//    bluetooth_ch9141_send_byte(10);
    tft180_show_int(80, 100, status, 3);
    // 此处编写用户代码 例如外设初始化代码等
    while(1)
    {
        Get_Infrared_Price();
        if (type == WAIT)
        {
            if (ChargeAdcNum >= 1620)
            {
                // 发送
                Send_Start();
            }
            Wait_Start();
        }
        if(mt9v03x_finish_flag)
        {
            // 图像处理
            Process_Image();
            /****元素判断****/
            CheckElementType();
            /****元素判断****/

            if (type == OUTBARN)
                Run_OutBarn();
            if (type == ZEBRA)
                Run_Zebra();
            if (type == CROSS)
                Run_Cross();
            if (type == RAMP)
                Run_Ramp();
            if (type == CIRCLE)
                Run_Circle();
            if (type == HINDER)
                Run_Hinder();
            if (type == OPENCIRCUIT)
                Run_OpenCricuit();
            if (type != STOP)
                Emergency_Stop();
            //出赛道停车判断
            if (type != STOP && type != WAIT)
                check_stop();
            if (type == STOP)
                Send_Emergency_Stop();

            //巡线
            Line_patrol();
            if (displayImageStatus || type == WAIT)
                display();
            else
                display_txt();
            // 清除标志位
            mt9v03x_finish_flag = 0;
        }
        // 输出ADC的值
//        display_adc();
    }
}

void init()
{
    /****************PWM***************/
    pwm_init(TIM1_PWM_MAP3_CH1_E9, 13000, 0);
    pwm_init(TIM1_PWM_MAP3_CH2_E11, 13000, 0);

    pwm_init(TIM1_PWM_MAP3_CH4_E14, 13000, 0);
    pwm_init(TIM1_PWM_MAP3_CH3_E13, 13000, 0);

    pwm_init(TIM9_PWM_MAP3_CH4_D15, 50, SteeringGear_Median);
    pwm_init(TIM10_PWM_MAP0_CH3_C3, 50, 200);         //硬件刹车            未刹车值200
    /****************PWM***************/

    /****************TFT***************/
    tft180_set_dir(TFT180_CROSSWISE_180);
    tft180_init();
    /****************TFT***************/

    /****************PIT***************/
    pit_ms_init(TIM8_PIT, 20);
    // 电机控制
    pit_ms_init(TIM7_PIT, 10);
    // 中断计时
    pit_ms_init(TIM5_PIT, 50);
    /****************PIT***************/

    /****************ENCODER***************/
    encoder_quad_init(TIM4_ENCOEDER, TIM4_ENCOEDER_MAP1_CH1_D12, TIM4_ENCOEDER_MAP1_CH2_D13);
    encoder_quad_init(TIM3_ENCOEDER, TIM3_ENCOEDER_MAP3_CH1_C6, TIM3_ENCOEDER_MAP3_CH2_C7);
    /****************ENCODER***************/

    /****************UART***************/
    uart_init(UART_2, 115200, UART2_MAP0_TX_A2, UART2_MAP0_RX_A3);
    uart_init(UART_6, 115200, UART6_MAP0_TX_C0, UART6_MAP0_RX_C1);
    /****************UART***************/

    /****************Bluetooth***************/
//    int status = bluetooth_ch9141_init();
    /****************Bluetooth***************/

    /****************LED***************/
    gpio_init(D3, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(D4, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(D7, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(D6, GPO, 1, GPIO_PIN_CONFIG);
    /****************LED***************/

    /****************BUZZER***************/
    gpio_init(C1, GPO, 0, GPIO_PIN_CONFIG);
    /****************BUZZER***************/

    /****************DIP-SWITCH***************/
    gpio_init(E6, GPI, 0, GPI_PULL_DOWN);
    gpio_init(E5, GPI, 0, GPI_PULL_DOWN);
    gpio_init(E4, GPI, 0, GPI_PULL_DOWN);
    gpio_init(E3, GPI, 0, GPI_PULL_DOWN);
    gpio_init(E2, GPI, 0, GPI_PULL_DOWN);
    gpio_init(D1, GPI, 0, GPI_PULL_DOWN);
    gpio_init(B1, GPI, 1, GPI_PULL_UP);
    /****************DIP-SWITCH***************/

    /****************OP-INIT***************/
    adc_init(ADC1_IN1_A1, ADC_12BIT);   //ADC0  红外
    adc_init(ADC1_IN7_A7, ADC_12BIT);   //ADC1
    adc_init(ADC1_IN14_C4, ADC_12BIT);   //ADC2
    adc_init(ADC1_IN15_C5, ADC_12BIT);   //ADC3
    adc_init(ADC1_IN8_B0, ADC_12BIT);   //ADC4
    adc_init(ADC1_IN0_A0, ADC_12BIT);   //ADC5
    adc_init(ADC1_IN12_C2, ADC_12BIT);   //电容采集
//    adc_init(ADC1_IN9_B1, ADC_12BIT);   //ADC6

    /****************OP-INIT***************/

    /****************MT9V03X***************/
    mt9v03x_init();
    /****************MT9V03X***************/
}
