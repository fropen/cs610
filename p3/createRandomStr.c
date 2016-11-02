#include"mcomm.h"


void createRandFile(int n, FILE* fp) {
  for(int i=0; i<n; i++) {
    int k = rand_between(1, 21);
 //   printf("\nk=%d\n", k);
    for(int j=0; j<=k; j++) {
      int c = rand_between('A', 'Z'+1);
//      printf("%4d", c);
      fprintf(fp, "%c", c);
    }
    fprintf(fp, "\n");
    
  }
}

int main(int argc, char* argv[])
{
  
  FILE *fin, *fout;
  for(int i=0; i<argc; i++)
    printf("arg[%d] is %s\n", i, argv[i]);
  if (argc!=3 || !isInt(argv[1])){
    printf("Usage: %s #num filename\n  Create #num random string to file\n", argv[0]);
    exit(0);
  }
  
  int num = atoi(argv[1]);
  
  if ((fout=fopen(argv[2],"w"))==NULL){
    printf("fopen %s error", argv[2]);
    exit(0);
  }
  
  createRandFile(num, fout);
  fclose(fout);
  return 0;
} 
