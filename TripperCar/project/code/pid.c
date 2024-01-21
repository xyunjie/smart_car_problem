#include "PID.h"
#include "zf_common_headfile.h"
#include "smotor.h"

///////////////////////
float pid_umax = 8000;
float pid_umin = -8000;
//////////////////////

/*
 * PID.c
 *
 *  Created on: Nov 27, 2021
 *      Author: Accepted
 */

void SteeringPID(SteeringParameter *steering , float Deviation)
{
    int PIDLoc;

    steering->Error = Deviation;

    PIDLoc = (int)(steering->Kp * steering->Error + steering->Kd * (steering->Error_Last - steering->Error));

    steering->ActualPWM = SteeringGear_Median + PIDLoc;

    if(steering->ActualPWM > (SteeringGear_Median + steering->Limit))
        steering->ActualPWM = (SteeringGear_Median + steering->Limit);

    if(steering->ActualPWM < (SteeringGear_Median - steering->Limit))
        steering->ActualPWM = (SteeringGear_Median - steering->Limit);
}


/**
 * 电机PI
 */

float MotorPID(MotorParamPID *pid, float err)
{
    pid->err = err;
    pid->out += pid->kp * (pid->err - pid->err_pre) + pid->ki * pid->err + pid->kd * (pid->err - 2 * pid->err_pre + pid->err_pre_pre);
    pid->err_pre_pre = pid->err_pre;
    pid->err_pre = pid->err;
    //pi输出最大值限幅
    if(pid->out > pid_umax) pid->out = pid_umax;
    //pi输出最小值限幅
    if(pid->out < pid_umin) pid->out = pid_umin;

    return pid->out;
}
