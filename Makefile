CFITS_LIBS= 
#-lcfitsio  
COMMON_LIBS=
#-lm -lgomp -lrt -lpthread 

PARA_LIBS= 
#-fopenmp

INCL_LIBS= $(COMMON_LIBS) $(CFITS_LIBS) 

CC=g++  -O2  -msse2 

DEBUG=

all: Galaxy

Galaxy: RFI_Flagger.o Driver.o NoiseGenerator.o NoiseRemover.o Test.o 
	  ${CC} $(DEBUG) -m64  $(CFITS_LIBS) $(COMMON_LIBS) RFI_Flagger.o Driver.o NoiseGenerator.o NoiseRemover.o Test.o -o RFIFlagging 
	  

RFI_Flagger.o: RFI_Flagger.cpp
	${CC} $(DEBUG) -m64 -c RFI_Flagger.cpp $(CFITS_LIBS) $(PARA_LIBS) $(COMMON_LIBS)	


Test.o: Test.cpp
	${CC} $(DEBUG) -m64 -c Test.cpp $(CFITS_LIBS) $(PARA_LIBS) $(COMMON_LIBS)

#fits_wrapper.o: fits_wrapper.cpp fits_wrapper.h types.h
#	${CC} $(DEBUG) -m64 -c fits_wrapper.cpp $(CFITS_LIBS) $(PARA_LIBS) $(COMMON_LIBS)

Driver.o: Driver.cpp Driver.h
	${CC} $(DEBUG) -m64 -c Driver.cpp $(CFITS_LIBS) $(PARA_LIBS) $(COMMON_LIBS) 	

NoiseGenerator.o: NoiseGenerator.cpp NoiseGenerator.h
	${CC} $(DEBUG) -m64 -c NoiseGenerator.cpp $(CFITS_LIBS) $(PARA_LIBS) $(COMMON_LIBS)
	
NoiseRemover.o: NoiseRemover.cpp NoiseRemover.h
	${CC} $(DEBUG) -m64 -c NoiseRemover.cpp $(CFITS_LIBS) $(PARA_LIBS) $(COMMON_LIBS)
		
clean:
	rm -rf *.o 
