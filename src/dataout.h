/* Waltech WBO2 for the ATmega8
 *
 * Copyright 2010, 2011 Waltech Systems
 *
 * This file is part of the Waltech WBO2 project.
 *
 * Waltech WBO2 software is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * Waltech WBO2 software is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * any Waltech WBO2 software.  If not, see http://www.gnu.org/licenses/
 *
 * If you make any changes to this file please fork the project on github.com,
 * commit the change and send us a pull request!
 *
 * http://www.waltech.com
 */


#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "stdint.h"
#define LINESIZE 50
char serialout[LINESIZE];

void uart_putch(uint8_t c);
void uart_putst(const char* s);
void uart_put16dec(uint16_t d);
uint8_t spitout(uint8_t place);
uint8_t put_in_string(int16_t number, char letter, uint8_t place); 


