/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Fábio Filho e Dávylla Maria
 * @brief          : MAX30102 - Fase 3: Leitura Bruta (Vermelho e Infravermelho)
 ******************************************************************************
 */

#include "stm32f1xx.h"

#define MAX30102_ADDR_W 0xAE
#define MAX30102_ADDR_R 0xAF
#define REG_MODE_CONFIG 0x09
#define REG_SPO2_CONFIG 0x0A
#define REG_LED1_PA     0x0C
#define REG_LED2_PA     0x0D
#define REG_FIFO_DATA   0x07 // A gaveta com os dados do sangue!

// Variáveis GLOBAIS para podermos ver no Debugger
volatile uint32_t valor_vermelho = 0;
volatile uint32_t valor_infravermelho = 0;

void Config_I2C1(void) {
    RCC->APB2ENR |= (1 << 3);
    RCC->APB1ENR |= (1 << 21);

    GPIOB->CRL &= ~(0xFF000000);
    GPIOB->CRL |= (0xFF000000);

    I2C1->CR1 |= (1 << 15);
    I2C1->CR1 &= ~(1 << 15);
    I2C1->CR2 = 8;
    I2C1->CCR = 40;
    I2C1->TRISE = 9;

    I2C1->CR1 |= (1 << 0);
    I2C1->CR1 |= (1 << 10);
}

void I2C_Write_Reg(uint8_t reg_addr, uint8_t data) {
    int timeout;
    I2C1->CR1 |= (1 << 8);
    timeout = 10000; while(!(I2C1->SR1 & (1 << 0))) if(--timeout==0) return;
    I2C1->DR = MAX30102_ADDR_W;
    timeout = 10000; while(!(I2C1->SR1 & (1 << 1))) if(--timeout==0) return;
    (void)I2C1->SR1; (void)I2C1->SR2;
    I2C1->DR = reg_addr;
    timeout = 10000; while(!(I2C1->SR1 & (1 << 7))) if(--timeout==0) return;
    I2C1->DR = data;
    timeout = 10000; while(!(I2C1->SR1 & (1 << 2))) if(--timeout==0) return;
    I2C1->CR1 |= (1 << 9);
}

// --- NOVA FUNÇÃO: LER VÁRIOS BYTES SEGUIDOS ---
void I2C_Read_Buffer(uint8_t reg_addr, uint8_t *buffer, uint8_t size) {
    int timeout;

    // START e Endereço de Escrita
    I2C1->CR1 |= (1 << 8);
    timeout = 10000; while(!(I2C1->SR1 & (1 << 0))) if(--timeout==0) return;
    I2C1->DR = MAX30102_ADDR_W;
    timeout = 10000; while(!(I2C1->SR1 & (1 << 1))) if(--timeout==0) return;
    (void)I2C1->SR1; (void)I2C1->SR2;

    // Pede a Gaveta da FIFO (0x07)
    I2C1->DR = reg_addr;
    timeout = 10000; while(!(I2C1->SR1 & (1 << 2))) if(--timeout==0) return;

    // RE-START e Endereço de Leitura
    I2C1->CR1 |= (1 << 8);
    timeout = 10000; while(!(I2C1->SR1 & (1 << 0))) if(--timeout==0) return;
    I2C1->DR = MAX30102_ADDR_R;
    timeout = 10000; while(!(I2C1->SR1 & (1 << 1))) if(--timeout==0) return;
    (void)I2C1->SR1; (void)I2C1->SR2;

    // Puxa os dados um a um
    for(uint8_t i = 0; i < size; i++) {
        if (i == size - 1) { // Se for o último byte, avisa o sensor para parar
            I2C1->CR1 &= ~(1 << 10); // Desliga ACK
            I2C1->CR1 |= (1 << 9);   // Pede o STOP
        }

        // Espera o byte chegar
        timeout = 10000; while(!(I2C1->SR1 & (1 << 6))) if(--timeout==0) break;
        buffer[i] = I2C1->DR; // Guarda o byte
    }

    I2C1->CR1 |= (1 << 10); // Religa o ACK
}

void MAX30102_Init(void) {
    I2C_Write_Reg(REG_MODE_CONFIG, 0x40);
    for(volatile int i=0; i<100000; i++);
    I2C_Write_Reg(REG_MODE_CONFIG, 0x03);
    I2C_Write_Reg(REG_SPO2_CONFIG, 0x27);
    I2C_Write_Reg(REG_LED1_PA, 0x3F);
    I2C_Write_Reg(REG_LED2_PA, 0x3F);
}

int main(void)
{
    Config_I2C1();
    MAX30102_Init();

    uint8_t dados_fifo[6];

    while(1)
    {
        // 1. Vai buscar 6 bytes à FIFO do sensor
        I2C_Read_Buffer(REG_FIFO_DATA, dados_fifo, 6);

        // 2. O sensor envia dados de 18 bits. Vamos juntar os 3 bytes de cada cor:
        // Pega no Byte 1, empurra 16 casas. Pega no Byte 2, empurra 8. Pega no Byte 3.
        valor_vermelho = ((uint32_t)dados_fifo[0] << 16) | ((uint32_t)dados_fifo[1] << 8) | dados_fifo[2];

        // O sensor esconde algum "lixo" nos bits mais altos, limpamos com a máscara 0x03FFFF (18 bits)
        valor_vermelho &= 0x03FFFF;

        valor_infravermelho = ((uint32_t)dados_fifo[3] << 16) | ((uint32_t)dados_fifo[4] << 8) | dados_fifo[5];
        valor_infravermelho &= 0x03FFFF;

        // Um delay curtíssimo, pois agora queremos ler o mais rápido possível!
        for(volatile int i=0; i<10000; i++);
    }
}
