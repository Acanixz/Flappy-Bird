/*Vers�o beta desenvolvida por Thiago Felski Pereira para disciplina de Algoritmos*/
#include <iostream>
#include <windows.h>
#include <conio.h> ///para o getch()
///https://stackoverflow.com/questions/34474627/linux-equivalent-for-conio-h-getch

using namespace std;


/**
    F L A P B I R D (M2 Algoritmos)
    - Lembrando: n�o permitido o uso de fun��es e vari�veis compostas como structs, vetores e matrizes
    - Corrigir os rastros (p�ssaro e obst�culos)
    - Implementar colis�o
    - Implementar pontua��o (mais um ponto para cada obst�culo superado)
    - Fazer 2 obst�culos simult�neos (obstaculo1 e obstaculo2)
    - Deixar a pontua��o vis�vel durante todo o jogo
    - Definir marcos para acelerar a velocidade
*/



int main()
{
    int retryGame = 0;
    int bestScore = 0;
    while (retryGame == 0 || retryGame == 1){
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
        int obstaculo_y_min = 3, obstaculo_y_max = 9;
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
        int bird_x=5, bird_y=10; // [Acanixz] Posi��o Y come�a de cima e vai para baixo
        int obstaculo_x=100, obstaculo_y; // [Acanixz] Originalmente o obstaculo_x era 129
        int tecla;





        while (true) { //esse la�o faz o jogo rodar para sempre
            system("cls"); // [Acanixz] Tela � limpa a cada frame novo, at� o momento, ningu�m morreu de epilepsia assim
            debugVar = runtimeSpeed;
            ///DESENHO DO CEN�RIO // [Acanixz] Originalmente tinha mais hifens, por�m n�o era compativel com a resolu��o
            cout<<"-------------------------------------------------------------------------------------------------------------------";
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout<<"---------------------- DEBUG: " << debugVar << " --------- SCORE: " << score << " -----------------------------------------------------------------";

            ///POSICIONA O OBST�CULO

            obstaculo_y=1;
            while(obstaculo_y<20){
                coord.X = obstaculo_x;    coord.Y = obstaculo_y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                if(obstaculo_y< obstaculo_y_min || obstaculo_y> obstaculo_y_max){
                    cout<<char(219);
                } else {
                    cout<<" ";
                }

                obstaculo_y++;
            }

            ///POSICIONA O P�SSARO
            coord.X = bird_x;    coord.Y = bird_y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<char(190);

            ///VERIFICA COMANDO DO JOGADOR
            if (kbhit()) { ///verifica se uma tecla foi pressionada
                tecla=getch(); //verifica comando do jogador
            }

            if ( tecla=='w' || tecla=='W' ){
                bird_y--;
                tecla='0';
            } else {
                bird_y++;
            }

            ///P�SSARO CAI 1 POSI��O SE N�O FOI PRESSIONADO PARA SUBIR

            ///OBST�CULO AVAN�A UMA POSI��O PARA ESQUERDA
            obstaculo_x--;

            if (obstaculo_x <= 0){
                obstaculo_x = 100;
            }

            ///VERIFICA COLIS�O

            if (bird_y >= 20 || bird_y <= 0){
                isDead = true;
            }

            if (bird_x == obstaculo_x){
                    if (bird_y < obstaculo_y_min || bird_y > obstaculo_y_max){
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
                if (runtimeSpeed < 0){
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
            cout<<"\n\n\n\n\n\n\n\t\t\t\t\t\tTry Again?\n\t\t\t\t\t    1 - Yes\t2 - No\n";
            cout<<"-------------------------------------------------------------------------------------------------------------------\n\n\t\t\t\t\t\t     ";
            cin >> retryGame;
        } while (retryGame != 1 && retryGame != 2);

    }
    return 0;
}
