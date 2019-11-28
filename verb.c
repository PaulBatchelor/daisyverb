#include "reverbsc.h"
#include "dcblock.h"
#include "libdaisy.h"

typedef struct
{
	dsy_sdram_handle_t sdram_handle;
	dsy_qspi_handle_t  qspi_handle;
	dsy_sai_handle_t   sai_handle;
	dsy_i2c_handle_t   i2c1_handle, i2c2_handle;
	dsy_adc_handle_t   adc_handle;
	dsy_dac_handle_t   dac_handle;
	dsy_gpio_t		   led, testpoint;
} daisy_handle;

#include "dsy_patch_bsp.h"
// Specifies whether generic initialization will be done within the daisy_seed_init, or not.
// Allows for more selective init
//#define DSY_SEED_NO_INIT 1

#define SEED_TEST_POINT_PORT DSY_GPIOG
#define SEED_TEST_POINT_PIN 14

const dsy_gpio_port seed_ports[32] =
{
	DSY_GPIOA, DSY_GPIOB, DSY_GPIOC, DSY_GPIOC,
	DSY_GPIOC, DSY_GPIOC, DSY_GPIOD, DSY_GPIOC,
	DSY_GPIOG, DSY_GPIOG, DSY_GPIOB, DSY_GPIOB,
	DSY_GPIOB, DSY_GPIOB, DSY_GPIOB, DSY_GPIOB,
	DSY_GPIOC, DSY_GPIOA, DSY_GPIOA, DSY_GPIOB,
	DSY_GPIOA, DSY_GPIOA, DSY_GPIOC, DSY_GPIOC,
	DSY_GPIOA, DSY_GPIOA, DSY_GPIOA, DSY_GPIOD,
	DSY_GPIOG, DSY_GPIOA, DSY_GPIOB, DSY_GPIOB,
};

const uint8_t seed_pins[32] = 
{
	8, 12, 11, 10,
	9, 8, 7, 12,
	10, 11, 4, 5, 
	8, 	9, 6, 7,
	0, 1, 3, 1, 
	7, 6, 1, 5,
	5, 4, 0, 11,
	9, 2, 14, 15,
};


/* // Probably should move this to a dsy_handle.h */
/* // So that it can be used in the other peripheral */
/* // initializations, etc. */
/* // (E.g. Audio needs both SAI, and I2C for most devices.) */
/* typedef struct */
/* { */
/* 	dsy_sdram_handle_t sdram_handle; */
/* 	dsy_qspi_handle_t  qspi_handle; */
/* 	dsy_sai_handle_t   sai_handle; */
/* 	dsy_i2c_handle_t   i2c1_handle, i2c2_handle; */
/* 	dsy_adc_handle_t   adc_handle; */
/* 	dsy_dac_handle_t   dac_handle; */
/* 	dsy_gpio_t		   led, testpoint; */
/* } daisy_handle; */

static daisy_patch patch;
static dsy_reverbsc_t verb;
static dsy_dcblock_t dcblock[2];
static float drylevel, send;
#define SEED_LED_PORT DSY_GPIOC
#define SEED_LED_PIN 7

