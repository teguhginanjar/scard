CC		= gcc
SRC		= main.c scard.c 

OBJS	= ${SRC:.c=.o}
LIBS	= `pkg-config --libs  libpcsclite glib-2.0`
CFLAGS	= -g -c -Wall `pkg-config --cflags libpcsclite glib-2.0`

TARGET	= ./SCARD

${TARGET} : ${OBJS}
		@${CC} -o ${TARGET} ${OBJS} ${LIBS}
		@echo "BUILD " ${TARGET}
	
.c.o :
		@${CC}  ${CFLAGS}  $<
		@echo "complaining ->" $<


clean :
		@ rm -rf *.o *.c~ *.h~ ${TARGET} 
		@ echo "removing " ${TARGET} *.o *.c~ *.h~

