################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_absolute_encoder.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_aht20.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_bluetooth_ch9141.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_camera.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_dl1a.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_dm1xa.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_gps_tau1201.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_icm20602.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_imu660ra.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_imu963ra.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_ips114.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_ips200.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_k24c02.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_key.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_mpu6050.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_mt9v03x_dvp.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_oled.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_scc8660_dvp.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_tft180.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_type.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_virtual_oscilloscope.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_w25q32.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_wifi_uart.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_wireless_ch573.c \
C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_wireless_uart.c 

OBJS += \
./zf_device/zf_device_absolute_encoder.o \
./zf_device/zf_device_aht20.o \
./zf_device/zf_device_bluetooth_ch9141.o \
./zf_device/zf_device_camera.o \
./zf_device/zf_device_dl1a.o \
./zf_device/zf_device_dm1xa.o \
./zf_device/zf_device_gps_tau1201.o \
./zf_device/zf_device_icm20602.o \
./zf_device/zf_device_imu660ra.o \
./zf_device/zf_device_imu963ra.o \
./zf_device/zf_device_ips114.o \
./zf_device/zf_device_ips200.o \
./zf_device/zf_device_k24c02.o \
./zf_device/zf_device_key.o \
./zf_device/zf_device_mpu6050.o \
./zf_device/zf_device_mt9v03x_dvp.o \
./zf_device/zf_device_oled.o \
./zf_device/zf_device_scc8660_dvp.o \
./zf_device/zf_device_tft180.o \
./zf_device/zf_device_type.o \
./zf_device/zf_device_virtual_oscilloscope.o \
./zf_device/zf_device_w25q32.o \
./zf_device/zf_device_wifi_uart.o \
./zf_device/zf_device_wireless_ch573.o \
./zf_device/zf_device_wireless_uart.o 

C_DEPS += \
./zf_device/zf_device_absolute_encoder.d \
./zf_device/zf_device_aht20.d \
./zf_device/zf_device_bluetooth_ch9141.d \
./zf_device/zf_device_camera.d \
./zf_device/zf_device_dl1a.d \
./zf_device/zf_device_dm1xa.d \
./zf_device/zf_device_gps_tau1201.d \
./zf_device/zf_device_icm20602.d \
./zf_device/zf_device_imu660ra.d \
./zf_device/zf_device_imu963ra.d \
./zf_device/zf_device_ips114.d \
./zf_device/zf_device_ips200.d \
./zf_device/zf_device_k24c02.d \
./zf_device/zf_device_key.d \
./zf_device/zf_device_mpu6050.d \
./zf_device/zf_device_mt9v03x_dvp.d \
./zf_device/zf_device_oled.d \
./zf_device/zf_device_scc8660_dvp.d \
./zf_device/zf_device_tft180.d \
./zf_device/zf_device_type.d \
./zf_device/zf_device_virtual_oscilloscope.d \
./zf_device/zf_device_w25q32.d \
./zf_device/zf_device_wifi_uart.d \
./zf_device/zf_device_wireless_ch573.d \
./zf_device/zf_device_wireless_uart.d 


# Each subdirectory must supply rules for building sources it contributes
zf_device/zf_device_absolute_encoder.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_absolute_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_aht20.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_aht20.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_bluetooth_ch9141.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_bluetooth_ch9141.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_camera.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_camera.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_dl1a.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_dl1a.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_dm1xa.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_dm1xa.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_gps_tau1201.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_gps_tau1201.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_icm20602.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_icm20602.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_imu660ra.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_imu660ra.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_imu963ra.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_imu963ra.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_ips114.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_ips114.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_ips200.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_ips200.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_k24c02.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_k24c02.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_key.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_key.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_mpu6050.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_mpu6050.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_mt9v03x_dvp.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_mt9v03x_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_oled.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_oled.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_scc8660_dvp.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_scc8660_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_tft180.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_tft180.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_type.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_type.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_virtual_oscilloscope.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_virtual_oscilloscope.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_w25q32.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_w25q32.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_wifi_uart.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_wifi_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_wireless_ch573.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_wireless_ch573.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_wireless_uart.o: C:/Users/Accepted/Documents/smart_car/HardCar/libraries/zf_device/zf_device_wireless_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\Accepted\Documents\smart_car\HardCar\Libraries\doc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Core" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Ld" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Peripheral" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\sdk\Startup" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\user\inc" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_common" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_device" -I"C:\Users\Accepted\Documents\smart_car\HardCar\project\code" -I"C:\Users\Accepted\Documents\smart_car\HardCar\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

