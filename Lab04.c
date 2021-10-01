#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trocaNumeros{     // 50 pontos nesse
    int numero;
    int listaElimin;
    struct trocaNumeros *prox;
    struct trocaNumeros *ant;
};

typedef struct trocaNumeros tipoNum;

struct NO{
    tipoNum *prim;
    tipoNum *ult;
    int tamLista;
};

typedef struct NO no;

no* iniciaLista(){
    no *lista = malloc(sizeof(no));
    lista->prim = NULL;
    lista->ult = NULL;
    lista->tamLista = 0;
    return lista;
}

void insereFim(no *lista, int num){
    tipoNum *novo = (tipoNum*)malloc(sizeof(tipoNum));
    if (lista->tamLista == 0){
        novo->ant = NULL;
        novo->prox = NULL;
        lista->prim = novo;
        lista->ult = novo;
        novo->numero = num;
    } else{
        novo->prox = NULL;
        novo->ant = lista->ult;
        lista->ult->prox = novo;
        lista->ult = novo;
        novo->numero = num;
    }
    lista->tamLista++;
}

void insereListaElimin(no *lista, int num){
    tipoNum *novo = (tipoNum*)malloc(sizeof(tipoNum));
    if (lista->tamLista == 0){
        novo->ant = NULL;
        novo->prox = NULL;
        lista->prim = novo;
        lista->ult = novo;
        novo->listaElimin = num;
    } else{
        novo->prox = NULL;
        novo->ant = lista->ult;
        lista->ult->prox = novo;
        lista->ult = novo;
        novo->listaElimin = num;
    }
    lista->tamLista++;
}

void inserirNum(no* lista, int num, int pos){  
    tipoNum *novo = (tipoNum*)malloc(sizeof(tipoNum));
    tipoNum *no, *aux;
    int cont=0;
    if (0<=pos<=9 && 0<=num<=9){
        if (pos == 0){
            novo->numero = num;
            if (lista->prim == NULL){
                novo->prox = NULL;
                lista->prim = novo;
                lista->ult = novo;
            } else{
                novo->prox = lista->prim;
                lista->prim = novo;
            }
            lista->tamLista++;
        } else{
            no = lista->prim;
            novo->numero = num;
            while (cont < pos-1){
                no = no->prox;
                cont++;
            }
            aux = no->prox;
            no->prox = novo;
            novo->prox = aux;
            lista->tamLista++;
        }
    }
}

int eliminarElemento(no* lista, int pos){    
    int i;
    tipoNum *aux = lista->prim;
    tipoNum *atual = lista->prim;
    if (pos == 0){  
        aux = lista->prim;
        lista->prim = lista->prim->prox;
        if (lista->prim == NULL){
            lista->ult = NULL;
        } else{
            lista->prim->ant == NULL;
        }
    } else if (pos == lista->tamLista-1){   
        aux = lista->ult;
        lista->ult->ant->prox = NULL;
        lista->ult = lista->ult->ant;
    } else {
        for (i=0; i<pos; i++){
            atual = atual->prox;
        }
        aux = atual;
        atual->ant->prox = atual->prox;
        atual->prox->ant = atual->ant;
    }
    free(aux);
    lista->tamLista--;
    return 0;
}

int imprimeLista(no *lista){    
    tipoNum *aux = lista->prim, *auxfim = lista->ult;
    if (lista->tamLista == 0){ 
        return;
    } else{
        for (aux; aux->prox!=NULL; aux=aux->prox){   
            printf("%d ", aux->numero);
        }
        printf("%d\n", auxfim->numero);
        return 0;
    }
}

int contagemEliminacao(no* lista){
    tipoNum *aux = lista->prim;
    int n1=0, n2=0, n3=0, soma, cont=0, i=0, ultimo;
    for (aux; aux!=NULL; aux=aux->prox){
        if (lista->tamLista == 3){
            n1 = lista->prim->numero;
            n2 = lista->prim->prox->numero;
            n3 = lista->prim->prox->prox->numero;
            soma = n1 + n2 + n3; 
            if (soma == 10){
                eliminarElemento(lista, 0);
                eliminarElemento(lista, 0);
                eliminarElemento(lista, 0);
            }
            return;
        } 
        if ((aux->prox == NULL) && (lista->tamLista < 3)) return;
        if (aux->prox == NULL){
            n1 = lista->prim->numero;
            n2 = lista->prim->prox->numero;
            n3 = lista->ult->numero;
            soma = n1 + n2 + n3; 
            if (soma == 10){
                int ultimo;
                ultimo = lista->tamLista-1;
                eliminarElemento(lista, ultimo);  
                eliminarElemento(lista, 0);
                eliminarElemento(lista, 0);
                cont = -2;
            }
        } else if ((aux->prox != NULL) && (aux->prox->prox != NULL)){
            n1 = aux->numero;
            n2 = aux->prox->numero;
            n3 = aux->prox->prox->numero;
            soma = n1 + n2 + n3;
            if (soma == 10){  
                eliminarElemento(lista, cont);
                eliminarElemento(lista, cont);
                eliminarElemento(lista, cont);
                cont = -2;
            }
        } else if ((aux->prox->prox == NULL) && (lista->tamLista < 3)){
            return; 
        } else if (aux->prox->prox == NULL){
            n1 = lista->prim->numero;
            n2 = lista->ult->ant->numero;
            n3 = lista->ult->numero;
            soma = n1 + n2 + n3;
            if (soma == 10){
                int ultimo;
                ultimo = lista->tamLista-1;
                eliminarElemento(lista, ultimo-1); 
                eliminarElemento(lista, ultimo-1);  
                eliminarElemento(lista, 0);
                cont = -2;
            }
        }
        cont++;
    }
    return 0;
}

void resultadoFinal(no *lista){
    if (lista->tamLista == 0){
        printf("ganhou");
    } else{
        printf("perdeu");
    }
}

int main(){

    no* no;
    no = iniciaLista();
    int n, i, posTroca, numAdd, cont=0;
    for (i=0; i<10; i++){
    	scanf("%d", &n);
        if (0<=n<=9){   
            insereFim(no, n);
        } // else break;
    }
    imprimeLista(no);
    while (cont < 5){
        scanf("%d %d", &numAdd, &posTroca);
        if ((numAdd == 0) || (numAdd < 0) || (numAdd > 9)){
            cont = cont;
        } else if (1<=numAdd<=9){
            inserirNum(no, numAdd, posTroca);
            contagemEliminacao(no);
            imprimeLista(no);
            if (no->tamLista == 0){
                resultadoFinal(no);
                return 0;
            } else cont++;
        }
    }
    resultadoFinal(no);

    return 0;
}
