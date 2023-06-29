# Frequencímetro com _Buildroot_

Execute o [_script_ nesta pasta](https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/5_T%C3%B3picos_avan%C3%A7ados/5.6_Aplica%C3%A7%C3%B5es/6_Frequencimetro_4/preparacao_buildroot.sh) em um computador pessoal ou _laptop_ para criar um sistema operacional mínimo para o Raspberry Pi que execute automaticamente o [frequencímetro com _display_ LCD](https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/5_T%C3%B3picos_avan%C3%A7ados/5.6_Aplica%C3%A7%C3%B5es/5_Frequencimetro_3). Repare que o _script_ pergunta inicialmente qual o modelo de Raspberry Pi desejado. Além disso, o _script_ não realiza a instalação completa; ao seu término, é necessário executar

```
cd ~/exemplos_buildroot/buildroot
make menuconfig
```

selecionar "Target packages ==> Miscellaneous ==> frequencimetro", salvar a configuração do Buildroot, e executar

```
time make
```

Alguns pontos importantes devem ser ressaltados:

* O [Makefile](https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/5_T%C3%B3picos_avan%C3%A7ados/5.6_Aplica%C3%A7%C3%B5es/5_Frequencimetro_3/Makefile) do frequencímetro não utiliza o ```gcc``` para compilação, e sim a variável ```$(CC)```. Se fosse usado o ```gcc```, não seria feita a compilação cruzada para o Raspberry Pi; a variável ```$(CC)``` é definida pelo _Buildroot_ para indicar o _cross-compiler_ correspondente.
* O código do frequencímetro depende da biblioteca PIGPIO. Para indicar isso ao _Buildroot_, foi acrescentada a linha ```select BR2_PACKAGE_PIGPIO``` ao arquivo [Config.in](https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/5_T%C3%B3picos_avan%C3%A7ados/5.6_Aplica%C3%A7%C3%B5es/6_Frequencimetro_4/Config.in).
* O código do frequencímetro espera que a biblioteca PIGPIO seja previamente instalada (comando `-lpigpio` no [Makefile](https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/5_T%C3%B3picos_avan%C3%A7ados/5.6_Aplica%C3%A7%C3%B5es/5_Frequencimetro_3/Makefile)). Para o _Buildroot_ baixar, compilar e instalar a PIGPIO antes de compilar o código do frequencímetro, foi adicionada a linha ```FREQUENCIMETRO_DEPENDENCIES = pigpio``` ao arquivo [frequencimetro.mk](https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/5_T%C3%B3picos_avan%C3%A7ados/5.6_Aplica%C3%A7%C3%B5es/6_Frequencimetro_4/frequencimetro.mk).
* Se você estiver criando um programa próprio para ser instalado com o _Buildroot_, e fizer alguma mudança no código, apague a pasta do seu programa em ```~/exemplos_buildroot/buildroot/output/build/``` antes de recompilar todo o projeto do _Buildroot_. Caso contrário, o _Buildroot_ não irá recompilar o seu programa (Seção 8.3 do [Manual Buildroot](../../Refs/Buildroot/Buildroot_Manual.pdf)).
