TARGET = verb
CHIPSET = stm32h7x

FLASH_ADDRESS = 0x08000000

LIBDAISY_DIR = libdaisy

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
-I$(LIBDAISY_DIR)/Drivers/CMSIS/Include/ \
-I$(LIBDAISY_DIR)/Drivers/CMSIS/Device/ST/STM32H7xx/Include \
-I$(LIBDAISY_DIR)/Drivers/STM32H7xx_HAL_Driver/Inc/ \

ASFLAGS += $(MCU) -O2 -Wall -fdata-sections -ffunction-sections
CFLAGS += $(MCU) -O2 -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

LDSCRIPT = verb/STM32H750IB_flash.lds

LIBS = -ldaisy -lc -lm -lnosys
LDFLAGS += -L$(LIBDAISY_DIR)
LDFLAGS += $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBS) -Wl,--gc-sections

all: $(TARGET).elf $(TARGET).hex $(TARGET).bin

OBJ += $(addprefix verb/, reverbsc.o dcblock.o system_stm32h7xx.o verb.o)
OBJ += $(addprefix verb/, startup_stm32h750xx.o)

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
