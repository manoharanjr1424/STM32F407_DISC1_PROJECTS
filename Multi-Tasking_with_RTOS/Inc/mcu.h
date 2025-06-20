/******************************************************************************
 * @file    <mcu.h>
 * @brief   <Brief description of the file or module functionality>
 * @author  <Author Name>
 * @date    <Date of creation or modification>
 *
 * @details This file contains definitions for <brief description of what the file does>
 *          and includes symbolic constants for edge detection, signal states,
 *          and control signals.
 *
 *          The edge detection constants are used to configure interrupt triggers
 *          for signal transitions, and the signal states represent the logic levels
 *          for input/output control. This module provides basic macros for
 *          configuring GPIOs and other hardware interfaces.
 *
 *
 * @note    Additional notes or warnings about the code can be included here.
 * @warning Potential risks or cautions associated with using these definitions.
 ******************************************************************************
 */


#ifndef MCU_H_
#define MCU_H_

#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define __VO volatile
#define FULL_WORD uint32_t
#define FALLINGEDGE 1
#define RISINGEDGE  2
#define BOTHEDGE 	3

#define LOW     0
#define SUCCESS LOW
#define OUTPUT 	LOW
#define DISABLE LOW

#define HIGH 	1
#define INPUT 	HIGH
#define FAILED  HIGH
#define ENABLE  HIGH


/*
 * Peripheral Bus Base Addresses for STM32F407 DISC1
 * -------------------------------------------------
 * These macros define the base addresses of the main peripheral buses:
 * - APB1: Advanced Peripheral Bus 1
 * - APB2: Advanced Peripheral Bus 2
 * - AHB1: Advanced High-performance Bus 1
 * - AHB2/AHB3: Additional high-performance buses for specialized peripherals
 *
 * All peripheral addresses branch off from PHERIPHERAL_BASE_ADDR (0x40000000U).
 */
#define PHERIPHERAL_BASE_ADDR 0x40000000U
#define PHERIPHERAL_APB1_ADDR PHERIPHERAL_BASE_ADDR
#define PHERIPHERAL_APB2_ADDR (PHERIPHERAL_BASE_ADDR + 0x10000)
#define PHERIPHERAL_AHB1_ADDR (PHERIPHERAL_BASE_ADDR + 0x20000)
#define PHERIPHERAL_AHB2_ADDR 0x50000000U
#define PHERIPHERAL_AHB3_ADDR 0xA0000000U

/*
 * GPIO Peripheral Base Addresses (AHB1 Bus)
 * -----------------------------------------
 * These macros define base addresses for GPIO ports A to I on the STM32F407 DISC1,
 * all located on the AHB1 bus. The offset between each GPIO port is 0x0400.
 */

#define GPIO_BASE_ADDR 	 (PHERIPHERAL_AHB1_ADDR)

/*
 * RCC and SYSCFG/EXTI Base Addresses
 * ----------------------------------
 * These macros define base addresses for key control blocks:
 * - RCC (Reset and Clock Control) on AHB1
 * - SYSCFG (System Configuration) and EXTI (External Interrupt) on APB2
 */

#define RCC_BASE_ADDR  	 (PHERIPHERAL_AHB1_ADDR + 0x3800)
#define SYSCFG_BASE_ADDR (PHERIPHERAL_APB2_ADDR + 0x3800)
#define EXTI_BASE_ADDR	 (PHERIPHERAL_APB2_ADDR + 0x3C00)


/*
 * GPIO Peripheral Base Addresses (AHB1 Bus)
 * -----------------------------------------
 * These macros define base addresses for GPIO ports A to I on the STM32F407 DISC1,
 * all located on the AHB1 bus. The offset between each GPIO port is 0x0400.
 */

#define GPIOA_BASE_ADDR GPIO_BASE_ADDR
#define GPIOB_BASE_ADDR (PHERIPHERAL_AHB1_ADDR + 0x0400)
#define GPIOC_BASE_ADDR (PHERIPHERAL_AHB1_ADDR + 0x0800)
#define GPIOD_BASE_ADDR (PHERIPHERAL_AHB1_ADDR + 0x0C00)
#define GPIOE_BASE_ADDR (PHERIPHERAL_AHB1_ADDR + 0x1000)
#define GPIOF_BASE_ADDR (PHERIPHERAL_AHB1_ADDR + 0x1400)
#define GPIOG_BASE_ADDR (PHERIPHERAL_AHB1_ADDR + 0x1800)
#define GPIOH_BASE_ADDR (PHERIPHERAL_AHB1_ADDR + 0x1C00)
#define GPIOI_BASE_ADDR (PHERIPHERAL_AHB1_ADDR + 0x2000)
/*
 * Timer Peripheral Base Address (APB2 Bus)
 * ----------------------------------------
 * This macro defines the base address of Timer 9 (TIM9), located on the APB2 bus.
 */

