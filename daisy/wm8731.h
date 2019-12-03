#ifndef SA_DRIVERS_CODEC_H_
#define SA_DRIVERS_CODEC_H_

uint8_t codec_wm8731_init(I2C_HandleTypeDef *hi2c,
                          uint8_t mcu_is_master,
                          int32_t sample_rate,
                          uint8_t bitdepth);
uint8_t codec_wm8731_enter_bypass(I2C_HandleTypeDef *hi2c);
uint8_t codec_wm8731_exit_bypass(I2C_HandleTypeDef *hi2c);

#endif
