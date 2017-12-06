/* 
 * This file is part of the W1209 firmware replacement project
 * (https://github.com/mister-grumbler/w1209-firmware).
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef STM8S003_CLOCK_H
#define STM8S003_CLOCK_H

#define	CLK_ICKR	*(unsigned char*)0x0050C0	// Internal clock control register
#define	CLK_ECKR	*(unsigned char*)0x0050C1	// External clock control register
#define	CLK_CMSR	*(unsigned char*)0x0050C3	// Clock master status register
#define	CLK_SWR		*(unsigned char*)0x0050C4	// Clock master switch register
#define	CLK_SWCR	*(unsigned char*)0x0050C5	// Clock switch control register
#define	CLK_CKDIVR	*(unsigned char*)0x0050C6	// Clock divider register
#define	CLK_PCKENR1	*(unsigned char*)0x0050C7	// Peripheral clock gating register 1
#define	CLK_CSSR	*(unsigned char*)0x0050C8	// Clock security system register
#define	CLK_CCOR	*(unsigned char*)0x0050C9	// Configurable clock control register
#define	CLK_PCKENR2	*(unsigned char*)0x0050CA	// Peripheral clock gating register 2
#define	CLK_HSITRIMR	*(unsigned char*)0x0050CC	// HSI clock calibration trimming register
#define	CLK_SWIMCCR	*(unsigned char*)0x0050CD	// SWIM clock control register

#endif