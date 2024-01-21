################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Accepted/Documents/smart_car/TripperCar/libraries/zf_common/zf_common_clock.c \
C:/Users/Accepted/Documents/smart_car/TripperCar/libraries/zf_common/zf_common_debug.c \
C:/Users/Accepted/Documents/smart_car/TripperCar/libraries/zf_common/zf_common_fifo.c \
C:/Users/Accepted/Documents/smart_car/TripperCar/libraries/zf_common/zf_common_font.c \
C:/Users/Accepted/Documents/smart_car/TripperCar/libraries/zf_common/zf_common_function.c \
C:/Users/Accepted/Documents/smart_car/TripperCar/libraries/zf_common/zf_common_interrupt.c 

OBJS += \
./zf_common/zf_common_clock.o \
./zf_common/zf_common_debug.o \
./zf_common/zf_common_fifo.o \
./zf_common/zf_common_font.o \
./zf_common/zf_common_function.o \
./zf_common/zf_common_interrupt.o 

C_DEPS += \
./zf_common/zf_common_clock.d \
./zf_common/zf_common_debug.d \
./zf_common/zf_common_fifo.d \
./zf_common/zf_common_font.d \
./zf_common/zf_common_function.d \
./zf_common/zf_common_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
zf_common/zf_common_clock.o: C:/Users/Accepted/Documents/smart_car/TripperCar/libraries/zf_common/zf_common_clock.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\TripperCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_debug.o: C:/Users/Accepted/Documents/smart_car/TripperCar/libraries/zf_common/zf_common_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\TripperCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_fifo.o: C:/Users/Accepted/Documents/smart_car/TripperCar/libraries/zf_common/zf_common_fifo.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\TripperCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_font.o: C:/Users/Accepted/Documents/smart_car/TripperCar/libraries/zf_common/zf_common_font.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\TripperCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_function.o: C:/Users/Accepted/Documents/smart_car/TripperCar/libraries/zf_common/zf_common_function.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\TripperCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_interrupt.o: C:/Users/Accepted/Documents/smart_car/TripperCar/libraries/zf_common/zf_common_interrupt.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\TripperCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\TripperCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

