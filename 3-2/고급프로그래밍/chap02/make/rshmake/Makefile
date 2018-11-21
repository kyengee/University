

DIRS    = lib/src/d1 lib/src/d2 lib/src/d3
OBJS    = main.o func1.o func2.o func3.o
TARGET  = main

CC	 = gcc

#===============================================
all: objects
	$(CC) -o $(TARGET) $(OBJS)
#===============================================
objects : 
	@for dir in $(DIRS) ; do \
	$(MAKE) -C $$dir || exit $? ; \
	done
#-----------------------------------------------
clean:
	@for dir in $(DIRS) ; do \
	$(MAKE) -C $$dir clean ; \
	done
	rm -f core *.o a.out 
#===============================================
