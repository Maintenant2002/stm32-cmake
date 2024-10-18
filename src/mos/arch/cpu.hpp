#ifndef _MOS_CPU_
#define _MOS_CPU_

#include "../config.h"

#if defined(MOS_ARCH_CORTEX_M4)
#include "mos_cortex_m4.hpp"
#endif

#if defined(MOS_ARCH_CORTEX_M7)
#include "mos_cortex_m7.hpp"
#endif

#if defined(MOS_ARCH_XXX)
#include "xxx.hpp"
#endif

#endif