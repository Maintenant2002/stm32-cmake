#ifndef _HAL_DWT_
#define _HAL_DWT_

#include "stm32h7xx.h"

namespace HAL::STM32H7xx
{
    class DWT_Ext_Singleton
    {
    private:
        DWT_Type& _dwt;  // 唯一的 DWT_Type 实例

        // 私有构造函数，确保外部无法实例化该类
        DWT_Ext_Singleton() : _dwt(*DWT)
        {
            init();
        }

        // 禁用复制构造函数和赋值运算符
        DWT_Ext_Singleton(const DWT_Ext_Singleton&) = delete;
        DWT_Ext_Singleton& operator=(const DWT_Ext_Singleton&) = delete;

    public:
        // 获取唯一实例的静态方法
        static DWT_Ext_Singleton& get_instance()
        {
            static DWT_Ext_Singleton instance;  // 静态局部变量，确保唯一性
            return instance;
        }

        // 初始化 DWT
        void init()
        {
            if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk))
            {
                CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;  // 启用 DWT
            }
            _dwt.CYCCNT = 0;                       // 清除计数器
            _dwt.CTRL |= DWT_CTRL_CYCCNTENA_Msk;   // 启用 DWT 计数器
        }

        // 重置 DWT 计数器
        void reset()
        {
            _dwt.CYCCNT = 0;
        }

        // 获取周期计数
        uint32_t get_cycles() const
        {
            return _dwt.CYCCNT;
        }

        // 计算经过的时间（秒）
        float get_time_in_seconds() const
        {
            // SystemCoreClock为系统时间频率，定义在system_stm32h7xx.c中，是一个会变的全局变量
            return static_cast<float>(_dwt.CYCCNT) / SystemCoreClock;
        }

        // 关闭 DWT
        void deinit()
        {
            _dwt.CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
        }

        // 扩展功能：计算两次测量之间的差异
        uint32_t elapsed_cycles(uint32_t start_cycle) const
        {
            return _dwt.CYCCNT - start_cycle;
        }

        // 延时功能，单位是微秒
        void delay_us(uint32_t us)
        {
            // 计算目标延时对应的时钟周期数
            uint32_t start = _dwt.CYCCNT;
            uint32_t cycles_to_wait = us * (SystemCoreClock / 1'000'000);  // us 转换为时钟周期数
            
            // 等待计数器增加到目标值
            while ((_dwt.CYCCNT - start) < cycles_to_wait)
            {
                // 忙等待直到计数器达到目标
            }
        }
    };
    
}  // namespace HAL::STM32H7xx

#endif

