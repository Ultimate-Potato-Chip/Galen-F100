#include "lcd_init.h"
#include "bsp_dma.h"

/* 定义初始化序列最大传输长度 */
#define MAX_DATA_LEN 36

/* 定义初始化序列结构体 */
typedef struct
{
    uint8_t reg;
    uint8_t data[MAX_DATA_LEN];
    uint8_t len;
} lcd_init_t;

/* 液晶初始化序列 */
static const lcd_init_t LCD_InitTable[] = {
    {0xF0,{0x28},1},
    {0xF2,{0x28},1},
    {0x73,{0xF0},1},
    {0x7C,{0xD1},1},
    {0x83,{0xE0},1},
    {0x84,{0x61},1},
    {0xF2,{0x82},1},
    {0xF0,{0x00},1},
    {0xF0,{0x01},1},
    {0xF1,{0x01},1},
    {0xB0,{0x69},1},
    {0xB1,{0x4A},1},
    {0xB2,{0x2F},1},
    {0xB3,{0x01},1},
    {0xB4,{0x69},1},
    {0xB5,{0x45},1},
    {0xB6,{0xAB},1},
    {0xB7,{0x41},1},
    {0xB8,{0x86},1},
    {0xB9,{0x15},1},
    {0xBA,{0x00},1},
    {0xBB,{0x08},1},
    {0xBC,{0x08},1},
    {0xBD,{0x00},1},
    {0xBE,{0x00},1},
    {0xBF,{0x07},1},
    {0xC0,{0x80},1},
    {0xC1,{0x10},1},
    {0xC2,{0x37},1},
    {0xC3,{0x80},1},
    {0xC4,{0x10},1},
    {0xC5,{0x37},1},
    {0xC6,{0xA9},1},
    {0xC7,{0x41},1},
    {0xC8,{0x01},1},
    {0xC9,{0xA9},1},
    {0xCA,{0x41},1},
    {0xCB,{0x01},1},
    {0xCC,{0x7F},1},
    {0xCD,{0x7F},1},
    {0xCE,{0xFF},1},
    {0xD0,{0x91},1},
    {0xD1,{0x68},1},
    {0xD2,{0x68},1},
    {0xF5,{0x00,0xA5},2},
    {0xF1,{0x10},1},
    {0xF0,{0x00},1},
    {0xF0,{0x02},1},
    {0xE0,{0xF0,0x10,0x18,0x0D,0x0C,0x38,0x3E,0x44,0x51,0x39,0x15,0x15,0x30,0x34},14},
    {0xE1,{0xF0,0x0F,0x17,0x0D,0x0B,0x07,0x3E,0x33,0x51,0x39,0x15,0x15,0x30,0x34},14},
    {0xF0,{0x10},1},
    {0xF3,{0x10},1},
    {0xE0,{0x08},1},
    {0xE1,{0x00},1},
    {0xE2,{0x00},1},
    {0xE3,{0x00},1},
    {0xE4,{0xE0},1},
    {0xE5,{0x06},1},
    {0xE6,{0x21},1},
    {0xE7,{0x03},1},
    {0xE8,{0x05},1},
    {0xE9,{0x02},1},
    {0xEA,{0xE9},1},
    {0xEB,{0x00},1},
    {0xEC,{0x00},1},
    {0xED,{0x14},1},
    {0xEE,{0xFF},1},
    {0xEF,{0x00},1},
    {0xF8,{0xFF},1},
    {0xF9,{0x00},1},
    {0xFA,{0x00},1},
    {0xFB,{0x30},1},
    {0xFC,{0x00},1},
    {0xFD,{0x00},1},
    {0xFE,{0x00},1},
    {0xFF,{0x00},1},
    {0x60,{0x40},1},
    {0x61,{0x05},1},
    {0x62,{0x00},1},
    {0x63,{0x42},1},
    {0x64,{0xDA},1},
    {0x65,{0x00},1},
    {0x66,{0x00},1},
    {0x67,{0x00},1},
    {0x68,{0x00},1},
    {0x69,{0x00},1},
    {0x6A,{0x00},1},
    {0x6B,{0x00},1},
    {0x70,{0x40},1},
    {0x71,{0x04},1},
    {0x72,{0x00},1},
    {0x73,{0x42},1},
    {0x74,{0xD9},1},
    {0x75,{0x00},1},
    {0x76,{0x00},1},
    {0x77,{0x00},1},
    {0x78,{0x00},1},
    {0x79,{0x00},1},
    {0x7A,{0x00},1},
    {0x7B,{0x00},1},
    {0x80,{0x48},1},
    {0x81,{0x00},1},
    {0x82,{0x07},1},
    {0x83,{0x02},1},
    {0x84,{0xD7},1},
    {0x85,{0x04},1},
    {0x86,{0x00},1},
    {0x87,{0x00},1},
    {0x88,{0x48},1},
    {0x89,{0x00},1},
    {0x8A,{0x09},1},
    {0x8B,{0x02},1},
    {0x8C,{0xD9},1},
    {0x8D,{0x04},1},
    {0x8E,{0x00},1},
    {0x8F,{0x00},1},
    {0x90,{0x48},1},
    {0x91,{0x00},1},
    {0x92,{0x0B},1},
    {0x93,{0x02},1},
    {0x94,{0xDB},1},
    {0x95,{0x04},1},
    {0x96,{0x00},1},
    {0x97,{0x00},1},
    {0x98,{0x48},1},
    {0x99,{0x00},1},
    {0x9A,{0x0D},1},
    {0x9B,{0x02},1},
    {0x9C,{0xDD},1},
    {0x9D,{0x04},1},
    {0x9E,{0x00},1},
    {0x9F,{0x00},1},
    {0xA0,{0x48},1},
    {0xA1,{0x00},1},
    {0xA2,{0x06},1},
    {0xA3,{0x02},1},
    {0xA4,{0xD6},1},
    {0xA5,{0x04},1},
    {0xA6,{0x00},1},
    {0xA7,{0x00},1},
    {0xA8,{0x48},1},
    {0xA9,{0x00},1},
    {0xAA,{0x08},1},
    {0xAB,{0x02},1},
    {0xAC,{0xD8},1},
    {0xAD,{0x04},1},
    {0xAE,{0x00},1},
    {0xAF,{0x00},1},
    {0xB0,{0x48},1},
    {0xB1,{0x00},1},
    {0xB2,{0x0A},1},
    {0xB3,{0x02},1},
    {0xB4,{0xDA},1},
    {0xB5,{0x04},1},
    {0xB6,{0x00},1},
    {0xB7,{0x00},1},
    {0xB8,{0x48},1},
    {0xB9,{0x00},1},
    {0xBA,{0x0C},1},
    {0xBB,{0x02},1},
    {0xBC,{0xDC},1},
    {0xBD,{0x04},1},
    {0xBE,{0x00},1},
    {0xBF,{0x00},1},
    {0xC0,{0x10},1},
    {0xC1,{0x47},1},
    {0xC2,{0x56},1},
    {0xC3,{0x65},1},
    {0xC4,{0x74},1},
    {0xC5,{0x88},1},
    {0xC6,{0x99},1},
    {0xC7,{0x01},1},
    {0xC8,{0xBB},1},
    {0xC9,{0xAA},1},
    {0xD0,{0x10},1},
    {0xD1,{0x47},1},
    {0xD2,{0x56},1},
    {0xD3,{0x65},1},
    {0xD4,{0x74},1},
    {0xD5,{0x88},1},
    {0xD6,{0x99},1},
    {0xD7,{0x01},1},
    {0xD8,{0xBB},1},
    {0xD9,{0xAA},1},
    {0xF3,{0x01},1},
    {0xF0,{0x00},1},
    #if(Display_Orientation==0)
    {0x36, {0x00}, 1},
    #elif(Display_Orientation==1)
    {0x36, {0xC0}, 1},
    #elif(Display_Orientation==2)
    {0x36, {0x60}, 1},
    #elif(Display_Orientation==3)
    {0x36, {0xA0}, 1},
    #endif
    {0x3A, {0x05}, 1},
    {0x35, {0x00}, 1},
    {0x21, {0x00}, 0},
    {0x11, {0x00}, 0},
    {0xff, {120}, 1},
    {0x29, {0x00}, 0},
    {0x2C, {0x00}, 0},
};

