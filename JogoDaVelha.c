//Jogo da velha
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>
#include<string.h>
#include <unistd.h>

//Declaração de funções

    //Modo computador
void jogadaComp(char tab[3][3]);   
bool analise(char tab[3][3], int coordenadas[]);  

    //Funcionamento universal
void limparTela();  
bool verificaP(char tab[3][3], bool comp, int numJogada, bool modoDuo, char nomePlayer[100]);
bool continuacao();  
void MostrarTabela(char tab[3][3]);

void jogadaUser(char tab[3][3], bool modoDuo, char player[100], int numJogador); //Incluir o mecânismo do nome do jogador   
void mensagemFim(bool comp, bool empate, bool modoDuo, char nomePlayer[100]); //Incluir mensagens para o modo de dois jogadores
void marcar(char tab[3][3], int i, int j, bool comp); //Adicionar uma parte para um jogador secundário
bool escolValida(char op, char tab[3][3], bool bolinha); //Adicionar adaptação para segundo jogador
void placar(char nomePlayer1[100], char nomePlayer2[100]); //Adicinar a uma adaptação para o jogadores


    //Modo Jogadores
void nomePlayer (bool modoDuo, char nome[100],int numPlayer);
bool modoJogo();
    

//Variáveis globais

int vitoPlayer1;
int vitoPlayer2;
int vitoComp;
int numEmpate;
int numPartidas;
char nomePlayer1 [100];
char nomePlayer2 [100];




void main(){
    bool jogando = true;
    vitoPlayer1 = 0;
    vitoPlayer2 = 0;
    numEmpate = 0;
    bool modBoot;
    
    //Modo de dois Jogadores...
    
    modBoot = modoJogo();
    
    if (modBoot){
        nomePlayer (false, nomePlayer1, 0);
        
        do{
            //Declarações
           char tabela [3][3] = {
                {'1', '2', '3'},
                {'4', '5', '6'},
                {'7', '8', '9'}
            };
            int numJogadas = 0;
            bool partida = true;
            char nomeComp[100] = "Th3odory_boot";
            
            
            do{
               //mostrar tabela do Jogo
               MostrarTabela(tabela);
               
               //pedir jogada do usuário
               jogadaUser(tabela, false, nomePlayer1, 1);
               numJogadas++;
               
               //Verficar se derrota,vitória ou empate
               partida = verificaP(tabela, false, numJogadas, false, nomePlayer1);
               
               if (partida){
                   //sortear jogada do computador
                   jogadaComp(tabela);
                   numJogadas++;
                   
                   //Verficar se derrota,vitória ou empate
                   partida = verificaP(tabela, true, numJogadas, false, nomeComp);
               }
               
            }while(partida);
            placar(nomePlayer1,nomeComp);
           
           //pergunta de continuação  
           jogando = continuacao();
        }while (jogando);
    } else{
        nomePlayer (true, nomePlayer1, 1);
        nomePlayer(true, nomePlayer2, 2);
        
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
               
               //Jogada do primeiro jogador
               jogadaUser(tabela, true, nomePlayer1, 1);
               numJogadas++;
               
               //Verificação de derrota, empate ou vitória
               partida = verificaP(tabela, false, numJogadas, true, nomePlayer1);
               
               
               
               //Jogada do segundo jogador
               if (partida){
                   //Mostrar a Tabela
                    MostrarTabela(tabela);
                   //sortear jogada do computador
                   jogadaUser(tabela, true, nomePlayer2, 2);
                   numJogadas++;
                   
                   //Verficar se derrota,vitória ou empate
                   partida = verificaP(tabela, true, numJogadas, true, nomePlayer2);
               }
               
            }while(partida);
            //placar
            placar(nomePlayer1,nomePlayer2);
            
           
           //pergunta de continuação  
           jogando = continuacao();
        }while (jogando);
    }
    
    
    
}

//Mensagem de continuação
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

