//MR.DO!
//RODRIGO DAL RI
//VITHOR AMARAL PRESTES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <conio2.h>
#include <windows.h>
#include <windowsx.h>
#include <time.h>
#include <conio.h>
#define NOME 50
#define TOP5 5
#define NUMLIN 23
#define NUMCOL 60
typedef struct
{//Estrutura de estado
    int pontos;
    int fantasmas_nascidos;
}JOGO_SALVO;
typedef struct
{//Estrutura de pontuação
    char nome[NOME];
    int pontos;
}HIGH_SCORES;
void menu()
{//Imprime o menu do jogo com todas as 4 opções
    printf("\n\t\t\t\tMr. Do!\n\n");
    printf("\t1 - Novo Jogo\n");
    printf("\t2 - Continuar\n");
    printf("\t3 - High Scores\n");
    printf("\t4 - Sair\n\n");
}
void abre_grava_arquivo(char m[NUMLIN][NUMCOL], char *nome_arq, JOGO_SALVO estado)
{//Função responsável por salvar a matriz (incluindo pontos) em seu estado atual nos arquivos .txt e .bin
    int i,j,ret;
    FILE *arq;
    FILE *arqb;

    arqb=fopen("estado.bin","wb");
    arq=fopen(nome_arq,"w");

    if(arqb==NULL)
        printf("\n ERRO, NAO FOI POSSIVEL SALVAR SEU JOGO!\n");
    else
        fwrite(&estado,sizeof(JOGO_SALVO),1,arqb);
    if(arq==NULL)
        printf("\n ERRO, NAO FOI POSSIVEL SALVAR SEU JOGO!\n");
    else{
        for(i=0;i<NUMLIN;i++){
            for(j=0;j<NUMCOL;j++)
                putc(m[i][j],arq);}}
    fclose(arq);
    fclose(arqb);
}
void imprime_matriz_tela(char m[NUMLIN][NUMCOL],int *pontos)
{//Funcao responsavel por imprimir o mapa na tela
    int i,j,k;

    for(k=0;k<NUMCOL+1;k++){//Imprime as bordas(margem) do jogo
        textcolor(WHITE);
        printf("-");}
    printf("\n");
    for(i=0;i<NUMLIN;i++){//Imprime as bordas(margem) do jogo
        textcolor(WHITE);
        printf("|");
        for(j=0;j<NUMCOL;j++){//Troca as cores dos caracteres e os substitui por outros símbolos
            switch(m[i][j]){
                case 'd': textcolor(WHITE);printf("%c",227);break;
                case 'i': textcolor(RED); printf("%c",153);break;
                case 'n': textcolor(BROWN);printf("%c",206);break;
                case 'p': textcolor(GREEN);printf("%c",176);break;
                case 'f': textcolor(BLUE);printf("%c",229);break;
                case 't': textcolor(WHITE);printf("%c",250);break;
                case 'v': textcolor(BLACK);printf("%c", 32);break;}}
    textcolor(WHITE);
    printf("|");
    if(i==0&&j==NUMCOL)
        printf("\t    Mr. Do!");//Imprime o score atual
    if(i==5&&j==NUMCOL)
        printf("\tSCORE: %5d", pontos);
    printf("\n");}
    for(k=0;k<NUMCOL;k++){
        textcolor(WHITE);
        printf("-");}
}
void abre_le_arquivo(char m[NUMLIN][NUMCOL], char *nome_arq)
{//Função responsável por abrir a matriz
    int i,ret;
    FILE *arq;

    arq=fopen(nome_arq,"r");
    if(arq==NULL)
        printf("\n ERRO, NAO FOI POSSIVEL ABRIR SEU JOGO!\n");
    else{
        ret=1;
        for(i=0;i<NUMLIN;i++)
            fscanf(arq,"%s\n",m[i]);}
    fclose(arq);
}
int abre_le_binario(HIGH_SCORES vet[TOP5])
{//Abre e lê os Highscores salvos em highscores.bin (arquivo binário)
    FILE* arqb;
    int pos=0;
    arqb=fopen("highscores.bin","rb");
    if(arqb==NULL){
        printf("\n ERRO, NAO FOI POSSIVEL ABRIR OS HIGH SCORES!\n");
        pos=0;}
    else
        do{
            fread(&vet[pos],sizeof(vet),1,arqb);
            pos++;
        }while(!feof(arqb));
    fclose(arqb);
    return (pos-1);
}
void imprime_binario(HIGH_SCORES vet[TOP5],int num_scores)
{//Função responsável por imprimir os high scores
    int i;
    for(i=0;i<num_scores-1;i++)
        printf("\n\t%d: %s %d\n ",i+1,vet[i].nome,vet[i].pontos);
}
void ordena_binario(HIGH_SCORES vet[TOP5],int num_scores)
{//Função responsável por ordenar os high scores em ordem crescente
    int i,j;
    HIGH_SCORES aux;
    FILE *arqb;

    arqb=fopen("highscores.bin","wb+");
    if(arqb==NULL)
        printf("\n ERRO, NAO FOI POSSIVEL ORDENAR OS HIGH SCORES!\n");
    else{
        for(i=0;i<num_scores;i++){
            for(j=i+1;j<num_scores;j++){
                if(vet[i].pontos>vet[j].pontos){
                    aux=vet[i];
                    vet[i]=vet[j];
                    vet[j]=aux;}}}
        for(i=0;i<num_scores;i++){
            fwrite(&vet[i],sizeof(HIGH_SCORES[i]),1,arqb);}}
    fclose(arqb);
}
void salva_novo_highscore(HIGH_SCORES vet[TOP5],int pontuacao)
{//Essa função é responsável por verificar se o último Score salvo é maior que algum do TOP 5, caso sim, substitui onde encontra-se o maior valor entre os 5 que seja menor que o Score salvo.
    HIGH_SCORES novo;
    int i;
    FILE *arqb;

    arqb=fopen("highscores.bin", "rb+");
    if(arqb==NULL)
        printf("\n ERRO, NAO FOI POSSIVEL SALVAR SUA PONTUACAO!\n");
    else{
        gets(novo.nome);
        novo.pontos=pontuacao;
        if(novo.pontos>vet[4].pontos){
            vet[0]=vet[1];
            vet[1]=vet[2];
            vet[2]=vet[3];
            vet[3]=vet[4];
            vet[4]=novo;}
        else if(novo.pontos>vet[3].pontos){
                vet[0]=vet[1];
                vet[1]=vet[2];
                vet[2]=vet[3];
                vet[3]=novo;}
             else if(novo.pontos>vet[2].pontos){
                    vet[0]=vet[1];
                    vet[1]=vet[2];
                    vet[2]=novo;}
                  else if(novo.pontos>vet[1].pontos){
                       vet[0]=vet[1];
                       vet[1]=novo;}
                       else if(novo.pontos>vet[0].pontos)
                            vet[0]=novo;
        for(i=0;i<TOP5;i++)
            fwrite(&vet[i],sizeof(HIGH_SCORES),1,arqb);}
    fclose(arqb);
}
int move_do(char m[NUMLIN][NUMCOL], char dir)
{//Função responsável pela movimentação do Mr.Do
    int retorno,i,j,lin=0,col=0;
    int pos_do[2];

    for(i=0;i<NUMLIN;i++)//localiza o Mr.DO
        for(j=0;j<NUMCOL;j++)
            if(m[i][j]=='d'){
                lin=i;
                col=j;}
    pos_do[0]=lin;
    pos_do[1]=col;
    dir=tolower(dir);
    switch(dir){//W-para cima S-para baixo D-para direita A-para esquerda
        case 'w': if(pos_do[0]!=0&&m[lin-1][col]!='n'){
                    if(m[lin-1][col]=='i')
                        retorno=27;
                    else{
                        if(m[lin-1][col]=='f')
                            retorno=229;
                        pos_do[0]=pos_do[0]-1;
                        for(i=0;i<NUMLIN;i++)
                            for(j=0;j<NUMCOL;j++)
                                if(m[i][j]=='d'){
                                    lin=i;
                                    col=j;
                                    pos_do[0]=lin-1;}
                        m[lin][col]='v';
                        m[lin-1][col]='d';}}
                  break;

        case 's': if(pos_do[0]!=22&&m[lin+1][col]!='n'){
                    if(m[lin+1][col]=='i')
                        retorno=27;
                    else{
                        if(m[lin+1][col]=='f')
                            retorno=229;
                        pos_do[0]=pos_do[0]+1;
                        for(i=0;i<NUMLIN;i++)
                            for(j=0;j<NUMCOL;j++)
                                if(m[i][j]=='d'){
                                    lin=i;
                                    col=j;
                                    pos_do[0]=lin+1;}
                        m[lin][col]='v';
                        m[lin+1][col]='d';}}
                  break;

        case 'a':if(pos_do[1]!=0&&m[lin][col-1]!='n'){
                    if(m[lin][col-1]=='i')
                        retorno=27;
                    else{
                        if(m[lin][col-1]=='f')
                            retorno=229;
                        pos_do[1]=pos_do[1]-1;
                        for(i=0;i<NUMLIN;i++)
                            for(j=0;j<NUMCOL;j++)
                                if(m[i][j]=='d'){
                                    lin=i;
                                    col=j;
                                    pos_do[1]=lin-1;}
                        m[lin][col]='v';
                        m[lin][col-1]='d';}}
                  break;

        case 'd': if(pos_do[1]!=59&&m[lin][col+1]!='n'){
                    if(m[lin][col+1]=='i')
                        retorno=27;
                    else{
                        if(m[lin][col+1]=='f')
                            retorno=229;
                        pos_do[1]=pos_do[1]+1;
                        for(i=0;i<NUMLIN;i++)
                            for(j=0;j<NUMCOL;j++)
                                if(m[i][j]=='d'){
                                    lin=i;
                                    col=j;
                                    pos_do[1]=lin+1;}
                        m[lin][col]='v';
                        m[lin][col+1]='d';}}
                  break;}

    return retorno; //retorno: 27=morreu, 229=comeu fruta
}
int main()
{
    HIGH_SCORES top[TOP5];
    JOGO_SALVO estado;
    int i,j,cod,pontos=0,num_scores=0,retorno_move_do,morreu=0,venceu=0,frutas=0,fantasmas=0,segunda_fase=0;
    char matriz_mapa[NUMLIN][NUMCOL];
    char fase1[NOME]="fase1.txt";
    char fase2[NOME]="fase2.txt";
    char continuar[NOME]="continuar.txt";
    char direct;
    int lin_n, col_n;
    menu();

    do{
        printf("\n\n          Entre com a opcao desejada: ");
        scanf("%d",&cod);
        system("cls||clear");

        switch (cod){
            case 1: abre_le_arquivo(matriz_mapa,fase1);//Abre o arquivo que contém a matriz da fase 1 (Novo jogo) caso a opção digitada seja 1
                    imprime_matriz_tela(matriz_mapa,pontos);//Imprime a matriz e junto dela o score que o jogador tiver obtido até o momento
                    do{
                        direct=0;
                        if(kbhit()){
                            system("cls||clear");
                            direct=getch();
                            imprime_matriz_tela(matriz_mapa,pontos);
                            }
                        retorno_move_do=move_do(matriz_mapa,direct);
                        if(fantasmas<10){//Gera no máximo dez fantasmas no mapa ao lado dos ninhos
                                            for(i=0;i<NUMLIN;i++)
                                                for(j=0;j<NUMCOL;j++){
                                                    if(matriz_mapa[i][j]=='n'){//Localiza um ninho no mapa para posteriormente gerar fantasmas ao redor do mesmo
                                                        lin_n=i;
                                                        col_n=j;}}
                                                if(matriz_mapa[lin_n+1][col_n]=='v')//Substitui o vazio 'v' encontrado ao lado de um ninho por um fantasma 'i'
                                                    matriz_mapa[lin_n+1][col_n]='i';//Uma busca por 'v' é feita, pois somente se a posição ao lado do ninho for 'v' ele gera fantasmas.
                                                else if(matriz_mapa[lin_n-1][col_n]=='v')
                                                    matriz_mapa[lin_n-1][col_n]='i';
                                                else if(matriz_mapa[lin_n][col_n+1]=='v')
                                                    matriz_mapa[lin_n][col_n+1]='i';
                                                else if(matriz_mapa[lin_n][col_n-1]=='v')
                                                    matriz_mapa[lin_n][col_n-1]='i';
                                                fantasmas++;}
                        if(retorno_move_do==229){//Soma o número de frutas que foram pegas na pontuação (50 pontos para cada uma)
                            pontos+=50;
                            frutas+=1;}
                        if(frutas==32){//Se todas as frutas foram pegas, a fase termina
                            venceu=1;
                            direct=27;}
                        if(retorno_move_do==27){//Caso algum fantasma mate Mr. Do, morreu =1; 27 corresponde à tecla ESC
                            morreu=1;
                            direct=27;}
                    }while(direct!=27);//Ao digitar ESC, o usuário estará salvando o jogo
                    if(direct==27&&venceu==0&&morreu==0){
                        system("cls||clear");
                        printf("\n\n             Voce saiu do jogo!");
                        estado.pontos=pontos;
                        estado.fantasmas_nascidos=fantasmas;
                        abre_grava_arquivo(matriz_mapa,continuar,estado);}
                    if(morreu==1){
                        system("cls||clear");
                        printf("\n\n             GAME OVER\n\n");
                       // num_scores=abre_le_binario(top);
                        ordena_binario(top,num_scores);
                        salva_novo_highscore(top,pontos);
                        pontos=0;
                        }
                    if(venceu==1){//Se todas as frutas foram capturadas, você passou de fase!
                       system("cls||clear");
                       printf("\n\n         PARABENS VOCE PASSOU DE FASE\n\n");
                       printf("\n\n\n\n                   Aguarde!");
                       Sleep(2000);
                       segunda_fase=1;
                                venceu=0;
                                morreu=0;
                                direct=0;
                                abre_le_arquivo(matriz_mapa,fase2);
                                imprime_matriz_tela(matriz_mapa,pontos);
                                    do{
                                        direct=0;
                                        if(kbhit()){
                                        system("cls||clear");
                                        direct=getch();
                                        imprime_matriz_tela(matriz_mapa,pontos);}
                                        retorno_move_do=move_do(matriz_mapa,direct);
                                        if(fantasmas<10){
                                            for(i=0;i<NUMLIN;i++)
                                                for(j=0;j<NUMCOL;j++){
                                                    if(matriz_mapa[i][j]=='n'){
                                                        lin_n=i;
                                                        col_n=j;}}
                                                if(matriz_mapa[lin_n+1][col_n]=='v')
                                                    matriz_mapa[lin_n+1][col_n]='i';
                                                else if(matriz_mapa[lin_n-1][col_n]=='v')
                                                    matriz_mapa[lin_n-1][col_n]='i';
                                                else if(matriz_mapa[lin_n][col_n+1]=='v')
                                                    matriz_mapa[lin_n][col_n+1]='i';
                                                else if(matriz_mapa[lin_n][col_n-1]=='v')
                                                    matriz_mapa[lin_n][col_n-1]='i';
                                                fantasmas++;}
                                        if(retorno_move_do==229){
                                            pontos+=50;
                                            frutas+=1;}
                                        if(frutas==64){
                                            venceu=1;
                                            direct=27;}
                                        if(retorno_move_do==27){
                                            morreu=1;
                                            direct=27;}
                                    }while(direct!=27);
                                if(direct==27&&venceu==0&&morreu==0){
                                    system("cls||clear");
                                    printf("\n\n             Voce saiu do jogo!");
                                    estado.pontos=pontos;
                                    estado.fantasmas_nascidos=fantasmas;
                                    abre_grava_arquivo(matriz_mapa,continuar,estado);}
                                if(morreu==1){
                                    system("cls||clear");
                                    printf("\n\n             GAME OVER\n\n");
                                    //num_scores=abre_le_binario(top);
                                    ordena_binario(top,num_scores);
                                    salva_novo_highscore(top,pontos);
                                    pontos=0;}
                                if(venceu==1){
                                    system("cls||clear");
                                    printf("\n\n            PARABENS VOCE GANHOU\n\n");
                                //num_scores=abre_le_binario(top);
                                ordena_binario(top,num_scores);
                                salva_novo_highscore(top,pontos);
                                pontos=0;}}
                    venceu=0;
                    morreu=0;
                    direct=0;
                    break;
            case 2: abre_le_arquivo(matriz_mapa,continuar);
                    imprime_matriz_tela(matriz_mapa,pontos);
                    do{
                        direct=0;
                        if(kbhit()){
                            system("cls||clear");
                            direct=getch();
                            imprime_matriz_tela(matriz_mapa,pontos);}
                        retorno_move_do=move_do(matriz_mapa,direct);
                        if(fantasmas<10){
                                            for(i=0;i<NUMLIN;i++)
                                                for(j=0;j<NUMCOL;j++){
                                                    if(matriz_mapa[i][j]=='n'){
                                                        lin_n=i;
                                                        col_n=j;}}
                                                if(matriz_mapa[lin_n+1][col_n]=='v')
                                                    matriz_mapa[lin_n+1][col_n]='i';
                                                else if(matriz_mapa[lin_n-1][col_n]=='v')
                                                    matriz_mapa[lin_n-1][col_n]='i';
                                                else if(matriz_mapa[lin_n][col_n+1]=='v')
                                                    matriz_mapa[lin_n][col_n+1]='i';
                                                else if(matriz_mapa[lin_n][col_n-1]=='v')
                                                    matriz_mapa[lin_n][col_n-1]='i';
                                                fantasmas++;}
                        if(retorno_move_do==229){
                            pontos+=50;
                            frutas+=1;}
                        if(frutas==32){
                            venceu=1;
                            direct=27;}
                        if(retorno_move_do==27){
                            morreu=1;
                            direct=27;}
                    }while(direct!=27);
                    if(direct==27&&venceu==0&&morreu==0){
                        system("cls||clear");
                        printf("\n\n             Voce saiu do jogo!");
                        estado.pontos=pontos;
                        estado.fantasmas_nascidos=fantasmas;
                        abre_grava_arquivo(matriz_mapa,continuar,estado);}
                    if(morreu==1){
                        system("cls||clear");
                        printf("\n\n             GAME OVER\n\n");
                        //num_scores=abre_le_binario(top);
                        ordena_binario(top,num_scores);
                        salva_novo_highscore(top,pontos);
                        pontos=0;}
                    if(venceu==1){
                       system("cls||clear");
                        if(segunda_fase==0){
                                printf("\n\n         PARABENS VOCE PASSOU DE FASE\n\n");
                                printf("\n\n\n\n                   Aguarde!");
                                Sleep(2000);
                                system("cls||clear");
                                venceu=0;
                                morreu=0;
                                direct=0;
                                abre_le_arquivo(matriz_mapa,fase2);
                                imprime_matriz_tela(matriz_mapa,pontos);
                                    do{
                                        direct=0;
                                        if(kbhit()){
                                        system("cls||clear");
                                        direct=getch();
                                        imprime_matriz_tela(matriz_mapa,pontos);}
                                        retorno_move_do=move_do(matriz_mapa,direct);
                                        if(fantasmas<10){
                                            for(i=0;i<NUMLIN;i++)
                                                for(j=0;j<NUMCOL;j++){
                                                    if(matriz_mapa[i][j]=='n'){
                                                        lin_n=i;
                                                        col_n=j;}}
                                                if(matriz_mapa[lin_n+1][col_n]=='v')
                                                    matriz_mapa[lin_n+1][col_n]='i';
                                                else if(matriz_mapa[lin_n-1][col_n]=='v')
                                                    matriz_mapa[lin_n-1][col_n]='i';
                                                else if(matriz_mapa[lin_n][col_n+1]=='v')
                                                    matriz_mapa[lin_n][col_n+1]='i';
                                                else if(matriz_mapa[lin_n][col_n-1]=='v')
                                                    matriz_mapa[lin_n][col_n-1]='i';
                                                fantasmas++;}
                                        if(retorno_move_do==229){
                                            pontos+=50;
                                            frutas+=1;}
                                        if(frutas==64){
                                            venceu=1;
                                            direct=27;}
                                        if(retorno_move_do==27){
                                            morreu=1;
                                            direct=27;}
                                    }while(direct!=27);
                                if(direct==27&&venceu==0&&morreu==0){
                                    system("cls||clear");
                                    printf("\n\n             Voce saiu do jogo!");
                                    estado.pontos=pontos;
                                    estado.fantasmas_nascidos=fantasmas;
                                    abre_grava_arquivo(matriz_mapa,continuar,estado);}
                                if(morreu==1){
                                    system("cls||clear");
                                    printf("\n\n             GAME OVER\n\n");
                                    //num_scores=abre_le_binario(top);
                                    ordena_binario(top,num_scores);
                                    salva_novo_highscore(top,pontos);
                                    pontos=0;}
                                if(venceu==1){
                                    system("cls||clear");
                                    printf("\n\n            PARABENS VOCE GANHOU\n\n");}
                        else
                            printf("\n\n            PARABENS VOCE GANHOU\n\n");
                       //num_scores=abre_le_binario(top);
                       ordena_binario(top,num_scores);
                       salva_novo_highscore(top,pontos);
                       pontos=0;}}
                    venceu=0;
                    morreu=0;
                    direct=0;
                    break;
            case 3: system("cls || clear");//Caso opção digitada for 3, limpa a tela e imprime o highscore atualizado (caso exista)
                    printf("\n\t\t\t\tTOP 5 - HIGH SCORES\n\n");
                    //num_scores=abre_le_binario(top);
                    imprime_binario(top,num_scores);
                    break;
            case 4: system("cls || clear");//Caso opção digitada for 4, limpa a tela e encerra o jogo
                    printf("\n                  JOGO ENCERRADO!\n");
                    break;}
    }while(cod!=4);
    return 0;
}

