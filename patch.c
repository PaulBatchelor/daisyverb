#include "daisy.h"
#include "seed.h"
#include "patch.h"

#define BUTTON_1_PORT DSY_GPIOA
#define BUTTON_1_PIN 8
#define BUTTON_2_PORT DSY_GPIOB
#define BUTTON_2_PIN 12
#define TOGGLE_PORT DSY_GPIOG
#define TOGGLE_PIN 11
#define GATE_1_PORT DSY_GPIOB
#define GATE_1_PIN 5
#define GATE_2_PORT DSY_GPIOB
#define GATE_2_PIN 4
#define GATE_OUT_PORT DSY_GPIOG
#define GATE_OUT_PIN 10

/* Mapping of LEDs via leddriver.h */
enum {
	LED_A4,
	LED_A3,
	LED_A2,
	LED_A1,
	LED_B4,
	LED_B3,
	LED_B2,
	LED_B1,
	LED_C4,
	LED_C3,
	LED_C2,
	LED_C1,
	LED_D4,
	LED_D3,
	LED_D2,
	LED_D1,
	LED_LAST
};


typedef struct {
	dsy_switch_t button1, button2, toggle;
	dsy_gpio_t gate_in1, gate_in2, gate_out;
	daisy_handle seed;
} daisy_patch;

static daisy_patch patch;

static void daisy_patch_init_(daisy_patch *p)
{
	/* p->button1.pin_config.port = BUTTON_1_PORT; */
	/* p->button1.pin_config.pin = BUTTON_1_PIN; */
    dsy_switch_pin(&p->button1, BUTTON_1_PORT, BUTTON_1_PIN);
	/* p->button1.pull = DSY_SWITCH_PULLUP; */
    dsy_switch_pull(&p->button1, DSY_SWITCH_PULLUP);
	/* p->button1.polarity = DSY_SWITCH_POLARITY_INVERTED; */
    dsy_switch_polarity(&p->button1, DSY_SWITCH_POLARITY_INVERTED);

	/* p->button1.type = DSY_SWITCH_TYPE_MOMENTARY; */
    dsy_switch_type(&p->button1, DSY_SWITCH_TYPE_MOMENTARY);

	/* p->button2.pin_config.port = BUTTON_2_PORT; */
	/* p->button2.pin_config.pin = BUTTON_2_PIN; */
    dsy_switch_pin(&p->button2, BUTTON_2_PORT, BUTTON_2_PIN);
	/* p->button2.pull = DSY_SWITCH_PULLUP; */
    dsy_switch_pull(&p->button2, DSY_SWITCH_PULLUP);
	/* p->button2.polarity = DSY_SWITCH_POLARITY_INVERTED; */
    dsy_switch_polarity(&p->button2, DSY_SWITCH_POLARITY_INVERTED);
	/* p->button2.type = DSY_SWITCH_TYPE_MOMENTARY; */
    dsy_switch_type(&p->button2, DSY_SWITCH_TYPE_MOMENTARY);

	/* p->toggle.pin_config.port = TOGGLE_PORT; */
	/* p->toggle.pin_config.pin = TOGGLE_PIN; */
    dsy_switch_pin(&p->toggle, TOGGLE_PORT, TOGGLE_PIN);
	/* p->toggle.pull = DSY_SWITCH_PULLUP; */
    dsy_switch_pull(&p->toggle, DSY_SWITCH_PULLUP);
	/* p->toggle.type = DSY_SWITCH_TYPE_TOGGLE; */
    dsy_switch_type(&p->toggle, DSY_SWITCH_TYPE_TOGGLE);

	/* p->gate_in1.pin.port = GATE_1_PORT; */
	/* p->gate_in1.pin.pin = GATE_1_PIN; */
	/* p->gate_in1.mode = DSY_GPIO_MODE_INPUT; */
    dsy_gpio_set(&p->gate_in1,
                 GATE_1_PORT,
                 GATE_1_PIN,
                 DSY_GPIO_MODE_INPUT);

	/* p->gate_in2.pin.port = GATE_2_PORT; */
	/* p->gate_in2.pin.pin = GATE_2_PIN; */
	/* p->gate_in2.mode = DSY_GPIO_MODE_INPUT; */

    dsy_gpio_set(&p->gate_in2,
                 GATE_2_PORT,
                 GATE_2_PIN,
                 DSY_GPIO_MODE_INPUT);

	/* p->gate_out.pin.port = GATE_OUT_PORT; */
	/* p->gate_out.pin.pin = GATE_OUT_PIN; */
	/* p->gate_out.mode = DSY_GPIO_MODE_OUTPUT_PP; */

    dsy_gpio_set(&p->gate_out,
                 GATE_OUT_PORT,
                 GATE_OUT_PIN,
                 DSY_GPIO_MODE_OUTPUT_PP);

	/* p->gate_out.pull = DSY_GPIO_NOPULL; */
    dsy_gpio_pull(&p->gate_out, DSY_GPIO_NOPULL);

	dsy_switch_init(&p->button1);
	dsy_switch_init(&p->button2);
	dsy_switch_init(&p->toggle);
	dsy_gpio_init(&p->gate_in1);
	dsy_gpio_init(&p->gate_in2);
	dsy_gpio_init(&p->gate_out);

	/* /\* ADC related *\/ */
    /* { */
    /*     uint8_t i; */
    /*     uint8_t channel_order[8] = { */
    /*         DSY_ADC_PIN_CHN3, */
    /*         DSY_ADC_PIN_CHN10, */
    /*         DSY_ADC_PIN_CHN7, */
    /*         DSY_ADC_PIN_CHN11, */
    /*         DSY_ADC_PIN_CHN4, */
    /*         DSY_ADC_PIN_CHN5, */
    /*         DSY_ADC_PIN_CHN15, */
    /*         DSY_ADC_PIN_CHN17 */
    /*     }; */
    /*     p->seed.adc_handle.channels = 8; */

    /*     for(i = 0; i < 8; i++) { */
    /*         p->seed.adc_handle.active_channels[i] = channel_order[i]; */
    /*     } */

    /*     dsy_adc_init(&p->seed.adc_handle); */
    /*     dsy_dac_init(&p->seed.dac_handle, DSY_DAC_CHN_BOTH); */
    /* } */
}

void daisy_patch_init(void)
{
    daisy_seed_init(&patch.seed);
    daisy_patch_init_(&patch);
}