#define TIMER9_BASE_ADDR (PHERIPHERAL_APB2_ADDR + 0x4000)


/*
 * I2C Peripheral Base Addresses (APB1 Bus)
 * ----------------------------------------
 * These macros define the base addresses for I2C peripherals 1 to 3.
 */


#define I2C1_BASE_ADDR (PHERIPHERAL_BASE_ADDR + 0x5400)
#define I2C2_BASE_ADDR (PHERIPHERAL_BASE_ADDR + 0x5800)
#define I2C3_BASE_ADDR (PHERIPHERAL_BASE_ADDR + 0x5C00)

/*
 * USART and UART Peripheral Base Addresses
 * ----------------------------------------
 * These macros define the base addresses for USART and UART peripherals:
 * - USART1, USART6 are on APB2
 * - USART2, USART3, UART4–8 are on APB1
 */

#define USART1_BASE_ADDR (PHERIPHERAL_APB2_ADDR + 0x1000)
#define USART2_BASE_ADDR (PHERIPHERAL_APB1_ADDR + 0x4400)
#define USART3_BASE_ADDR (PHERIPHERAL_APB1_ADDR + 0x4800)
#define UART4_BASE_ADDR  (PHERIPHERAL_APB1_ADDR + 0x4C00)
#define UART5_BASE_ADDR  (PHERIPHERAL_APB1_ADDR + 0x5000)
#define USART6_BASE_ADDR (PHERIPHERAL_APB2_ADDR + 0x1400)
#define UART7_BASE_ADDR  (PHERIPHERAL_APB1_ADDR + 0x7800)
#define UART8_BASE_ADDR  (PHERIPHERAL_APB1_ADDR + 0x7C00)


#define CPACR  (uint32_t *)0xE000ED88



/*
 * rcc_register_t - RCC (Reset and Clock Control) Register Definition
 * -------------------------------------------------------------------
 * Represents the register layout of the RCC peripheral in STM32F407 DISC1.
 * Used to control system clocks, peripheral enable/reset, and clock configuration.
 *
 * Note: Reserved fields are included for proper memory alignment.
 */

typedef struct {
	__VO FULL_WORD CR;
	__VO FULL_WORD PLLCFGR;
	__VO FULL_WORD CFGR;
	__VO FULL_WORD CIR;
	__VO FULL_WORD AHB1RSTR;
	__VO FULL_WORD AHB2RSTR;
	__VO FULL_WORD AHB3RSTR;
	FULL_WORD Reserved1;
	__VO FULL_WORD APB1RSTR;
	__VO FULL_WORD APB2RSTR;
	FULL_WORD Reserved2[2];
	__VO FULL_WORD AHB1ENR;
	__VO FULL_WORD AHB2ENR;
	__VO FULL_WORD AHB3ENR;
	FULL_WORD Reserved3;
	__VO FULL_WORD APB1ENR;
	__VO FULL_WORD APB2ENR;
	FULL_WORD Reserved4[2];
	__VO FULL_WORD AHB1LPENR;
	__VO FULL_WORD AHB2LPENR;
	__VO FULL_WORD AHB3LPENR;
	FULL_WORD Reserved5;
	__VO FULL_WORD APB1LPENR;
	__VO FULL_WORD APB2LPENR;
	FULL_WORD Reserved6[2];
	__VO FULL_WORD RCC_BDCR;
	__VO FULL_WORD CSR;
	FULL_WORD Reserved7[2];
	__VO FULL_WORD SSCGR;
	__VO FULL_WORD PLLI2SCFGR;
} rcc_register_t;

/**
 * @brief APB1 Peripheral Clock Enable Bit Positions
 *
 * This enumeration defines the bit positions for enabling
 * APB1 peripherals in the RCC APB1ENR register.
 */


