################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmsp -Ooff --use_hw_mpy=none --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/theo-/workspace_v7/codemsp2231" --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --define=__MSP430G2231__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pwmservo.obj: ../pwmservo.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmsp -Ooff --use_hw_mpy=none --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/theo-/workspace_v7/codemsp2231" --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --define=__MSP430G2231__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="pwmservo.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

spi2231.obj: ../spi2231.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmsp -Ooff --use_hw_mpy=none --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/theo-/workspace_v7/codemsp2231" --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --define=__MSP430G2231__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="spi2231.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

util.obj: ../util.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmsp -Ooff --use_hw_mpy=none --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/theo-/workspace_v7/codemsp2231" --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --define=__MSP430G2231__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="util.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


