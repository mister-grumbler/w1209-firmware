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

#ifndef STM8S003_TIMER_H
#define STM8S003_TIMER_H

#define	TIM1_CR1	*(unsigned char*)0x005250	// TIM1 control register 1
#define	TIM1_CR2	*(unsigned char*)0x005251	// TIM1 control register 2
#define	TIM1_SMCR	*(unsigned char*)0x005252	// TIM1 slave mode control register
#define	TIM1_ETR	*(unsigned char*)0x005253	// TIM1 external trigger register
#define	TIM1_IER	*(unsigned char*)0x005254	// TIM1 Interrupt enable register
#define	TIM1_SR1	*(unsigned char*)0x005255	// TIM1 status register 1
#define	TIM1_SR2	*(unsigned char*)0x005256	// TIM1 status register 2
#define	TIM1_EGR	*(unsigned char*)0x005257	// TIM1 event generation register
#define	TIM1_CCMR1	*(unsigned char*)0x005258	// TIM1 capture/compare mode register 1
#define	TIM1_CCMR2	*(unsigned char*)0x005259	// TIM1 capture/compare mode register 2
#define	TIM1_CCMR3	*(unsigned char*)0x00525A	// TIM1 capture/compare mode register 3
#define	TIM1_CCMR4	*(unsigned char*)0x00525B	// TIM1 capture/compare mode register 4
#define	TIM1_CCER1	*(unsigned char*)0x00525C	// TIM1 capture/compare enable register 1
#define	TIM1_CCER2	*(unsigned char*)0x00525D	// TIM1 capture/compare enable register 2
#define	TIM1_CNTRH	*(unsigned char*)0x00525E	// TIM1 counter high
#define	TIM1_CNTRL	*(unsigned char*)0x00525F	// TIM1 counter low
#define	TIM1_PSCRH	*(unsigned char*)0x005260	// TIM1 prescaler register high
#define	TIM1_PSCRL	*(unsigned char*)0x005261	// TIM1 prescaler register low
#define	TIM1_ARRH	*(unsigned char*)0x005262	// TIM1 auto-reload register high
#define	TIM1_ARRL	*(unsigned char*)0x005263	// TIM1 auto-reload register low
#define	TIM1_RCR	*(unsigned char*)0x005264	// TIM1 repetition counter register
#define	TIM1_CCR1H	*(unsigned char*)0x005265	// TIM1 capture/compare register 1 high
#define	TIM1_CCR1L	*(unsigned char*)0x005266	// TIM1 capture/compare register 1 low
#define	TIM1_CCR2H	*(unsigned char*)0x005267	// TIM1 capture/compare register 2 high
#define	TIM1_CCR2L	*(unsigned char*)0x005268	// TIM1 capture/compare register 2 low
#define	TIM1_CCR3H	*(unsigned char*)0x005269	// TIM1 capture/compare register 3 high
#define	TIM1_CCR3L	*(unsigned char*)0x00526A	// TIM1 capture/compare register 3 low
#define	TIM1_CCR4H	*(unsigned char*)0x00526B	// TIM1 capture/compare register 4 high
#define	TIM1_CCR4L	*(unsigned char*)0x00526C	// TIM1 capture/compare register 4 low
#define	TIM1_BKR	*(unsigned char*)0x00526D	// TIM1 break register
#define	TIM1_DTR	*(unsigned char*)0x00526E	// TIM1 dead-time register
#define	TIM1_OISR	*(unsigned char*)0x00526F	// TIM1 output idle state register

