#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

//Funcao para ler o reticulado
void adicionaNo(MatrizEsp* matriz, int lin, int col) {
    Node* newNode = alocaNo();
    Node *aux = matriz->cabecaCol;
    Node *aux2 = matriz->cabecaLin;
    newNode->lin = lin;
    newNode->col = col;

    //Vai até a cabeça da coluna correta
    for (int i = 0; i <= col; i++) {
        aux = aux->right;
    }
    //Vai até a cabeça da linha correta
    for (int i = 0; i <= lin; i++) {
        aux2 = aux2->down;
    }

    //Inserção na lista de colunas (down)
    Node *atual = aux->down;
    Node *prev = aux; //Começa pela cabeça da coluna

    while (atual != NULL && atual->lin < lin) {
        prev = atual;
        atual = atual->down;
    }
    //Insere o novo nó na posição correta na coluna
    prev->down = newNode;
    newNode->down = atual;

    //Inserção na lista de linhas (right)
    atual = aux2->right;
    prev = aux2; //Começa pela cabeça da linha

    while (atual != NULL && atual->col < col) {
        prev = atual;
        atual = atual->right;
    }
    //Insere o novo nó na posição correta na linha
    prev->right = newNode;
    newNode->right = atual;
}

//Funcao para imprimir o reticulado, se achar o nó na posicao passada ele imprime 1, senao imprime 0
void imprimeReticulado(MatrizEsp* matriz){
    for (int i = 0; i < matriz->tam; i++)
    {
        printf("\n");
        for (int j = 0; j < matriz->tam; j++)
        {
            if (pesquisaAutomato(matriz, i, j))
                printf("1 ");

            else
                printf("0 "); 
        }
        
    }
}


MatrizEsp* evoluirReticulado(MatrizEsp* matriz, MatrizEsp* matrizAux,int tam,int gen){ //Complexidade da funcao: O(n²)
      //Variavel para armazenar o valor das celulas ao redor da celula que está sendo verificada
    int verifica;

    //Decrementacao feita para evitar uma evolucao a mais
    gen--;

    //Desaloca e aloca o reticulado auxiliar novamente
    desalocarReticulado(matrizAux);
    matrizAux = alocaReticulado(tam);
    //lacos de repeticao para verificar quantas celulas vivas possuem ao redor da celula que está sendo verificada
    for (int j = 0; j < tam; j++)
        {
            for (int k = 0; k < tam; k++)
            {
                //00
                if(j==0 && k==0){
                    verifica = pesquisaAutomato(matriz, j, k+1) + pesquisaAutomato(matriz, j+1, k+1) + pesquisaAutomato(matriz, j+1, k);
                }
                //04
                else if(j==0 && k==tam-1){
                    verifica = pesquisaAutomato(matriz, j, k-1) + pesquisaAutomato(matriz, j+1, k-1) + pesquisaAutomato(matriz, j+1, k);
                }
                //44
                else if(j==tam-1 && k==tam-1){
                    verifica = pesquisaAutomato(matriz, j-1, k) + pesquisaAutomato(matriz, j-1, k-1) + pesquisaAutomato(matriz, j, k-1);
                }
                //40
                else if(j==tam-1 && k==0){
                    verifica = pesquisaAutomato(matriz, j-1, k) + pesquisaAutomato(matriz, j-1, k+1) + pesquisaAutomato(matriz, j, k+1);
                }
                //cima
                else if(j==0 && k>0 && k<tam-1){
                    verifica = pesquisaAutomato(matriz, j, k-1) + pesquisaAutomato(matriz, j+1, k-1) + pesquisaAutomato(matriz, j+1, k) +
                    pesquisaAutomato(matriz, j+1, k+1) + pesquisaAutomato(matriz, j, k+1);
                }
                //direita
                else if(k==tam-1 && j>0 && j<tam-1){
                    verifica = pesquisaAutomato(matriz, j-1, k-1) + pesquisaAutomato(matriz, j-1, k) +  pesquisaAutomato(matriz, j+1, k) +
                    pesquisaAutomato(matriz, j+1, k-1) + pesquisaAutomato(matriz, j, k-1);
                }
                //baixo
                else if(j==tam-1 && k>0 && k<tam-1){
                    verifica = pesquisaAutomato(matriz, j-1, k-1) + pesquisaAutomato(matriz, j-1, k) + pesquisaAutomato(matriz, j-1, k+1) +
                    pesquisaAutomato(matriz, j, k+1) +  pesquisaAutomato(matriz, j, k-1);
                }
                //esquerda
                else if(k==0 && j>0 && j<tam-1){
                    verifica = pesquisaAutomato(matriz, j-1, k) + pesquisaAutomato(matriz, j-1, k+1) + pesquisaAutomato(matriz, j, k+1) +  
                    pesquisaAutomato(matriz, j+1, k+1) + pesquisaAutomato(matriz, j+1, k);
                }
                
                else{
                    verifica = pesquisaAutomato(matriz, j-1, k-1) + pesquisaAutomato(matriz, j-1, k) + pesquisaAutomato(matriz, j-1, k+1)
                    + pesquisaAutomato(matriz, j, k+1) + pesquisaAutomato(matriz, j+1, k+1) + pesquisaAutomato(matriz, j+1, k) + pesquisaAutomato(matriz, j+1, k-1) + pesquisaAutomato(matriz, j, k-1);
                }
                
                //Sequencia de condicionais para validar as regras

                //regra para se manter viva
                if(verifica>1 && verifica<4 && pesquisaAutomato(matriz,j,k))
                    adicionaNo(matrizAux,j,k);
                //regra para uma célula morta renascer
                else if(verifica==3 && !pesquisaAutomato(matrizAux,j,k))
                    adicionaNo(matrizAux,j,k);
                //caso nenhuma regra se aplique a célula continua morta
                }
                
            }
            //Passando os valores recebidos pela matriz auxiliar na verificacao para a matriz do reticulado
            desalocarReticulado(matriz);
            matriz = alocaReticulado(tam);
            copiaMatriz(matrizAux,matriz);
            
            //Chamada recursiva
            if(gen>0){
                matriz = evoluirReticulado(matriz,matrizAux,tam, gen--);
            }
            
            return matriz;
}