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

#ifndef STM8S003_ADC_H
#define STM8S003_ADC_H

#define	ADC_DBxR	*(unsigned char[0x14]*)0x0053E0	// ADC data buffer registers
#define	ADC_CSR		*(unsigned char*)0x005400	// ADC control/status register
#define	ADC_CR1		*(unsigned char*)0x005401	// ADC configuration register 1
#define	ADC_CR2		*(unsigned char*)0x005402	// ADC configuration register 2
#define	ADC_CR3		*(unsigned char*)0x005403	// ADC configuration register 3
#define	ADC_DRH		*(unsigned char*)0x005404	// ADC data register high
#define	ADC_DRL		*(unsigned char*)0x005405	// ADC data register low
#define	ADC_TDRH	*(unsigned char*)0x005406	// ADC Schmitt trigger disable register high
#define	ADC_TDRL	*(unsigned char*)0x005407	// ADC Schmitt trigger disable register low
#define	ADC_HTRH	*(unsigned char*)0x005408	// ADC high threshold register high
#define	ADC_HTRL	*(unsigned char*)0x005409	// ADC high threshold register low
#define	ADC_LTRH	*(unsigned char*)0x00540A	// ADC low threshold register high
#define	ADC_LTRL	*(unsigned char*)0x00540B	// ADC low threshold register low
#define	ADC_AWSRH	*(unsigned char*)0x00540C	// ADC analog watchdog status register high
#define	ADC_AWSRL	*(unsigned char*)0x00540D	// ADC analog watchdog status register low
#define	ADC_AWCRH	*(unsigned char*)0x00540E	// ADC analog watchdog control register high
#define	ADC_AWCRL	*(unsigned char*)0x00540F	// ADC analog watchdog control register low

#endif