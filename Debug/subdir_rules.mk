################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
KEY.obj: ../KEY.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="D:/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="D:/CCS/TivaWare_C_Series-2.1.0.12573" --include_path="D:/CCS/final/circle of Sine_wave_TFT/EPIinit" --include_path="D:/CCS/final/circle of Sine_wave_TFT/TFTinit" --include_path="D:/CCS/final/circle of Sine_wave_TFT" -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --display_error_number --diag_wrap=off --diag_warning=225 --preproc_with_compile --preproc_dependency="KEY.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Sine_wave.obj: ../Sine_wave.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="D:/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="D:/CCS/TivaWare_C_Series-2.1.0.12573" --include_path="D:/CCS/final/circle of Sine_wave_TFT/EPIinit" --include_path="D:/CCS/final/circle of Sine_wave_TFT/TFTinit" --include_path="D:/CCS/final/circle of Sine_wave_TFT" -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --display_error_number --diag_wrap=off --diag_warning=225 --preproc_with_compile --preproc_dependency="Sine_wave.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

tm4c1294ncpdt_startup_ccs.obj: ../tm4c1294ncpdt_startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="D:/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="D:/CCS/TivaWare_C_Series-2.1.0.12573" --include_path="D:/CCS/final/circle of Sine_wave_TFT/EPIinit" --include_path="D:/CCS/final/circle of Sine_wave_TFT/TFTinit" --include_path="D:/CCS/final/circle of Sine_wave_TFT" -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --display_error_number --diag_wrap=off --diag_warning=225 --preproc_with_compile --preproc_dependency="tm4c1294ncpdt_startup_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uartstdio.obj: ../uartstdio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="D:/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="D:/CCS/TivaWare_C_Series-2.1.0.12573" --include_path="D:/CCS/final/circle of Sine_wave_TFT/EPIinit" --include_path="D:/CCS/final/circle of Sine_wave_TFT/TFTinit" --include_path="D:/CCS/final/circle of Sine_wave_TFT" -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --display_error_number --diag_wrap=off --diag_warning=225 --preproc_with_compile --preproc_dependency="uartstdio.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


