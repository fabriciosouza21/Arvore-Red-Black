#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct noh{
    int numero_arvore;
    char cor;
    struct noh *pai;
    struct noh *esquerda;
    struct noh *direita;
};

typedef struct noh nohVP;

// Prototipo das funções

nohVP* criaNovoNoh();
void rotacaoEsquerda(nohVP **Arvore_PV, nohVP *noh);
void rotacaoDireita(nohVP **Arvore_PV, nohVP *noh);
nohVP* inserir_Novo_Noh_PV(nohVP **Arvore_PV, nohVP *noh);
void inserirCorVP(nohVP **Arvore_PV, nohVP *noh);
void visitarEmOrdem(nohVP* Arvore_PV);
void mostraDadosNoh(nohVP* noh);
int menu();
nohVP* rotacaoDireitaEsquerda(nohVP* arvore);
nohVP* rotacaoEsquerdaDireita(nohVP*arvore);

nohVP *vazio = NULL;

int main(){
    nohVP *Arvore_PV = NULL;
    int opc;

    vazio = (nohVP*)malloc(sizeof(nohVP));
    vazio->pai = Arvore_PV;
    vazio->direita = vazio->esquerda = vazio;

    do{
        opc = menu();
        switch (opc){
        case 1:
            inserir_Novo_Noh_PV(&Arvore_PV, criaNovoNoh());
            break;
        case 2:
            printf("Listagem dos nohs da Arvore \n\n");
            if(Arvore_PV != NULL)
                visitarEmOrdem(Arvore_PV);
            else
                printf("Sem Elementos na Arvore \n");
            break;
            case 0:
                return 0;
                break;
        }
    }
    while (opc != 0);

    return 0;
}

// Rotação a Esquerda do Nó

void rotacaoEsquerda(nohVP **Arvore_PV, nohVP *noh){
    nohVP *y;

    if(((*Arvore_PV)->pai == vazio) && (noh->direita != vazio)){
        y = noh->direita;
        noh->direita = y->esquerda;
        y->esquerda->pai = noh;
        y->pai = noh->pai;

        if(noh->pai == vazio){
            *Arvore_PV = y;
        }
        else if(noh == noh->pai->esquerda){
            noh->pai->esquerda = y;
        }
        else{
            noh->pai->direita = y;
        }
    }
    y->esquerda = noh;
    noh->pai = y;
    (*Arvore_PV)->pai = vazio;
}

//Rotação a Direita do Nó

void rotacaoDireita(nohVP **Arvore_PV, nohVP *noh){
    nohVP *y;
    if(((*Arvore_PV)->pai == vazio) && (noh->esquerda != vazio)){
        y = noh->esquerda;
        noh->esquerda = y->direita;
        y->direita->pai = noh;
        y->pai = noh->pai;

        if(noh->pai == vazio){
            *Arvore_PV = y;
        }
        else if(noh == noh->pai->direita){
            noh->pai->direita = y;
        }
        else{
            noh->pai->esquerda = y;
        }
    }
    y->direita = noh;
    noh->pai = y;
    (*Arvore_PV)->pai = vazio;
}

//Insere na Arvore

nohVP* inserir_Novo_Noh_PV(nohVP **Arvore_PV, nohVP *noh){
    nohVP *y = vazio;
    nohVP *x = *Arvore_PV;
    if((*Arvore_PV)== NULL){
        *Arvore_PV = noh;
        (*Arvore_PV)->pai = vazio;
        vazio->pai = *Arvore_PV;
        (*Arvore_PV)->cor = 'P';
        return 0;
    }
    if((*Arvore_PV)->numero_arvore == noh->numero_arvore){
        printf(" Numero duplicado, Coloque outro numero !!\n\n");
        return 0;
    }
    while(x != vazio){
        y = x;
        if(noh->numero_arvore < x->numero_arvore){
            x = x->esquerda;
        }
        else{
            x = x->direita;
        }
    }
    noh->pai = y;
    if(noh->numero_arvore < y->numero_arvore){
        y->esquerda = noh;
    }
    else if(noh->numero_arvore > y->numero_arvore){
        y->direita = noh;
    }
    else if(noh->numero_arvore == y->numero_arvore){
        printf("Numeros iguais, Tente outro numero !!\n\n");
    }
    noh->esquerda = vazio;
    noh->direita = vazio;
    noh->cor = 'V';
    inserirCorVP(&(*Arvore_PV), noh);
    return noh;
}
// Insere a Cor do nó e faz o balaceamento caso precisar

void inserirCorVP(nohVP **Arvore_PV, nohVP *noh){
    nohVP *y;
    while(noh->pai->cor == 'V'){
        if(noh->pai == noh->pai->pai->esquerda){
            y = noh->pai->pai->direita;
            if(y->cor == 'V'){
                noh->pai->cor = 'P';
                y->cor = 'P';
                noh->pai->pai->cor = 'V';
                noh = noh->pai->pai;
            }
            else{
                if(noh == noh->pai->direita){
                    noh = noh->pai;
                    rotacaoEsquerda(&(*Arvore_PV), noh);
                }
                noh->pai->cor = 'P';
                noh->pai->pai->cor = 'V';
                rotacaoDireita(&(*Arvore_PV), noh->pai->pai);
            }
        }
        else{
            y = noh->pai->pai->esquerda;
            if(y->cor == 'V'){
                noh->pai->cor = 'P';
                y->cor = 'P';
                noh->pai->pai->cor = 'V';
                noh = noh->pai->pai;
            }
            else{
                if(noh == noh->pai->esquerda){
                    noh = noh->pai;
                    rotacaoDireita(&(*Arvore_PV), noh);
                }
                noh->pai->cor = 'P';
                noh->pai->pai->cor = 'V';
                rotacaoEsquerda(&(*Arvore_PV), noh->pai->pai);
            }
        }
    }
    (*Arvore_PV)->cor = 'P';
}

// Cria o no para a Arvore

nohVP* criaNovoNoh(){
    nohVP *novo;
    novo = (nohVP*)malloc(sizeof(nohVP));
    printf("Informe um numero para a Arvore...: ");
    scanf("%d", &novo->numero_arvore);
    if(novo->numero_arvore < 0){
        printf("Numero Invalido! Tente Novamente !!!\n");
        return criaNovoNoh();
    }
    novo->cor = 'V'; // todo novo noh Ã© vermelho
    novo->pai = vazio;
    novo->direita = vazio;
    novo->esquerda = vazio;
    return novo;
}

// Função de Listagem dos dados

void visitarEmOrdem(nohVP* Arvore_PV){
    if (Arvore_PV != vazio){
        mostraDadosNoh(Arvore_PV);
        visitarEmOrdem(Arvore_PV->esquerda);
        visitarEmOrdem(Arvore_PV->direita);
    }
}

// Mostra os dados da Arvore

void mostraDadosNoh(nohVP* noh){
    printf("Valor do noh.......................: %d\n", noh->numero_arvore);
    printf("Cor do noh.........................: %c\n\n", noh->cor);
    printf("\n\n");
}

int menu(){
    int opcao;
    printf("1 - Inserir Noh Na Arvore\n");
    printf("2 - Mostrar Arvore\n");
    printf("0 - Sair Do Programa \n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    return opcao;
}