void daisy_seed_init(daisy_handle *daisy_seed)
{
	dsy_gpio_pin *pin_group; // Pointer to an arbitrary group of pins.

	// QSPI
	daisy_seed->qspi_handle.device   = DSY_QSPI_DEVICE_IS25LP064A;
	daisy_seed->qspi_handle.mode	 = DSY_QSPI_MODE_DSY_MEMORY_MAPPED;
	pin_group						 = daisy_seed->qspi_handle.pin_config;
	pin_group[DSY_QSPI_PIN_IO0].port = DSY_GPIOF;
	pin_group[DSY_QSPI_PIN_IO0].pin  = 8;
	pin_group[DSY_QSPI_PIN_IO1].port = DSY_GPIOF;
	pin_group[DSY_QSPI_PIN_IO1].pin  = 9;
	pin_group[DSY_QSPI_PIN_IO2].port = DSY_GPIOF;
	pin_group[DSY_QSPI_PIN_IO2].pin  = 7;
	pin_group[DSY_QSPI_PIN_IO3].port = DSY_GPIOF;
	pin_group[DSY_QSPI_PIN_IO3].pin  = 6;
	pin_group[DSY_QSPI_PIN_CLK].port = DSY_GPIOF;
	pin_group[DSY_QSPI_PIN_CLK].pin  = 10;
	pin_group[DSY_QSPI_PIN_NCS].port = DSY_GPIOG;
	pin_group[DSY_QSPI_PIN_NCS].pin  = 6;

	// FMC
	daisy_seed->sdram_handle.state		= DSY_SDRAM_STATE_ENABLE;
	pin_group							= daisy_seed->sdram_handle.pin_config;
	pin_group[DSY_SDRAM_PIN_SDNWE].port = DSY_GPIOH;
	pin_group[DSY_SDRAM_PIN_SDNWE].pin  = 5;


	// SAI - Serial Audio Interface
	daisy_seed->sai_handle.init = DSY_AUDIO_INIT_BOTH;
	// SAI1 - config
	daisy_seed->sai_handle.device[DSY_SAI_1]	  = DSY_AUDIO_DEVICE_WM8731;
	daisy_seed->sai_handle.samplerate[DSY_SAI_1]  = DSY_AUDIO_SAMPLERATE_48K;
	daisy_seed->sai_handle.bitdepth[DSY_SAI_1]	= DSY_AUDIO_BITDEPTH_16;
	daisy_seed->sai_handle.sync_config[DSY_SAI_1] = DSY_AUDIO_SYNC_MASTER;
	pin_group						 = daisy_seed->sai_handle.sai1_pin_config;
	pin_group[DSY_SAI_PIN_MCLK].port = DSY_GPIOE;
	pin_group[DSY_SAI_PIN_MCLK].pin  = 2;
	pin_group[DSY_SAI_PIN_FS].port   = DSY_GPIOE;
	pin_group[DSY_SAI_PIN_FS].pin	= 4;
	pin_group[DSY_SAI_PIN_SCK].port  = DSY_GPIOE;
	pin_group[DSY_SAI_PIN_SCK].pin   = 5;
	pin_group[DSY_SAI_PIN_SIN].port  = DSY_GPIOE;
	pin_group[DSY_SAI_PIN_SIN].pin   = 6;
	pin_group[DSY_SAI_PIN_SOUT].port = DSY_GPIOE;
	pin_group[DSY_SAI_PIN_SOUT].pin  = 3;
	// SAI2 - config
	daisy_seed->sai_handle.device[DSY_SAI_2]	  = DSY_AUDIO_DEVICE_WM8731;
	daisy_seed->sai_handle.samplerate[DSY_SAI_2]  = DSY_AUDIO_SAMPLERATE_48K;
	daisy_seed->sai_handle.bitdepth[DSY_SAI_2]	= DSY_AUDIO_BITDEPTH_16;
	daisy_seed->sai_handle.sync_config[DSY_SAI_2] = DSY_AUDIO_SYNC_SLAVE;
	pin_group = daisy_seed->sai_handle.sai2_pin_config;
	pin_group[DSY_SAI_PIN_MCLK].port
		= DSY_GPIOA; // unused on daisy patch, but configurable
	pin_group[DSY_SAI_PIN_MCLK].pin
		= 1; // unused on daisy patch, but configurable
	pin_group[DSY_SAI_PIN_FS].port   = DSY_GPIOG;
	pin_group[DSY_SAI_PIN_FS].pin	= 9;
	pin_group[DSY_SAI_PIN_SCK].port  = DSY_GPIOA;
	pin_group[DSY_SAI_PIN_SCK].pin   = 2;
	pin_group[DSY_SAI_PIN_SIN].port  = DSY_GPIOD;
	pin_group[DSY_SAI_PIN_SIN].pin   = 11;
	pin_group[DSY_SAI_PIN_SOUT].port = DSY_GPIOA;
	pin_group[DSY_SAI_PIN_SOUT].pin  = 0;

	// I2C - Inter-Integrated Circuit
	// TODO: Add Config for I2C3 and I2C4
	// I2C 1 - (On daisy patch this controls the LED Driver, and the WM8731).
	daisy_seed->i2c1_handle.periph  = DSY_I2C_PERIPH_1;
	daisy_seed->i2c1_handle.speed   = DSY_I2C_SPEED_400KHZ;
	pin_group						= daisy_seed->i2c1_handle.pin_config;
	pin_group[DSY_I2C_PIN_SCL].port = DSY_GPIOB;
	pin_group[DSY_I2C_PIN_SCL].pin  = 8;
	pin_group[DSY_I2C_PIN_SDA].port = DSY_GPIOB;
	pin_group[DSY_I2C_PIN_SDA].pin  = 9;
	// I2C 2 - (On daisy patch this controls the on-board WM8731)
	daisy_seed->i2c2_handle.periph  = DSY_I2C_PERIPH_2;
	daisy_seed->i2c2_handle.speed   = DSY_I2C_SPEED_400KHZ;
	pin_group						= daisy_seed->i2c2_handle.pin_config;
	pin_group[DSY_I2C_PIN_SCL].port = DSY_GPIOH;
	pin_group[DSY_I2C_PIN_SCL].pin  = 4;
	pin_group[DSY_I2C_PIN_SDA].port = DSY_GPIOB;
	pin_group[DSY_I2C_PIN_SDA].pin  = 11;

	// ADC
	pin_group						  = daisy_seed->adc_handle.pin_config;
	pin_group[DSY_ADC_PIN_CHN3].port  = DSY_GPIOA;
	pin_group[DSY_ADC_PIN_CHN3].pin   = 6;
	pin_group[DSY_ADC_PIN_CHN4].port  = DSY_GPIOC;
	pin_group[DSY_ADC_PIN_CHN4].pin   = 5;
	pin_group[DSY_ADC_PIN_CHN5].port  = DSY_GPIOB;
	pin_group[DSY_ADC_PIN_CHN5].pin   = 1;
	pin_group[DSY_ADC_PIN_CHN7].port  = DSY_GPIOA;
	pin_group[DSY_ADC_PIN_CHN7].pin   = 7;
	pin_group[DSY_ADC_PIN_CHN10].port = DSY_GPIOC;
	pin_group[DSY_ADC_PIN_CHN10].pin  = 0;
	pin_group[DSY_ADC_PIN_CHN11].port = DSY_GPIOC;
	pin_group[DSY_ADC_PIN_CHN11].pin  = 1;
	pin_group[DSY_ADC_PIN_CHN15].port = DSY_GPIOA;
	pin_group[DSY_ADC_PIN_CHN15].pin  = 3;
	pin_group[DSY_ADC_PIN_CHN16].port = DSY_GPIOA;
	pin_group[DSY_ADC_PIN_CHN16].pin  = 0;
	pin_group[DSY_ADC_PIN_CHN17].port = DSY_GPIOA;
	pin_group[DSY_ADC_PIN_CHN17].pin  = 1;
	pin_group[DSY_ADC_PIN_CHN18].port = DSY_GPIOA;
	pin_group[DSY_ADC_PIN_CHN18].pin  = 4;
	pin_group[DSY_ADC_PIN_CHN19].port = DSY_GPIOA;
	pin_group[DSY_ADC_PIN_CHN19].pin  = 5;

	// DAC
	daisy_seed->dac_handle.mode		= DSY_DAC_MODE_POLLING;
	daisy_seed->dac_handle.bitdepth = DSY_DAC_BITS_12;
	pin_group						= daisy_seed->dac_handle.pin_config;
	pin_group[DSY_DAC_CHN1].port	= DSY_GPIOA;
	pin_group[DSY_DAC_CHN1].pin		= 4;
	pin_group[DSY_DAC_CHN2].port	= DSY_GPIOA;
	pin_group[DSY_DAC_CHN2].pin		= 5;

	// GPIO
	daisy_seed->led.pin.port	   = SEED_LED_PORT;
	daisy_seed->led.pin.pin		   = SEED_LED_PIN;
	daisy_seed->led.mode		   = DSY_GPIO_MODE_OUTPUT_PP;
	daisy_seed->testpoint.pin.port = SEED_TEST_POINT_PORT;
	daisy_seed->testpoint.pin.pin  = SEED_TEST_POINT_PIN;
	daisy_seed->testpoint.mode	 = DSY_GPIO_MODE_OUTPUT_PP;

	// System Initialization (optional)
#ifndef DSY_SEED_NO_INIT
	dsy_system_init();
	dsy_sdram_init(&daisy_seed->sdram_handle);
	dsy_qspi_init(&daisy_seed->qspi_handle);
	dsy_gpio_init(&daisy_seed->led);
	dsy_gpio_init(&daisy_seed->testpoint);
	dsy_audio_init(&daisy_seed->sai_handle,
				   &daisy_seed->i2c2_handle,
				   &daisy_seed->i2c1_handle);
#endif // DSY_SEED_NO_INIT
}

