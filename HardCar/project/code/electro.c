/*
 * electro.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Accepted
 */
#include "electro.h"
#include "zf_device_tft180.h"
float adcNum[6] = {0};
uint16 ADC_min = 25;
uint16 ADC_max = 3000 ;
uint16 infraredNum = 0;
float AdcDeviation = 0;
float DirectionErr[2];        //����ƫ�g_fDirectionError[0]Ϊһ��ˮƽ��еĲ�Ⱥ�ƫ�
                              //��g_fDirectionError[1]Ϊһ�Դ�ֱ��еĲ�Ⱥ�ƫ�
float DirectionErr_dot[2];    //����ƫ��΢�֣�g_fDirectionError_dot[0]Ϊһ��ˮƽ��еĲ�Ⱥ�ƫ��΢�֣�
                              //��g_fDirectionError_dot[1]Ϊһ�Դ�ֱ��еĲ�Ⱥ�ƫ��΢�֣�
float DirectionErrTemp[2][5]; //��ʱ�������

float g_fDirectionControlOut; //�������
float g_fDirectionControlOut_straight;   //ֱ
float difference = 0 ;     //��
float combine = 0 ;        //��
float a = 1 ;
float b = 1.5 ;
float g_dirControl_P = 98;  //�������P2150    760   420
float g_dirControl_D = 25;   //�������D       430
/*
 * @brief    ��ȡ���ֵ
 *
 * @see      Get_Adc_Price();
 */
void Get_Adc_Price()
{
    adcNum[0] = adc_mean_filter_convert(ADC1_IN7_A7, 5);

    adcNum[1] = adc_mean_filter_convert(ADC1_IN14_C4, 5);

    adcNum[2] = adc_mean_filter_convert(ADC1_IN15_C5, 5);

    adcNum[3] = adc_mean_filter_convert(ADC1_IN8_B0, 5);

    adcNum[4] = adc_mean_filter_convert(ADC1_IN0_A0, 5);

    adcNum[0] = (float)100*(adcNum[0]-ADC_min)/(ADC_max-ADC_min);          //��һ��
    adcNum[1] = (float)100*(adcNum[1]-ADC_min)/(ADC_max-ADC_min);
    adcNum[2] = (float)100*(adcNum[2]-ADC_min)/(ADC_max-ADC_min);
    adcNum[3] = (float)100*(adcNum[3]-ADC_min)/(ADC_max-ADC_min);
    adcNum[4] = (float)100*(adcNum[4]-ADC_min)/(ADC_max-ADC_min);

    adcNum[0] = (adcNum[0] > 100 ? 100 : adcNum[0]);       //���ֵ�޷�
    adcNum[1] = (adcNum[1] > 100 ? 100 : adcNum[1]);
    adcNum[2] = (adcNum[2] > 100 ? 100 : adcNum[2]);
    adcNum[3] = (adcNum[3] > 100 ? 100 : adcNum[3]);
    adcNum[4] = (adcNum[4] > 100 ? 100 : adcNum[4]);
}
/*
 * @brief    ��ȡ����ֵ
 *
 * @see      Get_Infrared_Price();
 */
void Get_Infrared_Price()
{
    infraredNum = adc_mean_filter_convert(ADC1_IN1_A1, 5);
}
/*
 * @brief    ��Ⱥ��㷨
 *
 * @return   float   ����Ⱥ�ֵ
 *
 * @see      Difference_Ratio_And();
 */