/**
 * @brief       端口初始化
 * @param       无
 * @retval      无
 */
void LCD_GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    PeripheralEnable(LCD_RES_CLK, ENABLE);
    PeripheralEnable(LCD_BLK_CLK, ENABLE);

    /* 配置端口工作模式 */
    GPIO_InitStructure.GPIO_Pin = LCD_RES_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(LCD_RES_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_BLK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(LCD_BLK_PORT, &GPIO_InitStructure);
}

/**
 * @brief       QSPI单线命令单线数据DMA模式A发送数据
 * @param       cmd:指令
 * @param       addr:地址
 * @param       len:数据长度
 * @param       buf:数据缓冲区地址
 * @retval      无
 */
void LCD_SingleCmdSingleData_DMA_TXA(uint8_t cmd, uint32_t addr, uint32_t len, uint8_t *buf)
{
    uint16_t i = 0;
    uint8_t cmd_bytesize = 1;  /* 存储指令长度 */
    uint8_t addr_bytesize = 3; /* 存储地址长度 */
    uint8_t loadbuf[4];
    HSPI_StandardSpiDef QSPI_SingleInitStructure = {0};
    BSP_QSPI_CS_Set();                                          /* 拉高片选 */
    HSPI_Cmd(DISABLE);                                          /* 失能QSPI */
    QSPI_SingleInitStructure.CKMode = HSPI_STANDARDSPI_CKMODE3; /* 配置QSPI 时钟相位 时钟极性 */
    QSPI_SingleInitStructure.Rx_NumberDFrame = 0;
    QSPI_SingleInitStructure.Transfer_Mode = HSPI_SandardSPI_Tx;             /* 配置QSPI 单线工作模式 */
    QSPI_SingleInitStructure.Tx_NumberDFrame = cmd_bytesize + addr_bytesize; /* 配置QSPI 发送字节长度 */
    HSPI_StandardSPI_Config(&QSPI_SingleInitStructure);
    HSPI_DataFrameSizeConfig(HSPI_DFS_8); /* 配置传输数据帧为字节 */
    HSPI_Cmd(ENABLE);                     /* 使能QSPI */
    BSP_QSPI_CS_Clr();                    /* 拉低片选 */
    loadbuf[0] = cmd;
    loadbuf[1] = 0x00;
    loadbuf[2] = (addr & 0xFF);
    loadbuf[3] = 0x00;
    for (i = 0; i < cmd_bytesize + addr_bytesize; i++)
    {
        while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
        HSPI_SendData(loadbuf[i]);
    }
    while (HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET || HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET); /* 发送指令数据 */
    if (len != 0)
    {
        BSP_QSPI_DMA_TransmitEnable(); /* 使能DMA数据传输 */

        BSP_QSPI_DMA_ConfigA(len, (uint32_t *)buf); /* 配置DMA传输 */

        while (DMA_GetFlagStatus(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF) == RESET); /* 等待传输完成 */
        DMA_ClearITPendingBit(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF); /* 清除传输完成标志位 */
        while ((HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET) || (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET)); /* 检查总线忙状态 发送缓冲区是否为空 */

        BSP_QSPI_DMA_TransmitDisable(); /* 失能DMA数据传输 */
    }
    BSP_QSPI_CS_Set(); /* 拉高片选 */
}

