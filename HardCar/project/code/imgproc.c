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

/** ��ֵ��ͼ�� */
uint8 bin_img[ImgH][ImgW] = {0};
uint8 stop_last[ImgH][ImgW] = {0};
uint8 stop_left[ImgH] = {0};
uint8 stop_right[ImgH] = {0};

/** ����߽�*/
LineNode leftLine[ImgH] = {0};
/** ���ұ߽�*/
LineNode rightLine[ImgH] = {0};

/** ���������� */
uint8 left_very_jump;
/** ����������λ�� */
uint8 left_very_jump_row;

/** ���������� */
uint8 right_very_jump;
/** ����������λ�� */
uint8 right_very_jump_row;

/** �������� */
uint8 center[MT9V03X_H] = {0};
/** ����ƫ������*/
int RoadErr[ImgH];
/** ���߻�׼*/
uint8 RoadCenter = ImgW / 2;
/** ·��ƫ��*/
float PathDeviation;
/** ����ͼ��߶�*/
uint8 height;
/** ǰհλ��*/
uint8 prospect;

/** ����*/
int test[4];
float ftest[4];

/** ��������*/
int left_lost_num;
int right_lost_num;

/** ���ҵ����� */
int left_point_num;
int right_point_num;

/** ����Ԫ������*/
EleType type;

uint8 enable_team = 0;
uint8 left_continuation_line = 0;
uint8 right_continuation_line = 0;

/*Ԫ�ؼ�ʱ*/
int charge_time = 0;
int zebra_time = 0;
int outbarn_time = 0;
int hinder_time = 0;
int circle_time = 0;
int ramp_time = 0;
int cross_time = 0;
int open_time = 0;
/*Ԫ�ؼ�ʱ*/

/*Ԫ��״̬����*/
CrossStatus cross;
OpenStatus open;
HinderStatus hinder;
OutbarnStatus outbarn;
ChargeStatus charge;
// Բ��
CircleCheckStatus circleCheckStatus = CIRCLE_CHECK_NONE;
CircleDirection circleDirection;
CircleStatus circle;
/*Ԫ��״̬����*/

// ͼ����ֵ
uint8 t1 = 0;
uint8 t2 = 0;
uint8 t3 = 0;


/*
 * @brief    �ػ��㷨
 *
 * @param    image    �� Ԥ����ͼ��ָ��
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
 * @brief    ��򷨶�̬��ֵ
 *
 * @param    tmImgage    �� ������ֵͼ������
 *
 * @return   Threshold   ����������ֵ
 *
 * @see      GetOSTU(mt9v03x_image_dvp);  //�������ͷ��ȡ��ͼ��������ֵ
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
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��;
    signed short MinValue, MaxValue;
    signed short Threshold = 0;
    short HistoGram[256] = {0};

    for (j = 0; j < ImgH; j++)
    {
        for (i = 0; i < ImgW; i++)
        {
            HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //��ȡ��С�Ҷȵ�ֵ
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //��ȡ���Ҷȵ�ֵ

    if (MaxValue == MinValue)
        return MaxValue;         // ͼ����ֻ��һ����ɫ
    if (MinValue + 1 == MaxValue)
        return MinValue;        // ͼ����ֻ�ж�����ɫ

    for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        //  ��������

    Pixelshortegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        Pixelshortegral += HistoGram[j] * j;        //�Ҷ�ֵ����
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];     //ǰ�����ص���
        PixelFore = Amount - PixelBack;           //�������ص���
        OmegaBack = (float) PixelBack / Amount;   //ǰ�����ذٷֱ�
        OmegaFore = (float) PixelFore / Amount;   //�������ذٷֱ�
        PixelshortegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //�����Ҷ�ֵ
        MicroBack = (float) PixelshortegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
        MicroFore = (float) PixelshortegralFore / PixelFore;   //�����ҶȰٷֱ�
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //������䷽��
        if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //���������ֵ;
}

/*
 * @brief    ���ߺ���
 *
 * @param    dx1    �� ��ʼλ��������
 * @param    dy1    �� ��ʼλ�ú�����
 * @param    dx2    �� ����λ��������
 * @param    dy2    ������λ�ú�����
 *
 * @return   ��
 *
 * @see      left_Patching(1, ImgH - 1, ImgW - 1, 1);  //�����ߴ����½��������Ͻ�
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
 * @brief    �Ҳ��ߺ���
 *
 * @param    dx1    �� ��ʼλ��������
 * @param    dy1    �� ��ʼλ�ú�����
 * @param    dx2    �� ����λ��������
 * @param    dy2    ������λ�ú�����
 *
 * @return   ��
 *
 * @see      right_Patching(ImgW - 1, ImgH - 1, 1, 1);  //�����ߴ����½��������Ͻ�
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
 * @brief    ���ߺ���
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      search_line();  //������ұ���
 */
