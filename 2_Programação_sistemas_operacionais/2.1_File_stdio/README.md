# Questões

1. Crie um código em C para escrever "Ola mundo!" em um arquivo chamado **ola_mundo.txt**. Utilize as funções da biblioteca `stdio.h` de leitura e de escrita em arquivo (`fopen()`, `fclose()`, `fwrite()`, `fread()`, dentre outras). Compile os códigos com o `gcc` e execute-os via terminal.

2. Crie um código em C que pergunta ao usuário seu nome e sua idade, e escreve este conteúdo em um arquivo com o seu nome e extensão '.txt'. Por exemplo, considerando que o código criado recebeu o nome de `ola_usuario_1`:

```
$ ./ola_usuario_1
  Digite o seu nome: Eu
  Digite a sua idade: 30
$ cat Eu.txt
  Nome: Eu
  Idade: 30 anos
```

Utilize as funções da biblioteca `stdio.h` de leitura e de escrita em arquivo (`fopen()`, `fclose()`, `fwrite()`, `fread()`, dentre outras). Compile os códigos com o `gcc` e execute-os via terminal.

3. Crie um código em C que recebe o nome do usuário e e sua idade como argumentos de entrada (usando as variáveis `argc` e `*argv[]`), e escreve este conteúdo em um arquivo com o seu nome e extensão '.txt'. Por exemplo, considerando que o código criado recebeu o nome de `ola_usuario_2`:

```
$ ./ola_usuario_2 Eu 30
$ cat Eu.txt
  Nome: Eu
  Idade: 30 anos
```

Utilize as funções da biblioteca `stdio.h` de leitura e de escrita em arquivo (`fopen()`, `fclose()`, `fwrite()`, `fread()`, dentre outras). Compile os códigos com o `gcc` e execute-os via terminal.

4. Crie um código em C que conta a ocorrência de uma palavra-chave em um arquivo-texto, e escreve o resultado no terminal. Reaproveite as funções já criadas nas questões anteriores. Por exemplo, considerando que o código criado recebeu o nome de `busca_e_conta`:

```
$ echo Ola mundo cruel! Ola universo ingrato! > ola.txt
$ ./busca_e_conta Ola ola.txt
  'Ola' ocorre 2 vezes no arquivo 'ola.txt'.
```

Utilize as funções da biblioteca `stdio.h` de leitura e de escrita em arquivo (`fopen()`, `fclose()`, `fwrite()`, `fread()`, dentre outras). Compile os códigos com o `gcc` e execute-os via terminal.
