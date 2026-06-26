/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Fábio Filho e Dávylla Maria
 * @brief          : Prática 7
 ******************************************************************************
 */

#include "stm32f1xx.h"

volatile int demo_mode = 0;
volatile char rx_buffer[16];
volatile int rx_index = 0;

/* ================= GPIO ================= */
void Config_GPIO(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // PA0, PA1, PA2 -> TIM2 CH1/2/3 (AF PP)
    GPIOA->CRL &= ~(0xFFF);

    GPIOA->CRL |=
        (0xB << 0) |   // PA0
        (0xB << 4) |   // PA1
        (0xB << 8);    // PA2

    // PA9 TX / PA10 RX
    GPIOA->CRH &= ~(0xFFF);
    GPIOA->CRH |= 0x4B0;

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |=  (0x2 << 20); // output push-pull 2MHz

    GPIOC->ODR |= GPIO_ODR_ODR13;
}

/* ================= USART ================= */
void Config_USART1(void) {
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // AJUSTE PARA CLOCK 8MHz (modo mais comum sem PLL)
    // 8MHz / 9600 ≈ 833
    USART1->BRR = 0x0341;

    USART1->CR1 |= USART_CR1_UE |
                   USART_CR1_TE |
                   USART_CR1_RE |
                   USART_CR1_RXNEIE;

    NVIC_EnableIRQ(USART1_IRQn);
}

/* ================= TIM2 PWM ================= */
void Config_TIM2_PWM(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->PSC = 79;   // 8MHz / 80 = 100kHz
    TIM2->ARR = 99;   // 100 níveis de PWM

    TIM2->CCMR1 &= ~((7 << 4) | (7 << 12));
    TIM2->CCMR2 &= ~(7 << 4);

    TIM2->CCMR1 |= (6 << 4) | (6 << 12);
    TIM2->CCMR2 |= (6 << 4);

    TIM2->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE;
    TIM2->CCMR2 |= TIM_CCMR2_OC3PE;

    TIM2->CR1 |= TIM_CR1_ARPE;

    TIM2->CCER |= TIM_CCER_CC1E |
                  TIM_CCER_CC2E |
                  TIM_CCER_CC3E;

    TIM2->CCR1 = 100;
    TIM2->CCR2 = 100;
    TIM2->CCR3 = 100;

    TIM2->CR1 |= TIM_CR1_CEN;
}

/* ================= TIM3 DEMO ================= */
void Config_TIM3_Base(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    TIM3->PSC = 799;  // mais lento e visível
    TIM3->ARR = 999;

    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1 |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM3_IRQn);
}

/* ================= PROCESSA COMANDO ================= */
void Processa_Comando(void) {
    char cmd = rx_buffer[0];

    if (cmd == 'd' || cmd == 'D') {
        demo_mode = !demo_mode;

        if (!demo_mode) {
            TIM2->CCR1 = 100;
            TIM2->CCR2 = 100;
            TIM2->CCR3 = 100;
        }
        return;
    }

    if (demo_mode) return;

    if (rx_index >= 3) {
        int dezena = rx_buffer[1] - '0';
        int unidade = rx_buffer[2] - '0';

        if (dezena >= 0 && dezena <= 9 &&
            unidade >= 0 && unidade <= 9) {

            int valor = dezena * 10 + unidade;
            if (valor > 99) valor = 99;

            int pwm = 100 - valor;

            if (cmd == 'r' || cmd == 'R') {
                TIM2->CCR1 = pwm;
            } else if (cmd == 'g' || cmd == 'G') {
                TIM2->CCR2 = pwm;
            } else if (cmd == 'b' || cmd == 'B') {
                TIM2->CCR3 = pwm;
            }
        }
    }
}

/* ================= UART IRQ ================= */
void USART1_IRQHandler(void) {
    if (USART1->SR & USART_SR_RXNE) {
        char c = USART1->DR;

        if (c == '\n' || c == '\r') {

            GPIOC->ODR &= ~GPIO_ODR_ODR13;
            for(volatile int i = 0; i < 50000; i++);
            GPIOC->ODR |= GPIO_ODR_ODR13;

            if (rx_index > 0) {
                rx_buffer[rx_index] = '\0';
                Processa_Comando();
                rx_index = 0;
            }
        } else {
            if (rx_index < sizeof(rx_buffer) - 1) {
                rx_buffer[rx_index++] = c;
            } else {
                rx_index = 0;
            }
        }
    }
}

/* ================= TIM3 IRQ ================= */
void TIM3_IRQHandler(void) {
    if (TIM3->SR & TIM_SR_UIF) {
        TIM3->SR &= ~TIM_SR_UIF;

        static int estado = 0;
        static int brilho = 0;
        static int dir = 1;

        //GPIOC->ODR ^= GPIO_ODR_ODR13;

        if (!demo_mode) return;

        brilho += dir;

        if (brilho >= 100) {
            dir = -1;
        } else if (brilho <= 0) {
            dir = 1;
            estado++;
            if (estado > 6) estado = 0;
        }

        switch (estado) {
            case 0:
                TIM2->CCR1 = 100 - brilho; TIM2->CCR2 = 100; TIM2->CCR3 = 100;
                break;
            case 1:
                TIM2->CCR1 = 100; TIM2->CCR2 = 100 - brilho; TIM2->CCR3 = 100;
                break;
            case 2:
                TIM2->CCR1 = 100; TIM2->CCR2 = 100; TIM2->CCR3 = 100 - brilho;
                break;
            case 3:
                TIM2->CCR1 = 100 - brilho; TIM2->CCR2 = 100 - brilho; TIM2->CCR3 = 100;
                break;
            case 4:
                TIM2->CCR1 = 100; TIM2->CCR2 = 100 - brilho; TIM2->CCR3 = 100 - brilho;
                break;
            case 5:
                TIM2->CCR1 = 100 - brilho; TIM2->CCR2 = 100; TIM2->CCR3 = 100 - brilho;
                break;
            case 6:
                TIM2->CCR1 = 100 - brilho;
                TIM2->CCR2 = 100 - brilho;
                TIM2->CCR3 = 100 - brilho;
                break;
        }
    }
}

/* ================= MAIN ================= */
int main(void) {
    Config_GPIO();
    Config_TIM2_PWM();
    Config_TIM3_Base();
    Config_USART1();

    while (1) {
    }
}