void search_line()
{
    // ��ʼ�����ұ߽�
    for (int i = 0; i < ImgH ; i++)
    {
        leftLine[i].position = LeftBoundary;
        leftLine[i].lineStatus = NO_LOST;
        rightLine[i].position = RightBoundary;
        rightLine[i].lineStatus = NO_LOST;
    }
    //�������ұ����ҵ�
    uint8 Find_Left = 0, Find_Right = 0;
    //��ʼ�����Ҷ�������
    left_lost_num = right_lost_num = 0;
    right_point_num = left_point_num = 0;
    //������һ�����
    if (bin_img[ImgH - 1][CenterPoint] == BLACK)
    {
        //��������ɨ��
        for (int i = 1; i < ImgW - 2; i++)
        {
            if (bin_img[ImgH - 1][i] == WHITE && bin_img[ImgH - 1][i + 1] == BLACK)
            {
                //��һ���׺�����
                leftLine[ImgH - 1].position = LeftBoundary;
                leftLine[ImgH - 1].lineStatus = LOST;
                rightLine[ImgH - 1].position = i + 1;
                right_point_num = 1;
                break;
            }
            else if (bin_img[ImgH - 1][i] == BLACK && bin_img[ImgH - 1][i + 1] == WHITE)
            {
                //��һ���ڰ������
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
        //û���ҵ�����,�ж�Ϊ����
        if(Find_Left == 0)
        {
            leftLine[ImgH - 1].position = LeftBoundary;
            leftLine[ImgH - 1].lineStatus = LOST;
            left_lost_num ++;
        }
        //������һ���ҵ�
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
        //û���ҵ��ҵ�
        if(Find_Right == 0)
        {
            rightLine[ImgH - 1].position = RightBoundary;
            rightLine[ImgH - 1].lineStatus = LOST;
            right_lost_num ++;
        }
    }
    //�����ҵ������ұ߽����������
    for (int i = ImgH - 1 - 1; i >= 5; i--)
    {
        left_very_jump = right_very_jump = 0;
        //��ʼ�����ұ߽��Ƿ��ҵ���־
        Find_Left = Find_Right = 0;
        //������һ�е���߽�����������
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
            //����û�ҵ��߽磬����
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
            //��һ�п��ܻ��Ǳ߽�㣬��һ��Ϊ�߽��
            if (leftLine[i + 1].position == LeftBoundary && \
                    bin_img[i][leftLine[i + 1].position] == WHITE && \
                    bin_img[i][leftLine[i + 1].position + 1] == WHITE && \
                    bin_img[i][leftLine[i + 1].position - 1] == WHITE)
            {
                //��һ��ҲΪ��ɫ
                leftLine[i].position = LeftBoundary;
                leftLine[i].lineStatus = LOST;
                Find_Left = 2;
                left_lost_num ++;
            }
        }

        if (!Find_Left)
        {
            //����������Ҷ�û�ҵ��߽�㣬��ô����ɨ����һ��
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
            //����
            leftLine[i].position = LeftBoundary;
            leftLine[i].lineStatus = LOST;
            left_lost_num ++;
        }

        if (ABS(leftLine[i].position - leftLine[i + 1].position) > 40 || (leftLine[i].position == LeftBoundary && leftLine[i + 1].position > ImgW / 2))
        {
            left_very_jump = 1;
            left_very_jump_row = i + 1;
        }
        //����������������
        //��ʼ�����ұ���,����������
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
            //����û�ҵ��߽磬����
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
            //��һ�п��ܻ��Ǳ߽�㣬��һ��Ϊ�߽��
            if (rightLine[i + 1].position == RightBoundary &&\
                    bin_img[i][rightLine[i + 1].position - 1] == WHITE &&\
                    bin_img[i][rightLine[i + 1].position + 1] == WHITE &&\
                    bin_img[i][rightLine[i + 1].position] == WHITE)
            {
                //��һ��ҲΪ��ɫ
                rightLine[i].position = RightBoundary;
                rightLine[i].lineStatus = LOST;
                Find_Right = 2;
                right_lost_num ++;
            }
        }

        if (!Find_Right)
        {
            //����������Ҷ�û�ҵ��߽�㣬��ô����ɨ����һ��
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
            //����
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
 * @brief    ���ͼ��߶�
 *
 * @param    ��
 *
 * @return   height ��ͼ���ʹ�ø߶�
 *
 * @state    ʹ����
 *
 * @see      get_Img_Height();  //���ͼ��߶�
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
 * @brief    �������
 *
 * @param    h ��ͼ����ø߶�
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      get_Center_Road(height);  //���ͼ������
 */
void get_Center_Road (uint8 h)
{
    for (int i = ImgH - 1; i >= h; i--)
    {
        center[i] = (leftLine[i].position + rightLine[i].position) / 2;
        //������������Ѵ���ô�м���������
        if (center[i] == BLACK)
        {
            center[i] = ImgW / 2;
        }

        RoadErr[i] = CenterPoint - center[i];
    }
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
 * @see      handle_outer(height);  //���ͼ������
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
 * @brief    ��ȡ����ƫ��
 *
 * @param    Err[ImgH]  ��ƫ������
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      CalculationDeviation(RoadErr);  //��ȡ����ƫ��
 */

void CalculationDeviation(int Err[ImgH])
{
    PathDeviation = (Err[prospect - 2] + Err[prospect] + Err[prospect + 2]) / 3;
}

/*
 * @brief    ͼ���ֵ��
 *
 * @param    threshold  ����ֵ
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      get_Bin_Img (threshold);  //ͼ���ֵ��
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
 * @brief    ����Ӧǰհ�߶�
 *
 * @param    h  ��ͼ��߶�
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      Adaptive_Look_Ahead(height);  //����Ӧǰհ�߶�
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
 * @brief    Ԥ����ͼ��
 *
 * @param    image    �� Ԥ����ͼ��ָ��
 *
 * @return   Threshold   ����������ֵ
 *
 * @see      ImagePrepro(mt9v03x_image_dvp);  //Ԥ����ͼ��
 */
void ImagePrepro ()
{
    // �ػ�ͼ��
//    uint8 outImage[ImgH / 2][ImgW / 2];
//    minPooling(mt9v03x_image, 2, outImage);
    // �����ֵ
//    int threshold = GetOSTU(outImage);
    int threshold = GetOSTU(mt9v03x_image);
    get_Bin_Img(threshold);
//    test[2] = threshold;
//    if (threshold > THRESHOLD_MAX) threshold = THRESHOLD_MAX;
//    if (threshold < THRESHOLD_MIN)  threshold = THRESHOLD_MIN;
    // �õ���ֵ��ͼ��
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
 * @brief    ͼ����
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      Process_Image();  //ͼ����
 */
void Process_Image()
{
    // ͼ��Ԥ����
    ImagePrepro();
    //������ұ���
    search_line();
    //���ͼ��߶�
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
 * @brief    �����������
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      check_cross();  //���ʮ��·
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
 * @brief    ���ʮ��
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      check_corss();  //��������
 */
void check_cross()
{
    //��¼���������Ƿ����
    int left_jump = 0, right_jump = 0;
    int left_point = 0, right_point = 0;
    for (int i = ImgH - 1; i >= 25; i--)
    {
        if (leftLine[i].position > leftLine[i - 2].position && leftLine[i - 2].position == LeftBoundary && i > 10)
        {
            //��¼����������
            left_jump = 1;
            left_point = i - 2;
            break;
        }
    }
    for (int i = ImgH - 1; i >= 25; i--)
    {
        if (rightLine[i].position < rightLine[i - 2].position && rightLine[i - 2].position == RightBoundary && i > 10)
        {
            //��¼�ұ��������
            right_jump = 1;
            right_point = i - 2;
            break;
        }
    }

    if (left_jump && right_jump && (left_point >= 25 || right_point >= 25) && rightLine[right_point - 3].lineStatus == LOST && leftLine[left_point - 3].lineStatus == LOST)
    {
        int err = left_point - right_point;
        err = err < 0 ? -err : err;
        //�ж�һ��
        if (left_lost_num >= 5 && right_lost_num >= 5 && err <= 15)
        {
            // ��Բ��״̬��Ϊ0
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
 * @brief    ��������
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      check_zebra();  //��������
 */
void check_zebra()
{
    //���һ���кڰ�����Ĵ���
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
        // ��Բ��״̬��Ϊ0
        circleCheckStatus = CIRCLE_CHECK_NONE;
        circle_time = 0;
//        type = ZEBRA;
        BING_ON;
//        record_last_image();
        type = STOP;
    }
}
/*
 * @brief    ����µ�
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      check_ramp();  //��������
 */
void check_ramp()
{
    if (infraredNum >= 1500)
    {
        if (leftLine[ImgH - 1].lineStatus == NO_LOST && rightLine[ImgH - 1].lineStatus == NO_LOST && abs(PathDeviation) < 15)
        {
            // ��Բ��״̬��Ϊ0
            circleCheckStatus = CIRCLE_CHECK_NONE;
            circle_time = 0;
            type = RAMP;
        }
    }
}

/*
 * @brief    ����ϰ�
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      check_zebra();  //��������
 */
void check_hinder()
{
    if (infraredNum >= 700)
    {
        // �����ϰ���һҪ�󣬺�����
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
            // �����ϰ��ڶ�Ҫ��
            if (height >= 20 && abs(left_lost_num - right_lost_num) < 10)
            {
                // ��Բ��״̬��Ϊ0
                circleCheckStatus = CIRCLE_CHECK_NONE;
                circle_time = 0;
                // �����ϰ�����Ҫ��
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
 * @brief    ����·
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      check_opencircuit();  //����·
 */
void check_opencircuit()
{
    int black_line = 20;
    // �����ж��Ƿ����������
    int cnt = 0;
    // �����еĺڵ�����
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
            // ��Բ��״̬��Ϊ0
            circleCheckStatus = CIRCLE_CHECK_NONE;
            circle_time = 0;
            // �����в�Ϊ����ɫ
//            type = STOP;
//            record_last_image();
            type = OPENCIRCUIT;
//            BING_ON;
            open = OPEN_FOUND;
            open_time = 0;
            return;
        }
    }

    // ����������
    int open_left_lost = 0, open_right_lost = 0;
    for (int i = ImgH - 1; i >= height + 1; i --)
    {
        if (leftLine[i].lineStatus == LOST) open_left_lost ++;
        if (rightLine[i].lineStatus == LOST)    open_right_lost ++;
    }
    if (open_left_lost <= 3 && open_right_lost <= 3)
    {
        // Ѱ�����߻������ߵ�����
        int left_point = 0, right_point = 0;
        int right_jump_p = 0, left_jump_p = 0;
        for (int i = ImgH - 6; i >= height + 5; i--)
        {
            if ((leftLine[i].position < leftLine[i - 5].position && abs(leftLine[i].position - leftLine[i - 5].position) >= 5) \
                    && leftLine[i].position < leftLine[i + 5].position \
                    && (leftLine[i - 5].lineStatus == NO_LOST || leftLine[i - 5].position != LeftBoundary) && leftLine[i].lineStatus != LOST)
            {
                // ������
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
                // ������
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
            // ����Ѱ�ҵ�1
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
            // ��ʼ����б��
            k_1 = (p_1 - p_2) / (float)(leftLine[p_1].position - leftLine[p_2].position);
            k_2 = (p_2 - p_3) / (float)(leftLine[p_2].position - leftLine[p_3].position);
            ftest[0] = k_1;
            ftest[1] = k_2;
            if (abs(k_1) + abs(k_2) >= 2 && abs(k_1) + abs(k_2) <= 4)
            {
                // ��ϵ�һ��ֱ��
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
                    // �����в�Ϊ����ɫ
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
            // �ж�
        }
        else if (right_point && !left_point && !left_jump_p)
        {
            test[0] = right_point;
            // ����Ѱ�ҵ�1
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
            // ��ʼ����б��
            k_1 = (p_1 - p_2) / (float)(rightLine[p_1].position - rightLine[p_2].position);
            k_2 = (p_2 - p_3) / (float)(rightLine[p_2].position - rightLine[p_3].position);
            ftest[0] = k_1;
            ftest[1] = k_2;
            if (abs(k_1) + abs(k_2) >= 2 && abs(k_1) + abs(k_2) <= 8)
            {
                // ��ϵ�һ��ֱ��
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
                    // �����в�Ϊ����ɫ
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
 * @brief    ��⻷��
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      check_circle();  //��⻷��
 */
void check_circle()
{
    if (circle_time >= 50)
        circle_time = 0;
    // Ѱ�����ҹյ�
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
        // ����Ѱ��һ���յ�
        for (int i = left_jump; i >= height; i--)
        {
            if (bin_img[i][leftLine[left_jump].position] == WHITE && bin_img[i - 1][leftLine[left_jump].position] == BLACK)
            {
                //�ҵ���յ�
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
        //�ҵ��ҹյ�
        int is_circle_status = 0;
        // ����Ѱ��һ���յ�
        for (int i = right_jump; i >= height; i--)
        {
            if (bin_img[i][rightLine[right_jump].position] == WHITE && bin_img[i - 1][rightLine[right_jump].position] == BLACK)
            {
                //�ҵ���յ�
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


    //�ҵ��յ㿪ʼ��¼
    switch (circleCheckStatus)
    {
    case CIRCLE_CHECK_STATUS_1:
    {
        //����״̬1�������ҵ���/�ҹյ�
        //����������������������������
        uint8 circle_status = 0;
        if (circleDirection == LEFT_CIRCLE)
        {
            //��߹յ�
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
            //�ұ߹յ�
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
            //����״̬2
            circleCheckStatus = CIRCLE_CHECK_STATUS_2;
            circle_time = 0;
        }

        if (circle_time >= 5)
        {
            circleCheckStatus = CIRCLE_CHECK_NONE;
            circle_time = 0;
        }
        //�õ�����
        break;
    }
    case CIRCLE_CHECK_STATUS_2:
    {
        //����ж���
        //��������10��ȫ������
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
            //�������ߣ��ҵ����õĲ��ߵ�
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
            //�ҵ����ߵĵ�
            left_Patching(leftLine[start_point].position, start_point, CenterPoint + 20, height);
        }
        else if (circleDirection == RIGHT_CIRCLE)
        {
            //�������ߣ��ҵ����õĲ��ߵ�
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

            //�ҵ����ߵĵ�
        }
        break;
    }
    case CIRCLE_CHECK_STATUS_3:
    {
        uint8 status_point = 0;
        if (circleDirection == LEFT_CIRCLE && (leftLine[ImgH - 1].lineStatus == NO_LOST && leftLine[ImgH - 1].position > LeftBoundary + 10))
        {
            // �󻷵�����������
            for (int i = ImgH - 1; i >= height + 3; i--)
            {
                if (leftLine[i].position > leftLine[i - 1].position) status_point ++;
            }
        }
        else if (circleDirection == RIGHT_CIRCLE && (rightLine[ImgH - 1].lineStatus == NO_LOST && rightLine[ImgH - 1].position > LeftBoundary + 10))
        {
            // �һ�������������
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
            //�������ߣ��ҵ����õĲ��ߵ�
            uint8 start_point = ImgH - 1, end_point = 0;
            for (int i = ImgH - 1; i >= height; i--)
            {
                if (leftLine[i].position > leftLine[end_point].position)
                {
                    end_point = i;
                }
            }

            //�ҵ����ߵĵ�
            left_Patching(leftLine[start_point].position, start_point, leftLine[end_point].position, height);
        }
        else if (circleDirection == RIGHT_CIRCLE)
        {
            //�������ߣ��ҵ����õĲ��ߵ�
            uint8 start_point = ImgH - 1, end_point = ImgH - 1;
            for (int i = ImgH - 1; i >= height; i--)
            {
                if (rightLine[i].position < rightLine[end_point].position)
                {
                    end_point = i;
                }
            }

            //�ҵ����ߵĵ�
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
            //�������ߣ��ҵ����õĲ��ߵ�
            uint8 start_point = ImgH - 1, end_point = 0;
            for (int i = ImgH - 1; i >= height; i--)
            {
                if (leftLine[i].position > leftLine[end_point].position)
                {
                    end_point = i;
                }
            }

            //�ҵ����ߵĵ�
            left_Patching(leftLine[start_point].position, start_point, leftLine[end_point].position, height);
        }
        else if (circleDirection == RIGHT_CIRCLE)
        {
            //�������ߣ��ҵ����õĲ��ߵ�
            uint8 start_point = ImgH - 1, end_point = ImgH - 1;
            for (int i = ImgH - 1; i >= height; i--)
            {
                if (rightLine[i].position < rightLine[end_point].position)
                {
                    end_point = i;
                }
            }

            //�ҵ����ߵĵ�
            right_Patching(ImgW - 1 - leftLine[start_point].position, start_point, rightLine[end_point].position, height);
        }
        break;
    }
    default:
        break;
    }
}

/*
 * @brief    ���ͣ��
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      check_stop();  //���ͣ��
 */
void check_stop()
{
    if (type == HINDER)
        return;
//    Send_Emergency_Stop();
    if (type == OPENCIRCUIT)
    {
        // �Ƚϵ��ֵ���м���
        if (adcNum[0] < ADC_MIN_NUM && adcNum[1] < ADC_MIN_NUM && adcNum[2] < ADC_MIN_NUM && adcNum[3] < ADC_MIN_NUM && adcNum[4] < ADC_MIN_NUM)
        {
            type = STOP;
        }
        return;
    }
    int cnt = 0;
    // �����еĺڵ�����
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
 * @brief    Ѳ��
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      Line_patrol();  //Ѳ��
 */
void Line_patrol()
{
    //���ݸ߶����ͼ������
    get_Center_Road(height);
    //����ǰհ
    Adaptive_Look_Ahead(height);
    //����ƫ��ֵ
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
        // �˳����
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
 * @brief    ����ʮ��
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      Run_Cross();
 */
void Run_Cross()
{
    // �жϵ�ǰ����ʮ�ֵ��Ǹ�λ��
    if (cross == CROSS_NONE)
    {
        // �ոս���ʮ��״̬�жϴ���ʮ�ֵ��Ǹ�λ��
        // 1.�ж���5�е�״̬
        int leftLostNum = 0, rightLostNum = 0;
        for (int i = ImgH - 1; i >= ImgH - 6; i--)
        {
            if (leftLine[i].lineStatus == LOST)
                leftLostNum ++;
            if (rightLine[i].lineStatus == LOST)
                rightLostNum ++;
        }
        // ͨ���ж϶��ߵ������ж�
        if ((leftLostNum >= 3 && rightLostNum >= 3 && cross_time >= 5  && leftLine[ImgH - 1].lineStatus == LOST && rightLine[ImgH - 1].lineStatus == LOST) || cross_time >= 10)
        {
            cross = CROSS_ENTRY;
            cross_time = 0;
        }
        else
        {
            // �����Ҷ���������
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
            // ����
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
        // ����Ѱ�Ҳ��ߵ�
        int left_point_line = 0, left_point_find = 0;
        int right_point_line = 0, right_point_find = 0;
        // ����
        for (int i = ImgH - 1; i >= height + 3; i--)
        {
            if (leftLine[i].lineStatus == LOST && leftLine[i - 2].lineStatus == NO_LOST && leftLine[i - 3].lineStatus == NO_LOST)
            {
                left_point_line = i - 2;
                left_point_find = 1;
                break;
            }
        }
        // ����
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
        // ���������
        // ����
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
        // ����
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
        // ����Ѱ�Ҳ��ߵ�
        int left_point_line = 0, left_point_find = 0;
        int right_point_line = 0, right_point_find = 0;
        // ����
        for (int i = ImgH - 1; i >= height + 3; i--)
        {
            if (leftLine[i].lineStatus == LOST && leftLine[i - 2].lineStatus == NO_LOST && leftLine[i - 3].lineStatus == NO_LOST)
            {
                left_point_line = i - 2;
                left_point_find = 1;
                break;
            }
        }
        // ����
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
 * @brief    �����µ�
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      Run_Ramp();
 */
void Run_Ramp()
{
    if (ramp_time >= 25)
        type = NORMAL;
}
/*
 * @brief    ����Բ��
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      Run_Circle();
 */
void Run_Circle()
{
    if (circleDirection == LEFT_CIRCLE)
    {
        //�󻷵�
        switch (circle)
        {
        case CIRCLE_FOUND:
        {
            // ɨ������
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
                //����Բ��
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
            //��ʼ����
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
            //��ʼ����
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
            //�����״̬��Ҫ���ұ���Ȼ���˳�����״̬
            left_Patching(leftLine[ImgH - 1].position, ImgH - 1, CenterPoint - 10, height + 2);
            break;
        }
        }
    }
    else if (circleDirection == RIGHT_CIRCLE)
    {
        //�һ���
        switch (circle)
        {
        case CIRCLE_FOUND:
        {
            // ɨ������
            uint8 jump_point = 0;
            for (int i = ImgH - 1; i >= height + 3; i--)
            {
                if (leftLine[i].position < leftLine[i - 1].position && (leftLine[i - 1].position - leftLine[i].position >= 15))
                {
                    jump_point = i;
                    break;
                }
            }
                // û���ҵ��յ�
            if ((jump_point != 0 && circle_time >= 3) || circle_time >= 7)
            {
                //����Բ��
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
            //��ʼ����
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
            //�����״̬��Ҫ���ұ���Ȼ���˳�����״̬
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
 * @brief    ���ж�·
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
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
        // ���ͼ����Ϣ
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
 * @brief    �����ϰ�
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
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
        // ������һ�в�Ϊ����ɫ
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
 * @brief    ��ʾͼ����Ϣ
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      display();  //��ʾͼ����Ϣ
 */
char text_dat[50];
void display ()
{
    // ��ʾͼ��
    tft180_show_gray_image(0,0,bin_img[0],MT9V03X_W,MT9V03X_H,MT9V03X_W,MT9V03X_H,0);
//    tft180_show_gray_image(0,0, mt9v03x_image[0],MT9V03X_W,MT9V03X_H,MT9V03X_W,MT9V03X_H,0);
    //��ʾ���� ��������
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
//    //ͼ����ø߶�
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
 * @brief    ��ʾ�ı���Ϣ
 *
 * @param    ��
 *
 * @return   ��
 *
 * @state    ʹ����
 *
 * @see      display_txt();  //��ʾ�ı���Ϣ
 */
void display_txt()
{
    // ��ʾֹͣǰ�����һ֡ͼ��
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
