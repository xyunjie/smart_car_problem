/*
 * motor.c
 *
 *  Created on: Mar 26, 2022
 *      Author: Accepted
 */

#include "motor.h"
#include "smotor.h"
#include "pid.h"
#include "imgproc.h"
#include <math.h>
/** PWM�Ƕȱ�*/
float PWMAngleRatio = 0.2;
/** �־ࣨ���������ĵľ��룩*/
float TrackWidth = 0.154;
/** ��ࣨǰ��������������ĵľ��룩*/
float WheelBase = 0.2;
/** �ǶȻ��ȱ�*/
float AngleRadianRatio = 0.01745;
//������������-����ת��ϵ��
float RadianCoefficient = 0.0030664;
//����Ƶ��
float ControlFrequency = 100.00;
//������-��̥���ٱ�
float ReductionRatio = 0.4285714;
//���ְ뾶
float TireRadius = 0.032;
/** ����*/
float diff;
// ���ҵ������
MotorParam motor_left, motor_right;
MotorParam* motor_text;

uint8 s1;
uint8 s2;
uint8 s3;


/*
 * @brief    ��ȡ��������ֵ
 *
 * @param    motor_param_t* ���������
 *
 *
 * @state    ʹ����
 *
 * @see      ENC_get(&motor_l, &motor_r);
 */
void EncoderGet(MotorParam* left, MotorParam* right)
{
    right->encoder_speed = encoder_get_count(TIM4_ENCOEDER);
    encoder_clear_count(TIM4_ENCOEDER);

    left->encoder_speed = -encoder_get_count(TIM3_ENCOEDER);
    encoder_clear_count(TIM3_ENCOEDER);
}

/*
 * @brief    ���õ����ֵ
 *
 * @param    motor_param_t* ���������
 *
 *
 * @state    ʹ����
 *
 * @see      Motor_Set(&motor_l, &motor_r);
 */
void MotorSet(MotorParam* left, MotorParam* right)
{
    // ����
    if(left->duty > 0)
    {
        pwm_set_duty(TIM1_PWM_MAP3_CH2_E11, left->duty);
        pwm_set_duty(TIM1_PWM_MAP3_CH1_E9, 0);

    }
    else
    {
        pwm_set_duty(TIM1_PWM_MAP3_CH2_E11, 0);
        pwm_set_duty(TIM1_PWM_MAP3_CH1_E9, -left->duty);
    }

    // ����
    if(right->duty > 0)
    {
        pwm_set_duty(TIM1_PWM_MAP3_CH4_E14, 0);
        pwm_set_duty(TIM1_PWM_MAP3_CH3_E13, right->duty);

    }
    else
    {
        pwm_set_duty(TIM1_PWM_MAP3_CH4_E14, -right->duty);
        pwm_set_duty(TIM1_PWM_MAP3_CH3_E13, 0);
    }
}

/*
 * @brief    C������������ģ��
 *
 * @param    SteeringParameter �����ת�����
 *
 * @return   ratio �����ٱ�
 *
 * @state    ʹ����
 *
 * @see      DifferentialRatioCalculation(&steering);
 */
float DifferentialRatioCalculation(SteeringParameter *steering)
{
    float ratio;
    steering->Angle = PWMAngleRatio * (float)(SteeringGear_Median - steering->ActualPWM);
    ratio = (TrackWidth / (2 * WheelBase)) * tan(steering->Angle * AngleRadianRatio);
    return ratio;
}

/*
 * @brief    ���������ٶ�תΪ���ٶ�
 *
 * @param    MotorParam ���������
 *
 *
 * @state    ʹ����
 *
 * @see      VelocityNormalization(&motor_left);
 */
void VelocityNormalization(MotorParam* motor)
{
    motor->encoder_angular_velocity = RadianCoefficient * ControlFrequency * motor->encoder_speed;
    motor->wheel_angular_velocity = ReductionRatio * motor->encoder_angular_velocity;
    motor->wheel_linear_velocity = TireRadius * motor->wheel_angular_velocity;
}

float GetTargetSpeed()
{
    float target_speed = 1.0;
    if (type == ZEBRA)
    {
        target_speed = BARN_Speed;
    }
    else if (type == CROSS)
    {
        target_speed = CROSS_Speed;
    }
    else if (type == STOP || type == WAIT || type == FINISH)
    {
        target_speed = 0;
    }
    else if (type == OUTBARN)
    {
        target_speed = Noraml_Speed;
    }
    else if (type == HINDER)
    {
        target_speed = HINDER_Speed;
    }
    else if (type == OPENCIRCUIT)
    {
//        float speed = Noraml_Speed - open_time * 1 < OPENCIRCUIT_Speed ? OPENCIRCUIT_Speed : Noraml_Speed;
        target_speed = OPENCIRCUIT_Speed;
    }
    else if (type == CIRCLE)
    {
        target_speed = CIRCLE_Speed;
    }
    else if (type == RAMP)
    {
        target_speed = RAMP_Speed;
    }
    else
    {
        if (ABS(PathDeviation) > 25)
        {
            target_speed = CROSS_Speed;
        }
//        else if (left_continuation_line >= 65 && right_continuation_line >= 65)
//        {
//            target_speed = 2.6;
//        }
        else
        {
            if (s1 == 0 && s2 == 0)
            {
                target_speed = Noraml_Speed;
            }
            else if (s1 == 1 && s2 == 0)
            {
                target_speed = 2.6;
            }
            else if (s1 == 0 && s2 == 1)
            {
                target_speed = 2.4;
            }
            else if (s1 == 1 && s2 == 1)
            {
                target_speed = 3;
            }
        }
    }
    return target_speed;
}

/*
 * @brief    �������
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      motor_control();  //�������
 */
void MotorControl()
{
    //����pidֵ
    motor_left.pid.kp = 4000;
    motor_left.pid.ki = 800;
    motor_left.pid.kd = 1200;

    //����
    motor_right.pid.kp = 4000;
    motor_right.pid.ki = 800;
    motor_right.pid.kd = 1200;

    //��ȡ��������ֵ
    if (type != WAIT)
        EncoderGet(&motor_left, &motor_right);
    motor_text = &motor_right;

    //��һ��
    VelocityNormalization(&motor_left);
    VelocityNormalization(&motor_right);

    //��ȡĿ���ٶ�
    float targetSpeed = GetTargetSpeed();

    //����
    float differential = DifferentialRatioCalculation(&steering) * targetSpeed;
//    float differential = 0;
    //���õ��Ŀ���ٶ�
    motor_left.target_speed = targetSpeed + differential;
    motor_right.target_speed = targetSpeed - differential;

    //�������

    //PID����
    if (type == WAIT)
    {
        motor_left.duty = 0;
        motor_right.duty = 0;
    }
    else
    {
        motor_left.duty = MotorPID(&motor_left.pid, motor_left.target_speed - motor_left.wheel_linear_velocity);
        motor_right.duty = MotorPID(&motor_right.pid, motor_right.target_speed - motor_right.wheel_linear_velocity);
    }
    MotorSet(&motor_left, &motor_right);
}
