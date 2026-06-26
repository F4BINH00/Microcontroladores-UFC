# Prática 7 — Controle de PWM via USART

## Descrição

Esta prática controla a razão cíclica dos canais PWM conectados a um LED RGB por meio de comandos enviados via USART.

O STM32 interpreta comandos seriais para alterar individualmente os canais vermelho, verde e azul, além de possuir um modo de demonstração semelhante ao comportamento da Prática 5.

## Objetivo

Controlar o brilho de um LED RGB via comunicação serial, reconhecendo comandos para modificar o PWM de cada cor.

## Hardware Utilizado

- Placa STM32F103C8T6;
- LED RGB ou 3 LEDs separados;
- Resistores adequados;
- Conversor USB-Serial, caso necessário;
- Jumpers e protoboard.

## Ligações Utilizadas

| Função | Pino do STM32 |
|---|---|
| PWM vermelho | PA0 / TIM2_CH1 |
| PWM verde | PA1 / TIM2_CH2 |
| PWM azul | PA2 / TIM2_CH3 |
| USART1 TX | PA9 |
| USART1 RX | PA10 |

## Comandos Reconhecidos

| Comando | Função |
|---|---|
| `rXX\n` ou `RXX\n` | Ajusta o PWM do LED vermelho para o valor XX |
| `gXX\n` ou `GXX\n` | Ajusta o PWM do LED verde para o valor XX |
| `bXX\n` ou `BXX\n` | Ajusta o PWM do LED azul para o valor XX |
| `d\n` ou `D\n` | Ativa ou desativa o modo de demonstração |

O valor `XX` deve estar no intervalo de `00` a `99`.

Caso seja utilizado Windows, pode ser necessário enviar o comando finalizando com `\r`.

## Funcionamento

A USART1 recebe os caracteres enviados pelo terminal serial. Quando o caractere de finalização é detectado, o comando é interpretado.

Se o comando for de uma cor, o valor recebido é usado para atualizar o registrador de comparação do canal PWM correspondente. Se o comando for `d` ou `D`, o sistema alterna o modo de demonstração.

Durante o modo de demonstração, os demais comandos devem ser ignorados.

## Periféricos Utilizados

- GPIOA;
- TIM2 em modo PWM;
- TIM3 para controle do modo de demonstração;
- USART1;
- NVIC.

## Arquivo Principal

```txt
Src/main.c
```

## Como Executar

1. Abra o projeto na STM32CubeIDE.
2. Compile o projeto.
3. Grave o programa na placa.
4. Conecte o LED RGB aos canais PWM.
5. Abra um terminal serial na taxa configurada no código.
6. Envie comandos como:

```txt
r50
b20
g99
d
```

7. Observe a alteração no brilho do LED RGB.
