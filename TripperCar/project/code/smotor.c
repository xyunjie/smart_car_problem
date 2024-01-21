/*
 * smotor.c
 *
 *  Created on: 2022Äê3ÔÂ27ÈÕ
 *      Author: Accepted
 */
#include "smotor.h"
#include "pid.h"
#include "imgproc.h"
SteeringParameter steering;
/**
 * ·½Ïò¿ØÖÆ
 */

void SERVO_Set (float SERVO_Set)
{
    pwm_set_duty(TIM9_PWM_MAP3_CH4_D15, SERVO_Set);
}

void DirectionControl(float Deviation)
{
    steering.Limit = 100;
    if (type == OPENCIRCUIT)
    {
//        steering.Kp = 100.0;
//        steering.Kd = 0;
        steering.Kp = 1.53;
        steering.Kd = 0.61;
    }
    else if (type == CIRCLE)
    {
        steering.Kp = 2.3;
        steering.Kd = 0.22;
    }
    else if (type == CROSS)
    {
        steering.Kp = 2.3;
        steering.Kd = 0.3;
    }
    else if (abs(PathDeviation) >= 35)
    {
        steering.Kp = 2.3;
        steering.Kd = 0.3;
    }
    else if (abs(PathDeviation) >= 45)
    {
        steering.Kp = 3.1;
        steering.Kd = 0.5;
    }
    else
    {
        // 2.6m/s       p 2.3       d0.18
        steering.Kp = 2.1;
        steering.Kd = 0.34;
    }
    if (type == STOP || type == WAIT)
    {
        SERVO_Set(SteeringGear_Median);
    }
    else if (type == HINDER)
    {
        if (hinder == HINDER_STATUS_1)
        {
            // ÕÏ°­×´Ì¬1
            SteeringPID(&steering, -60);
            SERVO_Set(steering.ActualPWM);
        }
        if (hinder == HINDER_STATUS_2)
        {
            // ÕÏ°­×´Ì¬2
            SteeringPID(&steering, 70);
            SERVO_Set(steering.ActualPWM);
        }
        if (hinder == HINDER_STATUS_3)
        {
            // ÕÏ°­×´Ì¬3
            int temp = (60 - hinder_time * 15) <= -40 ? -40 : (60 - hinder_time * 15);
            SteeringPID(&steering, temp);
            SERVO_Set(steering.ActualPWM);
        }
    }
    else if (type == ZEBRA)
    {
        SteeringPID(&steering, 70);
        SERVO_Set(steering.ActualPWM);
    }
    else
    {
        SteeringPID(&steering, Deviation);
        SERVO_Set(steering.ActualPWM);
    }
}
