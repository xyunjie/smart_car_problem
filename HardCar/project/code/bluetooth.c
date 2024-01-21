/*
 * bluetooth.c
 *
 *  Created on: 2023年7月25日
 *      Author: Accepted
 */
#include "bluetooth.h"
#include "electro.h"
#include "imgproc.h"

uint8 data_buffer[32];
uint8 blue_data_send_buff[64];
uint8 data_len;

void Send_Start()
{
    // 发信号前车启动发送
    *blue_data_send_buff = 0x01;
    bluetooth_ch9141_send_buff(blue_data_send_buff, sizeof 0x01);
}

void Emergency_Stop()
{
    // 接收到急停信号
    data_len = bluetooth_ch9141_read_buff(data_buffer, 32);
    if (data_len != 0)
    {
        if (*data_buffer == 0x35)
        {
            BING_ON;
            type = STOP;
        }
    }
}

void Send_Emergency_Stop()
{
    // 接收到急停信号
    *blue_data_send_buff = 0x35;
    bluetooth_ch9141_send_buff(blue_data_send_buff, sizeof 0x01);
}

void Wait_Start()
{
    // 等待开始
    data_len = bluetooth_ch9141_read_buff(data_buffer, 32);
    if (data_len != 0)
    {
        if (*data_buffer == 0x11)
        {
//            BING_ON;
//            system_delay_ms(300);
//            BING_OFF;
            charge_time = 0;
            charge = CHARGE_STATUS_1;
//            type = OUTBARN;
        }
    }
}