//Mostra a tabela do jogo
void MostrarTabela(char tab[3][3]){
    limparTela();
    
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

// Marca a resposta do usuário
void jogadaUser(char tab[3][3], bool modoDuo, char player[100], int numJogador){
    bool escolhendo = true;
    bool bolinha;
    char escol;
    
    if(numJogador == 1){
        bolinha = false;
    } else{
        bolinha = true;
    }
    
    if(modoDuo){
       do{
            printf("\n=================\n");
            printf("%s, escolha uma posição: ", player);
            scanf(" %c", &escol);
            
            if (escolValida(escol, tab, bolinha)){
                escolhendo = false;
            }else{
                printf("Posição inválida!!");
            }
       }while(escolhendo);
    } else{
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
    
}

// Escolhe a posição do boot
void jogadaComp(char tab[3][3]){
    srand(time(NULL));
    bool escolhendo = true;
    char iC,iJ;
    int coord[2] = {-1, -1};
    
   bool marcadoAnalise = analise(tab, coord);
    
    
    do{
        if(marcadoAnalise){
            escolhendo = false;
        } else{
            iC = rand() % 3;
            iJ = rand() % 3;
            
            if (escolValida(tab[iC][iJ], tab, true)){
            escolhendo = false;
            
            }
        }
    }while(escolhendo);
}

//Analise do Jogo
bool analise(char tab [3][3], int coordenadas[2]){

    //Verificação de possível vitória em coluna
    for(int j = 0; j < 3; j++){
        if (tab[0][j] == tab[1][j]){
            
            if(escolValida(tab[2][j], tab, true)){
                return true;
            }
            
            
        }else if (tab[0][j] == tab[2][j]){
            
            if (escolValida(tab[1][j], tab, true)){
                return true;
            }
            
        }else if (tab[1][j] == tab[2][j]){
        
            if (escolValida(tab[0][j], tab, true)){
                return true;
            }
        }
    }
    
    //Verificação de possível vitória em linha
    for(int i = 0; i < 3; i++){
        if (tab[i][0] == tab[i][1]){
            
            if(escolValida(tab[i][2], tab, true)){
                return true;
            }
            
            
        }else if (tab[i][0] == tab[i][2]){
            
            if (escolValida(tab[i][1], tab, true)){
                return true;
            }
            
        }else if (tab[i][1] == tab[i][2]){
        
            if (escolValida(tab[i][0], tab, true)){
                return true;
            }
        }
    }
    
    //Teste de vitória por diagonal comum 
    if(tab[0][0] == tab[1][1]){
        
        if(escolValida(tab[2][2], tab, true)){
            return true;
        }
    } else if (tab[0][0] == tab[2][2]){
        
        if(escolValida(tab[1][1], tab, true)){
            return true;
        }
    } else if (tab[1][1] == tab[2][2]){
        if(escolValida(tab[0][0], tab, true)){
            return true;
        }
    }
    
    //Teste de vitória por diagonal invertida
    if(tab[0][2] == tab[1][1]){
        
        if(escolValida(tab[2][0], tab, true)){
            return true;
        }
    } else if (tab[0][2] == tab[2][0]){
        
        if(escolValida(tab[1][1], tab, true)){
            return true;
        }
    } else if (tab[1][1] == tab[2][0]){
        if(escolValida(tab[0][2], tab, true)){
            return true;
        }
    }
    
    return false;
    
}

//Verificação de se a posição escolhida é válida
bool escolValida(char op, char tab[3][3], bool bolinha){
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            
            if (op == tab[i][j] && op != 'X' && op != 'O'){
                marcar(tab, i, j, bolinha);
                return true;
            }
        }
    }
    return false;
}

//Marcando posição
void marcar (char tab[3][3], int i, int j, bool comp){
    if (comp){
        tab[i][j] = 'O';
    }else{
        tab[i][j] = 'X';
    }
}

//Verificação de vitória, derrota ou empate
bool verificaP(char tab[3][3], bool comp, int numJogadas, bool modoDuo, char nomePlayer[100]){
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
        MostrarTabela(tab);
        resp = false;
        empate = true;
    } 

    
    //Acionamento de mensagem 
    if(!resp){
        mensagemFim(comp, empate, modoDuo, nomePlayer);
    } 
    
    return resp;
}

//Mensagens de final de partida
void mensagemFim(bool bolinha, bool empate, bool modoDuo, char nomePlayer[100]){
    printf("\nFIM DE JOGO!!\n\n");
    sleep(1);
    
    if (!empate){
            if(bolinha){
                printf("Vitória de %s!!\n", nomePlayer);
                vitoPlayer2++;
            }else{
                printf("Vitória de %s!!\n", nomePlayer);
                vitoPlayer1++;
            }
        }else{
            printf("Empate\n");
            numEmpate++;
        }
        
    numPartidas++;
    sleep(1);
    
}

//Placar
void placar(char nomePlayer1[100],char nomePlayer2[100]){
    printf("\n==============\n");
    printf("    Placar");
    printf("\n==============\n");
    printf("Número de partidas: %d \n", numPartidas);
    printf("%s: %d \n", nomePlayer1,vitoPlayer1);
    printf("%s: %d \n",nomePlayer2, vitoPlayer2 );
    printf("Empates: %d \n", numEmpate);
    printf("\n==============\n");
}

//Escolher modo do jogo

//Declaração de nome de player
void nomePlayer (bool modoDuo, char nome[100], int numPlayer){
    
    
    printf("\n=*=*=*=*=*=*=*=*=*=*=*\n");
    
    if (modoDuo){
        printf("Digite o nome do %dº jogador: ", numPlayer);
        scanf("%s", nome);
    }else{
        printf("Digite seu nome: ");
        scanf("%s", nome);
    }
    
  
}

bool modoJogo(){
    bool resp = true;
    int escol = 0;
    
    do{
        printf("\n=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=\n");
        printf("\tSelecione o modo de jogo\n");
        printf("\n=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=\n");
        printf("\t[1] - Jogador e boot\n");
        printf("\t[2] - Dois jogadores\n");
        
        printf("==> ");
        scanf("%d", &escol);
        
        if(escol == 1){
            resp = true;
        }else if(escol == 2){
            resp = false;
        } else{
            printf("Escolha um valor válido!!\n");
        }
      
    }while(escol != 1 && escol != 2);
    
      
    return resp;
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