static void VerbCallback(float *in, float *out, size_t size)
{
    float dryL, dryR, wetL, wetR, sendL, sendR;
    for (size_t i = 0; i < size; i += 2)
    {
        verb.feedback = 0.15f + (dsy_adc_get_float(DSY_PATCH_KNOB_1) * 0.85f);
        verb.lpfreq = 200.0f + (dsy_adc_get_float(DSY_PATCH_KNOB_2) * 18000.0f);
        drylevel = dsy_adc_get_float(DSY_PATCH_KNOB_3);
        send = dsy_adc_get_float(DSY_PATCH_KNOB_4);
        dryL = in[i];
        dryR = in[i+1];
        sendL = dryL * send;
        sendR = dryR * send;
        dsy_reverbsc_process(&verb, &sendL, &sendR, &wetL, &wetR);
        wetL = dsy_dcblock_process(&dcblock[0], wetL);
        wetR = dsy_dcblock_process(&dcblock[1], wetR);
        out[i] = (dryL * drylevel) + wetL;
        out[i + 1] = (dryR * drylevel) + wetR;
    }
}

void daisy_patch_init(daisy_patch *p) 
{

	p->button1.pin_config.port = BUTTON_1_PORT;
	p->button1.pin_config.pin = BUTTON_1_PIN;
	p->button1.pull = DSY_SWITCH_PULLUP;
	p->button1.polarity		   = DSY_SWITCH_POLARITY_INVERTED;
	p->button1.type			   = DSY_SWITCH_TYPE_MOMENTARY;

	p->button2.pin_config.port = BUTTON_2_PORT;
	p->button2.pin_config.pin = BUTTON_2_PIN;
	p->button2.pull = DSY_SWITCH_PULLUP;
	p->button2.polarity		   = DSY_SWITCH_POLARITY_INVERTED;
	p->button2.type			   = DSY_SWITCH_TYPE_MOMENTARY;

	p->toggle.pin_config.port = TOGGLE_PORT;
	p->toggle.pin_config.pin = TOGGLE_PIN;
	p->toggle.pull = DSY_SWITCH_PULLUP;
	p->toggle.type			   = DSY_SWITCH_TYPE_TOGGLE;

	p->gate_in1.pin.port = GATE_1_PORT;
	p->gate_in1.pin.pin = GATE_1_PIN;
	p->gate_in1.mode	 = DSY_GPIO_MODE_INPUT;

	p->gate_in2.pin.port = GATE_2_PORT;
	p->gate_in2.pin.pin = GATE_2_PIN;
	p->gate_in2.mode	 = DSY_GPIO_MODE_INPUT;

	p->gate_out.pin.port = GATE_OUT_PORT;
	p->gate_out.pin.pin = GATE_OUT_PIN;
	p->gate_out.pull	 = DSY_GPIO_NOPULL;
	p->gate_out.mode	 = DSY_GPIO_MODE_OUTPUT_PP;

	dsy_switch_init(&p->button1);
	dsy_switch_init(&p->button2);
	dsy_switch_init(&p->toggle);
	dsy_gpio_init(&p->gate_in1);
	dsy_gpio_init(&p->gate_in2);
	dsy_gpio_init(&p->gate_out);
	// ADC related
	uint8_t channel_order[8]		  = {DSY_ADC_PIN_CHN3,
								 DSY_ADC_PIN_CHN10,
								 DSY_ADC_PIN_CHN7,
								 DSY_ADC_PIN_CHN11,
								 DSY_ADC_PIN_CHN4,
								 DSY_ADC_PIN_CHN5,
								 DSY_ADC_PIN_CHN15,
								 DSY_ADC_PIN_CHN17};
	p->seed.adc_handle.channels
		= 8; // only initializing 8 primary channels.
	for(uint8_t i = 0; i < 8; i++)
	{
		p->seed.adc_handle.active_channels[i] = channel_order[i];
	}
	dsy_adc_init(&p->seed.adc_handle);
	dsy_dac_init(&p->seed.dac_handle, DSY_DAC_CHN_BOTH);
}


int main(void)
{
    daisy_seed_init(&patch.seed);
    daisy_patch_init(&patch);
    dsy_reverbsc_init(&verb, DSY_AUDIO_SAMPLE_RATE);
    dsy_dcblock_init(&dcblock[0], DSY_AUDIO_SAMPLE_RATE);
    dsy_dcblock_init(&dcblock[1], DSY_AUDIO_SAMPLE_RATE);
    dsy_audio_set_callback(DSY_AUDIO_INTERNAL, VerbCallback);
    dsy_adc_start();
    dsy_audio_start(DSY_AUDIO_INTERNAL);
    while(1) {}
}
