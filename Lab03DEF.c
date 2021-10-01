#include<stdio.h>
#include<stdlib.h>
 
struct list{    // 90 pontos nesse
    int valID; 
    int qtd;
    float lucro; 
    int qtdVenda; 
    struct list *prox; 
};

typedef struct list list;
 
typedef struct{
    list *primeiro; 
    list *ultimo;  
    list *penultimo; 
    int tam; 
} no; 
 
void iniciaLista (no *lista){   
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->penultimo = NULL;
    lista->tam = 0;
}
 
int inserirLista (no *lista, int id, int qtd, int lucro, int escolha){   
    if (lista->tam != 0) lista->penultimo = lista->ultimo; 
    list *novo;
    novo = malloc(sizeof(list));
    novo->valID = id;
    novo->qtd = qtd; 
    novo->lucro = lucro; 
    novo->qtdVenda = 0;
    if (lista->tam == 0) {
        novo -> prox = NULL; 
        lista -> primeiro = novo; 
        lista -> ultimo = novo; 
        lista -> tam++; 
    } else{
        if (escolha != -1){
            novo->prox = NULL; 
            lista->ultimo->prox = novo; 
            lista->ultimo = novo; 
            lista->tam++; 
        }
    }
}
 
int procurarProd (no *lista, int id){
    list *ini = lista->primeiro;
    for (;ini != NULL; ini = ini->prox){
        if (ini->valID == id){
            return -1;
            break;  
        }
    }
    return 1;
}
 
int excluirLista (no *lista, int id){
    list *aux = NULL; 
    list *anterior = NULL;
    list *ciclo = lista->primeiro;
    if (lista->primeiro->valID == id){
        anterior = lista->primeiro; 
        lista->primeiro = lista->primeiro->prox; 
        free(anterior); 
    } else{
        while (ciclo->valID != id){
            anterior = ciclo; 
            ciclo = ciclo->prox; 
        }
        if (anterior->prox == lista->ultimo){
            aux = lista->ultimo; 
            lista->ultimo = anterior; 
            free(aux); 
            anterior->prox = NULL;
        } else{
            aux = anterior->prox; 
            anterior->prox = aux->prox; 
            free(aux); 
        }
    }
}
 
void localInsercao (no *lista, int lucro){
    list *ini = lista->primeiro; 
    list *anterior = NULL;
    list *aux = NULL; 
    list *cont = NULL;
    while (ini != NULL){
        if (ini->lucro == lista->ultimo->lucro || ini->lucro < lista->ultimo->lucro){     
            if (ini == lista->primeiro || lista->primeiro->lucro == lista->ultimo->lucro){
                if (lista->tam == 2){
                    aux = lista->primeiro; 
                    cont = lista->ultimo;
                    cont->prox = lista->primeiro;
                    lista->primeiro = lista->ultimo;
                    lista->ultimo = aux; 
                    aux -> prox = NULL;
                    break; 
                }                          
                aux = lista->primeiro;
                cont = lista->ultimo;
                cont->prox = aux; 
                lista->primeiro = lista->ultimo; 
                lista->ultimo = lista->penultimo; 
                lista->penultimo->prox = NULL; 
                break; 
            } else{
                if (lista->penultimo->lucro > lista->ultimo->lucro) break;   
                else{
                    aux = anterior;
                    cont = lista->ultimo;
                    cont->prox = aux->prox; 
                    anterior->prox = lista->penultimo->prox; 
                    lista->ultimo = lista->penultimo; 
                    lista->penultimo->prox = NULL; 
                    break; 
                }
            }
        }
        anterior = ini; 
        ini = ini->prox; 
    }
    
}
 
int vendaProd (no *lista, int id, int qtd){
    list *ini; 
    for (ini = lista->primeiro; ini != NULL; ini = ini->prox){
        if(ini->valID == id){   
            if(ini->qtd == 0){
                printf("nao existe\n"); 
                break; 
            }
            ini->qtd--;
            ini->qtdVenda++;
            break; 
        }
    }
}
 
void novoProd (no *lista, int qtd, int id){
    list *ini; 
    for (ini = lista->primeiro; ini != NULL; ini = ini->prox){
        if (ini->valID == id){
            ini->qtd += qtd; 
            break; 
        }
    }
}
 
void resultado (no *lista){
    list *ini; 
    float lucrotot; 
    for(ini = lista->primeiro; ini != NULL; ini = ini->prox){
        lucrotot = 0; 
        lucrotot = ini->lucro * ini->qtdVenda; 
        printf("%d %f\n", ini->valID, lucrotot); 
 
    }
}

int main(){

    no lista;
    iniciaLista(&lista);
    int qtdMov, i, opc, id, qtd, lucro, novo, lucrotot=0, escolha=0; 
    scanf("%d", &qtdMov);
    for (i=0; i<qtdMov; i++){
        scanf("%d %d", &opc, & id);
        escolha = procurarProd(&lista, id); 
        if (opc == 1){
            scanf("%d %d", &qtd, &lucro); 
            inserirLista(&lista, id, qtd, lucro, escolha);
            if (i != 0) localInsercao(&lista, lucro); 
            if (escolha == -1) printf("ja existe\n");
        }
        if (opc == 2){
            scanf("%d", &novo); 
            if (escolha != 1) novoProd(&lista, novo, id);
            else printf("nao existe\n");
        }
        if (opc == 3){
            if(escolha != 1) vendaProd(&lista, id, qtd); 
            else printf("nao existe\n");
        }
        if (opc == 4){   
            if (escolha != 1) excluirLista(&lista, id); 
            else printf("nao existe\n");
        }
    }
    resultado(&lista); 
    
    return 0;
}