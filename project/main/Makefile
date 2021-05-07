# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:main.elf

libLcd.a: font-11x16.o lcdutils.o lcddraw.o
	$(AR) crs $@ $^

install: libLcd.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

#additional rules for files
main.elf: ${COMMON_OBJECTS} main.o p1_interrupt_handler.o wdt_handler.o switches.o jumpTable.o libLcd.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

switches.o: switches.h

jumpTable.o: jumpTable.s

load: main.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

