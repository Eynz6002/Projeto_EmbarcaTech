#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "libs/max30100/max30100.h" 
#include "libs/algorithm/algorithm.h"
#include "libs/display.h"
#include "libs/buttons_leds.h"
#include "libs/buzzer_pwm.h"

// Configurações do I2C
#define I2C_PORT i2c0
#define I2C_SDA_PIN 0
#define I2C_SCL_PIN 1

// Variáveis globais
static volatile int contador = 0;
uint32_t ir_buffer[BUFFER_SIZE];
uint32_t red_buffer[BUFFER_SIZE];
int32_t spo2;
int8_t spo2_valid;
int32_t heart_rate;
int8_t hr_valid;

// Cabeçalhos
void setup();
void ler_sensor();
void mensagem_display();

void setup() {
    // Inicialização dos perifericos padrões da placa
    init_buttons();
    pwm_init_buzzer();
    init_leds();
    init_display();

    // Inicialização do sensor (MAX3010x)
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    // Inicializa o sensor para leitura
    if (!max30102_init(I2C_PORT)) {
        // Caso o sensor não seja o MAX30102, ele ira mostrar o erro
        draw_display("Erro no Sensor", 0);
        show_on_display();
        on_red(2000, 0);
        while(1);
    }
}

void ler_sensor() {
    uint32_t buffer_idx = 0;
    
    // Tela de leitura de dados
    draw_display("Lendo dados...", 0);
    draw_display("Aguarde 4s", 2);
    show_on_display();
    
    // Acende o LED azul mostrando a leitura de dados
    gpio_put(led_blue, true); 

    // Preenche o buffer com a leitura do sensor
    while (buffer_idx < BUFFER_SIZE) {
        uint32_t ir, red;
        max30102_read_fifo(&ir, &red);
        ir_buffer[buffer_idx] = ir;
        red_buffer[buffer_idx] = red;
        buffer_idx++;
        sleep_ms(10);
    }
    
    // Apaga o LED
    gpio_put(led_blue, false);
    
    // Calculo dos batimentos e da oxigenação
    calc_spo2_and_hr(&spo2, &spo2_valid, &heart_rate, &hr_valid, ir_buffer, red_buffer);
}

void mensagem_display() {
    char texto_hr[20];
    char texto_spo2[20];

    if (hr_valid && spo2_valid) {
        sprintf(texto_hr, "HR: %ld bpm", heart_rate);
        sprintf(texto_spo2, "SpO2: %ld %%", spo2);
        
        draw_display("Resultado:", 0);
        draw_display(texto_hr, 3);
        draw_display(texto_spo2, 5);

        if (spo2 < 90) {
            // Alerta de oxigenação baixa
            gpio_put(led_red, true);
            on_buzzer(); 
            gpio_put(led_red, false);
        } else {
            // Pisca LED verde para sucesso
            on_green(500, 0);
        }

    } else {
        draw_display("Falha leitura", 0);
        draw_display("Insira o dedo", 2);
        draw_display("corretamente!", 4);

        // Pisca LED vermelho para o dedo mal posicionado
        on_red(500, 0);
    }
    
    // Atualiza a tela com os resultados
    show_on_display();
    sleep_ms(4000);
}

int main() {
    setup();
    
    while (1) {
        
        // Botão A incrementa a quantidade de ciclos de leitura
        if(gpio_get(button_A) == 0) {
            contador++;
            sleep_ms(300); // Debounce
        }
        
        // Botão B inicia os ciclos configurados
        if(gpio_get(button_B) == 0 && contador > 0) {
            while (contador > 0) {
                ler_sensor();
                mensagem_display();
                contador--;
                
                // Pausa para visualizar o resultado antes de começar a próxima leitura
                if (contador > 0) {
                    sleep_ms(3000); 
                }
            }
        }

        //||||||||||||||| Menu ||||||||||||||| 
        char texto_contador[20];
        
        if (contador == 0) {
            sprintf(texto_contador, "Ciclos: %d", contador);
            draw_display("Menu Principal", 0);
            draw_display("A: Add ciclo", 2);
            draw_display("B: Iniciar", 4);
            draw_display(texto_contador, 6);
        } else {
            sprintf(texto_contador, "Ciclos: %d", contador);
            draw_display("Pronto p/ ler", 0);
            draw_display("Aperte B", 2);
            draw_display("para iniciar", 4);
            draw_display(texto_contador, 6);
        }
        
        show_on_display();
        sleep_ms(150); // Delay do menu inicial
    }
    return 0;
}