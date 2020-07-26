################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Clock.obj: A:/workSpace_CCS/RSLK_base/inc/Clock.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include" --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include/CMSIS" --include_path="A:/workSpace_CCS/RSLK_base/Motor_test" --include_path="A:/workSpace_CCS/RSLK_base/inc" --include_path="A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Clock.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Motor.obj: A:/workSpace_CCS/RSLK_base/inc/Motor.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include" --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include/CMSIS" --include_path="A:/workSpace_CCS/RSLK_base/Motor_test" --include_path="A:/workSpace_CCS/RSLK_base/inc" --include_path="A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Motor.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

PWM.obj: A:/workSpace_CCS/RSLK_base/inc/PWM.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include" --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include/CMSIS" --include_path="A:/workSpace_CCS/RSLK_base/Motor_test" --include_path="A:/workSpace_CCS/RSLK_base/inc" --include_path="A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="PWM.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Reflectance.obj: A:/workSpace_CCS/RSLK_base/inc/Reflectance.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include" --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include/CMSIS" --include_path="A:/workSpace_CCS/RSLK_base/Motor_test" --include_path="A:/workSpace_CCS/RSLK_base/inc" --include_path="A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Reflectance.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

UART0.obj: A:/workSpace_CCS/RSLK_base/inc/UART0.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include" --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include/CMSIS" --include_path="A:/workSpace_CCS/RSLK_base/Motor_test" --include_path="A:/workSpace_CCS/RSLK_base/inc" --include_path="A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="UART0.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include" --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include/CMSIS" --include_path="A:/workSpace_CCS/RSLK_base/Motor_test" --include_path="A:/workSpace_CCS/RSLK_base/inc" --include_path="A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_msp432p401r_ccs.obj: ../startup_msp432p401r_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include" --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include/CMSIS" --include_path="A:/workSpace_CCS/RSLK_base/Motor_test" --include_path="A:/workSpace_CCS/RSLK_base/inc" --include_path="A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="startup_msp432p401r_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

system_msp432p401r.obj: ../system_msp432p401r.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include" --include_path="A:/CCS_10/CCS/ccsv8/ccs_base/arm/include/CMSIS" --include_path="A:/workSpace_CCS/RSLK_base/Motor_test" --include_path="A:/workSpace_CCS/RSLK_base/inc" --include_path="A:/CCS_10/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="system_msp432p401r.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


