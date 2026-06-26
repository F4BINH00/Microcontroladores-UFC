# Prática 4 — Timer

## Descrição

Esta prática utiliza um timer do microcontrolador para piscar duas vezes cada uma das combinações de cores de um LED RGB.

## Objetivo

Usar o timer do STM32F103 para piscar duas vezes cada cor da sequência:

```txt
Vermelho, Verde, Azul, Amarelo, Ciano, Roxo, Branco
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

O programa configura o TIM2 para gerar interrupções periódicas. A cada interrupção, o código alterna entre ligar e apagar a cor atual. Após duas piscadas, o programa passa para a próxima combinação de cor.

O LED RGB é tratado como ânodo comum, então a lógica de acionamento é invertida.

## Periféricos Utilizados

- GPIOA;
- TIM2;
- NVIC.

## Arquivo Principal

```txt
Src/main.c
```

## Como Executar

1. Abra o projeto na STM32CubeIDE.
2. Compile o projeto.
3. Grave o programa na placa.
4. Conecte o LED RGB aos pinos PA0, PA1 e PA2.
5. Observe cada cor piscando duas vezes antes da troca para a próxima.
