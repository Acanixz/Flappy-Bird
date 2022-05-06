/*Versão beta desenvolvida por Thiago Felski Pereira para disciplina de Algoritmos*/
#include <iostream>
#include <windows.h>
#include <conio.h> ///para o getch()
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
    //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INÍCIO DA TELA
    ///ALERTA: NÃO MODIFICAR O TRECHO DE CÓDIGO, ACIMA.

    /// VARIAVEIS DEBUG ABAIXO, REMOVER EM VERSÃO FINAL ///
    int debugVar = -1;
    /// FIM DAS VARIAVEIS DEBUG ///
    int score = 0;
    bool isDead = false;
    int bird_x=5, bird_y=10; // [Acanixz] Posição Y começa de cima e vai para baixo
    int obstaculo_x=100, obstaculo_y; // [Acanixz] Originalmente o obstaculo_x era 129
    int tecla;





    while (true) { //esse laço faz o jogo rodar para sempre
        system("cls"); // [Acanixz] Tela é limpa a cada frame novo, até o momento, ninguém morreu de epilepsia assim
        debugVar = bird_y;
        ///DESENHO DO CENÁRIO // [Acanixz] Originalmente tinha mais hifens, porém não era compativel com a resolução
        cout<<"----------------------------------------------------------------------------------------------------------------------";
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<"---------------------- DEBUG: " << debugVar << " --------- SCORE: " << score << " --------------------------------------------------------------------";

        ///POSICIONA O PÁSSARO
        coord.X = bird_x;    coord.Y = bird_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout<<char(190);

        ///POSICIONA O OBSTÁCULO

        obstaculo_y=1;
        while(obstaculo_y<20){
            coord.X = obstaculo_x;    coord.Y = obstaculo_y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            if(obstaculo_y<5 || obstaculo_y>7){
                cout<<char(219);
            } else {
                cout<<" ";
            }

            obstaculo_y++;
        }


        ///VERIFICA COLISÃO

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

        ///PÁSSARO CAI 1 POSIÇÃO SE NÃO FOI PRESSIONADO PARA SUBIR

        ///OBSTÁCULO AVANÇA UMA POSIÇÃO PARA ESQUERDA
        obstaculo_x--;

        ///TEMPO DE ESPERA
        Sleep(300);


    }





    return 0;
}
