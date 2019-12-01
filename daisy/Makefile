TARGET = libdaisy
CHIPSET = stm32f7x

MODULES = \
codec_pcm3060 \
codec_wm8731 \
dsy_dma \
dsy_adc \
dsy_audio \
dsy_leddriver \
dsy_qspi \
dsy_sdram \
dsy_system \
dsy_i2c \
dsy_sai \
dsy_gpio \
dsy_dac \
dsy_switch \
system_stm32h7xx \

OPT = -O3

BUILD_DIR = build

C_SOURCES += $(addsuffix .c, $(MODULES))

C_SOURCES += \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usb.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_adc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_adc_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dac.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dac_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_fmc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sdram.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_opamp.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_opamp_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_qspi.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rng.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sai.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sai_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_sdmmc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_delayblock.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c \

OBJ += $(C_SOURCES:.c=.o)

STARTUP_PATH = Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/gcc

ASM_SOURCES = $(STARTUP_PATH)/startup_stm32h750xx.s

OBJ += $(ASM_SOURCES:.s=.o)

PREFIX = arm-none-eabi-

CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
AR = $(PREFIX)ar
GDB = $(PREFIX)gdb

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

CPU = -mcpu=cortex-m7

FPU = -mfpu=fpv5-d16

FLOAT-ABI = -mfloat-abi=hard

MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32H750xx \
-DUSE_HAL_DRIVER \
-DSTM32H750xx

C_INCLUDES = \
-IDrivers/CMSIS/Include \
-IDrivers/CMSIS/Device/ST/STM32H7xx/Include \
-IDrivers/STM32H7xx_HAL_Driver/Inc \
-I. \

ASFLAGS = $(MCU) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

LDSCRIPT = STM32H750IB_FLASH.lds

LIBS = lc -lm -lnosys

all: $(TARGET).a

# OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
# #vpath %.c $(sort $(dir $(C_SOURCES)))
# OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
#vpath %.s $(sort $(dir $(ASM_SOURCES)))

%.o: %.c
	$(CC) -c $(CFLAGS) -static $< -o $@
%.o: %.s
	$(AS) -c $(CFLAGS) $< -o $@

$(TARGET).a: $(OBJ)
	$(AR) rcs $@ $(OBJ)

$(BUILD_DIR):
	mkdir $@

clean:
	$(RM) -R $(BUILD_DIR)
	$(RM) -R $(OBJ)