typedef enum {
    ENABLE_TIM2      = 0,
    ENABLE_TIM3      = 1,
    ENABLE_TIM4      = 2,
    ENABLE_TIM5      = 3,
    ENABLE_TIM6      = 4,
    ENABLE_TIM7      = 5,
    ENABLE_TIM12     = 6,
    ENABLE_TIM13     = 7,
    ENABLE_TIM14     = 8,
    ENABLE_WWDG      = 11,
    ENABLE_USART2    = 17,
    ENABLE_USART3    = 18,
    ENABLE_UART4     = 19,
    ENABLE_UART5     = 20,
    ENABLE_I2C1      = 21,
    ENABLE_I2C2      = 22,
    ENABLE_I2C3      = 23,
    ENABLE_CAN1      = 25,
    ENABLE_CAN2      = 26
}APB1PeripheralEnableBits;

/**
 * @brief APB2 Peripheral Clock Enable Bit Positions
 *
 * This enumeration defines the bit positions for enabling
 * APB2 peripherals in the RCC APB2ENR register.
 */

typedef enum {
    ENABLE_TIM1   = 0,
    ENABLE_TIM8   = 1,
    ENABLE_USART1 = 4,
    ENABLE_USART6 = 5,
    ENABLE_ADC1   = 8,
    ENABLE_ADC2   = 9,
    ENABLE_ADC3   = 10,
    ENABLE_SDIO   = 11,
    ENABLE_SPI1   = 12,
    ENABLE_SYSCFG = 14,
    ENABLE_TIM9   = 16,
    ENABLE_TIM10  = 17,
    ENABLE_TIM11  = 18
}APB2PeripheralEnableBits;



/*
 * gpio_register_t - GPIO Port Register Definition
 * -----------------------------------------------
 * Represents the register map of GPIO ports (A to I).
 * Used for configuring pin modes, output types, speed, pull-up/down,
 * and data input/output operations.
 */

typedef struct {
	__VO FULL_WORD MODER;
	__VO FULL_WORD OTYPER;
	__VO FULL_WORD OSPEEDR;
	__VO FULL_WORD PUPDR;
	__VO FULL_WORD IDR;
	__VO FULL_WORD ODR;
	__VO FULL_WORD BSRR;
	__VO FULL_WORD LCKR;
	__VO FULL_WORD AFRL;
	__VO FULL_WORD AFRH;
} gpio_register_t;


/*
 * usart_register_t - USART/UART Peripheral Register Definition
 * ------------------------------------------------------------
 * Represents the internal registers of a USART/UART peripheral.
 * Used for serial communication setup and control including baud rate,
 * transmission/reception control, and status flags.
 */


typedef struct {
	__VO FULL_WORD SR;
	__VO FULL_WORD DR;
	__VO FULL_WORD BRR;
	__VO FULL_WORD CR1;
	__VO FULL_WORD CR2;
	__VO FULL_WORD CR3;
	__VO FULL_WORD GTPR;
}usart_register_t;


/*
 * spi_register_t - SPI Peripheral Register Definition
 * ---------------------------------------------------
 * Placeholder for SPI register structure.
 * Should be defined according to the STM32F407 SPI register map
 * if SPI functionality is to be implemented.
 */


typedef struct {

} spi_register_t;


/*
 * i2c_register_t - I2C Peripheral Register Definition
 * ---------------------------------------------------
 * Represents the I2C register layout for configuration and data transfer.
 * Includes control, address, status, data, and timing registers.
 * Used for I2C master/slave communication.
 */

typedef struct {
	__VO FULL_WORD I2C_CR1;
	__VO FULL_WORD I2C_CR2;
	__VO FULL_WORD I2C_OAR1;
	__VO FULL_WORD I2C_OAR2;
	__VO FULL_WORD I2C_DR;
	__VO FULL_WORD I2C_SR1;
	__VO FULL_WORD I2C_SR2;
	__VO FULL_WORD I2C_CCR;
	__VO FULL_WORD I2C_TRISE;
	__VO FULL_WORD I2C_FLTR;

} i2c_register_t;

/*
 * tmr_9_register_t - Timer 9 Peripheral Register Definition
 * ---------------------------------------------------------
 * Represents the registers for Timer 9 in STM32F407 DISC1.
 * Used for time base generation, PWM, and input capture functionality.
 * Includes counter, prescaler, auto-reload, and capture/compare registers.
 */


