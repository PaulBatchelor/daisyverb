#pragma once
#ifndef DSY_GPIO_H
#define DSY_GPIO_H
#ifdef __cplusplus
extern "C"
{
#endif

enum
{
	DSY_GPIO_MODE_INPUT,
	DSY_GPIO_MODE_OUTPUT_PP,
	DSY_GPIO_MODE_OUTPUT_OD,
	DSY_GPIO_MODE_LAST,
};

enum
{
	DSY_GPIO_NOPULL,
	DSY_GPIO_PULLUP,
	DSY_GPIO_PULLDOWN,
};

typedef struct
{
	dsy_gpio_pin pin;
	int mode;
	int pull;
} dsy_gpio_t;

void dsy_gpio_init(dsy_gpio_t *p);
uint8_t dsy_gpio_read(dsy_gpio_t *p);
void dsy_gpio_write(dsy_gpio_t *p, uint8_t state);
void dsy_gpio_toggle(dsy_gpio_t *p);

void dsy_gpio_config_set(dsy_gpio_pin *config,
                         int port,
                         int pos,
                         int pin);

void dsy_gpio_set(dsy_gpio_t *p,
                  int pin,
                  int port,
                  int mode);

void dsy_gpio_pull(dsy_gpio_t *p, int pull);

#ifdef __cplusplus
}
#endif

#endif
