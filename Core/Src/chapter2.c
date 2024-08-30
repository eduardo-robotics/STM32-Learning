
#include "chapter2.h"

// Creates delay on 16 MHz SYSCLK
void delayMs(int n) {
  int i;
  for (; n> 0; n--)
    for (i = 0; i < 3195; i++)
    // Needs this or else compiler will try   
    // to optimize and remove an empty for loop
      __NOP(); 
}

// Blinks user LED on board connected to PA5
void LED_Blink(void) {
  RCC->AHB1ENR |= 1; // Enables clock for GPIOA
  GPIOA->MODER |= 1<<10; // Sets PA5 as output

  while(1) {
    GPIOA->ODR |= 1<<5; // Sets PA5 to HIGH
    delayMs(1000);
    GPIOA->ODR &= ~(1<<5); // Sets PA5 to LOW
    delayMs(1000);
  }
}

// LED Blink with BSRR registers
void LED_Blink_BSRR(void) {
  RCC->AHB1ENR |= 1; // Enables clock for GPIOA
  GPIOA->MODER |= 1<<10; // Sets PA5 as output

  while(1) {
    // We don't use | because we don't want to leave the 
    // other bits as is, we want to reset them to 0
    GPIOA->BSRR = 1<<5; // Sets PA5 to HIGH
    delayMs(1000);
    GPIOA->BSRR = 1<<21; // Sets PA5 to LOW
    delayMs(1000);
  }
}

// Reads a switch and turns on LED
void Switch_Read_With_LED(void) {
  RCC->AHB1ENR |= 1 | (1<<2); // Enables clock for GPIOA & GPIOC
  GPIOA->MODER |= 1<<10; // Sets PA5 as output
  GPIOC->MODER &= ~(1<<27 | 1<<26); // Sets PC13 as input

  while(1) {
    if(GPIOC->IDR & (1<<13)) // Reads PC13, If PC13 is HIGH
      GPIOA->ODR &= ~(1<<5); // Sets PA5 to LOW
    else
      GPIOA->ODR |= 1<<5; // Sets PA5 to HIGH
  }
}