// This is a Board Specific File
// I don't think it actually belongs in the library.
// Any new piece of hardware can just have their own board file.
// This will allow minor pin changes, etc. not to require changing the library in a million places.

/* #pragma once */
/* #ifndef DSY_SEED_H */
/* #define DSY_SEED_H */

/* #include "libdaisy.h" */

// Specifies whether generic initialization will be done within the daisy_seed_init, or not.
// Allows for more selective init
//#define DSY_SEED_NO_INIT 1

/* #define SEED_LED_PORT DSY_GPIOC */
/* #define SEED_LED_PIN 7 */

/* #define SEED_TEST_POINT_PORT DSY_GPIOG */
/* #define SEED_TEST_POINT_PIN 14 */

/* const dsy_gpio_port seed_ports[32] = */
/* { */
/* 	DSY_GPIOA, DSY_GPIOB, DSY_GPIOC, DSY_GPIOC, */
/* 	DSY_GPIOC, DSY_GPIOC, DSY_GPIOD, DSY_GPIOC, */
/* 	DSY_GPIOG, DSY_GPIOG, DSY_GPIOB, DSY_GPIOB, */
/* 	DSY_GPIOB, DSY_GPIOB, DSY_GPIOB, DSY_GPIOB, */
/* 	DSY_GPIOC, DSY_GPIOA, DSY_GPIOA, DSY_GPIOB, */
/* 	DSY_GPIOA, DSY_GPIOA, DSY_GPIOC, DSY_GPIOC, */
/* 	DSY_GPIOA, DSY_GPIOA, DSY_GPIOA, DSY_GPIOD, */
/* 	DSY_GPIOG, DSY_GPIOA, DSY_GPIOB, DSY_GPIOB, */
/* }; */

/* const uint8_t seed_pins[32] =  */
/* { */
/* 	8, 12, 11, 10, */
/* 	9, 8, 7, 12, */
/* 	10, 11, 4, 5,  */
/* 	8, 	9, 6, 7, */
/* 	0, 1, 3, 1,  */
/* 	7, 6, 1, 5, */
/* 	5, 4, 0, 11, */
/* 	9, 2, 14, 15, */
/* }; */


// Probably should move this to a dsy_handle.h
// So that it can be used in the other peripheral
// initializations, etc.
// (E.g. Audio needs both SAI, and I2C for most devices.)
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

/* #endif */
