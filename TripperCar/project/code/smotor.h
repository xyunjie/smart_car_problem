/*
 * smotor.h
 *
 *  Created on: 2022Äê3ÔÂ27ÈÕ
 *      Author: Accepted
 */

#ifndef SMOTOR_H_
#define SMOTOR_H_
#include "pid.h"

#define SteeringGear_Median 1030     //1030

extern SteeringParameter steering;

void DirectionControl(float Deviation);

#endif /* SMOTOR_H_ */
