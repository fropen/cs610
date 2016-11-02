#include"mcomm.h"

extern long long CAMPCOUNT;

//pushdown tree from tree_idx
void pushdown(int A[],int tree_idx, int heapSize) {
  dbgPrintf("pushdown(a, %d, %d)\n", tree_idx, heapSize);
  
  while(2*tree_idx<=heapSize-1) {
    int s = leftIsBig(A[2*tree_idx+1], A[2*tree_idx]) ? 2*tree_idx: 2*tree_idx+1;
    if (leftIsBig(A[tree_idx] , A[s])){
      swap(&A[tree_idx], &A[s]);
      tree_idx = s;
    }
    else
      break;
  }

  if(2*tree_idx==heapSize) {
    if(leftIsBig(A[tree_idx],A[heapSize]))
      swap(&A[tree_idx], &A[heapSize]);
  } 
}

void buildHeap(int a[], int tree_idx, int heapSize) {
  dbgPrintf("buildHeap(a, %d, %d)\n", tree_idx, heapSize);
  for (int i=(int)heapSize/2; i>=tree_idx; i--) 
    pushdown(a, i, heapSize);
}

int deleteMin(int *a, int heapSize) {
  swap(a+1, a+heapSize);
  pushdown(a, 1, heapSize-1);
  return a[heapSize];
}

int main(int argc, char* argv[])
{
  if (argc!=3 || !isInt(argv[1])){
    printf("Usage: %s #num srcfile\n\n", argv[0]);
    exit(0);
  }
  FILE *fin, *fout;
  if ((fin=fopen(argv[2],"r"))==NULL){
    printf("fopen %s error", argv[2]);
    exit(0);
  }
  char foutname[100];         //sorted data output filename
  getBaseName(foutname, argv[0]);
  strcat(strcat(foutname,"."), argv[1]);
  
  printf("output is %s\n", foutname);
  if ((fout=fopen(foutname,"w"))==NULL){
    printf("fopen %s error", foutname);
    exit(0);
  }
  
  int num = atoi(argv[1]);
  dbgPrintf("input number is %d\n", num);
  int* data=malloc((num+1)*sizeof(int));
  
  //Read original data
  for (int i=1; i<=num; i++) {
    fscanf(fin, "%d", &data[i]);
    dbgPrintf("%d ", data[i]);
  }
  
  long long s_us=getMicrosecond();
  
  //build Heap
  buildHeap(data, 1, num);
  //output sorted data
  for(int i=num; i>0; i--) {
    int x = deleteMin(data, i);
    fprintf(fout, "%8d%s", x, (num-i+1)%10?" ": "\n");
    dbgPrintf("%8d%s", x, (num-i+1)%10?" ": "\n");
  }
  
  long long e_us=getMicrosecond();

  printf("%s Collapse time: %lld us\n", argv[0], e_us-s_us);
  printf("%s CAMPCOUNT : %lld \n", argv[0], CAMPCOUNT);  
  
  free(data);
  fclose(fin);
  fclose(fout);
  return 0;
} 
