# Questões

1. Crie um "Hello World" organizado da seguinte maneira:

- **main.c**: Arquivo principal contendo a função `main( )`;
- **ola.c**: Arquivo contendo a definição da função `ola_mundo( )`, que imprime "Olá mundo!" na tela;
- **ola.h**: Arquivo incluído por **main.c**, contendo a declaração da função `ola_mundo( )`;
- **Makefile**: Arquivo que compila **main.c** e **ola.c** separadamente, e depois conecta os arquivos compilados em um executável chamado `hello`.

2. Crie um código em C que imprime todos os argumentos de entrada fornecidos pelo usuário. Por exemplo, considerando que o código criado recebeu o nome de `ola_argumentos`:

```
$ ./ola_argumentos Eu Mesmo e Minha Pessoa
   Argumentos: Eu Mesmo e Minha Pessoa
```

3. Crie um código em C que pergunta ao usuário o seu nome, e imprime no terminal "Ola " e o nome do usuário. Compile este código com o nome `ola_usuario_1`. Por exemplo:

```
$ ./ola_usuario_1
  Digite o seu nome: Eu
  Ola Eu
```

Utilize a função `scanf()` para obter o nome do usuário. Apresente os comportamentos deste código nos seguintes casos:

a. Se o usuário insere mais de um nome:
```
$ ./ola_usuario_1
  Digite o seu nome: Eu Mesmo
```

b. Se o usuário insere mais de um nome entre aspas duplas. Por exemplo:
```
$ ./ola_usuario_1
  Digite o seu nome: "Eu Mesmo"
```
c.  Se é usado um pipe. Por exemplo:
```
$ echo Eu | ./ola_usuario_1
```

d. Se é usado um pipe com mais de um nome. Por exemplo:
```
$ echo Eu Mesmo | ./ola_usuario_1
```

e. Se é usado um pipe com mais de um nome entre aspas duplas. Por exemplo:
```
$ echo "Eu Mesmo" | ./ola_usuario_1
```

f. Se é usado o redirecionamento de arquivo. Por exemplo:
```
$ echo Eu Mesmo > nome.txt
$ ./ola_usuario_1 < nome.txt
```

4. Crie um código em C que recebe o nome do usuário como um argumento de entrada (usando as variáveis `argc` e `*argv[]`), e imprime no terminal "Ola " e o nome do usuário. Compile este código com o nome `ola_usuario_2`. Por exemplo:

```
$ ./ola_usuario_2 Eu
  Ola Eu
```

Apresente os comportamentos deste código nos seguintes casos:

a. Se o usuário insere mais de um nome:
```
$ ./ola_usuario_2 Eu Mesmo
```

b. Se o usuário insere mais de um nome entre aspas duplas. Por exemplo:
```
$ ./ola_usuario_2 "Eu Mesmo"
```

c. Se é usado um pipe. Por exemplo:
```
$ echo Eu | ./ola_usuario_2
```

d. Se é usado um pipe com mais de um nome. Por exemplo:
```
$ echo Eu Mesmo | ./ola_usuario_2
```

e. Se é usado um pipe com mais de um nome entre aspas duplas. Por exemplo:
```
$ echo "Eu Mesmo" | ./ola_usuario_2
```

f. Se é usado o redirecionamento de arquivo. Por exemplo:
```
$ echo Eu Mesmo > nome.txt
$ ./ola_usuario_2 < nome.txt
```
