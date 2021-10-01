#include <stdio.h>
#include <stdlib.h>

struct no{
    int num;        
    struct no *esquerda;    // 100 pontos - okk
    struct no *direita;
};

typedef struct no No;

struct arvBin{
    No *raiz;
};

typedef struct arvBin arvBin;

No* inserirElem(No *raiz, int val){
    if (raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->num = val;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    } else{
        if(val < raiz->num){
            raiz->esquerda = inserirElem(raiz->esquerda, val);
        } else if(val > raiz->num){
            raiz->direita = inserirElem(raiz->direita, val);  
        }
        return raiz;
    }
}

int buscarElem(No *raiz, int val){
    if (raiz == NULL){
        printf("N\n");
        return 0;
    } else{
        if (raiz->num == val){
            printf("S\n");
            return 1;
        } else{
            if (val < raiz->num){
                return buscarElem(raiz->esquerda, val);
            } else{
                return buscarElem(raiz->direita, val);
            }
        }
    }
}

No* removerElem(No *raiz, int val) {
    if (raiz == NULL){
        return NULL;
    } else{
        if (raiz->num == val){
            if ((raiz->esquerda == NULL) && (raiz->direita == NULL)){
                free(raiz);
                return NULL;
            } else{
                if ((raiz->esquerda == NULL) || (raiz->direita == NULL)){
                    No *aux;
                    if (raiz->esquerda != NULL){
                        aux = raiz->esquerda;
                    } else{
                        aux = raiz->direita;
                    }
                    free(raiz);
                    return aux;
                } else{
                    No *aux = raiz->esquerda;
                    while (aux->direita != NULL){
                        aux = aux->direita;
                    }
                    raiz->num = aux->num;
                    aux->num = val;
                    raiz->esquerda = removerElem(raiz->esquerda, val);
                    return raiz;
                }
            }
        } else{
            if(val < raiz->num){
                raiz->esquerda = removerElem(raiz->esquerda, val);
            } else raiz->direita = removerElem(raiz->direita, val);
            return raiz;
        }
    }
}

void imprimir(No *raiz){  
    if(raiz != NULL){
        imprimir(raiz->esquerda);
        printf("%d ", raiz->num);
        imprimir(raiz->direita);
    }
}

int main(){

    arvBin arv;
    arv.raiz = NULL;
    No *raiz = NULL;
    int num, qtdMov=0, i=1;
    char opc;
    scanf("%d", &qtdMov);
    while (qtdMov >= i){
        scanf("%c %d", &opc, &num);
        switch(opc){
            case 'I':
                raiz = inserirElem(raiz, num);
                i++;
                break;
            case 'B':
                buscarElem(raiz, num);
                i++;
                break;
            case 'R':
                raiz = removerElem(raiz, num);
                i++;
                break;
            case 'M':
                imprimir(raiz);
                printf("\n");
                i++;
                break;
        }
        
    }
    return 0;
}