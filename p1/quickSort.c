#include"mcomm.h"

extern long long CAMPCOUNT;

void quickSort( int a[], int left, int right) {
  if (left >= right) return;
  int k= rand_between(left, right);   //random select pivot
  dbgPrintf("left=%d, right=%d, rand_between=%d\n", left, right, k);
  swap(&a[left], &a[k]);  //a[left] now is the pivot
  int l = left + 1; 
  int r = right;
  while (l <= r) {
    while(l<=r && leftIsBigOrEqual(a[left], a[l])) l++;
    while(l<=r && leftIsBigOrEqual(a[r], a[left])) r--;
    if(l<r) {
      swap(&a[l], &a[r]);
      l++;
      r--;
    }
  }
  swap(&a[left], &a[r]);    //a[r] left is less than it, right is greater than it
  quickSort(a, left, r-1);
  quickSort(a, r+1, right);
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
  int* data=malloc(num*sizeof(int));

  for (int i=0; i<num; i++) {
    fscanf(fin, "%d", &data[i]);
    dbgPrintf("%d ", data[i]);
  }
  
  long long s_us=getMicrosecond();
  
  quickSort(data, 0, num-1);
  for(int i=0; i<num; i++) {
    fprintf(fout, "%8d%s", data[i], (i+1)%10?" ": "\n");
    dbgPrintf("%8d%s", data[i], (i+1)%10?" ": "\n");
  }

  long long e_us=getMicrosecond();
  printf("%s Collapse time: %lld us\n", argv[0], e_us-s_us);
  printf("%s CAMPCOUNT : %lld \n", argv[0], CAMPCOUNT);
  
  free(data);
  fclose(fin);
  fclose(fout);
  return 0;
} 
