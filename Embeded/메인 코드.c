#include "stm32f10x.h"
#include "core_cm3.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_tim.h"
#include "stdio.h"
#include "lcd.h"
#include "touch.h"

void RCC_Configure(void);
void GPIO_Configure(void);
void USART2_Init(void);
void ADC_Configure(void);
void NVIC_Configure(void);
void EXTI_Configure(void);
void USART2_IRQHandler();
void EXTI15_10_IRQHandler(void);
void ADC1_2_IRQHandler(void);
void DMA_Configure(void);
void Tim_Configure(void);
void TIM2_IRQHandler(void);
void Delay(void);
void checkOpen();
void checkPill();
void checkCommand();

const static int ALERT_PIN[2] = {GPIO_Pin_15, GPIO_Pin_8};
const static int STANDARD_OPEN = 3300;
const static int STANDARD_DETECT = 2900;

volatile uint32_t ADC_values[6]; // UV distance sensor values
volatile uint32_t alarm = 0;     // command - alarm flag
volatile uint32_t find = 0;      // command - find flag
volatile uint32_t isOpen = 0;    // status - open flag

int color[12] = {WHITE, CYAN, BLUE, RED, MAGENTA, LGRAY, GREEN, YELLOW, BROWN, BRRED, GRAY};
int LED_PIN[11] = {GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3, GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7, GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14};
uint16_t value; // Ÿ�̸ӿ� ���� ��(s) ǥ��

//---------------------------------------------------------------------------------------------------

void RCC_Configure(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //  modified
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Configure(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // ADC (light sensor / magnetic sensor / distance sensor)
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  // LED INNER(14) AND OUTER(1-13)
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  // BLUETOOTH
  // TX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // RX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  //  Button(Touch sensor)
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  //  alert / PIEZO
  GPIO_InitStructure.GPIO_Pin = ALERT_PIN[0];
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  //  alert / vibe motor
  GPIO_InitStructure.GPIO_Pin = ALERT_PIN[1];
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void USART2_Init(void)
{
  USART_InitTypeDef USART2_InitStructure;
  USART_Cmd(USART2, ENABLE);
  USART2_InitStructure.USART_BaudRate = 9600;
  USART2_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART2_InitStructure.USART_StopBits = USART_StopBits_1;
  USART2_InitStructure.USART_Parity = USART_Parity_No;
  USART2_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART2_InitStructure.USART_HardwareFlowControl =
      USART_HardwareFlowControl_None;
  USART_Init(USART2, &USART2_InitStructure);
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  USART_ClockInitTypeDef USART_ClockInitStructure;
  USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
  USART_ClockInit(USART2, &USART_ClockInitStructure);
  
}

void ADC_Configure(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_NbrOfChannel = 6;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;

  ADC_Init(ADC1, &ADC_InitStructure);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_41Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 2, ADC_SampleTime_41Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 3, ADC_SampleTime_41Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 4, ADC_SampleTime_41Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 5, ADC_SampleTime_41Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_41Cycles5);

  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
  ADC_Cmd(ADC1, ENABLE);
  ADC_DMACmd(ADC1, ENABLE);

  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1) != RESET)
    ;
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1) != RESET)
    ;
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void NVIC_Configure(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_Init(&NVIC_InitStructure);

  // DMA (ADC PROCESS)
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // BLUETOOTH UART2
  NVIC_EnableIRQ(USART2_IRQn);
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_Init(&NVIC_InitStructure);
  NVIC_EnableIRQ(ADC1_2_IRQn);
  NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // Timer
  NVIC_EnableIRQ(TIM2_IRQn);
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /*
    NVIC_EnableIRQ(TIM1_IRQn);
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
*/

  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // TODO
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        // TODO
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void EXTI_Configure(void)
{

  EXTI_InitTypeDef EXTI_InitStructure;

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource11);
  EXTI_InitStructure.EXTI_Line = EXTI_Line11;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

void USART2_IRQHandler()
{
  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
    //word = USART_ReceiveData(USART2);
    if (alarm)
      {
        alarm = 0;
        value = 0;
      }
      else
        value = 20;
    USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
}

void EXTI15_10_IRQHandler(void)
{ // when the button is pressed
  if (EXTI_GetITStatus(EXTI_Line11) != RESET)
  {
    if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11) == Bit_RESET)
    {
      if (alarm)
      {
        alarm = 0;
        value = 0;
      }
      else
        value = 20;
    }
    EXTI_ClearITPendingBit(EXTI_Line11);
  }
}


