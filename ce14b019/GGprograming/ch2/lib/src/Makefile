TARGET = libmylib.a libmylib.so

CC	= gcc

WDIR = ../..
LDIR = $(WDIR)/lib

SHARED = -shared -fPIC

CFLAGS = -Wall -O3 -D_REENTRANT
CFLAGE += -I./include -I$(WDIR)/include

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

#=============================================
all: $(TARGET) clean
#=============================================

libmylib.a : $(OBJS)
		ar -rscv $@ $?

libmylib.so : $(SRCS)
		$(CC) $(SHARED) $(CFLAGS) -o $@ $? $(LIBS)

#-------------------------------------------------
clean:
#============================================
