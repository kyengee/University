### ../../../../rmake/lib/src/*/Makefile

TARGET  = libd1
TARGET1 = $(TARGET).a
TARGET2 = $(TARGET).so

CC	 = gcc

WDIR     = ../../..
LDIR    = ${WDIR}/lib

SHARED   = -shared -fPIC

CFLAGS   = -Wall -o32 -O2 -D_REENTRANT
CFLAGS  += -I./include -I${WDIR}/include 

LFLAGS  = -lm
LFLAGS  += 


SRCS    = $(wildcard *.c)
OBJS	= $(SRCS:.c=.o)


#===========================================================================
all: ${TARGET1} clean
#===========================================================================
$(TARGET1) : $(OBJS)
	ar -rscv $@ $?
	mv $@ ${LDIR}

$(TARGET2) : ${SRCS}
	$(CC) ${SHARED} $(CFLAGS) -o $@ $? $(LFLAGS)
	mv $@ ${LDIR}
#---------------------------------------------------------------------------
clean:
	rm -f core *.o a.out 
#===========================================================================
