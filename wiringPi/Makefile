#
# Makefile:
#	wiringPi - Wiring Compatable library for the Raspberry Pi
#
#	Copyright (c) 2012-2015 Gordon Henderson
#################################################################################
# This file is part of wiringPi:
#	https://projects.drogon.net/raspberry-pi/wiringpi/
#
#    wiringPi is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    wiringPi is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
#################################################################################

VERSION=$(shell cat ../VERSION)
DESTDIR=/usr
PREFIX=/local

STATIC=libwiringPi.a
DYNAMIC=libwiringPi.so.$(VERSION)

#DEBUG	= -g -O0
DEBUG	= -O2
CC	= gcc
INCLUDE	= -I.
DEFS	= -D_GNU_SOURCE
CFLAGS	= $(DEBUG) $(DEFS) -Wformat=2 -Wall -Winline $(INCLUDE) -pipe -fPIC

LIBS    =

###############################################################################

SRC	=	wiringPi.c						\
		wiringSerial.c wiringShift.c				\
		piHiPri.c piThread.c					\
		wiringPiSPI.c wiringPiI2C.c				\
		softPwm.c softTone.c					\
		mcp23008.c mcp23016.c mcp23017.c			\
		mcp23s08.c mcp23s17.c					\
		sr595.c							\
		pcf8574.c pcf8591.c					\
		mcp3002.c mcp3004.c mcp4802.c mcp3422.c			\
		max31855.c max5322.c					\
		sn3218.c						\
		drcSerial.c	\
		pca9685.c \
		dac7678.c \
		wpiExtensions.c

HEADERS =	wiringPi.h						\
		pca9685.h pca9685reg.h dac7678.h \
		wiringSerial.h wiringShift.h				\
		wiringPiSPI.h wiringPiI2C.h				\
		softPwm.h softTone.h					\
		mcp23008.h mcp23016.h mcp23017.h			\
		mcp23s08.h mcp23s17.h					\
		sr595.h							\
		pcf8574.h pcf8591.h					\
		mcp3002.h mcp3004.h mcp4802.h mcp3422.h			\
		max31855.h max5322.h					\
		sn3218.h						\
		drcSerial.h						\
		wpiExtensions.h 


OBJ	=	$(SRC:.c=.o)

all:		$(DYNAMIC)

static:		$(STATIC)

$(STATIC):	$(OBJ)
	@echo "[Link (Static)]"
	@ar rcs $(STATIC) $(OBJ)
	@ranlib $(STATIC)
#	@size   $(STATIC)

$(DYNAMIC):	$(OBJ)
	@echo "[Link (Dynamic)]"
	@$(CC) -shared -Wl,-soname,libwiringPi.so -o libwiringPi.so.$(VERSION) -lpthread $(OBJ)

.c.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@


.PHONY:	clean
clean:
	@echo "[Clean]"
	@rm -f $(OBJ) $(OBJ_I2C) *~ core tags Makefile.bak libwiringPi.*

.PHONY:	tags
tags:	$(SRC)
	@echo [ctags]
	@ctags $(SRC)


.PHONY:	install
install:	$(DYNAMIC)
	@echo "[Install Headers]"
	@install -m 0755 -d						$(DESTDIR)$(PREFIX)/include
	@install -m 0644 $(HEADERS)					$(DESTDIR)$(PREFIX)/include
	@echo "[Install Dynamic Lib]"
	@install -m 0755 -d						$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 libwiringPi.so.$(VERSION)			$(DESTDIR)$(PREFIX)/lib/libwiringPi.so.$(VERSION)
	@ln -sf $(DESTDIR)$(PREFIX)/lib/libwiringPi.so.$(VERSION)	$(DESTDIR)/lib/libwiringPi.so
	@ldconfig

