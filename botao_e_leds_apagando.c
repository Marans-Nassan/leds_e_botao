#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#define botao 5
#define red_led 11
#define yellow_led 12
#define green_led 13

static bool leds_ativos = false;
uint16_t delay; 
uint8_t i;
static volatile uint32_t last_time = 0;

int64_t turn_off_callback(alarm_id_t id, void* user_data) {  //chamada do alarme configurado na interrupção
    uint led = (uint)(uintptr_t)user_data; 
    gpio_put(led, 0);  
    leds_ativos = (gpio_get(13) != 0);
    return 0; 
}

void botinit(){  // inicialização do botão
    gpio_init(5);
    gpio_set_dir(5, 0);
    gpio_pull_up(5);
}

void ledinit(){  // inicialização dos leds
    for(i = 11; i < 14 ; i++){
        gpio_init(i);
        gpio_set_dir(i, 1);
        gpio_put(i, 0);
    }
}

static void gpio_irq_handler(uint gpio, uint32_t events){  //função usada ao utilizar a interupção do botão
    if(!leds_ativos){ 
        uint32_t current_time = to_us_since_boot(get_absolute_time());  //Debounce
        if(current_time - last_time > 200000){
            last_time = current_time;
                for(i = 11, delay = 3000; i < 14 ; i++, delay += 3000){  //Definição do delay de cada led apagando
                gpio_put(i, 1);
                add_alarm_in_ms(delay, turn_off_callback, (void*)(uintptr_t)i, false);
                }
    }    }      
}

int main()
{   
    botinit();
    ledinit();
    gpio_set_irq_enabled_with_callback(5, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); //interrupção
    while (true) {
        sleep_ms(1);
    }
}