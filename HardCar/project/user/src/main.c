/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library ����CH32V307VCT6 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���CH32V307VCT6 ��Դ���һ����
*
* CH32V307VCT6 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2022-09-15        ��W            first version
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
    clock_init(SYSTEM_CLOCK_144M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 144MHz
//    debug_init();                                                             // ��ʼ��Ĭ�� Debug UART
    // �˴���д�û����� ���������ʼ�������
    init();
    Get_Adc_Price();
    type = WAIT;
    int displayImageStatus = gpio_get_level(D1);
    t1 = gpio_get_level(E6);
    t2 = gpio_get_level(E5);
    t3 = gpio_get_level(E4);

    s1 = gpio_get_level(E3);
    s2 = gpio_get_level(E2);

    if(bluetooth_ch9141_init())                                                 // �ж��Ƿ�ͨ����ʼ��
    {
        while(1)                                                                // ��ʼ��ʧ�ܾ����������ѭ��
        {
            gpio_toggle_level(D7);                                            // ��ת LED ���������ƽ ���� LED ����
            system_delay_ms(100);                                               // ����ʱ�������Ʊ�ʾ�쳣
        }
    }
    bluetooth_ch9141_send_byte('\r');
    bluetooth_ch9141_send_byte('\n');
    bluetooth_ch9141_send_string("SEEKFREE ch9141 demo.\r\n");                  // ��ʼ������ ���������Ϣ
//    tft180_show_int(1, 1, 10, 3);
    // �˴���д�û����� ���������ʼ�������
//    char data[50];
    while(1)
    {
//        sprintf(data, "%f,%f\n", motor_text->wheel_linear_velocity, motor_text->target_speed);
//        uart_write_string(UART_2, data);
        Get_Infrared_Price();
        if (type == WAIT)
        {
            if(gpio_get_level(B1) == 0)
            {
                gpio_set_level(C3, 1);
                system_delay_ms(300);
                gpio_set_level(C3, 0);
                outbarn = OUTBARN_STATUS_0;
                type = OUTBARN;
            }
        }
        if(mt9v03x_finish_flag)
        {
            // ͼ����
            Process_Image();
            /****Ԫ���ж�****/
            CheckElementType();
            /****Ԫ���ж�****/

            if (type == CHARGE)
                Run_Charge();
            if (type == ERR_CHARGE)
                Run_Err_Charge();
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
            if (type == STOP)
                Send_Emergency_Stop();
            //������ͣ���ж�
            if (type != STOP && type != WAIT && type != OUTBARN && type != CHARGE)
                check_stop();

            //Ѳ��
            Line_patrol();
            if (displayImageStatus || type == WAIT)
                display();
            else
                display_txt();
            // �����־λ
            mt9v03x_finish_flag = 0;
        }
        // ���ADC��ֵ
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
    /****************PWM***************/

    /****************TFT***************/
    tft180_set_dir(TFT180_CROSSWISE_180);
    tft180_init();
    /****************TFT***************/

    /****************PIT***************/
    pit_ms_init(TIM8_PIT, 20);
    // �������
    pit_ms_init(TIM7_PIT, 10);
    // �жϼ�ʱ
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

    /****************LED***************/
    gpio_init(D3, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(D4, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(D7, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(D6, GPO, 1, GPIO_PIN_CONFIG);
    /****************LED***************/

    /****************BUZZER***************/
    gpio_init(C3, GPO, 0, GPIO_PIN_CONFIG);
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
    adc_init(ADC1_IN1_A1, ADC_12BIT);   //ADC0  ����
    adc_init(ADC1_IN7_A7, ADC_12BIT);   //ADC1
    adc_init(ADC1_IN14_C4, ADC_12BIT);   //ADC2
    adc_init(ADC1_IN15_C5, ADC_12BIT);   //ADC3
    adc_init(ADC1_IN8_B0, ADC_12BIT);   //ADC4
    adc_init(ADC1_IN0_A0, ADC_12BIT);   //ADC5
//    adc_init(ADC1_IN9_B1, ADC_12BIT);   //ADC6

    /****************OP-INIT***************/

    /****************MT9V03X***************/
    mt9v03x_init();
    /****************MT9V03X***************/
}
