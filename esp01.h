#ifndef ESP01_H
#define ESP01_H

#include "stm32f4xx.h"
#include <stm32f4xx_usart.h>
#include <stm32f4xx_rcc.h>
#include <string.h>
#include <stdio.h>

void MX_USART1_UART_Init(void);
void MX_USART7_UART_Init(void);
void DelayTimerUs(int n);
void usartSendArrar(USART_TypeDef *USART, uint8_t *Arrar);
void configure_timer_delay(void);
void send_COMMANDE(char cmd[30]);
uint8_t USART_ReceiveDataa(USART_TypeDef* USARTx);
void USART_SendDataa(USART_TypeDef* USARTx, uint8_t data);
void UART7_IRQHandler(void);
void wifi_connect(char ssid[20], char psswd[20]);
void am_i_connected(void);
void list_wifi(void);
void send_data_to_server(char data[50], char *size_data);
void request_site(char site[20], char port[4], char methode[50], char path[20], char POST_DATA[500]);

#endif 
