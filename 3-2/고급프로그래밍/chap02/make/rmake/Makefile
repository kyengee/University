# ../rmake/Makefile

TARGET = prog

OBJS = lib/src/d1/func1.o lib/src/d2/func2.o \
       lib/src/d3/func3.o lib/src/d3/main.o

all : $(TARGET)
$(TARGET) : D1 D2 D3 
	$(CC) $(CFLAGS) -o $@ $(OBJS)

D1 :
	cd lib/src/d1 ; $(MAKE) all
D2 :
	cd lib/src/d2 ; $(MAKE) all
D3 :
	cd lib/src/d3 ; $(MAKE) all

clean :
	rm -rf $(TARGET)
	cd lib/src/d1 ; $(MAKE) clean
	cd lib/src/d2 ; $(MAKE) clean
	cd lib/src/d3 ; $(MAKE) clean