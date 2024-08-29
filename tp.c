//Eduardo Henrique Fernandes Marques - 23.2.4010 e Caua Guenrick Alves - 23.2.4002
#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

int main(){
    MatrizEsp *matriz;
    MatrizEsp *auxiliar;
    int gen,tam;
    scanf("%d",&tam);
    scanf("%d",&gen);
    int val;
    matriz = alocaReticulado(tam);
    auxiliar = alocaReticulado(matriz->tam);

    for (int i = 0; i < matriz->tam; i++)
    {
        for (int j = 0; j < matriz->tam; j++)
        {
            scanf("%d",&val);
            if(val == 1){
                adicionaNo(matriz, i, j);
            }
        }
    }
    copiaMatriz(matriz,auxiliar);
    printf("\n");
    matriz = evoluirReticulado(matriz,auxiliar,matriz->tam,gen);
    imprimeReticulado(matriz);

    desalocarReticulado(auxiliar);
    desalocarReticulado(matriz);
}