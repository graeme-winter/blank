#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "pico/multicore.h"

volatile unsigned int counter;

const uint LED_PIN = 25;

void spinner() {
  counter = 0;
  while (1) {
    counter ++;
    //printf("Hello World %d\n", counter);
    //sleep_ms(100);
  }
}

int main() {

  bool led;

  bi_decl(bi_program_description("This is a test binary."));
  bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

  stdio_init_all();

  // start the counter
  multicore_launch_core1(spinner);

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  while (1) {
    printf("Bye World %d\n", counter);
    if (led) {
      gpio_put(LED_PIN, 0);
      led = false;
    } else {
      gpio_put(LED_PIN, 1);
      led = true;
    }
    sleep_ms(1000);
  }
}
