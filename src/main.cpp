#include "bsp.hpp"
#include "cpu.hpp"
#include "led.hpp"
#include "dwt.hpp"

int main()
{
    using namespace User;
    using namespace User::Global;
    using namespace HAL::STM32H7xx;
    
    BSP::config();
    DWT_Ext_Singleton& dwt = DWT_Ext_Singleton::get_instance();

    while (1)
    {
        for (auto& led : leds)
        {
            led.toggle();
        } 
        dwt.delay_us(500000);
    }
    
    return 0;
}