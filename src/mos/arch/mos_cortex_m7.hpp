#ifndef _MOS_ARCH_CORTEX_M7_
#define _MOS_ARCH_CORTEX_M7_

#include "cpu.hpp"

#ifdef MOS_ARCH_CORTEX_M7

#include "stm32h7xx.h"  // 引用 STM32H7 的头文件
#include "core_cm7.h"   // 引用 Cortex-M7 内核的 CMSIS 头文件

// 重新定义硬件相关的操作
#define MOS_REBOOT()              NVIC_SystemReset()
#define MOS_TRIGGER_SVC_INTR()    asm volatile("svc    0")
#define MOS_TRIGGER_PENDSV_INTR() SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk
#define MOS_SVC_HANDLER           SVC_Handler
#define MOS_PENDSV_HANDLER        PendSV_Handler
#define MOS_SYSTICK_HANDLER       SysTick_Handler
#define MOS_TEST_IRQ()            __get_PRIMASK() == 0
#define MOS_DISABLE_IRQ()         asm volatile("cpsid i" : : : "memory")
#define MOS_ENABLE_IRQ()          asm volatile("cpsie i" : : : "memory")
#define MOS_NOP()                 asm volatile("nop")
#define MOS_DSB()                 __DSB()
#define MOS_ISB()                 __ISB()

// 从 FreeRTOS 中引用的架构初始化汇编代码
#define ARCH_INIT_ASM                                                        \
	"cpsid   i\n" /* 关闭中断 */                                            \
	"ldr     r3, =cur_tcb\n"                                                 \
	"ldr     r1, [r3]\n"                                                     \
	"ldr     r0, [r1,#8]\n"   /* r0 = cur_tcb.sp */                          \
	"ldmia   r0!, {r4-r11}\n" /* 弹出寄存器 R4-R11 (用户保存的上下文) */    \
	"msr     psp, r0\n"       /* 设置 PSP = cur_tcb.sp(新值) */              \
	"mov     r0, #0\n"                                                       \
	"orr     lr, #0xD\n" /* 切换到线程模式: 0xFFFF'FFFD */                  \
	"cpsie   i\n"        /* 开启中断 */                                     \
	"bx      lr\n"

// 从 FreeRTOS 中引用的上下文切换汇编代码
#define ARCH_CONTEXT_SWITCH_ASM                          \
	"cpsid   i\n" /* 关闭中断 */                        \
	"mrs     r0, psp\n"                                  \
	"ldr     r3, =cur_tcb\n"                             \
	"ldr     r2, [r3]\n"                                 \
	"stmdb   r0!, {r4-r11}\n" /* 保存内核寄存器 */      \
	"str     r0, [r2,#8]\n"   /* 获取 cur_tcb.sp */      \
	"stmdb   sp!, {r3,lr}\n"                             \
	"bl      next_tcb\n"                                 \
	"ldmia   sp!, {r3,lr}\n"                             \
	"ldr     r1, [r3]\n"                                 \
	"ldr     r0, [r1,#8]\n"   /* 获取 cur_tcb.sp(新值) */\
	"ldmia   r0!, {r4-r11}\n" /* 弹出内核寄存器 */      \
	"msr     psp, r0\n"                                  \
	"cpsie   i\n" /* 开启中断 */                         \
	"bx      lr\n"

// 跳转到上下文切换的指令
#define ARCH_JUMP_TO_CONTEXT_SWITCH "b    context_switch"

#endif

#endif
