# Waltech WBO2 for the ATmega8
#
# Copyright 2010, 2011 Waltech Systems
#
# This file is part of the Waltech WBO2 project.
#
# Waltech WBO2 software is free software: you can redistribute it
# and/or modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the License,
# or (at your option) any later version.
#
# Waltech WBO2 software is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# any Waltech WBO2 software.  If not, see http://www.gnu.org/licenses/
#
# If you make any changes to this file please fork the project on github.com,
# commit the change and send us a pull request!
# 
# http://www.waltech.com


##this is makefile 6  
NAME := nb-nwebrd-2
HEX := $(NAME).hex
OUT := $(NAME).out
MAP := $(NAME).map
SOURCES := $(wildcard *.c)
HEADERS := $(wildcard *.h)
OBJECTS := $(patsubst %.c,%.o,$(SOURCES))

MCU := atmega8
MCU_AVRDUDE := m8
MCU_FREQ := 4000000UL

CC := avr-gcc
OBJCOPY := avr-objcopy
SIZE := avr-size -A
DOXYGEN := doxygen

CFLAGS = -mmcu=$(MCU) -g -pedantic -Os -gstabs -std=gnu99  -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums  -Wall -Wa,-adhlns=$(<:.c=.lst)  $(patsubst %,-I%,$(EXTRAINCDIRS)) -DF_CPU=$(MCU_FREQ)

#CFLAGS := -Wall -pedantic -mmcu=$(MCU) -std=c99 -g -os -DF_CPU=$(MCU_FREQ)

all: $(HEX)

clean:
	rm -f $(HEX) $(OUT) $(MAP) $(OBJECTS) 
	rm -rf doc/html
	rm -f *.lst

flash: $(HEX)
	avrdude -y -p $(MCU_AVRDUDE) -U flash:w:$(HEX)

$(HEX): $(OUT)
	$(OBJCOPY) -R .eeprom -O ihex $< $@

$(OUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ -Wl,-Map,$(MAP) $^
	@echo
	@$(SIZE) $@
	@echo

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

%.pp: %.c
	$(CC) $(CFLAGS) -E -o $@ $<

%.ppo: %.c
	$(CC) $(CFLAGS) -E $<

doc: $(HEADERS) $(SOURCES) Doxyfile
	$(DOXYGEN) Doxyfile

.PHONY: all clean flash doc

