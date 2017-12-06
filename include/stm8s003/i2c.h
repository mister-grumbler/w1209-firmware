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

#ifndef STM8S003_I2C_H
#define STM8S003_I2C_H

#define	I2C_CR1		*(unsigned char*)0x005210	// I2C control register 1
#define	I2C_CR2		*(unsigned char*)0x005211	// I2C control register 2
#define	I2C_FREQR	*(unsigned char*)0x005212	// I2C frequency register
#define	I2C_OARL	*(unsigned char*)0x005213	// I2C own address register low
#define	I2C_OARH	*(unsigned char*)0x005214	// I2C own address register high
#define	I2C_DR		*(unsigned char*)0x005216	// I2C data register
#define	I2C_SR1		*(unsigned char*)0x005217	// I2C status register 1
#define	I2C_SR2		*(unsigned char*)0x005218	// I2C status register 2
#define	I2C_SR3		*(unsigned char*)0x005219	// I2C status register 3
#define	I2C_ITR		*(unsigned char*)0x00521A	// I2C interrupt control register
#define	I2C_CCRL	*(unsigned char*)0x00521B	// I2C clock control register low
#define	I2C_CCRH	*(unsigned char*)0x00521C	// I2C clock control register high
#define	I2C_TRISER	*(unsigned char*)0x00521D	// I2C TRISE register
#define	I2C_PECR	*(unsigned char*)0x00521E	// I2C packet error checking register

#endif