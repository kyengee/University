# ../../rmake/lib/src/*/Makefile

OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
CFLAGS = -I../include

all : $(OBJS)
	cp -f $^ ../../..
clean :
	rm -rf *.o
