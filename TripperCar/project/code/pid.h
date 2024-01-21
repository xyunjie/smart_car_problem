/*
 * PID.h
 *
 *  Created on: Nov 27, 2021
 *      Author: Accepted
 */

#ifndef _PID_H_
#define _PID_H_

#include <zf_common_typedef.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MINMAX(input, low, upper) MIN(MAX(input, low), upper)

extern float pid_umax, pid_umin;

/**
 * 电机参数
 */
typedef struct pid_param_t {
    float kp;
    float ki;
    float kd;

    float err;
    float err_pre;
    float err_pre_pre;
    float out;
}MotorParamPID;

/**
 * 舵机参数
 */
typedef struct SteeringParameter {
    //pwm值
    int ActualPWM;
    //角度
    float Angle;
    //PID
    float Error;
    float Error_Last;
    float ErrorSum;

    float Kp;
    float Kd;
    float Ki;

    //限制
    uint32 Limit;
}SteeringParameter;

float MotorPID(MotorParamPID *pid, float err);
void SteeringPID(SteeringParameter *steering , float Deviation);

#endif /* USER_INCLUDE_PID_H_ */
