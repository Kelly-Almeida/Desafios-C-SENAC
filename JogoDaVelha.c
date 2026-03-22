//Jogo da velha
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>
#include<string.h>

//Declaração de funções
bool continuacao();
void MostrarTabela(char tab[3][3]);
void jogadaUser(char tab[3][3]);
bool escolValida(char op, char tab[3][3], bool comp);
void marcar(char tab[3][3], int i, int j, bool comp);
void jogadaComp(char tab[3][3]);
bool verificaP(char tab[3][3], bool comp, int numJogada);
void mensagemFim(bool comp, bool empate);

//Variáveis globais
void placar();
int vitoUser;
int vitoComp;
int numEmpate;
int numPartidas;



void main(){
    bool jogando = true;
    vitoUser = 0;
    vitoComp = 0;
    numEmpate = 0;
    
    do{
        //Declarações
       char tabela [3][3] = {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}
        };
        int numJogadas = 0;
        bool partida = true;
        
        do{
           //mostrar tabela do Jogo
           MostrarTabela(tabela);
           
           //pedir jogada do usuário
           jogadaUser(tabela);
           numJogadas++;
           
           //Verficar se derrota,vitória ou empate
           partida = verificaP(tabela, false, numJogadas);
           
           if (partida){
               //sortear jogada do computador
               jogadaComp(tabela);
               numJogadas++;
               
               //Verficar se derrota,vitória ou empate
               partida = verificaP(tabela, true, numJogadas);
           }
           
        }while(partida);
        placar();
       
       //pergunta de continuação  
       jogando = continuacao();
    }while (jogando);

}

bool continuacao (){
    bool respInvalida = true;
    bool continua;
    char resp[3];
    
    do{
        printf("\n=*=*=*=*=*=*=*=*=*=*=*\n");
        printf("Deseja continuar? \n");
        scanf("%s", &resp);
        
        //Validação de resposta
        if (strcmp(resp, "sim") == 0 || strcmp(resp, "Sim") == 0){
            continua = true;
            respInvalida = false;
            
        } else if (strcmp(resp, "não") == 0 || strcmp(resp, "Não") == 0){
            continua = false;
            respInvalida = false;
            
        }else{
            printf("Digite um valor válido!!");
        }
        
    }while(respInvalida);
    
    return continua;
} 

void MostrarTabela(char tab[3][3]){
    system("clear");
    
    printf("\n=================\n");
    printf("\n  Jogo da velha\n");
    printf("\n=================\n");
    
    //Tabela
    for (int i = 0; i < 3; i++){
        for(int j = 0; j <3; j++){
            
            printf(" %c", tab[i][j]);
            if (j != 2){
                printf(" |");
            }
        }
        if(i != 2){
            printf("\n-----------\n");
        }
    }
}

void jogadaUser(char tab[3][3]){
    bool escolhendo = true;
    char escol;
    do{
        printf("\n=================\n");
        printf("Escolha uma posição: ");
        scanf(" %c", &escol);
        
        if (escolValida(escol, tab, false)){
            escolhendo = false;
        }else{
            printf("Posição inválida!!");
        }
    }while(escolhendo);
}

void jogadaComp(char tab[3][3]){
    srand(time(NULL));
    bool escolhendo = true;
    char iC,iJ;
    
    do{
        iC = rand() % 3;
        iJ = rand() % 3;
        
        if (escolValida(tab[iC][iJ], tab, true)){
            escolhendo = false;
        }
    }while(escolhendo);
}

bool escolValida(char op, char tab[3][3], bool comp){
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            
            if (op == tab[i][j] && op != 'X' && op != 'O'){
                marcar(tab, i, j, comp);
                return true;
            }
        }
    }
    return false;
}

void marcar (char tab[3][3], int i, int j, bool comp){
    if (comp){
        tab[i][j] = 'O';
    }else{
        tab[i][j] = 'X';
    }
}

bool verificaP(char tab[3][3], bool comp, int numJogadas){
    bool resp = true;
    bool empate = false;
  
  
    //Verificações de vitória
    
        //Vitória por linha 
    for(int i = 0; i < 3; i++){
        if (tab[i][0] == tab[i][1] && tab[i][2] == tab[i][1]){
            MostrarTabela(tab);
            resp = false;
        }
    }
    
        //Vitória com coluna
    for(int j = 0; j < 3; j++){
        if (tab[0][j] == tab[1][j] && tab[2][j] == tab[1][j]){
            MostrarTabela(tab);
            resp = false;
        }
    }
    
    
        //Vitória por diagonal
    if (tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2]){
        MostrarTabela(tab);
        resp = false;
    }else if (tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0]){
        MostrarTabela(tab);
        resp = false;
    }
    
    //Verificação de empate
    
    if (numJogadas == 9 && resp){
        resp = false;
        empate = true;
    } 
    
    
    //Acionamento de mensagem 
    if(!resp){
        mensagemFim(comp, empate);
    }
    
    return resp;
}

void mensagemFim(bool comp, bool empate){
    printf("\nFIM DE JOGO!!\n");
    
    if (!empate){
        if(comp){
            printf("Vitória do computador!!\n");
            vitoComp++;
        }else{
            printf("Vitória do jogador!!\n");
            vitoUser++;
        }
    }else{
        printf("Empate\n");
        numEmpate++;
    }
    numPartidas++;
}

void placar(){
    printf("\n==============\n");
    printf("    Placar");
    printf("\n==============\n");
    printf("Número de partidas: %d \n", numPartidas);
    printf("User: %d \n", vitoUser);
    printf("Computador: %d \n", vitoComp);
    printf("Empates: %d \n", numEmpate);
    printf("\n==============\n");
}
