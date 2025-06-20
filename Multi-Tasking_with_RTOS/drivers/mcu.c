

#include "mcu.h"
#include "timer.h"



#define HSI_CLOCK 16000000UL
#define PLL_CLOCK 180000000UL
#define LSE_CLOCK 32000000UL
#define __FPU_PRESENT 1
#define __FPU_USED 1


uint32_t GetSystemClockFrequency(uint8_t _SystemBus) {


    uint8_t ui8_LocalClockSource = 0;

    // Extract bits 3:2 (SWS) and right-align
    ui8_LocalClockSource = (RCC->CFGR >> 2) & 0x3;

    switch (ui8_LocalClockSource)
    {
        case 0:
            return HSI_CLOCK;  // Internal 16 MHz
        case 1:
            //return HSE_CLOCK;  // External crystal (e.g. 8 MHz)
        case 2:
            return PLL_CLOCK;  // Usually 168 MHz for STM32F407
        default:
            return 0; // Unknown
    }

}


uint32_t GetAPB1ClockFrequency(void)
{
    uint32_t system_clock = 0;
    uint32_t ahb_prescaler = 1;
    uint32_t apb1_prescaler = 1;
    uint8_t clock_source = 0;

    // 1. Get system clock source
    clock_source = (RCC->CFGR >> 2) & 0x3;

    switch (clock_source)
    {
        case 0: // HSI
            system_clock = 16000000;
            break;
        case 1: // HSE
            system_clock = 8000000;
            break;
        case 2: // PLL
            // You must calculate PLL output here
            // Let's assume you've configured PLL to 168 MHz
            system_clock = 168000000;
            break;
    }

    // 2. Get AHB prescaler
    uint8_t ahb_presc_val = (RCC->CFGR >> 4) & 0xF;
    const uint16_t AHBPrescTable[16] = {
        1, 1, 1, 1, 1, 1, 1, 1,
        2, 4, 8, 16, 64, 128, 256, 512
    };
    ahb_prescaler = AHBPrescTable[ahb_presc_val];

    // 3. Get APB1 prescaler
    uint8_t apb1_presc_val = (RCC->CFGR >> 10) & 0x7;
    const uint8_t APBPrescTable[8] = {
        1, 1, 1, 1,
        2, 4, 8, 16
    };
    apb1_prescaler = APBPrescTable[apb1_presc_val];

    // 4. Final APB1 clock = SYSCLK / AHB_Presc / APB1_Presc
    return (system_clock / ahb_prescaler) / apb1_prescaler;
}


void SystemInit(void)
{
    /* FPU settings ------------------------------------------------------------*/
    #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
        (*CPACR) |= ((3UL << 20U)|(3UL << 22U));  /* set CP10 and CP11 Full Access */
    #endif
}
