# _Buildroot_

_Buildroot_ é uma ferramenta que simplifica e automatiza o processo de montar um sistema Linux completo para um sistema embarcado, usando compilação cruzada (_cross-compilation_).

Esta ferramenta gera uma _toolchain_ de _cross-compilation_, o sistema de arquivos _root_, uma imagem do _kernel_ do  Linux e um _bootloader_ para o sistema embarcado. (Você pode escolher executar somente a parte destes resultados que te interessar.)

O _Buildroot_ é importante no desenvolvimento de sistemas embarcados porque vários destes não utilizam processadores x86, tais como processadores PowerPC, MIPS, ARM etc. Além de atender a diversos processadores, ele também oferece opções prontas para diversas placas.

## Requerimentos

Execute ```sudo apt-get install build-essential libncurses5-dev bzr cvs git mercurial rsync subversion``` no terminal.

## _Download_

O _Buildroot_ está disponível em http://buildroot.org/download.html, e é atualizado a cada 3 meses, em fevereiro, maio, agosto e novembro. As versões são indicadas pelo formato YYYY.MM (por exemplo, 2013.02, 2014.08 etc.).

Para rodar os exemplos desta pasta, execute ```git clone https://github.com/buildroot/buildroot.git buildroot``` no terminal.

## Referências

Livro [Refs/Buildroot_Manual.pdf](Refs/Buildroot_Manual.pdf).
