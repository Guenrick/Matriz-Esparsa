//Caua Guenrick Alves 23.2.4002
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include <stdio_ext.h>

void imprimeCabecalhocol(int *qnumero, int tamanhocol, int **matcol, int numspc){
    int maiornum = matcol[0][0];
    int maiorq = qnumero[0];   
    // Verifica qual o maior valor da matriz para conferir se é maior que 10.
    for (int i = 0; i < tamanhocol; i++){ 
        for (int j = 0; j < qnumero[i]; j++){
            if(matcol[i][j] > maiornum)
            maiornum = matcol[i][j];  
        }
    }   
    
    // Verifica qual valor de qnumero e maior(o espacamento vai ser definido baseado nesse valor).
    for (int i = 1; i < tamanhocol; i++){
        if (qnumero[i] > maiorq)
            maiorq = qnumero[i];
    }

    // Para calcular os espacos.
    int *vdespc = malloc(tamanhocol * sizeof(int)), *vdespcaux = malloc(tamanhocol * sizeof(int)), test = -1;
    for (int i = 0; i < tamanhocol; i++){
        vdespc[i] = maiorq - qnumero[i];
        vdespcaux[i] = maiorq - qnumero[i];
    } 

    // Impressao do cabecalho.
    for (int i = 0; i < maiorq; i++){ 
        // Conta a quantidade de espacos necessaria.
        for (int i = 0; i < numspc; i++){
            printf(" ");
        }
        
        for (int j = 0; j < tamanhocol; j++){
            if(vdespc[j] > 0){
                vdespc[j]--;
                vdespcaux[j]--;
                printf("   ");
            }

            else if(test > j) {
                printf(" %-3d", matcol[j][vdespcaux[j]]);//tinha i ali. pensar sobre essa variaçao.
                vdespcaux[j]++;
                test = -1;
            }

            else if(matcol[j][vdespcaux[j]] >= 10) {
                printf("%d", matcol[j][vdespcaux[j]]);//tinha i ali. pensar sobre essa variaçao.
                vdespcaux[j]++;
                test = j + 100;
            }
            
            else{
                printf("%d  ", matcol[j][vdespcaux[j]]);
                vdespcaux[j]++;
            }
        }
        printf("\n");
    }

    for (int i = 0; i < numspc; i++){
        printf(" ");
    }

    for (int i = 0; i < tamanhocol; i++){
        printf("%c  ", 'A' + i);
    }
    printf("\n");
    free(vdespc);
    free(vdespcaux);
}

void imprimeCabecalholin(int *qnumero, int tamanholin, int **matlin, int maiorq, int maiornum, char **matc,int tamcol){   
    int qtespaco;
    for (int i = 0; i < tamanholin; i++){
        qtespaco = maiorq - qnumero[i];
        
        // Faz espaco especifico para quando o jogo tiver um valor maior do que 10.
        if(maiornum >= 10){
            for (int k = 0; k < 3*qtespaco; k++){
                printf(" ");
            }
            for (int j = 0; j < qnumero[i]; j++){
                printf("%2d ", matlin[i][j]);
            }
            printf(" %c ", 'A'+i);
            
            // Imprime a matriz do entrada.
            for (int l = 0; l < tamcol; l++){
                printf(" %c ", matc[i][l]);
            }
            printf("\n");
        }
        else{
            for (int k = 0; k < 2*qtespaco; k++){
                printf(" ");
            }
            for (int j = 0; j < qnumero[i]; j++){
                printf("%d ", matlin[i][j]);
            }
            printf(" %c ", 'A'+i);
            for (int l = 0; l < tamcol; l++){
                printf(" %c ", matc[i][l]);
            }
            printf("\n");
        }
    }
}

int valida(char arg[], int tamlin, int tamcol){
    // Verifica se há espacamento ou se só foi digitada uma letra.
    if (arg[1] == '\0' && arg[0] != '\n') {
        return 1;
    }

    // Converte letras minúsculas em maiúsculas.
    if (arg[0] >= 'a' && arg[0] <= 'z') {
        arg[0] = arg[0] - 'a' + 'A';
    }

    if (arg[1] >= 'a' && arg[1] <= 'z') {
        arg[1] = arg[1] - 'a' + 'A';
    }

    // Verifica se o usuário colocou mais de duas letras no argumento.
    if (arg[2] != '\0') {
        return 2;
    }

    // Verificando se foi adicionada alguma letra que não está presente no nonograma.
    char maiorlin = 'A' + tamlin, maiorcol = 'A' + tamcol;
    if (arg[0] >= maiorlin || arg[1] >= maiorcol) {
        return 3;
    }

    // Verificando se algum caractere inválido foi digitado.
    if (arg[0] < 'A' || arg[0] > 'Z' || arg[1] < 'A' || arg[1] > 'Z') {
        return 4;
    }

    return 0;
}

