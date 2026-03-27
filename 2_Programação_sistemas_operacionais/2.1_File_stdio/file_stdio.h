#ifndef _FILE_STDIO_H_
#define _FILE_STDIO_H_

#include <stdio.h>
#include <stdlib.h>

void erro_fopen(FILE *fp);
FILE * abre_arq(char* arquivo, char *modo);
void le_arq(FILE *p);

#endif // _FILE_STDIO_H_