################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Accepted/Documents/smart_car/HardCar/project/code/bluetooth.c \
C:/Users/Accepted/Documents/smart_car/HardCar/project/code/electro.c \
C:/Users/Accepted/Documents/smart_car/HardCar/project/code/imgproc.c \
C:/Users/Accepted/Documents/smart_car/HardCar/project/code/motor.c \
C:/Users/Accepted/Documents/smart_car/HardCar/project/code/pid.c \
C:/Users/Accepted/Documents/smart_car/HardCar/project/code/smotor.c 

OBJS += \
./code/bluetooth.o \
./code/electro.o \
./code/imgproc.o \
./code/motor.o \
./code/pid.o \
./code/smotor.o 

C_DEPS += \
./code/bluetooth.d \
./code/electro.d \
./code/imgproc.d \
./code/motor.d \
./code/pid.d \
./code/smotor.d 


# Each subdirectory must supply rules for building sources it contributes
code/bluetooth.o: C:/Users/Accepted/Documents/smart_car/HardCar/project/code/bluetooth.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/electro.o: C:/Users/Accepted/Documents/smart_car/HardCar/project/code/electro.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/imgproc.o: C:/Users/Accepted/Documents/smart_car/HardCar/project/code/imgproc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/motor.o: C:/Users/Accepted/Documents/smart_car/HardCar/project/code/motor.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/pid.o: C:/Users/Accepted/Documents/smart_car/HardCar/project/code/pid.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/smotor.o: C:/Users/Accepted/Documents/smart_car/HardCar/project/code/smotor.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

