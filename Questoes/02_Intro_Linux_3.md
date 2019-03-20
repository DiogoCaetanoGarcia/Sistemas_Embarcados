Para todas as questões, escreva os scripts e as chamadas correspondentes no terminal.

1. Crie um arquivo com nome _teste1.txt_, e escreva nele o texto "Número do arquivo = 1". Repita o procedimento para os arquivos _teste2.txt_, _teste3.txt_, ..., _teste100.txt_, escrevendo o texto correspondente para cada um deles ("Número do arquivo = 2", "Número do arquivo = 3", ..., "Número do arquivo = 100").

2. Faça um script chamado _cals.sh_ que apresente o calendário de vários meses indicados pelo usuário, usando o seguinte formato:

```script
./cals.sh MES1 ANO1 MES2 ANO2 MES3 ANO3
```

Não limite o script a 3 meses. Ele deve funcionar para vários casos, como por exemplo:

```script
./cals.sh 1 2020
./cals.sh 1 2019 2 2020 3 2021 1 2010
```

3. Utilizando a lógica do script anterior, descubra em que dia da semana caiu o seu aniversário nos últimos dez anos.

4. Crie um arquivo _sites.txt_ com o seguinte conteúdo:

```
https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Aulas/01_Linux%20b%C3%A1sico.pdf
https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Aulas/01_Linux%20b%C3%A1sico_Shell_Script.pdf
https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Aulas/01_Sistemas%20Embarcados%20-%20Aula%201%20-%20Introdu%C3%A7%C3%A3o.pdf
```

Estes são links para slides de 3 aulas desta dsciplina, um para cada linha do arquivo _sites.txt_. Faça um script que faz o download destes slides automaticamente, a partir do arquivo _sites.txt_. (DICA: use o comando wget.)

5. Faça um script chamado _up.sh_ que sobe _N_ níveis na pasta onde você estiver, usando $1 como parâmetro de entrada. Por exemplo, se você estiver em **/home/aluno/Documents** e executar **./up.sh 2**, você automaticamente vai para a pasta **/home**.
