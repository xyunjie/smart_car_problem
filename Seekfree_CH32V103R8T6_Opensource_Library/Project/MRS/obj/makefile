################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include wch_Libraries/Startup/subdir.mk
-include wch_Libraries/Peripheral/subdir.mk
-include wch_Libraries/Core/subdir.mk
-include seekfree_peripheral/subdir.mk
-include seekfree_libraries/subdir.mk
-include USER/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Seekfree_CH32V103R8T6_Opensource_Library.hex \

SECONDARY_LIST += \
Seekfree_CH32V103R8T6_Opensource_Library.lst \

SECONDARY_SIZE += \
Seekfree_CH32V103R8T6_Opensource_Library.siz \


# 所有目标
all: Seekfree_CH32V103R8T6_Opensource_Library.elf secondary-outputs

# 工具调用
Seekfree_CH32V103R8T6_Opensource_Library.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -Wl,-Map,"Seekfree_CH32V103R8T6_Opensource_Library.map" --specs=nano.specs --specs=nosys.specs -o "Seekfree_CH32V103R8T6_Opensource_Library.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
Seekfree_CH32V103R8T6_Opensource_Library.hex: Seekfree_CH32V103R8T6_Opensource_Library.elf
	@	riscv-none-embed-objcopy -O ihex "Seekfree_CH32V103R8T6_Opensource_Library.elf"  "Seekfree_CH32V103R8T6_Opensource_Library.hex"
	@	@
Seekfree_CH32V103R8T6_Opensource_Library.lst: Seekfree_CH32V103R8T6_Opensource_Library.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "Seekfree_CH32V103R8T6_Opensource_Library.elf" > "Seekfree_CH32V103R8T6_Opensource_Library.lst"
	@	@
Seekfree_CH32V103R8T6_Opensource_Library.siz: Seekfree_CH32V103R8T6_Opensource_Library.elf
	@	riscv-none-embed-size --format=berkeley "Seekfree_CH32V103R8T6_Opensource_Library.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) Seekfree_CH32V103R8T6_Opensource_Library.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
