#include "stm32h7xx_hal.h"
#include "core_hw.h"
#include "gpio.h"
#include "switch.h"

void dsy_switch_init(dsy_switch_t *sw)
{
    sw->gpio.pin.port = sw->pin_config.port;
    sw->gpio.pin.pin  = sw->pin_config.pin;
    switch(sw->pull) {
        case DSY_SWITCH_NOPULL:
            sw->gpio.pull = DSY_GPIO_NOPULL;
            break;
        case DSY_SWITCH_PULLUP:
            sw->gpio.pull = DSY_GPIO_PULLUP;
            break;
        case DSY_SWITCH_PULLDOWN:
            sw->gpio.pull = DSY_GPIO_PULLDOWN;
            break;
        default:
            break;
    }
    sw->gpio.mode = DSY_GPIO_MODE_INPUT;
    dsy_gpio_init(&sw->gpio);
    sw->state = sw->polarity ==
        DSY_SWITCH_POLARITY_NORMAL ? 0x00 : 0xFF;
}

void dsy_switch_debounce(dsy_switch_t *sw)
{
    sw->state = (sw->state << 1)
        | (sw->polarity == DSY_SWITCH_POLARITY_NORMAL
           ? dsy_gpio_read(&sw->gpio)
           : !dsy_gpio_read(&sw->gpio));
}

uint8_t dsy_switch_falling_edge(dsy_switch_t *sw)
{
    return sw->state == 0x80 ? 1 : 0;
}

uint8_t dsy_switch_rising_edge(dsy_switch_t *sw)
{
    return sw->state == 0x7F ? 1 : 0;
}

uint8_t dsy_switch_state(dsy_switch_t *sw)
{
    return (sw->polarity == DSY_SWITCH_POLARITY_NORMAL
            ? dsy_gpio_read(&sw->gpio)
            : !dsy_gpio_read(&sw->gpio));
}

void dsy_switch_pin(dsy_switch_t *sw, int port, int pin)
{
    sw->pin_config.port = port;
    sw->pin_config.pin = pin;
}

void dsy_switch_pull(dsy_switch_t *sw, int pull)
{
    sw->pull = pull;
}

void dsy_switch_polarity(dsy_switch_t *sw, int polarity)
{
    sw->polarity = polarity;
}

void dsy_switch_type(dsy_switch_t *sw, int type)
{
    sw->type = type;
}
