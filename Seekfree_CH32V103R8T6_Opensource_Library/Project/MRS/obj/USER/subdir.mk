################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Project/USER/isr.c \
C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Project/USER/main.c 

OBJS += \
./USER/isr.o \
./USER/main.o 

C_DEPS += \
./USER/isr.d \
./USER/main.d 


# Each subdirectory must supply rules for building sources it contributes
USER/isr.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Project/USER/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
USER/main.o: C:/Users/Accepted/Documents/smart_car/Seekfree_CH32V103R8T6_Opensource_Library/Project/USER/main.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\CODE" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Project\USER" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_libraries" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\seekfree_peripheral" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Core" -I"C:\Users\Accepted\Documents\smart_car\Seekfree_CH32V103R8T6_Opensource_Library\Libraries\wch_Libraries\Peripheral" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

