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

#ifndef STM8S003_UART_H
#define STM8S003_UART_H

#define	UART1_SR	*(unsigned char*)0x005230	// UART1 status register
#define	UART1_DR	*(unsigned char*)0x005231	// UART1 data register
#define	UART1_BRR1	*(unsigned char*)0x005232	// UART1 baud rate register 1
#define	UART1_BRR2	*(unsigned char*)0x005233	// UART1 baud rate register 2
#define	UART1_CR1	*(unsigned char*)0x005234	// UART1 control register 1
#define	UART1_CR2	*(unsigned char*)0x005235	// UART1 control register 2
#define	UART1_CR3	*(unsigned char*)0x005236	// UART1 control register 3
#define	UART1_CR4	*(unsigned char*)0x005237	// UART1 control register 4
#define	UART1_CR5	*(unsigned char*)0x005238	// UART1 control register 5
#define	UART1_GTR	*(unsigned char*)0x005239	// UART1 guard time register
#define	UART1_PSCR	*(unsigned char*)0x00523A	// UART1 prescaler register

/* USART_CR1 bits */
#define USART_CR1_R8	(1 << 7)
#define USART_CR1_T8	(1 << 6)
#define USART_CR1_UARTD	(1 << 5)
#define USART_CR1_M		(1 << 4)
#define USART_CR1_WAKE	(1 << 3)
#define USART_CR1_PCEN	(1 << 2)
#define USART_CR1_PS	(1 << 1)
#define USART_CR1_PIEN	(1 << 0)

/* USART_CR2 bits */
#define USART_CR2_TIEN	(1 << 7)
#define USART_CR2_TCIEN	(1 << 6)
#define USART_CR2_RIEN	(1 << 5)
#define USART_CR2_ILIEN	(1 << 4)
#define USART_CR2_TEN	(1 << 3)
#define USART_CR2_REN	(1 << 2)
#define USART_CR2_RWU	(1 << 1)
#define USART_CR2_SBK	(1 << 0)

/* USART_CR3 bits */
#define USART_CR3_LINEN	(1 << 6)
#define USART_CR3_STOP2	(1 << 5)
#define USART_CR3_STOP1	(1 << 4)
#define USART_CR3_CLKEN	(1 << 3)
#define USART_CR3_CPOL	(1 << 2)
#define USART_CR3_CPHA	(1 << 1)
#define USART_CR3_LBCL	(1 << 0)

/* USART_SR bits */
#define USART_SR_TXE	(1 << 7)
#define USART_SR_TC		(1 << 6)
#define USART_SR_RXNE	(1 << 5)
#define USART_SR_IDLE	(1 << 4)
#define USART_SR_OR		(1 << 3)
#define USART_SR_NF		(1 << 2)
#define USART_SR_FE		(1 << 1)
#define USART_SR_PE		(1 << 0)

#endif
