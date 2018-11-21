


TARGET  = main_1 main_2 main_3
WDIR     = .

CC	 = gcc

CFLAGS   = -Wall -O3 -D_REENTRANT
CFLAGS  += -I${WDIR}/include 

LFLAGS  = -L./lib -L./
LIBS  += -lmylib


SRCS    = ./$(wildcard *.c) 
OBJS	= $(SRCS:.c=.o)

#====================================================
all: ${TARGET} clean
#====================================================
main_1 : $(SRCS) ./src/file1.c ./src/file2.c
	$(CC) $(CFLAGS) -o $@ $? $(LFLAGS)

main_2 : $(SRCS) 
	$(CC) -static $(CFLAGS) -o $@ $? $(LFLAGS) $(LIBS)

main_3 : $(SRCS)
	$(CC) $(CFLAGS) -o $@ $? $(LFLAGS) $(LIBS)

#-----------------------------------------------------
clean:
	rm -f core *.o a.out 
#=====================================================
