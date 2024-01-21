/*
 * imgproc.c
 *
 *  Created on: Mar 21, 2022
 *      Author: Accepted
 */



#include <imgproc.h>
#include <motor.h>
#include <string.h>
#include <zf_device_mt9v03x_dvp.h>
#include <math.h>
#include "electro.h"
#include "bluetooth.h"

/** 二值化图像 */
uint8 bin_img[ImgH][ImgW] = {0};
uint8 stop_last[ImgH][ImgW] = {0};
uint8 stop_left[ImgH] = {0};
uint8 stop_right[ImgH] = {0};

/** 新左边界*/
LineNode leftLine[ImgH] = {0};
/** 新右边界*/
LineNode rightLine[ImgH] = {0};

/** 左严重跳变 */
uint8 left_very_jump;
/** 左严重跳变位置 */
uint8 left_very_jump_row;

/** 右严重跳变 */
uint8 right_very_jump;
/** 右严重跳变位置 */
uint8 right_very_jump_row;

/** 中线数组 */
uint8 center[MT9V03X_H] = {0};
/** 中线偏差数组*/
int RoadErr[ImgH];
/** 中线基准*/
uint8 RoadCenter = ImgW / 2;
/** 路径偏差*/
float PathDeviation;
/** 可用图像高度*/
uint8 height;
/** 前瞻位置*/
uint8 prospect;

/** 测试*/
int test[4];
float ftest[4];

/** 丢线数量*/
int left_lost_num;
int right_lost_num;

/** 左右点数量 */
int left_point_num;
int right_point_num;

/** 赛道元素类型*/
EleType type;

uint8 enable_team = 0;
uint8 left_continuation_line = 0;
uint8 right_continuation_line = 0;

/*元素计时*/
int charge_time = 0;
int zebra_time = 0;
int outbarn_time = 0;
int hinder_time = 0;
int circle_time = 0;
int ramp_time = 0;
int cross_time = 0;
int open_time = 0;
/*元素计时*/

/*元素状态变量*/
CrossStatus cross;
OpenStatus open;
HinderStatus hinder;
OutbarnStatus outbarn;
ChargeStatus charge;
// 圆环
CircleCheckStatus circleCheckStatus = CIRCLE_CHECK_NONE;
CircleDirection circleDirection;
CircleStatus circle;
/*元素状态变量*/

// 图像阈值
uint8 t1 = 0;
uint8 t2 = 0;
uint8 t3 = 0;


/*
 * @brief    池化算法
 *
 * @param    image    ： 预处理图像指针
 *
 * @see      minPooling(mt9v03x_image, 2, outImage);
 */
void minPooling(uint8 image[ImgH][ImgW], int poolSize, uint8 outImage[ImgH / 2][ImgW / 2])
{
    int outHeight = ImgH / poolSize;
    int outWeight = ImgW / poolSize;
    for (int i = 0; i < outHeight; i++)
    {
        for (int j = 0; j < outWeight; j++)
        {
            int start_row = i * poolSize;
            int end_row = start_row + poolSize;
            int start_col = j * poolSize;
            int end_col = start_col + poolSize;
            int min_value = image[start_row][start_col];
            for (int row = start_row; row < end_row; row++) {
                for (int col = start_col; col < end_col; col++) {
                    int pixel_value = image[row][col];
                    if (pixel_value < min_value) {
                        min_value = pixel_value;
                    }
                }
            }

            outImage[i][j] = min_value;
        }
    }
}

/*
 * @brief    大津法动态阈值
 *
 * @param    tmImgage    ： 待求阈值图像数组
 *
 * @return   Threshold   ：大津法最佳阈值
 *
 * @see      GetOSTU(mt9v03x_image_dvp);  //获得摄像头读取到图像的最佳阈值
 */
