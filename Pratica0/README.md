# Prática 0 — Configuração da STM32CubeIDE

## Descrição

Esta prática tem como objetivo realizar a configuração inicial da **STM32CubeIDE** e validar o funcionamento básico do ambiente de desenvolvimento com a placa **STM32F103**.

O projeto utiliza o LED conectado ao pino **PC13** para testar a configuração do clock, GPIO e SysTick.

## Objetivos

- Configurar o ambiente STM32CubeIDE;
- Criar/importar um projeto para o STM32F103;
- Configurar um pino GPIO como saída;
- Utilizar o SysTick como base de tempo;
- Testar o funcionamento do LED da placa.

## Hardware Utilizado

- Placa STM32F103C8T6;
- LED interno conectado ao pino PC13;
- Gravador/debugger compatível com STM32.

## Funcionamento

O código configura o clock interno, inicializa o GPIOC e utiliza o SysTick para gerar uma contagem em milissegundos. A partir dessa contagem, o LED em PC13 é alternado em intervalos definidos.

Além disso, o projeto utiliza a instrução `__WFI()` para colocar a CPU em modo de espera enquanto aguarda a próxima interrupção do SysTick, contribuindo para a redução do consumo de energia.

## Arquivo Principal

```txt
Src/main.c
```

## Como Executar

1. Abra o projeto na STM32CubeIDE.
2. Compile o projeto.
3. Grave o programa na placa STM32F103.
4. Observe o LED interno piscando no pino PC13.

## Observação

Esta prática também atende à atividade bônus de refazer a Prática 0 incluindo uma estratégia de redução de consumo de energia, por meio do uso do clock interno e da instrução `__WFI()`.
