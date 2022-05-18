/*Versão beta desenvolvida por Thiago Felski Pereira para disciplina de Algoritmos*/

/**Versão final desenvolvida por:
- Hérick Vitor Vieira Bittencourt
- Vinicius Henrique Ribeiro
- João Eduardo Gomes Müller
- Nicolas Henrique da Graça
*/

#include <iostream>
#include <windows.h>
#include <conio.h> ///para o getch()
#include <time.h>
#include <stdlib.h>

using namespace std;

/**
    F L A P B I R D (M2 Algoritmos)
    - Lembrando: não permitido o uso de funções e variáveis compostas como structs, vetores e matrizes
    - Corrigir os rastros (pássaro e obstáculos) [FEITO]
    - Implementar colisão [FEITO]
    - Implementar pontuação (mais um ponto para cada obstáculo superado) [FEITO]
    - Fazer 2 obstáculos simultâneos (obstaculo1 e obstaculo2) [A FAZER]
    - Deixar a pontuação visível durante todo o jogo [FEITO]
    - Definir marcos para acelerar a velocidade [FEITO]
*/

int main()
{
    srand(time(NULL)); /// Seed pseudo-aleatória

    int retryGame = 0; /// Loop principal
    int bestScore = 0; /// Armazenamento de high-score
    bool beatBestScore = false; /// Buffer high-score

    int difficultySelected = 0; /// Dificuldade
    string difficultyAux = ""; /// Buffer p/ cheats
    bool CheatsEnabled = false;
    bool CHEAT_Fly = false;
    bool CHEAT_SuperEasy = false;
    bool CHEAT_Speed = false;

    /// LISTA DE CHEATS
    /// "Arrays" = Gravidade desativada
    /// "Funcoes" = Modo super-facil
    /// "Atrasado" = Incremento de velocidade 2x
    ///

    ///ALERTA: NÃO MODIFICAR O TRECHO DE CÓDIGO, A SEGUIR.
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    COORD coord;
    ///ALERTA: NÃO MODIFICAR O TRECHO DE CÓDIGO, ACIMA.

    while (retryGame == 0 || retryGame == 1){
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(out, &cursorInfo);

        while(difficultySelected <= 0 || difficultySelected > 3){
            system("cls"); /// Limpar Game-Over

            /// DESENHO DA TELA INICIAL
            cout<<"-------------------------------------------------------------------------------------------------------------------";
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout<<"-------------------------------------------------------------------------------------------------------------------";

            coord.X = 50;    coord.Y = 2;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"Flappy Bird";

            coord.X = 40;    coord.Y = 3;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"So que terrivelmente escrito em C++";

            coord.X = 45;    coord.Y = 5;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"Escolha uma dificuldade:";

            coord.X = 50;    coord.Y = 7;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"1 - Facil";
            coord.Y = 8;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"2 - Medio";
            coord.Y = 9;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"3 - Dificil";

            coord.X = 25;    coord.Y = 19;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"Vinicius Ribeiro, Joao Eduardo, Herick Bittencourt e Nicolas Graca";

            coord.X = 55;    coord.Y = 20;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"2022";

            /// DESENHAR Avisos de Trapaça
            if (CHEAT_Fly == true){
                coord.X = 40;    coord.Y = 13;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<"CHEAT: Voar ativado";
            }
            if (CHEAT_SuperEasy == true){
                coord.X = 40;    coord.Y = 14;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<"CHEAT: Super-Facil ativado";
            }
            if (CHEAT_Speed == true){
                coord.X = 40;    coord.Y = 15;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<"CHEAT: O passaro esta atrasado pra defesa do codigo..";
            }

            coord.X = 55;    coord.Y = 11; /// Posicionar Cursor p/ escrita
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cin >> difficultyAux;

            /// LEITURA DE ESCOLHA
            if (difficultyAux == "1"){
                difficultySelected = 1;
            }
            if (difficultyAux == "2"){
                difficultySelected = 2;
            }
            if (difficultyAux == "3"){
                difficultySelected = 3;
            }

            if (difficultyAux == "Arrays"){
                if (CHEAT_Fly == false){ /// Liga/Desliga
                    CHEAT_Fly = true;
                } else {
                    CHEAT_Fly = false;
                }
            }
            if (difficultyAux == "Funcoes"){
                if (CHEAT_SuperEasy == false){ /// Liga/Desliga
                    CHEAT_SuperEasy = true;
                } else {
                    CHEAT_SuperEasy = false;
                }
            }
            if (difficultyAux == "Atrasado"){
                if (CHEAT_Speed == false){ /// Liga/Desliga
                    CHEAT_Speed = true;
                } else {
                    CHEAT_Speed = false;
                }
            }

            /// DETECTAR CHEATS EM GERAL
            if (CHEAT_Fly == true || CHEAT_SuperEasy == true || CHEAT_Speed == true){
                CheatsEnabled = true;
            } else {
                CheatsEnabled = false;
            }
        }
        system("cls"); /// Limpar Menu/Game Over

        /// DEFINIR PRIMEIROS OBSTACULOS
        int obstaculo_1y_min = rand() % 15 + 1;
        int obstaculo_2y_min = rand() % 15 + 1;
        int obstaculo_3y_min = rand() % 15 + 1;

        int tamanho_obstaculos; /// Baseado em dificuldade (ou cheats)
        int obstaculo_1y_max, obstaculo_2y_max, obstaculo_3y_max;
        switch (difficultySelected){
            case 1:
                tamanho_obstaculos = 7;
                break;

            case 2:
                tamanho_obstaculos = 5;
                break;

            case 3:
                tamanho_obstaculos = 3;
                break;
        }
        if (CHEAT_SuperEasy){
            tamanho_obstaculos = 15;
        }
        obstaculo_1y_max = obstaculo_1y_min + tamanho_obstaculos;
        obstaculo_2y_max = obstaculo_2y_min + tamanho_obstaculos;
        obstaculo_3y_max = obstaculo_3y_min + tamanho_obstaculos;

        /// Variaveis Gerais:
        /// PONTUAÇÃO/VELOCIDADE
        int score = 0;
        int speed = 0;
        int nextSpeedIncrement = score + 5;
        bool speedCapped = false;
        int runtimeSpeed = 300;
        int gravityAffector = 0;

        /// PASSARO
        bool isDead = false;
        int bird_x=5, bird_y=10; // Posição Y começa de cima e vai para baixo
        int bird_y_anterior = 9;
        int spawn_obstaculos = 90;

        /// OBSTACULOS
        int obstaculo_1x= spawn_obstaculos - 60, obstaculo_1y;
        int obstaculo_1x_anterior = 0;

        int obstaculo_2x= spawn_obstaculos - 30, obstaculo_2y;
        int obstaculo_2x_anterior = 0;

        int obstaculo_3x= spawn_obstaculos, obstaculo_3y;
        int obstaculo_3x_anterior = 0;

        /// TECLADO
        int tecla;

        ///DESENHO DO CENÁRIO
        cout<<"-------------------------------------------------------------------------------------------------------------------";
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<"-------------------------------------------------------------------------------------------------------------------";

        while (isDead == false) {
            ///POSICIONA OBSTÁCULO 1
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
            ///REMOVE TRAÇO ANTERIOR 1
            obstaculo_1y=1;
            while(obstaculo_1y<20){
                coord.X = obstaculo_1x_anterior;    coord.Y = obstaculo_1y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<" ";
                obstaculo_1y++;
            }

            ///POSICIONA O OBSTÁCULO 2
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
            ///REMOVE TRAÇO ANTERIOR 2
            obstaculo_2y=1;
            while(obstaculo_2y<20){
                coord.X = obstaculo_2x_anterior;    coord.Y = obstaculo_2y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<" ";
                obstaculo_2y++;
            }

            ///POSICIONA O OBSTÁCULO 3
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
            ///REMOVE TRAÇO ANTERIOR 3
            obstaculo_3y=1;
            while(obstaculo_3y<20){
                coord.X = obstaculo_3x_anterior;    coord.Y = obstaculo_3y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<" ";
                obstaculo_3y++;
            }

            ///POSICIONA O PÁSSARO
            coord.X = bird_x;    coord.Y = bird_y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<char(190);
            ///REMOVE TRAÇO ANTERIOR
            if (bird_y_anterior != bird_y) {
                coord.X = bird_x;    coord.Y = bird_y_anterior;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<" ";
            }

            ///DESENHA O SCORE
            coord.X = 50;    coord.Y = 20;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"SCORE: " << score;

            ///DESENHA O AVISO DE CHEAT (CASO EXISTA)
            if (CheatsEnabled == true){
                coord.X = 10;    coord.Y = 20;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<"PARTIDA COM CHEATS";
            }

            ///VERIFICA COMANDO DO JOGADOR
            if (kbhit()) { ///verifica se uma tecla foi pressionada
                tecla=getch(); //verifica comando do jogador
            }
            while(kbhit()) getch(); /// Solução para buffer não-intencional

            bird_y_anterior = bird_y;
            if ( tecla=='w' || tecla=='W' ){
                bird_y--;
                tecla='0';
            } else { /// W não pressionado
                if (CHEAT_Fly == false) { /// Gravidade ativada
                    if (speedCapped == false || (speedCapped == true && gravityAffector == 1)){
                        bird_y++;
                        gravityAffector = 0;
                    } else {
                        gravityAffector = 1;
                    }
                } else if ( tecla=='s' || tecla=='S' ){ /// Gravidade Desativada e S pressionado
                    bird_y++;
                    tecla='0';
                }
            }
            /**ACIMA: PÁSSARO CAI 1 POSIÇÃO SE NÃO FOI PRESSIONADO PARA SUBIR (Cheat desligado)
            PÁSSARO CAI 1 POSIÇÃO SE APERTOU *S* (Cheat ligado)
            */

            ///OBSTÁCULO 1 AVANÇA UMA POSIÇÃO PARA ESQUERDA
            obstaculo_1x_anterior = obstaculo_1x;
            obstaculo_1x--;

            /// REFAZER OBSTACULO SE PASSADO
            if (obstaculo_1x <= 0){
                obstaculo_1x_anterior = 1;
                obstaculo_1x = spawn_obstaculos;
                obstaculo_1y_min = rand() % 15 + 1;
                obstaculo_1y_max = obstaculo_1y_min + tamanho_obstaculos;
            }

            ///OBSTÁCULO 2 AVANÇA UMA POSIÇÃO PARA ESQUERDA
            obstaculo_2x_anterior = obstaculo_2x;
            obstaculo_2x--;

            /// REFAZER OBSTACULO SE PASSADO
            if (obstaculo_2x <= 0){
                obstaculo_2x_anterior = 1;
                obstaculo_2x = spawn_obstaculos;
                obstaculo_2y_min = rand() % 15 + 1;
                obstaculo_2y_max = obstaculo_2y_min + tamanho_obstaculos;
            }

            ///OBSTÁCULO 3 AVANÇA UMA POSIÇÃO PARA ESQUERDA
            obstaculo_3x_anterior = obstaculo_3x;
            obstaculo_3x--;

            /// REFAZER OBSTACULO SE PASSADO
            if (obstaculo_3x <= 0){
                obstaculo_3x_anterior = 1;
                obstaculo_3x = spawn_obstaculos;
                obstaculo_3y_min = rand() % 15 + 1;
                obstaculo_3y_max = obstaculo_3y_min + tamanho_obstaculos;
            }

            ///VERIFICA COLISÃO
            /// COLISÃO CHÃO E TETO
            if (bird_y >= 20 || bird_y <= 0){
                isDead = true;
            }

            /// COLISÃO OBSTACULO 1
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

            /// COLISÃO OBSTACULO 2
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

            /// COLISÃO OBSTACULO 3
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

            ///TEMPO DE ESPERA
            if (speedCapped == false) {
                runtimeSpeed = 300 - (50 * speed);
                if (CHEAT_Speed) {
                    runtimeSpeed = 300 - (100 * speed);
                }
                if (runtimeSpeed <= 50){ /// Limite de velocidade
                    runtimeSpeed = 50;
                    speedCapped = true;
                }
            } else{
                runtimeSpeed = 50; /// Limite maximo: 50ms
            }
            Sleep(runtimeSpeed);


        }
        /// GAME OVER, PASSARO MORREU
        do {
            /// DETECTAR PONTUAÇÃO
            if (score > bestScore) {
                beatBestScore = true;
            }

            system("cls"); /// Limpar tela de jogo
            /// DESENHO DA TELA DE GAME OVER
            cout<<"-------------------------------------------------------------------------------------------------------------------";
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout<<"-------------------------------------------------------------------------------------------------------------------";

            coord.X = 50;    coord.Y = 5;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"GAME OVER";

            coord.Y = 6;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"Score: " << score;

            coord.Y = 7;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"Best: " << bestScore;

            if (beatBestScore == true) { /// AVISO DE NOVO RECORDE
                coord.X = 48;    coord.Y = 10;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<"NOVO RECORDE!";
                if (CheatsEnabled){ /// AVISO DE RECORDE FALSO
                    coord.X = 25;    coord.Y = 11;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    cout<<".. so que nao, tenta nao usar arrays e funcoes na proxima vez ;)";
                }
            }

            coord.X = 50;   coord.Y = 15;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"Tentar Novamente?";

            coord.X = 40;    coord.Y = 17;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout<<"1 - Sim | 2 - Nao | 3 - Voltar ao menu";

            /// ENTRADA DE ESCOLHA PÓS-GAME OVER
            coord.X = 55;    coord.Y = 19;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

            Sleep(1000);
            while(kbhit()) getch(); /// Limpar entradas anteriores
            cursorInfo.bVisible = true; /// Cursor temporariamente visivel
            SetConsoleCursorInfo(out, &cursorInfo);

            cin >> retryGame;

            if (retryGame == 3) { /// VOLTAR AO MENU
                retryGame = 1;
                difficultySelected = -1;
            }
        } while (retryGame != 1 && retryGame != 2); ///
        /// SALVAR RECORDE
            if (score > bestScore && CheatsEnabled == false) {
                bestScore = score; /// TRAPAÇAS NÃO SALVAM
        }
        beatBestScore = false; /// COMPORTAMENTO DE RECORDE TERMINOU

        if (difficultySelected == -1){ /// DESATIVAR CHEATS APÓS VERIFICAÇÃO E RESETAR DIFICULDADE
            CHEAT_Fly = false;
            CHEAT_SuperEasy = false;
            CHEAT_Speed = false;
            CheatsEnabled = false;
            difficultySelected = 0;
        }
    }
    return 0;
}
