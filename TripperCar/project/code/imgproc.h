/*
 * imgproc.h
 *
 *  Created on: Mar 21, 2022
 *      Author: Accepted
 */

#ifndef IMGPROC_H_
#define IMGPROC_H_
#include <zf_common_headfile.h>
#include <zf_device_tft180.h>

/* ABS ����ֵ���� */
#define ABS(a) (((a) > (0)) ? (a) : (-a))
/* ImgH һ��ͼ��߶�*/
#define ImgH MT9V03X_H
/* ImgH һ��ͼ����*/
#define ImgW MT9V03X_W
/* WHITE ��ɫ��ֵ����*/
#define WHITE 254
/* BLACK ��ɫ��ֵ����*/
#define BLACK 0
/* PathRow ǰհ�߶� ���޸�*/       // 2.6m/s   32
#define PathRow  30
/* RightBoundary �ұ߽�ֵ*/
#define RightBoundary ImgW - 2
/* LeftBoundary ��߽�ֵ*/
#define LeftBoundary 1
/* CenterPoint �е�λ��*/
#define CenterPoint ImgW / 2
/* LED_ON ����LED*/
#define LED_ON gpio_set_level(B12, 0);
/* LED_OFF �ر�LED*/
#define LED_OFF gpio_set_level(B12, 1);
/* BING_ON ����������*/
#define BING_ON gpio_set_level(C1, 1);
/* BING_OFF �رշ�����*/
#define BING_OFF gpio_set_level(C1, 0);
/* �Ҷ�ֱ��ͼ�Ĵ�С*/
#define HISTOGRAM_SIZE 256
/* ��ʾ�Ҷȼ��������*/
#define LEVELS 256

#define THRESHOLD_MAX 230
#define THRESHOLD_MIN 210

/**
 * @brief ����Ԫ������
 */
typedef enum {
    WAIT,       /*WAIT      ������  */
    NORMAL,     /*NORMAL    ����Ѳ��״̬  */
    CROSS,      /*CROSS     ʮ��·��״̬  */
    CIRCLE,     /*CIRCLE    ����״̬            */
    LONG,       /*LONG      ��ֱ��״̬       */
    ZEBRA,      /*ZEBRA     ������״̬       */
    OUTBARN,    /*OUTBARN   ����״̬            */
    NONE,       /*NONE      ��״̬                 */
    STOP,       /*STOP      ͣ��״̬            */
    HINDER,     /*HINDER    �ϰ�                      */
    RAMP,       /*HINDER    �µ�                      */
    OPENCIRCUIT, /*OPENCIRCUIT ��·                */
    FINISH      /*FINISH ���                */
}EleType;

/**
 * @brief ��·��״̬
 */
typedef enum {
    LOST,       /*LOST          ����          */
    NO_LOST     /*NO_LOST       ������          */
} LineStatus;

typedef struct {
    // ��ǰ�ڵ����λ��
    uint8 position;
    // ��ǰԤ��ڵ�״̬
    LineStatus lineStatus;
} LineNode;

/**
 * @brief ʮ��״̬
 */
typedef enum {
    // �ո��ж�Ϊʮ��
    CROSS_NONE,
    //������ʮ��
    CROSS_FOUND,
    // ʮ����ڴ�
    CROSS_ENTRY,
    //���е�ʮ���ڲ�
    CROSS_RUN,
    // ʮ�ֳ��ڴ�
    CROSS_EXPORT,
    //��ʮ��
    CROSS_EXIT,
} CrossStatus;

/**
 * @brief ��·״̬
 */
typedef enum {
    // �ո��ж�Ϊ��·
    OPEN_NONE,
    //�����˶�·
    OPEN_FOUND,
    // �������ж�·
    OPEN_RUN
} OpenStatus;

/**
 * @brief �ϰ�״̬
 */
typedef enum {
    // �ո��ж�Ϊ�ϰ�
    HINDER_NONE,
    // �ϰ�ת��
    HINDER_STATUS_1,
    // �ϰ�ת��
    HINDER_STATUS_2,
    // �ϰ���������
    HINDER_STATUS_3
} HinderStatus;

/**
 * @brief �������״̬
 */
typedef enum {
    CIRCLE_CHECK_NONE,
    CIRCLE_CHECK_STATUS_1,
    CIRCLE_CHECK_STATUS_2,
    CIRCLE_CHECK_STATUS_3,
    CIRCLE_CHECK_STATUS_4
} CircleCheckStatus;

/**
 * @brief ��������
 */
typedef enum {
    RIGHT_CIRCLE,
    LEFT_CIRCLE
} CircleDirection;

/**
 * @brief ��������
 */
typedef enum {
    CIRCLE_NONE = 0,    /*CIRCLE_NONE   û���ҵ�����*/
    CIRCLE_FOUND,       /*CIRCLE_FOUND      �ҵ�����*/
    CIRCLE_ENTRY,       /*CIRCLE_ENTRY  ���ﻷ�����*/
    CIRCLE_RUN,         /*CIRCLE_RUN  ���е������ڲ�*/
    CIRCLE_EXIT         /*CIRCLE_EXIT       �˳�����*/
}CircleStatus;

/** RoadErr ����ƫ������ */
extern int RoadErr[ImgH];
/** RoadCenter  ���߻�׼ */
extern uint8 RoadCenter;
/** type    ����Ԫ������*/
extern EleType type;
/** test    ������*/
extern int test[4];
extern float ftest[4];

/** PathDeviation   ·��ƫ��*/
extern float PathDeviation;

/** bin_img   ��ֵ����ͼ��*/
extern uint8 bin_img[ImgH][ImgW];

/** left_lost_num   ��������*/
extern int left_lost_num;
/** right_lost_num   �Ҷ�������*/
extern int right_lost_num;

/** left_continuation_line   ������������*/
extern uint8 left_continuation_line;

/** left_continuation_line   ������������*/
extern uint8 right_continuation_line;

/** height   ͼ����ø߶�*/
extern uint8 height;

/** �����޸�ͼ����ֵ*/
extern uint8 t1;
extern uint8 t2;
extern uint8 t3;
/** �����޸�ͼ����ֵ*/

extern OpenStatus open;

extern HinderStatus hinder;

extern int zebra_time;
extern int hinder_time;
extern int circle_time;
extern int ramp_time;
extern int cross_time;
extern int open_time;
extern int outbarn_time;

void search_line(void);
void left_Patching(int16 dx1, int16 dy1, int16 dx2, int16 dy2);
void right_Patching(int16 dx1, int16 dy1, int16 dx2, int16 dy2);
void Process_Image(void);

void check_cross(void);
void check_circle(void);
void check_zebra(void);
void check_ramp(void);
void check_hinder(void);
void check_stop(void);
void check_opencircuit(void);
void Line_patrol(void);
void display (void);
void display_txt(void);



/** ���г��� */
void Run_OutBarn(void);
/** ���а����� */
void Run_Zebra(void);
/** �����ϰ� */
void Run_Hinder(void);
/** ����ʮ�� */
void Run_Cross(void);
/** �����µ� */
void Run_Ramp(void);
/** ���ж�· */
void Run_OpenCricuit(void);
/** ���л��� */
void Run_Circle(void);
/** ���Ԫ�� */
void CheckElementType(void);

#endif /* IMGPROC_H_ */
