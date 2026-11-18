#include "bsp_qspi.h"

/**
 * @brief       QSPI端口初始化
 * @param       无
 * @retval      无
 */
void BSP_QSPI_GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /* 使能端口时钟 */
    PeripheralEnable(BSP_QSPI_SCK_CLK, ENABLE);
    PeripheralEnable(BSP_QSPI_DATA0_CLK, ENABLE);
    PeripheralEnable(BSP_QSPI_DATA1_CLK, ENABLE);
    PeripheralEnable(BSP_QSPI_DATA2_CLK, ENABLE);
    PeripheralEnable(BSP_QSPI_DATA3_CLK, ENABLE);
    PeripheralEnable(BSP_QSPI_CS_CLK, ENABLE);
    PeripheralEnable(PeripheralHSPI, ENABLE);

    /* 配置端口工作模式 */
    GPIO_InitStructure.GPIO_Pin = BSP_QSPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(BSP_QSPI_SCK_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BSP_QSPI_DATA0_PIN;
    GPIO_Init(BSP_QSPI_DATA0_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BSP_QSPI_DATA1_PIN;
    GPIO_Init(BSP_QSPI_DATA1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BSP_QSPI_DATA2_PIN;
    GPIO_Init(BSP_QSPI_DATA2_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BSP_QSPI_DATA3_PIN;
    GPIO_Init(BSP_QSPI_DATA3_PORT, &GPIO_InitStructure);

    //    GPIO_InitStructure.GPIO_Pin = BSP_QSPI_CS_PIN;
    //    GPIO_Init(BSP_QSPI_CS_PORT, &GPIO_InitStructure);

    //    /* 配置端口工作模式 */
    GPIO_InitStructure.GPIO_Pin = BSP_QSPI_CS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(BSP_QSPI_CS_PORT, &GPIO_InitStructure);

    /* 配置管脚复用功能 */
    GPIO_PinAFConfig(BSP_QSPI_SCK_PORT, BSP_QSPI_SCK_PINSOURCE, BSP_QSPI_SCK_AF);
    GPIO_PinAFConfig(BSP_QSPI_DATA0_PORT, BSP_QSPI_DATA0_PINSOURCE, BSP_QSPI_DATA0_AF);
    GPIO_PinAFConfig(BSP_QSPI_DATA1_PORT, BSP_QSPI_DATA1_PINSOURCE, BSP_QSPI_DATA1_AF);
    GPIO_PinAFConfig(BSP_QSPI_DATA2_PORT, BSP_QSPI_DATA2_PINSOURCE, BSP_QSPI_DATA2_AF);
    GPIO_PinAFConfig(BSP_QSPI_DATA3_PORT, BSP_QSPI_DATA3_PINSOURCE, BSP_QSPI_DATA3_AF);

    //    GPIO_PinAFConfig(BSP_QSPI_CS_PORT, BSP_QSPI_CS_PINSOURCE, BSP_QSPI_CS_AF);

    BSP_QSPI_CS_Set();
}

/**
 * @brief       初始化QSPI外设
 * @param       无
 * @retval      无
 */
void BSP_QSPI_Init(void)
{
    HSPI_InitTypeDef QSPI_InitStructure = {0};
    BSP_QSPI_GPIOInit();
    HSPI_StructInit(&QSPI_InitStructure);                           /* 恢复默认值 */
    QSPI_InitStructure.HSPI_BAUDR_Sckdv = 6;                        /* 挂载在AHB时钟域 配置QSPI时钟频率 */
    QSPI_InitStructure.HSPI_CSMode = HSPI_CS_TOGGLE;                /* 配置发送数据过程中CS管脚状态 */
    QSPI_InitStructure.HSPI_Data_Frame_Size = HSPI_DFS_8;           /* 配置数据帧大小 以字节传输 */
    QSPI_InitStructure.HSPI_Endian_Conv = HSPI_ENDIAN_CONV_DISABLE; /* 配置大小端转换 失能大小端转换 */
    QSPI_InitStructure.HSPI_ReceiveFIFO_Threshold = 0x00;           /* 配置接收FIFO控制器接收数据量来触发中断 */
    QSPI_InitStructure.HSPI_RxSampleDelay = 2;                      /* 配置输入端口采样延迟时间 */
    QSPI_InitStructure.HSPI_TranFIFO_Threshold = 0x1F;              /* 配置发送FIFO控制器发送数据量来触发中断 */
    HSPI_Init(&QSPI_InitStructure);                                 /* 初始化QSPI */
}

/**
 * @brief       QSPI单线发送数据
 * @param       cmd:指令
 * @param       addr:地址
 * @param       len:数据长度
 * @param       buf:数据缓冲区地址
 * @retval      无
 * @note        一次最多8192个字节
 */
void BSP_QSPI_SingleLineSend(uint8_t cmd, uint32_t addr, uint32_t len, uint8_t *buf)
{
    uint16_t i = 0;
    uint8_t cmd_bytesize = 1;  /* 存储指令长度 */
    uint8_t addr_bytesize = 3; /* 存储地址长度 */
    uint8_t loadbuf[4];
    HSPI_StandardSpiDef QSPI_SingleInitStructure = {0};
    HSPI_Cmd(DISABLE);                                          /* 失能QSPI */
    QSPI_SingleInitStructure.CKMode = HSPI_STANDARDSPI_CKMODE3; /* 配置QSPI 时钟相位 时钟极性 */
    QSPI_SingleInitStructure.Rx_NumberDFrame = 0;
    QSPI_SingleInitStructure.Transfer_Mode = HSPI_SandardSPI_Tx;                   /* 配置QSPI 单线工作模式 */
    QSPI_SingleInitStructure.Tx_NumberDFrame = len + cmd_bytesize + addr_bytesize; /* 配置QSPI 发送字节长度 */
    HSPI_StandardSPI_Config(&QSPI_SingleInitStructure);
    HSPI_Cmd(ENABLE); /* 使能QSPI */
    BSP_QSPI_CS_Clr();
    loadbuf[0] = cmd;
    loadbuf[1] = 0x00;
    loadbuf[2] = (addr & 0xFF);
    loadbuf[3] = 0x00;

    for (i = 0; i < cmd_bytesize + addr_bytesize; i++)
    {
        while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
        HSPI_SendData(loadbuf[i]);
    }
    for (i = 0; i < len; i++)
    {
        while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
        HSPI_SendData(buf[i]);
    }
    while (HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET || HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET);
    BSP_QSPI_CS_Set();
}

/**
 * @brief       QSPI双线发送数据
 * @param       cmd:指令
 * @param       addr:地址
 * @param       len:数据长度
 * @param       buf:数据缓冲区地址
 * @retval      无
 */
void BSP_QSPI_DualLineSend(uint8_t cmd, uint32_t addr, uint32_t len, uint8_t *buf)
{
    uint32_t i = 0;
    addr <<= 8;
    HSPI_DualSpiDef QSPI_DualInitStructure = {0};
    HSPI_Cmd(DISABLE);                                        /* 失能QSPI */
    QSPI_DualInitStructure.Address_Len = HSPI_AdressLen_24;   /* 配置QSPI 地址长度 */
    QSPI_DualInitStructure.CKMode = HSPI_QUADSPI_CKMODE3;     /* 配置QSPI 时钟相位 时钟极性 */
    QSPI_DualInitStructure.Direction_Mode = HSPI_DualSPI_Tx;  /* 配置QSPI 双线工作模式 */
    QSPI_DualInitStructure.Instruction_Len = HSPI_8_INST;     /* 配置QSPI 指令长度 */
    QSPI_DualInitStructure.Line_Mode = HSPI_DualSPI_Line_112; /* 配置QSPI 单线指令 单线地址 双线数据 */
    QSPI_DualInitStructure.Rx_NumberDFrame = 0;               /* 配置QSPI 接收数据帧，仅在接收模式或者 EEPROM读取下有效 */
    QSPI_DualInitStructure.Tx_NumberDFrame = len;             /* 配置QSPI 连续传输数据帧长度 */
    QSPI_DualInitStructure.Wait_Cycles = 0;                   /* 配置QSPI 发送控制帧和数据帧之间的等待周期 */
    HSPI_DualSPI_Config(&QSPI_DualInitStructure);             /* 初始化结构体 */
    HSPI_Cmd(ENABLE);                                         /* 使能QSPI */

    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(cmd);

    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(addr);

    for (i = 0; i < len; i++)
    {
        while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
        HSPI_SendData(buf[i]);
    }
    while (HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET || HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET);
}

/**
 * @brief       QSPI四线发送数据
 * @param       cmd:指令
 * @param       addr:地址
 * @param       len:数据长度
 * @param       buf:数据缓冲区地址
 * @retval      无
 */
void BSP_QSPI_QuadLineSend(uint8_t cmd, uint32_t addr, uint32_t len, uint8_t *buf)
{
    uint32_t i = 0;
    addr <<= 8;
    HSPI_QuadSpiDef QSPI_QuadInitStructure = {0};
    HSPI_Cmd(DISABLE);                                        /* 失能QSPI */
    QSPI_QuadInitStructure.Address_Len = HSPI_AdressLen_24;   /* 配置QSPI 地址长度 */
    QSPI_QuadInitStructure.CKMode = HSPI_QUADSPI_CKMODE3;     /* 配置QSPI 时钟相位 时钟极性 */
    QSPI_QuadInitStructure.Direction_Mode = HSPI_QuadSPI_Tx;  /* 配置QSPI 双线工作模式 */
    QSPI_QuadInitStructure.Instruction_Len = HSPI_8_INST;     /* 配置QSPI 指令长度 */
    QSPI_QuadInitStructure.Line_Mode = HSPI_QuadSPI_Line_114; /* 配置QSPI 单线指令 单线地址 双线数据 */
    QSPI_QuadInitStructure.Rx_NumberDFrame = 0;               /* 配置QSPI 接收数据帧，仅在接收模式或者 EEPROM读取下有效 */
    QSPI_QuadInitStructure.Tx_NumberDFrame = len;             /* 配置QSPI 连续传输数据帧长度 */
    QSPI_QuadInitStructure.Wait_Cycles = 0;                   /* 配置QSPI 发送控制帧和数据帧之间的等待周期 */
    HSPI_QuadSPI_Config(&QSPI_QuadInitStructure);             /* 初始化结构体 */
    HSPI_Cmd(ENABLE);                                         /* 使能QSPI */

    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(cmd);

    while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
    HSPI_SendData(addr);

    for (i = 0; i < len; i++)
    {
        while (HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_NOT_FULL) != SET);
        HSPI_SendData(buf[i]);
    }
    while (HSPI_GetFlagStatus(HSPI_FLAG_BUSY) == SET || HSPI_GetFlagStatus(HSPI_FLAG_TX_FIFO_EMPTY) != SET);
}
