CC=gcc -std=gnu99 
all: createRandStr radixSort

radixSort : mcommon.o radixSort.c mcomm.h
	$(CC) -o radixSort mcommon.o radixSort.c

mcommon.o: mcommon.c mcomm.h
	$(CC) -c mcommon.c

createRandStr: mcommon.o createRandomStr.c
	$(CC) -o createRandStr mcommon.o createRandomStr.c

runall: createRandStr radixSort
	./createRandStr 1000 f.txt
	./radixSort f.txt g.txt


clear :
	rm createRandStr radixSort *.o
