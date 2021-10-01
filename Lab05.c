#include <stdio.h>
#include <stdlib.h>

#define max 100

struct filaCirc{
	int elementos[max];
	int prim;
	int ult;
	int tamFila; 
};

typedef struct filaCirc controleFila;

controleFila *iniciaFila (){
    controleFila *fila = (controleFila*)malloc(sizeof(controleFila)); 
	fila->prim = 0;
	fila->ult = -1;
    fila->tamFila = 0;
    int i;
    for (i=0; i<max; i++){
        fila->elementos[i] = 0;
    }
}

void inserirTarefa (controleFila *fila, int id){
	if(fila->ult == max-1)
		fila->ult = -1;
    fila->ult++;
    fila->elementos[fila->ult] = id; 
    fila->tamFila++; 
}

int filaVazia (controleFila *fila){
	return (fila->tamFila == 0);
}

int removerTarefa (controleFila *fila){ 
	int cont;
    if (filaVazia(fila)){
        printf("vazia");
        printf("\n");
    } else{
        cont = fila->elementos[fila->prim++]; 
        cont = 0;
        if(fila->prim == max)
            fila->prim = 0;
        fila->tamFila--;  
    }
	return cont;
}

void concluirTarefa (controleFila *fila){
    int aux;
    if (filaVazia(fila)){
        printf("vazia");
        printf("\n");
    } else{
        aux = fila->elementos[fila->prim];
        removerTarefa(fila);
        inserirTarefa(fila, aux);
    }
}

int imprimir (controleFila *fila){
    int i=0;
    if (fila->tamFila == 0) return;
    for (i=fila->ult; i>fila->prim; i--){
        printf("%d ", fila->elementos[i]);
    }
    printf("%d\n", fila->elementos[fila->prim]);
    return 0;
}

int main() {

    controleFila* fila;
    fila = iniciaFila();
    int qtdOp, opcao, id, i=0;
    scanf("%d", &qtdOp);
    for (i=0; i<qtdOp; i++){
        scanf("%d", &opcao);
        if (opcao == 1){
            scanf("%d", &id);
            inserirTarefa(fila, id);
        } else if (opcao == 2){
            removerTarefa(fila);
        } else if (opcao == 3){
            concluirTarefa(fila);
        }
    }
    imprimir(fila);
    return 0;
}