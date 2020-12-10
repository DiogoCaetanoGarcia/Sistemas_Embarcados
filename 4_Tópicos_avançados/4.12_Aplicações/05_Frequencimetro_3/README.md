# Frequencímetro com _Buildroot_

Execute o [_script_ nesta pasta](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/Code/27_Aplica%C3%A7%C3%B5es/Frequencimetro_3/preparacao_buildroot.sh) em um computador pessoal ou _laptop_ para criar um sistema operacional mínimo para o Raspberry Pi que execute automaticamente o [frequencímetro com _display_ LCD](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/tree/master/Code/27_Aplica%C3%A7%C3%B5es/Frequencimetro_2). Repare que o _script_ pergunta inicialmente qual o modelo de Raspberry Pi desejado. Além disso, o _script_ não realiza a instalação completa; ao seu término, é necessário executar

```
cd ~/exemplos_buildroot/buildroot
make xconfig
```

selecionar "Target packages ==> Miscellaneous ==> frequencimetro", salvar a configuração do Buildroot, e executar

```
time make
```

Alguns pontos importantes devem ser ressaltados:

* O [Makefile](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/Code/27_Aplica%C3%A7%C3%B5es/Frequencimetro_2/Makefile) do frequencímetro não utiliza o ```gcc``` para compilação, e sim a variável ```$(CC)```. Se fosse usado o ```gcc```, não seria feita a compilação cruzada para o Raspberry Pi; a variável ```$(CC)``` é definida pelo _Buildroot_ para indicar o _cross-compiler_ correspondente.
* O código do frequencímetro depende da biblioteca WiringPi. Para indicar isso ao _Buildroot_, foi acrescentada a linha ```select BR2_PACKAGE_WIRINGPI``` ao arquivo [Config.in](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/Code/27_Aplica%C3%A7%C3%B5es/Frequencimetro_3/Config.in).
* O código do frequencímetro espera que a biblioteca WiringPi seja previamente instalada (comando `-lwiringPi` no [Makefile](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/Code/27_Aplica%C3%A7%C3%B5es/Frequencimetro_2/Makefile)). Para o _Buildroot_ baixar, compilar e instalar a WiringPi antes de compilar o código do frequencímetro, foi adicionada a linha ```FREQUENCIMETRO_DEPENDENCIES = wiringpi``` ao arquivo [frequencimetro.mk](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/Code/27_Aplica%C3%A7%C3%B5es/Frequencimetro_3/frequencimetro.mk).
* Se você estiver criando um programa próprio para ser instalado com o _Buildroot_, e fizer alguma mudança no código, apague a pasta do seu programa em ```~/exemplos_buildroot/buildroot/output/build/``` antes de recompilar todo o projeto do _Buildroot_. Caso contrário, o _Buildroot_ não irá recompilar o seu programa (Seção 8.3 do [Manual Buildroot](../../Refs/Buildroot/Buildroot_Manual.pdf)).
