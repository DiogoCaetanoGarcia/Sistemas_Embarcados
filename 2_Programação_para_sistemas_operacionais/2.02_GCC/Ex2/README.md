Execute os seguintes comandos para ver a pasta antes e depois da compilação:

	$ ls -l
	$ make
	$ ls -l

Execute o programa recém criado:

	$ ./mensagens
	$ ./mensagens Fulano
	$ ./mensagens Beltrano

Para apagar os arquivos criados, execute:

	$ make clean

A flag 'CFLAGS' no arquivo 'Makefile' permite acrescentar argumentos às chamadas ao gcc. Por exemplo:

	$ make clean
	$ make CFLAGS=-O0
	$ ls -l mensagens

Repare o tamanho do programa criado. Agora, execute:

	$ make clean
	$ make CFLAGS=-O3
	$ ls -l mensagens
 
Repare novamente o tamanho do programa criado.

[Confira as principais opções de compilação do GCC](https://www.rapidtables.com/code/linux/gcc/gcc-o.html).
