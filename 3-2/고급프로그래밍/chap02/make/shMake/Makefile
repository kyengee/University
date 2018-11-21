
TARGET  = main

WDIR     = .
DIRS    = lib/src/d1 lib/src/d2 lib/src/d3

export CC = gcc

CFLAGS   = -Wall -O3 -D_REENTRANT
CFLAGS  += -I${WDIR}/include 

LFLAGS  = -L./lib -L./
LIBS  = -ld1 -ld2 -ld3

SRCS    = $(wildcard *.c)
OBJS	= $(SRCS:.c=.o)
#====================================================
all: archives ${TARGET} clean
#====================================================
$(TARGET) : $(SRCS)
	  $(CC) $(CFLAGS) -o $@ $? $(LFLAGS) $(LIBS)
#-----------------------------------------------------	  
archives : 
	@for dir in $(DIRS) ; do \
	   $(MAKE) -C $$dir || exit $? ; \
	done
#-----------------------------------------------------
clean:
	@for dir in $(DIRS) ; do \
	      $(MAKE) -C $$dir clean ; \
	done
	rm -f core *.o a.out 
#=====================================================
