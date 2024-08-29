#ifndef AUTOMATO_H
#define AUTOMATO_H
#include "matriz.h"

void adicionaNo(MatrizEsp*,int, int);
MatrizEsp* evoluirReticulado(MatrizEsp*,MatrizEsp*,int,int);
void imprimeReticulado(MatrizEsp*);

#endif