/**
 * @brief       QSPI单线命令单线数据DMA模式B发送数据
 * @param       cmd:指令
 * @param       addr:地址
 * @param       len:数据长度
 * @param       color:颜色数据
 * @retval      无
 */
void LCD_SingleCmdSingleData_DMA_TXB(uint8_t cmd, uint32_t addr, uint32_t len, uint16_t color)
{
    uint16_t color1[1];
    uint16_t i = 0;
    uint8_t cmd_bytesize = 1;  /* 存储指令长度 */
    uint8_t addr_bytesize = 3; /* 存储地址长度 */
    uint8_t loadbuf[4];
    color1[0] = color;
    HSPI_StandardSpiDef QSPI_SingleInitStructure = {0};
    BSP_QSPI_CS_Set();                                          /* 拉高片选 */
    HSPI_Cmd(DISABLE);                                          /* 失能QSPI */
    QSPI_SingleInitStructure.CKMode = HSPI_STANDARDSPI_CKMODE3; /* 配置QSPI 时钟相位 时钟极性 */
    QSPI_SingleInitStructure.Rx_NumberDFrame = 0;
    QSPI_SingleInitStructure.Transfer_Mode = HSPI_SandardSPI_Tx;             /* 配置QSPI 单线工作模式 */
    QSPI_SingleInitStructure.Tx_NumberDFrame = cmd_bytesize + addr_bytesize; /* 配置QSPI 发送字节长度 */
    HSPI_StandardSPI_Config(&QSPI_SingleInitStructure);
    HSPI_DataFrameSizeConfig(HSPI_DFS_8); /* 配置传输数据帧为字节 */
    HSPI_Cmd(ENABLE);                     /* 使能QSPI */
    BSP_QSPI_CS_Clr();                    /* 拉低片选 */
    loadbuf[0] = cmd;
    loadbuf[1] = 0x00;
    loadbuf[2] = (addr & 0xFF);
    loadbuf[3] = 0x00;
    for (i = 0; i < cmd_bytesize + addr_bytesize; i++)
    {
        while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
        HSPI_SendData(loadbuf[i]);
    }
    while (HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET || HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET); /* 检查总线忙状态 发送缓冲区是否为空 */

    HSPI_Cmd(DISABLE);                     /* 失能QSPI */
    HSPI_DataFrameSizeConfig(HSPI_DFS_16); /* 切换数据帧为半字传输 */
    HSPI_Cmd(ENABLE);                      /* 使能QSPI */

    BSP_QSPI_DMA_TransmitEnable(); /* 使能DMA数据传输 */

    BSP_QSPI_DMA_ConfigB(len, (uint32_t *)color1); /* 配置DMA传输 */

    while (DMA_GetFlagStatus(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF) == RESET); /* 等待传输完成 */
    DMA_ClearITPendingBit(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF); /* 清除传输完成标志位 */

    while ((HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET) || (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET)); /* 检查总线忙状态 发送缓冲区是否为空 */

    BSP_QSPI_DMA_TransmitDisable(); /* 失能DMA数据传输 */

    BSP_QSPI_CS_Set(); /* 拉高片选 */

    HSPI_Cmd(DISABLE);                    /* 失能QSPI */
    HSPI_DataFrameSizeConfig(HSPI_DFS_8); /* 切换数据帧为字节传输 */
    HSPI_Cmd(ENABLE);                     /* 使能QSPI */
}