void printaValidacao(int val){
    // Verifica se ha espacamento ou se so foi digitada uma letra. COLOCAR PRA VERFICAR SE APERTOU ENTER DIRETO
    if (val == 1){
        printf("\nLetras insuficientes para o argumento, ou espacamento incorreto!\n");
    }
    
    // Verifica se o usuario colocou mais de duas letras no argumento.
    if (val == 2){
        printf("\nArgumento invalido! \nSo sao aceitas duas letras no argumento!\n");
    }   
    
    // Verificando se foi adicionada alguma letra que nao esta presente no nonograma.
    if (val == 3){
        printf("\nArgumento invalido!\nLetra ou sequencia de letras nao compativeis com o jogo!\n");
    }
    
    // Verificando se algum caractere invalido foi digitado.
    if(val == 4){
        printf("\nArgumento invalido!\nCaractere nao disponivel no jogo!\n");
    }

     if(val == 5){
        printf("\nA linha alcancou seu numero maximo! \n");
    }

     if(val == 6){
        printf("\nA coluna alcancou seu numero maximo! \n");
    }
}

void salvaNonograma(char nomearq[], int **lin, int **col, int tamlin, int tamcol, int *qtnumlin, int *qtnumcol, char **matc){
    FILE *salva = fopen(nomearq, "w");
    
    // Verifica se o arquivo foi aberto com sucesso
    if (salva == NULL){
        printf("\n\nFalha ao abrir o arquivo para salvar!\n");
        return;
    }

    // Salva linha e coluna.
    fprintf(salva,"%d %d ", tamlin, tamcol);
    fprintf(salva, "\n");   

    // Salva o cabecalho das linhas.
    for(int i = 0; i < tamlin; i++){
        fprintf(salva,"%d ", qtnumlin[i]);
        
        for (int j = 0; j < qtnumlin[i]; j++){           
            fprintf(salva, "%d ", lin[i][j]);
        }
        fprintf(salva, "\n");   
    }

    // Salva o cabecalho das colunas.
    for(int i = 0; i < tamcol; i++){
        fprintf(salva, "%d ",qtnumcol[i]);
    
        for (int j = 0; j < qtnumcol[i]; j++){
            fprintf(salva, "%d ", col[i][j]);
        }   
        fprintf(salva, "\n");   
    }

    // Salva a matriz de char editada pelo usuario.
    for (int i = 0; i < tamlin; i++){
        for (int j = 0; j < tamcol; j++){
            //__fpurge
            (stdin);
            fprintf(salva, "%c ", matc[i][j]);
        }
        fprintf(salva, "\n");   
    }   
    fclose(salva);
    printf("\n\nNonograma salvo com sucesso! ");
}

int regrasNonograma(int **lin, int **col, int linaces, int colaces, int tamlin, int tamcol, int *qtnumlin, int *qtnumcol, char **matc){
    int contaxlin = 0, contaxcol = 0, somalin = 0, somacol = 0;
    
    // Soma linha
    for (int j = 0; j < qtnumlin[linaces]; j++){
        somalin += lin[linaces][j];
    }
    
    // Conta se a linha ja alcancou seu numero maximo. 
    for (int i = 0; i < tamcol; i++){
        if (matc[linaces][i] == 'x'){
            contaxlin++;
        }
    
        if (contaxlin >= somalin){
            return 5;
        }    
    }
   
    
    // Soma Coluna
    for (int j = 0; j < qtnumcol[colaces]; j++){
        somacol += col[colaces][j];
    }
    
    // Conta se a coluna ja alcancou seu numero maximo. 
    for (int i = 0; i < tamlin; i++){
        if (matc[i][colaces] == 'x'){
            contaxcol++;
        }
    
        if (contaxcol >= somacol){
            return 6;
        }    
    }
    
    // Retorna 0 caso nenhuma regra tenha sido quebrada.
    return 0;
}

