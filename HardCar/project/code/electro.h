/*
 * electro.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Accepted
 */

#ifndef ELECTRO_H_
#define ELECTRO_H_

#define ADC_MIN_NUM 3

#include "zf_driver_adc.h"
extern float adcNum[6];
extern uint16 infraredNum;
extern float AdcDeviation;
extern float g_fDirectionControlOut;
extern float DirectionErr[2];

void Get_Adc_Price();
void Get_Infrared_Price();
void display_adc(void);
void Difference_Ratio_And(void);

#endif /* ELECTRO_H_ */