void Difference_Ratio_And()
{
//        difference = (adcNum[0] - adcNum[4])+(adcNum[0]-adcNum[3]);
//        combine    = (adcNum[0] + adcNum[4])+(adcNum[0]+adcNum[3]);
        DirectionErr[0] = (adcNum[0] - adcNum[4]) / (adcNum[0] + adcNum[4]); //��-��ˮƽ��еĲ�Ⱥ���Ϊƫ��
        DirectionErr[0] = (DirectionErr[0] >= 1 ? 1 : DirectionErr[0]);                                      //ƫ���޷�
        DirectionErr[0] = (DirectionErr[0] <= -1 ? -1 : DirectionErr[0]);
//        //��ֱ���ƫ�����
//        DirectionErr[1] = ((float)adcNum[0] - (float)adcNum[5]) / ((float)adcNum[0] + (float)adcNum[5]); //��-�Ҵ�ֱ��еĲ�Ⱥ���Ϊƫ��
//        DirectionErr[1] = (DirectionErr[1] >= 1 ? 1 : DirectionErr[1]);                                      //ƫ���޷�
//        DirectionErr[1] = (DirectionErr[1] <= -1 ? -1 : DirectionErr[1]);
        //ˮƽ���ƫ��΢�ּ���(��ʷ���ѭ������)
        DirectionErrTemp[0][4] = DirectionErrTemp[0][3];
        DirectionErrTemp[0][3] = DirectionErrTemp[0][2];
        DirectionErrTemp[0][2] = DirectionErrTemp[0][1];
        DirectionErrTemp[0][1] = DirectionErrTemp[0][0];
        DirectionErrTemp[0][0] = DirectionErr[0];
        DirectionErr_dot[0] = 5 * (DirectionErrTemp[0][0] - DirectionErrTemp[0][3]);   //ˮƽ��е�ƫ��΢��
        DirectionErr_dot[0] = (DirectionErr_dot[0] > 0.7 ? 0.7 : DirectionErr_dot[0]); //ƫ��΢���޷�
        DirectionErr_dot[0] = (DirectionErr_dot[0] < -0.7 ? -0.7 : DirectionErr_dot[0]);
//        //��ֱ���ƫ��΢�ּ���(��ʷ������ѭ��)
//        DirectionErrTemp[1][4] = DirectionErrTemp[1][3];
//        DirectionErrTemp[1][3] = DirectionErrTemp[1][2];
//        DirectionErrTemp[1][2] = DirectionErrTemp[1][1];
//        DirectionErrTemp[1][1] = DirectionErrTemp[1][0];
//        DirectionErrTemp[1][0] = DirectionErr[1];
//        DirectionErr_dot[1] = 5 * (DirectionErrTemp[1][0] - DirectionErrTemp[1][3]);   //��ֱ��е�ƫ��΢��
//        DirectionErr_dot[1] = (DirectionErr_dot[1] > 0.7 ? 0.7 : DirectionErr_dot[1]); //ƫ��΢���޷�
//        DirectionErr_dot[1] = (DirectionErr_dot[1] < -0.7 ? -0.7 : DirectionErr_dot[1]);


        g_fDirectionControlOut = DirectionErr[0] * g_dirControl_P  + DirectionErr_dot[0] * g_dirControl_D ; //�������    λ��ʽPD
        g_fDirectionControlOut = (g_fDirectionControlOut > 100 ? 100 : g_fDirectionControlOut);
        g_fDirectionControlOut = (g_fDirectionControlOut < -100 ? -100 : g_fDirectionControlOut);
}

void display_adc()
{
    uint16 numPoint = 50;
    tft180_show_string(0, 0, "AD:");
    tft180_show_float(numPoint, 0, AdcDeviation, 4, 2);
    tft180_show_string(0, 20, "LL:");
    tft180_show_float(numPoint, 20, adcNum[0], 4, 2);
    tft180_show_string(0, 40, "LR:");
    tft180_show_float(numPoint, 40, adcNum[1], 4, 2);
    tft180_show_string(0, 60, "MD:");
    tft180_show_float(numPoint, 60, adcNum[2], 4, 2);
    tft180_show_string(0, 80, "RL:");
    tft180_show_float(numPoint, 80, adcNum[3], 4, 2);
    tft180_show_string(0, 100, "RR:");
    tft180_show_float(numPoint, 100, adcNum[4], 4, 2);
}
