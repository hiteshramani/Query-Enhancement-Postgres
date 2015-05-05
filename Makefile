CC = nvcc
CFLAGS = -lpqxx -lpq

Result : Fetcher.o Sorter.o
	${CC} ${CFLAGS} Sorter1.o Fetcher.o -o Result

Fetcher.o : Fetcher.cpp
	${CC} ${CFLAGS} -c Fetcher.cpp -o Fetcher.o
	
Sorter.o : Sorter.cu
	${CC} -c Sorter.cu -o Sorter.o
