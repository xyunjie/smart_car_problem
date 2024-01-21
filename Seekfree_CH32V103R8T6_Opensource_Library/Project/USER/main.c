/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            main
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.51
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2021-10-20
 ********************************************************************************************************************/
//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�

//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//�Ҽ��������̣�ѡ��ˢ��


#include "headfile.h"


/*********************************************************************
 * @fn      TIM1_Dead_Time_Init
 *
 * @brief   Initializes TIM1 complementary output and dead time.
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *
 * @return  none
 */
void TIM1_Dead_Time_Init( uint32 freq, uint32 duty )
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    TIM_OCInitTypeDef TIM_OCInitStructure={0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};
    TIM_BDTRInitTypeDef TIM_BDTRInitStructure={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA  | RCC_APB2Periph_GPIOB | RCC_APB2Periph_TIM1, ENABLE );

    /* TIM1_CH1 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOA, &GPIO_InitStructure );

    /* TIM1_CH1N */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOB, &GPIO_InitStructure );

    uint16 match_temp;                                          //ռ�ձ�ֵ
    uint16 period_temp;                                         //����ֵ
    uint16 freq_div = 0;                                        //��Ƶֵ

    int pwm_sys_clk = 88000000;
    // �����Ƶ
    freq_div = (uint16)((pwm_sys_clk / freq) >> 16);                            //���ٷ�Ƶ
    period_temp = (uint16)(pwm_sys_clk/(freq*(freq_div + 1)));                  //����
    match_temp = (period_temp - 1) * duty / 10000;                         //ռ�ձ�

    TIM_TimeBaseInitStructure.TIM_Period = period_temp - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = match_temp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OC1Init( TIM1, &TIM_OCInitStructure );

    TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;
    TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStructure.TIM_DeadTime = 10;  // ���ø�λ
    TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
    TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
    TIM_BDTRConfig( TIM1, &TIM_BDTRInitStructure );

    TIM_CtrlPWMOutputs(TIM1, ENABLE );
    TIM_OC1PreloadConfig( TIM1, TIM_OCPreload_Disable );
    TIM_ARRPreloadConfig( TIM1, ENABLE );
    TIM_Cmd( TIM1, ENABLE );
}

void buck_init(uint32 freq, uint32 duty)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    uint16 match_temp;                                          //ռ�ձ�ֵ
    uint16 period_temp;                                         //����ֵ
    uint16 freq_div = 0;                                        //��Ƶֵ

    gpio_init(A6, GPO, 0, SPEED_50MHZ|OUT_AF_PP);                                       //PWM���ų�ʼ��

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);    //ʹ�ܶ�ʱ��3ʱ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);        //ʹ��AFIO���ù���ģ��ʱ��

    //������ӳ��
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);

    //��ȡϵͳ��Ƶ
    sys_clk = 8000000 * (((RCC->CFGR0 >> 18)&0x0F) + 2);

    freq_div = (uint16)((sys_clk / freq) >> 16);                            //���ٷ�Ƶ
    period_temp = (uint16)(sys_clk/(freq*(freq_div + 1)));                  //����
    match_temp = period_temp * duty / PWM_DUTY_MAX;                         //ռ�ձ�

    //��ʼ��TIM1-4
    TIM_TimeBaseStructure.TIM_Period = period_temp - 1;                     //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = freq_div;                         //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                 //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;             //TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

    //��ʼ��TIM1-4 PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                       //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;           //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_Pulse = match_temp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                //�������:TIM����Ƚϼ��Ը�
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_Low;               //�������:TIM����Ƚϼ��Ը�
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

    TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );  //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_CtrlPWMOutputs(TIM3, ENABLE );
    TIM_OC3Init(TIM3, &TIM_OCInitStructure );
    TIM_OC3PreloadConfig( TIM3, TIM_OCPreload_Disable );
    TIM_ARRPreloadConfig( TIM3, ENABLE );
    TIM_Cmd( TIM3, ENABLE );
}

int main(void)
{
    //�ر����ж�
    DisableGlobalIRQ();
    //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    board_init();

    //�˴���д�û�����(���磺�����ʼ�������)
    gpio_init(B12, GPO, 0, GPIO_PIN_CONFIG);
    gpio_init(B6, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(B5, GPO, 1, GPIO_PIN_CONFIG);
    gpio_init(B3, GPI, 0, IN_PULLUP);
    TIM1_Dead_Time_Init( 156300, 5000 );
//    TIM1_Dead_Time_Init( 550, 280 );
    int switch_status = 0;
    //    buck_init(300000, 4700);
    timer_pwm_init(PWM3_CH1_A6, 300000, 4700);
//    timer_pit_interrupt_ms(TIMER_4, 10);
    uart_init(UART_2, 115200, UART2_TX_A2, UART2_RX_A3);
//    uart_rx_irq(UART_2, ENABLE);
    //���ж������
    EnableGlobalIRQ(0);
    while(1)
    {
//        uart_putstr(UART_2, (char *)"111111111");
        //�˴���д��Ҫѭ��ִ�еĴ���;
        uint8 data = 0;
        uint8 get_status = uart_query(UART_2, &data);
        if (get_status)
        {
            if (data != 0)
            {
                if (data == 1)
                {
                    if (switch_status == 0)
                    {
                        gpio_set(B12, 1);
                        switch_status = 1;
                        gpio_set(B5, 0);
                    }
//                    gpio_toggle(B6);
                }
                else if (data == 2)
                {
                    if (switch_status == 1)
                    {
                        gpio_set(B12, 0);
                        switch_status = 0;
                        gpio_set(B5, 1);
                    }
//                    gpio_toggle(B5);
                }
            }
        }

        if (gpio_get(B3) == 0 && switch_status == 0)
        {
            // ��������
            gpio_set(B12, 1);
            switch_status = 1;
            gpio_set(B5, 0);
        }
        else if (gpio_get(B3) == 0 && switch_status == 1)
        {
            gpio_set(B12, 0);
            switch_status = 0;
            gpio_set(B5, 1);
        }
        systick_delay_ms(300);
    }
}

