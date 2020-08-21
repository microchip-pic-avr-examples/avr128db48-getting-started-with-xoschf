/**
 * \file main.c
 *
 * \brief Main source file.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.
    Subject to your compliance with these terms, you may use this software and
    any derivatives exclusively with Microchip products. It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

#include <avr/io.h>
#include <avr/cpufunc.h>

void CLOCK_XOSCHF_crystal_PLL_init(void);
void TIMER_TCD0_init(void);

int main(void)
{
	CLOCK_XOSCHF_crystal_PLL_init();
	TIMER_TCD0_init();

	/* Replace with your application code */
	while(1)
	{
	}
}


void CLOCK_XOSCHF_crystal_PLL_init(void)
{
	/* Enable crystal oscillator with frequency range 16 MHz and 4K cycles start-up time */
	ccp_write_io((uint8_t *) &CLKCTRL.XOSCHFCTRLA, CLKCTRL_RUNSTDBY_bm
	             | CLKCTRL_CSUTHF_4K_gc
	             | CLKCTRL_FRQRANGE_16M_gc
	             | CLKCTRL_SELHF_CRYSTAL_gc
	             | CLKCTRL_ENABLE_bm);

	/* Confirm crystal oscillator start-up */
	while(!(CLKCTRL.MCLKSTATUS & CLKCTRL_EXTS_bm))
	{
		;
	}

	/* Set the PLL to use XOSCHF as source, and select 3x multiplication factor */
	ccp_write_io((uint8_t *) &CLKCTRL.PLLCTRLA, CLKCTRL_SOURCE_bm | CLKCTRL_MULFAC_3x_gc);

	/* Clear RUNSTDBY for power save during sleep */
	ccp_write_io((uint8_t *) &CLKCTRL.XOSCHFCTRLA, CLKCTRL.XOSCHFCTRLA & ~CLKCTRL_RUNSTDBY_bm);
}


void TIMER_TCD0_init(void)
{
	/* Configure the TCD with PLL (48 MHz) as source */
	TCD0.CTRLA = TCD_CLKSEL_PLL_gc | TCD_CNTPRES_DIV1_gc | TCD_SYNCPRES_DIV1_gc;

	/* Replace with your application configuration */

	/* Enable TCD0 */
	TCD0.CTRLA |= TCD_ENABLE_bm;
}
