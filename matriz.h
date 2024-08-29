#ifndef MATRIZ_H
#define MATRIZ_H
#include<stdbool.h>


//Nó esqueleto para percorrer a matriz
typedef struct node{
    int lin;
    int col;
    struct node *right;
    struct node *down;
}Node;

//Matriz esqueleto com cabecas para percorrer a matriz
typedef struct{
    int tam;
    Node *cabecaCol;
    Node *cabecaLin;
}MatrizEsp;

MatrizEsp* alocaReticulado(int);
Node *alocaNo();
void desalocarReticulado(MatrizEsp*);
bool pesquisaAutomato(MatrizEsp*, int lin, int col);
void copiaMatriz(MatrizEsp*,MatrizEsp*);

#endif