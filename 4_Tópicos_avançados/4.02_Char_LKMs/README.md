Dentre os vários módulos do *kernel* Linux, *device drivers* permitem a comunicação entre programas e o *hardware* conectado. Por exemplo, executando

```
ls -l /dev/spi*
```

no terminal do Raspbian, são apresentadas as portas SPI disponíveis:

```
crw-rw---- 1 root spi 153, 0 Nov 17 12:39 /dev/spidev0.0
crw-rw---- 1 root spi 153, 1 Nov 17 12:39 /dev/spidev0.1
```

Repare os números apresentados antes da data de criação. O primeiro número, 153, é o *major number*, indicando qual *driver* é usado para acessar este *hardware*. Neste caso, ambas as portas SPI são controladas pelo mesmo *driver*. 

O segundo número (0 e 1) é o *minor number* do *device driver*. Ele é usado para o *driver* distinguir dois ou mais dispositivos.

Existem dois tipo de *device drivers*: de caracter e de bloco. Dispositivos de caracter permitem leituras e escritas de qualquer quantidade de *bytes*, e dispositivos de bloco só permitem leituras e escritas em tamanho pré-determinado. Dispositivos de bloco também possuem um *buffer* para pedidos de leitura e escrita, para que eles definam em qual ordem atenderão a pedidos. Isto é importante para dispositivos de memória, aonde é mais rápido ler e escrever setores próximos ao invés de distantes.

Dispositivos de bloco e de caracter são diferenciados pelo seu primeiro caracter na saída do comando `ls -l`. Por exemplo,

```
ls -l /dev/ram0 /dev/spidev0.0
```

retorna algo como

```
brw-rw---- 1 root disk   1, 0 Nov 17 12:39 /dev/ram0
crw-rw---- 1 root spi  153, 0 Nov 17 12:39 /dev/spidev0.0
```

indicando que `/dev/ram0` é um dispositivo de bloco, e `/dev/spidev0.0` é um dispositivo de caracter.
