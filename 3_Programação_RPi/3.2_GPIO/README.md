# Instalação de requisitos

Para rodar os exemplos desta aula, execute

```
sudo apt-get install build-essential
sudo apt-get install git-all
cd ~
git clone https://github.com/WiringPi/WiringPi
cd ~/WiringPi
./build
cd ..
```

# Questões

1. Escreva um código em C para gerar uma onda quadrada de 1 Hz em um pino GPIO do Raspberry Pi.
2. Escreva um código em C para gerar uma onda quadrada em um pino GPIO do Raspberry Pi. Generalize o código para qualquer frequência factível.
3. Crie dois processos, e faça com que o processo-filho gere uma onda quadrada, enquanto o processo-pai lê um botão no GPIO, aumentando a frequência da onda sempre que o botão for pressionado. A frequência da onda quadrada deve começar em 1 Hz, e dobrar cada vez que o botão for pressionado. A frequência máxima é de 64 Hz, devendo retornar a 1 Hz se o botão for pressionado novamente.  