typedef struct {
	__VO FULL_WORD TIM_CR1;
	__VO FULL_WORD TIM_CR2;
	__VO FULL_WORD TIM_SMCR;
	__VO FULL_WORD TIM_DIER;
	__VO FULL_WORD TIM_SR;
	__VO FULL_WORD TIM_EGR;
	__VO FULL_WORD TIM_CCMR1;
	FULL_WORD reserved0;
	__VO FULL_WORD TIM_CCER;
	__VO FULL_WORD TIM_CNT;
	__VO FULL_WORD TIM_PSC;
	__VO FULL_WORD TIM_ARR;
	FULL_WORD reserved1;
	__VO FULL_WORD TIM_CCR1;
	__VO FULL_WORD TIM_CCR2;
} tmr_9_register_t;

/*
 * syscfg_register_t - System Configuration Controller Register Definition
 * -----------------------------------------------------------------------
 * Provides access to system-level configuration features.
 * Includes memory remapping, external interrupt configuration,
 * and compensation cell control.
 */

typedef struct {

	__VO FULL_WORD SYSCFG_MEMRM;
	__VO FULL_WORD SYSCFG_PMC;
	__VO FULL_WORD SYSCFG_EXTICR[4];
	__VO FULL_WORD SYSCFG_CMPCR;
} syscfg_register_t;

/*
 * exti_register_t - External Interrupt/Event Controller Register Definition
 * -------------------------------------------------------------------------
 * Represents the register structure for handling external interrupt lines.
 * Supports interrupt/event masking, edge selection (rising/falling),
 * software trigger, and pending flag management.
 */

typedef struct {
	__VO FULL_WORD EXTI_IMR;
	__VO FULL_WORD EXTI_EMR;
	__VO FULL_WORD EXTI_RTSR;
	__VO FULL_WORD EXTI_FTSR;
	__VO FULL_WORD EXTI_SWIER;
	__VO FULL_WORD EXTI_PR;
} exti_register_t;


/*
 * extiConfg_t - EXTI Port Source Enum
 * -----------------------------------
 * Enumerates GPIO ports used for EXTI line configuration.
 * Each value represents a GPIO port (A–I) used in SYSCFG_EXTICR for pin-to-line mapping.
 */

typedef enum {
	PAEXTIPIN = 0,
	PBEXTIPIN = 1,
	PCEXTIPIN = 2,
	PDEXTIPIN = 3,
	PEEXTIPIN = 4,
	PFEXTIPIN = 5,
	PGEXTIPIN = 6,
	PHEXTIPIN = 7,
	PIEXTIPIN = 8
} extiConfg_t;


typedef enum {
	AHB_SYSTEMBUS,
	APB1_SYSTEMBUS,
	APB2_SYSTEMBUS,
}systemPheripheralBus;



#define RCC   ((rcc_register_t  *)RCC_BASE_ADDR)

/*
 * GPIO Peripheral Base Pointers
 * -----------------------------
 * These macros define pointers to the base addresses of the General Purpose
 * Input/Output (GPIO) peripheral register structures. Each GPIO port
 * (A to I) is mapped to its corresponding memory-mapped base address
 * and cast to a 'gpio_register_t *' structure for direct register access.
 *
 * These macros enable low-level control of GPIO functionality such as
 * pin direction, output levels, input reading, alternate function
 * configuration, and more.
 *
 * Usage Example:
 *   GPIOA->MODER |= (1 << (2 * PIN)); // Configure GPIOA PIN as output
 *   GPIOB->ODR |= (1 << PIN);         // Set GPIOB PIN high
 *
 * Note:
 * - Ensure that the base address macros (e.g., GPIOA_BASE_ADDR) are defined
 *   correctly based on the MCU's memory map.
 * - The 'gpio_register_t' structure should match the MCU’s GPIO register layout
 *   (e.g., MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, etc.).
 */

#define GPIOA ((gpio_register_t *)GPIOA_BASE_ADDR)
#define GPIOB ((gpio_register_t *)GPIOB_BASE_ADDR)
#define GPIOC ((gpio_register_t *)GPIOC_BASE_ADDR)
#define GPIOD ((gpio_register_t *)GPIOD_BASE_ADDR)
#define GPIOE ((gpio_register_t *)GPIOE_BASE_ADDR)
#define GPIOF ((gpio_register_t *)GPIOF_BASE_ADDR)
#define GPIOG ((gpio_register_t *)GPIOG_BASE_ADDR)
#define GPIOH ((gpio_register_t *)GPIOH_BASE_ADDR)
#define GPIOI ((gpio_register_t *)GPIOI_BASE_ADDR)


