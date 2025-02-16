#include <stdio.h>
#include "pico/stdlib.h"
#define botao_A 5
#define botao_B 6

int contador = 0;

void fibonacci(int n) {
    int a = 0, b = 1, c;
    if (n >= 1) {
        printf("%d, ", a);
    }
    if (n >= 2) {
        printf("%d, ", b);
    }
    for (int i = 3; i <= n; i++) {
        c = a + b;
        printf("%d, ", c);
        a = b;
        b = c;
    }
    printf("\n");
}
int main()
{
    stdio_init_all();
    gpio_init(botao_A);
    gpio_init(botao_B);

    gpio_set_dir(botao_A, GPIO_IN);
    gpio_set_dir(botao_B, GPIO_IN);

    gpio_pull_up(botao_A);
    gpio_pull_up(botao_B);


    while (true) {
        bool pressao_A = !gpio_get(botao_A), pressao_B = !gpio_get(botao_B); 

        if (pressao_A == 1) {
            contador++;
            printf("Contador: %d\n", contador);
            sleep_ms(1000);
        }

        if (pressao_B == 1) {
            printf("A sequência de Fibonacci até o %d algarismo:\n", contador);
            fibonacci(contador);
            contador = 0;
            sleep_ms(1000);
        }
    }

    return 0;
}
