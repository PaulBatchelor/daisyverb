OBJ += reverbsc.o dcblock.o system_stm32h7xx.o verb.o
OBJ += patch.o
OBJ += seed.o
OBJ += startup_stm32h750xx.o

LIBDAISY_DIR = daisy

CSRCS += $(addprefix $(LIBDAISY_DIR)/, \
	pcm3060.c \
	wm8731.c \
	dma.c \
	adc.c \
	audio.c \
	leddriver.c \
	qspi.c \
	sdram.c \
	system.c \
	i2c.c \
	sai.c \
	gpio.c \
	dac.c \
	switch.c)

HAL_DIR = $(LIBDAISY_DIR)/drivers/STM32H7xx_HAL_Driver/Src/

CSRCS += $(addprefix $(HAL_DIR), \
	stm32h7xx_hal_pcd_ex.c \
	stm32h7xx_ll_usb.c \
	stm32h7xx_hal_adc.c \
	stm32h7xx_hal_adc_ex.c \
	stm32h7xx_hal_cortex.c \
	stm32h7xx_hal_dac.c \
	stm32h7xx_hal_dac_ex.c \
	stm32h7xx_ll_fmc.c \
	stm32h7xx_hal_sdram.c \
	stm32h7xx_hal_i2c.c \
	stm32h7xx_hal_i2c_ex.c \
	stm32h7xx_hal_opamp.c \
	stm32h7xx_hal_opamp_ex.c \
	stm32h7xx_hal_qspi.c \
	stm32h7xx_hal_rng.c \
	stm32h7xx_hal_sai.c \
	stm32h7xx_hal_sai_ex.c \
	stm32h7xx_ll_sdmmc.c \
	stm32h7xx_ll_delayblock.c \
	stm32h7xx_hal_sd.c \
	stm32h7xx_hal_sd_ex.c \
	stm32h7xx_hal_spi.c \
	stm32h7xx_hal_spi_ex.c \
	stm32h7xx_hal_tim.c \
	stm32h7xx_hal_tim_ex.c \
	stm32h7xx_hal_uart.c \
	stm32h7xx_hal_uart_ex.c \
	stm32h7xx_hal_rcc.c \
	stm32h7xx_hal_rcc_ex.c \
	stm32h7xx_hal_flash.c \
	stm32h7xx_hal_flash_ex.c \
	stm32h7xx_hal_gpio.c \
	stm32h7xx_hal_hsem.c \
	stm32h7xx_hal_dma.c \
	stm32h7xx_hal_dma_ex.c \
	stm32h7xx_hal_mdma.c \
	stm32h7xx_hal_pwr.c \
	stm32h7xx_hal_pwr_ex.c \
	stm32h7xx_hal.c)

OBJ += $(CSRCS:.c=.o)

TARGET = verb
CHIPSET = stm32h7x

FLASH_ADDRESS = 0x08000000

PREFIX = arm-none-eabi-

CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

CPU = -mcpu=cortex-m7
FPU = -mfpu=fpv5-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

CFLAGS +=  \
-DUSE_HAL_DRIVER \
-DSTM32H750xx \
-DUSE_HAL_DRIVER \
-DSTM32H750xx

CFLAGS += \
-I$(LIBDAISY_DIR) \
-I$(LIBDAISY_DIR)/drivers/CMSIS/Include/ \
-I$(LIBDAISY_DIR)/drivers/CMSIS/Device/ST/STM32H7xx/Include \
-I$(LIBDAISY_DIR)/drivers/STM32H7xx_HAL_Driver/Inc/ \

ASFLAGS += $(MCU) -O2 -Wall -fdata-sections -ffunction-sections
CFLAGS += $(MCU) -O2 -Wall -fdata-sections -ffunction-sections

# this shuts up warnings from stm32h7xx_hal_spi.c
CFLAGS += -Wno-strict-aliasing

CFLAGS += -pedantic

LDSCRIPT = STM32H750IB_flash.lds

LIBS = -lc -lm -lnosys
LDFLAGS += -L$(LIBDAISY_DIR)
LDFLAGS += $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBS)
LDFLAGS += -Wl,--gc-sections

all: $(TARGET).elf $(TARGET).hex $(TARGET).bin

%.o: %.c
	@echo "${CC} $(notdir $<)"
	@$(CC) -c $(CFLAGS) $< -o $@

%.o: %.s
	@echo "${AS} $(notdir $<)"
	@$(AS) -c $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJ)
	@echo "Creating $@"
	@$(CC) $(OBJ) $(LDFLAGS) -o $@
	@$(SZ) $@

%.hex: %.elf
	@$(HEX) $< $@

%.bin: %.elf
	@$(BIN) $< $@

clean:
	@$(RM) $(OBJ)
	@$(RM) $(TARGET).bin
	@$(RM) $(TARGET).hex
	@$(RM) $(TARGET).elf

flash:
	dfu-util -a 0 -s $(FLASH_ADDRESS):leave -D $(TARGET).bin
