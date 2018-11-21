# ../vpath/Makefile

VPATH = lib/src/d1 lib/src/d2 lib/src/d3
TARGET = prog

OBJS = func1.o func2.o func3.o main.o
#OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
#OBJS = $($(wildcard *.c):.c=.o)


all : $(TARGET) clean
$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $?

clean :
	rm -rf *.o *~
