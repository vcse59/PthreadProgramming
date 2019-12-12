-include ../common.mk
CC_INCLUDE=-I../CommonServices/

all: CPipelineDataClass.o

CPipelineDataClass.o:
	$(CC) $(CFLAGS) $(CC_INCLUDE) $(TESTFLAG) -c CPipelineDataClass.cpp -o CPipelineDataClass.o

clean:
	rm *.o
