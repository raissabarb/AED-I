#include<stdlib.h>
#include<stdio.h>
#define tam 10

struct no{
    int lista[tam];
    struct no *proximo;
};

typedef struct no no;

typedef struct{
    no *inicio;
    int tam;
}Lista;

void inserirLista(no **lista, int ra){
    no *novo, *aux = malloc(sizeof(no));
    if (novo){
        novo->lista[ra] = ra;
        if (*lista == NULL){
            novo->proximo = NULL;
            *lista = novo;
        } else if (novo->lista[ra] < (*lista)->lista[ra]){
            novo->proximo = *lista;
            *lista = novo;
        } else{
            aux = *lista;
            while(aux->proximo && novo->lista[ra] > aux->proximo->lista[ra]){
                aux = aux->proximo;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
    }
}

void imprimirLista(Lista *lista){
    no *inicio = l->inicio;
    while(inicio != NULL){
        printf("%d ", inicio->lista[inicio]);
    }
}

int main(){
    Lista lista;
    lista.inicio = NULL;
    lista.tam = 0;

    return 0;
}
