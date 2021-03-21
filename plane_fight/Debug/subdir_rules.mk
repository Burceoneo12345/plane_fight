################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"F:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="F:/ti/ccs1011/TivaWare_C_Series-2.1.0.12573" --include_path="F:/ti/ccs1011/TivaWare_C_Series-2.1.0.12573/work" --include_path="F:/ti/ccs1011/TivaWare_C_Series-2.1.0.12573/work/plane_fight/plane_fight/EPIinit" --include_path="F:/ti/ccs1011/TivaWare_C_Series-2.1.0.12573/work/plane_fight/plane_fight/TOUCHinit" --include_path="F:/ti/ccs1011/TivaWare_C_Series-2.1.0.12573/work/plane_fight/plane_fight" --include_path="F:/ti/ccs1011/TivaWare_C_Series-2.1.0.12573/work/plane_fight/plane_fight/TFTinit" --include_path="F:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --include_path="D:/CCS/final/circle of Sine_wave_TFT/EPIinit" --include_path="D:/CCS/final/circle of Sine_wave_TFT/TFTinit" --include_path="D:/CCS/final/circle of Sine_wave_TFT" -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --display_error_number --diag_wrap=off --diag_warning=225 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


