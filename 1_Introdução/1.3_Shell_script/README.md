# Questões

1. Crie um arquivo com nome **teste1.txt**, e escreva nele o texto "Número do arquivo = 1". Repita o procedimento para os arquivos **teste2.txt**, **teste3.txt**, ..., **teste100.txt**, escrevendo o texto correspondente para cada um deles ("Número do arquivo = 2", "Número do arquivo = 3", ..., "Número do arquivo = 100").

2. Faça um script chamado **cals.sh** que apresente o calendário de vários meses indicados pelo usuário, usando o seguinte formato:

```
./cals.sh MES1 ANO1 MES2 ANO2 MES3 ANO3
```
Não limite o script a 3 meses. Ele deve funcionar para vários casos, como por exemplo:

```
./cals.sh 1 2020
./cals.sh 1 2019 2 2020 3 2021 1 2010
```

3. Considere um arquivo **sites.txt** com o seguinte conteúdo:

```
https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Refs/Command_line_cheatsheet.pdf
https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Refs/Dicas%20para%20projetos.pdf
https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Refs/Dicas_de_escrita.pdf
```

Estes são links para documentos de dicas desta disciplina, um para cada linha do arquivo **sites.txt**. Faça um script que faz o download destes slides automaticamente, a partir do arquivo **sites.txt**. (DICA: use o comando wget.)

5. Faça uma função chamada `up` que sobe N níveis na pasta onde você estiver, usando `$1` como parâmetro de entrada. Por exemplo, se você estiver em `/home/aluno/Documents` e executar `up 2`, você automaticamente vai para a pasta `/home`.
