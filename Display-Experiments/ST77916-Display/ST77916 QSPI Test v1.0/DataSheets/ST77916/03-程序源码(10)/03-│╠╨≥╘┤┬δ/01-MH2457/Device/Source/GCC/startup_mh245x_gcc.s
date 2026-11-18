.extern HardFault_Handler

.global __Vectors
.global Default_Handler

	.word _sidata  
	.word _sdata
	.word _edata
	.word _sbss
	.word _ebss

/********************************************************/
.section .text.Default_Handler,"ax",%progbits

Default_Handler:
Infinite_Loop:
		b Infinite_Loop
		
.size Default_Handler, .-Default_Handler
/********************************************************/

/*********************vector table***********************/
.section .isr_vector,"a",%progbits

__Vectors:
	.word _estack
    .word Reset_Handler                       
    .word NMI_Handler                         
    .word HardFault_Handler                   
    .word MemManage_Handler                   
    .word BusFault_Handler                    
    .word UsageFault_Handler                  
    .word 0                                   
    .word 0                                   
    .word 0                                   
    .word 0                                   
    .word SVC_Handler                         
    .word DebugMon_Handler                    
    .word 0                                   
    .word PendSV_Handler                      
    .word SysTick_Handler                     

    @; Interrupts
     .word WWDG_IRQHandler                     ;
     .word PVD_IRQHandler                      ;
     .word 0                                   ;
     .word 0                                   ;
     .word QSPI_IRQHandler                     ;
     .word RCC_IRQHandler                      ;
     .word EXTI0_IRQHandler                    ;
     .word EXTI1_IRQHandler                    ;
     .word EXTI2_IRQHandler                    ;
     .word EXTI3_IRQHandler                    ;
     .word EXTI4_IRQHandler                    ;
     .word DMA1_Stream0_IRQHandler             ;
     .word DMA1_Stream1_IRQHandler             ;
     .word DMA1_Stream2_IRQHandler             ;
     .word DMA1_Stream3_IRQHandler             ;
     .word DMA1_Stream4_IRQHandler             ;
     .word DMA1_Stream5_IRQHandler             ;
     .word DMA1_Stream6_IRQHandler             ;
     .word ADC_IRQHandler                      ;
     .word CAN1_TX_IRQHandler                  ;
     .word CAN1_RX0_IRQHandler                 ;
     .word CAN1_RX1_IRQHandler                 ;
     .word CAN1_SCE_IRQHandler                 ;
     .word EXTI9_5_IRQHandler                  ;
     .word TIM1_BRK_TIM9_IRQHandler            ;
     .word TIM1_UP_TIM10_IRQHandler            ;
     .word TIM1_TRG_COM_TIM11_IRQHandler       ;
     .word TIM1_CC_IRQHandler                  ;
     .word TIM2_IRQHandler                     ;
     .word TIM3_IRQHandler                     ;
     .word TIM4_IRQHandler                     ;
     .word I2C1_EV_IRQHandler                  ;
     .word I2C1_ER_IRQHandler                  ;
     .word I2C2_EV_IRQHandler                  ;
     .word I2C2_ER_IRQHandler                  ;
     .word SPI1_IRQHandler                     ;
     .word SPI2_IRQHandler                     ;
     .word USART1_IRQHandler                   ;
     .word USART2_IRQHandler                   ;
     .word USART3_IRQHandler                   ;
     .word EXTI15_10_IRQHandler                ;
     .word RTC_Alarm_IRQHandler                ;
     .word 0                                   ;
     .word TIM8_BRK_TIM12_IRQHandler           ;
     .word TIM8_UP_TIM13_IRQHandler            ;
     .word TIM8_TRG_COM_TIM14_IRQHandler       ;
     .word TIM8_CC_IRQHandler                  ;
     .word DMA1_Stream7_IRQHandler             ;
     .word FSMC_IRQHandler                     ;
     .word SDIO_IRQHandler                     ;
     .word TIM5_IRQHandler                     ;
     .word SPI3_IRQHandler                     ;
     .word UART4_IRQHandler                    ;
     .word 0                                   ;
     .word TIM6_DAC_IRQHandler                 ;
     .word TIM7_IRQHandler                     ;
     .word DMA2_Stream0_IRQHandler             ;
     .word DMA2_Stream1_IRQHandler             ;
     .word DMA2_Stream2_IRQHandler             ;
     .word DMA2_Stream3_IRQHandler             ;
     .word DMA2_Stream4_IRQHandler             ;
     .word ETH_IRQHandler                      ;
     .word 0                                   ;
     .word CAN2_TX_IRQHandler                  ;
     .word CAN2_RX0_IRQHandler                 ;
     .word CAN2_RX1_IRQHandler                 ;
     .word CAN2_SCE_IRQHandler                 ;
     .word USB1_IRQHandler                     ;
     .word DMA2_Stream5_IRQHandler             ;
     .word DMA2_Stream6_IRQHandler             ;
     .word DMA2_Stream7_IRQHandler             ;
     .word USART6_IRQHandler                   ;
     .word I2C3_EV_IRQHandler                  ;
     .word I2C3_ER_IRQHandler                  ;
     .word 0                                   ;
     .word 0                                   ;
     .word 0                                   ;
     .word 0                                   ;
     .word DCMI_IRQHandler                     ;
     .word 0                                   ;
     .word HASH_RNG_IRQHandler                 ;
     .word FPU_IRQHandler                      ;
     .word UART7_IRQHandler                    ;
     .word 0                                   ;
     .word SPI4_IRQHandler                     ;
     .word 0                                   ;
     .word 0                                   ;
     .word 0                                   ;
     .word LTDC_IRQHandler                     ;
     .word 0                                   ;
     .word DMA2D_IRQHandler                    ;
     .word 0                                   ;
     .word DSI_IRQHandler                      ;
     .word 0                                   ;
     .word 0                                   ;
     .word 0                                   ;
     .word HSPI_IRQHandler                     ;
     .word 0                                   ;
     .word JPEGD_IRQHandler                    ;
     .word 0                                   ;
     .word 0                                   ;
     .word 0                                   ;
     .word 0                                   ;
     .word 0                                   ;
     .word 0                                   ;
     .word 0                                   ;
     .word 0                                   ;
     .word 0                                   ;
     .word 0                                   ;
     .word BUSERROR_IRQHandler                 ;

