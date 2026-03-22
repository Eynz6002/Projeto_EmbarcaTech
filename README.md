# Monitor de Batimentos Cardíacos e Oxímetro (Projeto EmbarcaTech)

> Sistema de monitoramento de saúde embarcado utilizando Raspberry Pi Pico e sensor MAX30102, com interface visual via display OLED, alarmes sonoros/luminosos e controlo interativo por botões.

![Status](https://img.shields.io/badge/Status-Active-success)
![Platform](https://img.shields.io/badge/Platform-Raspberry%20Pi%20Pico-C51A4A?logo=raspberrypi&logoColor=white)
![Language](https://img.shields.io/badge/Language-C-00599C?logo=c&logoColor=white)
![Framework](https://img.shields.io/badge/Framework-Pico%20SDK-8A2BE2)
![License](https://img.shields.io/badge/License-MIT-green)

## ✨ Funcionalidades

- **Recolha e Processamento de Dados:** Leitura de dados I2C a partir do sensor MAX30102 e processamento matemático de picos para calcular a Frequência Cardíaca (HR) e a Saturação de Oxigénio no Sangue (SpO2).
- **Interface Interativa:** Menu navegável através do Ecrã OLED e controlo por botões físicos (Botão A para adicionar ciclos de leitura e Botão B para iniciar o processo).
- **Sistema de Alarmes:** Acionamento de um Buzzer PWM e LED Vermelho caso o nível de oxigénio (SpO2) lido caia para valores de alerta (abaixo de 90%).
- **Feedback Visual de Estado:** Utilização de LEDs indicadores durante a operação (LED Azul enquanto o sensor efetua leituras e LED Verde para leituras concluídas com sucesso e valores normais).

## 🛠️ Tecnologias e Requisitos

**Hardware:**
- Raspberry Pi Pico ou Pico W.
- Módulo Sensor de Frequência Cardíaca e Oxímetro **MAX30102**.
- Display OLED 0.96" I2C (**SSD1306**).
- 1 Buzzer (Ativo/Passivo).
- 3 LEDs (Verde, Azul, Vermelho) e 2 Botões (Push buttons).
- Protoboard e Cabos Jumper.

**Software e Ferramentas:**
- C / C++.
- **Raspberry Pi Pico SDK**.
- `CMake` e `Ninja` (Para build e compilação do firmware).
- Visual Studio Code com a extensão Raspberry Pi Pico.

## 📁 Estrutura do Projeto

- `Projeto_EmbarcaTech.c`: Ficheiro principal. Contém as rotinas de inicialização, a lógica de controlo do menu por botões, chamadas de leitura do sensor e acionamento dos alertas.
- `libs/`: Pasta que contém as bibliotecas essenciais e cabeçalhos (`.h`):
  - `max30100/`: Controladores e comunicação I2C com o sensor.
  - `algorithm/`: Algoritmo avançado de processamento de sinais para calcular as taxas cardíacas e de oxigénio.
- `source/`: Código-fonte (`.c`) para controlo de hardware:
  - `display.c` e `ssd1306_i2c.c`: Tratamento e renderização gráfica no Ecrã OLED.
  - `buttons_leds.c`: Inicialização e controlo simplificado dos atuadores luminosos e entradas.
  - `buzzer_pwm.c`: Controlo de frequência PWM para emissão do alarme sonoro.
- `CMakeLists.txt`: Configuração do CMake com a definição dos ficheiros a compilar e link das bibliotecas de hardware do SDK (i2c, pwm, clocks).

## 📚 Referências e Créditos

O driver de comunicação I2C para o sensor **MAX30102** e a lógica do algoritmo (`algorithm.c` e `max30100.c`) utilizados como base neste projeto foram adaptados a partir do repositório [pico_max30102](https://github.com/LabirasIFPI/pico_max30102) desenvolvido pelo **LABIRAS (IFPI)**.

Agradecimentos aos autores originais da implementação do sensor: [@antoniojosemota](https://github.com/antoniojosemota), [@NicolasRafael](https://github.com/NicolasRaf) e [@Arthur Vieira](https://github.com/ArthurV10).
