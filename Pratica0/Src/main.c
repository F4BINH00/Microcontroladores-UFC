/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Fábio Filho e Dávylla Maria
 * @brief          : Prática 0 - Redução de consumo com instrução WFI
 ******************************************************************************
 */
#include "stm32f1xx.h"

volatile uint32_t ms_count = 0;

void CONFIG_CLOCK_LOW_POWER(void);
void CONFIG_GPIO(void);
void CONFIG_SYSTICK(void);

int main(void) {
    CONFIG_CLOCK_LOW_POWER();
    CONFIG_GPIO();
    CONFIG_SYSTICK();

    uint8_t estado = 0;
    uint32_t tempo_referencia = 0; // guarda a marca de tempo

    while (1) {
        if (estado == 0) {
            // verifica a diferenca para evitar drift e problemas de rollover
            if ((ms_count - tempo_referencia) >= 500) {
                tempo_referencia = ms_count; // atualiza a referencia sem zerar o global
                GPIOC->BSRR = (1 << 13); // desliga led
                estado = 1;
            }
        } else {
            if ((ms_count - tempo_referencia) >= 800) {
                tempo_referencia = ms_count; // atualiza a referencia
                GPIOC->BSRR = (1 << 29); // liga led
                estado = 0;
            }
        }

        // cpu dorme e acorda no proximo systick
        __WFI();
    }
}

void CONFIG_CLOCK_LOW_POWER(void) {
    RCC->CR |= (1 << 0);
    while(!(RCC->CR & (1 << 1)));

    RCC->CFGR &= ~(3 << 0);
    // desliga hse e pll pra economizar energia (bits 16 e 24)
    RCC->CR &= ~((1 << 16) | (1 << 24));
}

void CONFIG_GPIO(void) {
    RCC->APB2ENR |= (1 << 4); // clock no gpioc
    // pc13 como saida push-pull 2mhz
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |= (2 << 20);
    // inicia com led ligado (pc13 = 0)
    GPIOC->BSRR = (1 << 29);
}

void CONFIG_SYSTICK(void) {
    SysTick->LOAD = 8000 - 1; // 1ms no clock de 8mhz
    SysTick->VAL = 0;
    SysTick->CTRL = 0x7;
}

void SysTick_Handler(void) {
    ms_count++;
}
