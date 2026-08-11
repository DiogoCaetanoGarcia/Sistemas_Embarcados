# Sistemas Operacionais Embarcados - Plano de Ensino

- Código: FGA0309
- Créditos: 6
- Turma: A
- Locais e horários: Lab SS, 2<sup>as</sup>, 4<sup>as</sup> e 6<sup>as</sup> feiras, sempre das 14:00 às 15:50
- Professor: Diogo Caetano Garcia
- Email: diogogarcia(at)unb.br

## Formato das aulas

- O curso consistirá em aulas teóricas presenciais, nas segundas, quartas e sextas, sempre das 14:00 às 15:50.
- Todo o conteúdo, listas de exercícios, provas e entrega de trabalhos estarão disponíveis via página no Moodle Aprender 3.
- O aluno pode tirar dúvidas via fórum de dúvidas no Moodle da disciplina, ou pode agendar por e-mail uma reunião via video-conferência.

## Controle de presenças

A presença dos alunos será conferida a cada aula, sendo necessário assistir a pelo menos 75% das aulas para não receber menção SR ao final do semestre.

## Critérios de avaliação

A avaliação na disciplina é dividida da seguinte forma:

- Dois testes, cada um valendo 20% da nota final;
- Projeto da disciplina, valendo 25% da nota final;
- 5 pontos de controle do projeto da disciplina, cada um valendo 5% da nota final;
- Respostas dos questionários das aulas no Moodle, valendo 10% da nota final.

![Calendário](https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/blob/master/Calendario.jpg)

### Projeto

