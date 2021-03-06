#include "daisy.h"
#include "seed.h"

#define SEED_LED_PORT DSY_GPIOC
#define SEED_LED_PIN 7
#define SEED_TEST_POINT_PORT DSY_GPIOG
#define SEED_TEST_POINT_PIN 14

void daisy_seed_init(daisy_handle *daisy_seed)
{
	dsy_gpio_pin *pin_group;

	/* QSPI */
	daisy_seed->qspi_handle.device = DSY_QSPI_DEVICE_IS25LP064A;
	daisy_seed->qspi_handle.mode = DSY_QSPI_MODE_DSY_MEMORY_MAPPED;
	pin_group = daisy_seed->qspi_handle.pin_config;
	/* pin_group[DSY_QSPI_PIN_IO0].port = DSY_GPIOF; */
	/* pin_group[DSY_QSPI_PIN_IO0].pin = 8; */
    dsy_gpio_config_set(pin_group,
                        DSY_QSPI_PIN_IO0,
                        DSY_GPIOF,
                        8);

	/* pin_group[DSY_QSPI_PIN_IO1].port = DSY_GPIOF; */
	/* pin_group[DSY_QSPI_PIN_IO1].pin = 9; */

    dsy_gpio_config_set(pin_group,
                        DSY_QSPI_PIN_IO1,
                        DSY_GPIOF,
                        9);

	/* pin_group[DSY_QSPI_PIN_IO2].port = DSY_GPIOF; */
	/* pin_group[DSY_QSPI_PIN_IO2].pin = 7; */


    dsy_gpio_config_set(pin_group,
                        DSY_QSPI_PIN_IO2,
                        DSY_GPIOF,
                        7);

	/* pin_group[DSY_QSPI_PIN_IO3].port = DSY_GPIOF; */
	/* pin_group[DSY_QSPI_PIN_IO3].pin = 6; */

    dsy_gpio_config_set(pin_group,
                        DSY_QSPI_PIN_IO3,
                        DSY_GPIOF,
                        6);

	/* pin_group[DSY_QSPI_PIN_CLK].port = DSY_GPIOF; */
	/* pin_group[DSY_QSPI_PIN_CLK].pin = 10; */

    dsy_gpio_config_set(pin_group,
                        DSY_QSPI_PIN_CLK,
                        DSY_GPIOF,
                        10);

	/* pin_group[DSY_QSPI_PIN_NCS].port = DSY_GPIOG; */
	/* pin_group[DSY_QSPI_PIN_NCS].pin = 6; */

    dsy_gpio_config_set(pin_group,
                        DSY_QSPI_PIN_NCS,
                        DSY_GPIOG,
                        6);

	/* FMC */
	daisy_seed->sdram_handle.state = DSY_SDRAM_STATE_ENABLE;
	pin_group = daisy_seed->sdram_handle.pin_config;

	/* pin_group[DSY_SDRAM_PIN_SDNWE].port = DSY_GPIOH; */
	/* pin_group[DSY_SDRAM_PIN_SDNWE].pin = 5; */

    dsy_gpio_config_set(pin_group,
                        DSY_SDRAM_PIN_SDNWE,
                        DSY_GPIOH,
                        5);


	/* SAI - Serial Audio Interface */
	daisy_seed->sai_handle.init = DSY_AUDIO_INIT_BOTH;

	/* SAI1 - config */
	daisy_seed->sai_handle.device[DSY_SAI_1] = DSY_AUDIO_DEVICE_WM8731;
	daisy_seed->sai_handle.samplerate[DSY_SAI_1] = DSY_AUDIO_SAMPLERATE_48K;
	daisy_seed->sai_handle.bitdepth[DSY_SAI_1] = DSY_AUDIO_BITDEPTH_16;
	daisy_seed->sai_handle.sync_config[DSY_SAI_1] = DSY_AUDIO_SYNC_MASTER;
	pin_group = daisy_seed->sai_handle.sai1_pin_config;
	/* pin_group[DSY_SAI_PIN_MCLK].port = DSY_GPIOE; */
	/* pin_group[DSY_SAI_PIN_MCLK].pin = 2; */

    dsy_gpio_config_set(pin_group,
                        DSY_SAI_PIN_MCLK,
                        DSY_GPIOE,
                        2);

	/* pin_group[DSY_SAI_PIN_FS].port = DSY_GPIOE; */
	/* pin_group[DSY_SAI_PIN_FS].pin = 4; */

    dsy_gpio_config_set(pin_group,
                        DSY_SAI_PIN_FS,
                        DSY_GPIOE,
                        4);


	/* pin_group[DSY_SAI_PIN_SCK].port = DSY_GPIOE; */
	/* pin_group[DSY_SAI_PIN_SCK].pin = 5; */

    dsy_gpio_config_set(pin_group,
                        DSY_SAI_PIN_SCK,
                        DSY_GPIOE,
                        5);

	/* pin_group[DSY_SAI_PIN_SIN].port = DSY_GPIOE; */
	/* pin_group[DSY_SAI_PIN_SIN].pin = 6; */

    dsy_gpio_config_set(pin_group,
                        DSY_SAI_PIN_SIN,
                        DSY_GPIOE,
                        6);

	/* pin_group[DSY_SAI_PIN_SOUT].port = DSY_GPIOE; */
	/* pin_group[DSY_SAI_PIN_SOUT].pin = 3; */

    dsy_gpio_config_set(pin_group,
                        DSY_SAI_PIN_SOUT,
                        DSY_GPIOE,
                        3);

	/* SAI2 - config */
	daisy_seed->sai_handle.device[DSY_SAI_2] = DSY_AUDIO_DEVICE_WM8731;
	daisy_seed->sai_handle.samplerate[DSY_SAI_2] = DSY_AUDIO_SAMPLERATE_48K;
	daisy_seed->sai_handle.bitdepth[DSY_SAI_2] = DSY_AUDIO_BITDEPTH_16;
	daisy_seed->sai_handle.sync_config[DSY_SAI_2] = DSY_AUDIO_SYNC_SLAVE;
	pin_group = daisy_seed->sai_handle.sai2_pin_config;

	/* pin_group[DSY_SAI_PIN_MCLK].port = DSY_GPIOA; /\* unused *\/ */
	/* pin_group[DSY_SAI_PIN_MCLK].pin = 1; /\* ununsed *\/ */

    /* Unused */

    dsy_gpio_config_set(pin_group,
                        DSY_SAI_PIN_MCLK,
                        DSY_GPIOA,
                        1);

	/* pin_group[DSY_SAI_PIN_FS].port = DSY_GPIOG; */
	/* pin_group[DSY_SAI_PIN_FS].pin = 9; */

    dsy_gpio_config_set(pin_group,
                        DSY_SAI_PIN_FS,
                        DSY_GPIOG,
                        9);


	/* pin_group[DSY_SAI_PIN_SCK].port = DSY_GPIOA; */
	/* pin_group[DSY_SAI_PIN_SCK].pin = 2; */

    dsy_gpio_config_set(pin_group,
                        DSY_SAI_PIN_SCK,
                        DSY_GPIOA,
                        2);

	/* pin_group[DSY_SAI_PIN_SIN].port = DSY_GPIOD; */
	/* pin_group[DSY_SAI_PIN_SIN].pin = 11; */

    dsy_gpio_config_set(pin_group,
                        DSY_SAI_PIN_SIN,
                        DSY_GPIOD,
                        11);

	/* pin_group[DSY_SAI_PIN_SOUT].port = DSY_GPIOA; */
	/* pin_group[DSY_SAI_PIN_SOUT].pin = 0; */

    dsy_gpio_config_set(pin_group,
                        DSY_SAI_PIN_SOUT,
                        DSY_GPIOA,
                        0);

	/* I2C - Inter-Integrated Circuit */
	/* I2C 1 - controls the LED Driver and the WM8731. */
	daisy_seed->i2c1_handle.periph = DSY_I2C_PERIPH_1;
	daisy_seed->i2c1_handle.speed = DSY_I2C_SPEED_400KHZ;
	pin_group = daisy_seed->i2c1_handle.pin_config;

	/* pin_group[DSY_I2C_PIN_SCL].port = DSY_GPIOB; */
	/* pin_group[DSY_I2C_PIN_SCL].pin = 8; */

    dsy_gpio_config_set(pin_group,
                        DSY_I2C_PIN_SCL,
                        DSY_GPIOB,
                        8);

	/* pin_group[DSY_I2C_PIN_SDA].port = DSY_GPIOB; */
	/* pin_group[DSY_I2C_PIN_SDA].pin = 9; */

    dsy_gpio_config_set(pin_group,
                        DSY_I2C_PIN_SDA,
                        DSY_GPIOB,
                        9);

	/* I2C 2 - controls the on-board WM8731 on the Patch) */

	daisy_seed->i2c2_handle.periph = DSY_I2C_PERIPH_2;
	daisy_seed->i2c2_handle.speed = DSY_I2C_SPEED_400KHZ;
	pin_group = daisy_seed->i2c2_handle.pin_config;

	/* pin_group[DSY_I2C_PIN_SCL].port = DSY_GPIOH; */
	/* pin_group[DSY_I2C_PIN_SCL].pin = 4; */

    dsy_gpio_config_set(pin_group,
                        DSY_I2C_PIN_SCL,
                        DSY_GPIOH,
                        4);

	/* pin_group[DSY_I2C_PIN_SDA].port = DSY_GPIOB; */
	/* pin_group[DSY_I2C_PIN_SDA].pin = 11; */

    dsy_gpio_config_set(pin_group,
                        DSY_I2C_PIN_SDA,
                        DSY_GPIOB,
                        11);

	/* ADC */
	pin_group = daisy_seed->adc_handle.pin_config;

	/* pin_group[DSY_ADC_PIN_CHN3].port = DSY_GPIOA; */
	/* pin_group[DSY_ADC_PIN_CHN3].pin = 6; */

    dsy_gpio_config_set(pin_group,
                        DSY_ADC_PIN_CHN3,
                        DSY_GPIOA,
                        6);

	/* pin_group[DSY_ADC_PIN_CHN4].port = DSY_GPIOC; */
	/* pin_group[DSY_ADC_PIN_CHN4].pin = 5; */

    dsy_gpio_config_set(pin_group,
                        DSY_ADC_PIN_CHN4,
                        DSY_GPIOC,
                        5);

	/* pin_group[DSY_ADC_PIN_CHN5].port = DSY_GPIOB; */
	/* pin_group[DSY_ADC_PIN_CHN5].pin = 1; */

    dsy_gpio_config_set(pin_group,
                        DSY_ADC_PIN_CHN5,
                        DSY_GPIOB,
                        1);

	/* pin_group[DSY_ADC_PIN_CHN7].port = DSY_GPIOA; */
	/* pin_group[DSY_ADC_PIN_CHN7].pin = 7; */

    dsy_gpio_config_set(pin_group,
                        DSY_ADC_PIN_CHN7,
                        DSY_GPIOA,
                        7);

	/* pin_group[DSY_ADC_PIN_CHN10].port = DSY_GPIOC; */
	/* pin_group[DSY_ADC_PIN_CHN10].pin = 0; */

    dsy_gpio_config_set(pin_group,
                        DSY_ADC_PIN_CHN10,
                        DSY_GPIOC,
                        0);

	/* pin_group[DSY_ADC_PIN_CHN11].port = DSY_GPIOC; */
	/* pin_group[DSY_ADC_PIN_CHN11].pin = 1; */

    dsy_gpio_config_set(pin_group,
                        DSY_ADC_PIN_CHN11,
                        DSY_GPIOC,
                        1);

	/* pin_group[DSY_ADC_PIN_CHN15].port = DSY_GPIOA; */
	/* pin_group[DSY_ADC_PIN_CHN15].pin = 3; */

    dsy_gpio_config_set(pin_group,
                        DSY_ADC_PIN_CHN15,
                        DSY_GPIOA,
                        3);

	/* pin_group[DSY_ADC_PIN_CHN16].port = DSY_GPIOA; */
	/* pin_group[DSY_ADC_PIN_CHN16].pin = 0; */

    dsy_gpio_config_set(pin_group,
                        DSY_ADC_PIN_CHN16,
                        DSY_GPIOA,
                        0);

	/* pin_group[DSY_ADC_PIN_CHN17].port = DSY_GPIOA; */
	/* pin_group[DSY_ADC_PIN_CHN17].pin = 1; */

    dsy_gpio_config_set(pin_group,
                        DSY_ADC_PIN_CHN17,
                        DSY_GPIOA,
                        1);

	/* pin_group[DSY_ADC_PIN_CHN18].port = DSY_GPIOA; */
	/* pin_group[DSY_ADC_PIN_CHN18].pin = 4; */

    dsy_gpio_config_set(pin_group,
                        DSY_ADC_PIN_CHN18,
                        DSY_GPIOA,
                        4);

	/* pin_group[DSY_ADC_PIN_CHN19].port = DSY_GPIOA; */
	/* pin_group[DSY_ADC_PIN_CHN19].pin = 5; */

    dsy_gpio_config_set(pin_group,
                        DSY_ADC_PIN_CHN19,
                        DSY_GPIOA,
                        5);

	/* DAC */
	daisy_seed->dac_handle.mode = DSY_DAC_MODE_POLLING;
	daisy_seed->dac_handle.bitdepth = DSY_DAC_BITS_12;
	pin_group = daisy_seed->dac_handle.pin_config;

	/* pin_group[DSY_DAC_CHN1].port = DSY_GPIOA; */
	/* pin_group[DSY_DAC_CHN1].pin = 4; */

    dsy_gpio_config_set(pin_group,
                        DSY_DAC_CHN1,
                        DSY_GPIOA,
                        4);

	/* pin_group[DSY_DAC_CHN2].port = DSY_GPIOA; */
	/* pin_group[DSY_DAC_CHN2].pin = 5; */

    dsy_gpio_config_set(pin_group,
                        DSY_DAC_CHN2,
                        DSY_GPIOA,
                        5);

	/* GPIO */
	daisy_seed->led.pin.port = SEED_LED_PORT;
	daisy_seed->led.pin.pin = SEED_LED_PIN;
	daisy_seed->led.mode = DSY_GPIO_MODE_OUTPUT_PP;
	daisy_seed->testpoint.pin.port = SEED_TEST_POINT_PORT;
	daisy_seed->testpoint.pin.pin = SEED_TEST_POINT_PIN;
	daisy_seed->testpoint.mode = DSY_GPIO_MODE_OUTPUT_PP;

	/* System Initialization */

	dsy_system_init();
	dsy_sdram_init(&daisy_seed->sdram_handle);
	dsy_qspi_init(&daisy_seed->qspi_handle);
	dsy_gpio_init(&daisy_seed->led);
	dsy_gpio_init(&daisy_seed->testpoint);
	dsy_audio_init(&daisy_seed->sai_handle,
				   &daisy_seed->i2c2_handle,
				   &daisy_seed->i2c1_handle);

	/* ADC related */
    {
        uint8_t i;
        uint8_t channel_order[8] = {
            DSY_ADC_PIN_CHN3,
            DSY_ADC_PIN_CHN10,
            DSY_ADC_PIN_CHN7,
            DSY_ADC_PIN_CHN11,
            DSY_ADC_PIN_CHN4,
            DSY_ADC_PIN_CHN5,
            DSY_ADC_PIN_CHN15,
            DSY_ADC_PIN_CHN17
        };

        daisy_seed->adc_handle.channels = 8;

        for(i = 0; i < 8; i++) {
            daisy_seed->adc_handle.active_channels[i] = channel_order[i];
        }

        dsy_adc_init(&daisy_seed->adc_handle);
        dsy_dac_init(&daisy_seed->dac_handle, DSY_DAC_CHN_BOTH);
    }
}
