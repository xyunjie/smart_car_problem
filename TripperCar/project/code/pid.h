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
 * �������
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
 * �������
 */
typedef struct SteeringParameter {
    //pwmֵ
    int ActualPWM;
    //�Ƕ�
    float Angle;
    //PID
    float Error;
    float Error_Last;
    float ErrorSum;

    float Kp;
    float Kd;
    float Ki;

    //����
    uint32 Limit;
}SteeringParameter;

float MotorPID(MotorParamPID *pid, float err);
void SteeringPID(SteeringParameter *steering , float Deviation);

#endif /* USER_INCLUDE_PID_H_ */
