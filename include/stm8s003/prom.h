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

#ifndef STM8S003_PROM_H
#define STM8S003_PROM_H

#define	FLASH_CR1	*(unsigned char*)0x00505A	// Flash control register 1
#define	FLASH_CR2	*(unsigned char*)0x00505B	// Flash control register 2
#define	FLASH_NCR2	*(unsigned char*)0x00505C	// Flash complementary control register 2
#define	FLASH_FPR	*(unsigned char*)0x00505D	// Flash protection register
#define	FLASH_NFPR	*(unsigned char*)0x00505E	// Flash complementary protection register
#define	FLASH_IAPSR	*(unsigned char*)0x00505F	// Flash in-application programming status register
#define	FLASH_PUKR	*(unsigned char*)0x005062	// Flash Program memory unprotection register

#define	FLASH_DUKR	*(unsigned char*)0x005064	// Data EEPROM unprotection register

#endif