/*
 * GPIO Port Clock Enable Macros (AHB1 Bus)
 * ----------------------------------------
 * These macros enable the clock for the respective GPIO ports (A to F)
 * by setting the corresponding bits in the AHB1ENR (AHB1 peripheral clock
 * enable register) of the RCC (Reset and Clock Control) module.
 *
 * Before accessing or configuring any GPIO registers, the corresponding
 * port's clock must be enabled; otherwise, the peripheral will remain
 * disabled and unresponsive.
 *
 * Usage Example:
 *   GPIOAEN; // Enables clock for GPIOA
 *   GPIOBEN; // Enables clock for GPIOB
 *
 * Bit Positions in RCC->AHB1ENR:
 *   - Bit 0: GPIOAEN
 *   - Bit 1: GPIOBEN
 *   - Bit 2: GPIOCEN
 *   - Bit 3: GPIODEN
 *   - Bit 4: GPIOEEN
 *   - Bit 5: GPIOFEN
 *
 * Note:
 * - Make sure the RCC struct is properly defined and accessible.
 * - Always enable the corresponding GPIO clock before configuring GPIO pins.
 */


#define GPIOAEN (RCC->AHB1ENR |= 1)
#define GPIOBEN (RCC->AHB1ENR |= (1 << 1))
#define GPIOCEN (RCC->AHB1ENR |= (1 << 2))
#define GPIODEN (RCC->AHB1ENR |= (1 << 3))
#define GPIOEEN (RCC->AHB1ENR |= (1 << 4))
#define GPIOFEN (RCC->AHB1ENR |= (1 << 5))



/*
 * System Configuration (SYSCFG) and External Interrupt (EXTI) Base Pointers
 * -------------------------------------------------------------------------
 * These macros define pointers to the base addresses of the SYSCFG and EXTI
 * peripheral register structures. They allow structured access to system
 * configuration controls and external interrupt/event management features.
 *
 * - SYSCFG: Used for configuration of external interrupt sources, memory remapping,
 *   and peripheral-specific settings. It plays a key role in connecting GPIO pins
 *   to EXTI lines for interrupt handling.
 *
 * - EXTI: Manages external interrupts and events. The EXTI peripheral handles
 *   edge detection, interrupt/event masking, and pending interrupt flags for
 *   external signal lines.
 *
 * Usage Example:
 *   SYSCFG->EXTICR[0] |= (1 << 4);  // Map EXTI0 line to port B
 *   EXTI->IMR |= (1 << 0);          // Unmask EXTI0 interrupt line
 *   EXTI->RTSR |= (1 << 0);         // Enable rising edge trigger on EXTI0
 *
 * Note:
 * - Ensure SYSCFG_BASE_ADDR and EXTI_BASE_ADDR are defined as per the MCU's memory map.
 * - The 'syscfg_register_t' and 'exti_register_t' structures must match the actual
 *   register layout for proper access and control.
 */


#define SYSCFG ((syscfg_register_t *)SYSCFG_BASE_ADDR)
#define EXTI   ((exti_register_t *)EXTI_BASE_ADDR)


/*
 * NVIC Interrupt Set-Enable Register (ISER) Macros
 * ------------------------------------------------
 * These macros define direct pointers to the NVIC ISER (Interrupt Set-Enable Registers),
 * which are used to enable external interrupt lines in ARM Cortex-M based systems.
 *
 * Each macro points to a 32-bit register that controls 32 interrupt lines.
 * Writing a '1' to a bit in any of these registers enables the corresponding IRQ.
 *
 * Base Address: 0xE000E100 (Start of ISER block in the System Control Space)
 *
 * Registers:
 *   - NVIC_ISER0 : IRQ 0  to 31
 *   - NVIC_ISER1 : IRQ 32 to 63
 *   - NVIC_ISER2 : IRQ 64 to 95
 *   - NVIC_ISER3 : IRQ 96 to 127
 *   - NVIC_ISER4 : IRQ 128 to 159
 *   - NVIC_ISER5 : IRQ 160 to 191
 *   - NVIC_ISER6 : IRQ 192 to 223
 *   - NVIC_ISER7 : IRQ 224 to 255
 *
 * Usage Example:
 *   *NVIC_ISER1 = (1 << (USART1_IRQn % 32)); // Enable USART1 interrupt
 *
 * Note:
 * - Ensure that 'FULL_WORD' is defined as a 32-bit data type (e.g., uint32_t).
 * - The NVICusart_register_t_ISER5 macro name appears to be incorrect; consider renaming it to NVIC_ISER5.
 */


