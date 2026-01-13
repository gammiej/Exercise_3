/*
James Gammie
1/13/2026

This program requires an sp32s3 board with a button and led, the led pin is 10, the button pin is 4.
every other time the button is pressed, the LED will turn on
*/

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_10        // Choose your LED pin
#define BUTTON_PIN GPIO_NUM_4       // Choose your button pin
#define ENABLE_PIN GPIO_NUM_5       // Choose your enable pin
#define LOOP_DELAY_MS 25 // Loop delay

void app_main(void) {

    // TO-DO: Configure LED output

    gpio_config_t led_io_conf = {
        .pin_bit_mask = (1ULL << LED_PIN), 
        .mode = GPIO_MODE_OUTPUT,          
        .pull_up_en = GPIO_PULLUP_DISABLE, 
        .pull_down_en = GPIO_PULLDOWN_DISABLE, 
        .intr_type = GPIO_INTR_DISABLE    
    };
    // Configure the GPIO pin using the defined structure
    ESP_ERROR_CHECK(gpio_config(&led_io_conf)); // Use ESP_ERROR_CHECK for error handling

    // TO-DO: Configure Button input

    gpio_config_t button_io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_PIN), 
        .mode = GPIO_MODE_INPUT,          
        .pull_up_en = GPIO_PULLUP_ENABLE, 
        .pull_down_en = GPIO_PULLDOWN_DISABLE, 
        .intr_type = GPIO_INTR_DISABLE    
    };

    // Configure the GPIO pin using the defined structure
    ESP_ERROR_CHECK(gpio_config(&button_io_conf)); // Use ESP_ERROR_CHECK for error handling
    

    gpio_config_t enable_io_conf = {
        .pin_bit_mask = (1ULL << ENABLE_PIN), 
        .mode = GPIO_MODE_INPUT,          
        .pull_up_en = GPIO_PULLUP_ENABLE, 
        .pull_down_en = GPIO_PULLDOWN_DISABLE, 
        .intr_type = GPIO_INTR_DISABLE    
    };

    // Configure the GPIO pin using the defined structure
    ESP_ERROR_CHECK(gpio_config(&enable_io_conf)); // Use ESP_ERROR_CHECK for error handling

    bool prev_bstate = false;
    bool current_bstate = gpio_get_level(BUTTON_PIN) == 0;
    bool every_other = true;
    bool enable = gpio_get_level(ENABLE_PIN) == 0;


    while (1) {
    // TO-DO: Implement LED toggle and button logic here
        current_bstate = gpio_get_level(BUTTON_PIN) == 0;
        enable = gpio_get_level(ENABLE_PIN) == 0;

        if (current_bstate && current_bstate != prev_bstate) {
            every_other = !every_other;
        }

        prev_bstate = current_bstate;

        gpio_set_level(LED_PIN, (every_other && current_bstate && enable));
        vTaskDelay(  LOOP_DELAY_MS / portTICK_PERIOD_MS); //Use appropriate loop delays
        
    }
}
