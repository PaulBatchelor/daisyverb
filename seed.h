#ifndef DSY_SEED_H
#define DSY_SEED_H
typedef struct {
	dsy_sdram_handle_t sdram_handle;
	dsy_qspi_handle_t qspi_handle;
	dsy_sai_handle_t sai_handle;
	dsy_i2c_handle_t i2c1_handle, i2c2_handle;
	dsy_adc_handle_t adc_handle;
	dsy_dac_handle_t dac_handle;
	dsy_gpio_t led, testpoint;
} daisy_handle;

void daisy_seed_init(daisy_handle *daisy_seed);
void daisy_seed_init_adc(daisy_handle *daisy_seed);
#endif
