#include "stm32f10x.h"
#include <time.h>

#define RCC_APB2_CLK *(volatile unsigned int *)0x40021018 // Clock

// Port D
#define GPIOD_CRH *(volatile unsigned int *)0x40011404
#define GPIOD_IDR *(volatile unsigned int *)0x40011408

// Port C
#define GPIOC_CRH *(volatile unsigned int *)0x40011004
#define GPIOC_BSRR *(volatile unsigned int *)0x40011010
#define GPIOC_BRR *(volatile unsigned int *)0x40011014

#define GPIOB_CRH *(volatile unsigned int *)0x40010C04
#define GPIOB_IDR *(volatile unsigned int *)0x40010C08

void delay(){
  for(int i = 0; i < 10000000; ++i);
}

int main()
{
  RCC_APB2_CLK = 0x38;

  GPIOC_BSRR = 0x00000300 ;// bit reset 
  GPIOC_CRH = 0x33;
  GPIOD_CRH = 0x88444;
  GPIOB_CRH = 0x8;

  
  while (1)
  {
    if ((GPIOD_IDR & 0x800)==0){ // S1 버튼 /  pc8 좌측 모터
      GPIOC_BRR |= 0x100;
      delay();
    }
    else if ((GPIOD_IDR & 0x1000)==0){ // S2 버튼 / pc9 우측 모터
      GPIOC_BRR |= 0x200;
       delay();
    }
    else if ((GPIOB_IDR & 0x100)==0){ // 조이스틱 가운데 버튼 /  pc8, pc9 양측 모터
      GPIOC_BRR |= 0x300;
      delay();
    }
    GPIOC_BSRR |= 0x300; // 모터 정지
  }
}