short GetOSTU (unsigned char tmImage[ImgH][ImgW])
{
    signed short i, j;
    unsigned long Amount = 0;
    unsigned long PixelBack = 0;
    unsigned long PixelshortegralBack = 0;
    unsigned long Pixelshortegral = 0;
    signed long PixelshortegralFore = 0;
    signed long PixelFore = 0;
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
    signed short MinValue, MaxValue;
    signed short Threshold = 0;
    short HistoGram[256] = {0};

    for (j = 0; j < ImgH; j++)
    {
        for (i = 0; i < ImgW; i++)
        {
            HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //获取最小灰度的值
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //获取最大灰度的值

    if (MaxValue == MinValue)
        return MaxValue;         // 图像中只有一个颜色
    if (MinValue + 1 == MaxValue)
        return MinValue;        // 图像中只有二个颜色

    for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        //  像素总数

    Pixelshortegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        Pixelshortegral += HistoGram[j] * j;        //灰度值总数
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];     //前景像素点数
        PixelFore = Amount - PixelBack;           //背景像素点数
        OmegaBack = (float) PixelBack / Amount;   //前景像素百分比
        OmegaFore = (float) PixelFore / Amount;   //背景像素百分比
        PixelshortegralBack += HistoGram[j] * j;  //前景灰度值
        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //背景灰度值
        MicroBack = (float) PixelshortegralBack / PixelBack;   //前景灰度百分比
        MicroFore = (float) PixelshortegralFore / PixelFore;   //背景灰度百分比
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //计算类间方差
        if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //返回最佳阈值;
}

/*
 * @brief    左补线函数
 *
 * @param    dx1    ： 起始位置纵坐标
 * @param    dy1    ： 起始位置横坐标
 * @param    dx2    ： 结束位置纵坐标
 * @param    dy2    ：结束位置横坐标
 *
 * @return   无
 *
 * @see      left_Patching(1, ImgH - 1, ImgW - 1, 1);  //将左线从左下角拉到右上角
 */
void left_Patching(int16 dx1, int16 dy1, int16 dx2, int16 dy2)
{
    int16 beginLine = MIN(dy1, dy2);
    int16 endLine = MAX(dy1, dy2);
    int16 t;
    for (int i = beginLine + 1; i < endLine; i++)
    {
        t = (uint8)((i - dy1) / (float)(dy2 - dy1) * (dx2 - dx1) + dx1);
        if (t <= 0 || t >= ImgW)
            continue;
        leftLine[i].position = t;
    }
}

/*
 * @brief    右补线函数
 *
 * @param    dx1    ： 起始位置纵坐标
 * @param    dy1    ： 起始位置横坐标
 * @param    dx2    ： 结束位置纵坐标
 * @param    dy2    ：结束位置横坐标
 *
 * @return   无
 *
 * @see      right_Patching(ImgW - 1, ImgH - 1, 1, 1);  //将右线从右下角拉到左上角
 */
void right_Patching(int16 dx1, int16 dy1, int16 dx2, int16 dy2)
{
    int16 beginLine = MIN(dy1, dy2);
    int16 endLine = MAX(dy1, dy2);
    int16 t;
    for (int i = beginLine + 1; i < endLine; i++)
    {
        t = (uint8)((i - dy1) / (float)(dy2 - dy1) * (dx2 - dx1) + dx1);
        if (t <= 0 || t >= ImgW)
            continue;
        rightLine[i].position = t;
    }
}

/*
 * @brief    搜线函数
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      search_line();  //获得左右边线
 */
void search_line()
{
    // 初始化左右边界
    for (int i = 0; i < ImgH ; i++)
    {
        leftLine[i].position = LeftBoundary;
        leftLine[i].lineStatus = NO_LOST;
        rightLine[i].position = RightBoundary;
        rightLine[i].lineStatus = NO_LOST;
    }
    //定义左右边线找到
    uint8 Find_Left = 0, Find_Right = 0;
    //初始化左右丢线数量
    left_lost_num = right_lost_num = 0;
    right_point_num = left_point_num = 0;
    //搜索第一个左点
    if (bin_img[ImgH - 1][CenterPoint] == BLACK)
    {
        //从左向右扫描
        for (int i = 1; i < ImgW - 2; i++)
        {
            if (bin_img[ImgH - 1][i] == WHITE && bin_img[ImgH - 1][i + 1] == BLACK)
            {
                //第一个白黑跳变
                leftLine[ImgH - 1].position = LeftBoundary;
                leftLine[ImgH - 1].lineStatus = LOST;
                rightLine[ImgH - 1].position = i + 1;
                right_point_num = 1;
                break;
            }
            else if (bin_img[ImgH - 1][i] == BLACK && bin_img[ImgH - 1][i + 1] == WHITE)
            {
                //第一个黑白跳变点
                leftLine[ImgH - 1].position = i + 1;
                rightLine[ImgH - 1].lineStatus = LOST;
                rightLine[ImgH - 1].position = RightBoundary;
                left_point_num = 1;
                break;
            }
        }
    }
    else
    {
        for(int i = RoadCenter; i >= 3; i--)
        {
            if(bin_img[ImgH - 1][i] == WHITE && bin_img[ImgH - 1][i - 1] == BLACK && bin_img[ImgH - 1][i - 2] == BLACK)
            {
                leftLine[ImgH - 1].position = i - 1;
                Find_Left = 1;
                left_point_num = 1;
                break;
            }
        }
        //没有找到左线,判断为丢线
        if(Find_Left == 0)
        {
            leftLine[ImgH - 1].position = LeftBoundary;
            leftLine[ImgH - 1].lineStatus = LOST;
            left_lost_num ++;
        }
        //搜索第一个右点
        for(int i = RoadCenter; i <= ImgW - 3; i++)
        {
            if(bin_img[ImgH - 1][i] == WHITE && bin_img[ImgH - 1][i + 1] == BLACK && bin_img[ImgH - 1][i + 2] == BLACK)
            {
                rightLine[ImgH - 1].position = i + 1;
                Find_Right = 1;
                right_point_num = 1;
                break;
            }
        }
        //没有找到右点
        if(Find_Right == 0)
        {
            rightLine[ImgH - 1].position = RightBoundary;
            rightLine[ImgH - 1].lineStatus = LOST;
            right_lost_num ++;
        }
    }
    //根据找到的左右边界点向上搜索
    for (int i = ImgH - 1 - 1; i >= 5; i--)
    {
        left_very_jump = right_very_jump = 0;
        //初始化左右边界是否找到标志
        Find_Left = Find_Right = 0;
        //根据上一行的左边界向右找五行
        for (int j = leftLine[i + 1].position; j <= leftLine[i + 1].position + 5 && j < RightBoundary - 2; j++)
        {
            if (bin_img[i][j] == BLACK && bin_img[i][j + 1] == WHITE && bin_img[i][j + 2] == WHITE)
            {
                leftLine[i].position = j;
                Find_Left = 1;
                left_point_num ++;
                break;
            }
        }

        if (!Find_Left)
        {
            //向右没找到边界，向左
            for (int j = leftLine[i + 1].position; j >= leftLine[i + 1].position - 5 && j > LeftBoundary; j--)
            {
                if (bin_img[i][j] == BLACK && bin_img[i][j + 1] == WHITE && bin_img[i][j + 2] == WHITE)
                {
                    leftLine[i].position = j;
                    Find_Left = 1;
                    left_point_num ++;
                    break;
                }
            }
        }

        if (!Find_Left)
        {
            //这一行可能还是边界点，上一行为边界点
            if (leftLine[i + 1].position == LeftBoundary && \
                    bin_img[i][leftLine[i + 1].position] == WHITE && \
                    bin_img[i][leftLine[i + 1].position + 1] == WHITE && \
                    bin_img[i][leftLine[i + 1].position - 1] == WHITE)
            {
                //这一行也为白色
                leftLine[i].position = LeftBoundary;
                leftLine[i].lineStatus = LOST;
                Find_Left = 2;
                left_lost_num ++;
            }
        }

        if (!Find_Left)
        {
            //如果向左向右都没找到边界点，那么重新扫描这一行
            for (int j = CenterPoint; j > LeftBoundary; j--)
            {
                if (bin_img[i][j] == BLACK && bin_img[i][j + 1] == WHITE && bin_img[i][j + 2] == WHITE)
                {
                    leftLine[i].position = j;
                    Find_Left = 1;
                    left_point_num ++;
                    break;
                }
            }
        }

        if (!Find_Left)
        {
            //左丢线
            leftLine[i].position = LeftBoundary;
            leftLine[i].lineStatus = LOST;
            left_lost_num ++;
        }

        if (ABS(leftLine[i].position - leftLine[i + 1].position) > 40 || (leftLine[i].position == LeftBoundary && leftLine[i + 1].position > ImgW / 2))
        {
            left_very_jump = 1;
            left_very_jump_row = i + 1;
        }
        //至此左边线搜索完成
        //开始搜索右边线,先向左搜索
        for (int j = rightLine[i + 1].position; j >= rightLine[i + 1].position - 5 && j > LeftBoundary + 2; j--)
        {
            if (bin_img[i][j] == BLACK && bin_img[i][j - 1] == WHITE && bin_img[i][j - 2] == WHITE)
            {
                rightLine[i].position = j;
                Find_Right = 1;
                right_point_num ++;
                break;
            }
        }

        if (!Find_Right)
        {
            //向右没找到边界，向左
            for (int j = rightLine[i + 1].position; j <= rightLine[i + 1].position + 5 && j < RightBoundary; j++)
            {
                if (bin_img[i][j] == BLACK && bin_img[i][j - 1] == WHITE && bin_img[i][j - 2] == WHITE)
                {
                    rightLine[i].position = j;
                    Find_Right = 1;
                    right_point_num ++;
                    break;
                }
            }
        }

        if (!Find_Right)
        {
            //这一行可能还是边界点，上一行为边界点
            if (rightLine[i + 1].position == RightBoundary &&\
                    bin_img[i][rightLine[i + 1].position - 1] == WHITE &&\
                    bin_img[i][rightLine[i + 1].position + 1] == WHITE &&\
                    bin_img[i][rightLine[i + 1].position] == WHITE)
            {
                //这一行也为白色
                rightLine[i].position = RightBoundary;
                rightLine[i].lineStatus = LOST;
                Find_Right = 2;
                right_lost_num ++;
            }
        }

        if (!Find_Right)
        {
            //如果向左向右都没找到边界点，那么重新扫描这一行
            for (int j = CenterPoint; j < RightBoundary; j++)
            {
                if (bin_img[i][j] == BLACK && bin_img[i][j - 1] == WHITE && bin_img[i][j - 2] == WHITE)
                {
                    rightLine[i].position = j;
                    Find_Right = 1;
                    right_point_num ++;
                    break;
                }
            }
        }

        if (!Find_Right)
        {
            //左丢线
            rightLine[i].position = RightBoundary;
            rightLine[i].lineStatus = LOST;
            right_lost_num ++;
        }

        if (ABS(rightLine[i].position - rightLine[i + 1].position) > 40 || (rightLine[i].position == RightBoundary && rightLine[i + 1].position < ImgW / 2))
        {
            right_very_jump = 1;
            right_very_jump_row = i + 1;
        }

        if (left_very_jump || right_very_jump)
            break;
    }
}

/*
 * @brief    获得图像高度
 *
 * @param    无
 *
 * @return   height ：图像可使用高度
 *
 * @state    使用中
 *
 * @see      get_Img_Height();  //获得图像高度
 */
uint8 get_Img_Height()
{
    int h = 5;
    if (left_very_jump && right_very_jump)
    {
        return left_very_jump_row > right_very_jump_row ? left_very_jump_row : right_very_jump_row;
    }
    if (left_very_jump)
    {
        return left_very_jump_row;
    }
    if (right_very_jump)
    {
        return right_very_jump_row;
    }
    return h;
}

/*
 * @brief    拟合中线
 *
 * @param    h ：图像可用高度
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      get_Center_Road(height);  //拟合图像中线
 */
void get_Center_Road (uint8 h)
{
    for (int i = ImgH - 1; i >= h; i--)
    {
        center[i] = (leftLine[i].position + rightLine[i].position) / 2;
        //如果出现中线搜错那么中间点就是中线
        if (center[i] == BLACK)
        {
            center[i] = ImgW / 2;
        }

        RoadErr[i] = CenterPoint - center[i];
    }
}
/*
 * @brief    处理边线
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      handle_outer(height);  //拟合图像中线
 */
void handle_outer()
{
    left_continuation_line = 0;
    right_continuation_line = 0;
    for (int i = ImgH - 2; i >= height; i--)
    {
        if (leftLine[i].position >= leftLine[i + 1].position && leftLine[i].lineStatus != LOST && leftLine[i + 1].lineStatus != LOST)
        {
            left_continuation_line ++;
        }
        if (rightLine[i].position <= rightLine[i + 1].position && rightLine[i].lineStatus != LOST && rightLine[i + 1].lineStatus != LOST)
        {
            right_continuation_line ++;
        }
    }
}

/*
 * @brief    获取中线偏差
 *
 * @param    Err[ImgH]  ：偏差数组
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      CalculationDeviation(RoadErr);  //获取中线偏差
 */

void CalculationDeviation(int Err[ImgH])
{
    PathDeviation = (Err[prospect - 2] + Err[prospect] + Err[prospect + 2]) / 3;
}

/*
 * @brief    图像二值化
 *
 * @param    threshold  ：阈值
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      get_Bin_Img (threshold);  //图像二值化
 */
void get_Bin_Img (int threshold)
{
    for(int i = 0; i < ImgH; i++)
    {
        for(int j = 0; j < ImgW; j++)
        {
            if(mt9v03x_image[i][j] <= threshold)
                bin_img[i][j] = BLACK;
            else
                bin_img[i][j] = WHITE;
        }
    }
}

/*
 * @brief    自适应前瞻高度
 *
 * @param    h  ：图像高度
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      Adaptive_Look_Ahead(height);  //自适应前瞻高度
 */
void Adaptive_Look_Ahead(int h)
{
    if (h >= PathRow)
    {
        prospect = h + 4;
    }
    else
    {
        if (type == CIRCLE)
        {
            prospect = 32;
        }
        else if (type == CROSS)
            prospect = 37;
        else
            prospect = PathRow;
    }
}

/*
 * @brief    预处理图像
 *
 * @param    image    ： 预处理图像指针
 *
 * @return   Threshold   ：大津法最佳阈值
 *
 * @see      ImagePrepro(mt9v03x_image_dvp);  //预处理图像
 */
void ImagePrepro ()
{
    // 池化图像
//    uint8 outImage[ImgH / 2][ImgW / 2];
//    minPooling(mt9v03x_image, 2, outImage);
    // 获得阈值
//    int threshold = GetOSTU(outImage);
    int threshold = GetOSTU(mt9v03x_image);
    get_Bin_Img(threshold);
//    test[2] = threshold;
//    if (threshold > THRESHOLD_MAX) threshold = THRESHOLD_MAX;
//    if (threshold < THRESHOLD_MIN)  threshold = THRESHOLD_MIN;
    // 得到二值化图像
    // 230
//    if (t1 == 0 && t2 == 0 && t3 == 0)
//    {
//        get_Bin_Img(230);
//    }
//    else if (t1 == 1 && t2 == 0 && t3 == 0)
//    {
//        get_Bin_Img(210);
//    }
//    else if (t1 == 0 && t2 == 1 && t3 == 0)
//    {
//        get_Bin_Img(190);
//    }
//    else if (t1 == 0 && t2 == 0 && t3 == 1)
//    {
//        get_Bin_Img(170);
//    }
//    else if (t1 == 1 && t2 == 1 && t3 == 0)
//    {
//        get_Bin_Img(150);
//    }
//    else if (t1 == 0 && t2 == 1 && t3 == 1)
//    {
//        get_Bin_Img(130);
//    }
//    else if (t1 == 1 && t2 == 0 && t3 == 1)
//    {
//        get_Bin_Img(110);
//    }
//    else if (t1 == 1 && t2 == 1 && t3 == 1)
//    {
//        get_Bin_Img(90);
//    }
}

/*
 * @brief    图像处理
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      Process_Image();  //图像处理
 */
void Process_Image()
{
    // 图像预处理
    ImagePrepro();
    //获得左右边线
    search_line();
    //获得图像高度
    height = get_Img_Height();
    //handle_outer
    handle_outer();
}

void record_last_image()
{
    for (int i = 0; i < ImgH; i++)
    {
        for (int j = 0; j < ImgW; j++)
        {
            stop_last[i][j] = bin_img[i][j];
        }
        stop_left[i] = leftLine[i].position;
        stop_right[i] = rightLine[i].position;
    }
}

/*
 * @brief    检测赛道类型
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      check_cross();  //检测十字路
 */
void CheckElementType()
{
    if (type == NORMAL)
        check_zebra();
    if (type == NORMAL)
        check_ramp();
    if (type == NORMAL)
        check_opencircuit();
    if (type == NORMAL)
        check_cross();
    if (type == NORMAL)
        check_circle();
//    if (type == NORMAL)
//        check_hinder();
}
int cross_cnt = 0;
/*
 * @brief    检测十字
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      check_corss();  //检测斑马线
 */
void check_cross()
{
    //记录左右跳变是否存在
    int left_jump = 0, right_jump = 0;
    int left_point = 0, right_point = 0;
    for (int i = ImgH - 1; i >= 25; i--)
    {
        if (leftLine[i].position > leftLine[i - 2].position && leftLine[i - 2].position == LeftBoundary && i > 10)
        {
            //记录左边跳变存在
            left_jump = 1;
            left_point = i - 2;
            break;
        }
    }
    for (int i = ImgH - 1; i >= 25; i--)
    {
        if (rightLine[i].position < rightLine[i - 2].position && rightLine[i - 2].position == RightBoundary && i > 10)
        {
            //记录右边跳变存在
            right_jump = 1;
            right_point = i - 2;
            break;
        }
    }

    if (left_jump && right_jump && (left_point >= 25 || right_point >= 25) && rightLine[right_point - 3].lineStatus == LOST && leftLine[left_point - 3].lineStatus == LOST)
    {
        int err = left_point - right_point;
        err = err < 0 ? -err : err;
        //判断一次
        if (left_lost_num >= 5 && right_lost_num >= 5 && err <= 15)
        {
            // 将圆环状态置为0
            circleCheckStatus = CIRCLE_CHECK_NONE;
            circle_time = 0;
            BING_ON;
            cross_cnt ++;
            type = CROSS;
            cross = CROSS_NONE;
//            type = STOP;
        }
    }
}

/*
 * @brief    检测斑马线
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      check_zebra();  //检测斑马线
 */
void check_zebra()
{
    //检测一行中黑白跳变的次数
    int jump_cnt = 0;
    int line = 35;
    if (line > height)
    {
        for (int i = leftLine[line].position; i < rightLine[line].position; i++)
        {
            if (bin_img[line][i] == WHITE && bin_img[line][i + 1] == BLACK)
                jump_cnt ++;
        }
    }
    if (jump_cnt >= 4)
    {
        // 将圆环状态置为0
        circleCheckStatus = CIRCLE_CHECK_NONE;
        circle_time = 0;
//        type = ZEBRA;
        BING_ON;
//        record_last_image();
        type = STOP;
    }
}
/*
 * @brief    检测坡道
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      check_ramp();  //检测斑马线
 */
void check_ramp()
{
    if (infraredNum >= 1500)
    {
        if (leftLine[ImgH - 1].lineStatus == NO_LOST && rightLine[ImgH - 1].lineStatus == NO_LOST && abs(PathDeviation) < 15)
        {
            // 将圆环状态置为0
            circleCheckStatus = CIRCLE_CHECK_NONE;
            circle_time = 0;
            type = RAMP;
        }
    }
}

/*
 * @brief    检测障碍
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      check_zebra();  //检测斑马线
 */
void check_hinder()
{
    if (infraredNum >= 700)
    {
        // 满足障碍第一要求，红外测距
        int hinder_line = 0;
        for (int i = ImgH - 1; i >= 5; i--)
        {
            if (bin_img[i][ImgW / 2] == WHITE && bin_img[i - 1][ImgW / 2] == BLACK)
            {
                hinder_line = i;
                break;
            }
        }
        if (hinder_line >= 20)
        {
            // 满足障碍第二要求
            if (height >= 20 && abs(left_lost_num - right_lost_num) < 10)
            {
                // 将圆环状态置为0
                circleCheckStatus = CIRCLE_CHECK_NONE;
                circle_time = 0;
                // 满足障碍第三要求
//                type = HINDER;
//                BING_ON;
                hinder = HINDER_STATUS_1;
                type = STOP;
                record_last_image();
            }
        }
    }
}

/*
 * @brief    检测断路
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      check_opencircuit();  //检测断路
 */
void check_opencircuit()
{
    int black_line = 20;
    // 首先判断是否满足该条件
    int cnt = 0;
    // 最下行的黑点数量
    for (int i = 0; i < ImgW; i++)
        if (bin_img[black_line][i] == BLACK)
            cnt ++;
    if (cnt >= 120)
    {
        int cnt_2 = 0;
        for (int i = 0; i < ImgW; i++)
            if (bin_img[ImgH - 1][i] == BLACK)
                cnt_2 ++;
        if (cnt_2 < 100 \
                && left_lost_num < 5 \
                && right_lost_num < 5 \
                && height >= 20 \
                && abs(PathDeviation) < 15)
        {
            // 将圆环状态置为0
            circleCheckStatus = CIRCLE_CHECK_NONE;
            circle_time = 0;
            // 最下行不为纯黑色
//            type = STOP;
//            record_last_image();
            type = OPENCIRCUIT;
//            BING_ON;
            open = OPEN_FOUND;
            open_time = 0;
            return;
        }
    }

    // 遍历左右线
    int open_left_lost = 0, open_right_lost = 0;
    for (int i = ImgH - 1; i >= height + 1; i --)
    {
        if (leftLine[i].lineStatus == LOST) open_left_lost ++;
        if (rightLine[i].lineStatus == LOST)    open_right_lost ++;
    }
    if (open_left_lost <= 3 && open_right_lost <= 3)
    {
        // 寻找左线或者右线的跳变
        int left_point = 0, right_point = 0;
        int right_jump_p = 0, left_jump_p = 0;
        for (int i = ImgH - 6; i >= height + 5; i--)
        {
            if ((leftLine[i].position < leftLine[i - 5].position && abs(leftLine[i].position - leftLine[i - 5].position) >= 5) \
                    && leftLine[i].position < leftLine[i + 5].position \
                    && (leftLine[i - 5].lineStatus == NO_LOST || leftLine[i - 5].position != LeftBoundary) && leftLine[i].lineStatus != LOST)
            {
                // 不连续
                left_point = i;
                break;
            }
            if (leftLine[i].position > leftLine[i - 2].position && leftLine[i].position > leftLine[i + 2].position && !left_jump_p)
            {
                left_jump_p = i;
            }
        }
        for (int i = ImgH - 1; i >= height + 5; i--)
        {
            if ((rightLine[i].position > rightLine[i - 5].position && abs(rightLine[i].position - rightLine[i - 5].position) >= 5) \
                    && rightLine[i].position > rightLine[i + 5].position)
            {
                // 不连续
                right_point = i;
                break;
            }
            if (rightLine[i].position < rightLine[i - 2].position && rightLine[i].position < rightLine[i + 2].position && !right_jump_p)
            {
                right_jump_p = i;
            }
        }
        if (left_point && !right_point && !right_jump_p)
        {
            test[0] = left_point;
            // 向上寻找点1
            int p_1 = 0, p_2 = left_point, p_3 = ImgH - 1;
            float k_1, k_2;
            for (int i = left_point; i >= 10; i--)
            {
                if (leftLine[i].lineStatus == NO_LOST && (leftLine[i - 2].lineStatus == LOST || leftLine[i - 2].position == LeftBoundary || leftLine[i - 2].position <= LeftBoundary + 5))
                {
                    p_1 = i;
                    break;
                }
            }
            int err_point = 0;
            for (int i = left_point + 5; i >= left_point - 5; i--)
            {
                if (leftLine[left_point].lineStatus == LOST)    err_point ++;
            }
            if (p_1 == 0 || left_point >= ImgH / 2 \
                    || leftLine[left_point].lineStatus == LOST \
                    || leftLine[left_point - 5].lineStatus == LOST \
                    || leftLine[left_point + 5].lineStatus == LOST \
                    || err_point >= 3 \
                    || abs(p_1 - p_2) < 8)
            {
                return;
            }
            test[1] = p_1;
            // 开始计算斜率
            k_1 = (p_1 - p_2) / (float)(leftLine[p_1].position - leftLine[p_2].position);
            k_2 = (p_2 - p_3) / (float)(leftLine[p_2].position - leftLine[p_3].position);
            ftest[0] = k_1;
            ftest[1] = k_2;
            if (abs(k_1) + abs(k_2) >= 2 && abs(k_1) + abs(k_2) <= 4)
            {
                // 拟合第一条直线
                float b = (p_2 - k_1 * leftLine[p_2].position);
                int cnt_x = 0;
                for (int i = p_2; i >= p_1; i--)
                {
                    int x = (i - b) / k_1;
                    if (abs(x - leftLine[i].position) <= 2)
                    {
                        cnt_x ++;
                    }
                }
                if (cnt_x >= ((p_2 - p_1) - 3))
                {
                    circleCheckStatus = CIRCLE_CHECK_NONE;
                    circle_time = 0;
                    // 最下行不为纯黑色
//                    record_last_image();
//                    type = STOP;
                    type = OPENCIRCUIT;
//                    BING_ON;
                    open = OPEN_FOUND;
                    open_time = 0;
                }
            }
            else
            {
                return;
            }
            // 判断
        }
        else if (right_point && !left_point && !left_jump_p)
        {
            test[0] = right_point;
            // 向上寻找点1
            int p_1 = 0, p_2 = right_point, p_3 = ImgH - 1;
            float k_1, k_2;
            for (int i = right_point; i >= 13; i--)
            {
                if (rightLine[i].lineStatus == NO_LOST && (rightLine[i - 2].lineStatus == LOST || rightLine[i - 2].position == RightBoundary || rightLine[i - 2].position >= RightBoundary - 5))
                {
                    p_1 = i;
//                    type = STOP;
                    break;
                }
            }
            int err_point = 0;
            for (int i = right_point + 5; i >= right_point - 5; i--)
            {
                if (rightLine[right_point].lineStatus == LOST)    err_point ++;
            }
            if (p_1 == 0 || right_point >= ImgH / 2 \
                    || rightLine[right_point].lineStatus == LOST \
                    || rightLine[right_point - 5].lineStatus == LOST \
                    || rightLine[right_point + 5].lineStatus == LOST \
                    || err_point >= 3 \
                    || abs(p_1 - p_2) < 8)
            {
                return;
            }
            test[1] = p_1;
            // 开始计算斜率
            k_1 = (p_1 - p_2) / (float)(rightLine[p_1].position - rightLine[p_2].position);
            k_2 = (p_2 - p_3) / (float)(rightLine[p_2].position - rightLine[p_3].position);
            ftest[0] = k_1;
            ftest[1] = k_2;
            if (abs(k_1) + abs(k_2) >= 2 && abs(k_1) + abs(k_2) <= 8)
            {
                // 拟合第一条直线
                float b = (p_2 - k_1 * rightLine[p_2].position);
                int cnt_x = 0;
                for (int i = p_2; i >= p_1; i--)
                {
                    int x = (i - b) / k_1;
                    if (abs(x - rightLine[i].position) <= 3)
                    {
                        cnt_x ++;
                    }
                }
                if (cnt_x >= ((p_2 - p_1) - 3))
                {
                    circleCheckStatus = CIRCLE_CHECK_NONE;
                    circle_time = 0;
                    // 最下行不为纯黑色
//                    record_last_image();
//                    type = STOP;
                    type = OPENCIRCUIT;
                    BING_ON;
                    open = OPEN_FOUND;
                    open_time = 0;
                }
            }
            else
            {
                return;
            }
        }
        else
        {
            test[0] = 0;
            test[1] = 0;
        }
    }
}


/*
 * @brief    检测环岛
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      check_circle();  //检测环岛
 */
void check_circle()
{
    if (circle_time >= 50)
        circle_time = 0;
    // 寻找左右拐点
    int left_jump = 0, right_jump = 0;
    for (int i = ImgH - 4; i >= height + 3; i--)
    {
        if (!left_jump && leftLine[i].lineStatus == LOST && leftLine[i + 1].lineStatus == NO_LOST && leftLine[i + 2].lineStatus == NO_LOST)
        {
            left_jump = i + 1;
        }
        if (!right_jump && rightLine[i].lineStatus == LOST && rightLine[i + 1].lineStatus == NO_LOST && rightLine[i + 2].lineStatus == NO_LOST)
        {
            right_jump = i + 1;
        }
        if (left_jump || right_jump)
            break;
    }
    if (left_jump && !right_jump && circleCheckStatus == CIRCLE_CHECK_NONE)
    {
        int is_circle_status = 0;
        // 向上寻找一个拐点
        for (int i = left_jump; i >= height; i--)
        {
            if (bin_img[i][leftLine[left_jump].position] == WHITE && bin_img[i - 1][leftLine[left_jump].position] == BLACK)
            {
                //找到左拐点
                circleCheckStatus = CIRCLE_CHECK_STATUS_1;
                circleDirection = LEFT_CIRCLE;
                circle_time = 0;
                is_circle_status = 1;
                break;
            }
        }
        if (!is_circle_status)
        {
            circle_time = 0;
            return;
        }
    }
    else if (!left_jump && right_jump && circleCheckStatus == CIRCLE_CHECK_NONE)
    {
        //找到右拐点
        int is_circle_status = 0;
        // 向上寻找一个拐点
        for (int i = right_jump; i >= height; i--)
        {
            if (bin_img[i][rightLine[right_jump].position] == WHITE && bin_img[i - 1][rightLine[right_jump].position] == BLACK)
            {
                //找到左拐点
                circleCheckStatus = CIRCLE_CHECK_STATUS_1;
                circleDirection = RIGHT_CIRCLE;
                circle_time = 0;
                is_circle_status = 1;
                break;
            }
        }
        if (!is_circle_status)
        {
            circle_time = 0;
            return;
        }
    }


    //找到拐点开始记录
    switch (circleCheckStatus)
    {
    case CIRCLE_CHECK_STATUS_1:
    {
        //环岛状态1成立，找到左/右拐点
        //内缩数量，外扩数量，丢线数量
        uint8 circle_status = 0;
        if (circleDirection == LEFT_CIRCLE)
        {
            //左边拐点
            for (int i = ImgH - 3; i >= height + 5; i--)
            {
                if (leftLine[i].position > leftLine[i + 2].position && leftLine[i].position > leftLine[i - 5].position && \
                        leftLine[i - 5].lineStatus == LOST && leftLine[i - 6].lineStatus == LOST && i >= ImgH / 2)
                {
//                    point = i;
                    circle_status = 1;
                    break;
                }
            }
        }
        else
        {
            //右边拐点
            for (int i = ImgH - 3; i >= height + 5; i--)
            {
                if (rightLine[i].position < rightLine[i + 2].position && rightLine[i].position < rightLine[i - 5].position && \
                        rightLine[i - 5].lineStatus == LOST && rightLine[i - 6].lineStatus == LOST && i >= ImgH / 2)
                {
                    circle_status = 1;
//                    point = i;
                    break;
                }
            }
        }
        if (circle_status)
        {
            //进入状态2
            circleCheckStatus = CIRCLE_CHECK_STATUS_2;
            circle_time = 0;
        }

        if (circle_time >= 5)
        {
            circleCheckStatus = CIRCLE_CHECK_NONE;
            circle_time = 0;
        }
        //得到数量
        break;
    }
    case CIRCLE_CHECK_STATUS_2:
    {
        //最近行丢线
        //从下向上10行全部丢线
        uint8 lost_cnt = 0;
        for (int i = ImgH - 1; i >= ImgH - 20; i--)
        {
            if (circleDirection == LEFT_CIRCLE && (leftLine[i].lineStatus == LOST || leftLine[i].position <= LeftBoundary + 5)) lost_cnt ++;
            if (circleDirection == RIGHT_CIRCLE && rightLine[i].lineStatus == LOST) lost_cnt ++;
        }

        if (lost_cnt >= 10 && ((leftLine[ImgH - 1].lineStatus == LOST || leftLine[ImgH - 1].position <= 10) || rightLine[ImgH - 1].lineStatus == LOST))
        {
            circleCheckStatus = CIRCLE_CHECK_STATUS_3;

        }
        if (circleDirection == LEFT_CIRCLE)
        {
            //遍历左线，找到可用的补线点
            uint8 start_point = 0, end_point = 0;
            for (int i = ImgH - 1; i >= height; i--)
            {
                if (leftLine[i].position > leftLine[i - 1].position && leftLine[i - 1].position == LeftBoundary && start_point == 0)
                {
                    start_point = i;
                }
                else if (leftLine[i].position > leftLine[end_point].position)
                {
                    end_point = i;
                }
            }
            //找到补线的点
            left_Patching(leftLine[start_point].position, start_point, CenterPoint + 20, height);
        }
        else if (circleDirection == RIGHT_CIRCLE)
        {
            //遍历左线，找到可用的补线点
            uint8 start_point = 0, end_point = ImgH - 1;
            for (int i = ImgH - 1; i >= height; i--)
            {
                if (rightLine[i].position < rightLine[i - 1].position && rightLine[i - 1].position == RightBoundary && start_point == 0)
                {
                    start_point = i;
                }
                else if (rightLine[i].position < rightLine[end_point].position)
                {
                    end_point = i;
                }
            }
            if (start_point >= ImgH - 3)
            {
                right_Patching(ImgW - 1 - leftLine[ImgH - 1].position, start_point, rightLine[end_point].position, height);
            }
            else
            {
                right_Patching(rightLine[start_point].position, start_point, rightLine[end_point].position, height);
            }

            //找到补线的点
        }
        break;
    }
    case CIRCLE_CHECK_STATUS_3:
    {
        uint8 status_point = 0;
        if (circleDirection == LEFT_CIRCLE && (leftLine[ImgH - 1].lineStatus == NO_LOST && leftLine[ImgH - 1].position > LeftBoundary + 10))
        {
            // 左环岛，遍历左线
            for (int i = ImgH - 1; i >= height + 3; i--)
            {
                if (leftLine[i].position > leftLine[i - 1].position) status_point ++;
            }
        }
        else if (circleDirection == RIGHT_CIRCLE && (rightLine[ImgH - 1].lineStatus == NO_LOST && rightLine[ImgH - 1].position > LeftBoundary + 10))
        {
            // 右环岛，遍历左线
            for (int i = ImgH - 1; i >= height + 3; i--)
            {
                if (rightLine[i].position < rightLine[i - 1].position) status_point ++;
            }
        }
        if (status_point >= 5)
        {
            circleCheckStatus = CIRCLE_CHECK_STATUS_4;
        }
        if (circleDirection == LEFT_CIRCLE)
        {
            //遍历左线，找到可用的补线点
            uint8 start_point = ImgH - 1, end_point = 0;
            for (int i = ImgH - 1; i >= height; i--)
            {
                if (leftLine[i].position > leftLine[end_point].position)
                {
                    end_point = i;
                }
            }

            //找到补线的点
            left_Patching(leftLine[start_point].position, start_point, leftLine[end_point].position, height);
        }
        else if (circleDirection == RIGHT_CIRCLE)
        {
            //遍历左线，找到可用的补线点
            uint8 start_point = ImgH - 1, end_point = ImgH - 1;
            for (int i = ImgH - 1; i >= height; i--)
            {
                if (rightLine[i].position < rightLine[end_point].position)
                {
                    end_point = i;
                }
            }

            //找到补线的点
            if (start_point >= ImgH - 3)
            {
                right_Patching(ImgW - 1 - leftLine[ImgH - 1].position, start_point, rightLine[end_point].position, height);
            }
            else
            {
                right_Patching(rightLine[start_point].position, start_point, rightLine[end_point].position, height);
            }
        }
        break;
    }
    case CIRCLE_CHECK_STATUS_4:
    {
        int jump_point = 0;
        if (circleDirection == RIGHT_CIRCLE)
        {
            for (int i = ImgH - 1; i >= height + 3; i--)
            {
                if (rightLine[i].lineStatus == NO_LOST && rightLine[i - 2].lineStatus == LOST)
                {
                    jump_point = i;
                    break;
                }
            }
            if (jump_point >= 25)
            {
                type = CIRCLE;
//                type = STOP;
//                record_last_image();
                BING_ON;
                circle = CIRCLE_FOUND;
                circleCheckStatus = CIRCLE_CHECK_NONE;
                circle_time = 0;
            }
        }
        else if (circleDirection == LEFT_CIRCLE)
        {
            for (int i = ImgH - 1; i >= height + 3; i--)
            {
                if (leftLine[i].lineStatus == NO_LOST && (leftLine[i - 2].lineStatus == LOST || leftLine[i - 2].position <= 10))
                {
                    jump_point = i;
                    break;
                }
            }
            if (jump_point >= 25)
            {
                type = CIRCLE;
//                type = STOP;
//                record_last_image();
                BING_ON;
                circle = CIRCLE_FOUND;
                circleCheckStatus = CIRCLE_CHECK_NONE;
                circle_time = 0;
            }
        }
        if (circleDirection == LEFT_CIRCLE)
        {
            //遍历左线，找到可用的补线点
            uint8 start_point = ImgH - 1, end_point = 0;
            for (int i = ImgH - 1; i >= height; i--)
            {
                if (leftLine[i].position > leftLine[end_point].position)
                {
                    end_point = i;
                }
            }

            //找到补线的点
            left_Patching(leftLine[start_point].position, start_point, leftLine[end_point].position, height);
        }
        else if (circleDirection == RIGHT_CIRCLE)
        {
            //遍历左线，找到可用的补线点
            uint8 start_point = ImgH - 1, end_point = ImgH - 1;
            for (int i = ImgH - 1; i >= height; i--)
            {
                if (rightLine[i].position < rightLine[end_point].position)
                {
                    end_point = i;
                }
            }

            //找到补线的点
            right_Patching(ImgW - 1 - leftLine[start_point].position, start_point, rightLine[end_point].position, height);
        }
        break;
    }
    default:
        break;
    }
}

/*
 * @brief    检测停车
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      check_stop();  //检测停车
 */
void check_stop()
{
    if (type == HINDER)
        return;
//    Send_Emergency_Stop();
    if (type == OPENCIRCUIT)
    {
        // 比较电感值进行计算
        if (adcNum[0] < ADC_MIN_NUM && adcNum[1] < ADC_MIN_NUM && adcNum[2] < ADC_MIN_NUM && adcNum[3] < ADC_MIN_NUM && adcNum[4] < ADC_MIN_NUM)
        {
            type = STOP;
        }
        return;
    }
    int cnt = 0;
    // 最下行的黑点数量
    for (int i = 0; i < ImgW; i++)
        if (bin_img[ImgH - 1][i] == BLACK)
            cnt ++;

    if (cnt >= 140)
    {
        record_last_image();
        type = STOP;
    }
}


/*
 * @brief    巡线
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      Line_patrol();  //巡线
 */
void Line_patrol()
{
    //根据高度求出图像中线
    get_Center_Road(height);
    //设置前瞻
    Adaptive_Look_Ahead(height);
    //计算偏差值
    CalculationDeviation(RoadErr);
}

void Run_Charge()
{
    if (charge == CHARGE_STATUS_0)
    {
        Wait_Start();
    }
    else if (charge == CHARGE_STATUS_1)
    {
        Send_Start();
    }
    // 140 7s
    if (charge_time >= 140)
    {
        // 退出充电
        type = ERR_CHARGE;
        charge = CHARGE_STATUS_1;
        charge_time = 0;
    }
    left_Patching(1, ImgH - 1, CenterPoint, 1);
    right_Patching(ImgW - 1, ImgH - 1, CenterPoint, 1);
    if (charge_time >= 10 && charge == CHARGE_STATUS_1)
    {
        type = NORMAL;
        charge = CHARGE_STATUS_NONE;
    }
}

void Run_Err_Charge()
{
    left_Patching(1, ImgH - 1, ImgW - 1, 1);
    right_Patching(ImgW - 1, ImgH - 1, ImgW - 1, 1);
}

void Run_OutBarn()
{
//    right_Patching(ImgH - 1, ImgW - 1, 1, 1);
    if (outbarn_time >= 10 && outbarn == OUTBARN_STATUS_0)
    {
        outbarn_time = 0;
//        type = STOP;
        outbarn = OUTBARN_STATUS_1;
    }
    if (outbarn_time >= 5 && outbarn == OUTBARN_STATUS_1)
    {
        outbarn_time = 0;
        outbarn = OUTBARN_STATUS_2;
    }
    if (outbarn_time >= 3 && outbarn == OUTBARN_STATUS_2)
    {
        outbarn_time = 0;
        outbarn = OUTBARN_STATUS_NONE;
        type = CHARGE;
        charge = CHARGE_STATUS_0;
//        type = STOP;
    }
}

void Run_Zebra()
{
//    right_Patching(ImgW - 1, ImgH - 1, 1, 1);
    left_Patching(1, ImgH - 1, CenterPoint + 25, 5);
    right_Patching(ImgW - 1, ImgH - 1, CenterPoint + 25, 5);
    if (zebra_time >= 2)
    {
        zebra_time = 0;
        type = FINISH;
    }
}

/*
 * @brief    运行十字
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      Run_Cross();
 */
void Run_Cross()
{
    // 判断当前处于十字的那个位置
    if (cross == CROSS_NONE)
    {
        // 刚刚进入十字状态判断处于十字的那个位置
        // 1.判断下5行的状态
        int leftLostNum = 0, rightLostNum = 0;
        for (int i = ImgH - 1; i >= ImgH - 6; i--)
        {
            if (leftLine[i].lineStatus == LOST)
                leftLostNum ++;
            if (rightLine[i].lineStatus == LOST)
                rightLostNum ++;
        }
        // 通过判断丢线的数量判断
        if ((leftLostNum >= 3 && rightLostNum >= 3 && cross_time >= 5  && leftLine[ImgH - 1].lineStatus == LOST && rightLine[ImgH - 1].lineStatus == LOST) || cross_time >= 10)
        {
            cross = CROSS_ENTRY;
            cross_time = 0;
        }
        else
        {
            // 向上找丢、不丢点
            int left_point_line = 0, left_point_find = 0;
            int right_point_line = 0, right_point_find = 0;
            for (int i = ImgH - 1; i >= height + 3; i--)
            {
                if (leftLine[i].lineStatus == LOST && leftLine[i - 2].lineStatus == NO_LOST && leftLine[i - 3].lineStatus == NO_LOST)
                {
                    left_point_line = i - 2;
                    left_point_find = 1;
                    break;
                }
            }
            // 右线
            for (int i = ImgH - 1; i >= height + 3; i--)
            {
               if (rightLine[i].lineStatus == LOST && rightLine[i - 2].lineStatus == NO_LOST && rightLine[i - 3].lineStatus == NO_LOST)
               {
                   right_point_line = i - 2;
                   right_point_find = 1;
                   break;
               }
            }
            if (left_point_find)
            {
                left_Patching(20, ImgH - 1, leftLine[left_point_line].position, height);
            }
            else
            {
                if (left_lost_num > right_lost_num)
                {
                    left_Patching(20, ImgH - 1, CenterPoint, height);
                }
                else
                {
                    left_Patching(20, ImgH - 1, CenterPoint, height);
                }
            }
            if (right_point_find)
            {
                right_Patching(ImgW - 20 - 1, ImgH - 1, rightLine[right_point_line].position, height);
            }
            else
            {
                if (left_lost_num > right_lost_num)
                {
                    right_Patching(ImgW - 20 - 1, ImgH - 1, CenterPoint, height);
                }
                else
                {
                    right_Patching(ImgW - 20 - 1, ImgH - 1, CenterPoint, height);
                }
            }
        }
    }
    else if (cross == CROSS_FOUND || cross == CROSS_ENTRY)
    {
        // 向上寻找补线点
        int left_point_line = 0, left_point_find = 0;
        int right_point_line = 0, right_point_find = 0;
        // 左线
        for (int i = ImgH - 1; i >= height + 3; i--)
        {
            if (leftLine[i].lineStatus == LOST && leftLine[i - 2].lineStatus == NO_LOST && leftLine[i - 3].lineStatus == NO_LOST)
            {
                left_point_line = i - 2;
                left_point_find = 1;
                break;
            }
        }
        // 右线
        for (int i = ImgH - 1; i >= height + 3; i--)
        {
           if (rightLine[i].lineStatus == LOST && rightLine[i - 2].lineStatus == NO_LOST && rightLine[i - 3].lineStatus == NO_LOST)
           {
               right_point_line = i - 2;
               right_point_find = 1;
               break;
           }
        }
        if ((leftLine[ImgH - 1].lineStatus == NO_LOST && rightLine[ImgH - 1].lineStatus == NO_LOST &&
            leftLine[ImgH - 8].lineStatus == NO_LOST && rightLine[ImgH - 8].lineStatus == NO_LOST && cross_time >= 2) || cross_time >= 15)
        {
            cross = CROSS_RUN;
            cross_time = 0;
            BING_OFF;
        }
        if (left_point_find)
        {
            left_Patching(leftLine[ImgH - 1].position, ImgH - 1, leftLine[left_point_line].position, height);
        }
        else
        {
            if (left_lost_num > right_lost_num)
            {
                left_Patching(leftLine[ImgH - 1].position, ImgH - 1, CenterPoint - 10, height);
            }
            else
            {
                left_Patching(leftLine[ImgH - 1].position, ImgH - 1, CenterPoint + 10, height);
            }
        }
        if (right_point_find)
        {
            right_Patching(rightLine[ImgH - 1].position, ImgH - 1, rightLine[right_point_line].position, height);
        }
        else
        {
            if (left_lost_num > right_lost_num)
            {
                right_Patching(rightLine[ImgH - 1].position, ImgH - 1, CenterPoint + 10, height);
            }
            else
            {
                right_Patching(rightLine[ImgH - 1].position, ImgH - 1, CenterPoint - 10, height);
            }
        }
    }
    else if (cross == CROSS_RUN)
    {
        int left_jump = 0, right_jump = 0;
        int left_point = 0, right_point = 0;
        // 找右跳变点
        // 左线
        for (int i = ImgH - 1; i >= height + 3; i--)
        {
            if (leftLine[i].lineStatus == NO_LOST && (leftLine[i - 2].lineStatus == LOST || leftLine[i - 2].position <= 10) \
                    && (leftLine[i - 3].lineStatus == LOST || leftLine[i - 3].position <= 10))
            {
                left_point = i - 2;
                left_jump = 1;
                break;
            }
        }
        // 右线
        for (int i = ImgH - 1; i >= height + 3; i--)
        {
           if (rightLine[i].lineStatus == NO_LOST && (rightLine[i - 2].lineStatus == LOST || rightLine[i - 2].position >= RightBoundary - 10) \
                   && (rightLine[i - 3].lineStatus == LOST || rightLine[i - 3].position >= RightBoundary - 10))
           {
               right_point = i - 2;
               right_jump = 1;
               break;
           }
        }
        if (((right_jump && left_jump && right_point >= 40 && left_point >= 40) \
                || (left_lost_num >= 15 && leftLine[ImgH - 3].lineStatus == LOST && right_jump && right_point >= 30 \
                        && (abs(rightLine[right_point].position - rightLine[right_point + 2].position) >= 15 && abs(rightLine[right_point].position - rightLine[right_point + 2].position) <= 30)) \
                || (right_lost_num >= 15 && rightLine[ImgH - 3].lineStatus == LOST && left_jump && left_point >= 30 \
                        && (abs(leftLine[right_point].position - leftLine[right_point + 2].position) >= 15 && abs(leftLine[right_point].position - leftLine[right_point + 2].position) <= 30)) \
                || (leftLine[ImgH - 1].lineStatus == LOST && rightLine[ImgH - 1].lineStatus == LOST)) && cross_time >= 15)
        {
            cross = CROSS_EXIT;
            BING_ON;
            cross_time = 0;
        }
    }
    else if (cross == CROSS_EXIT)
    {
        // 向上寻找补线点
        int left_point_line = 0, left_point_find = 0;
        int right_point_line = 0, right_point_find = 0;
        // 左线
        for (int i = ImgH - 1; i >= height + 3; i--)
        {
            if (leftLine[i].lineStatus == LOST && leftLine[i - 2].lineStatus == NO_LOST && leftLine[i - 3].lineStatus == NO_LOST)
            {
                left_point_line = i - 2;
                left_point_find = 1;
                break;
            }
        }
        // 右线
        for (int i = ImgH - 1; i >= height + 3; i--)
        {
           if (rightLine[i].lineStatus == LOST && rightLine[i - 2].lineStatus == NO_LOST && rightLine[i - 3].lineStatus == NO_LOST)
           {
               right_point_line = i - 2;
               right_point_find = 1;
               break;
           }
        }
        if ((leftLine[ImgH - 1].lineStatus == NO_LOST && rightLine[ImgH - 1].lineStatus == NO_LOST &&
            leftLine[ImgH - 8].lineStatus == NO_LOST && rightLine[ImgH - 8].lineStatus == NO_LOST && cross_time >= 5) || cross_time >= 6)
        {
            cross = CROSS_NONE;
            type = NORMAL;
            cross_time = 0;
            BING_OFF;
        }
        if (left_point_find && right_point_find)
        {
            left_Patching(leftLine[ImgH - 1].position, ImgH - 1, leftLine[left_point_line].position, height);
            right_Patching(rightLine[ImgH - 1].position, ImgH - 1, rightLine[right_point_line].position, height);
        }
        else
        {
            left_Patching(leftLine[ImgH - 1].position, ImgH - 1, CenterPoint - 15, height);
            right_Patching(rightLine[ImgH - 1].position, ImgH - 1, CenterPoint + 15, height);
        }
    }
}
/*
 * @brief    运行坡道
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      Run_Ramp();
 */
void Run_Ramp()
{
    if (ramp_time >= 25)
        type = NORMAL;
}
/*
 * @brief    运行圆环
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      Run_Circle();
 */
void Run_Circle()
{
    if (circleDirection == LEFT_CIRCLE)
    {
        //左环岛
        switch (circle)
        {
        case CIRCLE_FOUND:
        {
            // 扫描右线
            uint8 jump_point = 0;
            for (int i = ImgH - 1; i >= height + 3; i--)
            {
                if (rightLine[i].position < rightLine[i - 1].position && (rightLine[i - 1].position - rightLine[i].position >= 15))
                {
                    jump_point = i;
                    break;
                }
            }
            if (jump_point != 0 || circle_time >= 7)
            {
                //进入圆环
                circle = CIRCLE_RUN;
                circle_time = 0;
                BING_OFF;
//                type = STOP;
                circle_time = 0;
            }
            if (jump_point)
            {
                right_Patching(rightLine[ImgH - 1].position, ImgH - 1, rightLine[jump_point].position, height);
            }
            else
            {
                right_Patching(rightLine[ImgH - 1].position, ImgH - 1, 55, height);
            }
            break;
        }
        case CIRCLE_ENTRY:
        {
            break;
        }
        case CIRCLE_RUN:
        {
            uint8 right_jump_point_find = 0, right_jump_point = 0;
            for (int i = ImgH - 10; i >= height + 5; i--)
            {
                if (rightLine[i].position < rightLine[i - 3].position && (rightLine[i - 3].position == RightBoundary || rightLine[i - 3].position >= RightBoundary - 5) \
                        && (rightLine[i - 8].position >= RightBoundary - 5 || rightLine[i - 5].position >= RightBoundary - 5))
                {
                    right_jump_point_find = 1;
                    right_jump_point = i;
                    break;
                }
            }
            if (right_jump_point_find && rightLine[right_jump_point].position >= CenterPoint && circle_time >= 3)
            {
                circle = CIRCLE_EXIT;
                circle_time = 0;
                BING_ON;
//                type = STOP;
//                record_last_image();
            }
            break;
        }
        case CIRCLE_EXIT:
        {
            //开始补线
            uint8 right_jump_point_find = 0;
            for (int i = ImgH - 10; i >= 15; i--)
            {
                if (rightLine[i].position < rightLine[i - 3].position && (rightLine[i - 3].position == RightBoundary || rightLine[i - 3].position >= RightBoundary - 15) \
                        && (rightLine[i - 8].position >= RightBoundary - 10 || rightLine[i - 5].position >= RightBoundary - 10))
                {
                    right_jump_point_find = 1;
                    break;
                }
            }
            //开始补线
            if (right_lost_num < 10 && ((leftLine[ImgH - 3].lineStatus == NO_LOST || leftLine[ImgH - 6].lineStatus == NO_LOST) || circle_time >= 6) && !right_jump_point_find)
            {
                circle_time = 0;
                circle = CIRCLE_NONE;
//                type = STOP;
//                record_last_image();
            }
            if (right_jump_point_find)
            {
                right_Patching(rightLine[ImgH - 1].position, ImgH - 1, CenterPoint - 40, height + 1);
            }
            else
            {
                right_Patching(rightLine[ImgH - 1].position, ImgH - 1, 15, height + 1);
            }
            break;
        }
        case CIRCLE_NONE:
        {
            if (circle_time >= 5)
            {
               type = NORMAL;
//               record_last_image();
//               type = STOP;
               BING_OFF;
               circle_time = 0;
            }
            //到达此状态需要补右边线然后退出环岛状态
            left_Patching(leftLine[ImgH - 1].position, ImgH - 1, CenterPoint - 10, height + 2);
            break;
        }
        }
    }
    else if (circleDirection == RIGHT_CIRCLE)
    {
        //右环岛
        switch (circle)
        {
        case CIRCLE_FOUND:
        {
            // 扫描左线
            uint8 jump_point = 0;
            for (int i = ImgH - 1; i >= height + 3; i--)
            {
                if (leftLine[i].position < leftLine[i - 1].position && (leftLine[i - 1].position - leftLine[i].position >= 15))
                {
                    jump_point = i;
                    break;
                }
            }
                // 没有找到拐点
            if ((jump_point != 0 && circle_time >= 3) || circle_time >= 7)
            {
                //进入圆环
                circle = CIRCLE_RUN;
//                record_last_image();
//                type = STOP;
                BING_OFF;
                circle_time = 0;
            }
            left_Patching(15, ImgH - 1, ImgW - 15, height);
            right_Patching(rightLine[ImgH - 1].position, ImgH - 1, ImgW, height);
            break;
        }
        case CIRCLE_ENTRY:
        {
            break;
        }
        case CIRCLE_RUN:
        {
            uint8 left_jump_point_find = 0, left_jump_point = 0;
            for (int i = ImgH - 10; i >= height + 5; i--)
            {
                if (leftLine[i].position > leftLine[i - 3].position && (leftLine[i - 3].position == LeftBoundary || leftLine[i - 3].position <= LeftBoundary + 15) \
                        && (leftLine[i - 8].position <= LeftBoundary + 10 || leftLine[i - 5].position <= LeftBoundary + 10))
                {
                    left_jump_point_find = 1;
                    left_jump_point = i;
                    break;
                }
            }
            // && (leftLine[left_jump_point - 3].lineStatus == LOST || leftLine[left_jump_point - 5].lineStatus == LOST) && leftLine[left_jump_point].position <= 20
            if (left_jump_point_find && leftLine[left_jump_point].position <= CenterPoint)
            {
                circle = CIRCLE_EXIT;
                circle_time = 0;
                BING_ON;
//                record_last_image();
//                type = STOP;
            }
            break;
        }
        case CIRCLE_EXIT:
        {
            uint8 left_jump_point_find = 0;
            for (int i = ImgH - 10; i >= 15; i--)
            {
                if (leftLine[i].position > leftLine[i - 3].position && (leftLine[i - 3].position == LeftBoundary || leftLine[i - 3].position <= LeftBoundary + 15) \
                        && (leftLine[i - 8].position <= LeftBoundary + 10 || leftLine[i - 5].position <= LeftBoundary + 10))
                {
                    left_jump_point_find = 1;
                    break;
                }
            }
            if (left_lost_num < 10 && ((rightLine[ImgH - 3].lineStatus == NO_LOST || rightLine[ImgH - 6].lineStatus == NO_LOST) || circle_time >= 6) && circle_time >= 4 && !left_jump_point_find)
            {
                circle_time = 0;
                circle = CIRCLE_NONE;
//                record_last_image();
//                type = STOP;
            }
            //开始补线
            if (left_jump_point_find)
            {
//                left_Patching(leftLine[ImgH - 1].position, ImgH - 1, CenterPoint, height + 1);
                left_Patching(leftLine[ImgH - 1].position, ImgH - 1, CenterPoint + 15, height + 1);
            }
            else
            {
                left_Patching(leftLine[ImgH - 1].position, ImgH - 1, ImgW - 25, height + 1);
            }
            break;
        }
        case CIRCLE_NONE:
        {
           if (circle_time >= 4)
           {
               type = NORMAL;
               BING_OFF;
//               record_last_image();
//               type = STOP;
               circle_time = 0;
           }
            //到达此状态需要补右边线然后退出环岛状态
//            right_Patching(rightLine[ImgH - 1].position, ImgH - 1, CenterPoint + 20, height + 2);
//           if (rightLine[height + 2].lineStatus == LOST)
//           {
//               right_Patching(rightLine[ImgH - 1].position, ImgH - 1, CenterPoint - 10, height + 2);
//           }
//           else
//           {
//               right_Patching(rightLine[ImgH - 1].position, ImgH - 1, rightLine[height + 2].position, height + 2);
//           }
           right_Patching(rightLine[ImgH - 1].position, ImgH - 1, CenterPoint + 20, height);
            break;
        }
        }
    }
}

/*
 * @brief    运行断路
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      Run_OpenCricuit();
 */
void Run_OpenCricuit()
{
    if (open == OPEN_FOUND)
    {
        int cnt = 0;
        for (int i = 0; i < ImgW; i++)
            if (bin_img[ImgH - 1][i] == BLACK)
                cnt ++;
        if (cnt >= 80 && open_time >= 25)
        {
            open = OPEN_RUN;
//            record_last_image();
//            type = STOP;
            open_time = 0;
//            BING_OFF;
        }
    }
    if (open == OPEN_RUN)
    {
        // 检测图像信息
        if (leftLine[ImgH - 1].lineStatus == NO_LOST && leftLine[ImgH - 10].lineStatus == NO_LOST
                && rightLine[ImgH - 1].lineStatus == NO_LOST && rightLine[ImgH - 10].lineStatus == NO_LOST \
                && bin_img[ImgH - 1][CenterPoint] == WHITE && bin_img[ImgH - 1][CenterPoint + 10] == WHITE && bin_img[ImgH - 1][CenterPoint - 10] == WHITE && height <= 15)
        {
            type = NORMAL;
            open = OPEN_NONE;
            BING_OFF;
            open_time = 0;
//            record_last_image();
        }
    }
}

/*
 * @brief    运行障碍
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      Run_Hinder();
 */
void Run_Hinder()
{
    if (hinder == HINDER_STATUS_1 && hinder_time >= 4)
    {
        hinder = HINDER_STATUS_2;
        hinder_time = 0;
    }
    if (hinder == HINDER_STATUS_2 && hinder_time >= 6)
    {
        // 检测最后一行不为纯黑色
        hinder = HINDER_STATUS_3;
        hinder_time = 0;
    }
    if (hinder == HINDER_STATUS_3 && hinder_time >= 5)
    {
        hinder = HINDER_NONE;
        type = NORMAL;
        BING_OFF;
        hinder_time = 0;
    }
}

/*
 * @brief    显示图像信息
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      display();  //显示图像信息
 */
char text_dat[50];
void display ()
{
    // 显示图像
    tft180_show_gray_image(0,0,bin_img[0],MT9V03X_W,MT9V03X_H,MT9V03X_W,MT9V03X_H,0);
//    tft180_show_gray_image(0,0, mt9v03x_image[0],MT9V03X_W,MT9V03X_H,MT9V03X_W,MT9V03X_H,0);
    //显示边线 左右中线
    for(int i = height + 1; i < ImgH; i++)
    {
        if (leftLine[i].lineStatus == LOST)
        {
            tft180_draw_point(leftLine[i].position, i, RGB565_RED);
        }
        else
        {
            tft180_draw_point(leftLine[i].position, i, RGB565_RED);
        }
        if (rightLine[i].lineStatus == LOST)
        {
            tft180_draw_point(rightLine[i].position, i, RGB565_RED);
        }
        else
        {
            tft180_draw_point(rightLine[i].position, i, RGB565_RED);
        }
        tft180_draw_point(center[i], i, RGB565_RED);
    }
//    //图像可用高度
    for (int i = 0; i < ImgW; i++)
    {
        tft180_draw_point(i, test[0], RGB565_PINK);
        tft180_draw_point(i, test[1], RGB565_PURPLE);
        tft180_draw_point(i, prospect, RGB565_YELLOW);
    }
//
//    tft180_show_int(10, 90, ImgW - 1 - rightLine[ImgH - 1].position, 4);
//    tft180_show_int(60, 90, leftLine[ImgH - 1].position, 4);
//    tft180_show_float(10, 90, ftest[0], 4, 4);
    tft180_set_font(TFT180_6X8_FONT);
    sprintf(text_dat, "S4-OFF&S5-OFF 2.8m/s");
    tft180_show_string(0, 85, text_dat);
    sprintf(text_dat, "S4-ON&S5-OFF 2.6m/s");
    tft180_show_string(0, 95, text_dat);
    sprintf(text_dat, "S4-OFF&S5-ON 2.4m/s");
    tft180_show_string(0, 105, text_dat);
    sprintf(text_dat, "S4-ON&S5-ON 3m/s");
    tft180_show_string(0, 115, text_dat);
//    tft180_show_float(10, 110, ftest[1], 4, 4);
//    tft180_show_uint(60, 90, right_continuation_line, 4);
//    tft180_show_uint(110, 90, height, 4);
//
//    tft180_show_int(70, 90, test[2], 4);
//    tft180_show_uint(60, 110, leftLine[ImgH - 1].position, 4);
//    tft180_show_uint(110, 110, ImgW - 1 - rightLine[ImgH - 1].position, 4);
}

/*
 * @brief    显示文本信息
 *
 * @param    无
 *
 * @return   无
 *
 * @state    使用中
 *
 * @see      display_txt();  //显示文本信息
 */
void display_txt()
{
    // 显示停止前的最后一帧图像
    if (type == STOP)
    {
        tft180_show_gray_image(0,0,stop_last[0],MT9V03X_W,MT9V03X_H,MT9V03X_W,MT9V03X_H,0);
        for (int i = 0; i < ImgW; i++)
        {
            tft180_draw_point(i, test[0], RGB565_PINK);
            tft180_draw_point(i, test[1], RGB565_PURPLE);
            tft180_draw_point(i, prospect, RGB565_YELLOW);
        }
    }

    for(int i = height + 1; i < ImgH; i++)
    {
        tft180_draw_point(stop_left[i], i, RGB565_GREEN);
        tft180_draw_point(stop_right[i], i, RGB565_GREEN);
    }
    tft180_show_int(10, 90, test[0], 4);
    tft180_show_int(50, 90, test[1], 4);
    tft180_show_int(90, 90, left_continuation_line, 4);
    tft180_show_int(120, 90, right_continuation_line, 4);
//    tft180_show_float(10, 10,10.2, 3, 2);
//    tft180_show_float(50, 10, motor_r.encoder_speed, 3, 2);
//    tft180_show_float(10, 40, motor_l.duty, 3, 2);
//    tft180_show_float(50, 40, motor_l.MotionPID.ActualPWM, 3, 2);
}
