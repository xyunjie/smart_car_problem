################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Accepted/Documents/smart_car/HardCar/project/user/src/isr.c \
C:/Users/Accepted/Documents/smart_car/HardCar/project/user/src/main.c 

OBJS += \
./user_c/isr.o \
./user_c/main.o 

C_DEPS += \
./user_c/isr.d \
./user_c/main.d 


# Each subdirectory must supply rules for building sources it contributes
user_c/isr.o: C:/Users/Accepted/Documents/smart_car/HardCar/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: C:/Users/Accepted/Documents/smart_car/HardCar/project/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

