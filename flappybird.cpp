/*Vers�o beta desenvolvida por Thiago Felski Pereira para disciplina de Algoritmos*/
#include <iostream>
#include <windows.h>
#include <conio.h> ///para o getch()
#include <time.h>
#include <stdlib.h>
///https://stackoverflow.com/questions/34474627/linux-equivalent-for-conio-h-getch

using namespace std;


/**
    F L A P B I R D (M2 Algoritmos)
    - Lembrando: n�o permitido o uso de fun��es e vari�veis compostas como structs, vetores e matrizes
    - Corrigir os rastros (p�ssaro e obst�culos) [FEITO]
    - Implementar colis�o [FEITO]
    - Implementar pontua��o (mais um ponto para cada obst�culo superado) [FEITO]
    - Fazer 2 obst�culos simult�neos (obstaculo1 e obstaculo2) [A FAZER]
    - Deixar a pontua��o vis�vel durante todo o jogo [FEITO]
    - Definir marcos para acelerar a velocidade [FEITO]
*/



int main()
{
    srand(time(NULL));
    int retryGame = 0;
    int bestScore = 0;
    while (retryGame == 0 || retryGame == 1){
        system("cls");
        ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, A SEGUIR.
        //INICIO: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
        //IN�CIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
        ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, ACIMA.
        COORD coord;
        int obstaculo_1y_min = rand() % 15 + 1;
        int obstaculo_1y_max = obstaculo_1y_min + 3 + (rand() % 6);

        int obstaculo_2y_min = rand() % 15 + 1;
        int obstaculo_2y_max = obstaculo_2y_min + 3 + (rand() % 6);

        int obstaculo_3y_min = rand() % 15 + 1;
        int obstaculo_3y_max = obstaculo_3y_min + 3 + (rand() % 6);
        //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
        ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, ACIMA.

        /// VARIAVEIS DEBUG ABAIXO, REMOVER EM VERS�O FINAL ///
        int debugVar = -1;
        /// FIM DAS VARIAVEIS DEBUG ///

        int score = 0;
        int runtimeSpeed = 300;
        int speed = 0;
        int nextSpeedIncrement = score + 5;
        bool speedCapped = false;
        bool isDead = false;
        int bird_x=5, bird_y=10; // Posi��o Y come�a de cima e vai para baixo
        int bird_y_anterior = 9;
        int spawn_obstaculos = 80;

        int obstaculo_1x= spawn_obstaculos - 60, obstaculo_1y;
        int obstaculo_1x_anterior = 0;

        int obstaculo_2x= spawn_obstaculos - 30, obstaculo_2y;
        int obstaculo_2x_anterior = 0;

        int obstaculo_3x= spawn_obstaculos, obstaculo_3y;
        int obstaculo_3x_anterior = 0;

        int tecla;

        ///DESENHO DO CEN�RIO
        cout<<"-------------------------------------------------------------------------------------------------------------------";
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<"-------------------------------------------------------------------------------------------------------------------";



        while (true) { //esse la�o faz o jogo rodar para sempre
            debugVar = obstaculo_1y_min;
            ///POSICIONA O OBST�CULO 1
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
            ///REMOVE TRA�O ANTERIOR 1
            obstaculo_1y=1;
            while(obstaculo_1y<20){
                coord.X = obstaculo_1x_anterior;    coord.Y = obstaculo_1y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<" ";
                obstaculo_1y++;
            }

            ///POSICIONA O OBST�CULO 2
            obstaculo_2y=1;
            while(obstaculo_2y<20){
                coord.X = obstaculo_2x;    coord.Y = obstaculo_2y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                if(obstaculo_2y< obstaculo_2y_min || obstaculo_2y> obstaculo_2y_max){
                    cout<<char(219);
                } else {
                    cout<<" ";
                }

                obstaculo_2y++;
            }
            ///REMOVE TRA�O ANTERIOR 2
            obstaculo_2y=1;
            while(obstaculo_2y<20){
                coord.X = obstaculo_2x_anterior;    coord.Y = obstaculo_2y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<" ";
                obstaculo_2y++;
            }

            ///POSICIONA O OBST�CULO 3
            obstaculo_3y=1;
            while(obstaculo_3y<20){
                coord.X = obstaculo_3x;    coord.Y = obstaculo_3y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                if(obstaculo_3y< obstaculo_3y_min || obstaculo_3y> obstaculo_3y_max){
                    cout<<char(219);
                } else {
                    cout<<" ";
                }

                obstaculo_3y++;
            }
            ///REMOVE TRA�O ANTERIOR 3
            obstaculo_3y=1;
            while(obstaculo_3y<20){
                coord.X = obstaculo_3x_anterior;    coord.Y = obstaculo_3y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<" ";
                obstaculo_3y++;
            }

            ///POSICIONA O P�SSARO
            coord.X = bird_x;    coord.Y = bird_y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<char(190);
            ///REMOVE TRA�O ANTERIOR
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

            ///P�SSARO CAI 1 POSI��O SE N�O FOI PRESSIONADO PARA SUBIR

            ///OBST�CULO 1 AVAN�A UMA POSI��O PARA ESQUERDA
            obstaculo_1x_anterior = obstaculo_1x;
            obstaculo_1x--;

            if (obstaculo_1x <= 0){
                obstaculo_1x_anterior = 1;
                obstaculo_1x = spawn_obstaculos;
                obstaculo_1y_min = rand() % 15 + 1;
                obstaculo_1y_max = obstaculo_1y_min + 3 + (rand() % 6);
            }

            ///OBST�CULO 2 AVAN�A UMA POSI��O PARA ESQUERDA
            obstaculo_2x_anterior = obstaculo_2x;
            obstaculo_2x--;

            if (obstaculo_2x <= 0){
                obstaculo_2x_anterior = 1;
                obstaculo_2x = spawn_obstaculos;
                obstaculo_2y_min = rand() % 15 + 1;
                obstaculo_2y_max = obstaculo_2y_min + 3 + (rand() % 6);
            }

            ///OBST�CULO 3 AVAN�A UMA POSI��O PARA ESQUERDA
            obstaculo_3x_anterior = obstaculo_3x;
            obstaculo_3x--;

            if (obstaculo_3x <= 0){
                obstaculo_3x_anterior = 1;
                obstaculo_3x = spawn_obstaculos;
                obstaculo_3y_min = rand() % 15 + 1;
                obstaculo_3y_max = obstaculo_3y_min + 3 + (rand() % 6);
            }

            ///VERIFICA COLIS�O

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

            if (bird_x == obstaculo_2x){
                    if (bird_y < obstaculo_2y_min || bird_y > obstaculo_2y_max){
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

            if (bird_x == obstaculo_3x){
                    if (bird_y < obstaculo_3y_min || bird_y > obstaculo_3y_max){
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
