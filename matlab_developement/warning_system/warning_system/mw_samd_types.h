/* Copyright 2023 The MathWorks, Inc. */
#ifndef __MW_SAMD_TYPES_H__
#define __MW_SAMD_TYPES_H__

#include "rtwtypes.h"
/* Pre-processor to get form Interrupt handler function prototype. */
#define MAKE_FN_NAME(x)   void x (void)
#define GETIRQ_NAME(signal) MAKE_FN_NAME(signal)

#define MW_IRQ_EXPAND_NAME(x) HWI_##x
#define MW_GET_IRQ_HANDLER_DEFINE(x)  MW_IRQ_EXPAND_NAME(x)
#define MW_EXPAND_DEFINED(x) defined(x)

#define DMA_BUFFER_SIZE_BYTE_ALLIGNED(numBytes,byteAlign) (((numBytes) + ((byteAlign) - 1)) & ~((byteAlign) - 1))

#endif
