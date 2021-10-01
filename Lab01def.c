#include <stdio.h>
#include <string.h>

#define maxReservas 10
#define L 100

struct reserva{
    int qtdReserva;
    int nRetirada;
    int nReserva;
    int tamLista;
    int lista[L];
};

typedef struct reserva res;

void iniciaLista(res *aux, int qtdLivros){
    int i;
    for(i=0; i<qtdLivros; i++){
        aux->lista[i] = 0;
    }
    aux->qtdReserva = 0;
    aux->tamLista = 0;
    aux->nRetirada = 0;
    aux->nReserva = 0;
}

int novaReserva(res *aux, int numLivro){
    int i;
    if (aux->qtdReserva >= maxReservas){
        printf("Lista de reserva cheia\n");
    } else{
        aux->qtdReserva++;
        aux->lista[aux->qtdReserva-1] = numLivro;
        printf("Sua reserva foi realizada\n");
        aux->nReserva++;
    }
    return 1;
}

void retirada(res *aux, int numLivro){
  int i, k, auxiliar = 1;
  for (i=0; i<aux->qtdReserva; i++){
    if (aux->lista[i] == numLivro){
      for (k=i; k<aux->qtdReserva; k++){
        aux->lista[k] = aux->lista[k+1];
      }
      printf("O livro foi retirado com sucesso\n");
      aux->nRetirada++;
      aux->nReserva--;
      auxiliar++;
    }
  }
  if (auxiliar == 1){
    printf("Você não possui reserva desse livro\n");
  }
}  

int main(){

    res *aux;
    int qtdReserva, i, escolha = 0, numLivro = 0;
    scanf("%d", &qtdReserva);
    iniciaLista(aux, qtdReserva);
    for (i=0; i<qtdReserva; i++){
        scanf("%d %d", &escolha, &numLivro);
        if (escolha == 1){
           novaReserva(aux, numLivro);  
        } else if (escolha == 2){
            retirada(aux, numLivro);
        }
    }
  printf("Você realizou %d reservas e %d retiradas\n", aux->nReserva, aux->nRetirada);
  return 0;
}