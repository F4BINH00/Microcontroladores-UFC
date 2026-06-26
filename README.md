# ⚙️ Microcontroladores – UFC Quixadá (2026.1)

Repositório centralizado com as práticas de laboratório desenvolvidas na disciplina de **Microcontroladores**, ministrada no curso de **Engenharia de Computação** da **Universidade Federal do Ceará (UFC) – Campus Quixadá**.

O foco da disciplina é o desenvolvimento de sistemas embarcados utilizando a arquitetura **ARM Cortex-M3 (STM32F103)**, explorando os principais periféricos do microcontrolador por meio da **STM32CubeIDE** e da biblioteca **STM32 HAL**.

---

## 🛠️ Conteúdo do Repositório

### 📘 Prática 00 – Configuração do Ambiente

* Configuração da STM32CubeIDE.
* Configuração do Clock do sistema.
* Introdução ao gerenciamento de energia.

### 💡 Prática 01 – GPIO

* Configuração de portas GPIO.
* Controle de LEDs por meio de Push Buttons utilizando *polling*.

### ⚡ Prática 02 – Interrupções Externas

* Configuração do controlador NVIC.
* Utilização de interrupções EXTI para controle de hardware.

### ⏱️ Prática 03 – SysTick

* Utilização do temporizador SysTick.
* Geração de temporizações periódicas sem uso de delays bloqueantes.

### ⌚ Prática 04 – Timers

* Configuração dos Timers de hardware.
* Utilização de Prescaler e Auto-Reload Register (ARR).

### 🌈 Prática 05 – PWM

* Geração de sinais PWM.
* Controle gradual da intensidade luminosa de LEDs RGB.

### 🎚️ Prática 06 – ADC + DMA

* Conversão Analógico-Digital.
* Transferência automática utilizando DMA.
* Leitura de potenciômetros para controle de LEDs.

### 💬 Prática 07 – USART

* Comunicação serial entre o STM32 e o computador.
* Recepção e interpretação de comandos enviados pelo terminal serial.

### 🚀 Projeto Final

O projeto final da disciplina será disponibilizado em um repositório próprio após sua conclusão.

---

## 📂 Estrutura do Repositório

```text
Microcontroladores-UFC/
│
├── README.md
├── Pratica00/
├── Pratica01/
├── Pratica02/
├── Pratica03/
├── Pratica04/
├── Pratica05/
├── Pratica06/
└── Pratica07/
```

Cada prática possui seu próprio **README.md**, contendo:

* Objetivo da atividade.
* Hardware utilizado.
* Funcionalidades implementadas.
* Estrutura dos arquivos.
* Instruções de compilação e execução.
* Conceitos abordados.

---

## 🧰 Tecnologias Utilizadas

* Linguagem C
* STM32CubeIDE
* STM32CubeMX
* STM32 HAL
* ARM Cortex-M3
* STM32F103
* Git
* GitHub

---

## 🎯 Conceitos Abordados

Ao longo da disciplina são explorados conceitos fundamentais de Sistemas Embarcados, incluindo:

* Configuração de Clock
* GPIO
* Interrupções Externas (EXTI)
* NVIC
* SysTick
* Timers
* PWM
* ADC
* DMA
* USART
* Manipulação de periféricos
* Desenvolvimento em tempo real
* Programação para microcontroladores ARM Cortex-M

---

## 👨‍💻 Autor

**Fábio Rodrigues Borges Filho**

Graduando em Engenharia de Computação
Universidade Federal do Ceará (UFC) – Campus Quixadá
