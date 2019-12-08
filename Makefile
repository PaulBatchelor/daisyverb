OBJ += reverbsc.o dcblock.o system_stm32h7xx.o verb.o
OBJ += patch.o
OBJ += startup_stm32h750xx.o

MODULES = \
pcm3060 \
wm8731 \
dma \
adc \
audio \
leddriver \
qspi \
sdram \
system \
i2c \
sai \
gpio \
dac \
switch \

C_SOURCES += $(addprefix daisy/, $(addsuffix .c, $(MODULES)))

C_SOURCES += \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usb.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_adc.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_adc_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dac.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dac_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_fmc.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sdram.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_opamp.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_opamp_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_qspi.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rng.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sai.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sai_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_sdmmc.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_delayblock.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c \
daisy/drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c \

OBJ += $(C_SOURCES:.c=.o)

STARTUP_PATH = daisy/drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/gcc

TARGET = verb
CHIPSET = stm32h7x

FLASH_ADDRESS = 0x08000000

LIBDAISY_DIR = daisy

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
-Icore/ \
-I$(LIBDAISY_DIR) \
-I$(LIBDAISY_DIR)/drivers/CMSIS/Include/ \
-I$(LIBDAISY_DIR)/drivers/CMSIS/Device/ST/STM32H7xx/Include \
-I$(LIBDAISY_DIR)/drivers/STM32H7xx_HAL_Driver/Inc/ \

ASFLAGS += $(MCU) -O2 -Wall -fdata-sections -ffunction-sections
CFLAGS += $(MCU) -O2 -Wall -fdata-sections -ffunction-sections

LDSCRIPT = STM32H750IB_flash.lds

LIBS = -lc -lm -lnosys
LDFLAGS += -L$(LIBDAISY_DIR)
LDFLAGS += $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBS) -Wl,--gc-sections

all: $(TARGET).elf $(TARGET).hex $(TARGET).bin

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) -c $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJ) Makefile
	$(CC) $(OBJ) $(LDFLAGS) -o $@
	$(SZ) $@

%.hex: %.elf
	$(HEX) $< $@

%.bin: %.elf
	$(BIN) $< $@

clean:
	$(RM) -r $(OBJ)
	$(RM) -r $(TARGET).bin
	$(RM) -r $(TARGET).hex
	$(RM) -r $(TARGET).elf

flash:
	dfu-util -a 0 -s $(FLASH_ADDRESS):leave -D $(TARGET).bin