void verificaGanhou(int **lin, int **col, int tamlin, int tamcol, int *qtnumlin, int *qtnumcol, char **matc){
    int contaxlin, contaxcol, lincerta = 0, colcerta = 0, somalin = 0, somacol = 0;;
    
    // Verifica se as linhas estao corretas.
    for (int i = 0; i < tamlin; i++){
        contaxlin = 0;
        somalin = 0;
        for (int k = 0; k < qtnumlin[i]; k++){
                somalin += lin[i][k];
            }
        for (int j = 0; j < tamcol; j++){
            if(matc[i][j] == 'x'){
                contaxlin++;
            }
        }
        if (contaxlin == somalin){
            lincerta++;
        }
    }
    
    //Verifica se as colunas estao corretas.
    for (int i = 0; i < tamcol; i++){
        contaxcol = 0;
        somacol = 0;
        // Soma os valores maximos de marcacoes possiveis para cada coluns
        for (int k = 0; k < qtnumcol[i]; k++){
                somacol += col[i][k];
            }
        
        // Verifica se a quantidade de marcacoes estao corretas
        for (int j = 0; j < tamlin; j++){
            if(matc[j][i] == 'x'){
                contaxcol++;
            }
        }
        if (contaxcol == somacol){
            colcerta++;
        }
    }

    // Verifica se ganhou.
    if (lincerta == tamlin && colcerta == tamcol){
        printf("\n\nParabens, o jogo foi concluido com sucesso!\n\n");
    }
    
}

