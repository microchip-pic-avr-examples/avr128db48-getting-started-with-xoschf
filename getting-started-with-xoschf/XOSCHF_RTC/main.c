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
#include <avr/interrupt.h>

void CLOCK_XOSCHF_crystal_init(void);
void TIMER_RTC_init(void);

static inline void LED0_init(void)
{
	PORTF.DIRSET = PIN5_bm;
	PORTF.OUTSET = PIN5_bm;
}

static inline void LED0_toggle(void)
{
	PORTF.OUTTGL = PIN5_bm;
}

int main(void)
{
	CLOCK_XOSCHF_crystal_init();
	TIMER_RTC_init();
	LED0_init();

	/* Enable global interrupts */
	sei();

	/* Replace with your application code */
	while(1)
	{
	}
}


void CLOCK_XOSCHF_crystal_init(void)
{
	/* Enable crystal oscillator with frequency range 8MHz and 1K cycles startup time */
	ccp_write_io((uint8_t *) &CLKCTRL.XOSCHFCTRLA, CLKCTRL_RUNSTDBY_bm
	             | CLKCTRL_CSUTHF_1K_gc
	             | CLKCTRL_FRQRANGE_8M_gc
	             | CLKCTRL_SELHF_CRYSTAL_gc
	             | CLKCTRL_ENABLE_bm);

	/* Confirm crystal oscillator startup */
	while(!(CLKCTRL.MCLKSTATUS & CLKCTRL_EXTS_bm))
	{
		;
	}

	/* Clear RUNSTDBY for power save during sleep */
	ccp_write_io((uint8_t *) &CLKCTRL.XOSCHFCTRLA, CLKCTRL.XOSCHFCTRLA & ~CLKCTRL_RUNSTDBY_bm);
}


void TIMER_RTC_init(void)
{
	while(RTC.STATUS > 0)
	{
		/* Wait for RTC registers to synchronize */
	}

	/* Configure RTC to use XOSCHF as source */
	RTC.CLKSEL = RTC_CLKSEL_EXTCLK_gc;

	/* Replace with your application configuration */
	RTC.PER = 0xffff;
	RTC.INTCTRL = RTC_OVF_bm;
	RTC.CTRLA = RTC_PRESCALER_DIV32_gc | RTC_RTCEN_bm;
}


ISR(RTC_CNT_vect)
{
	/* This interrupt will trigger every time the RTC overflows */
	LED0_toggle();

	/* Clear the RTC overflow interrupt flag */
	RTC.INTFLAGS = RTC_OVF_bm;
}