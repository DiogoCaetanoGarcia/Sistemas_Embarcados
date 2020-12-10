# Dicas Linux e Raspberry Pi

## Execução automática de programas e _scripts_

Existem diversas maneiras de executar automaticamente programas e _scripts_ no Linux:

* Arquivo ```/etc/rc.local``` - acrescente o comando ou _script_ ao final deste arquivo, antes do comando ```exit 0```. Se o arquivo não existir ou estiver vazio, acrescente o comando de sua escolha e o comando ```exit 0``` na linha final do arquivo. Os comandos neste arquivo são executados no _boot_ do sistema.
* Arquivo ```~/.bashrc``` - acrescente o comando ou script ao final deste arquivo. A execução ocorrerá assim que for feito _login_ do usuário nesta conta (Lembre-se de que a pasta ```~``` corresponde a ```/home/NOME_DO_USUARIO```).
* Diretório ```/etc/init.d```: crie um _script_ neste diretório com todos os comandos que você deseja executar. Acrescente o seguinte texto ao começo do _script_, depois do comando ```#!/bin/bash```:

```
### BEGIN INIT INFO
# Provides:          NOME_DO_SCRIPT
# Required-Start:    $all
# Required-Stop:     $all
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Executar este script ao final do boot
### END INIT INFO
```

Este texto documenta todas as dependências do seu _script_ para ele ser executado durante o processo de _boot_.
* Comando ```crontab -e```: execute-o para adicionar tarefas a serem executadas pelo programa ```cron```. Escolha um dos editores de texto indicados pelo  comando ```crontab```, e um arquivo será aberto neste editor. Adicione ```@reboot sudo NOME_DO_COMANDO_OU_SCRIPT``` ao final do arquivo aberto para o comando ou _script_ ser executado no _boot_ do sistema.

## Agendamento de tarefas

A última maneira de executar tarefas automaticamente utilizou o ```crontab``` para agendar esta tarefa no _boot_ do sistema, mas é possível agendar tarefas de acordo com a hora e/ou data do sistema. Execute ```crontab -e``` e acrescente ao final do arquivo aberto as tarefas que deseja executar usando a seguinte terminologia: ```MINUTO HORA DIA MES DIA_DA_SEMANA COMANDO```. Os valores possíveis são:

* ```MINUTO```: `0` a `59`;
* ```HORA```: `0` a `23`;
* ```DIA```: `1` a `31`;
* ```MES```: `1` a `12`;
* ```DIA_DA_SEMANA```: `0` a `7`, sendo que `0` e `7` indicam o domingo.

Estes campos também podem utilizar caracteres especiais:

* `*`: todos valores possíveis;
* `-`: indicador de intervalo (por exemplo, `1-3` indica os números `1`, `2` e `3`);
* `,`: sequência de valores (por exemplo, `1,3` indica os números `1` e `3`);
* `/`: tamanho do salto (por exemplo, `0-10/5` indica os números `0`, `5` e `10`);
* `#`: delimitador de comentário.

Alguns exemplos de uso:

* ```0  20 * * 1-5 comando```: executa o comando de segunda a sexta (1-5), exatamente às 20h.
* ```10 10 1 * * comando```: executa o commando às 10h10 do dia 1º de todos os meses.
* ```0,10,20,30,40,50 * 31 12 * comando```: executa o comando no dia 31 de dezembro, a cada dez minutos, durante todo o dia. 
* ```*/10 * 31 12 * comando```: mesmo que o exemplo anterior.
* ```* * * * * comando```: executa o comando de minuto em minuto.

Também  possível usar alguns parâmetros no lugar destes campos numéricos:

* `@yearly`: equivale a `0 0 1 1 *`;
* `@annually`: equivale a `0 0 1 1 *`;
* `@monthly`: equivale a `0 0 1 * *`;
* `@weekly`: equivale a `0 0 * * 0`;
* `@daily`: equivale a `0 0 * * *`;
* `@midnight`: equivale a `0 0 * * *`;
* `@hourly`:  equivale a `0 * * * *`.

## Desligamento de serviços

Execute ```ls /etc/rc*.d``` para ver todos os serviços automaticamente iniciados pelo sistema operacional. Serão listadas várias pastas, tais como ```/etc/rc0.d```, ```/etc/rc1.d``` e ```/etc/rcS.d```. Os números `0-6` e a letra `S` indicam diferentes _runlevels_, que controlam quais processos e serviços são automaticamente iniciados. `0` corresponde ao _shutdown_, `1` corresponde ao modo de usuário único/modo minimalista, `2-5` correspondem a modos multi-usuário, `6` corresponde ao _reboot_, e `S` corresponde ao modo de usuário único.

Execute ```who -r``` para descobrir em qual _runlevel_ seu sistema está operando, e desabilite serviços desnecessários executando ```update-rc.d NOME_DO_SERVICO disable```.

## Economia de energia via _hardware_

Dependendo do sistema a ser desenvolvido, é possível desligar alguns recursos do Raspberry Pi para economizar energia. Obviamente, desligue somente o que você não precisar:

