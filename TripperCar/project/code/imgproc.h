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

/* ABS 绝对值函数 */
#define ABS(a) (((a) > (0)) ? (a) : (-a))
/* ImgH 一幅图像高度*/
#define ImgH MT9V03X_H
/* ImgH 一幅图像宽度*/
#define ImgW MT9V03X_W
/* WHITE 白色点值定义*/
#define WHITE 254
/* BLACK 黑色点值定义*/
#define BLACK 0
/* PathRow 前瞻高度 可修改*/       // 2.6m/s   32
#define PathRow  30
/* RightBoundary 右边界值*/
#define RightBoundary ImgW - 2
/* LeftBoundary 左边界值*/
#define LeftBoundary 1
/* CenterPoint 中点位置*/
#define CenterPoint ImgW / 2
/* LED_ON 开启LED*/
#define LED_ON gpio_set_level(B12, 0);
/* LED_OFF 关闭LED*/
#define LED_OFF gpio_set_level(B12, 1);
/* BING_ON 开启蜂鸣器*/
#define BING_ON gpio_set_level(C1, 1);
/* BING_OFF 关闭蜂鸣器*/
#define BING_OFF gpio_set_level(C1, 0);
/* 灰度直方图的大小*/
#define HISTOGRAM_SIZE 256
/* 表示灰度级别的数量*/
#define LEVELS 256

#define THRESHOLD_MAX 230
#define THRESHOLD_MIN 210

/**
 * @brief 赛道元素类型
 */
typedef enum {
    WAIT,       /*WAIT      待发车  */
    NORMAL,     /*NORMAL    正常巡线状态  */
    CROSS,      /*CROSS     十字路口状态  */
    CIRCLE,     /*CIRCLE    环岛状态            */
    LONG,       /*LONG      长直道状态       */
    ZEBRA,      /*ZEBRA     斑马线状态       */
    OUTBARN,    /*OUTBARN   出库状态            */
    NONE,       /*NONE      无状态                 */
    STOP,       /*STOP      停车状态            */
    HINDER,     /*HINDER    障碍                      */
    RAMP,       /*HINDER    坡道                      */
    OPENCIRCUIT, /*OPENCIRCUIT 断路                */
    FINISH      /*FINISH 完成                */
}EleType;

/**
 * @brief 道路行状态
 */
typedef enum {
    LOST,       /*LOST          丢线          */
    NO_LOST     /*NO_LOST       不丢线          */
} LineStatus;

typedef struct {
    // 当前节点的行位置
    uint8 position;
    // 当前预测节点状态
    LineStatus lineStatus;
} LineNode;

/**
 * @brief 十字状态
 */
typedef enum {
    // 刚刚判断为十字
    CROSS_NONE,
    //发现了十字
    CROSS_FOUND,
    // 十字入口处
    CROSS_ENTRY,
    //运行到十字内部
    CROSS_RUN,
    // 十字出口处
    CROSS_EXPORT,
    //出十字
    CROSS_EXIT,
} CrossStatus;

/**
 * @brief 断路状态
 */
typedef enum {
    // 刚刚判断为断路
    OPEN_NONE,
    //发现了断路
    OPEN_FOUND,
    // 正在运行断路
    OPEN_RUN
} OpenStatus;

/**
 * @brief 障碍状态
 */
typedef enum {
    // 刚刚判断为障碍
    HINDER_NONE,
    // 障碍转向
    HINDER_STATUS_1,
    // 障碍转回
    HINDER_STATUS_2,
    // 障碍调整方向
    HINDER_STATUS_3
} HinderStatus;

/**
 * @brief 环岛检测状态
 */
typedef enum {
    CIRCLE_CHECK_NONE,
    CIRCLE_CHECK_STATUS_1,
    CIRCLE_CHECK_STATUS_2,
    CIRCLE_CHECK_STATUS_3,
    CIRCLE_CHECK_STATUS_4
} CircleCheckStatus;

/**
 * @brief 环岛方向
 */
typedef enum {
    RIGHT_CIRCLE,
    LEFT_CIRCLE
} CircleDirection;

/**
 * @brief 环岛参数
 */
typedef enum {
    CIRCLE_NONE = 0,    /*CIRCLE_NONE   没有找到环岛*/
    CIRCLE_FOUND,       /*CIRCLE_FOUND      找到环岛*/
    CIRCLE_ENTRY,       /*CIRCLE_ENTRY  到达环岛入口*/
    CIRCLE_RUN,         /*CIRCLE_RUN  运行到环岛内部*/
    CIRCLE_EXIT         /*CIRCLE_EXIT       退出环岛*/
}CircleStatus;

/** RoadErr 中线偏差数组 */
extern int RoadErr[ImgH];
/** RoadCenter  中线基准 */
extern uint8 RoadCenter;
/** type    赛道元素类型*/
extern EleType type;
/** test    测试用*/
extern int test[4];
extern float ftest[4];

/** PathDeviation   路径偏差*/
extern float PathDeviation;

/** bin_img   二值化后图像*/
extern uint8 bin_img[ImgH][ImgW];

/** left_lost_num   左丢线数量*/
extern int left_lost_num;
/** right_lost_num   右丢线数量*/
extern int right_lost_num;

/** left_continuation_line   左连续点数量*/
extern uint8 left_continuation_line;

/** left_continuation_line   右连续点数量*/
extern uint8 right_continuation_line;

/** height   图像可用高度*/
extern uint8 height;

/** 拨码修改图像阈值*/
extern uint8 t1;
extern uint8 t2;
extern uint8 t3;
/** 拨码修改图像阈值*/

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



/** 运行出库 */
void Run_OutBarn(void);
/** 运行斑马线 */
void Run_Zebra(void);
/** 运行障碍 */
void Run_Hinder(void);
/** 运行十字 */
void Run_Cross(void);
/** 运行坡道 */
void Run_Ramp(void);
/** 运行断路 */
void Run_OpenCricuit(void);
/** 运行环岛 */
void Run_Circle(void);
/** 检测元素 */
void CheckElementType(void);

#endif /* IMGPROC_H_ */
