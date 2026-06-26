/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Fábio Filho e Dávylla Maria
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include "stm32f1xx.h"

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

int main(void) {
    /* 1. HABILITAR CLOCKS */
    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN);

    /* 2. CONFIGURAR LEDS (PA0, PA1, PA2) - SAÍDA 2MHz PUSH-PULL */
    GPIOA->CRL &= ~(0x00000FFF);
    GPIOA->CRL |=  (0x00000222);

    /* 3. CONFIGURAR BOTÕES (PB0, PB1, PB10) - ENTRADA PULL-UP */
    GPIOB->CRL &= ~(0x000000FF);
    GPIOB->CRL |=  (0x00000088);

    GPIOB->CRH &= ~(0x00000F00);
    GPIOB->CRH |=  (0x00000800);

    GPIOB->ODR |= (GPIO_ODR_ODR0 | GPIO_ODR_ODR1 | GPIO_ODR_ODR10);

    /* 4. CONFIGURAR AFIO (Mapear os pinos do PORT B para o EXTI) */
    AFIO->EXTICR[0] |= (AFIO_EXTICR1_EXTI0_PB | AFIO_EXTICR1_EXTI1_PB);
    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI10_PB;

    /* 5. CONFIGURAR EXTI (Trigger e Máscara) */
    EXTI->FTSR |= (EXTI_FTSR_TR0 | EXTI_FTSR_TR1 | EXTI_FTSR_TR10);
    EXTI->IMR  |= (EXTI_IMR_MR0 | EXTI_IMR_MR1 | EXTI_IMR_MR10);

    /* 6. HABILITAR NO NVIC (Controlador de Interrupções do Núcleo) */
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    while (1) {
    }
}

/* --- FUNÇÕES DE TRATAMENTO DE INTERRUPÇÃO (HANDLERS) --- */

// Função chamada quando o Botão 1 (PB0) é pressionado
void EXTI0_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR0) {    // Verifica se a flag do pino 0 está ativa
        GPIOA->ODR ^= GPIO_ODR_ODR0; // XOR no LED 1 (PA0): Liga se desligado / Desliga se ligado
        EXTI->PR |= EXTI_PR_PR0;     // LIMPA A FLAG (Crucial para não travar o código)
    }
}

// Função chamada quando o Botão 2 (PB1) é pressionado
void EXTI1_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR1) {
        GPIOA->ODR ^= GPIO_ODR_ODR1; // XOR no LED 2 (PA1)
        EXTI->PR |= EXTI_PR_PR1;     // Limpa a flag
    }
}

// Função chamada quando o Botão 3 (PB10) é pressionado
void EXTI15_10_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR10) {   // Verifica especificamente o pino 10
        GPIOA->ODR ^= GPIO_ODR_ODR2; // XOR no LED 3 (PA2)
        EXTI->PR |= EXTI_PR_PR10;    // Limpa a flag
    }
}
