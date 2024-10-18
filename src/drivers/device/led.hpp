#ifndef _DEVICE_LED_
#define _DEVICE_LED_

#include "stm32h7xx_hal.h"

namespace Drivers::Device
{
    struct LED_t
    {
        using Port_t = GPIO_TypeDef&;
        using Raw_t = GPIO_TypeDef*;
        using Pint_t = const uint16_t;

        Port_t _port;
        Pint_t _pin;

        static inline constexpr GPIO_TypeDef&
		convert(Raw_t GPIOx) { return (GPIO_TypeDef&) (*GPIOx); }
        
        LED_t() = delete;

        LED_t(Port_t port, Pint_t pin)
            : _port(port), _pin(pin) {}

        LED_t(Raw_t GPIOx, Pint_t pin)
            : _port(convert(GPIOx)), _pin(pin) {}

        inline void init()
        {
            GPIO_InitTypeDef GPIO_InitStruct = {};
            GPIO_InitStruct.Pin = _pin;
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
            
            HAL_GPIO_Init(&_port, &GPIO_InitStruct);
            off();
        }

        inline void on()
        {
            HAL_GPIO_WritePin(&_port, _pin, GPIO_PIN_SET);
        }

        inline void off()
        {
            HAL_GPIO_WritePin(&_port, _pin, GPIO_PIN_RESET);
        }

        inline void toggle()
        {
            HAL_GPIO_TogglePin(&_port, _pin);
        }  
    };
    
} // namespace Drivers::Device

#endif
