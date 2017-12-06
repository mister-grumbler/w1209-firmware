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

#ifndef STM8S003_SPI_H
#define STM8S003_SPI_H

#define	SPI_CR1		*(unsigned char*)0x005200	// SPI control register 1
#define	SPI_CR2		*(unsigned char*)0x005201	// SPI control register 2
#define	SPI_ICR		*(unsigned char*)0x005202	// SPI interrupt control register
#define	SPI_SR		*(unsigned char*)0x005203	// SPI status register
#define	SPI_DR		*(unsigned char*)0x005204	// SPI data register
#define	SPI_CRCPR	*(unsigned char*)0x005205	// SPI CRC polynomial register
#define	SPI_RXCRCR	*(unsigned char*)0x005206	// SPI Rx CRC register
#define	SPI_TXCRCR	*(unsigned char*)0x005207	// SPI Tx CRC register

#endif