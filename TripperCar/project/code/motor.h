/*
 * motor.h
 *
 *  Created on: Mar 26, 2022
 *      Author: Accepted
 */

#ifndef MOTOR_H_
#define MOTOR_H_
#include "pid.h"

/* Noraml_Speed ����ѭ���ٶ� */
#define Noraml_Speed 2.6
/* CROSS_Speed  ʮ��·���ٶ� */
#define CROSS_Speed 2.3
/* FORK_Speed   ����·���ٶ� */
#define FORK_Speed 0.45
/* CIRCLE_Speed     �����ٶ� */
#define CIRCLE_Speed 2.2
/* CIRCLE_Speed     ������ */
#define BARN_Speed 2.6
/* CIRCLE_Speed     �ϰ� */
#define HINDER_Speed 2.0
/* OPENCIRCUIT_Speed     ��· */
#define OPENCIRCUIT_Speed 1.4    // 1.5
/* OPENCIRCUIT_Speed     �µ� */
#define RAMP_Speed 2.0    // 1.5

/**
 * @brief �������
 */
typedef struct motor_param_t {
    float encoder_speed;    /*encoder_speed ��������õ��ٶ�*/
    float target_speed;     /*target_speed Ŀ���ٶ�*/
    float encoder_angular_velocity; /*�������Ƕ��ٶ�*/
    float wheel_angular_velocity;   /*���ֽ��ٶ�*/
    float wheel_linear_velocity;    /*����ת��*/

    float duty;             /*ռ�ձ�ֵ*/
    MotorParamPID pid;        /*PID�ջ�����*/
}MotorParam;

extern MotorParam* motor_text;
extern uint8 s1;
extern uint8 s2;
extern uint8 s3;

void MotorControl();

#endif /* MOTOR_H_ */
