-include ../common.mk
INCLUDE = -I./

all: CCommonServices

CCommonServices: CLinkList.o CNode.o Cthread.o CQueue.o Ctask.o CDataPackUnPack.o CLogger.o CMutex.o CLogLevel.o CBinarySearchTree.o CTreeNode.o CStack.o

CLinkList.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(TESTFLAG) -c CLinkList.cpp -o CLinkList.o
CNode.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(TESTFLAG) -c CNode.cpp -o CNode.o
Cthread.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(TESTFLAG) -c Cthread.cpp -o Cthread.o
Ctask.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(TESTFLAG) -c Ctask.cpp -o Ctask.o
CDataPackUnPack.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(TESTFLAG) -c CDataPackUnPack.cpp -o CDataPackUnPack.o
CLogger.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(TESTFLAG) -c CLogger.cpp -o CLogger.o
CMutex.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(TESTFLAG) -c CMutex.cpp -o CMutex.o
CLogLevel.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(TESTFLAG) -c CLogLevel.cpp -o CLogLevel.o
CQueue.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(TESTFLAG) -c CQueue.cpp -o CQueue.o
CBinarySearchTree.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(TESTFLAG) -c CBinarySearchTree.cpp -o CBinarySearchTree.o
CTreeNode.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(TESTFLAG) -c CTreeNode.cpp -o CTreeNode.o
CStack.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(TESTFLAG) -c CStack.cpp -o CStack.o
clean:
	rm -f *.o