* _Chip_ USB: se você não precisar da porta USB, é possível desabilitar o acesso à porta USB executando ```echo '1-1' |sudo tee /sys/bus/usb/drivers/usb/unbind```. Para reabilitar o acesso, execute ```echo '1-1' |sudo tee /sys/bus/usb/drivers/usb/bind```.
* Saída HDMI: desabilite a saída de video executando ```sudo /opt/vc/bin/tvservice -o```, e a reabilite executando ```sudo /opt/vc/bin/tvservice -p```.
* WiFi e Bluetooth: desabilite estes serviços acrescentando as linhas ```dtoverlay=pi3-disable-wifi``` e ```dtoverlay=pi3-disable-bt``` ao arquivo ```/boot/config.txt```. As mudanças ocorrerão após o _boot_ do sistema. Remova estas linhas do arquivo ```/boot/config.txt``` para reabilitar estes serviços.
* LEDs da placa: assim como a WiFi e o Bluetooth, desabilite os LEDs acrescentando as linhas ```dtparam=act_led_trigger=none``` e ```dtparam=act_led_activelow=on``` ao arquivo ```/boot/config.txt```.

## _Webcams_

O pacote ```fswebcam``` permite utilizar _webcams_ com o Raspberry Pi:

* Execute ```sudo apt-get install fswebcam``` para instalar este pacote.
* Se você não estiver usando a conta padrão ```pi``` no Rasbian, execute ```sudo usermod -a -G video NOME_DO_USUARIO``` para ter acesso à _webcam_ nesta conta.
* Execute ```fswebcam image.jpg``` para tirar uma foto com a _webcam_, e salva-la em formato JPEG com o nome ```image.jpg```.
* Execute ```fswebcam -r 1280x720 image.jpg``` para tirar a foto na resolução de `1280x720` _pixels_.
* Execute ```fswebcam -r 1280x720 --no-banner image.jpg``` para retirar o _banner horizontal_ da foto.

## _Player_ de audio e video

Utilize o comando ```omxplayer NOME_DO_ARQUIVO```, onde o arquivo pode ser de áudio (MP3 etc.) ou video (MP4 etc.). Este comando possui diversas opções:

* Saída de audio: `-o hdmi` para HDMI, `-o local` para o conector de fone de ouvido e `-o both` para ambos;
* Saída de video: `--display 5` para HDMI, `--display 4` para o [_touchscreen_ da Raspberry Pi Foundation](https://www.raspberrypi.org/products/raspberry-pi-touch-display/);
* Tamanho da tela: `--win 0,0,640,480` para mostrar o video dentro de uma janela de `640x480` _pixels_;
* Recorte do video: `--crop 100,100,300,300` para mostrar somente os _pixels_ das posições `(100,100)` até `(300,300)` do video escolhido.

## Conversão de áudio, video e imagens

Conversão de audio e video: [FFMPEG](https://blogs.warwick.ac.uk/mikewillis/entry/quick_and_easy/).

Conversão de imagens: ImageMagick (```sudo apt-get install imagemagick```). Exemplos:
* ```convert file.png file.jpeg``` converte uma imagem PNG para JPEG.
* ```convert file.png -resize 150 150-file.png``` muda a largura da imagem PNG para `150` _pixels_.

## Informações do sistema

O comando ```vcgencmd``` disponibiliza diversas informações relevantes do _hardware_ do Raspberry Pi:

* ```vcgencmd measure_clock core``` apresenta a frequência de _clock_ da CPU;
* ```for src in arm core h264 isp v3d uart pwm emmc pixel vec hdmi dpi ; do echo -e "$src:\t$(vcgencmd measure_clock $src)" ; done``` apresenta diversas frequências de _clock_;
* ```vcgencmd measure_volts core``` apresenta a tensão da CPU;
* ```for id in core sdram_c sdram_i sdram_p ; do echo -e "$id:\t$(vcgencmd measure_volts $id)" ; done``` apresenta diversas tensões;
* ```vcgencmd measure_temp``` apresenta a temperatura do SoC BCM2835;
* ```vcgencmd codec_enabled H264``` indica se o _codec_ H.264/AVC está habilitado;
* ```for codec in H264 MPG2 WVC1 MPG4 MJPG WMV9 ; do echo -e "$codec:\t$(vcgencmd codec_enabled $codec)" ; done``` indica se diversos _codecs_ estão habilitados;
* ```vcgencmd get_config int``` apresenta as configurações atualmente definidas;
* ```vcgencmd get_mem arm``` e ```vcgencmd get_mem gpu``` indicam quanta memória está separada para a CPU e a GPU, especificamente;
* ```vcgencmd commands``` lista todos os comandos possíveis.

# Referências

* https://www.dexterindustries.com/howto/run-a-program-on-your-raspberry-pi-at-startup/
* https://wiki.debian.org/LSBInitScripts
* https://www.dexterindustries.com/howto/auto-run-python-programs-on-the-raspberry-pi/
* https://e-tinet.com/linux/crontab/
* https://www.dicas-l.com.br/arquivo/automatizacao_de_tarefas_com_crontab_e_cron.php
* https://wiki.debian.org/RunLevel
* https://linuxconfig.org/how-to-check-a-current-runlevel-of-your-linux-system
* https://www.raspberrypi.org/forums/viewtopic.php?t=28502
* https://learn.pi-supply.com/make/how-to-save-power-on-your-raspberry-pi/
* https://www.raspberrypi.org/documentation/usage/webcams/README.md
* https://www.raspberrypi.org/documentation/raspbian/applications/omxplayer.md
* https://blogs.warwick.ac.uk/mikewillis/entry/quick_and_easy/
* https://www.theurbanpenguin.com/image-manipulation-on-the-raspberry-pi-using-imagemagick/
* https://elinux.org/RPI_vcgencmd_usage
* https://github.com/nezticle/RaspberryPi-BuildRoot/wiki/VideoCore-Tools
