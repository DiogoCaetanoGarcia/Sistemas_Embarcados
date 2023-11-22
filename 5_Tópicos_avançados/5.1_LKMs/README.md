Para rodar os exemplos desta aula, execute

```
sudo apt install raspberrypi-kernel-headers libncurses5-dev bc bison flex libssl-dev python2 rpi-update
sudo rpi-update
sudo reboot
```

Depois que o Raspberry Pi reiniciar, execute

```
sudo wget https://raw.githubusercontent.com/notro/rpi-source/master/rpi-source -O /usr/bin/rpi-source
sudo chmod +x /usr/bin/rpi-source
python2 /usr/bin/rpi-source -q --tag-update
python2 /usr/bin/rpi-source
sudo ln -s /usr/src/linux-headers-$(uname -r)/ /lib/modules/$(uname -r)/build
```
