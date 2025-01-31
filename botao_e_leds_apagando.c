#include <stdio.h>
#include "pico/stdlib.h"

#define botao 5
#define red_led 11
#define yellow_led 12
#define green_led 13

uint8_t i;
struct repeating_timer timer;

void botinit(){
    gpio_init(5);
    gpio_set_dir(5, 0);
    gpio_pull_up(5);
}

void ledinit(){
    for(i = 11; i < 14 ; i++){
        gpio_init(i);
        gpio_set_dir(i, 1);
        gpio_put(i, 0);
    }
}

static void gpio_irq_handler(uint gpio, uint32_t events){
    for(i = 11; i < 14 ; i++){
    gpio_put(i, 1);
    }
}



int main()
{   
    stdio_init_all();
    botinit();
    ledinit();
    gpio_set_irq_enabled_with_callback(5, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
