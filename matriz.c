#include <stdlib.h>
#include "matriz.h"
#include "automato.h"

//Funcao para alocar o nó
Node *alocaNo(){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->right = NULL;
    newNode->down = NULL;

    return newNode;
}

//Funcao para alocar o reticulado
MatrizEsp* alocaReticulado(int tam){
    MatrizEsp *matriz = (MatrizEsp*)malloc(sizeof(MatrizEsp));
    matriz->cabecaCol = (Node*)malloc(sizeof(Node));
    matriz->cabecaLin = (Node*)malloc(sizeof(Node));
    matriz->tam = tam;
    Node *aux = matriz->cabecaCol;
    Node *aux2 = matriz->cabecaLin;
    for (int i = 0; i < matriz->tam; i++)
    {
        //Aloca cabeca de coluna e da seu indice.
        aux->right = alocaNo();
        aux->right->col = i;
        aux->right->lin = -1;

        //Aloca cabeca de linha e da seu indice.
        aux2->down = alocaNo();
        aux2->down->col = -1;
        aux2->down->lin = i;

        //Andando para adicionar proxima cabeca.
        aux = aux->right;
        aux2 = aux2->down;
    }
    
    return matriz;
}

//Funcao para desalocar o reticulado
void desalocarReticulado(MatrizEsp* matriz){
    Node *aux = matriz->cabecaCol->right;
    Node *aux2 = matriz->cabecaLin;
    Node *aux3;
    Node *aux4;
    //Node *aux4;
    aux3 = aux;
    //Desalocando as cabecas da coluna e o reticulado
    while (aux->right != NULL)
    {
        aux4 = aux3->down;
        aux3 = aux4;
        free(aux4);
        if (aux3 == NULL)
        {
            aux = aux->right;
            aux3 = aux;
        }
        
    }
    //Desalocando as cabecas das linhas
    while(aux2->down != NULL){
        aux4 = aux2;
        aux2 = aux4->down;
        free(aux4);
    }
    free(matriz->cabecaCol);
}

//Funcao para copiar o reticulado para o reticulado auxiliar
void copiaMatriz(MatrizEsp* matriz,MatrizEsp* copia){
    for (int i = 0; i < matriz->tam; i++)
    {
        for (int j = 0; j < matriz->tam; j++)
        {   //Condicional para copiar só os nós vivos de uma determinada posicao
            if (pesquisaAutomato(matriz, i, j))
                adicionaNo(copia,i,j);
        }
    }
}

bool pesquisaAutomato(MatrizEsp* matriz , int lin, int col){

    //Pesquisa de Automato baseada em linha e coluna.
    Node *aux = matriz->cabecaLin;

    //While para chegar na cabeca da linha a ser analisada.  
    for (int i = 0; i <= lin; i++)
    {
        aux = aux->down;
    }
    
    //Compara indices dos automatos. Se encontrar, retorna true.
    //Recebendo primeiro automato da Matriz.
    while (aux != NULL)
    {
        if (aux->col == col)
        {
            return true; //Se retorna true, automato esta vivo. 
        }
        
        aux = aux->right;
    }
    
    
    return false; //Se retorna true automato esta morto.
}