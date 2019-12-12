-include ../common.mk
CC_INCLUDE=-I../CommonServices/

all: CProducer.o

CProducer.o:
	$(CC) $(CFLAGS) $(CC_INCLUDE) $(TESTFLAG) -c CProducer.cpp -o CProducer.o

clean:
	rm *.o
