#!/bin/bash

function show_box()
{
	SHOW_BOX_MSG=$1
	SHOW_BOX_L=${#SHOW_BOX_MSG}
	SHOW_BOX_L=$((SHOW_BOX_L+4))
	SHOW_BOX_LINE=""
	for SHOW_BOX_i in $(seq $SHOW_BOX_L)
	do
		SHOW_BOX_LINE=${SHOW_BOX_LINE}"-"
	done
	echo
	echo ${SHOW_BOX_LINE}
	echo \| $SHOW_BOX_MSG \|
	echo ${SHOW_BOX_LINE}
	echo
}

case $1 in
	0) show_box "Apagar arquivos desnecessários"
		rm -f *.txt index.html saida.html Arquivo_na_nuvem1.pdf Arquivo_na_nuvem2.pdf README.md;;
	1) show_box "Listar redes Wi-Fi. Interfaces disponíveis:"
		ifconfig -s
		show_box "Digite o nome da interface"
		read INTERFACE
		sudo iwlist ${INTERFACE} scan > redes_wifi.txt
		grep SSID redes_wifi.txt;;
	2) show_box "Criptografar senha Wi-Fi para rede hipotética 'testing'"
		show_box "Digite a senha 'testingPassword'"
		wpa_passphrase testing;;
	3) show_box "Download de arquivos com o wget"
		wget https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/README.md
		wget https://www.unb.br
		show_box "Arquivos 'README.md' e 'index.html' baixados"
		ls -l README.md index.html;;
	4) show_box "Download de arquivos com o curl"
		rm README.md
		curl -O https://raw.githubusercontent.com/DiogoCaetanoGarcia/Sistemas_Embarcados/master/README.md
		curl -o saida.html https://www.unb.br
		show_box "Arquivos 'README.md' e 'saida.html' baixados"
		ls -l README.md saida.html;;
	5) show_box "Download de arquivo no Google Drive"
		filename="Arquivo_na_nuvem1.pdf"
		fileid="11uI5-BAXzIhKO14clUwmQlAo8LyqS-Ui"
		curl -L -o ${filename} "https://drive.google.com/uc?export=download&id=${fileid}"
		show_box "Arquivo '${filename}' baixado"
		ls -l ${filename};;
	6) show_box "Download de arquivo com mais de 100MB no Google Drive"
		filename="Arquivo_na_nuvem2.pdf"
		fileid="1EPVcIVl0UiNtjw9S751ZRiw_FQdTLHf0"
		curl -L -c cookies.txt 'https://docs.google.com/uc?export=download&id='$fileid | sed -rn 's/.*confirm=([0-9A-Za-z_]+).*/\1/p' > confirm.txt
		curl -L -b cookies.txt -o $filename 'https://docs.google.com/uc?export=download&id='$fileid'&confirm='$(<confirm.txt)
		rm -f confirm.txt cookies.txt
		show_box "Arquivo '${filename}' baixado"
		ls -l ${filename};;
	7) show_box "Busca no Google pelo termo 'raspberry pi'"
		curl -o saida.html https://www.google.com/search?q=raspberry+pi
		show_box "Repare a mensagem de erro"
		grep --color "Your client does not have permission to get URL" saida.html;;
	8) show_box "Repare na forma como o 'curl' se identifica para o servidor (campo 'User-Agent:')"
		curl -v www.unb.br > /dev/null
		show_box "Busca VÁLIDA no Google pelo termo 'raspberry pi'"
		curl -A USER-AGENT -o saida.html https://www.google.com/search?q=raspberry+pi
		xdg-open saida.html;;
	9) show_box "Hora atual pela internet, baseado no IP"
		curl http://worldtimeapi.org/api/ip.txt
		echo;;
	10) show_box "Hora atual pela internet, baseado no fuso horário de São-Paulo"
		curl http://worldtimeapi.org/api/timezone/America/Sao_Paulo.txt
		echo;;
	11) show_box "Fuso-horários disponíveis"
		curl http://worldtimeapi.org/api/timezone.txt
		echo;;
	12) show_box "Update da hora do computador a partir do fuso-horário de Greenwich"
		sudo date +%s -s @$(curl -s http://worldtimeapi.org/api/timezone/Etc/GMT.txt | grep unixtime | sed "s/unixtime: //")
		date
		show_box "Aperte ENTER para continuar"
		read
		show_box "Update da hora do computador a partir do seu IP"
		sudo date +%s -s @$(curl -s http://worldtimeapi.org/api/ip.txt | grep unixtime | sed "s/unixtime: //")
		date;;
	13) show_box "Exemplo de requisição POST"
		curl -v -o saida.html -d query=eletronica http://noticias.unb.br/component/search/
		show_box "Aperte ENTER para continuar"
		xdg-open saida.html
		read
		rm saida.html;;
	14) show_box "Envio de dados para Google Forms"
		formid="18YYhW1Dk3xtge66XdG38SfBuPEhm7esfBI4Ajhyh4Bg"
		curl https://docs.google.com/forms/d/$formid/formResponse -d ifq -d "entry.1962235247=Eu Mesmo" -d "entry.146553730=18" -d submit=Submit;;
	*) echo "Opção inválida";;
esac
