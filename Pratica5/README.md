# Prática 5 — PWM

## Descrição

Esta prática tem como proposta utilizar PWM para acender e apagar lentamente cada uma das combinações de cores de um LED RGB, sem o uso de `delay` ou função similar.

A variação da razão cíclica deve ser feita com auxílio de um segundo timer.

## Objetivo

Usar PWM para controlar o brilho de um LED RGB, variando lentamente a intensidade das cores:

```txt
Vermelho, Verde, Azul, Amarelo, Ciano, Roxo, Branco
```

## Hardware Utilizado

- Placa STM32F103C8T6;
- LED RGB ou 3 LEDs separados;
- Resistores adequados;
- Jumpers e protoboard.

## Funcionamento Esperado

O PWM controla a intensidade de cada canal do LED RGB. A razão cíclica é alterada gradualmente, fazendo a cor acender e apagar de forma suave.

De acordo com a especificação da prática, não deve ser utilizado `delay`. Um segundo timer deve ser configurado para controlar a atualização da razão cíclica.

## Periféricos Esperados

- GPIO;
- Timer para PWM;
- Segundo timer para atualização da razão cíclica.

## Arquivo Principal

```txt
Src/main.c
```

## Observação

Ao revisar o projeto, verifique se o arquivo `Src/main.c` corresponde à implementação de PWM com LED RGB. Caso o código atual esteja relacionado a outro periférico ou sensor, recomenda-se conferir se a pasta correta da Prática 5 foi adicionada ao repositório.
