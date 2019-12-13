#ifndef PATCH_H
#define PATCH_H
/* Order of ADC Channels for accessing adc.h */
enum {
	DSY_PATCH_KNOB_1,
	DSY_PATCH_KNOB_2,
	DSY_PATCH_KNOB_3,
	DSY_PATCH_KNOB_4,
	DSY_PATCH_CV_1,
	DSY_PATCH_CV_2,
	DSY_PATCH_CV_3,
	DSY_PATCH_CV_4,
	DSY_PATCH_CV_LAST
};

typedef struct {
	dsy_sdram_handle_t sdram_handle;
	dsy_qspi_handle_t qspi_handle;
	dsy_sai_handle_t sai_handle;
	dsy_i2c_handle_t i2c1_handle, i2c2_handle;
	dsy_adc_handle_t adc_handle;
	dsy_dac_handle_t dac_handle;
	dsy_gpio_t led, testpoint;
} daisy_handle;

typedef struct {
	dsy_switch_t button1, button2, toggle;
	dsy_gpio_t gate_in1, gate_in2, gate_out;
	daisy_handle seed;
} daisy_patch;

void daisy_patch_init(daisy_patch *p);
#endif