void ADC1_2_IRQHandler(void) {
  if (ADC_GetITStatus(ADC1, ADC_IT_EOC) != RESET) {
    // CHANGE TO ADC
  }
  ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
}

void DMA_Configure(void)
{
  // USE DMA FOR ADC
  DMA_InitTypeDef DMA_InitStructure;
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_values;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 6;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; // 32bit
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;         // 32bit
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  // Enable DMA1 Channel1
  DMA_Cmd(DMA1_Channel1, ENABLE);
}

void Tim_Configure(void)
{
  TIM_TimeBaseInitTypeDef tim;
  tim.TIM_Period = 10000;
  tim.TIM_Prescaler = 7200;
  tim.TIM_ClockDivision = TIM_CKD_DIV1;
  tim.TIM_CounterMode = TIM_CounterMode_Up;
  tim.TIM_RepetitionCounter = 0x0000;
  //  PIEZO
  TIM_TimeBaseInit(TIM1, &tim);
  TIM_Cmd(TIM1, ENABLE);
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
  //  TIMER
  TIM_TimeBaseInit(TIM2, &tim);
  TIM_Cmd(TIM2, ENABLE);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void TIM2_IRQHandler(void)
{
  // TIMER
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    value--;
  }
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void Delay(void)
{
  int i;

  for (i = 0; i < 1000000; i++)
  {
  }
}

void checkOpen()
{
  if (isOpen)
  {
    alarm = 0;
    value = 0;
  }
}

void checkPill()
{
  isOpen = ADC_values[0] > STANDARD_OPEN;
  int isEmpty = 5;
  for (int i = 1; i < 6; i++)
  {
    int j = (i - 1) * 2;
    if (ADC_values[i] > STANDARD_DETECT)
    {
      if (j == 0) GPIO_SetBits(GPIOE, LED_PIN[j]);
      else GPIO_SetBits(GPIOD, LED_PIN[j]);
      GPIO_ResetBits(GPIOD, LED_PIN[j + 1]);
      isEmpty--;
    }
    else
    {
      if (j == 0) GPIO_ResetBits(GPIOE, LED_PIN[j]);
      else GPIO_ResetBits(GPIOD, LED_PIN[j]);
      
      GPIO_SetBits(GPIOD, LED_PIN[j + 1]);
    }
  }

  if (isEmpty==0)
  {
    char word[] = "Lacking pill!\r\n";
    for (int j = 0; j <= 15; j++)
    {
      USART_SendData(USART2, word[j]);
      while ((USART2->SR & USART_SR_TC) == 0)
        ;
    }
  }
  GPIO_SetBits(GPIOD, LED_PIN[10]);
}

void checkCommand()
{
  if (find)
  {
    find = 0;
    alarm = 1;
  }
  if (alarm)
  {
    char word[] = "Alert!!\r\n";
    for (int j = 0; j <= 8; j++)
    {
      USART_SendData(USART2, word[j]);
      while ((USART2->SR & USART_SR_TC) == 0)
        ;
    }
    GPIO_SetBits(GPIOD, ALERT_PIN[0]);
    GPIO_SetBits(GPIOA, ALERT_PIN[1]);
  }
  else
  {
    GPIO_ResetBits(GPIOD, ALERT_PIN[0]);
    GPIO_ResetBits(GPIOA, ALERT_PIN[1]);
  }
}

int main(void)
{
  SystemInit();
  RCC_Configure();
  GPIO_Configure();
  USART2_Init();
  NVIC_Configure();
  EXTI_Configure();
  DMA_Configure();
  ADC_Configure();
  Tim_Configure();
  // LCD FOR DEBUG
  LCD_Init();
  LCD_Clear(WHITE);

  while (1)
  {
    checkOpen();
    checkPill();
    checkCommand();
/* // DEBUG CODE
    LCD_ShowNum(44, 60, ADC_values[0], 5, color[1], color[2]);
    LCD_ShowNum(44, 80, ADC_values[1], 5, color[1], color[2]);
    LCD_ShowNum(44, 100, ADC_values[2], 5, color[1], color[2]);
    LCD_ShowNum(44, 120, ADC_values[3], 5, color[1], color[2]);
    LCD_ShowNum(44, 140, ADC_values[4], 5, color[1], color[2]);
    LCD_ShowNum(44, 160, ADC_values[5], 5, color[1], color[2]);
    LCD_ShowNum(44, 200, value, 5, color[1], color[2]);
*/
    if (value < 10 && value > 0)
    {
      alarm = 1;
    } else {
      alarm = 0;
    } 
  }

  return 0;
}