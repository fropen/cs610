CC=gcc -std=gnu99 
all: quickSort createRand mergeSort heapSort runall

quickSort : mcommon.o quickSort.c mcomm.h
	$(CC) -o quickSort mcommon.o quickSort.c

mcommon.o: mcommon.c mcomm.h
	$(CC) -c mcommon.c

createRand: mcommon.o createRandom.c
	$(CC) -o createRand mcommon.o createRandom.c

mergeSort : mcommon.o mergeSort.c mcomm.h
	$(CC) -o mergeSort mcommon.o mergeSort.c
  
heapSort : mcommon.o heapSort.c mcomm.h
	$(CC) -o heapSort mcommon.o heapSort.c

runall: quickSort createRand mergeSort heapSort
	./run32.sh | tee run32.out
	./run32sort.sh | tee run32sort.out
	./run32rev.sh | tee run32rev.out
	./run1024.sh | tee run1024.out
	./run32768.sh | tee run32768.out
	./run1048576.sh | tee run1048576.out

clean :
	rm quickSort createRand mergeSort heapSort *.o