int main(int argc, char **argv){
    // Abrindo o arquivo.
    FILE *entrada = fopen(argv[1],"r");
    
    // Verifica se o arquivo foi aberto com sucesso.
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo");
        return 0;
    }

    // Armazena a entrada da matriz.
    int tamlin, tamcol;
    fscanf(entrada,"%d %d", &tamlin, &tamcol);
    
    int **lin, *qtnumlin; /* O qtnumlin e qtnumcol sao os numeros da primeira fileira do arquivo. 
    Sao usados para calculo de espacamento e alocacao de memoria. */
    
    qtnumlin = malloc(tamlin * sizeof(int));
    lin = malloc(tamlin * sizeof(int*));
    
    // Armazena os valores da matriz da linha (lin), juntamente com a quantidade de valores por linha(qtnumlin). 
    for(int i = 0; i < tamlin; i++){
        fscanf(entrada,"%d",&qtnumlin[i]);
        lin[i] = malloc(qtnumlin[i] * sizeof(int)); //???
        for (int j = 0; j < qtnumlin[i]; j++){           
            fscanf(entrada, "%d", &lin[i][j]);
        }   
    }        
    
    
    // Verifica qual valor de qtnumlin e maior(o espacamento vai ser definido baseado nesse valor).
    int maiorqlin = qtnumlin[0];
    for (int i = 0; i < tamlin; i++){
        if (qtnumlin[i] > maiorqlin)
            maiorqlin = qtnumlin[i];
    }
    
    
    // Verifica qual o maior valor da matriz para conferir se é maior que 10.
    int maiornum = lin[0][0], cont10 = 0;
    for (int i = 0; i < tamlin; i++){ 
        for (int j = 0; j < qtnumlin[i]; j++){
            if(lin[i][j] > maiornum)
                maiornum = lin[i][j];
            if(lin[i][j] >= 10)
                cont10++;  
        }
    }   
    
    // Descobrindo a quantidade de espacos (numspc) necessarios para as linhas.
    int numspc;
    if (cont10 > 0)
        numspc = (maiorqlin + 1)*3 + 1;
    else
        numspc = (maiorqlin*3 + 1)+ 1;

    // Armazena a matriz do cabecalho das colunas.
    int  *qtnumcol;
    int **col;
    
    qtnumcol = malloc(tamcol * sizeof(int));
    col = malloc(tamcol * sizeof(int*));
    
    for(int i = 0; i < tamcol; i++){
        fscanf(entrada, "%d",&qtnumcol[i]);
        col[i] = malloc(qtnumcol[i] * sizeof(int));
        for (int j = 0; j < qtnumcol[i]; j++){
            fscanf(entrada, "%d", &col[i][j]);
        }   
    }   
    
    // Armazena a matriz de caracteres (a que sera alterada pelo usuario).
    char **matc = malloc(tamlin * sizeof(char*)), rechar;
    for (int i = 0; i < tamlin; i++){
        matc[i] = malloc(tamcol * sizeof(char));
    }
    for (int i = 0; i < tamlin; i++){
        for (int j = 0; j < tamcol; j++){
            //__fpurge(stdin); // Limpa buffer.
            fscanf(entrada, " %c", &rechar);
            if(rechar == '\n' || rechar == ' '){
            j--;
            continue;
            }
            matc[i][j] = rechar;
        }
    }
    
    // Comecando o Jogo.
    printf("\nComandos e argumentos necessarios para jogar:\n");
    printf("\nComando   Argumento   Resultado");
    printf("\nx         AC          Preenche a célula da linha A e coluna C com um x.");
    printf("\n-         EC          Preenche a célula da linha E e coluna C com um -");
    printf("\n.         BA          Limpa a célula da linha B e coluna A.");
    printf("\nsalvar    out.txt     Salva o Nonograma tal como está no momento no arquivo out.txt");
    printf("\nsair                  Encerra o programa (sem salvar as últimas alterações).\n");
    printf("\nBem vindo ao Nonograma! \n\n"); 
    imprimeCabecalhocol(qtnumcol, tamcol, col, numspc);
    imprimeCabecalholin(qtnumlin, tamlin, lin, maiorqlin, maiornum, matc, tamcol);

    // Looping de comandos.    
    char comando[9], arg[4], nomearq[256], vernomearq[5]; 
    int val, posicaotxt, contanomearq = 0; // Variavel val serve para retornar o valor da validacao.
    int linaces, colaces;
    do{
        verificaGanhou(lin, col, tamlin, tamcol, qtnumlin, qtnumcol, matc);
        printf("\n\nDigite um comando: ");

        //__fpurge(stdin);
        fflush(stdin);
        scanf(" %8s", comando); 
        // Validando o comando.
        if(strcmp(comando,"x") != 0 && strcmp(comando,"X") != 0 && strcmp(comando,"-") != 0 && strcmp(comando,".") != 0 && 
            strcmp(comando,"salvar") != 0 && strcmp(comando,"sair") != 0){
            printf("\n\n");
            printf("\ec \e[3j");
            imprimeCabecalhocol(qtnumcol, tamcol, col, numspc);
            imprimeCabecalholin(qtnumlin, tamlin, lin, maiorqlin, maiornum, matc, tamcol);
            printf("\n\nComando invalido!\n");
            continue;
        }

        // Argumentos a serem digitados.
        // Substituindo por "x".
        if(strcmp(comando,"x") == 0 || strcmp(comando,"X") == 0){ 
            //__fpurge(stdin);
            scanf(" %3s", arg);
            printf("\n\n");

            // Validacao dos argumentos.
            val = valida(arg, tamlin, tamcol);
            
            if(val != 0){
                printf("\ec \e[3j");
                imprimeCabecalhocol(qtnumcol, tamcol, col, numspc);
                imprimeCabecalholin(qtnumlin, tamlin, lin, maiorqlin, maiornum, matc, tamcol);
                printaValidacao(val);
                continue;
            }

            // Avisa ao usuario que a area ja esta marcada.
            if (matc[arg[0] - 'A'][arg[1] - 'A'] == 'x'){
                printf("\ec \e[3j");
                imprimeCabecalhocol(qtnumcol, tamcol, col, numspc);
                imprimeCabecalholin(qtnumlin, tamlin, lin, maiorqlin, maiornum, matc, tamcol);
                printf("\n\nEsta celula ja esta marcada com x!\n\n");
                continue;
            }
            
            // Substitui a variavel normalmente caso nao tenha nenhum problema.
            else{
                // Verifica se esta infringindo alguma regra.
                linaces = arg[0] - 'A';
                colaces = arg[1] - 'A';
                val = regrasNonograma(lin, col, linaces, colaces, tamlin, tamcol, qtnumlin, qtnumcol, matc);
                if(val == 0){
                    printf("\ec \e[3j");
                    matc[linaces][colaces] = 'x';
                    imprimeCabecalhocol(qtnumcol, tamcol, col, numspc);
                    imprimeCabecalholin(qtnumlin, tamlin, lin, maiorqlin, maiornum, matc, tamcol);
                    continue;
                }
                else{
                    printf("\ec \e[3j");
                    imprimeCabecalhocol(qtnumcol, tamcol, col, numspc);
                    imprimeCabecalholin(qtnumlin, tamlin, lin, maiorqlin, maiornum, matc, tamcol);
                    printaValidacao(val); 
                    continue;
                }
            }
        }

        // Substituindo por "-".
        if(strcmp(comando,"-") == 0){
            //__fpurge(stdin);
            scanf(" %3s", arg);
            printf("\n\n");

            // Validacao dos argumentos.
            val = valida(arg, tamlin, tamcol);
            
            if(val != 0){
                printf("\ec \e[3j");
                imprimeCabecalhocol(qtnumcol, tamcol, col, numspc);
                imprimeCabecalholin(qtnumlin, tamlin, lin, maiorqlin, maiornum, matc, tamcol);
                printaValidacao(val);
                continue;
            }

            // Avisa ao usuario que a area ja esta marcada.
            if (matc[arg[0] - 'A'][arg[1] - 'A'] == '-'){
                printf("\ec \e[3j");
                imprimeCabecalhocol(qtnumcol, tamcol, col, numspc);
                imprimeCabecalholin(qtnumlin, tamlin, lin, maiorqlin, maiornum, matc, tamcol);
                printf("\n\nEsta celula ja esta marcada com -!\n\n");
                continue;
            }
            
            // Substitui a variavel normalmente caso nao tenha nenhum problema.
            else{
                printf("\ec \e[3j");    
                matc[arg[0] - 'A'][arg[1] - 'A'] = '-';
                imprimeCabecalhocol(qtnumcol, tamcol, col, numspc);
                imprimeCabecalholin(qtnumlin, tamlin, lin, maiorqlin, maiornum, matc, tamcol);
                continue;
            }
        }
        
        // Substituindo por ".".
        if(strcmp(comando,".") == 0){
            //__fpurge(stdin);
            scanf(" %3s", arg);
            printf("\n\n");

            // Validacao dos argumentos.
            val = valida(arg, tamlin, tamcol);

            if(val != 0){
                printf("\ec \e[3j");
                imprimeCabecalhocol(qtnumcol, tamcol, col, numspc);
                imprimeCabecalholin(qtnumlin, tamlin, lin, maiorqlin, maiornum, matc, tamcol);
                printaValidacao(val);
                continue;
            }

            // Avisa ao usuario que a area ja esta marcada.
            if (matc[arg[0] - 'A'][arg[1] - 'A'] == '.'){
                printf("\ec \e[3j");
                imprimeCabecalhocol(qtnumcol, tamcol, col, numspc);
                imprimeCabecalholin(qtnumlin, tamlin, lin, maiorqlin, maiornum, matc, tamcol);
                printf("\n\nEsta celula ja esta marcada com ponto!\n\n");
                continue;
            }
            
            // Substitui a variavel normalmente caso nao tenha nenhum problema.
            else{
            matc[arg[0] - 'A'][arg[1] - 'A'] = '.';
            printf("\ec \e[3j");
            imprimeCabecalhocol(qtnumcol, tamcol, col, numspc);
            imprimeCabecalholin(qtnumlin, tamlin, lin, maiorqlin, maiornum, matc, tamcol);
            continue;
            }
        }

        // Comando para salvar o jogo.
        if(strcmp(comando,"salvar") == 0){
            //__fpurge(stdin);
            scanf(" %s", nomearq);
            
            if (strlen(nomearq) > 254){
                printf("\n\nSem sucesso no salvamento!\nNome do arquivo muito extenso!\n");
                continue;
            }

            if (strlen(nomearq) < 5){
                printf("\n\nO nome do aquivo deve ser digitado juntamente com o .txt");
                continue;
            }
            
            posicaotxt = strlen(nomearq) - 4; 
            for (int i = posicaotxt; i < strlen(nomearq); i++){
                vernomearq[contanomearq] = nomearq[i];
                contanomearq++;
            }
            vernomearq[4] = '\0';
            
            if (strcmp(vernomearq, ".txt") != 0){
                printf("\n\nSem sucesso no salvamento!\nO .txt deve ser adicionado logo apos o nome do arquivo!\n");
                continue;
            }
            
            salvaNonograma(nomearq, lin, col, tamlin, tamcol, qtnumlin, qtnumcol, matc);
            continue;
        }
        
        // Comando para sair do jogo.
        if(strcmp(comando,"sair") == 0){
            break;
        }

    } while (1);
    

    // Fechando arquivo de entrada.
    fclose(entrada);

    // Limpando memoria de todas as variaveis alocadas
    for (int i = 0; i < tamcol; i++){
        free(matc[i]);
    }
    free(matc);
    
    for (int i = 0; i < tamlin; i++){
        free(lin[i]);
    }
    free(lin);

    for (int i = 0; i < tamcol; i++){
        free(col[i]);
    }
    free(col);

    free(qtnumlin);
    free(qtnumcol);

    return 0;
}
