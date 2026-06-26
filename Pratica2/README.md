# Prática 2 — Interrupção Externa

## Descrição

Esta prática utiliza três push buttons para alterar o estado de três LEDs por meio de interrupções externas. Cada botão aciona uma interrupção diferente e muda o estado do LED correspondente usando operação XOR.

## Objetivo

Utilizar 3 push buttons e um LED RGB, ou 3 LEDs distintos, para mudar o estado de cada LED usando diferentes interrupções externas.

## Hardware Utilizado

- Placa STM32F103C8T6;
- 3 push buttons;
- LED RGB ou 3 LEDs separados;
- Resistores adequados;
- Jumpers e protoboard.

## Ligações Utilizadas

| Componente | Pino do STM32 |
|---|---|
| LED vermelho / LED 1 | PA0 |
| LED verde / LED 2 | PA1 |
| LED azul / LED 3 | PA2 |
| Botão 1 | PB0 / EXTI0 |
| Botão 2 | PB1 / EXTI1 |
| Botão 3 | PB10 / EXTI10 |

## Funcionamento

Cada botão foi configurado como entrada com pull-up interno. Quando o botão é pressionado, ocorre uma borda de descida no pino correspondente, gerando uma interrupção externa.

Dentro de cada rotina de interrupção, o estado do LED correspondente é invertido com XOR. Assim, a cada pressionamento, o LED alterna entre ligado e desligado.

## Periféricos Utilizados

- GPIOA;
- GPIOB;
- AFIO;
- EXTI;
- NVIC.

## Arquivo Principal

```txt
Src/main.c
```

## Como Executar

1. Abra o projeto na STM32CubeIDE.
2. Compile o projeto.
3. Grave o programa na placa.
4. Monte os botões e LEDs conforme a tabela.
5. Pressione os botões e observe a alteração no estado dos LEDs.
