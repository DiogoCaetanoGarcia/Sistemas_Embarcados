# Biblioteca GTK

Os exemplos desta pasta foram retirados do livro [C GUI Programming](Refs/C_GUI_Programming.pdf).

Para obter a biblioteca GTK e compilar todos os exemplos, execute

```
$ sudo apt-get install gtk2.0
$ make
```

(Existe uma versão mais recente da biblioteca GTK através de ```sudo apt-get install libgtk-3-dev```, mas nem todos os códigos desta pasta compilam com esta versão. Para compilar os códigos com a versão mais recente da GTK, o ```Makefile``` desta pasta deve ser alterado.)

O _Glade_ é uma interface gráfica para desenvolver interfaces gráficas usando a biblioteca GTK. Com ele, fica mais fácil saber como a interface ficará antes de compilar e executar o projeto. Para utiliza-lo, execute

```
$ sudo apt-get install glade
$ glade
```

# Biblioteca Qt

Uma opção bastante popular para o desenvolvimento de interfaces gráficas é o Qt, que possui muito mais funcionalidades do que o GTK. Para instalar o Qt, execute

```
sudo apt-get update
sudo apt-get install qt5-default
sudo apt-get install qtcreator
sudo apt-get install qtdeclarative5-* qml-module-qtquick* qtquickcontrols5-* qml-module-qtquick2
```

Execute o ```qtcreator``` e confira a enorme quantidade de exemplos disponíveis. Apesar da linguagem utilizada ser o C++, é possível ver que ambas as bibliotecas criam elementos gráficos e respostas a eventos chamando funções específicas.

# Referências

* https://www.gtk.org/documentation.php
* https://doc.qt.io/qt-5/qtexamplesandtutorials.html
* https://sempreupdate.com.br/qual-a-diferenca-entre-gtk-e-qt/
* https://pt.stackoverflow.com/questions/42294/diferen%C3%A7a-do-qt-contra-o-gtk-em-recursos