/**
 * @brief       QSPI单线命令单线数据DMA模式C发送数据
 * @param       cmd:指令
 * @param       addr:地址
 * @param       len:数据长度
 * @param       buf:数据缓冲区地址
 * @retval      无
 */
void LCD_SingleCmdSingleData_DMA_TXC(uint8_t cmd, uint32_t addr, uint32_t len, uint16_t *buf)
{
    uint16_t i = 0;
    uint8_t cmd_bytesize = 1;  /* 存储指令长度 */
    uint8_t addr_bytesize = 3; /* 存储地址长度 */
    uint8_t loadbuf[4];
    HSPI_StandardSpiDef QSPI_SingleInitStructure = {0};
    BSP_QSPI_CS_Set();                                          /* 拉高片选 */
    HSPI_Cmd(DISABLE);                                          /* 失能QSPI */
    QSPI_SingleInitStructure.CKMode = HSPI_STANDARDSPI_CKMODE3; /* 配置QSPI 时钟相位 时钟极性 */
    QSPI_SingleInitStructure.Rx_NumberDFrame = 0;
    QSPI_SingleInitStructure.Transfer_Mode = HSPI_SandardSPI_Tx;             /* 配置QSPI 单线工作模式 */
    QSPI_SingleInitStructure.Tx_NumberDFrame = cmd_bytesize + addr_bytesize; /* 配置QSPI 发送字节长度 */
    HSPI_StandardSPI_Config(&QSPI_SingleInitStructure);
    HSPI_Cmd(ENABLE);  /* 使能QSPI */
    BSP_QSPI_CS_Clr(); /* 拉低片选 */
    loadbuf[0] = cmd;
    loadbuf[1] = 0x00;
    loadbuf[2] = (addr & 0xFF);
    loadbuf[3] = 0x00;
    for (i = 0; i < cmd_bytesize + addr_bytesize; i++)
    {
        while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
        HSPI_SendData(loadbuf[i]);
    }
    while (HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET || HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET); /* 发送指令数据 */

    HSPI_Cmd(DISABLE);                     /* 失能QSPI */
    HSPI_DataFrameSizeConfig(HSPI_DFS_16); /* 切换数据帧为半字传输 */
    HSPI_Cmd(ENABLE);                      /* 使能QSPI */

    BSP_QSPI_DMA_TransmitEnable(); /* 使能DMA数据传输 */

    BSP_QSPI_DMA_ConfigC(len, (uint32_t *)buf); /* 配置DMA传输 */

    while (DMA_GetFlagStatus(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF) == RESET);   /* 等待传输完成 */
    DMA_ClearITPendingBit(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF); /* 清除传输完成标志位 */

    while ((HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET) || (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET)); /* 检查总线忙状态 发送缓冲区是否为空 */

    BSP_QSPI_DMA_TransmitDisable(); /* 失能DMA数据传输 */

    BSP_QSPI_CS_Set(); /* 拉高片选 */

    HSPI_Cmd(DISABLE);                    /* 失能QSPI */
    HSPI_DataFrameSizeConfig(HSPI_DFS_8); /* 切换数据帧为字节传输 */
    HSPI_Cmd(ENABLE);                     /* 使能QSPI */
}

/**
 * @brief       QSPI单线命令四线数据DMA模式A发送数据
 * @param       cmd:指令
 * @param       addr:地址
 * @param       len:数据长度
 * @param       buf:数据缓冲区地址
 * @retval      无
 */
