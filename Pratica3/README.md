# Prática 3 — SysTick

## Descrição

Esta prática utiliza o SysTick para acionar, de forma alternada, todas as combinações de cores de um LED RGB com intervalo de 1 segundo entre elas.

## Objetivo

Usar o SysTick para alternar as cores de um LED RGB seguindo a sequência:

```txt
Apagado, Vermelho, Verde, Azul, Amarelo, Ciano, Roxo, Branco
```

## Hardware Utilizado

- Placa STM32F103C8T6;
- LED RGB ou 3 LEDs separados;
- Resistores adequados;
- Jumpers e protoboard.

## Ligações Utilizadas

| Cor | Pino do STM32 |
|---|---|
| Vermelho | PA0 |
| Verde | PA1 |
| Azul | PA2 |

## Funcionamento

O SysTick é configurado para gerar uma interrupção a cada 1 ms. A variável global de contagem é incrementada no `SysTick_Handler`. Quando a contagem atinge 1000 ms, o programa muda para a próxima cor da sequência.

O código considera o uso de LED RGB com lógica de ânodo comum, invertendo os níveis lógicos para acender as cores corretamente.

## Periféricos Utilizados

- GPIOA;
- SysTick.

## Arquivo Principal

```txt
Src/main.c
```

## Como Executar

1. Abra o projeto na STM32CubeIDE.
2. Compile o projeto.
3. Grave o programa na placa.
4. Conecte o LED RGB aos pinos PA0, PA1 e PA2.
5. Observe a troca automática das cores a cada 1 segundo.
