################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ADC.obj: ../ADC.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/theo-/workspace_v7/codemsp2553" --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="ADC.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

capteurInfrarouge.obj: ../capteurInfrarouge.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/theo-/workspace_v7/codemsp2553" --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="capteurInfrarouge.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivermoteur.obj: ../drivermoteur.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/theo-/workspace_v7/codemsp2553" --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="drivermoteur.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/theo-/workspace_v7/codemsp2553" --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

scan.obj: ../scan.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/theo-/workspace_v7/codemsp2553" --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="scan.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

spi2553.obj: ../spi2553.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/theo-/workspace_v7/codemsp2553" --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="spi2553.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart.obj: ../uart.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/theo-/workspace_v7/codemsp2553" --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uart.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

util.obj: ../util.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/theo-/workspace_v7/codemsp2553" --include_path="C:/Program Files (x86)/ti/ccsv7/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="util.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


