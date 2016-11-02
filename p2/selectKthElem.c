#include"mcomm.h"

extern long long CAMPCOUNT;
extern long long CAMPCOUNT;

//sort array and assign median to a[left]
void assignMedian(int a[], int left, int right, int step) {
  if(left>right) return;
  for (int i=left; i<=right; i+=step) {
    for (int j=i; j>left; j-=step) {
      if (leftIsBig(a[j-step], a[j]))
        swap(&a[j-step], &a[j]);
      else
        break;
    }
  }
  swap(&a[left], &a[(right-left+1)/step/2*step+left]);
  dbgPrintf("AAAAAAAAAAAA %d, %d, %d, %d, %d\n", left, right, step, ((right-left+1)/step)/2*step+left, a[left]);
}

//calculate row median, row - every 5 elements 
//recursively call to find the median of median
void calcRowMedian(int a[], int left, int right, int step) {
  if (step>right) return;
  int i = left;
  for ( ; i<=right-4*step; i+=5*step) {
    assignMedian(a, i, i+4*step, step);
  }
  assignMedian(a, i, right, step);
  
  calcRowMedian(a, left, right, 5*step);
}

//quick sort algorithm
void quickSort( int a[], int left, int right) {
  if (left >= right) return;
  int k= rand_between(left, right);
  //getMedianIdx(a, left, right); //(left+right)/2; //rand_between(left, right);   //random select pivot
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

//insertSort
void insertSort(int a[], int left, int right) {
  for (int i=left; i<=right; i++) {
    for (int j=i; j>left; j--) {
      if (leftIsBig(a[j-1], a[j]))
        swap(&a[j-1], &a[j]);
      else
        break;
    }
  }
}

//use quickSort and return the kth smallest value
//n is the array size
int SELECT1 (int a[], int n, int k) {
  if(k>n) {
    printf("No %d elements in Array\n", k);
    return -1;
  }
  
  quickSort(a, 0, n-1);  
  return a[k-1];
}

//Randomized selection. Quick-Select in text book
//when array size less than 25, use insertSort
//SPLIT TO 2 ARRAY, ONE is less or equal to pivot
//ONE is great or equal to pivot
//No extra array needed
int SELECT2 (int L[], int left, int right, int k) {
  dbgPrintf("SELECT2: left: %d, right: %d k: %d\n", left, right, k);
  if(k>right-left+1) {
    printf("No %d elements in Array\n", k);
    return -1;
  }
    
  if(right-left+1<25) {
    insertSort(L, left, right);
    return L[k+left-1];
  }
  
  //random pivot
  int v = rand_between(left, right);
  int pivot = L[v];
  int leftIdx = left;
  int rightIdx = right;
  int leftEqualCount = 0;
  int rightEqualCount = 0;
  //move pivot to right
  //swap(&L[v], &L[right]);
  
  //split L to 2 Array
  while (leftIdx<=rightIdx) {
    while(leftIsBig(pivot, L[leftIdx])) {
      leftIdx++;
    }
    while(leftIsBig(L[rightIdx], pivot)) {
      rightIdx--;
    }
    dbgPrintf("leftIdx: %d, leftEqualCount: %d, rightEqualCount: %d rightIdx: %d pivot: %d\n", 
           leftIdx, leftEqualCount, rightEqualCount, rightIdx, pivot);
    
    dbgPrintf("%d, %d\n", L[leftIdx], L[rightIdx]);
    
    if(leftIdx<=rightIdx) {
      swap(&L[leftIdx], &L[rightIdx]);
      if(equals(L[leftIdx], pivot)) {
        leftEqualCount++;
      }
      if(equals(L[rightIdx], pivot)) {
        rightEqualCount++;
      }
      leftIdx++;
      rightIdx--;
    }
  }
  if (left+k<=leftIdx-leftEqualCount) {
    return SELECT2(L, left, leftIdx-1, k);
  }
  if (left+k-1<rightIdx+1+rightEqualCount)
    return pivot;
  dbgPrintf("leftIdx: %d, leftEqualCount: %d, rightEqualCount: %d rightIdx: %d pivot: %d\n", 
           leftIdx, leftEqualCount, rightEqualCount, rightIdx, pivot);
  return SELECT2(L, rightIdx+1, right, k-rightIdx-1+left);
}

//Need 1 extra temp array to store the pivot-great elems, L is reused to store the pivot-less elems
int SELECT2_2 (int L[], int left, int right, int k, int R[]) {
  dbgPrintf("SELECT2_2: left: %d, right: %d k: %d\n", left, right, k);
  if(right-left+1<25) {
    insertSort(L, left, right);
    return L[k+left-1];
  }
  
  //random pivot
  int v = rand_between(left, right);
  int pivot = L[v];
  int leftIdx = left;
  int rightIdx = right;
  int equalCount = 0;
  //move pivot to right
  //swap(&L[v], &L[right]);
  
  //split L to 2 Array
  for (int i=left; i<=right; i++) {
    if (leftIsBig(pivot, L[i])) {
      dbgPrintf("L[leftIdx]=%d, leftIdx=%d, L[i] = %d, i=%d\n", L[leftIdx], leftIdx, L[i], i);
      L[leftIdx++] = L[i];
    }
    else if(equals(L[i], pivot)){
      equalCount++;
      dbgPrintf("equalCount=%d, L[i] = %d, i=%d\n", equalCount, L[i], i);
    }
    else {
      dbgPrintf("rightIdx=%d, L[i] = %d, i=%d\n", rightIdx, L[i], i);
      R[rightIdx--] = L[i];
    }
  }

  
  if (left+k<=leftIdx) {
    return SELECT2_2(L, left, leftIdx-1, k, R);
  }
  if (left+k<=leftIdx+equalCount)
    return pivot;
  dbgPrintf("leftIdx: %d, equalCount: %d rightIdx: %d pivot: %d\n", leftIdx, equalCount, rightIdx, pivot);
  return SELECT2_2(R, rightIdx+1, right, k-leftIdx-equalCount+left, L);
}

//Use recurssion algorithm to calculate the median of the array and
//use the median as pivot to split the orig array
int SELECT3 (int L[], int left, int right, int k) {
  dbgPrintf("SELECT3: left: %d, right: %d k: %d\n", left, right, k);
  int num = right - left + 1;
  if(k>num) {
    printf("No %d elements in Array\n", k);
    return -1;
  }
    
  if(num<25) {
    insertSort(L, left, right);
    return L[k+left-1];
  }
    
  calcRowMedian(L, left, right, 1);
  //assignMedian(L, left, right, 5);
  //random pivot
  int pivot = L[left];
  int leftIdx = left;
  int rightIdx = right;
  int leftEqualCount = 0;
  int rightEqualCount = 0;
  
  //split L to 2 Array
  while (leftIdx<=rightIdx) {
    while(leftIsBig(pivot, L[leftIdx])) {
      leftIdx++;
    }
    while(leftIsBig(L[rightIdx], pivot)) {
      rightIdx--;
    }
    dbgPrintf("leftIdx: %d, leftEqualCount: %d, rightEqualCount: %d rightIdx: %d pivot: %d\n", 
           leftIdx, leftEqualCount, rightEqualCount, rightIdx, pivot);
    
    dbgPrintf("%d, %d\n", L[leftIdx], L[rightIdx]);
    
    if(leftIdx<=rightIdx) {
      swap(&L[leftIdx], &L[rightIdx]);
      if(equals(L[leftIdx], pivot)) {
        leftEqualCount++;
      }
      if(equals(L[rightIdx], pivot)) {
        rightEqualCount++;
      }
      leftIdx++;
      rightIdx--;
    }
  }
  if (left+k<=leftIdx-leftEqualCount) {
    return SELECT3(L, left, leftIdx-1, k);
  }
  if (left+k-1<rightIdx+1+rightEqualCount)
    return pivot;
  dbgPrintf("leftIdx: %d, leftEqualCount: %d, rightEqualCount: %d rightIdx: %d pivot: %d\n", 
           leftIdx, leftEqualCount, rightEqualCount, rightIdx, pivot);
  return SELECT3(L, rightIdx+1, right, k-rightIdx-1+left);

}

int main(int argc, char* argv[])
{
  if (argc!=4 || !isInt(argv[1]) || !isInt(argv[3])){
    printf("Usage: %s #num srcfile #kth\n\n", argv[0]);
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
  //Unsorted data for SELECT1
  int* data=malloc(num*sizeof(int));
  
  //Unsorted temp data array
  int* temp=malloc(num*sizeof(int));
  
  //Unsorted data for SELECT2
  int* data2=malloc(num*sizeof(int));
  
  //Unsorted data for SELECT2_2
  int* data3=malloc(num*sizeof(int));
  
  int* data4=malloc(num*sizeof(int));
  
  int kth = atoi(argv[3]);
  dbgPrintf("input kth is %d\n", kth);

  for (int i=0; i<num; i++) {
    fscanf(fin, "%d", &data[i]);
    data2[i] = data3[i] = data4[i] = data[i];
    dbgPrintf("%d ", data[i]);
  }
  
  long long s_us=getMicrosecond();
  
  int value = SELECT1(data, num, kth);
  
  long long e_us=getMicrosecond();
  printf("|Algorithm |  Number  |   kth   |   A[k]   |  Key-Comp  |SWAP COUNT|CollapTime|\n");
  printf("|SELECT1   |%10d|%9d|%10d|%12lld|%10d|%10d|\n", num, kth, value, CAMPCOUNT, SWAPCOUNT, e_us-s_us);
  
  for(int i=0; i<num; i++) {
    fprintf(fout, "%8d%s", data[i], (i+1)%10?" ": "\n");
    dbgPrintf("%8d%s", data[i], (i+1)%10?" ": "\n");
  }
  
  CAMPCOUNT = 0;
  SWAPCOUNT = 0;
  s_us=getMicrosecond();
  int value2 = SELECT2(data2, 0, num-1, kth);
  e_us=getMicrosecond();
  printf("|SELECT2   |%10d|%9d|%10d|%12lld|%10d|%10d|\n", num, kth, value2, CAMPCOUNT, SWAPCOUNT, e_us-s_us);
  
  CAMPCOUNT = 0;
  SWAPCOUNT = 0;
  s_us=getMicrosecond();
  int value3 = SELECT2_2(data3, 0, num-1, kth, temp);
  e_us=getMicrosecond();
  printf("|SELECT2_2 |%10d|%9d|%10d|%12lld|%10d|%10d|\n", num, kth, value3, CAMPCOUNT, SWAPCOUNT, e_us-s_us);
  
  CAMPCOUNT = 0;
  SWAPCOUNT = 0;
  s_us=getMicrosecond();
  int value4 = SELECT3(data4, 0, num-1, kth);
  e_us=getMicrosecond();
  printf("|SELECT3   |%10d|%9d|%10d|%12lld|%10d|%10d|\n", num, kth, value4, CAMPCOUNT, SWAPCOUNT, e_us-s_us);

  free(data);
  free(data2);
  free(data3);
  free(data4);
  free(temp);
  
  fclose(fin);
  fclose(fout);
  return 0;
} 
