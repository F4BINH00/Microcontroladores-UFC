/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Fábio Filho e Dávylla Maria
 * @brief          : Prática 3 - SysTick e Máquina de Estados
 ******************************************************************************
 */

#include "stm32f1xx.h"

// macro pra setar a cor limpando os bits primeiro (anodo comum)
#define RGB_SET(cor) (GPIOA->ODR = (GPIOA->ODR & ~0x7) | ((~(cor)) & 0x7))

volatile uint32_t ms_count = 0;

void GPIO_INIT(void);
void SYSTICK_INIT(void);

int main(void) {
    GPIO_INIT();
    SYSTICK_INIT();

    uint8_t estado = 0;

    // mapeamento: apagado, verm, verde, azul, amar, ciano, roxo, branco
    const uint8_t cores[] = {0, 1, 2, 4, 3, 6, 5, 7};

    while (1) {
        // verifica se passou 1s sem travar a execucao
        if (ms_count >= 1000) {
            ms_count = 0;

            RGB_SET(cores[estado]);

            estado++;
            if (estado > 7) {
                estado = 0;
            }
        }
    }
}

void GPIO_INIT(void) {
    // habilita clock no GPIOA
    RCC->APB2ENR |= (1 << 2);

    // PA0 a PA2 como saida push-pull 2MHz
    GPIOA->CRL &= ~(0xFFF);
    GPIOA->CRL |= (0x222);

    // garante os leds apagados no inicio
    GPIOA->ODR |= 0x7;
}

void SYSTICK_INIT(void) {
    // config pra estourar a cada 1ms (clock de 8MHz)
    SysTick->LOAD = 8000 - 1;
    SysTick->VAL = 0;

    // liga clock, int e o contador
    SysTick->CTRL = 0x7;
}

void SysTick_Handler(void) {
    ms_count++;
}
