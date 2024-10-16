cmake_minimum_required(VERSION 3.22)

project(stm32_hal)
add_library(stm32_hal INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(stm32_hal INTERFACE 
	USE_HAL_DRIVER
	STM32H743xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(stm32_hal INTERFACE
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Inc
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Inc/Legacy
    stm32_hal_drivers/CMSIS/Device/ST/STM32H7xx/Include
    stm32_hal_drivers/CMSIS/Include
)

target_sources(stm32_hal INTERFACE
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_eth.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_eth_ex.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd_ex.c
    stm32_hal_drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usb.c
    core/src/system_stm32h7xx.c
    core/src/sysmem.c
    core/src/syscalls.c
    init/startup_stm32h743xx.s
)

target_link_directories(stm32_hal INTERFACE
)

target_link_libraries(stm32_hal INTERFACE
)

# Validate that STM32_HAL code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()