# Makefile for test
# AIX version

.SUFFIXES:
.SUFFIXES: .cpp .obj .o

CPP = g++

INCBASE = $(HOME)/include

INC= -I$(INCBASE)  -I$(INCBASE)/kernel -I$(INCBASE)/dbpub -I$(INCBASE)/dreb -I$(INCBASE)/gtp -I../sgeapi/include -I../

CPPFLAGS =  -g -Wall  -O2 -fpic -m64
CPPDEFS =  -DUNIX -DLINUX  -Wall -D_THREAD_SAFE
DLLLIB  =   -lbf_kernel    -lpthread
DLLLIB2  =   -lbf_kernel -lbf_gtp    -lpthread

.cpp.o:
	$(CPP) $(CPPFLAGS) -c   $(CPPDEFS)  $(INC)  $< -o $@

OBJL = OfferingTrade.o 
OBJL2 = OfferingTrade.o main.o

ALL: libfptrade.so  clean

libfptrade.so: $(OBJL)
	g++ $(CPPFLAGS) $(CPPDEFS) -shared $(OBJL) -L$(HOME)/lib $(DLLLIB) -o $@ 
	mv $@ $(HOME)/libapp
libfptrade.a: $(OBJL)
	ar -rv $@ $(OBJL) 
	mv $@ $(HOME)/libapp
testsge: $(OBJL2)
	g++ $(CPPFLAGS) $(CPPDEFS) -o $@ $(OBJL2) $(INC) -L$(HOME)/lib    $(CPPDEFS) $(DLLLIB2)
	mv $@ $(HOME)/bin
clean:
	rm -f *.o
