#ifndef _USER_GLOBAL_
#define _USER_GLOBAL_

#include "led.hpp"

#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_1
#define LD2_GPIO_Port GPIOE
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB

namespace User::Global
{
    using namespace Drivers::Device;

    LED_t leds[] = {
        {LD1_GPIO_Port, LD1_Pin},
        {LD2_GPIO_Port, LD2_Pin},
        {LD3_GPIO_Port, LD3_Pin},
    };
}

#endif