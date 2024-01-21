/*
 * smotor.h
 *
 *  Created on: 2022��3��27��
 *      Author: Accepted
 */

#ifndef SMOTOR_H_
#define SMOTOR_H_
#include "pid.h"

#define SteeringGear_Median 1030     //1030

extern SteeringParameter steering;

void DirectionControl(float Deviation);

#endif /* SMOTOR_H_ */
