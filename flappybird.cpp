/*Versão beta desenvolvida por Thiago Felski Pereira para disciplina de Algoritmos*/
#include <iostream>
#include <windows.h>
#include <conio.h> ///para o getch()
#include <time.h>
#include <stdlib.h>
///https://stackoverflow.com/questions/34474627/linux-equivalent-for-conio-h-getch

using namespace std;


/**
    F L A P B I R D (M2 Algoritmos)
    - Lembrando: não permitido o uso de funções e variáveis compostas como structs, vetores e matrizes
    - Corrigir os rastros (pássaro e obstáculos)
    - Implementar colisão
    - Implementar pontuação (mais um ponto para cada obstáculo superado)
    - Fazer 2 obstáculos simultâneos (obstaculo1 e obstaculo2)
    - Deixar a pontuação visível durante todo o jogo
    - Definir marcos para acelerar a velocidade
*/



int main()
{
    srand(time(NULL));
    int retryGame = 0;
    int bestScore = 0;
    while (retryGame == 0 || retryGame == 1){
        system("cls");
        ///ALERTA: NÃO MODIFICAR O TRECHO DE CÓDIGO, A SEGUIR.
        //INICIO: COMANDOS PARA QUE O CURSOR NÃO FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR NÃO FIQUE PISCANDO NA TELA
        //INÍCIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INÍCIO DA TELA
        ///ALERTA: NÃO MODIFICAR O TRECHO DE CÓDIGO, ACIMA.
        COORD coord;
        int obstaculo_1y_min = rand() % 15 + 1;
        int obstaculo_1y_max = obstaculo_1y_min + 3 + (rand() % 6);
        //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INÍCIO DA TELA
        ///ALERTA: NÃO MODIFICAR O TRECHO DE CÓDIGO, ACIMA.

        /// VARIAVEIS DEBUG ABAIXO, REMOVER EM VERSÃO FINAL ///
        int debugVar = -1;
        /// FIM DAS VARIAVEIS DEBUG ///

        int score = 0;
        int runtimeSpeed = 300;
        int speed = 0;
        int nextSpeedIncrement = score + 5;
        bool speedCapped = false;
        bool isDead = false;
        int bird_x=5, bird_y=10; // [Acanixz] Posição Y começa de cima e vai para baixo
        int bird_y_anterior = 9;
        int spawn_obstaculos = 80;
        int obstaculo_1x= spawn_obstaculos, obstaculo_1y; // [Acanixz] Originalmente o obstaculo_1x era 129
        int obstaculo_1x_anterior = 0;
        int tecla;

        ///DESENHO DO CENÁRIO // [Acanixz] Originalmente tinha mais hifens, porém não era compativel com a resolução
        cout<<"-------------------------------------------------------------------------------------------------------------------";
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<"-------------------------------------------------------------------------------------------------------------------";



        while (true) { //esse laço faz o jogo rodar para sempre
            debugVar = obstaculo_1y_min;
            ///POSICIONA O OBSTÁCULO
            obstaculo_1y=1;
            while(obstaculo_1y<20){
                coord.X = obstaculo_1x;    coord.Y = obstaculo_1y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                if(obstaculo_1y< obstaculo_1y_min || obstaculo_1y> obstaculo_1y_max){
                    cout<<char(219);
                } else {
                    cout<<" ";
                }

                obstaculo_1y++;
            }
            ///REMOVE TRAÇO ANTERIOR
            obstaculo_1y=1;
            while(obstaculo_1y<20){
                coord.X = obstaculo_1x_anterior;    coord.Y = obstaculo_1y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<" ";
                obstaculo_1y++;
            }

            ///POSICIONA O PÁSSARO
            coord.X = bird_x;    coord.Y = bird_y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<char(190);
            ///REMOVE TRAÇO ANTERIOR
            coord.X = bird_x;    coord.Y = bird_y_anterior;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<" ";

            ///DESENHA O SCORE
            coord.X = 30;    coord.Y = 20;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"SCORE: " << score;

            ///DESENHA O DEBUG
            coord.X = 50;    coord.Y = 20;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"DEBUG: " << debugVar;

            ///VERIFICA COMANDO DO JOGADOR
            if (kbhit()) { ///verifica se uma tecla foi pressionada
                tecla=getch(); //verifica comando do jogador
            }
            while(kbhit()) getch();

            bird_y_anterior = bird_y;
            if ( tecla=='w' || tecla=='W' ){
                bird_y--;
                tecla='0';
            } else {
                bird_y++;
            }

            ///PÁSSARO CAI 1 POSIÇÃO SE NÃO FOI PRESSIONADO PARA SUBIR

            ///OBSTÁCULO AVANÇA UMA POSIÇÃO PARA ESQUERDA
            obstaculo_1x_anterior = obstaculo_1x;
            obstaculo_1x--;

            if (obstaculo_1x <= 0){
                obstaculo_1x_anterior = 1;
                obstaculo_1x = spawn_obstaculos;
                obstaculo_1y_min = rand() % 15 + 1;
                obstaculo_1y_max = obstaculo_1y_min + 3 + (rand() % 6);
            }

            ///VERIFICA COLISÃO

            if (bird_y >= 20 || bird_y <= 0){
                isDead = true;
            }

            if (bird_x == obstaculo_1x){
                    if (bird_y < obstaculo_1y_min || bird_y > obstaculo_1y_max){
                        isDead = true;
                    }
                    else
                    {
                        score++;
                        if (score >= nextSpeedIncrement){
                            nextSpeedIncrement = score + 5;
                            speed++;
                            cout << "\a" << endl;
                        }
                    }
            }

            if (isDead == true){
                break;
            }
            ///TEMPO DE ESPERA
            if (speedCapped == false) {
                runtimeSpeed = 300 - (100 * speed);
                if (runtimeSpeed <= 0){
                    runtimeSpeed = 100;
                    speedCapped = true;
                }
            } else{
                runtimeSpeed = 100;
            }
            Sleep(runtimeSpeed);


        }
        do {
            if (score > bestScore) {
                bestScore = score;
            }

            system("cls");
            cout<<"-------------------------------------------------------------------------------------------------------------------";
            cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tGAME OVER!" << "\n\t\t\t\t\t\tScore: " << score << "\n\t\t\t\t\t\tBest: " << bestScore;
            Sleep(1500);
            while(kbhit()) getch();
            cout<<"\n\n\n\n\n\n\n\t\t\t\t\t\tTry Again?\n\t\t\t\t\t    1 - Yes\t2 - No\n";
            cout<<"-------------------------------------------------------------------------------------------------------------------\n\n\t\t\t\t\t\t     ";
            cin >> retryGame;
        } while (retryGame != 1 && retryGame != 2);

    }
    return 0;
}
