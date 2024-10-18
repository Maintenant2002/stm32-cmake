#include "bsp.hpp"
#include "kernel.hpp"
#include "led.hpp"

int main()
{
    using namespace User;
    using namespace User::Global;
    
    BSP::config();

    while (1)
    {
        for (auto& led : leds)
        {
            led.toggle();
        } 
        HAL_Delay(500);
    }
    
    return 0;
}