#include <sys/timeb.h>
#include <sys/time.h>
#include <time.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//#define DEBUG 1

#ifdef DEBUG
#define dbgPrintf printf
#else
#define dbgPrintf /\
/dbgPrintf
#endif

typedef enum {false = 0, true = 1} bool;

long long CAMPCOUNT;
long long SWAPCOUNT;

int isInt( char *num );
long long getMillisecond();
long long getMicrosecond();
void swap(int *a, int *b);
void sort(int *a, int *b, int *c);
int rand_between(int left, int right);
int* randInt(int a[], int n);
bool leftIsBig(int l, int r);
bool equals(int l, int r);
bool leftIsBigOrEqual(int l, int r);
char* getBaseName(char* baseName, char* dirName);