__Vectors_End:
.equ __Vectors_Size,__Vectors_End-__Vectors
/********************************************************/

/*********************reset handle***********************/
.section .text.Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
	movs r0, #0
	movs r1, #0
	movs r2, #0
	movs r3, #0
	movs r4, #0
	movs r5, #0
	movs r6, #0
	movs r7, #0

	LDR R0, =__Vectors
	LDR R1, =0xE000ED08
	STR R0,[R1]
	LDR R0,[R0]
	MOV SP,R0
	
/**数据搬移，配合ld文件**/
	ldr r0, =0x0
	ldr r1, =_sidata
	ldr r2, =_sdata 
	ldr r3, =_edata 
	b LoopCopyDataInit

CopyDataInit:
	ldr r4, [r1, r0]
	str r4, [r2, r0]
	add r0, r0, #4

LoopCopyDataInit:
	add r4, r2, r0
	cmp r3, r4
	bgt CopyDataInit
	
	movs r0, #0
	ldr r1,=_sbss
	ldr r2,=_ebss
	b LoopFillZerobss

FillZerobss:
	str r0, [r1]
	add r1, r1, #4

LoopFillZerobss:
	cmp r2, r1
	bgt FillZerobss

	LDR R0, =SystemInit
	BLX R0

	LDR R0, =main
	BX R0

/********************************************************/
	
