################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/sdk/Core/core_riscv.c 

OBJS += \
./sdk/Core/core_riscv.o 

C_DEPS += \
./sdk/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Core/core_riscv.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/sdk/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

