#include "ch32v10x_usart.h"
#include "ch32v10x_rcc.h"
#include "board.h"
#include "ch32v10x_gpio.h"



void board_init(void)
{
    GPIO_DeInit(GPIOA);
    GPIO_DeInit(GPIOB);
    GPIO_DeInit(GPIOC);
    GPIO_DeInit(GPIOD);

    //��ȡϵͳ��Ƶ
    sys_clk = 8000000 * (((RCC->CFGR0 >> 18)&0x0F) + 2);
    //��ʼ��DEBUG����
    uart_init(DEBUG_UART, DEBUG_UART_BAUD, DEBUG_UART_TX_PIN, DEBUG_UART_RX_PIN);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      printf�ض���
//  @param      void
//  @return     void
//  @since      v1.0
//  Sample usage:              �ض���printf��DEBUG������
//-------------------------------------------------------------------------------------------------------------------
#if (1 == PRINTF_ENABLE)
int _write(int fd, char *buf, int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        while (USART_GetFlagStatus((USART_TypeDef*)UARTN[DEBUG_UART], USART_FLAG_TC) == RESET);
        USART_SendData((USART_TypeDef*)UARTN[DEBUG_UART], *buf++);
    }
    return size;
}
#endif

