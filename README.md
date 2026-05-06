# ArvoreParaArquivo

## Ideia

O projeto é um trabalho proposto pelo professor para a matéria Algorítmos e Estrutura de Dados 3, focado na fixação do conteúdeo de árvores

## Sobre o código

O código deve simular um sistema gerenciador de arquivos em terminal utilizando estrutura de dados do tipo árvore. O sistema
tem os seguintes RF (**Requisitos Funcionais**):

### - Mostrar caminho da pasta corrente
O caminho corrente deve ser exibido antes de inserir qualquer comando.
Exemplo:
Se a pasta raiz for a pasta corrente, mostrar apenas 

```bash
->
```

Se a pasta corrente for teste2 que é subpasta da pasta temp que por sua vez está dentro da pasta raiz, o caminho
a ser exibido será 

```bash
-temp-teste2->
```

### - Mostrar o conteúdo de uma pasta
Comando: 
```bash
ls
```

O que faz: mostra todos os arquivos e pastas contidos na pasta corrente.
Exemplo: se a pasta temp contém os arquivos a.txt, www.html e run.exe, e também as pastas Boot e teste2, o
comando **ls** deve retornar os nomes dos arquivos e pastas em ordem alfabética, com um único registro por linha e, no
caso das pastas, com “**-**” ao final do nome, como demonstrado a seguir.
```bash
a.txt
Bootrun.exe
teste2-
www.html
```

### - Criar arquivo dentro da pasta corrente
Comando: ma <nome do arquivo>
O que faz: cria um arquivo (**nó terminal**) dentro da pasta corrente.
Exemplo:
```bash
ma quest.txt
```
cria o arquivo quest.txt na pasta corrente.

### - Criar pasta dentro da pasta corrente
Comando: 
```bash
mp <nome da pasta>
```

O que faz: cria uma pasta vazia dentro da pasta corrente.
Exemplo: 
```bash
mp 
```
backup cria a pasta backup como subpasta da pasta corrente.

### - Navegar nas pastas do sistema
Comando: 
```bash
cd <pasta>
```
O que faz: altera a pasta corrente entrando em um subpasta ou acessando a pasta do nível hierárquico superior
(caso exista).
Exemplo: 
```bash
cd .. 
```
acessa a pasta que contém a pasta corrente (caso exista)
```bash
 cd teste2
 ```
acessa a pasta teste2 que está dentro da pasta corrente (caso exista).

### - Apagar arquivos ou pastas
Comando: 
```bash
rm <arquivo ou pasta>
```
O que faz: apaga um arquivo ou pasta que está na pasta corrente. No caso de uma pasta, apaga todo o seu
conteúdo também.
Exemplo: 
```bash
rm temp
```
apaga a pasta temp e todo o seu conteúdo (caso exista a pasta temp dentro
da pasta corrente)

### - Encerrar a execução do programa
Comando: 
```bash
ex
```
O que faz: encerra a execução do programa exibindo a mensagem “sistema encerrado”. É utilizado como critério
de parada para o laço de leitura e execução dos comandos do simulador de gerenciador de arquivos.

## Observações
- Quando não for possível executar algum comando, como no caso de utilizar um comando de forma equivocada,
com grafia incorreta, tentando acessar ou apagar arquivos ou pastas inexistentes, exibir a mensagem “comando
invalido”;
- Não existem limites de profundidade da árvore de diretórios ou no número de arquivos e pastas contidos em
qualquer pasta;
- Armazenar arquivos e pastas em ordem lexicográfica dentro da pasta que os contém;
- Após executar qualquer comando, exibir qualquer mensagem ou informação, proceder com uma quebra de linha.
- Não foi utilizado IA na criação dos códigos

## Integrantes
- Nícolas oliveira dos Santos
- Raphael de Almeida Cruz
- João Venâncio de Gonçalves Ribeiro Taques
