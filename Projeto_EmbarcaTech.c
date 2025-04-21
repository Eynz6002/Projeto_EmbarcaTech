#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pico/stdlib.h"
#include "libs/display.h"
#include "libs/buttons_leds.h"
#include "libs/buzzer_pwm.h"

#define tam_array 13 //Tamanho do array

//Variaveis globais
const int range_medio = 7;
const int range_baixo = 3;
const int range_alto = 10;
static volatile int local = 0;
static volatile int contador = 0;
static volatile int aleatorio = 0;
int sequencia[tam_array] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233};

//Prototipos de Função
void mensagem_display();//Configura a mensagem do Display
void mensagem_serial();//Configura a mensagem do monitor serial
void encontrar_num_aleatorio();//Escolhe um nomero aleatório de 'sequencia'
void setup();//Inicializa todos os pinos/perifericos

void setup(){
    stdio_init_all();
    //Inicialização dos botões
    init_buttons();

    //Inicialização do buzzer
    pwm_init_buzzer();

    //Inicialização do display
    init_display();
}
void mensagem_display(){
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

    //Imprime a analise de frequencia
    draw_display((char*)texto_freq, 0);
    draw_display((char*)texto_status, 3);

    show_on_display();
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
    
    //Laço de repetição principal
    while (1) {
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
                    mensagem_display();
                    mensagem_serial();
                    on_buzzer();
                    sleep_ms(600);//Espera antes da repetição para aliviar processamento
                }
                sleep_ms(100);//Tempo de espera antes de iniciar o proximo ciclo
            }
            
        }

        //Tela inicial do Display
        printf("Contador: %d\n", contador);
        
        char texto_contador[10];
        sprintf(texto_contador, "  Cont %d", contador);
        draw_display((char*)texto_contador, 1);
        show_on_display();
        sleep_ms(1000);

    }
    return 0;
}