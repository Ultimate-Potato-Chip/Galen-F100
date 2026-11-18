; Copyright (c) 2011-2023 Megahunt Technologies Inc.
; SPDX-License-Identifier: Apache-2.0

; << Use Configuration Wizard in Context Menu >>>

; <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
      MODULE  ?cstartup
        
        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)
        SECTION .intvec:CODE:NOROOT(2)
        EXTERN  __iar_program_start
        EXTERN  SystemInit        
        PUBLIC  __vector_table
        DATA
__vector_table
;__Vectors       DCD      __initial_sp                        ;     Top of Stack
                DCD     sfe(CSTACK)
                DCD      Reset_Handler                       ;     Reset Handler
                DCD      NMI_Handler                         ; -14 NMI Handler
                DCD      HardFault_Handler                   ; -13 Hard Fault Handler
                DCD      MemManage_Handler                   ; -12 MPU Fault Handler
                DCD      BusFault_Handler                    ; -11 Bus Fault Handler
                DCD      UsageFault_Handler                  ; -10 Usage Fault Handler
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      SVC_Handler                         ;  -5 SVC Handler
                DCD      DebugMon_Handler                    ;  -4 Debug Monitor Handler
                DCD      0                                   ;     Reserved
                DCD      PendSV_Handler                      ;  -2 PendSV Handler
                DCD      SysTick_Handler                     ;  -1 SysTick Handler

                ; Interrupts
                DCD      WWDG_IRQHandler                     ;
                DCD      PVD_IRQHandler                      ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      QSPI_IRQHandler                     ;
                DCD      RCC_IRQHandler                      ;
                DCD      EXTI0_IRQHandler                    ;
                DCD      EXTI1_IRQHandler                    ;
                DCD      EXTI2_IRQHandler                    ;
                DCD      EXTI3_IRQHandler                    ;
                DCD      EXTI4_IRQHandler                    ;
                DCD      DMA1_Stream0_IRQHandler             ;
                DCD      DMA1_Stream1_IRQHandler             ;
                DCD      DMA1_Stream2_IRQHandler             ;
                DCD      DMA1_Stream3_IRQHandler             ;
                DCD      DMA1_Stream4_IRQHandler             ;
                DCD      DMA1_Stream5_IRQHandler             ;
                DCD      DMA1_Stream6_IRQHandler             ;
                DCD      ADC_IRQHandler                      ;
                DCD      CAN1_TX_IRQHandler                  ;
                DCD      CAN1_RX0_IRQHandler                 ;
                DCD      CAN1_RX1_IRQHandler                 ;
                DCD      CAN1_SCE_IRQHandler                 ;
                DCD      EXTI9_5_IRQHandler                  ;
                DCD      TIM1_BRK_TIM9_IRQHandler            ;
                DCD      TIM1_UP_TIM10_IRQHandler            ;
                DCD      TIM1_TRG_COM_TIM11_IRQHandler       ;
                DCD      TIM1_CC_IRQHandler                  ;
                DCD      TIM2_IRQHandler                     ;
                DCD      TIM3_IRQHandler                     ;
                DCD      TIM4_IRQHandler                     ;
                DCD      I2C1_EV_IRQHandler                  ;
                DCD      I2C1_ER_IRQHandler                  ;
                DCD      I2C2_EV_IRQHandler                  ;
                DCD      I2C2_ER_IRQHandler                  ;
                DCD      SPI1_IRQHandler                     ;
                DCD      SPI2_IRQHandler                     ;
                DCD      USART1_IRQHandler                   ;
                DCD      USART2_IRQHandler                   ;
                DCD      USART3_IRQHandler                   ;
                DCD      EXTI15_10_IRQHandler                ;
                DCD      RTC_Alarm_IRQHandler                ;
                DCD      0                                   ;
                DCD      TIM8_BRK_TIM12_IRQHandler           ;
                DCD      TIM8_UP_TIM13_IRQHandler            ;
                DCD      TIM8_TRG_COM_TIM14_IRQHandler       ;
                DCD      TIM8_CC_IRQHandler                  ;
                DCD      DMA1_Stream7_IRQHandler             ;
                DCD      FSMC_IRQHandler                     ;
                DCD      SDIO_IRQHandler                     ;
                DCD      TIM5_IRQHandler                     ;
                DCD      SPI3_IRQHandler                     ;
                DCD      UART4_IRQHandler                    ;
                DCD      0                                   ;
                DCD      TIM6_DAC_IRQHandler                 ;
                DCD      TIM7_IRQHandler                     ;
                DCD      DMA2_Stream0_IRQHandler             ;
                DCD      DMA2_Stream1_IRQHandler             ;
                DCD      DMA2_Stream2_IRQHandler             ;
                DCD      DMA2_Stream3_IRQHandler             ;
                DCD      DMA2_Stream4_IRQHandler             ;
                DCD      ETH_IRQHandler                      ;
                DCD      0                                   ;
                DCD      CAN2_TX_IRQHandler                  ;
                DCD      CAN2_RX0_IRQHandler                 ;
                DCD      CAN2_RX1_IRQHandler                 ;
                DCD      CAN2_SCE_IRQHandler                 ;
                DCD      USB1_IRQHandler                     ;
                DCD      DMA2_Stream5_IRQHandler             ;
                DCD      DMA2_Stream6_IRQHandler             ;
                DCD      DMA2_Stream7_IRQHandler             ;
                DCD      USART6_IRQHandler                   ;
                DCD      I2C3_EV_IRQHandler                  ;
                DCD      I2C3_ER_IRQHandler                  ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      DCMI_IRQHandler                     ;
                DCD      0                                   ;
                DCD      HASH_RNG_IRQHandler                 ;
                DCD      FPU_IRQHandler                      ;
                DCD      USART7_IRQHandler                   ;
                DCD      0                                   ;
                DCD      SPI4_IRQHandler                     ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      LTDC_IRQHandler                     ;
                DCD      0                                   ;
                DCD      DMA2D_IRQHandler                    ;
                DCD      0                                   ;
                DCD      DSI_IRQHandler                      ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      HSPI_IRQHandler                     ;
                DCD      0                                   ;
                DCD      JPEGD_IRQHandler                    ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      0                                   ;
                DCD      BUSERROR_IRQHandler                 ;
                THUMB
                PUBWEAK Reset_Handler
                SECTION .text:CODE:REORDER(2)

