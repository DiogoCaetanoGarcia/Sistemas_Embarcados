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
		curl -v -A USER-AGENT -o saida.html https://www.google.com/search?q=raspberry+pi
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
		curl -v -o saida.html -d searchword=eletronica https://noticias.unb.br/component/search/
		show_box "Aperte ENTER para continuar"
		xdg-open saida.html
		read
		rm saida.html;;
	14) show_box "Envio de dados para Google Forms"
		formid="18YYhW1Dk3xtge66XdG38SfBuPEhm7esfBI4Ajhyh4Bg"
		curl https://docs.google.com/forms/d/$formid/formResponse -d ifq -d "entry.1962235247=Eu Mesmo" -d "entry.146553730=18" -d submit=Submit;;
	15) show_box "Envio de e-mail com o curl"
		email_from="EMAIL_REMETENTE"
		passw_from="SENHA_REMETENTE"
		email_to="EMAIL_DESTINATARIO"
		servidor_envio="smtp://smtp.unb.br:587"
		criptografia="--ssl"
		email_subject="ASSUNTO"
		email_msg="MENSAGEM"
		echo "From: <$email_from>" > email.txt
		echo "To: <$email_to>" >> email.txt
		echo Subject: $email_subject >> email.txt
		echo Date: $(date) >> email.txt
		echo $email_msg >> email.txt
		curl -u $email_from:$passw_from -n -v --mail-from $email_from --mail-rcpt $email_to --url $servidor_envio $criptografia -T email.txt
		show_box "Este foi o arquivo usado para enviar o e-mail"
		cat email.txt
		rm email.txt;;
	16) show_box "Envio de e-mail com imagem em anexo"
		nome_imagem="unb.png"
		email_from="EMAIL_REMETENTE"
		passw_from="SENHA_REMETENTE"
		email_to="EMAIL_DESTINATARIO"
		servidor_envio="smtp://smtp.unb.br:587"
		criptografia="--ssl"
		email_subject="ASSUNTO"
		email_msg="MENSAGEM"
		echo "From: <$email_from>" > email.txt
		echo "To: <$email_to>" >> email.txt
		echo Subject: $email_subject >> email.txt
		echo Date: $(date) >> email.txt
		echo Content-Type: multipart/mixed\; boundary=corpo_msg >> email.txt
		echo >> email.txt
		echo --corpo_msg >> email.txt
		echo Content-Type: text/plain\; charset=UTF-8 >> email.txt
		echo >> email.txt
		echo $email_msg >> email.txt
		echo >> email.txt
		echo --corpo_msg >> email.txt
		echo Content-Type: image/png\; name=\"$nome_imagem\" >> email.txt
		echo Content-Transfer-Encoding: base64 >> email.txt
		echo Content-Disposition: attachment; filename=\"$nome_imagem\" >> email.txt
		echo >> email.txt
		cat $nome_imagem | base64 >> email.txt
		echo --corpo_msg-- >> email.txt
		echo curl -u $email_from:$passw_from -n -v --mail-from $email_from --mail-rcpt $email_to --url $servidor_envio $criptografia -T email.txt
		show_box "Este foi o arquivo usado para enviar o e-mail"
		cat email.txt
		rm email.txt;;
	17) show_box "Envio de dados do browser para o RPi usando o Apache"
		./exemplos.sh 22
		sudo cp formulario_RPi1.html /var/www/html/index.html
		sudo cp obrigado.html /var/www/html/obrigado.html
		show_box "Acesse o servidor em um browser e responda o formulário"
		show_box "Quando terminar, aperte ENTER aqui"
		read
		show_box "Confira se a sua resposta chegou ao RPi"
		tail -1 /var/log/apache2/access.log
		sudo cp /var/www/html/index_original.html /var/www/html/index.html
		./exemplos.sh 21;;
	18) show_box "Envio de dados do browser para o RPi usando o Apache, com um formulário mais bonito"
		./exemplos.sh 22
		sudo cp formulario_RPi2.html /var/www/html/index.html
		sudo cp obrigado.html /var/www/html/obrigado.html
		show_box "Acesse o servidor em um browser e responda o formulário"
		show_box "Quando terminar, aperte ENTER aqui"
		read
		show_box "Confira se a sua resposta chegou ao RPi"
		tail -1 /var/log/apache2/access.log
		./exemplos.sh 21;;
	19) show_box "Mostrar temperatura do RPi no browser"
		./exemplos.sh 22
		echo '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/><title>Temperatura do Raspberry Pi</title></head><body><div class="container"><h1>' > index.html
		echo $(date) >> index.html
		echo '</h1><p>' >> index.html
		echo $(/opt/vc/bin/vcgencmd measure_temp) >> index.html
		echo '</p></div></body></html>' >> index.html
		sudo cp index.html /var/www/html/index.html
		show_box "Acesse o servidor em um browser"
		show_box "Quando terminar, aperte ENTER aqui"
		read
		show_box "Acesse novamente o servidor em um browser, e repare que os dados não mudaram"
		show_box "Quando terminar, aperte ENTER aqui"
		read
		./exemplos.sh 21;;
	20) show_box "Mostrar temperatura do RPi no browser, atualizando a cada segundo"
		./exemplos.sh 22
		show_box "Acesse o servidor em um browser, e atualize a página periodicamente"
		show_box "Quando terminar, aperte CTRL-C para matar este processo e execute './exemplos.sh 21'"
		./update_servidor.sh;;
	21) show_box "Parar a execução do Apache"
		sudo cp /var/www/html/index_original.html /var/www/html/index.html
		sudo /etc/init.d/apache2 stop
		sudo update-rc.d apache2 disable;;
	22)	show_box "Reiniciar a execução do Apache"
		sudo cp /var/www/html/index.html /var/www/html/index_original.html
		sudo update-rc.d apache2 enable
		sudo /etc/init.d/apache2 start;;
	23) show_box "Instalar o Apache2"
		sudo apt-get update
		sudo apt-get install apache2;;
	*) echo "Opção inválida";;
esac
