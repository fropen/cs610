CC=gcc -std=gnu99 
all: selectKthElem createRand runall

selectKthElem : mcommon.o selectKthElem.c mcomm.h
	$(CC) -o selectKthElem mcommon.o selectKthElem.c

mcommon.o: mcommon.c mcomm.h
	$(CC) -c mcommon.c

createRand: mcommon.o createRandom.c
	$(CC) -o createRand mcommon.o createRandom.c

runall: createRand selectKthElem
	./createRand 10000 rand10k.txt
	./createRand 100000 rand100k.txt
	./createRand 1000000 rand1000k.txt
	./createRand 10000000 rand10m.txt
	./run10k.sh
	./run100k.sh
	./run1000k.sh
	./run10m.sh

clean :
	rm createRand selectKthElem *.o
