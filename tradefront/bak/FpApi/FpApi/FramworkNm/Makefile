
#Makefile for 
# AIX version

.SUFFIXES:
.SUFFIXES: .cpp .obj .o

CPP = g++

KERNEL_INC=-I$(HOME)/include -I../Utility  -I../NetMgr -I../CommFramwork

CPPFLAGS =  -g -Wall  -O2
CPPDEFS = -DLINUX -DUNIX -DNDEBUG -D_THREAD_SAFE -D_MT -DSA_USE_PTHREAD -D_AIX32_THREADS 

.cpp.o:
	$(CPP) $(CPPFLAGS) -c  $(CPPDEFS) $(KERNEL_INC) $< -o $@

OBJL = WorkThreadNm.o ProcessInterfaceNm.o

#ALL:   libnetmgr.a  clean
ALL:   libframworknm.a

libframworknm.a : $(OBJL)
	ar rv $@ $(OBJL)
	mv $@ $(HOME)/lib
clean:
	rm -f *.o
