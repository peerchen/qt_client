#Makefile for test
# AIX version

.SUFFIXES:
.SUFFIXES: .cpp .obj .o

CPP = g++


INCBASE = $(HOME)/include

BU_INC= -I$(INCBASE) -I$(INCBASE)/kernel -I$(INCBASE)/dbpub -I$(INCBASE)/dreb -I$(INCBASE)/gtp -I$(INCBASE)/kvdata -I$(INCBASE)/xdp -Isgeapi/include 


CPPFLAGS = -Wall -g -rdynamic -fPIC -m64 
CPPDEFS = -DUNIX -DLINUX -DNDEBUG -D_THREAD_SAFE 

.cpp.o:
	$(CPP) $(CPPFLAGS) -c  $(CPPDEFS) $(BU_INC) $< -o $@

OBJL =   DllMgr.o         FlowData.o  PoolData.o    S2SgeThread.o  SgeMsgProcThread.o  SocketMgr.o  TradeResource.o DrebMsgThread.o  MsgHead.o   PoolModule.o  SendQueue.o    SocketInfo.o        TradeMain.o  main.o

ALL:   tradefront clean

BCCLIB = -L$(HOME)/lib   -lbf_kernel -lbf_dbpub -lbf_drebapi -lbf_gtp -lbf_kvdata -lbf_xdp   -lpthread -ldl

tradefront: $(OBJL)
	g++ $(CPPFLAGS) $(CPPDEFS) -o $@ $(OBJL) $(KERNEL_INC) -L$(HOME)/lib    $(CPPDEFS) $(BCCLIB)
	mv $@ $(HOME)/bin
clean:
	rm -f *.o
