# Prática 1 — GPIO

## Descrição

Esta prática utiliza três push buttons e três LEDs conectados ao STM32F103. Cada botão controla um LED diferente por meio de leitura direta dos pinos GPIO usando a técnica de polling.

## Objetivo

Conectar 3 push buttons e 3 LEDs ao STM32F103, de forma que cada push button acione um LED diferente.

## Hardware Utilizado

- Placa STM32F103C8T6;
- 3 push buttons;
- 3 LEDs;
- Resistores adequados para os LEDs;
- Jumpers e protoboard.

## Ligações Utilizadas

| Componente | Pino do STM32 |
|---|---|
| LED 1 | PA0 |
| LED 2 | PA1 |
| LED 3 | PA2 |
| Botão 1 | PB0 |
| Botão 2 | PB1 |
| Botão 3 | PB10 |

Os botões são configurados como entrada com resistor de pull-up interno. Assim, quando um botão é pressionado, o pino correspondente é levado para nível lógico baixo.

## Funcionamento

O programa verifica continuamente o estado dos botões. Quando um botão é pressionado, o LED correspondente é ligado. Quando o botão é solto, o LED é desligado.

## Periféricos Utilizados

- GPIOA para saída dos LEDs;
- GPIOB para entrada dos botões.

## Arquivo Principal

```txt
Src/main.c
```

## Como Executar

1. Abra o projeto na STM32CubeIDE.
2. Compile o projeto.
3. Grave o programa na placa.
4. Monte o circuito conforme a tabela de ligações.
5. Pressione cada botão e observe o LED correspondente.
