#ifndef _BSP_DMA_H_
#define _BSP_DMA_H_

#include "mh2457.h"

/* QSPI DMA定义 */
#define BSP_QSPI_DMA_BASE HSPI->DR
#define BSP_QSPI_DMA_CHANNEL DMA_Channel_0
#define BSP_QSPI_DMA_STREAM DMA2_Stream3
#define BSP_QSPI_DMA_TCIF DMA_IT_TCIF3

/* 函数声明 */
void BSP_QSPI_DMA_ConfigA(uint32_t cndtr, uint32_t *cmar);
void BSP_QSPI_DMA_ConfigB(uint32_t cndtr, uint32_t *cmar);
void BSP_QSPI_DMA_ConfigC(uint32_t cndtr, uint32_t *cmar);
void BSP_QSPI_DMA_TransmitEnable(void);
void BSP_QSPI_DMA_TransmitDisable(void);

#endif
