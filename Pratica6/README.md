# Prática 6 — ADC, PWM e DMA

## Descrição

Esta prática utiliza três canais analógicos distintos para controlar a intensidade das cores primárias de um LED RGB.

A leitura dos canais analógicos é feita pelo conversor A/D, e os valores obtidos são usados para ajustar o ciclo de trabalho dos canais PWM.

## Objetivo

Controlar a intensidade do brilho das cores vermelho, verde e azul de um LED RGB usando entradas analógicas.

## Hardware Utilizado

- Placa STM32F103C8T6;
- LED RGB ou 3 LEDs separados;
- 3 potenciômetros ou fontes analógicas distintas;
- Resistores adequados;
- Jumpers e protoboard.

## Ligações Utilizadas

| Função | Pino do STM32 |
|---|---|
| PWM vermelho | PA0 / TIM2_CH1 |
| PWM verde | PA1 / TIM2_CH2 |
| PWM azul | PA2 / TIM2_CH3 |
| Entrada analógica 1 | PA3 |
| Entrada analógica 2 | PA4 |
| Entrada analógica 3 | PA5 |

## Funcionamento

O ADC é configurado em modo SCAN para realizar a leitura de três canais analógicos. O DMA transfere automaticamente os valores convertidos para um vetor na memória.

No laço principal, os valores lidos pelo ADC são usados para atualizar os registradores de comparação do TIM2, alterando a razão cíclica do PWM e, consequentemente, o brilho de cada cor do LED RGB.

## Periféricos Utilizados

- GPIOA;
- ADC1;
- DMA1;
- TIM2 em modo PWM.

## Arquivo Principal

```txt
Src/main.c
```

## Como Executar

1. Abra o projeto na STM32CubeIDE.
2. Compile o projeto.
3. Grave o programa na placa.
4. Conecte o LED RGB e as entradas analógicas conforme a tabela.
5. Varie os sinais analógicos e observe a alteração do brilho em cada cor.
