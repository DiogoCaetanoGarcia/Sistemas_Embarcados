#include <stdio.h>
#include <stdlib.h> /* Para a função exit() */

int main(int argc, const char * argv[]) {
   
   FILE *fp;
   fp=fopen ("exemplo.bin","wb");
   if (!fp)
   {
       printf ("Erro na abertura do arquivo. Fim de programa.");
       exit (1);
   }
   return 0;
}