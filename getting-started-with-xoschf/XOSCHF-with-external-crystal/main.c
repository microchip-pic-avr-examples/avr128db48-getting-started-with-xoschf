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

#define F_CPU 16000000ul

#include <avr/io.h>
#include <avr/cpufunc.h>

void CLOCK_XOSCHF_crystal_init(void);

static inline void LED0_init(void)
{
	PORTB.DIRSET = PIN3_bm;
}

int main(void)
{
	CLOCK_XOSCHF_crystal_init();

	/* Turn on LED0 to show successful clock init */
	LED0_init();

	/* Replace with your application code */
	while(1)
	{
	}
}


void CLOCK_XOSCHF_crystal_init(void)
{
	/* Enable crystal oscillator with frequency range 16MHz and 4K cycles startup time */
	ccp_write_io((uint8_t *) &CLKCTRL.XOSCHFCTRLA, CLKCTRL_RUNSTDBY_bm
	             | CLKCTRL_CSUTHF_4K_gc
	             | CLKCTRL_FRQRANGE_16M_gc
	             | CLKCTRL_SELHF_CRYSTAL_gc
	             | CLKCTRL_ENABLE_bm);

	/* Confirm crystal oscillator startup */
	while(!(CLKCTRL.MCLKSTATUS & CLKCTRL_EXTS_bm))
	{
		;
	}

	/* Clear Main Clock Prescaler */
	ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLB, 0x00);

	/* Set the main clock to use XOSCHF as source, and enable the CLKOUT pin */
	ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_EXTCLK_gc | CLKCTRL_CLKOUT_bm);

	/* Wait for system oscillator changing to complete */
	while(CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm)
	{
		;
	}

	/* Clear RUNSTDBY for power save during sleep */
	ccp_write_io((uint8_t *) &CLKCTRL.XOSCHFCTRLA, CLKCTRL.XOSCHFCTRLA & ~CLKCTRL_RUNSTDBY_bm);

	/* Change complete and the main clock is 16 MHz */
}
