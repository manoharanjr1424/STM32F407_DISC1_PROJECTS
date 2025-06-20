/*
 * interrupt.h
 *
 *  Created on: Feb 23, 2025
 *      Author: mjayakumar
 */
#ifndef INTERRUPT_H_
#define INTERRUPT_H_


typedef enum
{
    WWDG_IRQn = 0,
    PVD_IRQn,
    TAMP_STAMP_IRQn,
    RTC_WKUP_IRQn,
    FLASH_IRQn,
    RCC_IRQn,
    EXTI0_IRQn,
    EXTI1_IRQn,
    EXTI2_IRQn,
    EXTI3_IRQn,
    EXTI4_IRQn,
    DMA1_Stream0_IRQn,
    DMA1_Stream1_IRQn,
    DMA1_Stream2_IRQn,
    DMA1_Stream3_IRQn,
    DMA1_Stream4_IRQn,
    DMA1_Stream5_IRQn,
    DMA1_Stream6_IRQn,
    ADC_IRQn,
    CAN1_TX_IRQn,
    CAN1_RX0_IRQn,
    CAN1_RX1_IRQn,
    CAN1_SCE_IRQn,
    EXTI9_5_IRQn,
    TIM1_BRK_TIM9_IRQn,
    TIM1_UP_TIM10_IRQn,
    TIM1_TRG_COM_TIM11_IRQn,
    TIM1_CC_IRQn,
    TIM2_IRQn,
    TIM3_IRQn,
    TIM4_IRQn,
    I2C1_EV_IRQn,
    I2C1_ER_IRQn,
    I2C2_EV_IRQn,
    I2C2_ER_IRQn,
    SPI1_IRQn,
    SPI2_IRQn,
    USART1_IRQn,
    USART2_IRQn,
    USART3_IRQn,
    EXTI15_10_IRQn,
    RTC_Alarm_IRQn,
    OTG_FS_WKUP_IRQn,
    TIM8_BRK_TIM12_IRQn,
    TIM8_UP_TIM13_IRQn,
    TIM8_TRG_COM_TIM14_IRQn,
    TIM8_CC_IRQn,
    DMA1_Stream7_IRQn,
    FSMC_IRQn,
    SDIO_IRQn,
    TIM5_IRQn,
    SPI3_IRQn,
    UART4_IRQn,
    UART5_IRQn,
    TIM6_DAC_IRQn,
    TIM7_IRQn,
    DMA2_Stream0_IRQn,
    DMA2_Stream1_IRQn,
    DMA2_Stream2_IRQn,
    DMA2_Stream3_IRQn,
    DMA2_Stream4_IRQn,
    ETH_IRQn,
    ETH_WKUP_IRQn,
    CAN2_TX_IRQn,
    CAN2_RX0_IRQn,
    CAN2_RX1_IRQn,
    CAN2_SCE_IRQn,
    OTG_FS_IRQn,
    DMA2_Stream5_IRQn,
    DMA2_Stream6_IRQn,
    DMA2_Stream7_IRQn,
    USART6_IRQn,
    I2C3_EV_IRQn,
    I2C3_ER_IRQn,
    OTG_HS_EP1_OUT_IRQn,
    OTG_HS_EP1_IN_IRQn,
    OTG_HS_WKUP_IRQn,
    OTG_HS_IRQn,
    DCMI_IRQn,
    CRYP_IRQn,
    HASH_RNG_IRQn,
    FPU_IRQn
} IRQn_Type;


typedef enum {
	NVIC_PriorityGroup_4 = 0,
	NVIC_PriorityGroup_3,
	NVIC_PriorityGroup_2,
	NVIC_PriorityGroup_1,
	NVIC_PriorityGroup_0
}nvicPriorityGrouping;

uint8_t NvicEnableInt(uint8_t IntNumber);
int8_t NvicGetPriority(uint8_t IntNumber);
int8_t  NvicSetPriority(uint8_t IntNumber, uint8_t preEmption, uint8_t subPriority);
int8_t NvicSetPriorityGrouping(nvicPriorityGrouping);
#endif

