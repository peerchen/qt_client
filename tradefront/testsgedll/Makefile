# Makefile for test
# AIX version

.SUFFIXES:
.SUFFIXES: .cpp .obj .o

CPP = g++

INCBASE = $(HOME)/include

INC= -I$(INCBASE)  -I$(INCBASE)/kernel -I$(INCBASE)/dbpub -I$(INCBASE)/gtp -I../sgeapi/include -I../

CPPFLAGS =  -g -Wall  -O2 -fpic -m64
CPPDEFS =  -DUNIX -DLINUX  -Wall -D_THREAD_SAFE
DLLLIB  =   -lbf_kernel    -lpthread

.cpp.o:
	$(CPP) $(CPPFLAGS) -c   $(CPPDEFS)  $(INC)  $< -o $@

OBJL = TestSgeDll.o 

ALL: libTestSgeDll.so clean

libTestSgeDll.so: $(OBJL)
	g++ $(CPPFLAGS) $(CPPDEFS) -shared $(OBJL) -L$(HOME)/lib $(DLLLIB) -o $@ 
	mv $@ $(HOME)/libapp
libTestSgeDll.a: $(OBJL)
	ar -rv $@ $(OBJL) 
	mv $@ $(HOME)/libapp
clean:
	rm -f *.o
