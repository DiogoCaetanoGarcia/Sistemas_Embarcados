Para rodar os exemplos desta aula, execute

```
sudo apt install linux-headers-rpi-v8 libncurses5-dev bc bison flex libssl-dev rpi-update
CUR_DIR=$(pwd)
cd ~
wget https://www.python.org/ftp/python/2.7.9/Python-2.7.9.tgz
sudo tar xzf Python-2.7.9.tgz
cd Python-2.7.9
sudo ./configure --enable-optimizations
sudo make altinstall
cd ${CUR_DIR}
sudo rpi-update
sudo reboot
```

Depois que o Raspberry Pi reiniciar, execute

```
sudo wget https://raw.githubusercontent.com/notro/rpi-source/master/rpi-source -O /usr/bin/rpi-source
sudo chmod +x /usr/bin/rpi-source
python2.7 /usr/bin/rpi-source -q --tag-update
python2.7 /usr/bin/rpi-source
sudo ln -s /usr/src/linux-headers-$(uname -r)/ /lib/modules/$(uname -r)/build
```
