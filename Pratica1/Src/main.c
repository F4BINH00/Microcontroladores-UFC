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

int main(void) {
    /* 1. HABILITAR CLOCK */
    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN);

    /* 2. CONFIGURAR LEDS (PA0, PA1, PA2) como SAÍDA */
    GPIOA->CRL &= ~(0x00000FFF);
    GPIOA->CRL |=  (0x00000222);

    /* 3. CONFIGURAR BOTÕES (PB0, PB1, PB10) como ENTRADA PULL-UP */
    GPIOB->CRL &= ~(0x000000FF);
    GPIOB->CRL |=  (0x00000088);

    GPIOB->CRH &= ~(0x00000F00);
    GPIOB->CRH |=  (0x00000800);

    /* 4. ATIVAR O RESISTOR DE PULL-UP */
    GPIOB->ODR |= (GPIO_ODR_ODR0 | GPIO_ODR_ODR1 | GPIO_ODR_ODR10);

    while (1) {
        /* LÓGICA DE POLLING */
        // Se o bit no IDR for 0, significa que o botão foi pressionado (ligado ao GND)

    	// Botão 1 (PB0) controla LED 1 (PA0)
        if (!(GPIOB->IDR & GPIO_IDR_IDR0))
            GPIOA->BSRR = GPIO_BSRR_BS0; // Liga LED
        else
            GPIOA->BSRR = GPIO_BSRR_BR0; // Desliga LED

        // Botão 2 (PB1) controla LED 2 (PA1)
        if (!(GPIOB->IDR & GPIO_IDR_IDR1))
            GPIOA->BSRR = GPIO_BSRR_BS1;
        else
            GPIOA->BSRR = GPIO_BSRR_BR1;

        // Botão 3 (PB10) controla LED 3 (PA2)
        if (!(GPIOB->IDR & GPIO_IDR_IDR10))
            GPIOA->BSRR = GPIO_BSRR_BS2;
        else
            GPIOA->BSRR = GPIO_BSRR_BR2;
    }
}