void LCD_SingleCmdQuadData_DMA_TXA(uint8_t cmd, uint32_t addr, uint32_t len, uint8_t *buf)
{
    addr <<= 8;
    HSPI_QuadSpiDef QSPI_QuadInitStructure = {0};
    BSP_QSPI_CS_Set();                                        /* 拉高片选 */
    HSPI_Cmd(DISABLE);                                        /* 失能QSPI */
    QSPI_QuadInitStructure.Address_Len = HSPI_AdressLen_24;   /* 配置QSPI 地址长度 */
    QSPI_QuadInitStructure.CKMode = HSPI_QUADSPI_CKMODE3;     /* 配置QSPI 时钟相位 时钟极性 */
    QSPI_QuadInitStructure.Direction_Mode = HSPI_QuadSPI_Tx;  /* 配置QSPI 双线工作模式 */
    QSPI_QuadInitStructure.Instruction_Len = HSPI_8_INST;     /* 配置QSPI 指令长度 */
    QSPI_QuadInitStructure.Line_Mode = HSPI_QuadSPI_Line_114; /* 配置QSPI 单线指令 单线地址 四线数据 */
    QSPI_QuadInitStructure.Rx_NumberDFrame = 0;               /* 配置QSPI 接收数据帧，仅在接收模式或者 EEPROM读取下有效 */
    QSPI_QuadInitStructure.Tx_NumberDFrame = 0;               /* 配置QSPI 连续传输数据帧长度 */
    QSPI_QuadInitStructure.Wait_Cycles = 0;                   /* 配置QSPI 发送控制帧和数据帧之间的等待周期 */
    HSPI_QuadSPI_Config(&QSPI_QuadInitStructure);             /* 初始化结构体 */
    HSPI_DataFrameSizeConfig(HSPI_DFS_8);                     /* 配置传输数据帧为字节 */
    HSPI_Cmd(ENABLE);                                         /* 使能QSPI */
    BSP_QSPI_CS_Clr();                                        /* 拉低片选 */

    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(cmd);
    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(addr);

    BSP_QSPI_DMA_TransmitEnable(); /* 使能DMA数据传输 */

    BSP_QSPI_DMA_ConfigA(len, (uint32_t *)buf); /* 配置DMA传输 */

    while (DMA_GetFlagStatus(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF) == RESET); /* 等待传输完成 */
    DMA_ClearITPendingBit(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF); /* 清除传输完成标志位 */

    while ((HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET) || (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET)); /* 检查总线忙状态 发送缓冲区是否为空 */

    BSP_QSPI_DMA_TransmitDisable(); /* 失能DMA数据传输 */

    BSP_QSPI_CS_Set(); /* 拉高片选 */
}

/**
 * @brief       QSPI单线命令四线数据DMA模式B发送数据
 * @param       cmd:指令
 * @param       addr:地址
 * @param       len:数据长度
 * @param       color:颜色数据
 * @retval      无
 */
void LCD_SingleCmdQuadData_DMA_TXB(uint8_t cmd, uint32_t addr, uint32_t len, uint16_t color)
{
    uint16_t color1[1];
    addr <<= 8;
    color1[0] = color;
    HSPI_QuadSpiDef QSPI_QuadInitStructure = {0};
    BSP_QSPI_CS_Set();                                        /* 拉高片选 */
    HSPI_Cmd(DISABLE);                                        /* 失能QSPI */
    QSPI_QuadInitStructure.Address_Len = HSPI_AdressLen_24;   /* 配置QSPI 地址长度 */
    QSPI_QuadInitStructure.CKMode = HSPI_QUADSPI_CKMODE3;     /* 配置QSPI 时钟相位 时钟极性 */
    QSPI_QuadInitStructure.Direction_Mode = HSPI_QuadSPI_Tx;  /* 配置QSPI 双线工作模式 */
    QSPI_QuadInitStructure.Instruction_Len = HSPI_8_INST;     /* 配置QSPI 指令长度 */
    QSPI_QuadInitStructure.Line_Mode = HSPI_QuadSPI_Line_114; /* 配置QSPI 单线指令 单线地址 四线数据 */
    QSPI_QuadInitStructure.Rx_NumberDFrame = 0;               /* 配置QSPI 接收数据帧，仅在接收模式或者 EEPROM读取下有效 */
    QSPI_QuadInitStructure.Tx_NumberDFrame = 0;               /* 配置QSPI 连续传输数据帧长度 */
    QSPI_QuadInitStructure.Wait_Cycles = 0;                   /* 配置QSPI 发送控制帧和数据帧之间的等待周期 */
    HSPI_QuadSPI_Config(&QSPI_QuadInitStructure);             /* 初始化结构体 */
    HSPI_DataFrameSizeConfig(HSPI_DFS_16);                    /* 配置传输数据帧为半字 */
    HSPI_Cmd(ENABLE);                                         /* 使能QSPI */
    BSP_QSPI_CS_Clr();                                        /* 拉低片选 */

    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(cmd);
    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(addr);

    BSP_QSPI_DMA_TransmitEnable(); /* 使能DMA数据传输 */

    BSP_QSPI_DMA_ConfigB(len, (uint32_t *)color1); /* 配置DMA传输 */

    while (DMA_GetFlagStatus(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF) == RESET); /* 等待传输完成 */
    DMA_ClearITPendingBit(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF); /* 清除传输完成标志位 */

    while ((HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET) || (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET)); /* 检查总线忙状态 发送缓冲区是否为空 */

    BSP_QSPI_DMA_TransmitDisable(); /* 失能DMA数据传输 */

    BSP_QSPI_CS_Set(); /* 拉高片选 */

    HSPI_Cmd(DISABLE);                    /* 失能QSPI */
    HSPI_DataFrameSizeConfig(HSPI_DFS_8); /* 切换数据帧为字节传输 */
    HSPI_Cmd(ENABLE);                     /* 使能QSPI */
}

