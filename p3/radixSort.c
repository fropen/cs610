#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mcomm.h"

void LSD(char** src, int N, int W, int buckets, char** dst) {
  dbgPrintf("\nLSD N=%d, W=%d", N, W);
  int d = W-1;
  if (d<0) return;
  
  int *count = (int*)malloc(sizeof(int)*(buckets+1));
  memset(count, 0, sizeof(int)*(buckets+1));
  
  // compute frequency counts
  for (int i = 0; i < N; i++) {
    dbgPrintf("\n%5d,%5d", i, src[i][d]);
    count[src[i][d]+1]++;
  }

  // compute cumulates
  for (int r = 0; r < buckets; r++) {
    count[r+1] += count[r];
    dbgPrintf("\n%5d,%5d", r+1, count[r+1]);
  }

  // move data
  for (int i = 0; i < N; i++) {
    dst[count[src[i][d]]++] = src[i];
  }
  
  free(count);
  
  //recursive call
  LSD(dst, N, d, buckets, src);
  
  
}

char** radix_sort(char a[][22], int N, int W) {
  dbgPrintf("\nradix_sort N=%d, W=%d", N, W);
  int buckets = 256;
  char **src = malloc(sizeof(char*)*N);
  char **dst = malloc(sizeof(char*)*N);
  
  for (int x = 0; x<N; x++) {
    src[x] = a[x];
  }
  
  LSD(src, N, W, buckets, dst);
  free(src);
  
  return dst;

}


int main(int argc, char * argv[]) {

  if (argc>=4){
    printf("Usage: %s [srcfile [dstfile]]\n\n", argv[0]);
    exit(0);
  }
  char srcfile[100];
  char dstfile[100];
  if (argc==3) {
    strcpy(srcfile, argv[1]);
    strcpy(dstfile, argv[2]);
  }
  else if(argc==2) {
    strcpy(srcfile, argv[1]);
    strcpy(dstfile, "g.txt");
  }
  else if(argc==1) {
    printf("\nPlease specify input file (default f.txt): ");
    fgets(srcfile, 99, stdin);
    if(strcmp(srcfile, "\n")==0) strcpy(srcfile, "f.txt");
    printf("\nPlease specify output file (default g.txt): ");
    fgets(dstfile, 99, stdin);
    if(strcmp(dstfile, "\n")==0) strcpy(dstfile, "g.txt");
  }
  printf("\nUsage: %s [srcfile [dstfile]]", argv[0]);
  printf("\n   This program will sort the data of %s.\n \
  Line will be truncated if the length greater than 21.\n \
  Limits 1000 lines, others will be ignored.", srcfile);
  
  printf("\nInput file:  %s", srcfile);
  printf("\nOutput file: %s", dstfile);
  
  FILE *fin, *fout;
  if ((fin=fopen(srcfile,"r"))==NULL){
    printf("\nfopen %s error", srcfile);
    exit(0);
  }

  if ((fout=fopen(dstfile,"w"))==NULL){
    printf("\nfopen %s error", dstfile);
    exit(0);
  }

  char src_str[1000][22];
  memset(src_str, 0, 22000);
  int lines = 0;
  for (lines=0; lines<1000; lines++) {
    if(fscanf(fin, "%21s", src_str[lines])==EOF)
    break;
  }
  
  long long s_us=getMicrosecond();
  char** dst = radix_sort(src_str, lines, 21);
  long long e_us=getMicrosecond();
  
  printf("\nlines:core radis_sort time = %d:%lld\nDone.\n", lines, e_us-s_us);
  
  for (int i = 0; i < lines; i++) {
    fprintf(fout, "%s\n", dst[i]);
    dbgPrintf("\ndst[%d] = %s", i, dst[i]);
  }
  free(dst);

  fclose(fin);
  fclose(fout);
  return 0;
}

