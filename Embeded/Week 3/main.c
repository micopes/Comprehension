#include "stm32f10x.h"
#include <time.h>

#define RCC_APB2_CLK *(volatile unsigned int *)0x40021018 // Clock
#define GPIOD_CRL *(volatile unsigned int *)0x40011400    // Port D
#define GPIOD_BSRR *(volatile unsigned int *)0x40011410
#define GPIOD_BRR *(volatile unsigned int *)0x40011414
#define GPIOC_CRL *(volatile unsigned int *)0x40011000 // Port C
#define GPIOC_IDR *(volatile unsigned int *)0x40011008
enum Direction
{
  DOWN = 1,
  LEFT,
  RIGHT,
  UP
};

int main()
{
  RCC_APB2_CLK |= 0x30;

  // 초기화 코드 - 기본적으로 Reset되므로 주석 처리
  // GPIOD_CRL = 0x44444444; // GPIOD reset
  // GPIOC_CRL = 0x44444444; // GPIOC reset
  // GPIOD_BSRR = 0x00000000; // bit reset

  GPIOD_CRL = 0x10011100; // LED pin setting to use

  int i = 0;
  GPIOD_BRR |= 0x9C;

  while (1)
  {
    i = 0;
    if (~GPIOC_IDR & 0x4)
      i = DOWN;
    if (~GPIOC_IDR & 0x8)
      i = LEFT;
    if (~GPIOC_IDR & 0x10)
      i = RIGHT;
    if (~GPIOC_IDR & 0x30)
      i = UP;

    switch (i)
    {
    case DOWN:
      GPIOD_BSRR |= 0xC;
      break;

    case LEFT:
      GPIOD_BRR |= 0x90;
      break;

    case RIGHT:
      GPIOD_BRR |= 0xC;
      break;

    case UP:
      GPIOD_BSRR |= 0x90;
      break;
    }
  }
}