/**
 * @brief       QSPI单线命令四线数据DMA模式C发送数据
 * @param       cmd:指令
 * @param       addr:地址
 * @param       len:数据长度
 * @param       buf:数据缓冲区地址
 * @retval      无
 */
void LCD_SingleCmdQuadData_DMA_TXC(uint8_t cmd, uint32_t addr, uint32_t len, uint16_t *buf)
{
    addr <<= 8;
    HSPI_QuadSpiDef QSPI_QuadInitStructure = {0};
    BSP_QSPI_CS_Set();                                        /* 拉高片选 */
    HSPI_Cmd(DISABLE);                                        /* 失能QSPI */
    QSPI_QuadInitStructure.Address_Len = HSPI_AdressLen_24;   /* 配置QSPI 地址长度 */
    QSPI_QuadInitStructure.CKMode = HSPI_QUADSPI_CKMODE3;     /* 配置QSPI 时钟相位 时钟极性 */
    QSPI_QuadInitStructure.Direction_Mode = HSPI_QuadSPI_Tx;  /* 配置QSPI 双线工作模式 */
    QSPI_QuadInitStructure.Instruction_Len = HSPI_8_INST;     /* 配置QSPI 指令长度 */
    QSPI_QuadInitStructure.Line_Mode = HSPI_QuadSPI_Line_114; /* 配置QSPI 单线指令 单线地址 四线数据 */
    QSPI_QuadInitStructure.Rx_NumberDFrame = 0;               /* 配置QSPI 接收数据帧，仅在接收模式或者 EEPROM读取下有效 */
    QSPI_QuadInitStructure.Tx_NumberDFrame = 0;               /* 配置QSPI 连续传输数据帧长度 */
    QSPI_QuadInitStructure.Wait_Cycles = 0;                   /* 配置QSPI 发送控制帧和数据帧之间的等待周期 */
    HSPI_QuadSPI_Config(&QSPI_QuadInitStructure);             /* 初始化结构体 */
    HSPI_DataFrameSizeConfig(HSPI_DFS_16);                    /* 配置传输数据帧为半字 */
    HSPI_Cmd(ENABLE);                                         /* 使能QSPI */
    BSP_QSPI_CS_Clr();                                        /* 拉低片选 */

    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(cmd);
    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(addr);

    BSP_QSPI_DMA_TransmitEnable(); /* 使能DMA数据传输 */

    BSP_QSPI_DMA_ConfigC(len, (uint32_t *)buf); /* 配置DMA传输 */

    while (DMA_GetFlagStatus(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF) == RESET); /* 等待传输完成 */
    DMA_ClearITPendingBit(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF); /* 清除传输完成标志位 */

    while ((HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET) || (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET)); /* 检查总线忙状态 发送缓冲区是否为空 */

    BSP_QSPI_DMA_TransmitDisable(); /* 失能DMA数据传输 */

    BSP_QSPI_CS_Set(); /* 拉高片选 */

    HSPI_Cmd(DISABLE);                    /* 失能QSPI */
    HSPI_DataFrameSizeConfig(HSPI_DFS_8); /* 切换数据帧为字节传输 */
    HSPI_Cmd(ENABLE);                     /* 使能QSPI */
}

/**
 * @brief       QSPI四线命令四线数据DMA模式A发送数据
 * @param       cmd:指令
 * @param       addr:地址
 * @param       len:数据长度
 * @param       buf:数据缓冲区地址
 * @retval      无
 */
void LCD_QuadCmdQuadData_DMA_TXA(uint8_t cmd, uint32_t addr, uint32_t len, uint8_t *buf)
{
    addr <<= 8;
    HSPI_QuadSpiDef QSPI_QuadInitStructure = {0};
    BSP_QSPI_CS_Set();                                        /* 拉高片选 */
    HSPI_Cmd(DISABLE);                                        /* 失能QSPI */
    QSPI_QuadInitStructure.Address_Len = HSPI_AdressLen_24;   /* 配置QSPI 地址长度 */
    QSPI_QuadInitStructure.CKMode = HSPI_QUADSPI_CKMODE3;     /* 配置QSPI 时钟相位 时钟极性 */
    QSPI_QuadInitStructure.Direction_Mode = HSPI_QuadSPI_Tx;  /* 配置QSPI 双线工作模式 */
    QSPI_QuadInitStructure.Instruction_Len = HSPI_8_INST;     /* 配置QSPI 指令长度 */
    QSPI_QuadInitStructure.Line_Mode = HSPI_QuadSPI_Line_144; /* 配置QSPI 四线指令 四线地址 四线数据 */
    QSPI_QuadInitStructure.Rx_NumberDFrame = 0;               /* 配置QSPI 接收数据帧，仅在接收模式或者 EEPROM读取下有效 */
    QSPI_QuadInitStructure.Tx_NumberDFrame = 0;               /* 配置QSPI 连续传输数据帧长度 */
    QSPI_QuadInitStructure.Wait_Cycles = 0;                   /* 配置QSPI 发送控制帧和数据帧之间的等待周期 */
    HSPI_QuadSPI_Config(&QSPI_QuadInitStructure);             /* 初始化结构体 */
    HSPI_DataFrameSizeConfig(HSPI_DFS_8);                     /* 配置传输数据帧为字节 */
    HSPI_Cmd(ENABLE);                                         /* 使能QSPI */
    BSP_QSPI_CS_Clr();                                        /* 拉低片选 */

    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(cmd);
    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(addr);

    BSP_QSPI_DMA_TransmitEnable(); /* 使能DMA数据传输 */

    BSP_QSPI_DMA_ConfigA(len, (uint32_t *)buf); /* 配置DMA传输 */

    while (DMA_GetFlagStatus(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF) == RESET);   /* 等待传输完成 */
    DMA_ClearITPendingBit(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF); /* 清除传输完成标志位 */

    while ((HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET) || (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET)); /* 检查总线忙状态 发送缓冲区是否为空 */

    BSP_QSPI_DMA_TransmitDisable(); /* 失能DMA数据传输 */

    BSP_QSPI_CS_Set(); /* 拉高片选 */
}

