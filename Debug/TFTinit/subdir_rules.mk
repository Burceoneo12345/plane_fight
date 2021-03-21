################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
TFTinit/TFT_400x240_OTM4001A_16bit.obj: ../TFTinit/TFT_400x240_OTM4001A_16bit.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="D:/CCS/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="D:/CCS/TivaWare_C_Series-2.1.0.12573" --include_path="D:/CCS/final/circle of Sine_wave_TFT/EPIinit" --include_path="D:/CCS/final/circle of Sine_wave_TFT/TFTinit" --include_path="D:/CCS/final/circle of Sine_wave_TFT" -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --display_error_number --diag_wrap=off --diag_warning=225 --preproc_with_compile --preproc_dependency="TFTinit/TFT_400x240_OTM4001A_16bit.d_raw" --obj_directory="TFTinit" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