#define	TIM2_CR1	*(unsigned char*)0x005300	// TIM2 control register 1
#define	TIM2_IER	*(unsigned char*)0x005303	// TIM2 interrupt enable register
#define	TIM2_SR1	*(unsigned char*)0x005304	// TIM2 status register 1
#define	TIM2_SR2	*(unsigned char*)0x005305	// TIM2 status register 2
#define	TIM2_EGR	*(unsigned char*)0x005306	// TIM2 event generation register
#define	TIM2_CCMR1	*(unsigned char*)0x005307	// TIM2 capture/compare mode register 1
#define	TIM2_CCMR2	*(unsigned char*)0x005308	// TIM2 capture/compare mode register 2
#define	TIM2_CCMR3	*(unsigned char*)0x005309	// TIM2 capture/compare mode register 3
#define	TIM2_CCER1	*(unsigned char*)0x00530A	// TIM2 capture/compare enable register 1
#define	TIM2_CCER2	*(unsigned char*)0x00530B	// TIM2 capture/compare enable register 2
#define	TIM2_CNTRH	*(unsigned char*)0x00530C	// TIM2 counter high
#define	TIM2_CNTRL	*(unsigned char*)0x00530D	// TIM2 counter low
#define	TIM2_PSCR	*(unsigned char*)0x00530E	// TIM2 prescaler register
#define	TIM2_ARRH	*(unsigned char*)0x00530F	// TIM2 auto-reload register high
#define	TIM2_ARRL	*(unsigned char*)0x005310	// TIM2 auto-reload register low
#define	TIM2_CCR1H	*(unsigned char*)0x005311	// TIM2 capture/compare register 1 high
#define	TIM2_CCR1L	*(unsigned char*)0x005312	// TIM2 capture/compare register 1 low
#define	TIM2_CCR2H	*(unsigned char*)0x005313	// TIM2 capture/compare reg. 2 high
#define	TIM2_CCR2L	*(unsigned char*)0x005314	// TIM2 capture/compare register 2 low
#define	TIM2_CCR3H	*(unsigned char*)0x005315	// TIM2 capture/compare register 3 high
#define	TIM2_CCR3L	*(unsigned char*)0x005316	// TIM2 capture/compare register 3 low

#define	TIM4_CR1	*(unsigned char*)0x005340	// TIM4 control register 1
#define	TIM4_IER	*(unsigned char*)0x005343	// TIM4 interrupt enable register
#define	TIM4_SR		*(unsigned char*)0x005344	// TIM4 status register
#define	TIM4_EGR	*(unsigned char*)0x005345	// TIM4 event generation register
#define	TIM4_CNTR	*(unsigned char*)0x005346	// TIM4 counter
#define	TIM4_PSCR	*(unsigned char*)0x005347	// TIM4 prescaler register
#define	TIM4_ARR	*(unsigned char*)0x005348	// TIM4 auto-reload register

/* TIM_IER bits */
#define TIM_IER_BIE		(1 << 7)
#define TIM_IER_TIE		(1 << 6)
#define TIM_IER_COMIE	(1 << 5)
#define TIM_IER_CC4IE	(1 << 4)
#define TIM_IER_CC3IE	(1 << 3)
#define TIM_IER_CC2IE	(1 << 2)
#define TIM_IER_CC1IE	(1 << 1)
#define TIM_IER_UIE		(1 << 0)

/* TIM_CR1 bits */
#define TIM_CR1_APRE	(1 << 7)
#define TIM_CR1_CMSH	(1 << 6)
#define TIM_CR1_CMSL	(1 << 5)
#define TIM_CR1_DIR		(1 << 4)
#define TIM_CR1_OPM		(1 << 3)
#define TIM_CR1_URS		(1 << 2)
#define TIM_CR1_UDIS	(1 << 1)
#define TIM_CR1_CEN		(1 << 0)

/* TIM_SR1 bits */
#define TIM_SR1_BIF		(1 << 7)
#define TIM_SR1_TIF		(1 << 6)
#define TIM_SR1_COMIF	(1 << 5)
#define TIM_SR1_CC4IF	(1 << 4)
#define TIM_SR1_CC3IF	(1 << 3)
#define TIM_SR1_CC2IF	(1 << 2)
#define TIM_SR1_CC1IF	(1 << 1)
#define TIM_SR1_UIF		(1 << 0)

#endif