.PHONY:	install-static
install-static:	$(STATIC)
	@echo "[Install Headers]"
	@install -m 0755 -d						$(DESTDIR)$(PREFIX)/include
	@install -m 0644 $(HEADERS)					$(DESTDIR)$(PREFIX)/include
	@echo "[Install Static Lib]"
	@install -m 0755 -d						$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 libwiringPi.a					$(DESTDIR)$(PREFIX)/lib

.PHONY:	install-deb
install-deb:	$(DYNAMIC)
	@echo "[Install Headers: deb]"
	@install -m 0755 -d							~/wiringPi/debian/wiringPi/usr/include
	@install -m 0644 $(HEADERS)						~/wiringPi/debian/wiringPi/usr/include
	@echo "[Install Dynamic Lib: deb]"
	install -m 0755 -d							~/wiringPi/debian/wiringPi/usr/lib
	install -m 0755 libwiringPi.so.$(VERSION)				~/wiringPi/debian/wiringPi/usr/lib/libwiringPi.so.$(VERSION)
	ln -sf ~/wiringPi/debian/wiringPi/usr/lib/libwiringPi.so.$(VERSION)	~/wiringPi/debian/wiringPi/usr/lib/libwiringPi.so

.PHONY:	uninstall
uninstall:
	@echo "[UnInstall]"
	@cd $(DESTDIR)$(PREFIX)/include/ && rm -f $(HEADERS)
	@cd $(DESTDIR)$(PREFIX)/lib/     && rm -f libwiringPi.*
	@ldconfig


.PHONY:	depend
depend:
	makedepend -Y $(SRC) $(SRC_I2C)

# DO NOT DELETE

wiringPi.o: softPwm.h softTone.h wiringPi.h
wiringSerial.o: wiringSerial.h
wiringShift.o: wiringPi.h wiringShift.h
piHiPri.o: wiringPi.h
piThread.o: wiringPi.h
wiringPiSPI.o: wiringPi.h wiringPiSPI.h
wiringPiI2C.o: wiringPi.h wiringPiI2C.h
softPwm.o: wiringPi.h softPwm.h
softTone.o: wiringPi.h softTone.h
mcp23008.o: wiringPi.h wiringPiI2C.h mcp23x0817.h mcp23008.h
mcp23016.o: wiringPi.h wiringPiI2C.h mcp23016.h mcp23016reg.h
mcp23017.o: wiringPi.h wiringPiI2C.h mcp23x0817.h mcp23017.h
mcp23s08.o: wiringPi.h wiringPiSPI.h mcp23x0817.h mcp23s08.h
mcp23s17.o: wiringPi.h wiringPiSPI.h mcp23x0817.h mcp23s17.h
sr595.o: wiringPi.h sr595.h
pcf8574.o: wiringPi.h wiringPiI2C.h pcf8574.h
pcf8591.o: wiringPi.h wiringPiI2C.h pcf8591.h
mcp3002.o: wiringPi.h wiringPiSPI.h mcp3002.h
mcp3004.o: wiringPi.h wiringPiSPI.h mcp3004.h
mcp4802.o: wiringPi.h wiringPiSPI.h mcp4802.h
mcp3422.o: wiringPi.h wiringPiI2C.h mcp3422.h
max31855.o: wiringPi.h wiringPiSPI.h max31855.h
max5322.o: wiringPi.h wiringPiSPI.h max5322.h
sn3218.o: wiringPi.h wiringPiI2C.h sn3218.h
drcSerial.o: wiringPi.h wiringSerial.h drcSerial.h
pca9685.o: wiringPi.h pca9685.h pca9685reg.h
dac7678.o: wiringPi.h wiringPiI2C.h dac7678.h
wpiExtensions.o: wiringPi.h mcp23008.h mcp23016.h mcp23017.h mcp23s08.h
wpiExtensions.o: mcp23s17.h sr595.h pcf8574.h pcf8591.h mcp3002.h mcp3004.h
wpiExtensions.o: mcp4802.h mcp3422.h max31855.h max5322.h sn3218.h
wpiExtensions.o: drcSerial.h wpiExtensions.h
