#include "stm32f4xx.h"
#include <stm32f4xx_usart.h>
#include <stm32f4xx_rcc.h>
#include "string.h"
#include "stdio.h"
#define BAUD_RATE 115200
// HSE = 8MHZ
// USART1 AND UART7
void MX_USART1_UART_Init(void) {
  /* Enable USART clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	    NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Set alternate function for USART1 pins */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

  /* Configure USART */
  USART_InitTypeDef USART_InitStructure;

  /* Calculate PCLK1 frequency based on HSE and AHB prescaler (assuming no pre-division) */
  uint32_t  pclk1 = HSE_VALUE;
  uint32_t ahb_prescaler = ((RCC->CFGR & RCC_CFGR_HPRE) >> 4) + 1; // Assuming direct access is available
  if (ahb_prescaler != 0) {
    pclk1 /= ahb_prescaler;
  }

  /* Set baud rate using the calculated PCLK1 frequency and desired baud rate */
  uint32_t baud_rate = 115200;  // Desired baud rate (adjustable)
  uint32_t usartdiv = (pclk1 * 2) / baud_rate;  // Calculate USARTDIV based on formula

  /* Adjust USART configuration for oversampling effect (if baud rate is below 3600) */
    /* Option 1: Increase baud rate and adjust USARTDIV for oversampling by 8 */
    USART_InitStructure.USART_BaudRate = baud_rate ;  // Double the baud rate  
	
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE);
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // Enable the UART7 IRQ channel in the NVIC
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}



void MX_USART7_UART_Init(void) {
    /* Enable USART clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;

    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_SetPriorityGrouping(7);
    NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

    GPIO_Init(GPIOF, &GPIO_InitStructure);

    /* Set alternate function for USART7 pins */
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource6, GPIO_AF_UART7);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource7, GPIO_AF_UART7);

    /* Configure USART */
    USART_InitTypeDef USART_InitStructure;
    uint32_t pclk1 = HSE_VALUE;
    uint32_t ahb_prescaler = ((RCC->CFGR & RCC_CFGR_HPRE) >> 4) + 1; // Assuming direct access is available
    if (ahb_prescaler != 0) {
        pclk1 /= ahb_prescaler;
    }
    /* Calculate PCLK1 frequency based on HSE and AHB prescaler (assuming no pre-division) */

    /* Set baud rate using the calculated PCLK1 frequency and desired baud rate */
    uint32_t baud_rate = 115200;  // Desired baud rate (adjustable)

    /* Adjust USART configuration for oversampling effect (if baud rate is below 3600) */
    /* Option 1: Increase baud rate and adjust USARTDIV for oversampling by 8 */
    USART_InitStructure.USART_BaudRate = baud_rate;  // Double the baud rate
    // Adjust USARTDIV for doubled baud rate

    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART_Init(UART7, &USART_InitStructure);
    USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);

    USART_Cmd(UART7, ENABLE);
}






void DelayTimerUs(int n){
	// 1 Mhz ---> 1Us
	//ARR = n (n=1 --> 1us) (n=2 --> 2us) ....
 
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = 36;
	TIM2->ARR = n;
	TIM2->CNT = 0;
	TIM2->CR1 = TIM_CR1_CEN;
	int i;
	for(i =0; i<n; i++){
		
		  while (!(TIM2->SR & (1<<0))) {}
		}
	TIM2->SR &=~ (1<<0);
		
	TIM2->CR1 &=~ TIM_CR1_CEN;
		
		
	}
void usartSendArrar(USART_TypeDef *USART, uint8_t *Arrar)
{
	uint16_t length, i;
	length = strlen((char *)Arrar);
		
	for(i=0; i<length; i++)
	{
		USART_ClearFlag(USART,USART_FLAG_TC);	//?????????????
		USART_SendData(USART, *Arrar);
		while(USART_GetFlagStatus(USART, USART_FLAG_TC) == RESET);
		Arrar++;
	}
	    *Arrar = NULL;

}

void configure_timer_delay(void) {
  // Enable timer clock for Timer 2
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  // Configure Timer 2 in Up-counting mode
  TIM_TimeBaseInitTypeDef tim_init_structure;
  TIM_TimeBaseStructInit(&tim_init_structure);
  tim_init_structure.TIM_Prescaler = SystemCoreClock / 1000 - 1; // Adjust for 1 kHz clock
  tim_init_structure.TIM_Period = 999; // Set period for 1ms delay (1kHz - 1 count)
  tim_init_structure.TIM_ClockDivision = TIM_CKD_DIV1;
  tim_init_structure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &tim_init_structure);

  // Enable Timer 2 update interrupt
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  // Enable NVIC interrupt for Timer 2
  NVIC_EnableIRQ(TIM2_IRQn);

  // Start the timer
  TIM_Cmd(TIM2, ENABLE);
}
volatile uint32_t timer_delay_flag = 0; // Flag to indicate delay completion