.section .text

    .weak NMI_Handler
	.thumb_set NMI_Handler,Default_Handler
	
    .weak MemManage_Handler
	.thumb_set MemManage_Handler,Default_Handler
	
    .weak HardFault_Handler
	.thumb_set HardFault_Handler,Default_Handler
	
    .weak BusFault_Handler
	.thumb_set BusFault_Handler,Default_Handler
	
    .weak UsageFault_Handler
	.thumb_set UsageFault_Handler,Default_Handler
	
    .weak SVC_Handler
	.thumb_set SVC_Handler,Default_Handler
	
    .weak DebugMon_Handler
	.thumb_set DebugMon_Handler,Default_Handler
	
    .weak PendSV_Handler
	.thumb_set PendSV_Handler,Default_Handler
	
    .weak SysTick_Handler
	.thumb_set SysTick_Handler,Default_Handler
	

    .weak WWDG_IRQHandler
    .weak PVD_IRQHandler
    .weak QSPI_IRQHandler
    .weak RCC_IRQHandler
    .weak EXTI0_IRQHandler
    .weak EXTI1_IRQHandler
    .weak EXTI2_IRQHandler
    .weak EXTI3_IRQHandler
    .weak EXTI4_IRQHandler
    .weak DMA1_Stream0_IRQHandler
    .weak DMA1_Stream1_IRQHandler
    .weak DMA1_Stream2_IRQHandler
    .weak DMA1_Stream3_IRQHandler
    .weak DMA1_Stream4_IRQHandler
    .weak DMA1_Stream5_IRQHandler
    .weak DMA1_Stream6_IRQHandler
    .weak ADC_IRQHandler
    .weak CAN1_TX_IRQHandler
    .weak CAN1_RX0_IRQHandler
    .weak CAN1_RX1_IRQHandler
    .weak CAN1_SCE_IRQHandler
    .weak EXTI9_5_IRQHandler
    .weak TIM1_BRK_TIM9_IRQHandler
    .weak TIM1_UP_TIM10_IRQHandler
    .weak TIM1_TRG_COM_TIM11_IRQHandler
    .weak TIM1_CC_IRQHandler
    .weak TIM2_IRQHandler
    .weak TIM3_IRQHandler
    .weak TIM4_IRQHandler
    .weak I2C1_EV_IRQHandler
    .weak I2C1_ER_IRQHandler
    .weak I2C2_EV_IRQHandler
    .weak I2C2_ER_IRQHandler
    .weak SPI1_IRQHandler
    .weak SPI2_IRQHandler
    .weak USART1_IRQHandler
    .weak USART2_IRQHandler
    .weak USART3_IRQHandler
    .weak EXTI15_10_IRQHandler
    .weak RTC_Alarm_IRQHandler
    .weak TIM8_BRK_TIM12_IRQHandler
    .weak TIM8_UP_TIM13_IRQHandler
    .weak TIM8_TRG_COM_TIM14_IRQHandler
    .weak TIM8_CC_IRQHandler
    .weak DMA1_Stream7_IRQHandler
    .weak FSMC_IRQHandler
    .weak SDIO_IRQHandler
    .weak TIM5_IRQHandler
    .weak SPI3_IRQHandler
    .weak UART4_IRQHandler
    .weak TIM6_DAC_IRQHandler
    .weak TIM7_IRQHandler
    .weak DMA2_Stream0_IRQHandler
    .weak DMA2_Stream1_IRQHandler
    .weak DMA2_Stream2_IRQHandler
    .weak DMA2_Stream3_IRQHandler
    .weak DMA2_Stream4_IRQHandler
    .weak ETH_IRQHandler
    .weak CAN2_TX_IRQHandler
    .weak CAN2_RX0_IRQHandler
    .weak CAN2_RX1_IRQHandler
    .weak CAN2_SCE_IRQHandler
    .weak USB1_IRQHandler
    .weak DMA2_Stream5_IRQHandler
    .weak DMA2_Stream6_IRQHandler
    .weak DMA2_Stream7_IRQHandler
    .weak USART6_IRQHandler
    .weak I2C3_EV_IRQHandler
    .weak I2C3_ER_IRQHandler
    .weak DCMI_IRQHandler
    .weak HASH_RNG_IRQHandler
    .weak FPU_IRQHandler
    .weak UART7_IRQHandler
    .weak SPI4_IRQHandler
    .weak LTDC_IRQHandler
    .weak DMA2D_IRQHandler
    .weak DSI_IRQHandler
    .weak HSPI_IRQHandler
    .weak JPEGD_IRQHandler
    .weak BUSERROR_IRQHandler

        
