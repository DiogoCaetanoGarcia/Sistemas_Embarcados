Exemplos do livro Refs/C_GUI_Programming.pdf.

Para compila-los, execute

```
$ sudo apt-get install gtk2.0
```

para obter a biblioteca GTK, e

```
$ make
```

para compilar todos os exemplos.

Execute

```
$ sudo apt-get install glade
$ glade
```
para utilizar o _Glade_, uma interface gráfica para desenvolver interfaces gráficas.

(Existe uma versão mais recente da biblioteca GTK através de ```sudo apt-get install libgtk-3-dev```, mas nem todos os códigos desta pasta compilam com esta versão. Para compilar os códigos com a versão mais recente da GTK, o ```Makefile``` desta pasta deve ser alterado.)