void TIM2_IRQHandler(void) {
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    timer_delay_flag = 1; // Set flag when delay complete (1 second in this case)
  }
}

void send_COMMANDE(char cmd[30]){
usartSendArrar(UART7,(uint8_t *)cmd);
	DelayTimerUs(1000);
	

}


uint8_t rx_len;

uint8_t USART_ReceiveDataa(USART_TypeDef* USARTx) {
  while (!(USARTx->SR & USART_SR_RXNE));  // Wait for receive data not empty flag
  return USARTx->DR;
}

void USART_SendDataa(USART_TypeDef* USARTx, uint8_t data) {
  while (!(USARTx->SR & USART_SR_TXE));  // Wait for transmit empty flag
  USARTx->DR = data;
}


volatile char received_data;
char test[50];
char vv[50];

int i =0;
	char recived_d[500];
void UART7_IRQHandler(void) {
    received_data = (char)USART_ReceiveData(UART7);
	
    // **Send received data on USART1**
  //  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // Wait for USART1 transmit buffer empty
   USART_SendData(USART1, (uint8_t)received_data);
		  recived_d[strlen(recived_d)]=received_data;
    USART_ClearITPendingBit(UART7, USART_IT_RXNE);
  
}


void wifi_connect(char ssid[20],char psswd[20]){
	char result[40];
	sprintf(result,"AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,psswd);
usartSendArrar(UART7,(uint8_t *)result);
		DelayTimerUs(1000);
}
void am_i_connected(){
usartSendArrar(UART7,(uint8_t *)"AT+CIFSR\r\n");
		DelayTimerUs(1000);

}
void list_wifi(){
send_COMMANDE("AT+CWLAP\r\n");
}

void send_data_to_server(char data[50],char *size_data){
	char rs1[500];
	sprintf(rs1,"AT+CIPSEND=1,%s\r\n",size_data);
	
send_COMMANDE("AT+CIPMUX=1\r\n");
send_COMMANDE("AT+CIPSERVER=1,80\r\n");
				usartSendArrar(USART1,(uint8_t *)"Waiting");
	while(1){
			while(strstr(recived_d,"+IPD") == NULL){
			
			usartSendArrar(USART1,(uint8_t *)".");
			DelayTimerUs(800);

			}
			      memset(recived_d,0,sizeof(recived_d));       
						DelayTimerUs(1000);
						send_COMMANDE(rs1);

      			while(strstr(recived_d,">") == NULL);

			   
				send_COMMANDE(data);
			  send_COMMANDE("AT+CIPCLOSE=1\r\n");


	memset(recived_d,0,sizeof(recived_d));
		}

}
void request_site(char site[20], char port[4],char methode[50],char path[20],char POST_DATA[500])
	{
		int i=0;
		char command[60];
		char data[300];
    sprintf(command, "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", site, port);
		send_COMMANDE(command);
		memset(command,0,sizeof(command));
		
		if(strcmp(methode,"GET") == 0){
		sprintf(data,"GET /%s HTTP/1.1\r\nHost: %s/\r\n\r\n",path,site);
			}
		if(strcmp(methode,"POST") == 0){
			sprintf(data, "POST %s HTTP/1.1\r\n", path);
    sprintf(command + strlen(data), "Host: %s\r\n", site);
    sprintf(data + strlen(data), "Content-Type: application/json,application/x-www-form-urlencoded\r\n");
    sprintf(data + strlen(data), "Content-Length: %d\r\n\r\n", strlen(data));
    sprintf(data + strlen(data), "%s", POST_DATA);
		
			}
		sprintf(command,"AT+CIPSEND=%d\r\n",strlen(data));
    send_COMMANDE(command);
		
while (i==0){
		if(strstr(recived_d,">") != NULL){
		       DelayTimerUs(1000);

      	send_COMMANDE(data);
	      DelayTimerUs(1000);
			send_COMMANDE("AT+CIPCLOSE\r\n");
		       DelayTimerUs(500);
	memset(recived_d,0,sizeof(recived_d));
			i++;
		}
	}
	}