Reset_Handler
      LDR     R0, =__vector_table
        LDR     R1, =0xE000ED08
        STR     R0, [R1]
        
        LDR     R0, =SystemInit
        BLX     R0
        
        LDR     R0, =__iar_program_start
        BX      R0
               
        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler
                
        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler
        
        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B MemManage_Handler
        
         PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B BusFault_Handler
        
        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B UsageFault_Handler
        
        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler
        
        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B DebugMon_Handler
        
        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler
        
        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler
        
        PUBWEAK WWDG_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WWDG_IRQHandler
        B WWDG_IRQHandler
        
        PUBWEAK PVD_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PVD_IRQHandler
        B PVD_IRQHandler
        
        PUBWEAK QSPI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
QSPI_IRQHandler
        B QSPI_IRQHandler
        
        PUBWEAK RCC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RCC_IRQHandler
        B RCC_IRQHandler
        
        PUBWEAK EXTI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI0_IRQHandler
        B EXTI0_IRQHandler
        
        PUBWEAK EXTI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI1_IRQHandler
        B EXTI1_IRQHandler
        
        PUBWEAK EXTI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI2_IRQHandler
        B EXTI2_IRQHandler
        
        PUBWEAK EXTI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI3_IRQHandler
        B EXTI3_IRQHandler
        
        PUBWEAK EXTI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI4_IRQHandler
        B EXTI4_IRQHandler
        
        PUBWEAK DMA1_Stream0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream0_IRQHandler
        B DMA1_Stream0_IRQHandler
        
        PUBWEAK DMA1_Stream1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream1_IRQHandler
        B DMA1_Stream1_IRQHandler
        
        PUBWEAK DMA1_Stream2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream2_IRQHandler
        B DMA1_Stream2_IRQHandler
        
        PUBWEAK DMA1_Stream3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream3_IRQHandler
        B DMA1_Stream3_IRQHandler
        
        PUBWEAK DMA1_Stream4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream4_IRQHandler
        B DMA1_Stream4_IRQHandler
        
        PUBWEAK DMA1_Stream5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream5_IRQHandler
        B DMA1_Stream5_IRQHandler
        
        PUBWEAK DMA1_Stream6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream6_IRQHandler
        B DMA1_Stream6_IRQHandler
        
        PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC_IRQHandler
        B ADC_IRQHandler
        
        PUBWEAK CAN1_TX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_TX_IRQHandler
        B CAN1_TX_IRQHandler
        
        PUBWEAK CAN1_RX0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_RX0_IRQHandler
        B CAN1_RX0_IRQHandler
        
        PUBWEAK CAN1_RX1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_RX1_IRQHandler
        B CAN1_RX1_IRQHandler
        
        PUBWEAK CAN1_SCE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_SCE_IRQHandler
        B CAN1_SCE_IRQHandler
        
        PUBWEAK EXTI9_5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI9_5_IRQHandler
        B EXTI9_5_IRQHandler
        
        PUBWEAK TIM1_BRK_TIM9_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM1_BRK_TIM9_IRQHandler
        B TIM1_BRK_TIM9_IRQHandler
        
        PUBWEAK TIM1_UP_TIM10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM1_UP_TIM10_IRQHandler
        B TIM1_UP_TIM10_IRQHandler
        
        PUBWEAK TIM1_TRG_COM_TIM11_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM1_TRG_COM_TIM11_IRQHandler
        B TIM1_TRG_COM_TIM11_IRQHandler
        
        PUBWEAK TIM1_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM1_CC_IRQHandler
        B TIM1_CC_IRQHandler
        
        PUBWEAK TIM2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM2_IRQHandler
        B TIM2_IRQHandler
        
        PUBWEAK TIM3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM3_IRQHandler
        B TIM3_IRQHandler
        
        PUBWEAK TIM4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM4_IRQHandler
        B TIM4_IRQHandler
        
        PUBWEAK I2C1_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_EV_IRQHandler
        B I2C1_EV_IRQHandler
        
        PUBWEAK I2C1_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_ER_IRQHandler
        B I2C1_ER_IRQHandler
        
        PUBWEAK I2C2_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_EV_IRQHandler
        B I2C2_EV_IRQHandler
        
        PUBWEAK I2C2_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_ER_IRQHandler
        B I2C2_ER_IRQHandler
        
        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_IRQHandler
        B SPI1_IRQHandler
        
        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI2_IRQHandler
        B SPI2_IRQHandler
        
        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART1_IRQHandler
        B USART1_IRQHandler
        
        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART2_IRQHandler
        B USART2_IRQHandler
        
        PUBWEAK USART3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART3_IRQHandler
        B USART3_IRQHandler
        
        PUBWEAK EXTI15_10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI15_10_IRQHandler
        B EXTI15_10_IRQHandler
        
        PUBWEAK RTC_Alarm_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_Alarm_IRQHandler
        B RTC_Alarm_IRQHandler
        
        PUBWEAK TIM8_BRK_TIM12_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM8_BRK_TIM12_IRQHandler
        B TIM8_BRK_TIM12_IRQHandler
        
        PUBWEAK TIM8_UP_TIM13_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM8_UP_TIM13_IRQHandler
        B TIM8_UP_TIM13_IRQHandler
        
        PUBWEAK TIM8_TRG_COM_TIM14_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM8_TRG_COM_TIM14_IRQHandler
        B TIM8_TRG_COM_TIM14_IRQHandler
        
        PUBWEAK TIM8_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM8_CC_IRQHandler
        B TIM8_CC_IRQHandler
        
        PUBWEAK DMA1_Stream7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream7_IRQHandler
        B DMA1_Stream7_IRQHandler
        
        PUBWEAK FSMC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FSMC_IRQHandler
        B FSMC_IRQHandler
        
        PUBWEAK SDIO_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDIO_IRQHandler
        B SDIO_IRQHandler
        
        PUBWEAK TIM5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM5_IRQHandler
        B TIM5_IRQHandler
        
        PUBWEAK SPI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI3_IRQHandler
        B SPI3_IRQHandler
        
        PUBWEAK UART4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART4_IRQHandler
        B UART4_IRQHandler
        
        PUBWEAK TIM6_DAC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM6_DAC_IRQHandler
        B TIM6_DAC_IRQHandler
        
        PUBWEAK TIM7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM7_IRQHandler
        B TIM7_IRQHandler
        
        PUBWEAK DMA2_Stream0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream0_IRQHandler
        B DMA2_Stream0_IRQHandler
        
        PUBWEAK DMA2_Stream1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream1_IRQHandler
        B DMA2_Stream1_IRQHandler
        
        PUBWEAK DMA2_Stream2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream2_IRQHandler
        B DMA2_Stream2_IRQHandler
        
        PUBWEAK DMA2_Stream3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream3_IRQHandler
        B DMA2_Stream3_IRQHandler
        
        PUBWEAK DMA2_Stream4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream4_IRQHandler
        B DMA2_Stream4_IRQHandler
        
        PUBWEAK ETH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ETH_IRQHandler
        B ETH_IRQHandler
        
        PUBWEAK CAN2_TX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN2_TX_IRQHandler
        B CAN2_TX_IRQHandler
        
        PUBWEAK CAN2_RX0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN2_RX0_IRQHandler
        B CAN2_RX0_IRQHandler
        
        PUBWEAK CAN2_RX1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN2_RX1_IRQHandler
        B CAN2_RX1_IRQHandler
        
        PUBWEAK CAN2_SCE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN2_SCE_IRQHandler
        B CAN2_SCE_IRQHandler
        
        PUBWEAK USB1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB1_IRQHandler
        B USB1_IRQHandler
        
        PUBWEAK DMA2_Stream5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream5_IRQHandler
        B DMA2_Stream5_IRQHandler
        
        PUBWEAK DMA2_Stream6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream6_IRQHandler
        B DMA2_Stream6_IRQHandler
        
        PUBWEAK DMA2_Stream7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream7_IRQHandler
        B DMA2_Stream7_IRQHandler
        
        PUBWEAK USART6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART6_IRQHandler
        B USART6_IRQHandler
        
        PUBWEAK I2C3_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_EV_IRQHandler
        B I2C3_EV_IRQHandler
        
        PUBWEAK I2C3_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_ER_IRQHandler
        B I2C3_ER_IRQHandler
        
        PUBWEAK DCMI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DCMI_IRQHandler
        B DCMI_IRQHandler
        
        PUBWEAK HASH_RNG_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
HASH_RNG_IRQHandler
        B HASH_RNG_IRQHandler
        
        PUBWEAK FPU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FPU_IRQHandler
        B FPU_IRQHandler
        
        PUBWEAK USART7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART7_IRQHandler
        B USART7_IRQHandler
        
        PUBWEAK SPI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI4_IRQHandler
        B SPI4_IRQHandler
        
        PUBWEAK LTDC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LTDC_IRQHandler
        B LTDC_IRQHandler
        
        PUBWEAK DMA2D_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2D_IRQHandler
        B DMA2D_IRQHandler
        
        PUBWEAK DSI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DSI_IRQHandler
        B DSI_IRQHandler
        
        PUBWEAK HSPI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
HSPI_IRQHandler
        B HSPI_IRQHandler
        
        PUBWEAK JPEGD_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
JPEGD_IRQHandler
        B JPEGD_IRQHandler
        
        PUBWEAK BUSERROR_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
BUSERROR_IRQHandler
        B BUSERROR_IRQHandler
            

         END

