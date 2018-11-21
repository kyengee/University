
###-------------------------------------------------------------###
###  Program Name :  Makefile					###
###								###
###  Copyrights 						###
###  reserved by Bo-kyun Na (bkna@ecs.syr.edu)			###
###  ----  IntellActive Research Lab. ----			###
###-------------------------------------------------------------###
###  This file contains the information necessary for           ###
###  the compiler and linker to create the object file  	###
###  for library archive in the UNIX.                   	###
###                                                     	###
###-------------------------------------------------------------###
###  USAGE:							###
###  To run a makefile: make -f libvdo.mk 			###
###  To clean:          make -f libvdo.mk clean			###
###-------------------------------------------------------------###

PROGS =	ftw
CC = gcc
WDIR = .

CFLAGS = -Wall -I${WDIR}/include
LDLIBS = -L/usr/X11R6/lib -L${WDIR}/lib 

LDLIBS +=-lm 

CFLAGS += -DTEST
LDLIBS += 

SRCS = ftw.c dll.c 
OBJS = ${SRCS:.c=.o}


### ************************************************************************
all : ${PROGS}
### ************************************************************************

libstorage.a : ${OBJS}
	ar -rv $@ $?
	mv $@ ${WDIR}/lib/

${PROGS}: ${OBJS}
	${CC} ${CFLAGS} -o $@ $? $(LFLAGS) ${LIBS}

### ------------------------------------------------------------------------
clean:
	rm -f a.out core *.o $(OBJS)
### ************************************************************************
