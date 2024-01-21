/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file            zf_usb_cdc
 * @company         成都逐飞科技有限公司
 * @author          逐飞科技(QQ790875685)
 * @version         查看doc内version文件 版本说明
 * @Software        MounRiver Studio V1.51
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2021-10-20
 ********************************************************************************************************************/

#ifndef _zf_usb_cdc_h
#define _zf_usb_cdc_h

#include "common.h"
#include "string.h"




void usb_cdc_init( void );
void cdc_send_pack(uint8 *p, uint32 length);
void seekfree_sendimg_usb_cdc(uint8 *image, uint32 length);

#endif
