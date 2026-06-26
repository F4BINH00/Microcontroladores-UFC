/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Fábio Filho e Dávylla Maria
 * @brief          : Prática 6 - Controle RGB com 3 ADCs via DMA e PWM
 ******************************************************************************
 */
#include "stm32f1xx.h"

volatile uint16_t adc_values[3];

void CONFIG_CLOCKS(void);
void CONFIG_GPIO(void);
void CONFIG_DMA(void);
void CONFIG_ADC(void);
void CONFIG_TIM2_PWM(void);
void DELAY_US(uint32_t us);

int main(void) {
    CONFIG_CLOCKS();
    CONFIG_GPIO();
    CONFIG_DMA();
    CONFIG_ADC();
    CONFIG_TIM2_PWM();

    while (1) {
        // Inversao via software para Anodo Comum
        TIM2->CCR1 = 4095 - adc_values[0]; // vermelho (PA0, lido do PA3)
        TIM2->CCR2 = 4095 - adc_values[1]; // verde    (PA1, lido do PA4)
        TIM2->CCR3 = 4095 - adc_values[2]; // azul     (PA2, lido do PA5)
    }
}

void CONFIG_CLOCKS(void) {
    // Configura prescaler do ADC para PCLK2/6 (Max 14MHz, usando 12MHz)
    RCC->CFGR &= ~(3 << 14);
    RCC->CFGR |=  (2 << 14);

    // gpioa, adc1, tim2 e dma1
    RCC->APB2ENR |= (1 << 2) | (1 << 9);
    RCC->APB1ENR |= (1 << 0);
    RCC->AHBENR  |= (1 << 0);
}

void CONFIG_GPIO(void) {
    // zera config do PA0 ate PA5
    GPIOA->CRL &= ~(0xFFFFFF);

    // PA0, PA1, PA2 como alternate function push-pull 2MHz (PWM) -> 0xA
    // PA3, PA4, PA5 ficam como analog input (0x0)
    GPIOA->CRL |= 0x000AAA;
}

void CONFIG_DMA(void) {
    // endereco do periferico (origem) e memoria (destino)
    DMA1_Channel1->CPAR = (uint32_t)&(ADC1->DR);
    DMA1_Channel1->CMAR = (uint32_t)adc_values;

    // 3 conversoes por ciclo
    DMA1_Channel1->CNDTR = 3;

    // mem size 16 bits, periph size 16 bits, mem inc, circ mode, enable
    DMA1_Channel1->CCR |= (1 << 7) | (1 << 10) | (1 << 8) | (1 << 5) | (1 << 0);
}

void CONFIG_ADC(void) {
    ADC1->CR2 |= (1 << 0); // ADC ON

    // Aguarda o tSTAB usando o SysTick (sem loop for)
    DELAY_US(2);

    // Sequencia de Calibracao
    ADC1->CR2 |= (1 << 3); // RSTCAL
    while(ADC1->CR2 & (1 << 3));

    ADC1->CR2 |= (1 << 2); // CAL
    while(ADC1->CR2 & (1 << 2));

    ADC1->CR1 |= (1 << 8); // SCAN mode

    // CONT, DMA, EXTTRIG enable, EXTSEL = 111 (SWSTART)
    ADC1->CR2 |= (1 << 1) | (1 << 8) | (1 << 20) | (7 << 17);

    ADC1->SQR1 = (2 << 20); // 3 conversoes
    ADC1->SQR3 = (3 << 0) | (4 << 5) | (5 << 10); // ch3(PA3), ch4(PA4), ch5(PA5)

    // Sample time (7 = 239.5 cycles) para maior estabilidade
    ADC1->SMPR2 = (7 << 9) | (7 << 12) | (7 << 15);

    ADC1->CR2 |= (1 << 22); // SWSTART
}

void CONFIG_TIM2_PWM(void) {
    TIM2->PSC = 0;
    TIM2->ARR = 4095; // alinha com resolucao 12 bits do adc

    // pwm mode 1 e preload (CH1 a CH3)
    TIM2->CCMR1 |= (6 << 4) | (1 << 3) | (6 << 12) | (1 << 11);
    TIM2->CCMR2 |= (6 << 4) | (1 << 3);

    // enable dos canais (polaridade padrao, ativa em HIGH)
    TIM2->CCER |= (1 << 0) | (1 << 4) | (1 << 8);

    TIM2->EGR |= (1 << 0); // force update

    // auto-reload e enable
    TIM2->CR1 |= (1 << 7) | (1 << 0);
}

void DELAY_US(uint32_t us) {
    // Configura o timer SysTick para gerar atraso em microssegundos
    SysTick->LOAD = (8 * us) - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = 5;

    while (!(SysTick->CTRL & (1 << 16)));

    SysTick->CTRL = 0;
}
