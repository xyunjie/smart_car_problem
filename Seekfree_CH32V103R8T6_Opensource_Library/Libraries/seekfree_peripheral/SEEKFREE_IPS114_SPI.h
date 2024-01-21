/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		IPSҺ��
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MounRiver Studio V1.51
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-03-06
 * @note		
					���߶��壺
					------------------------------------ 
						ģ��ܽ�            ��Ƭ���ܽ�
                        SCL                 �鿴IPS114_SCL_PIN�궨�������     Ӳ��SPI���Ų��������л�
						SDA                 �鿴IPS114_SDA_PIN�궨�������     Ӳ��SPI���Ų��������л�
						RES                 �鿴IPS114_REST_PIN�궨�������    
						DC                  �鿴IPS114_DC_PIN�궨�������  
						CS                  �鿴IPS114_CS_PIN�궨�������      Ӳ��SPI���Ų��������л�
						
						��Դ����
						BL  3.3V��Դ������������ţ�Ҳ���Խ�PWM���������ȣ�
						VCC 3.3V��Դ
						GND ��Դ��
						���ֱ���135*240
					------------------------------------ 

 ********************************************************************************************************************/


#ifndef _SEEKFREE_IPS114_H
#define _SEEKFREE_IPS114_H


#include "common.h"
#include "SEEKFREE_FONT.h"


//-----------------���Ŷ���------------------------------
#define IPS114_SPIN             SPI_1           //����ʹ�õ�SPI��
#define IPS114_SCL_PIN          SPI1_SCK_PA5    //����SPI_SCK����
#define IPS114_SDA_PIN          SPI1_MOSI_PA7   //����SPI_MOSI����
#define IPS114_SDA_IN_PIN       SPI_MISO_NULL   //����SPI_MISO����
#define IPS114_REST_PIN         C13             //Һ����λ���Ŷ��� ����ʵ��ͨѶδʹ��B2��� ���︴��ΪGPIO
#define IPS114_DC_PIN 	        C14	            //Һ������λ���Ŷ���
#define IPS114_CS_PIN           C15             //����SPI_CS����
#define IPS114_BL_PIN           PIN_NULL        //Һ���������Ŷ���

#define IPS114_DC(x)            ((x == 0)? (GPIO_PIN_RESET(IPS114_DC_PIN))  :(GPIO_PIN_SET(IPS114_DC_PIN)))
#define IPS114_REST(x)          ((x == 0)? (GPIO_PIN_RESET(IPS114_REST_PIN)):(GPIO_PIN_SET(IPS114_REST_PIN)))
#define IPS114_CS(x)            ((x == 0)? (GPIO_PIN_RESET(IPS114_CS_PIN))  :(GPIO_PIN_SET(IPS114_CS_PIN)))


//-------������ɫ��SEEKFREE_FONT.h�ļ��ж���----------
//#define RED          	    0xF800	//��ɫ
//#define BLUE         	    0x001F  //��ɫ
//#define YELLOW       	    0xFFE0	//��ɫ
//#define GREEN        	    0x07E0	//��ɫ
//#define WHITE        	    0xFFFF	//��ɫ
//#define BLACK        	    0x0000	//��ɫ 
//#define GRAY  			0X8430 	//��ɫ
//#define BROWN 			0XBC40 	//��ɫ
//#define PURPLE    		0XF81F	//��ɫ
//#define PINK    		    0XFE19	//��ɫ


//����д�ֱʵ���ɫ
#define IPS114_PENCOLOR    RED

//���屳����ɫ
#define IPS114_BGCOLOR     WHITE



#define IPS114_W   135
#define IPS114_H   240

//������ʾ����
//0 ����ģʽ
//1 ����ģʽ  ��ת180
//2 ����ģʽ
//3 ����ģʽ  ��ת180
#define IPS114_DISPLAY_DIR 3

#if (0==IPS114_DISPLAY_DIR || 1==IPS114_DISPLAY_DIR)
#define	IPS114_X_MAX	IPS114_W	//Һ��X������
#define IPS114_Y_MAX	IPS114_H    //Һ��Y������
     
#elif (2==IPS114_DISPLAY_DIR || 3==IPS114_DISPLAY_DIR)
#define	IPS114_X_MAX	IPS114_H	//Һ��X������
#define IPS114_Y_MAX	IPS114_W    //Һ��Y������
     
#else
#error "IPS114_DISPLAY_DIR �������"
     
#endif


void ips114_init(void);
void ips114_clear(uint16 color);
void ips114_drawpoint(uint16 x,uint16 y,uint16 color);
void ips114_showchar(uint16 x,uint16 y,const int8 dat);
void ips114_showstr(uint16 x,uint16 y,const int8 dat[]);
void ips114_showint8(uint16 x,uint16 y,int8 dat);
void ips114_showuint8(uint16 x,uint16 y,uint8 dat);
void ips114_showint16(uint16 x,uint16 y,int16 dat);
void ips114_showuint16(uint16 x,uint16 y,uint16 dat);
void ips114_showint32(uint16 x,uint16 y,int32 dat,uint8 num);
void ips114_showfloat(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum);
void ips114_displayimage032(uint8 *p, uint16 width, uint16 height);
void ips114_displayimage032_zoom(uint8 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips114_displayimage032_zoom1(uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y, uint16 dis_width, uint16 dis_height);
void ips114_displayimage8660_zoom(uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips114_displayimage8660_zoom1(uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y, uint16 dis_width, uint16 dis_height);
void ips114_displayimage7725(uint8 *p, uint16 width, uint16 height);
void ips114_display_chinese(uint16 x, uint16 y, uint8 size, const uint8 *p, uint8 number, uint16 color);

#endif