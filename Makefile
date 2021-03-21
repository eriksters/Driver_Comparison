SHELL=F:\Program Files\Git\bin\sh.exe
CC=arm-none-eabi-gcc

########	Files/Folders	########
OBJ_DIR = obj

C_INCLUDES = \
-Iinc \
-IDrivers/CMSIS/Include \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy

AS_INCLUDES = 

C_SOURCE_DIRS = \
src \
Drivers/STM32F4xx_HAL_Driver/Src

ASM_SOURCE_DIRS = \
.

C_SOURCES = $(foreach dir, $(C_SOURCE_DIRS), $(wildcard $(dir)/*.c))
ASM_SOURCES = $(foreach dir, $(ASM_SOURCE_DIRS), $(wildcard $(dir)/*.s))

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.c,%.o,$(C_SOURCES))))
OBJ += $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.s,%.o,$(ASM_SOURCES))))

LD=Link.ld


########	Hardware	########
CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard

MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)


########	Compilation		########
C_DEFS = \
-DSTM32F469xx \
-DUSE_HAL_DRIVER

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -c -O0 -g
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -c -O0 -g 
LDFLAGS = $(MCU) -T$(LD) -Wl,-Map=$(OBJ_DIR)/Out.map,--cref -Wl,--gc-sections -O0 -g


########	Rules	########
vpath %.c $(C_SOURCE_DIRS)
vpath %.s $(ASM_SOURCE_DIRS)

all: $(OBJ)
	$(CC) $(LDFLAGS) -o $(OBJ_DIR)/Out.elf $(OBJ)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.s
	$(CC) $(ASFLAGS) -o $@ $^

clean:
	rm ./obj/* -f