#define NVIC_ISER0 ((FULL_WORD *)0xE000E100)
#define NVIC_ISER1 ((FULL_WORD *)0xE000E104)
#define NVIC_ISER2 ((FULL_WORD *)0xE000E108)
#define NVIC_ISER3 ((FULL_WORD *)0xE000E10C)
#define NVIC_ISER4 ((FULL_WORD *)0xE000E110)
#define NVICusart_register_t_ISER5 ((FULL_WORD *)0xE000E114)
#define NVIC_ISER6 ((FULL_WORD *)0xE000E118)
#define NVIC_ISER7 ((FULL_WORD *)0xE000E11C)


#define NVIC_IPR_BASE  ((volatile uint32_t*)0xE000E400)
#define NVIC_IPR(n)    (*(NVIC_IPR_BASE + (n / 4) ) )
#define TIMER9 	((tmr_9_register_t *)TIMER9_BASE_ADDR)




#define ACTLR (*(uint32_t *)0xE000E008)
#define AIRCR (*(uint32_t *)0xE000ED0C)

/*
 * USART and UART Peripheral Base Pointers
 * ---------------------------------------
 * These macros define pointers to the base addresses of USART and UART
 * peripheral registers. Each macro casts the corresponding base address
 * to a pointer of type 'usart_register_t *', allowing structured access
 * to the peripheral registers for configuration and data transfer.
 *
 * These macros are essential for low-level hardware access in
 * register-level embedded programming, typically used in drivers or
 * peripheral abstraction layers.
 *
 * Usage Example:
 *   USART1->CR1 |= (1 << 13); // Enable USART1 by setting UE bit
 *
 * Note:
 * - Make sure the base addresses (e.g., USART1_BASE_ADDR) are defined
 *   correctly as per the device memory map.
 * - The 'usart_register_t' struct must match the register layout of
 *   the respective peripheral.
 */

#define USART1 ((usart_register_t *) USART1_BASE_ADDR)
#define USART2 ((usart_register_t *) USART2_BASE_ADDR)
#define USART3 ((usart_register_t *) USART3_BASE_ADDR)
#define UART4  ((usart_register_t *) UART4_BASE_ADDR)
#define UART5  ((usart_register_t *) UART5_BASE_ADDR)
#define USART6 ((usart_register_t *) USART6_BASE_ADDR)
#define UART7  ((usart_register_t *) UART7_BASE_ADDR)
#define UART8  ((usart_register_t *) UART8_BASE_ADDR)


/*
 * I2C Peripheral Base Pointers
 * ----------------------------
 * These macros define pointers to the base addresses of the I2C peripheral
 * registers. Each macro casts the corresponding base address to a pointer
 * of type 'i2c_register_t *', enabling structured access to the I2C
 * peripheral's control and status registers.
 *
 * These macros are commonly used in low-level embedded software to configure
 * and operate I2C interfaces without relying on high-level libraries.
 *
 * Usage Example:
 *   I2C1->CR1 |= (1 << 0); // Enable I2C1 by setting the PE (Peripheral Enable) bit
 *
 * Note:
 * - Ensure that the base address macros (e.g., I2C1_BASE_ADDR) are defined
 *   according to the device's memory map.
 * - The 'i2c_register_t' struct should match the register layout of the
 *   microcontroller's I2C peripheral.
 */
#define I2C1 ((i2c_register_t*)I2C1_BASE_ADDR)
#define I2C2 ((i2c_register_t*)I2C2_BASE_ADDR)
#define I2C3 ((i2c_register_t*)I2C3_BASE_ADDR)



uint32_t GetSystemClockFrequency(uint8_t _SystemBus);
void SystemInit(void);
uint32_t GetAPB1ClockFrequency(void);
#define ENABLE_FPU() (SystemInit())


#endif /* MCU_H_ */
