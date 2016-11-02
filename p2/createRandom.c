#include"mcomm.h"


void createRandFile(int n, FILE* fp) {
  srand((unsigned)time(NULL));
  for(int i=0; i<n; i++) {
   fprintf(fp, "%d ", 1+(int)(10.0*n*rand()/(RAND_MAX+1.0)));
  }
}

int main(int argc, char* argv[])
{
  
  FILE *fin, *fout;
  for(int i=0; i<argc; i++)
    printf("arg[%d] is %s\n", i, argv[i]);
  if (argc!=3 || !isInt(argv[1])){
    printf("Usage: %s #num filename\n  Create #num random integer to file\n", argv[0]);
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