/**
 * @brief       QSPI四线命令四线数据DMA模式B发送数据
 * @param       cmd:指令
 * @param       addr:地址
 * @param       len:数据长度
 * @param       color:颜色数据
 * @retval      无
 */
void LCD_QuadCmdQuadData_DMA_TXB(uint8_t cmd, uint32_t addr, uint32_t len, uint16_t color)
{
    uint16_t color1[1] = {0};
    addr <<= 8;
    color1[0] = color;
    HSPI_QuadSpiDef QSPI_QuadInitStructure = {0};
    BSP_QSPI_CS_Set();                                        /* 拉高片选 */
    HSPI_Cmd(DISABLE);                                        /* 失能QSPI */
    QSPI_QuadInitStructure.Address_Len = HSPI_AdressLen_24;   /* 配置QSPI 地址长度 */
    QSPI_QuadInitStructure.CKMode = HSPI_QUADSPI_CKMODE3;     /* 配置QSPI 时钟相位 时钟极性 */
    QSPI_QuadInitStructure.Direction_Mode = HSPI_QuadSPI_Tx;  /* 配置QSPI 双线工作模式 */
    QSPI_QuadInitStructure.Instruction_Len = HSPI_8_INST;     /* 配置QSPI 指令长度 */
    QSPI_QuadInitStructure.Line_Mode = HSPI_QuadSPI_Line_144; /* 配置QSPI 四线指令 四线地址 四线数据 */
    QSPI_QuadInitStructure.Rx_NumberDFrame = 0;               /* 配置QSPI 接收数据帧，仅在接收模式或者 EEPROM读取下有效 */
    QSPI_QuadInitStructure.Tx_NumberDFrame = 0;               /* 配置QSPI 连续传输数据帧长度 */
    QSPI_QuadInitStructure.Wait_Cycles = 0;                   /* 配置QSPI 发送控制帧和数据帧之间的等待周期 */
    HSPI_QuadSPI_Config(&QSPI_QuadInitStructure);             /* 初始化结构体 */
    HSPI_DataFrameSizeConfig(HSPI_DFS_16);                    /* 配置传输数据帧为半字 */
    HSPI_Cmd(ENABLE);                                         /* 使能QSPI */
    BSP_QSPI_CS_Clr();                                        /* 拉低片选 */

    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(cmd);
    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(addr);

    BSP_QSPI_DMA_TransmitEnable(); /* 使能DMA数据传输 */

    BSP_QSPI_DMA_ConfigB(len, (uint32_t *)color1); /* 配置DMA传输 */

    while (DMA_GetFlagStatus(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF) == RESET);   /* 等待传输完成 */
    DMA_ClearITPendingBit(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF); /* 清除传输完成标志位 */

    while ((HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET) || (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET)); /* 检查总线忙状态 发送缓冲区是否为空 */

    BSP_QSPI_DMA_TransmitDisable(); /* 失能DMA数据传输 */

    BSP_QSPI_CS_Set(); /* 拉高片选 */
}

/**
 * @brief       QSPI四线命令四线数据DMA模式C发送数据
 * @param       cmd:指令
 * @param       addr:地址
 * @param       len:数据长度
 * @param       buf:数据缓冲区地址
 * @retval      无
 */
