#include"mcomm.h"

extern long long CAMPCOUNT;

//src[left->m], src[m+1, right] are sorted data individually
//after merge, dst[left->right] is sorted
void merge (int *src, int left, int m, int right, int *dst) {
  dbgPrintf("\nmerge left=%d, right=%d, middle=%d\n", left, right, m);

  for (int i = left, j = m+1, k = left; k <= right; k++) {
      dst[k] = j == right+1             ? src[i++]
           : i == m+1                   ? src[j++]
           : leftIsBig(src[i] , src[j]) ? src[j++]
           :                              src[i++];
  }
}

//improved mergeSort. No need to malloc a temp array during each recursion
void mergeSort (int *dst, int left, int right, int *temp) {
  dbgPrintf("\nmergeSort left=%d, right=%d\n", left, right);
  if (left >= right)
    return;
  int m = (left+right) / 2;

  mergeSort(temp, left, m, dst);
  mergeSort(temp, m+1, right, dst);
  merge(temp, left, m, right, dst);

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
  int* temp_data = malloc(num*sizeof(int));

  for (int i=0; i<num; i++) {
    fscanf(fin, "%d", &data[i]);
    temp_data[i] = data[i];
    dbgPrintf("%d ", data[i]);
  }
  
  long long s_us=getMicrosecond();
  
  mergeSort(data, 0, num-1, temp_data);  
  for(int i=0; i<num; i++) {
    fprintf(fout, "%8d%s", data[i], (i+1)%10?" ": "\n");
    dbgPrintf("%8d%s", data[i], (i+1)%10?" ": "\n");
  }
  
  long long e_us=getMicrosecond();

  printf("%s Collapse time: %lld us\n", argv[0], e_us-s_us);
  printf("%s CAMPCOUNT : %lld \n", argv[0], CAMPCOUNT);  

  free(data);
  free(temp_data);
  fclose(fin);
  fclose(fout);
  return 0;
} 