Os alunos formarão duplas para montar um projeto final de maior dificuldade, cobrindo os tópicos vistos em sala de aula. Os projetos serão propostos pelos alunos, e será apresentado um protótipo em funcionamento e o repositório documentado do mesmo, seguindo [este template](https://github.com/DiogoCaetanoGarcia/SOE_template).

Os pontos de controle serão prévias do projeto final. Cada dia de atraso na apresentação dos pontos de controle acarreta na perda de 0,5 ponto da nota do mesmo. Serão esperados os seguintes resultados para cada ponto de controle:

- PC1: proposta do projeto
	- 1 - Termo de Abertura do Projeto
	- 2 - Requisitos
	- 3 - Estrutura Analítica do Produto
- PC2: projeto conceitual e gestão de recursos (tempo e dinheiro)
	- 4.1 - Projeto conceitual de hardware
	- 4.2 - Projeto conceitual de software
	- 5 - Cronograma
- PC3: testes de componentes e algoritmos
	- 6.1 - Testes de hardware
	- 6.2 - Testes de software
- PC4: integração de componentes
	- 6.3 - Testes de integração
- PC5: integração de componentes
	- 6.3 - Testes de integração
- Entrega final
	- 7 - Relatório de encerramento do projeto

Fazendo uma analogia com o projeto com a montagem de um quebra-cabeças:

- PC1: escolha do quebra-cabeças
- PC2: estruturação do quebra-cabeças
- PC3: disposição de todas as peças do quebra-cabeças sobre a mesa
- PC4 e PC5: montagem do quebra-cabeças

Todos os relatórios dos pontos de controle serão entregues via Moodle. Em caso de cópias (integrais ou parciais), os relatórios ficarão com nota ZERO.

### Orientações para a escolha do tema do projeto

A escolha do tema do projeto é responsabilidade dos alunos. Entretanto, a proposta deverá observar as seguintes orientações:

1. **O projeto deverá resultar em um protótipo funcional.** Não é permitida a representação simbólica de suas saídas ou componentes. Por exemplo, representar a abertura de uma porta com um LED ou utilizar palitos de picolé para representar catracas físicas.

2. **A proposta deve partir de um problema, e não de uma tecnologia.** Evitem escolher primeiro uma tecnologia ou componente e só depois procurar uma aplicação para ele. Por exemplo, é possível usar um Raspberry Pi para construir um cubo de LEDs, mas qual problema ele resolve?

3. **O projeto deverá justificar o uso do Raspberry Pi.** A utilização do Raspberry Pi deve ser necessária. Não serão consideradas adequadas propostas que possam ser implementadas utilizando apenas um microcontrolador.

4. **O escopo deverá ser compatível com a duração do semestre.** É preferível desenvolver uma solução menor, porém completa e funcional, do que propor um sistema abrangente que não possa ser concluído adequadamente.

5. **O custo do projeto deverá ser considerado desde a definição da proposta.** Caso ele tenha um custo elevado, recomenda-se modificar a proposta, por meio da substituição de componentes, da redução do escopo ou da alteração da solução técnica.

A proposta deve, portanto, partir de um **problema concreto**, definir uma **solução com escopo bem delimitado** e, somente então, selecionar as tecnologias e componentes necessários para sua implementação.

## Ementa

- Introdução aos sistemas embarcados
- Introdução aos sistemas operacionais Linux
- Recursos do sistema operacional
- Desenvolvimento para sistemas embarcados
- Subsistema de I/Os.
- Introdução ao RTOS
- Introdução aos LKM e aos device drivers

## Programa

- Introdução aos sistemas embarcados
- Introdução aos sistemas operacionais Linux
	- Obtendo informações do sistema
	- Principais comandos
	- Estrutura de diretórios
	- Instalação padrão de programas
- Recursos do sistema operacional
	- Processos, sinais e threads
	- Comunicação e sincronismo entre processos
	- Fila de mensagens
	- Programação para redes (sockets)
	- Alarmes
	- MUTEX
	- Semáforos
	- Variáveis condicionais
- Desenvolvimento para sistemas embarcados
	- Conceito de cross-platform
	- Componentes e suas funções (host, target, interface de comunicação, etc)
	- Processo de geração de imagens
	- Utilização de makefiles
	- Inicialização em Sistemas Embarcados
	- Ferramentas para o Target System
	- Transferência de imagens
	- Cenários de boot do target
	- Seqüência de inicialização do target
- Subsistema de I/Os.
	- Conceito básico de I/Os
	- O subsistema de I/Os
	- Modo de transferência serial e em blocos
	- Funções de um subsistema de I/O
- Introdução ao RTOS
	- Características dos sistemas RT
	- Conceitos de Hard Real-Time e Soft Real-Time
	- Conceito de latência e Jitter
- Introdução aos LKM e aos device drivers
	- Desenvolvimento de um módulo do kernel
	- Comandos do modutils
	- Conceitos básicos sobre device driver
	- Estrutura de um device driver
	- Funções de um device driver
	- Instalação e carregamento de um device driver

## Bibliografia

### Básica: 
1. Doug Abbott, Embedded Technology: Linux for Embedded and Real-Time Applications, 2nd Ed., Newnes, USA, 2006. 
2. Mark Mitchell, Jeffrey Oldham e Alex Samuel, Advanced Linux Programming, New Riders, USA, 2001. 
3. Christopher Hallinan, Embedded Linux Primer: A Practical Real-World Approach, Prentice Hall, USA, 2006. 
4. Qing Li e Caroline Yao, Real-Time Concepts for Embedded Systems, CMP, USA, 2003. 

### Complementar: 
1. Rajaram Regupathy, Bootstrap Yourself with Linux-USB Stack : Design, Develop, Debug, and Validate Embedded USB, Course Technology, USA, 2011. 
2. Daniel Bovet e Marco Cesati, Understanding the Linux Kernel, 3rd Ed., O'Reilly, USA, 2005. 
3. Jonathan Corbet, Alessandro Rubini e Greg Kroah-Hartman, Linux Device Drivers, 3rd Ed., O'Reilly, USA, 2005. 
4. Karim Yaghmour, Jon Masters e Gilad Ben-Yossef, Building Embedded Linux Systems, 3rd Ed., O'Reilly, USA, 2003.
