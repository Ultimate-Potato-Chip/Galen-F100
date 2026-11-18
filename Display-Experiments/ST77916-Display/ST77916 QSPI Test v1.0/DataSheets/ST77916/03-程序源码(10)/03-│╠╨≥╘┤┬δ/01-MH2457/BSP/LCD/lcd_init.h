#ifndef _LCD_INIT_H_
#define _LCD_INIT_H_

#include "bsp_qspi.h"

/* 端口定义 */
#define LCD_RES_CLK PeripheralGPIOA
#define LCD_RES_PORT GPIOA
#define LCD_RES_PIN GPIO_Pin_0

#define LCD_BLK_CLK PeripheralGPIOF
#define LCD_BLK_PORT GPIOF
#define LCD_BLK_PIN GPIO_Pin_6

#define LCD_RES_Set() GPIO_SetBits(LCD_RES_PORT, LCD_RES_PIN)
#define LCD_RES_Clr() GPIO_ResetBits(LCD_RES_PORT, LCD_RES_PIN)

#define LCD_BLK_Set() GPIO_SetBits(LCD_BLK_PORT, LCD_BLK_PIN)
#define LCD_BLK_Clr() GPIO_ResetBits(LCD_BLK_PORT, LCD_BLK_PIN)

/* 定义液晶显示方向 */
#define Display_Orientation 0 /* 0 默认显示方向 1旋转180度显示 2旋转90度显示 3旋转270度显示 */

#define LCD_W 360
#define LCD_H 360

/* 定义LCD指令格式 */
#define LCD_SingleAddr_SingleData 0x02
#define LCD_SingleAddr_QuadData 0x32
#define LCD_QuadAddr_QuadData 0x38


/* 函数声明 */
void LCD_GPIOInit(void);
void LCD_SingleCmdSingleData_DMA_TXA(uint8_t cmd, uint32_t addr, uint32_t len, uint8_t *buf);
void LCD_SingleCmdSingleData_DMA_TXB(uint8_t cmd, uint32_t addr, uint32_t len, uint16_t color);
void LCD_SingleCmdSingleData_DMA_TXC(uint8_t cmd, uint32_t addr, uint32_t len, uint16_t *buf);
void LCD_SingleCmdQuadData_DMA_TXA(uint8_t cmd, uint32_t addr, uint32_t len, uint8_t *buf);
void LCD_SingleCmdQuadData_DMA_TXB(uint8_t cmd, uint32_t addr, uint32_t len, uint16_t color);
void LCD_SingleCmdQuadData_DMA_TXC(uint8_t cmd, uint32_t addr, uint32_t len, uint16_t *buf);
void LCD_QuadCmdQuadData_DMA_TXA(uint8_t cmd, uint32_t addr, uint32_t len, uint8_t *buf);
void LCD_QuadCmdQuadData_DMA_TXB(uint8_t cmd, uint32_t addr, uint32_t len, uint16_t color);
void LCD_QuadCmdQuadData_DMA_TXC(uint8_t cmd, uint32_t addr, uint32_t len, uint16_t *buf);
void LCD_Address_Set(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye);
void LCD_Fill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color);
void LCD_ColorFill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t *color);
void LCD_Init(void);


/* 定义颜色参数 */
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40      /* 棕色 */
#define BRRED 0XFC07      /* 棕红色 */
#define GRAY 0X8430       /* 灰色 */
#define DARKBLUE 0X01CF   /* 深蓝色 */
#define LIGHTBLUE 0X7D7C  /* 浅蓝色 */
#define GRAYBLUE 0X5458   /* 灰蓝色 */
#define LIGHTGREEN 0X841F /* 浅绿色 */
#define LGRAY 0XC618      /* 浅灰色(PANNEL),窗体背景色 */
#define LGRAYBLUE 0XA651  /* 浅灰蓝色(中间层颜色) */
#define LBBLUE 0X2B12     /* 浅棕蓝色(选择条目的反色) */




#endif
