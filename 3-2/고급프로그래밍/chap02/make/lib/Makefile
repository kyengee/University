


TARGET  = main_lib_so main_lib_a
WDIR     = .

CC	 = gcc

CFLAGS   = -Wall -O3 -D_REENTRANT
CFLAGS  += -I${WDIR}/include 

LFLAGS  = -L./lib
LFLAGS  += -lmylib


SRCS    = $(wildcard *.c)
OBJS	= $(SRCS:.c=.o)

#====================================================
all: ${TARGET} clean
#====================================================
main_lib_so : $(SRCS)
	  $(CC) $(CFLAGS) -o $@ $? $(LFLAGS)

main_lib_a : $(SRCS)
	  $(CC) -static $(CFLAGS) -o $@ $? $(LFLAGS)
#-----------------------------------------------------
clean:
	rm -f core *.o a.out 
#=====================================================
