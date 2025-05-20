/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#if defined(FSL_FEATURE_SOC_PORT_COUNT) && (FSL_FEATURE_SOC_PORT_COUNT)
#include "fsl_port.h"
#endif
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "app.h"
#include "pin_mux.h"
#include "board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define led1_GPIO GPIO1
#define led1_Pin 10

#define led2_GPIO GPIO1
#define led2_Pin 12

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Whether the SW button is pressed */
volatile uint32_t tick = 0;
volatile uint8_t state = 0;
volatile bool toggle = false;
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 *
 * @brief Interrupt service fuction of switch.
 *
 * This function toggles the LED
 */

void main1(void){
    GPIO_PinWrite(led1_GPIO, led1_Pin, toggle);
    GPIO_PinWrite(led2_GPIO, led2_Pin, 0);
}
void main2(void){
    GPIO_PinWrite(led2_GPIO, led2_Pin, toggle);
    GPIO_PinWrite(led1_GPIO, led1_Pin, 0);
}
void SysTick_Handler(void);
void delay_ms(uint32_t ms);
void BOARD_SW_IRQ_HANDLER(void)
{
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT) || \
    (!defined(FSL_FEATURE_SOC_PORT_COUNT))
    /* Clear external interrupt flag. */
    GPIO_GpioClearInterruptFlags(BOARD_SW_GPIO, 1U << BOARD_SW_GPIO_PIN);
#else
    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(BOARD_SW_GPIO, 1U << BOARD_SW_GPIO_PIN);
#endif
    /* Change state of button. */
    state = (state == 1) ? 2 : 1; // chuyển qua lại giữa 1 và 2
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */

void SysTick_Handler(void)
{
    tick++;

    static bool toggle = false;

    if (tick >= 500) // 500 * 1ms = 500ms
    {
        tick = 0;
        toggle = !toggle;

        if (state == 1)
        {
          main1();
        }
        else if (state == 2)
        {
        	main2();
        }
        else
        {
            // Nếu state == 0 (chưa nhấn lần nào) thì tắt cả 2 LED
            GPIO_PinWrite(led1_GPIO, led1_Pin, 0);
            GPIO_PinWrite(led2_GPIO, led2_Pin, 0);
        }
    }
}

int main(void)
{
    /* Define the init structure for the input switch pin */
    gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput,
        0,
    };

    /* Define the init structure for the output LED pin */
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        0,
    };

    BOARD_InitHardware();

/* Init input switch GPIO. */
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT) || \
    (!defined(FSL_FEATURE_SOC_PORT_COUNT))
    GPIO_SetPinInterruptConfig(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, kGPIO_InterruptFallingEdge);
#else
    PORT_SetPinInterruptConfig(BOARD_SW_PORT, BOARD_SW_GPIO_PIN, kPORT_InterruptFallingEdge);
#endif
    EnableIRQ(BOARD_SW_IRQ);
    GPIO_PinInit(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, &sw_config);

    /* Init output LED GPIO. */
    GPIO_PinInit(led1_GPIO,led1_Pin, &led_config);
    GPIO_PinInit(led2_GPIO,led2_Pin, &led_config);
    SysTick_Config(CLOCK_GetFreq(kCLOCK_CoreSysClk) / 1000U);

    while (1)
    {

    }
}
