# _Buildroot_

[_Buildroot_](https://buildroot.org/) é uma ferramenta que simplifica e automatiza [o processo de montar um sistema Linux completo](Cria%C3%A7%C3%A3o_sistema_Linux.md) para um sistema embarcado, usando compilação cruzada (_cross-compilation_). Outras opções são o [_OpenWRT Project_](https://openwrt.org/) e o [_Yocto Project_](https://www.yoctoproject.org/).

Esta ferramenta gera uma _toolchain_ de _cross-compilation_, o sistema de arquivos _root_, uma imagem do _kernel_ do  Linux e um _bootloader_ para o sistema embarcado. (Você pode escolher executar somente a parte destes resultados que te interessar.)

O _Buildroot_ é importante no desenvolvimento de sistemas embarcados porque vários destes não utilizam processadores x86, tais como processadores PowerPC, MIPS, ARM etc. Além de atender a diversos processadores, ele também oferece opções prontas para diversas placas.

## Requerimentos

Execute ```sudo apt-get install build-essential libncurses5-dev bzr cvs git mercurial rsync subversion``` no terminal.

## _Download_

O _Buildroot_ está disponível no repositório https://github.com/buildroot/buildroot e em http://buildroot.org/download.html, sendo atualizado a cada 3 meses, em fevereiro, maio, agosto e novembro. As versões são indicadas pelo formato YYYY.MM (por exemplo, 2013.02, 2014.08 etc.).

## Sistema mínimo

Para baixar o Buildroot, execute

```
mkdir ~/exemplos_buildroot
cd ~/exemplos_buildroot
git clone https://github.com/buildroot/buildroot.git buildroot
cd buildroot
```

O Buildroot possui configurações pré-definidas para uma série de placas. Execute ```make list-defconfigs``` para ver uma lista destas placas. Como são muitas, execute ```make list-defconfigs | grep raspberry``` para listar somente as configurações para placas Raspberry Pi:

```
  raspberrypi0_defconfig              - Build for raspberrypi0
  raspberrypi0w_defconfig             - Build for raspberrypi0w
  raspberrypi2_defconfig              - Build for raspberrypi2
  raspberrypi3_64_defconfig           - Build for raspberrypi3_64
  raspberrypi3_defconfig              - Build for raspberrypi3
  raspberrypi3_qt5we_defconfig        - Build for raspberrypi3_qt5we
  raspberrypi_defconfig               - Build for raspberrypi
```

A partir daí, escolha a configuração para a sua placa. Por exemplo, para o Raspberry Pi 0W, execute ```make raspberrypi0w_defconfig```. Assim, será criado um ```Makefile``` necessário para compilar todo um sistema Linux mínimo para esta placa. (Executando ```make xconfig```, surge uma interface gráfica para a definição de diversas opções de compilação.) Execute então ```make``` e aguarde cerca de uma hora.

Se não ocorrerem erros, o arquivo ```~/exemplos_buildroot/buildroot/output/images/sdcard.img``` conterá a imagem do sistema operacional mínimo. Instale esta imagem em um cartão SD. No Linux, insira um cartão SD, execute ```lsblk``` para ver quais partições seu cartão SD possui e onde estão montadas, e desmonte-as. Por exemplo, se o seu cartão SD tiver 2 partições montadas em ```/dev/sdb1``` e ```/dev/sdb2```, desmonte-as executando ```sudo umount /dev/sdb1 /dev/sdb2```. Finalmente, instale a imagem executando ```sudo dd bs=4M if=~/exemplos_buildroot/buildroot/output/images/sdcard.img of=/dev/sdb conv=fsync status=progress``` e retire o cartão SD.

Com este sistema instalado, é necessário usar o Raspberry Pi com teclado e tela. Repare que o _boot_ do sistema é bem mais rápido do que o de um sistema operacional regular, como o Raspbian. Para fazer o _login_, utilize o usuário ```root``` com senha em branco. Digite ```ls /bin``` e ```ls /usr/bin``` para ver os poucos programas já instalados (```sudo```, por exemplo, não está presente), e execute ```poweroff``` para desligar o Raspberry Pi.

## _Hello World_

Neste exemplo, criaremos um sistema operacional semelhante ao anterior, mas com um programa _Hello World_ já compilado e executado durante o _boot_. Execute

```
cd ~/exemplos_buildroot
mkdir hello_buildroot
cd hello_buildroot
wget https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/Code/25_Buildroot/hello_buildroot/Config.in
wget https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/Code/25_Buildroot/hello_buildroot/Makefile
wget https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/Code/25_Buildroot/hello_buildroot/hello_buildroot-init
wget https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/Code/25_Buildroot/hello_buildroot/hello_buildroot.c
wget https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/Code/25_Buildroot/hello_buildroot/hello_buildroot.mk
```

para baixar o código do _Hello World_ e outros arquivos importantes:

* `hello_buildroot.c` é o código do _Hello World_, e `Makefile` é o arquivo para compilação do mesmo;
* `hello_buildroot-init` é um _script_ a ser instalado na pasta `/etc/init.d`, garantindo a execução do programa no _boot_ do sistema;
* `Config.in` contém descrições de opções deste programa;
* `hello_buildroot.mk` indica o caminho do código do _Hello World_ para o Buildroot, como compila-lo, aonde instala-lo (```/usr/bin```), e aonde instalar o _script_ `hello_buildroot-init`.

Execute

```
cd ~/exemplos_buildroot/buildroot/packages
mkdir hello_buildroot
cd hello_buildroot
cp ~/exemplos_buildroot/hello_buildroot/Config.in .
cp ~/exemplos_buildroot/hello_buildroot/hello_buildroot.mk .
cd .. 
```

Agora, abra o arquivo `~/exemplos_buildroot/buildroot/packages/Config.in`, procure pelo texto `menu "Miscellaneous"` e insira a linha `source "package/hello_buildroot/Config.in"` mantendo a ordem alfabética dos comandos abaixo da linha `menu "Miscellaneous"`.

Execute

```
cd ..
make xconfig
```

para abrir a interface gráfica de personalização da ompilação do sistema operacional. 
Obs.: Se no seu terminal der algum erro e aparecer

```
* Could not find Qt via pkg-config.
* Please install either Qt 4.8 or 5.x. and make sure it's in PKG_CONFIG_PATH
```

Use `menuconfig` ao invés do `xconfig`

Marque as seguintes opções:

* `System Configuration ==> Run a getty (login prompt) after boot`
* `Target packages ==> Miscellaneous ==> hello_buildroot`
* `Target packages ==> BusyBox ==> Show packages that are also provided by busybox`

e salve estas configurações. Execute ```make``` para criar uma nova imagem do sistema operacional, e a instale em um cartão SD.

Depois de ligar o Raspberry Pi com o novo sistema operacional, faça _login_ como `root` sem senha, e execute ```grep Hello /var/log/message``` para ver as mensagens deixadas durante o _boot_ do sistema pelo _script_ `hello_buildroot-init`. Execute ```ps | grep hello``` para ver que o programa _Hello World_ está em execução. Execute ```hello_buildroot``` para ver o programa _Hello World_ em execução, e aperte CONTROL-C para sair.

## Referências

* [Manual Buildroot](../../Refs/Buildroot/Buildroot_Manual.pdf)
* http://www.chip-community.org/index.php/Startup_Program_with_Buildroot
* https://www.cyberciti.biz/tips/howto-linux-unix-write-to-syslog.html
* https://unix.stackexchange.com/questions/108281/how-long-system-has-been-awake-running-since-restart
