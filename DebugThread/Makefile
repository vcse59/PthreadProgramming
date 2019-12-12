-include ../common.mk
CC_INCLUDE=-I../CommonServices/

all: DebugThreadClass.o

DebugThreadClass.o:
	$(CC) $(CFLAGS) $(CC_INCLUDE) $(TESTFLAG) -c DebugThreadClass.cpp -o DebugThreadClass.o

clean:
	rm *.o
