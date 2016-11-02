#include"mcomm.h"

long long CAMPCOUNT = 0;

bool leftIsBig(int l, int r) {
  CAMPCOUNT++;
  if (l > r)
    return true;
  return false;
}

bool leftIsBigOrEqual(int l, int r) {
  CAMPCOUNT++;
  if (l >= r)
    return true;
  return false;
}

int isInt( char *num )
{
  int i;
  for( i=0;num[i];i++ )
  {
    if ( num[i] >'9'|| num[i] <'0' ) //只要有非数字，就返回错误
      return 0;
  }
  if ( i>10 ) //都是数字，但长度超过10位，返回错误
    return 0;
  return 1;
}

long long getMillisecond() {
    struct timeb t;
    ftime(&t);
    return (long long)(1000 * t.time + t.millitm);
}

long long getMicrosecond() {
    struct timeval t;
    gettimeofday( &t, NULL );
    return (long long)(1000000 * t.tv_sec + t.tv_usec);
}

int* randInt(int a[], int n) {
  srand((unsigned)time(NULL));
  for(int i=0; i<n; i++) {
    a[i] = 1+(int)(10.0*n*rand()/(RAND_MAX+1.0));
    dbgPrintf("%d ", a[i]);
  }
  return a;
}

int rand_between(int left, int right) {
  srand((unsigned)time(NULL));
  int x = (int)(rand()/(RAND_MAX+1.0)*(right-left))+left;
  dbgPrintf("x=%d\n", x);
  return x; 
}

void swap(int *a, int *b) {
  int temp = *b;
   *b = *a;
   *a = temp;
}

char* getBaseName(char* baseName, char* dirName) {
  char * fname = strrchr(dirName, '/') == NULL ? dirName : strrchr(dirName, '/') +1;
  strcpy(baseName, fname);
  char * cn = index(baseName, '.');
  if (cn!=NULL)
    *(cn+1) = '\0';
  return baseName;
}