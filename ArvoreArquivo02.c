#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct fila;                // é uma fila encadeada
typedef struct nodo Nodo;

typedef struct fila {
    Nodo *inicio;
} Fila;

struct nodo{
    char nome [50];
    int tipo;               // 0 = Arquivo, 1 = Pasta
    Nodo *pai;              // Ponteiro para subir de nivel
    Fila *arquivo;          // armazena dentro os arquivos
    Nodo *prox;             // próximo arquivo ou pasta dentro da pasta atual
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

    if (tipo ==1){               //se for pasta vai criar uma fila para guardar os qrquivos dentro
        novo->arquivo = CriarFila();
    }else{
        novo->arquivo = NULL;
    }
    return novo;
    
}

void copiarStr(char dest[], char orig[], int ini, int fim){
    int i=0, tam=strlen(orig);
    while(i+ini<tam && i<fim-ini && orig[i+ini] != '\0' && orig[i+ini] != '\n'){
        dest[i] = orig[i+ini];
        i++;
    }
    dest[i] = '\0';
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
    if (pasta == NULL || pasta->tipo != 1){
        printf("comando invalido\n");
        return;
    }

    Nodo *atual = pasta->arquivo->inicio;
    while (atual != NULL){
        printf("%s", atual->nome);
        if (atual->tipo == 1){                  // se for pasta, adiciona um - no final do nome
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
Nodo* comando_cd(Nodo *pasta, char nome[]){
        if (pasta == NULL || pasta->tipo != 1){
        printf("comando invalido\n");           
        return pasta; 
    }
    if (strcmp(nome, "..") == 0){             
        if (pasta->pai != NULL){
            return pasta->pai;
        }else{
            printf("comando invalido\n");
            return pasta;
        }
    }
    if(pasta->arquivo != NULL && pasta->arquivo->inicio != NULL){
        Nodo *atual = pasta->arquivo->inicio;
        while (atual != NULL){
            if (strcmp(atual->nome, nome) == 0){              
               if(atual->tipo == 1){
                    return atual;                        
                }else{
                    printf("comando invalido\n");  
                    return pasta;
                }
            }
            atual = atual->prox; 
    }
    printf("comando invalido\n");
    return pasta;
}}



/* void comando_ma
Comando: ma <nome do arquivo>
O que faz: cria um arquivo (nó terminal) dentro da pasta corrente.
Exemplo: ma quest.txt cria o arquivo quest.txt na pasta corrente.*/
void comando_ma(Nodo *pasta, char nome[]){
    if (pasta == NULL) {
        printf("comando invalido\n"); 
    }
    if (pasta->arquivo != NULL && pasta->arquivo->inicio != NULL) {
        Nodo *atual = pasta->arquivo->inicio;
        while (atual != NULL) {
            if (strcmp(atual->nome, nome) == 0) {
                printf("comando invalido\n");
                return;
            }
            atual = atual->prox;
        }
    }
    Nodo *novo = CriarNodo(nome, 0, pasta); // 0 = arquivo
    OrdenarAntes(pasta->arquivo, novo);
}





/* void comando_mp
Comando: mp <nome da pasta>
O que faz: cria uma pasta vazia dentro da pasta corrente.
Exemplo: mp backup cria a pasta backup como subpasta da pasta corrente.*/


void comando_mp(Nodo *pasta, char nome[]){
    if (pasta == NULL) {    
        printf("comando invalido\n");
        return;
    }
    if (pasta->arquivo != NULL && pasta->arquivo->inicio != NULL) {
        Nodo *atual = pasta->arquivo->inicio;
        while (atual != NULL) {
            if (strcmp(atual->nome, nome) == 0) {
                printf("comando invalido\n");
                return;
            }
            atual = atual->prox;
        }
    }
    Nodo *novo = CriarNodo(nome, 1, pasta); // 1 = pasta
    OrdenarAntes(pasta->arquivo, novo);
}


/* void comando_rm
Comando: rm <arquivo ou pasta>
O que faz: apaga um arquivo ou pasta que está na pasta corrente. No caso de uma pasta, apaga todo o seu
conteúdo também.
Exemplo: rm temp apaga a pasta temp e todo o seu conteúdo (caso exista a pasta temp dentro
da pasta corrente). */

void comando_rm(Nodo *pasta, char nome[]){                              // mais ou menos a funçao de desenfileirar 
    if (pasta == NULL || pasta->arquivo == NULL || pasta->arquivo->inicio == NULL) {
        printf("comando invalido\n");
        return;
    }

    Nodo *atual = pasta->arquivo->inicio;
    Nodo *anterior = NULL; 

    while (atual != NULL) {   //faz a busca
        if (strcmp(atual->nome, nome) == 0) {
            
            // tira o item da fila
            if (anterior == NULL) {
                pasta->arquivo->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            
            if (atual->tipo == 1 && atual->arquivo != NULL) {   // se for pasta, apaga tudo o que tem dentro dela antes de apagar 
                
                while (atual->arquivo->inicio != NULL) {
                    comando_rm(atual, atual->arquivo->inicio->nome);
                }
                
                free(atual->arquivo); 
            }
            
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("comando invalido\n"); // se nao achou = mensagem de erro
}

/* void comando_ex
Comando: ex
O que faz: encerra a execução do programa exibindo a mensagem “sistema encerrado”. É utilizado como critério
de parada para o laço de leitura e execução dos comandos do simulador de gerenciador de arquivos.*/
void comando_ex(){
    printf("sistema encerrado\n");
    exit(0);
}

/*O caminho corrente deve ser exibido antes de inserir qualquer comando.
Exemplo:
Se a pasta raiz for a pasta corrente, mostrar apenas “->”
Se a pasta corrente for teste2 que é subpasta da pasta temp que por sua vez está dentro da pasta raiz, o caminho
a ser exibido será “-temp-teste2->”*/

void mostrar_caminho(Nodo *atual) {   
  if (atual->pai == NULL) {
        return; 
    }
mostrar_caminho(atual->pai); //volta ate a raiz e printa o (-)

  printf("-%s", atual->nome);
}





int main() {
    Nodo *raiz = CriarNodo("raiz", 1, NULL); 
    Nodo *atual = raiz; 

    char str[100], cmd[3], par[50];

    do {
        mostrar_caminho(atual);
        printf("->");

        if (fgets(str, sizeof(str), stdin) != NULL) {
            str[strcspn(str, "\n")] = '\0';
            
            if (strlen(str) == 0) {
                continue;
            }

            copiarStr(cmd, str, 0, 2);
            par[0] = '\0';
            
            if (strlen(str) > 3) {
                copiarStr(par, str, 3, strlen(str));
            }

            if (strcmp(cmd, "ls") == 0) {
                comando_ls(atual);
            } else if (strcmp(cmd, "ma") == 0) {
                comando_ma(atual, par);
            } else if (strcmp(cmd, "mp") == 0) {
                comando_mp(atual, par);
            } else if (strcmp(cmd, "cd") == 0) {
                atual = comando_cd(atual, par);
            } else if (strcmp(cmd, "rm") == 0) {
                comando_rm(atual, par);
            } else if (strcmp(cmd, "ex") == 0) {
                comando_ex();
            } else {
                printf("comando invalido\n");
            }
        }

    } while(strcmp(cmd, "ex") != 0);

    return 0;
}
