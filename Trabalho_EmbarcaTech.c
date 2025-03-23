#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "hardware/clocks.h"
#include "inc/ssd1306.h"

#define tam_array 13 //Tamanho do array
#define beep_freq 10 // Frequencia do beep

//Pinos
#define button_A 5
#define button_B 6
#define buzzer_pin 21 
const uint i2c_SDA = 14;
const uint i2c_SCL = 15;

//Variaveis globais
const int range_medio = 7;
const int range_baixo = 3;
const int range_alto = 10;
static volatile int local = 0;
static volatile int contador = 0;
static volatile int aleatorio = 0;
int sequencia[tam_array] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233};

//Prototipos de Função
void beep();//Gera beep's no buzzer
void mensagem_display(struct render_area *frame_area, uint8_t *ssd);//Configura a mensagem do Display
void mensagem_serial();//Configura a mensagem do monitor serial
void encontrar_num_aleatorio();//Escolhe um nomero aleatório de 'sequencia'
void pwm_init_buzzer_pin();//inicializa o pino do buzzer
void setup();//Inicializa todos os pinos/perifericos

void setup(){
    stdio_init_all();

    //Inicialização dos botões
    gpio_init(button_A);
    gpio_set_dir(button_A, GPIO_IN);
    gpio_pull_up(button_A);
    gpio_init(button_B);
    gpio_set_dir(button_B, GPIO_IN);
    gpio_pull_up(button_B);

    //Inicialização do buzzer
    pwm_init_buzzer_pin(buzzer_pin, beep_freq);

    //Inicialização do display
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(i2c_SDA, GPIO_FUNC_I2C);
    gpio_set_function(i2c_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(i2c_SDA);
    gpio_pull_up(i2c_SCL);
    ssd1306_init();
}
void pwm_init_buzzer_pin(uint pin, uint freq){
    gpio_set_function(pin, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(pin);

    pwm_config config = pwm_get_default_config();

    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys)/(freq * 4096));
    pwm_init(slice_num, &config, true);

    pwm_set_gpio_level(pin, 0);
}
void beep(){
    uint slice_num = pwm_gpio_to_slice_num(buzzer_pin);

    pwm_set_gpio_level(buzzer_pin, 1024);//Ativa o buzzer

    sleep_ms(300);//Tempo do beep

    pwm_set_gpio_level(buzzer_pin, 0);//Desativa o buzzer

    sleep_ms(100);//Espera para finalizar a função beep
}
void mensagem_display(struct render_area *frame_area, uint8_t *ssd){
    char texto_freq[10];//String para a frequecia
    char texto_status[20];//String para o Status

    sprintf(texto_freq, "Freq %d", aleatorio);//Formata a string de frequencia para ser atualizada
    
    //Formata a string status
    if(local == range_medio){
        sprintf(texto_status, " Normal");
    } else if(local < range_medio){
        if(local < range_baixo){
            sprintf(texto_status, " Baixa");
        } else {
            sprintf(texto_status, " Quase baixa");
        }
    } else {
        if(local > range_alto){
            sprintf(texto_status, " Alta");
        } else {
            sprintf(texto_status, " Quase Alta");
        }
    }

    //String que organiza o display
    char* string_oled[] =
    {
        "",
        "",
        "Status",
        "",
    };

    //Alocação das strings que seram mostradas
    string_oled[3] = texto_status;
    string_oled[0] = texto_freq;

    //Imprime a analise de frequencia
    int y = 0;
    for (uint i = 0; i < count_of(string_oled); i++)
    {
        ssd1306_draw_string(ssd, 5, y, string_oled[i]);
        y += 8;
    }

    render_on_display(ssd, frame_area);
    memset(ssd, 0, ssd1306_buffer_length);//Limpa o Display
}
void mensagem_serial(){
    printf("Freq: %d\n", aleatorio);
    if(local == range_medio){
        printf("Normal");

    } else if(local < range_medio){
        if(local < range_baixo){
            printf("Baixa");

        } else {
            printf("Quase Baixa");

        }
    } else {
        if(local > range_alto){
            printf("Alta");
        
        } else {
            printf("Quase Alta");
        
        }
    }
    printf("\n");
}
void encontrar_num_aletorio(){
    srand(time(NULL));
    local = rand() % tam_array;
    aleatorio = sequencia[local];
}
int main() {
    setup();

    //Configuração do Display - Inicio
    struct render_area frame_area = 
    {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page: ssd1306_n_pages - 1
    };
    calculate_render_area_buffer_length(&frame_area);
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);
    //Configuração do Display - Fim

    //String para a mensagem inicial do display
    char* display_inicio[] = {
        "",
        "",
    };

    char texto_contador[10];
    
    //Laço de repetição principal
    while (true) {
        if(gpio_get(button_A) == 0)
        {
            contador++;
            sleep_ms(1000);
        }
        if(gpio_get(button_B) == 0){
            for (contador; contador > 0; contador--)
            {
                for (int i = 0; i < 15; i++) {//Duração dos ciclos
                    encontrar_num_aletorio();
                    mensagem_display(&frame_area, ssd);
                    mensagem_serial();
                    beep();
                    sleep_ms(600);//Espera antes da repetição para aliviar processamento
                }
                sleep_ms(100);//Tempo de espera antes de iniciar o proximo ciclo
            }
            
        }

        //Tela inicial do Display
        printf("Contador: %d", contador);
        
        sprintf(texto_contador, "Cont %d", contador);
        display_inicio[1] = texto_contador;

        int y = 0;
        for (uint i = 0; i < count_of(display_inicio); i++)
        {
            ssd1306_draw_string(ssd, 5, y, display_inicio[i]);
            y += 8;
        }

        render_on_display(ssd, &frame_area);
        memset(ssd, 0, ssd1306_buffer_length);

    }
    return 0;
}
