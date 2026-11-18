#include "bsp_dma.h"

/**
 * @brief       配置DMA传输
 * @param       cndtr:DMA传输数据量
 * @param       buf:DMA数据地址
 * @retval      无
 * @note        配置DMA内存地址自增 外设地址不变 以字节传输
 */
void BSP_QSPI_DMA_ConfigA(uint32_t cndtr, uint32_t *buf)
{
    DMA_InitTypeDef DMA_InitStructure;

    /* 使能时钟 */
    RCC_AHB4PeriphClockCmd(RCC_AHB4Periph_DMA2, ENABLE);

    /* 复位初始化DMA数据流 */
    DMA_DeInit(BSP_QSPI_DMA_STREAM);
    /* 确保 DMA数据流复位完成 */
    while (DMA_GetCmdStatus(BSP_QSPI_DMA_STREAM) != DISABLE);

    /* 初始化DMA */
    DMA_InitStructure.DMA_BufferSize = cndtr;               /* 定义数据传输长度 */
    DMA_InitStructure.DMA_Channel = BSP_QSPI_DMA_CHANNEL;   /* 配置DMA通道 */
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; /* DMA传输方向从内存到外设 */
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;   /* 使能FIFO */
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)buf;                   /* 定义内存地址 */
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;              /* 内存突发传输 1个节拍 */
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;          /* 定义内存数据单位 字节传输 */
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                  /* 内存地址自增 */
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                            /* DMA模式 非循环模式 */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&BSP_QSPI_DMA_BASE; /* 定义外设地址 */
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;      /* 外设突发传输 1个节拍 */
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  /* 定义外设数据单位 字节传输 */
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;         /* 外设地址不变 */
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                    /* 定义DMA传输优先级 中优先级 */
    DMA_Init(BSP_QSPI_DMA_STREAM, &DMA_InitStructure);                       /* 初始化DMA */
    DMA_ITConfig(BSP_QSPI_DMA_STREAM, DMA_IT_TC, ENABLE);
    DMA_Cmd(BSP_QSPI_DMA_STREAM, ENABLE);
}

/**
 * @brief       配置DMA传输
 * @param       cndtr:DMA传输数据量
 * @param       buf:DMA数据地址
 * @retval      无
 * @note        配置DMA内存地址不变 外设地址不变 以半字传输
 */
void BSP_QSPI_DMA_ConfigB(uint32_t cndtr, uint32_t *buf)
{
    DMA_InitTypeDef DMA_InitStructure;

    /* 使能时钟 */
    RCC_AHB4PeriphClockCmd(RCC_AHB4Periph_DMA2, ENABLE);

    /* 复位初始化DMA数据流 */
    DMA_DeInit(BSP_QSPI_DMA_STREAM);
    /* 确保 DMA数据流复位完成 */
    while (DMA_GetCmdStatus(BSP_QSPI_DMA_STREAM) != DISABLE);

    /* 初始化DMA */
    DMA_InitStructure.DMA_BufferSize = cndtr;               /* 定义数据传输长度 */
    DMA_InitStructure.DMA_Channel = BSP_QSPI_DMA_CHANNEL;   /* 配置DMA通道 */
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; /* DMA传输方向从内存到外设 */
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;   /* 使能FIFO */
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)buf;                      /* 定义内存地址 */
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;                 /* 内存突发传输 1个节拍 */
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         /* 定义内存数据单位 半字传输 */
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;                    /* 内存地址不变 */
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                               /* DMA模式 非循环模式 */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&BSP_QSPI_DMA_BASE;    /* 定义外设地址 */
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;         /* 外设突发传输 1个节拍 */
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; /* 定义外设数据单位 半字传输 */
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;            /* 外设地址不变 */
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                       /* 定义DMA传输优先级 中优先级 */
    DMA_Init(BSP_QSPI_DMA_STREAM, &DMA_InitStructure);                          /* 初始化DMA */
    DMA_ITConfig(BSP_QSPI_DMA_STREAM, DMA_IT_TC, ENABLE);
    DMA_Cmd(BSP_QSPI_DMA_STREAM, ENABLE);
}

/**
 * @brief       配置DMA传输
 * @param       cndtr:DMA传输数据量
 * @param       buf:DMA数据地址
 * @retval      无
 * @note        配置DMA内存地址自增 外设地址不变 以半字传输
 */
void BSP_QSPI_DMA_ConfigC(uint32_t cndtr, uint32_t *buf)
{
    DMA_InitTypeDef DMA_InitStructure;

    /* 使能时钟 */
    RCC_AHB4PeriphClockCmd(RCC_AHB4Periph_DMA2, ENABLE);

    /* 复位初始化DMA数据流 */
    DMA_DeInit(BSP_QSPI_DMA_STREAM);
    /* 确保 DMA数据流复位完成 */
    while (DMA_GetCmdStatus(BSP_QSPI_DMA_STREAM) != DISABLE);

    /* 初始化DMA */
    DMA_InitStructure.DMA_BufferSize = cndtr;               /* 定义数据传输长度 */
    DMA_InitStructure.DMA_Channel = BSP_QSPI_DMA_CHANNEL;   /* 配置DMA通道 */
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; /* DMA传输方向从内存到外设 */
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;   /* 使能FIFO */
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)buf;                      /* 定义内存地址 */
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;                 /* 内存突发传输 1个节拍 */
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         /* 定义内存数据单位 半字传输 */
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                     /* 内存地址自增 */
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                               /* DMA模式 非循环模式 */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&BSP_QSPI_DMA_BASE;    /* 定义外设地址 */
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;         /* 外设突发传输 1个节拍 */
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; /* 定义外设数据单位 半字传输 */
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;            /* 外设地址不变 */
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                       /* 定义DMA传输优先级 中优先级 */
    DMA_Init(BSP_QSPI_DMA_STREAM, &DMA_InitStructure);                          /* 初始化DMA */
    DMA_ITConfig(BSP_QSPI_DMA_STREAM, DMA_IT_TC, ENABLE);
    DMA_Cmd(BSP_QSPI_DMA_STREAM, ENABLE);
}

/**
 * @brief       使能DMA发送数据传输
 * @param       无
 * @retval      无
 */
void BSP_QSPI_DMA_TransmitEnable(void)
{
    HSPI_DMAConfigTypeDef HSPI_DmaConfigStructure = {0};
    HSPI_DmaConfigStructure.HSPI_TDMA_DLevel = 16 - 1;
    HSPI_DmaConfigStructure.HSPI_RDMA_DLevel = 16 - 1;
    HSPI_DmaConfigStructure.HSPI_Tran_DMA = HSPI_TDMA_Enable;
    HSPI_DmaConfigStructure.HSPI_Receive_DMA = HSPI_RDMA_Disable;
    HSPI_DmaConfig(&HSPI_DmaConfigStructure);
}

/**
 * @brief       失能DMA发送数据传输
 * @param       无
 * @retval      无
 */
void BSP_QSPI_DMA_TransmitDisable(void)
{
    HSPI_DMAConfigTypeDef HSPI_DmaConfigStructure = {0};
    HSPI_DmaConfigStructure.HSPI_TDMA_DLevel = 16 - 1;
    HSPI_DmaConfigStructure.HSPI_RDMA_DLevel = 16 - 1;
    HSPI_DmaConfigStructure.HSPI_Tran_DMA = HSPI_TDMA_Disable;
    HSPI_DmaConfigStructure.HSPI_Receive_DMA = HSPI_RDMA_Disable;
    HSPI_DmaConfig(&HSPI_DmaConfigStructure);
}
