/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Fábio Filho e Dávylla Maria
 * @brief          : Prática 4 - Acionamento Sequencial com Interrupção de Hardware
 ******************************************************************************
 */
#include "stm32f1xx.h"

// macros pra simplificar o led e evitar funcao (anodo comum)
#define RGB_SET(cor) (GPIOA->ODR = (GPIOA->ODR | 0x7) & ~(cor))
#define RGB_OFF()    (GPIOA->ODR |= 0x7)

void GPIO_INIT(void);
void TIM2_INIT(void);

// sequencia: Vermelho, Verde, Azul, Amarelo, Ciano, Roxo, Branco (PA0=R, PA1=G, PA2=B)
const uint8_t sequencia[] = {0x1, 0x2, 0x4, 0x3, 0x6, 0x5, 0x7};
volatile uint8_t indice = 0;
volatile uint8_t contador_passos = 0;

int main(void) {
    GPIO_INIT();
    TIM2_INIT();

    while (1) {
    }
}

void GPIO_INIT(void) {
    // clock no porta
    RCC->APB2ENR |= (1 << 2);

    // pinos PA0 a PA2 como saida push-pull 2MHz
    GPIOA->CRL &= ~(0xFFF);
    GPIOA->CRL |= (0x222);

    // inicia apagado
    RGB_OFF();
}

void TIM2_INIT(void) {
    // clock no tim2
    RCC->APB1ENR |= (1 << 0);

    // prescaler e arr (se o clock for 8MHz, muda o PSC pra 7999 pra dar 1s certinho)
    TIM2->PSC = 71999;
    TIM2->ARR = 999;

    // habilita interrupcao de update e liga o timer
    TIM2->DIER |= (1 << 0);
    NVIC_EnableIRQ(TIM2_IRQn);
    TIM2->CR1 |= (1 << 0);
}

void TIM2_IRQHandler(void) {
    // checa se a flag de update foi setada
    if (TIM2->SR & (1 << 0)) {
        // limpa a flag pra nao ficar preso na interrupcao
        TIM2->SR &= ~(1 << 0);

        // passos 0 e 2 liga, passos 1 e 3 apaga
        if (contador_passos == 0 || contador_passos == 2) {
            RGB_SET(sequencia[indice]);
        } else {
            RGB_OFF();
        }

        contador_passos++;

        // fechou 4 passos (piscou 2x), reseta contador e troca a cor
        if (contador_passos >= 4) {
            contador_passos = 0;
            indice++;
            if (indice >= 7) {
                indice = 0;
            }
        }
    }
}
