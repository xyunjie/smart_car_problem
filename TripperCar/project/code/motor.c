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
/** PWM角度比*/
float PWMAngleRatio = 0.2;
/** 轮距（两后轮中心的距离）*/
float TrackWidth = 0.154;
/** 轴距（前轮中心与后轮中心的距离）*/
float WheelBase = 0.2;
/** 角度弧度比*/
float AngleRadianRatio = 0.01745;
//编码器脉冲数-弧度转换系数
float RadianCoefficient = 0.0030664;
//控制频率
float ControlFrequency = 100.00;
//编码器-轮胎减速比
float ReductionRatio = 0.4285714;
//后轮半径
float TireRadius = 0.032;
/** 差速*/
float diff;
// 左右电机参数
MotorParam motor_left, motor_right;
MotorParam* motor_text;

uint8 s1;
uint8 s2;
uint8 s3;


/*
 * @brief    获取编码器的值
 *
 * @param    motor_param_t* ：电机参数
 *
 *
 * @state    使用中
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
 * @brief    设置电机的值
 *
 * @param    motor_param_t* ：电机参数
 *
 *
 * @state    使用中
 *
 * @see      Motor_Set(&motor_l, &motor_r);
 */
void MotorSet(MotorParam* left, MotorParam* right)
{
    // 左轮
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

    // 右轮
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
 * @brief    C车阿克曼差速模型
 *
 * @param    SteeringParameter ：舵机转向参数
 *
 * @return   ratio ：差速比
 *
 * @state    使用中
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
 * @brief    编码器角速度转为线速度
 *
 * @param    MotorParam ：电机参数
 *
 *
 * @state    使用中
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
 * @brief    电机控制
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      motor_control();  //电机控制
 */
void MotorControl()
{
    //设置pid值
    motor_left.pid.kp = 4000;
    motor_left.pid.ki = 800;
    motor_left.pid.kd = 1200;

    //右轮
    motor_right.pid.kp = 4000;
    motor_right.pid.ki = 800;
    motor_right.pid.kd = 1200;

    //获取编码器的值
    if (type != WAIT)
        EncoderGet(&motor_left, &motor_right);
    motor_text = &motor_right;

    //归一化
    VelocityNormalization(&motor_left);
    VelocityNormalization(&motor_right);

    //获取目标速度
    float targetSpeed = GetTargetSpeed();

    //差速
    float differential = DifferentialRatioCalculation(&steering) * targetSpeed;
//    float differential = 0;
    //设置电机目标速度
    motor_left.target_speed = targetSpeed + differential;
    motor_right.target_speed = targetSpeed - differential;

    //计算误差

    //PID控制
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
