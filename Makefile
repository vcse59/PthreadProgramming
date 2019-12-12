-include common.mk

THIRD_PARTY_DIR = 3rdParty
CURLDIRS = $(THIRD_PARTY_DIR)/curl
SUBDIRS = CommonServices ProducerClass ConsumerClass AppData DebugThread
CC_INCLUDE = -I./CommonService -I./ProducerClass -I./ConsumerClass -I./AppData -I./DebugThread
LDFLAGS = -lpthread

all: ThreadApp

ThreadApp: main.o $(SUBDIRS)
	$(CC) $(CFLAGS) $(CC_INCLUDE) $(DEBUG) $(TESTFLAG) main.o CommonServices/*.o ProducerClass/*.o ConsumerClass/*.o AppData/*.o DebugThread/*.o -o ThreadApp $(LDFLAGS) 

main.o:
	$(CC) $(CFLAGS) $(CC_INCLUDE) -c main.cpp -o main.o

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: $(SUBDIRS)

clean:
	rm -f CommonServices/*.o ProducerClass/*.o ConsumerClass/*.o AppData/*.o DebugThread/*.o *.o ThreadApp
