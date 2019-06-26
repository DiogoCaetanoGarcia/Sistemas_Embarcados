# Dicas de uso do Linux e do Raspberry Pi

## Execução automática de programas e _scripts_

Existem diversas maneiras de executar automaticamente programas e _scripts_ no Linux:

* Arquivo ```/etc/rc.local``` - acrescente o comando ou _script_ ao final deste arquivo, antes do comando ```exit 0```. Se o arquivo não existir ou estiver vazio, acrescente o comando de sua escolha e o comando ```exit 0``` na linha final do arquivo. Os comandos neste arquivo são executados no _boot_ do sistema.
* Arquivo ```~\.bashrc``` - acrescente o comando ou script ao final deste arquivo. A execução ocorrerá assim que for feito _login_ do usuário nesta conta (Lembre-se de que a pasta ```~``` corresponde a ```/home/NOME_DO_USUARIO```).
* Diretório ```/etc/init.d```: crie um _script_ neste diretório com todos os comandos que você deseja executar. Acrescente o seguinte texto ao começo do _script_, depois do comando ```#! /bin/bash```:

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

# Referências

* https://www.dexterindustries.com/howto/run-a-program-on-your-raspberry-pi-at-startup/
* https://wiki.debian.org/LSBInitScripts