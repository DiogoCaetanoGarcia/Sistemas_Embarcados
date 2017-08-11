#include <stdio.h>

int main(int argc, const char * argv[]) {
   
   FILE *fp; // Declaracao da estrutura
   fp=fopen ("exemplo.bin","wb");  /* o arquivo se chama exemplo.bin e esta
                                       localizado no diretório corrente */
   if (!fp)
       printf ("Erro na abertura do arquivo.");
   
   return 0;
}