void LCD_QuadCmdQuadData_DMA_TXC(uint8_t cmd, uint32_t addr, uint32_t len, uint16_t *buf)
{
    addr <<= 8;
    HSPI_QuadSpiDef QSPI_QuadInitStructure = {0};
    BSP_QSPI_CS_Set();                                        /* 拉高片选 */
    HSPI_Cmd(DISABLE);                                        /* 失能QSPI */
    QSPI_QuadInitStructure.Address_Len = HSPI_AdressLen_24;   /* 配置QSPI 地址长度 */
    QSPI_QuadInitStructure.CKMode = HSPI_QUADSPI_CKMODE3;     /* 配置QSPI 时钟相位 时钟极性 */
    QSPI_QuadInitStructure.Direction_Mode = HSPI_QuadSPI_Tx;  /* 配置QSPI 双线工作模式 */
    QSPI_QuadInitStructure.Instruction_Len = HSPI_8_INST;     /* 配置QSPI 指令长度 */
    QSPI_QuadInitStructure.Line_Mode = HSPI_QuadSPI_Line_144; /* 配置QSPI 四线指令 四线地址 四线数据 */
    QSPI_QuadInitStructure.Rx_NumberDFrame = 0;               /* 配置QSPI 接收数据帧，仅在接收模式或者 EEPROM读取下有效 */
    QSPI_QuadInitStructure.Tx_NumberDFrame = 0;               /* 配置QSPI 连续传输数据帧长度 */
    QSPI_QuadInitStructure.Wait_Cycles = 0;                   /* 配置QSPI 发送控制帧和数据帧之间的等待周期 */
    HSPI_QuadSPI_Config(&QSPI_QuadInitStructure);             /* 初始化结构体 */
    HSPI_DataFrameSizeConfig(HSPI_DFS_16);                    /* 配置传输数据帧为半字 */
    HSPI_Cmd(ENABLE);                                         /* 使能QSPI */
    BSP_QSPI_CS_Clr();                                        /* 拉低片选 */

    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(cmd);
    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(addr);

    BSP_QSPI_DMA_TransmitEnable(); /* 使能DMA数据传输 */

    BSP_QSPI_DMA_ConfigC(len, (uint32_t *)buf); /* 配置DMA传输 */

    while (DMA_GetFlagStatus(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF) == RESET); /* 等待传输完成 */
    DMA_ClearITPendingBit(BSP_QSPI_DMA_STREAM, BSP_QSPI_DMA_TCIF); /* 清除传输完成标志位 */

    while ((HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET) || (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET)); /* 检查总线忙状态 发送缓冲区是否为空 */

    BSP_QSPI_DMA_TransmitDisable(); /* 失能DMA数据传输 */

    BSP_QSPI_CS_Set(); /* 拉高片选 */

    HSPI_Cmd(DISABLE);                    /* 失能QSPI */
    HSPI_DataFrameSizeConfig(HSPI_DFS_8); /* 切换数据帧为字节传输 */
    HSPI_Cmd(ENABLE);                     /* 使能QSPI */
}

/**
 * @brief       设置显示窗口
 * @param       xs:窗口列起始地址
 * @param       ys:坐标行起始地址
 * @param       xe:窗口列结束地址
 * @param       ye:坐标行结束地址
 * @retval      无
 */
void LCD_Address_Set(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
    uint8_t x_position[4] = {xs >> 8, xs & 0xFF, xe >> 8, xe & 0xFF};
    uint8_t y_position[4] = {ys >> 8, ys & 0xFF, ye >> 8, ye & 0xFF};
    LCD_SingleCmdSingleData_DMA_TXA(LCD_SingleAddr_SingleData, 0x2A, 4, x_position);
    LCD_SingleCmdSingleData_DMA_TXA(LCD_SingleAddr_SingleData, 0x2B, 4, y_position);
    LCD_SingleCmdSingleData_DMA_TXA(LCD_SingleAddr_SingleData, 0x2C, 0, NULL);
}

void LCD_Fill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color)
{
    uint32_t num;
    num=(xe - xs)*(ye - ys);
    LCD_Address_Set(xs,ys,xe-1,ye-1);
    LCD_QuadCmdQuadData_DMA_TXB(LCD_QuadAddr_QuadData, 0x3C, num, color);
}

void LCD_ColorFill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t *color)
{
    uint32_t num;
    num=(xe - xs)*(ye - ys);
    LCD_Address_Set(xs,ys,xe-1,ye-1);
    LCD_QuadCmdQuadData_DMA_TXC(LCD_QuadAddr_QuadData, 0x3C, num, color);
}


/**
 * @brief       液晶初始化
 * @param       无
 * @retval      无
 */
void LCD_Init(void)
{
    uint16_t cmd = 0;
    LCD_GPIOInit();
    LCD_RES_Set();
    SystemDelay(120);
    LCD_RES_Clr();
    SystemDelay(120);
    LCD_RES_Set();
    SystemDelay(120);

    lcd_init_t *init = (lcd_init_t *)&LCD_InitTable[0];
    for (cmd = 0; cmd < sizeof(LCD_InitTable) / sizeof(lcd_init_t); cmd++)
    {
        if (init->reg == 0xFF)
        {
            SystemDelay(init->data[0]);
        }
        else
        {
            LCD_SingleCmdSingleData_DMA_TXA(LCD_SingleAddr_SingleData, init->reg, init->len, init->data); /* 操作寄存器时仅只能单数据线 */
        }
        init++;
    }
}
