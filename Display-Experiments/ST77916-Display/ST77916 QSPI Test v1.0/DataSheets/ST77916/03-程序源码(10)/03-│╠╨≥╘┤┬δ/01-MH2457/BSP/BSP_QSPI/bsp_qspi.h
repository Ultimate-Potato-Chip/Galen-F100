#ifndef _BSP_QSPI_H_
#define _BSP_QSPI_H_

#include "mh2457.h"

/* 端口定义 */
#define BSP_QSPI_SCK_CLK PeripheralGPIOI
#define BSP_QSPI_SCK_PORT GPIOI
#define BSP_QSPI_SCK_PIN GPIO_Pin_9
#define BSP_QSPI_SCK_PINSOURCE GPIO_PinSource9
#define BSP_QSPI_SCK_AF GPIO_AF6_HSPI

#define BSP_QSPI_DATA0_CLK PeripheralGPIOI
#define BSP_QSPI_DATA0_PORT GPIOI
#define BSP_QSPI_DATA0_PIN GPIO_Pin_4
#define BSP_QSPI_DATA0_PINSOURCE GPIO_PinSource4
#define BSP_QSPI_DATA0_AF GPIO_AF6_HSPI

#define BSP_QSPI_DATA1_CLK PeripheralGPIOI
#define BSP_QSPI_DATA1_PORT GPIOI
#define BSP_QSPI_DATA1_PIN GPIO_Pin_5
#define BSP_QSPI_DATA1_PINSOURCE GPIO_PinSource5
#define BSP_QSPI_DATA1_AF GPIO_AF6_HSPI

#define BSP_QSPI_DATA2_CLK PeripheralGPIOI
#define BSP_QSPI_DATA2_PORT GPIOI
#define BSP_QSPI_DATA2_PIN GPIO_Pin_6
#define BSP_QSPI_DATA2_PINSOURCE GPIO_PinSource6
#define BSP_QSPI_DATA2_AF GPIO_AF6_HSPI

#define BSP_QSPI_DATA3_CLK PeripheralGPIOI
#define BSP_QSPI_DATA3_PORT GPIOI
#define BSP_QSPI_DATA3_PIN GPIO_Pin_7
#define BSP_QSPI_DATA3_PINSOURCE GPIO_PinSource7
#define BSP_QSPI_DATA3_AF GPIO_AF6_HSPI

#define BSP_QSPI_CS_CLK PeripheralGPIOI
#define BSP_QSPI_CS_PORT GPIOI
#define BSP_QSPI_CS_PIN GPIO_Pin_10
// #define BSP_QSPI_CS_PINSOURCE GPIO_PinSource10
// #define BSP_QSPI_CS_AF GPIO_AF6_HSPI

/* 定义端口电平状态 */
#define BSP_QSPI_CS_Set() GPIO_SetBits(BSP_QSPI_CS_PORT, BSP_QSPI_CS_PIN)
#define BSP_QSPI_CS_Clr() GPIO_ResetBits(BSP_QSPI_CS_PORT, BSP_QSPI_CS_PIN)

/* 函数声明 */
void BSP_QSPI_GPIOInit(void);
void BSP_QSPI_Init(void);
void BSP_QSPI_SingleLineSend(uint8_t cmd, uint32_t addr, uint32_t len, uint8_t *buf);
void BSP_QSPI_DualLineSend(uint8_t cmd, uint32_t addr, uint32_t len, uint8_t *buf);
void BSP_QSPI_QuadLineSend(uint8_t cmd, uint32_t addr, uint32_t len, uint8_t *buf);

#endif
