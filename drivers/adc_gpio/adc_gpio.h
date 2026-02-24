#ifndef ADC_GPIO_H
#define ADC_GPIO_H

#include <stdint.h>

struct adc_gpio_data {
	uint16_t adc_ch0, adc_ch1, adc_ch2;
	uint8_t gpio_state;
};

int adc_gpio_init(void);
int adc_gpio_read(struct adc_gpio_data *data);
int adc_gpio_set_gpio(uint8_t pin, uint8_t state);
uint8_t adc_gpio_get_gpio(uint8_t pin);
uint16_t adc_gpio_read_channel(uint8_t channel);

#endif /* ADC_GPIO_H */
