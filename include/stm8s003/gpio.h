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

#ifndef STM8S003_GPIO_H
#define STM8S003_GPIO_H

#define	PA_ODR	*(unsigned char*)0x005000	// Port A data output latch register
#define	PA_IDR	*(unsigned char*)0x005001	// Port A input pin value register
#define	PA_DDR	*(unsigned char*)0x005002	// Port A data direction register
#define	PA_CR1	*(unsigned char*)0x005003	// Port A control register 1
#define	PA_CR2	*(unsigned char*)0x005004	// Port A control register 2

#define	PB_ODR	*(unsigned char*)0x005005	// Port B data output latch register
#define	PB_IDR	*(unsigned char*)0x005006	// Port B input pin value register
#define	PB_DDR	*(unsigned char*)0x005007	// Port B data direction register
#define	PB_CR1	*(unsigned char*)0x005008	// Port B control register 1
#define	PB_CR2	*(unsigned char*)0x005009	// Port B control register 2

#define	PC_ODR	*(unsigned char*)0x00500A	// Port C data output latch register
#define	PC_IDR	*(unsigned char*)0x00500B	// Port C input pin value register
#define	PC_DDR	*(unsigned char*)0x00500C	// Port C data direction register
#define	PC_CR1	*(unsigned char*)0x00500D	// Port C control register 1
#define	PC_CR2	*(unsigned char*)0x00500E	// Port C control register 2

#define	PD_ODR	*(unsigned char*)0x00500F	// Port D data output latch register
#define	PD_IDR	*(unsigned char*)0x005010	// Port D input pin value register
#define	PD_DDR	*(unsigned char*)0x005011	// Port D data direction register
#define	PD_CR1	*(unsigned char*)0x005012	// Port D control register 1
#define	PD_CR2	*(unsigned char*)0x005013	// Port D control register 2

#define	PE_ODR	*(unsigned char*)0x005014	// Port E data output latch register
#define	PE_IDR	*(unsigned char*)0x005015	// Port E input pin value register
#define	PE_DDR	*(unsigned char*)0x005016	// Port E data direction register
#define	PE_CR1	*(unsigned char*)0x005017	// Port E control register 1
#define	PE_CR2	*(unsigned char*)0x005018	// Port E control register 2

#define	PF_ODR	*(unsigned char*)0x005019	// Port F data output latch register
#define	PF_IDR	*(unsigned char*)0x00501A	// Port F input pin value register
#define	PF_DDR	*(unsigned char*)0x00501B	// Port F data direction register
#define	PF_CR1	*(unsigned char*)0x00501C	// Port F control register 1
#define	PF_CR2	*(unsigned char*)0x00501D	// Port F control register 2

#define	EXTI_CR1	*(unsigned char*)0x0050A0	// External interrupt control register 1
#define	EXTI_CR2	*(unsigned char*)0x0050A1	// External interrupt control register 2

#endif