-include ../common.mk
CC_INCLUDE=-I../CommonServices/

all: CConsumer.o

CConsumer.o:
	$(CC) $(CFLAGS) $(CC_INCLUDE) $(TESTFLAG) -c CConsumer.cpp -o CConsumer.o

clean:
	rm *.o
