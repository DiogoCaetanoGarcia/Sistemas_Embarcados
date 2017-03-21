#include <stdio.h>
#include <stdlib.h>
int main(int argc, const char * argv[]) {

   FILE *fp;
   char c;
   fp = fopen("arquivo.txt","r"); /* Arquivo ASCII, para leitura */
   if(!fp)
   {
       printf( "Erro na abertura do arquivo");
       exit(-1);
   }
   while((c = getc(fp) ) != EOF)  /* Enquanto não chegar ao final do arquivo */
       printf("%c", c);           /* imprime o caracter lido */
   fclose(fp);
   printf("\n");
   return 0;
}