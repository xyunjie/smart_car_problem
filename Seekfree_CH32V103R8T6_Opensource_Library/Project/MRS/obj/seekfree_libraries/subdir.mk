################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/board.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/clock_config.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/common.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/misc.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_adc.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_camera.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_flash.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_gpio.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_nvic.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_pit.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_pwm.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_spi.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_systick.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_timer.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_uart.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_usb_cdc.c 

S_UPPER_SRCS += \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_irq.S 

OBJS += \
./seekfree_libraries/board.o \
./seekfree_libraries/clock_config.o \
./seekfree_libraries/common.o \
./seekfree_libraries/misc.o \
./seekfree_libraries/zf_adc.o \
./seekfree_libraries/zf_camera.o \
./seekfree_libraries/zf_flash.o \
./seekfree_libraries/zf_gpio.o \
./seekfree_libraries/zf_irq.o \
./seekfree_libraries/zf_nvic.o \
./seekfree_libraries/zf_pit.o \
./seekfree_libraries/zf_pwm.o \
./seekfree_libraries/zf_spi.o \
./seekfree_libraries/zf_systick.o \
./seekfree_libraries/zf_timer.o \
./seekfree_libraries/zf_uart.o \
./seekfree_libraries/zf_usb_cdc.o 

S_UPPER_DEPS += \
./seekfree_libraries/zf_irq.d 

C_DEPS += \
./seekfree_libraries/board.d \
./seekfree_libraries/clock_config.d \
./seekfree_libraries/common.d \
./seekfree_libraries/misc.d \
./seekfree_libraries/zf_adc.d \
./seekfree_libraries/zf_camera.d \
./seekfree_libraries/zf_flash.d \
./seekfree_libraries/zf_gpio.d \
./seekfree_libraries/zf_nvic.d \
./seekfree_libraries/zf_pit.d \
./seekfree_libraries/zf_pwm.d \
./seekfree_libraries/zf_spi.d \
./seekfree_libraries/zf_systick.d \
./seekfree_libraries/zf_timer.d \
./seekfree_libraries/zf_uart.d \
./seekfree_libraries/zf_usb_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
seekfree_libraries/board.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/board.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/clock_config.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/clock_config.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/common.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/common.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/misc.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/misc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/zf_adc.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/zf_camera.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_camera.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/zf_flash.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/zf_gpio.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/zf_irq.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_irq.S
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/zf_nvic.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_nvic.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/zf_pit.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_pit.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/zf_pwm.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_pwm.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/zf_spi.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/zf_systick.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_systick.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/zf_timer.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_timer.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/zf_uart.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
seekfree_libraries/zf_usb_cdc.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Libraries/seekfree_libraries/zf_usb_cdc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

