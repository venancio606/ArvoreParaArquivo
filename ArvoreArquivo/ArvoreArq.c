#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct fila;
typedef struct nodo Nodo;

typedef struct fila {
    Nodo *inicio;
} Fila;

struct nodo{
    char nome [50];
    int tipo;               // 0 = Arquivo, 1 = Pasta
    Nodo *pai;              // Ponteiro para subir de nivel (cd ..)
    Fila *arquivo;         // armazena dentro os arquivos
    Nodo *prox;
};

Fila * CriarFila(){
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f-> inicio = NULL;
    return f;
}

Nodo * CriarNodo(char nome[], int tipo, Nodo *pai){
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo)); 
    strcpy(novo->nome, nome);
    novo->tipo = tipo;
    novo->pai = pai;
    novo->arquivo = NULL;
    novo->prox = NULL;

    if (tipo ==1){          //se for pasta vai criar uma fila para guardar os qrquivos dentro
        novo->arquivo = CriarFila();
    }else{
        novo->arquivo = NULL;
    }
    return novo;
    
}
void OrdenarAntes(Fila *f, Nodo *novo){
    if (f->inicio == NULL || strcmp(novo->nome, f->inicio->nome) < 0){
        novo->prox = f->inicio;
        f->inicio = novo;
        return;
    }else{
        Nodo *atual = f->inicio;
        while (atual->prox != NULL && strcmp(novo->nome, atual->prox->nome) > 0){
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
}
/*void comando_ls 
O que faz: mostra todos os arquivos e pastas contidos na pasta corrente.
Exemplo: se a pasta temp contém os arquivos a.txt, www.html e run.exe, e também as pastas Boot e teste2, o
comando ls deve retornar os nomes dos arquivos e pastas em ordem alfabética, com um único registro por linha e, no
caso das pastas, com “-” ao final do nome, como demonstrado a seguir.
*/
void comando_ls(Nodo *pasta){
    if (pasta->arquivo == NULL){
        printf("A pasta %s esta vazia.\n", pasta->nome);
        return;
    }
    Nodo *atual = pasta->arquivo->inicio;
    while (atual != NULL){
        printf("%s", atual->nome);
        if (atual->tipo == 1){              // se for pasta, adiciona um - no final do nome
            printf("-");
        }
        printf("\n");
        atual = atual->prox;
    }
}

/*void comando_cd
Comando: cd <pasta>
O que faz: altera a pasta corrente entrando em um subpasta ou acessando a pasta do nível hierárquico superior
(caso exista).
Exemplo: cd .. acessa a pasta que contém a pasta corrente (caso exista)
cd teste2 acessa a pasta teste2 que está dentro da pasta corrente (caso exista).
*/


/* void comando_ma
Comando: ma <nome do arquivo>
O que faz: cria um arquivo (nó terminal) dentro da pasta corrente.
Exemplo: ma quest.txt cria o arquivo quest.txt na pasta corrente.*/




/* void comando_mp
Comando: mp <nome da pasta>
O que faz: cria uma pasta vazia dentro da pasta corrente.
Exemplo: mp backup cria a pasta backup como subpasta da pasta corrente.*/



/* void comando_rm
Comando: rm <arquivo ou pasta>
O que faz: apaga um arquivo ou pasta que está na pasta corrente. No caso de uma pasta, apaga todo o seu
conteúdo também.
Exemplo: rm temp apaga a pasta temp e todo o seu conteúdo (caso exista a pasta temp dentro
da pasta corrente).*/


/* void comando_ex
Comando: ex
O que faz: encerra a execução do programa exibindo a mensagem “sistema encerrado”. É utilizado como critério
de parada para o laço de leitura e execução dos comandos do simulador de gerenciador de arquivos.*/


