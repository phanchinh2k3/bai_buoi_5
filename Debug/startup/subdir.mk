################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mcxa153.c 

C_DEPS += \
./startup/startup_mcxa153.d 

OBJS += \
./startup/startup_mcxa153.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MCXA153VLH -DCPU_MCXA153VLH_cm33_nodsp -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\MCUXpresso\CODE\bai5_gpio_input_interrupt\source" -I"D:\MCUXpresso\CODE\bai5_gpio_input_interrupt\drivers" -I"D:\MCUXpresso\CODE\bai5_gpio_input_interrupt\CMSIS" -I"D:\MCUXpresso\CODE\bai5_gpio_input_interrupt\CMSIS\m-profile" -I"D:\MCUXpresso\CODE\bai5_gpio_input_interrupt\device" -I"D:\MCUXpresso\CODE\bai5_gpio_input_interrupt\device\periph" -I"D:\MCUXpresso\CODE\bai5_gpio_input_interrupt\utilities" -I"D:\MCUXpresso\CODE\bai5_gpio_input_interrupt\utilities\str" -I"D:\MCUXpresso\CODE\bai5_gpio_input_interrupt\utilities\debug_console_lite" -I"D:\MCUXpresso\CODE\bai5_gpio_input_interrupt\component\uart" -I"D:\MCUXpresso\CODE\bai5_gpio_input_interrupt\board" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33+nodsp -c -ffunction-sections -fdata-sections -fno-builtin -imacros "D:\MCUXpresso\CODE\bai5_gpio_input_interrupt\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-startup

clean-startup:
	-$(RM) ./startup/startup_mcxa153.d ./startup/startup_mcxa153.o

.PHONY: clean-startup

