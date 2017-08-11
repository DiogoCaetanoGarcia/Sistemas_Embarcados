#include <stdio.h>
#include <stdlib.h>
int main(int argc, const char * argv[]) {
  FILE *fp;
  char string[100];
  int i;
  fp = fopen("arquivo.txt","w");
  if(!fp)
  {
    /* Arquivo ASCII, para escrita */
    printf( "Erro na abertura do arquivo");
    exit(0);
  }
  printf("Entre com a string a ser gravada no arquivo:");
  gets(string);
  for(i=0; string[i]; i++) putc(string[i], fp); /* Grava a string, caractere a
                                                caractere */
  putc('\n', fp);
  fclose(fp);
  return 0;
}