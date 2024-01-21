/*
 * motor.h
 *
 *  Created on: Mar 26, 2022
 *      Author: Accepted
 */

#ifndef MOTOR_H_
#define MOTOR_H_
#include "pid.h"

/* Noraml_Speed 正常循迹速度 */
#define Noraml_Speed 2.6
/* CROSS_Speed  十字路口速度 */
#define CROSS_Speed 2.3
/* FORK_Speed   三岔路口速度 */
#define FORK_Speed 0.45
/* CIRCLE_Speed     环岛速度 */
#define CIRCLE_Speed 2.2
/* CIRCLE_Speed     斑马线 */
#define BARN_Speed 2.6
/* CIRCLE_Speed     障碍 */
#define HINDER_Speed 2.0
/* OPENCIRCUIT_Speed     断路 */
#define OPENCIRCUIT_Speed 1.4    // 1.5
/* OPENCIRCUIT_Speed     坡道 */
#define RAMP_Speed 2.0    // 1.5

/**
 * @brief 电机参数
 */
typedef struct motor_param_t {
    float encoder_speed;    /*encoder_speed 编码器测得的速度*/
    float target_speed;     /*target_speed 目标速度*/
    float encoder_angular_velocity; /*编码器角度速度*/
    float wheel_angular_velocity;   /*车轮角速度*/
    float wheel_linear_velocity;    /*车轮转速*/

    float duty;             /*占空比值*/
    MotorParamPID pid;        /*PID闭环控制*/
}MotorParam;

extern MotorParam* motor_text;
extern uint8 s1;
extern uint8 s2;
extern uint8 s3;

void MotorControl();

#endif /* MOTOR_H_ */
