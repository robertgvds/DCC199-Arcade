/******************************************************************************

                    BATALHA NAVAL NO TERMINAL

1- Gerar tabuleiro 10x10
2- Gerar x quantidade de barcos de 3 tamanhos diferentes

Dificuldades:
    1 - Fácil:
        3 de Quatro Und.
        3 de Três Unid.
        2 de Duas Unid.
        2 de Uma Unid.

    2 - Médio: (Normal)
        1 de Quatro Unid.
        2 de Três Unid.
        3 de Duas Unid.
        4 de Uma Unid.

    3 - Difícil:
        1 de Três Unid.
        2 de Duas Unid.
        2 de Uma Unid.
    
    4 - Surpreenda-me:
        Uma quantidade aleatória de 1 a 10;

Pontuacao:
    Acertar 1 navio = 1 ponto
    Completar o navio = +1 ponto
    Completar o navio sozinho = +1 ponto

*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <thread>

// DEFINICAO DAS PARTES DA INTERFACE
#define PONTO '.'
#define BARRA "---"
#define BARRA1 '|'
#define BARRA2 "—"
#define BARCO 'X'
#define ERRO ' '
#define TAM 10
#define MARGEM TAM*TAM-30+(3*6)
#define spc "      "

using namespace std;

/*******************************************************************************************/
/*                                    BATALHA NAVAL                                        */

// ESTRUTURAS //
struct DadosCoordBarco // DADOS DOS BARCOS
{
    int coord[2] = {-1, -1}; // 0: Horizontal 1: Vertical
    bool atacado;
    int jogadorAtacante;
};

struct DadosJogador // DADOS DOS JOGADORES
{
    int NumJogador;
    char Nome[50] =  "          ";
    int pontos = 0;
};

// FUNCOES PARA AS ANIMACOES //
void sleep(int milliseconds) // DELAY
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void clear() // LIMPAR O TERMINAL
{
    #ifdef _WIN32
        system("cls");  // Comando para limpar o terminal no Windows
    #else
        system("clear");  // Comando para limpar o terminal em sistemas baseados em Unix (Linux, macOS)
    #endif
}

// INTERFACES //
void regras() // TUTORIAL DE DIGITACAO
{
    clear();

    for(int i = 0; i < MARGEM; i++)
        cout << "=";

    cout << endl << endl;
    cout << "                            BATALHA NAVAL - REGRAS" << endl << endl << endl;
    cout << "  Cada jogador deve jogar somente na sua vez, se ele acertar uma barco ele tem direito a\n";
    cout << "jogar novamente, se acertar de novo, ele ganhrá mais uma chance, até acabar errando ou o\n";
    cout << "jogo finalizar.\n\n\n";
    cout << "  Durante a digitação das coordenadas você deve escrever ou um dos códigos disponíveis ou\n";
    cout << "a coordenada desejada. Para os códigos você pode escrever tanto em maiúsculo quanto em mi-\n";
    cout << "núsculo.\n\n\n";
    cout << "  Para as coordenadas você pode escrever de quatro formas, por exemplo:\n\n";
    cout << "    A1 ou a1 ou 1A ou 1a\n\n";
    cout << "  Código oculto:\n\n";
    cout << "  - Digite (G) sempre que desejar ver o gabarito (onde estão os navios) do tabuleiro.\n\n";


    for(int i = 0; i < MARGEM; i++)
        cout << "=";
    
    cout << endl;
}

void comoJogar() // EXPLICACAO DO JOGO
{
    clear();

    for(int i = 0; i < MARGEM; i++)
        cout << "=";

    cout << endl << endl;
    cout << "                          BATALHA NAVAL - COMO JOGAR" << endl << endl << endl << endl;
    cout << "  O jogo Batalha Naval é um jogo de tabuleiro no qual dois jogadores competem para afun-\n";
    cout << "dar a frota inimiga. Nesta versão do jogo, são gerados navios aleatoriamente em um tabu-\n";
    cout << "leiro e os jogadores  tentam adivinhar as  coordenadas dos navios para atacá-los.\n\n\n";
    cout << "  O objetivo é afundar todos os navios. Cada tipo de acerto gera uma pontuação diferente.\n";
    cout << "Ganha quem tiver mais pontos quando toda a frota afundar. Os navios podem ter uma, duas,\n";
    cout << "três ou quatro unidades, além de poderem estar na vertical ou na horizontal.\n\n\n";
    cout << "  Existem 4 níveis de dificuldade, sendo que o mais fácil possui navios maiores e em ma-\n";
    cout << "ior quantidade, enquanto o difícil apresenta navios menores e em menor quantidade. O ní-\n";
    cout << "vel “Surpreenda-me” gera uma quantidade aleatória de navios, podendo acarretar de um jo-\n";
    cout << "go médio a um jogo difícil.\n\n\n\n";


    for(int i = 0; i < MARGEM; i++)
        cout << "=";

    cout << "\n\n    Digite qualquer tecla para ler mais: ";
    char res; cin >> res;

    regras();
}

int inicio(bool animacao) // ANIMACAO/TELA INICIAL
{   
    clear();

    char res;
    char spcInicio[10] = "    ";

    int a, b, c;
    
    if(animacao)
    {
        a = 0; b = 0; c = 0;
    }
    else
    {
        a = MARGEM-61; b = MARGEM-60; c = 1;
    }

    while(c < 2)
    {
        char spcTempo[MARGEM/2] = "    ";
        
        if(!animacao)
            strcpy(spcTempo, "                   ");

        while(a < MARGEM-60)
        {

            for(int i = 0; i < MARGEM; i++)
                cout << "=";
            cout << endl << endl << endl;

            cout << spcInicio << " ____    __   ____   __    __    _   _    __      _  _    __  _  _  __    __   \n";
            cout << spcInicio << "(  _ \\  /__\\ (_  _) /__\\  (  )  ( )_( )  /__\\    ( \\( )  /__\\( \\/ )/__\\  (  )  \n";
            cout << spcInicio << " ) _ < /(__)\\  )(  /(__)\\  )(__  ) _ (  /(__)\\    )  (  /(__)\\\\  //(__)\\  )(__ \n";
            cout << spcInicio << "(____/(__)(__)(__)(__)(__)(____)(_) (_)(__)(__)  (_)\\_)(__)(__)\\/(__)(__)(____)\n";

            cout << endl << endl << endl;

            cout << spcTempo << "      _~      " << spc << "      _~      " << spc << "      _~      \n";
            cout << spcTempo << "   _~)_)_~    " << spc << "   _~)_)_~    " << spc << "   _~)_)_~    \n";
            cout << spcTempo << "  )_))_))_)   " << spc << "  )_))_))_)   " << spc << "  )_))_))_)   \n";
            cout << spcTempo << "  _!__!__!_   " << spc << "  _!__!__!_   " << spc << "  _!__!__!_   \n";
            cout << spcTempo << "  \\______t/   " << spc << "  \\______t/   " << spc << "  \\______t/   \n";
            cout << "   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

            cout << endl << endl << endl;

            cout << spcInicio << "Para jogar escolha a dificuldade: \n\n";
            cout << spcInicio << "   1 - Facil\n";
            cout << spcInicio << "   2 - Medio\n";
            cout << spcInicio << "   3 - Dificil                                    Digite (C) pra saber como jogar.\n";
            cout << spcInicio << "   4 - Surpreenda-me                                         Digite (S) para sair.\n";

            cout << endl << endl;

            for(int i = 0; i < MARGEM; i++)
                cout << "=";
            cout << endl << endl;

            if(!(a > 12 && c == 1))
            {
                strcat(spcTempo, " ");
                sleep(50);
            }

            if(!(a == MARGEM-61 && c == 1))
                clear();

            a++;
        }

        while(b < MARGEM-60 && c != 1)
        {

            for(int i = 0; i < MARGEM; i++)
                cout << "=";
            cout << endl << endl << endl;

            cout << spcInicio << " ____    __   ____   __    __    _   _    __      _  _    __  _  _  __    __   \n";
            cout << spcInicio << "(  _ \\  /__\\ (_  _) /__\\  (  )  ( )_( )  /__\\    ( \\( )  /__\\( \\/ )/__\\  (  )  \n";
            cout << spcInicio << " ) _ < /(__)\\  )(  /(__)\\  )(__  ) _ (  /(__)\\    )  (  /(__)\\\\  //(__)\\  )(__ \n";
            cout << spcInicio << "(____/(__)(__)(__)(__)(__)(____)(_) (_)(__)(__)  (_)\\_)(__)(__)\\/(__)(__)(____)\n";

            cout << endl << endl << endl;

            cout << spcTempo << "     ~_       " << spc << "     ~_       " << spc << "     ~_       \n";
            cout << spcTempo << "   ~_(_(~_    " << spc << "   ~_(_(~_    " << spc << "   ~_(_(~_    \n";
            cout << spcTempo << "  (_((_((_(   " << spc << "  (_((_((_(   " << spc << "  (_((_((_(   \n";
            cout << spcTempo << "  _!__!__!_   " << spc << "  _!__!__!_   " << spc << "  _!__!__!_   \n";
            cout << spcTempo << "  \\t______/   " << spc << "  \\t______/   " << spc << "  \\t______/   \n";
            cout << "   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

            cout << endl << endl << endl;

            cout << spcInicio << "Para jogar escolha a dificuldade: \n\n";
            cout << spcInicio << "   1 - Facil\n";
            cout << spcInicio << "   2 - Medio\n";
            cout << spcInicio << "   3 - Dificil                                    Digite (C) pra saber como jogar.\n";
            cout << spcInicio << "   4 - Surpreenda-me                                         Digite (S) para sair.\n";

            cout << endl << endl;

            for(int i = 0; i < MARGEM; i++)
                cout << "=";
            cout << endl << endl;


            spcTempo[4+a-b] = '\0';
            sleep(50);

            clear();

            b++;
        }

        a = 0; b = 0;
        c++;
    }

    cout << spcInicio << "Digite a dificuldade: ";
    cin >> res;

    while(!(res == '1' || res == '2' || res == '3' || res == '4' || res == 'S' || res == 's' || res == 'C' || res == 'c'))
    {
        cout << spcInicio << "Digite um valor válido: ";
        cin >> res;
    }

    if(res == 'S' || res == 's')
        return 0;
    
    if(res == 'C' || res == 'c')
    {
        clear();
        comoJogar();
        cout << endl << spcInicio << "Digite qualquer tecla para voltar: ";
        cin >> res;

        return -1;
    }
    
    return (int)(res - '0');
}

int definicaoJogadores(DadosJogador jogador[], bool multiplayer) // ESCOLHA DOS NOMES DO JOGADORES
{
    char nome[50] = "          ";
    char spcInicio[10] = "    ";

    char spcTempo[MARGEM/2] = "                ";

    cin.ignore();

    for(int i = 0; i <= 2; i++)
    {
        int a = 0;

        while(a < 5)
        {
            sleep(50);
            clear();

            for(int i = 0; i < MARGEM; i++)
                cout << "=";
            cout << endl << endl << endl;

            cout << spcInicio << " ____    __   ____   __    __    _   _    __      _  _    __  _  _  __    __   \n";
            cout << spcInicio << "(  _ \\  /__\\ (_  _) /__\\  (  )  ( )_( )  /__\\    ( \\( )  /__\\( \\/ )/__\\  (  )  \n";
            cout << spcInicio << " ) _ < /(__)\\  )(  /(__)\\  )(__  ) _ (  /(__)\\    )  (  /(__)\\\\  //(__)\\  )(__ \n";
            cout << spcInicio << "(____/(__)(__)(__)(__)(__)(____)(_) (_)(__)(__)  (_)\\_)(__)(__)\\/(__)(__)(____)\n";

            cout << endl << endl << endl;

            cout << spcTempo << "      _~      " << spc << "      _~      " << spc << "      _~      \n";
            cout << spcTempo << "   _~)_)_~    " << spc << "   _~)_)_~    " << spc << "   _~)_)_~    \n";
            cout << spcTempo << "  )_))_))_)   " << spc << "  )_))_))_)   " << spc << "  )_))_))_)   \n";
            cout << spcTempo << "  _!__!__!_   " << spc << "  _!__!__!_   " << spc << "  _!__!__!_   \n";
            cout << spcTempo << "  \\______t/   " << spc << "  \\______t/   " << spc << "  \\______t/   \n";
            cout << "   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

            cout << endl << endl << endl << endl;

            cout << spcInicio << "Digite os nomes dos Jogadores: \n\n";
            cout << spcInicio << "   Jogador 1: " << jogador[0].Nome << endl;
            cout << spcInicio << "   Jogador 2: " << jogador[1].Nome << endl;
            cout << spcInicio << "                                                       Digite (S) para sair.\n";

            cout << endl << endl;

            for(int i = 0; i < MARGEM; i++)
                cout << "=";
            cout << endl << endl;

            strcat(spcTempo, " ");
            a++;
        }

        int num = 2;
        if(!multiplayer)
            num = 1;

        if(i < num)
        {
            cout << spcInicio << "Digite o nome do jogador: ";
            cin.getline(nome, 50);

            if((nome[0] == 'S' || nome[0] == 's') && nome[1] == '\0')
                return 0;

            strcpy(jogador[i].Nome, nome);
        }
        else
            sleep(1000);
    }

    return 1;
}

void tabuleiroImprimir(char tabuleiro[][TAM], DadosJogador jogador[], int dificuldade) // IMPRESSÃO DO TABULEIRO
{
    clear();

    for(int i = 0; i < MARGEM; i++)
        cout << "=";

    cout << "\n\n                              BATALHA NAVAL - TABULEIRO" << endl << endl << endl;

    char coordLetras[270] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    cout << spc;
    for(int i = 1; i < TAM+1; i++)
        cout << "   " << i;

    for(int i = 0; i < TAM; i++) {
        cout << endl << spc << coordLetras[i] << " ";

        for(int j = 0; j < TAM; j++) {
            if(j != 0)
                cout << BARRA1;

            cout << " " << tabuleiro[i][j] << " ";
        }

        switch(i) {
        case 0:
            cout << spc << "Dificuldade: " << dificuldade;
            break;
        case 1:
            cout << spc << "Pontuação de " << jogador[0].Nome << ": " << jogador[0].pontos;
            break;
        case 4:
            cout << spc << "culdade do jogo, digite (N).";
            break;
        case 5:
            cout << spc << "Caso esteja com dúvidas de ";
            break;
        case 7:
            cout << spc << "gitação, digite (R).";
            break;
        case 8:
            cout << spc << "-----------------------------";
            break;
        case TAM-1:
            cout << spc << "Digite (S) para sair do jogo";
        default:
            break;;
        }

        cout << endl << spc << "  ";
        if(i < TAM-1)
            for(int j = 0; j < TAM; j++) {
                if(j != 0)
                    cout << BARRA1;

                cout << BARRA;
            }

        switch(i) {
        case 1:
            cout << spc << "Pontuação de " << jogador[1].Nome << ": " << jogador[1].pontos;
            break;
        case 2:
            cout << spc << "-----------------------------";
            break;
        case 3:
            cout << spc << "Para mudar o nível de difi-";
            break;
        case 5:
            cout << spc << "como jogar digite (C).";
            break;
        case 6:
            cout << spc << "Para saber as regras de di-";
            break;
        case TAM-1:
            for(int j = 0; j < TAM; j++) {
                if(j != 0)
                    cout << BARRA1;

                cout << BARRA;
            }
            break;
        default:
            break;;
        }
    }

    cout << endl << endl;

    for(int i = 0; i < MARGEM; i++)
        cout << "=";

    cout << endl << endl;
}

void bomba(int num) // ANIMACAO DE UM NAVIO DESTRUIDO
{
    for(int i = 0; i < 2; i++)
    {
        clear();

        for(int i = 0; i < MARGEM; i++)
            cout << "=";
        cout << endl << endl << endl;

        cout << "     ____    __   ____   __    __    _   _    __      _  _    __  _  _  __    __   \n";
        cout << "    (  _ \\  /__\\ (_  _) /__\\  (  )  ( )_( )  /__\\    ( \\( )  /__\\( \\/ )/__\\  (  )  \n";
        cout << "     ) _ < /(__)\\  )(  /(__)\\  )(__  ) _ (  /(__)\\    )  (  /(__)\\\\  //(__)\\  )(__ \n";
        cout << "    (____/(__)(__)(__)(__)(__)(____)(_) (_)(__)(__)  (_)\\_)(__)(__)\\/(__)(__)(____)\n";

        cout << endl << endl << endl << endl << endl;

        if(i == 0)
        {
            cout << endl << endl << endl << endl << endl << endl;
            cout << "                                  " << "      _~      \n";
            cout << "                                  " << "   _~)_)_~    \n";
            cout << "                                  " << "  )_))_))_)   \n";
            cout << "                                  " << "  _!__!__!_   \n";
            cout << "                                  " << "  \\______t/   \n";
        }

        if(i == 1)
        {
            cout << "                           " << "     _.-^^---....,,--       \n";
            cout << "                           " << " _--                  --_   \n";
            cout << "                           " << "<           BOOM!        >)\n";
            cout << "                           " << "|                         |\n";
            cout << "                           " << " \\._                   _./ \n";
            cout << "                           " << "    ```--. . , ; .--'''    \n";
            cout << "                           " << "          | |   |          \n";
            cout << "                           " << "       .-=||  | |=-.       \n";
            cout << "                           " << "       `-=#$%&%$#=-'       \n";
            cout << "                           " << "          | ;  :|          \n";
            cout << "                           " << "     _____L_____J____.     \n";
        }

        if(num != 0)
        {
            cout << "\n                        Parabens, o " << num << "o barco destruido!\n\n\n";

            for(int i = 0; i < MARGEM; i++)
                cout << "=";
            cout << endl << endl;

            sleep(200);

            if(i == 1)
                sleep(1000);
        }
        else
        {
            cout << endl << endl << endl << endl;

            for(int i = 0; i < MARGEM; i++)
                cout << "=";
            cout << endl << endl;
            sleep(300);
        }
    }
}

void bombinha(char tabuleiro[][TAM], DadosJogador jogador[], int dificuldade, int coord[]) // ANIMACAO NO TABULEIRO
{
    sleep(1000);
    tabuleiro[coord[0]][coord[1]] =  '*';
    tabuleiroImprimir(tabuleiro, jogador, dificuldade);
    sleep(800);
    tabuleiro[coord[0]][coord[1]] =  '@';
    tabuleiroImprimir(tabuleiro, jogador, dificuldade);
    sleep(500);
    tabuleiro[coord[0]][coord[1]] =  '#';
    tabuleiroImprimir(tabuleiro, jogador, dificuldade);
    sleep(200);
    tabuleiro[coord[0]][coord[1]] =  BARCO;
    tabuleiroImprimir(tabuleiro, jogador, dificuldade);
}

void final(DadosJogador jogador[]) // TELA FINAL
{
    clear();

    char ganhador[50];
    bool empate = false;

    if(jogador[0].pontos > jogador[1].pontos)
       strcpy(ganhador, jogador[0].Nome);
    else
    {
        if(jogador[1].pontos > jogador[0].pontos)
            strcpy(ganhador, jogador[1].Nome);
        else
            empate = true;
    }

    for(int i = 0; i < MARGEM; i++)
        cout << "=";
    cout << endl;

    if(!empate)
    {
        cout << "                   _____|\\                    \n";
        cout << "              _.--| R S |:                    \n";
        cout << "             <____|.----||                    \n";
        cout << "                    .---''---,                 \n";
        cout << "                     ;..__..'    _...            \n";
        cout << "                   ,'/  ;|/..--''    \\         \n";
        cout << "                 ,'_/.-/':            :        " << " __        __        __   _/_       __ \n";
        cout << "            _..-'''/  /  |  \\    \\   _|/|      " << "|__)  /\\  |__)  /\\  |__) |__  |\\ | /__` \n";
        cout << "           \\      /-./_ \\;   \\    \\,;'   \\     " << "|    /~~\\ |  \\ /~~\\ |__) |___ | \\| .__/ \n";
        cout << "           ,\\    / \\:  `:\\    \\   //    `:`.    \n";
        cout << "         ,'  \\  /-._;   | :    : ::    ,.   .   \n";
        cout << "       ,'     ::   /`-._| |    | || ' :  `.`.)    " << ganhador << " foi o ganhador da partida!\n";
        cout << "    _,'       |;._:: |  | |    | `|   :    `'  \n";
        cout << "  ,'   `.     /   |`-:_ ; |    |  |  : \\         \n";
        cout << "  `--.   )   /|-._:    :          |   \\ \\      \n";
        cout << "     /  /   :_|   ;`-._;   __..--';    : :     \n";
        cout << "    /  (    ;|;-./_  _/.-:'o |   /     ' |     \n";
        cout << "   /  , \\._/_/_./--''/_|:|___|_,'        |     \n";
        cout << "  :  /   `'-'--'----'---------'          |     \n";
        cout << "  | :     O ._O   O_. O ._O   O_.      ; ;     \n";
        cout << "  : `.      //    //    //    //     ,' /      \n";
        cout << "~~~`.______//____//____//____//_______,'~      \n";
        cout << "          //    //~   //    //                        " << "Pontuacao de " << jogador[0].Nome << ": " << jogador[0].pontos << endl;
        cout << "   ~~   _//   _//   _// ~ _//     ~                   " << "Pontuacao de " << jogador[1].Nome << ": " << jogador[1].pontos << endl;
        cout << " ~     / /   / /   / /   / /  ~      ~~        \n";
        cout << "      ~~~   ~~~   ~~~   ~~~                    \n";
    }
    else
    {
        cout << "                   _____|\\                    \n";
        cout << "              _.--| R S |:                    \n";
        cout << "             <____|.----||                    \n";
        cout << "                    .---''---,                 \n";
        cout << "                     ;..__..'    _...            \n";
        cout << "                   ,'/  ;|/..--''    \\         \n";
        cout << "                 ,'_/.-/':            :        " << " ___        __       ___  ___ \n";
        cout << "            _..-'''/  /  |  \\    \\   _|/|      " << "|__   |\\/| |__)  /\\   |  |__ \n";
        cout << "           \\      /-./_ \\;   \\    \\,;'   \\     " << "|___  |  | |    /~~\\  |  |___\n";
        cout << "           ,\\    / \\:  `:\\    \\   //    `:`.    \n";
        cout << "         ,'  \\  /-._;   | :    : ::    ,.   .  " << "Os jogadores emparatam na partida. :(\n";
        cout << "       ,'     ::   /`-._| |    | || ' :  `.`.) \n";
        cout << "    _,'       |;._:: |  | |    | `|   :    `'  \n";
        cout << "  ,'   `.     /   |`-:_ ; |    |  |  : \\         \n";
        cout << "  `--.   )   /|-._:    :          |   \\ \\      \n";
        cout << "     /  /   :_|   ;`-._;   __..--';    : :     \n";
        cout << "    /  (    ;|;-./_  _/.-:'o |   /     ' |     \n";
        cout << "   /  , \\._/_/_./--''/_|:|___|_,'        |     \n";
        cout << "  :  /   `'-'--'----'---------'          |     \n";
        cout << "  | :     O ._O   O_. O ._O   O_.      ; ;     \n";
        cout << "  : `.      //    //    //    //     ,' /      \n";
        cout << "~~~`.______//____//____//____//_______,'~      \n";
        cout << "          //    //~   //    //                        " << "Pontuacao de " << jogador[0].Nome << ": " << jogador[0].pontos << endl;
        cout << "   ~~   _//   _//   _// ~ _//     ~                   " << "Pontuacao de " << jogador[1].Nome << ": " << jogador[1].pontos << endl;
        cout << " ~     / /   / /   / /   / /  ~      ~~        \n";
        cout << "      ~~~   ~~~   ~~~   ~~~                    \n";
    }

    for(int i = 0; i < MARGEM; i++)
        cout << "=";
    cout << endl;
}

// ORGANIZACAO DAS RESPOSTAS //
void jogadaPC(char tabuleiro[][TAM], char gabarito[][TAM], char res[4]) // JOGADA PC
{
    int letra = rand()%10;
    int num = rand()%10;

    int aux = 0;
    while(tabuleiro[num][letra] != PONTO)
    {
        letra = rand()%10;
        num = rand()%10;

        if(aux > 1000)
        {
            for(int i = 0; i < TAM; i++)
                for(int j = 0; j < TAM; j++)
                    if(gabarito[i][j] == BARCO && tabuleiro[i][j] != BARCO)
                    {
                        res[0] = i;
                        res[1] = j;

                        return;
                    }
        }
        aux++;
    }

    res[0] = letra;
    res[1] = num;
}

int conversao(char tabuleiro[][TAM], char gabarito[][TAM], char Res[4], int coord[], char nome[100]) // GERACAO DAS RESPOSTAS
{
    if(strcmp(nome, "Computador") == 0)
    {
        jogadaPC(tabuleiro, gabarito, Res);

        coord[0] = Res[0];
        coord[1] = Res[1];

        return 1;
    }
    else
        cin >> Res;

    char res[4] = {'\0', '\0', '\0', '\0'};
    res[0] = Res[0]; res[1] = Res[1]; res[2] = Res[2];

    coord[0] = -1; // 0: Horizontal
    coord[1] = -1; // 1: Vertival

    // return 0: erro
    // return 1: jogada
    // return 2: regras
    // return 3: sair
    // return 4: voltar
    // return 5: gabarito
    // return 6: nivel de dificuldade

    if(res[1] == '\0')
        switch (res[0])
        {
        case 'R': case 'r': // REGRAS
            return 2;
            break;
        case 'S': case 's': // SAIR
            return 3;
            break;
        case 'V': case 'v': // VOLTAR
            return 4;
            break;
        case 'G': case 'g': // GABARITO
            return 5;
            break;
        case 'N': case 'n': // NIVEL
            return 6;
            break;
        case 'C': case 'c':
            return 7;
            break;
        default:            // ERRO
            return 0;
            break;
        }

    if(res[0] == '1' && res[1] == '0' && ((res[2] >= 'A' && res[2] <= 'J') || (res[2] >= 'a' && res[2] <= 'j')))
    {
        if(res[2] >= 'a' && res[2] <= 'j')
            res[2] = res[2] - 32; // Converter para maiuscula
        coord[0] = res[2] - 'A';
        coord[1] = 9;

        if(tabuleiro[coord[0]][coord[1]] != PONTO)
            return 0;
        return 1; // JOGADA
    }
    if(res[1] == '1' && res[2] == '0' && ((res[0] >= 'A' && res[0] <= 'J') || (res[0] >= 'a' && res[0] <= 'j')))
    {
        if(res[0] >= 'a' && res[0] <= 'j')
            res[0] = res[0] - 32; // Converter para maiuscula
        coord[0] = res[0] - 'A';
        coord[1] = 9;

        if(tabuleiro[coord[0]][coord[1]] != PONTO)
            return 0;
        return 1; // JOGADA
    }

    if(res[2] == '1')
    {
        return 0;
    }

    for(int i = 0; i < 2; i++)
    {
            if(res[1] == '\0' || res[2] == '\0') {
                if((res[i] >= 'A' && res[i] <= 'J') || (res[i] >= 'a' && res[i] <= 'j'))
                {
                    if(res[i] >= 'a' && res[i] <= 'j')
                        res[i] = res[i] - 32; // Converter para maiuscula

                    coord[0] = res[i] - 'A';
                }
                else
                {
                    if(res[i] >= '1' && res[i] <= '9')
                        coord[1] = res[i] - '1';
                }
            }
            else
                return 0;
    }

    if((coord[0] >= 0 && coord[1] >= 0) && (tabuleiro[coord[0]][coord[1]] == PONTO))
        return 1; // JOGADA

    return 0;
}

// CRIACAO DOS BARCOS //
bool validacao(char tabuleiro[][TAM], char gabarito[][TAM], int coordH, int coordV) // SE EH VALIDO
{
    if ((coordH >= 0 && coordH < TAM) && (coordV >= 0 && coordV < TAM)) //Se esta dentro da matriz
        if (tabuleiro[coordH][coordV] == PONTO) //Se esta vazia
        {
            for (int i = -1; i <= 1; i++) //Se ha X nas laterais e diagonais
                for (int j = -1; j <= 1; j++)
                    if ((coordH + i >= 0 && coordH + i < TAM) && (coordV + j >= 0 && coordV + j < TAM))
                        if (gabarito[coordH + i][coordV + j] == BARCO)
                            return false; // NAO VALIDO
            return true; // VALIDO
        }
    return false; // NAO VALIDO
}

void escolhaBarco(int tamBarco,  char tabuleiro[][TAM], char gabarito[][TAM], int barco[4], DadosCoordBarco barcoTam[][4], int numBarco) // GERA��O DE COORDENADAS
{
    int coordH = rand()%10;
    int coordV = rand()%10;
    int orientacao = rand()%2;

    if(orientacao == 0) // Horizontal
    {
        while( !validacao(tabuleiro, gabarito, coordH, coordV + barco[0]) ||
               !validacao(tabuleiro, gabarito, coordH, coordV + barco[1]) ||
               !validacao(tabuleiro, gabarito, coordH, coordV + barco[2]) ||
               !validacao(tabuleiro, gabarito, coordH, coordV + barco[3])) // Enquanto nao for valido
        {
            coordH = rand()%100;
            coordV = rand()%100;
        }

        for(int i = 0; i < tamBarco; i++) // Cadastrando as coordenadas
        {
            gabarito[coordH][coordV+i] = BARCO;

            barcoTam[numBarco][i].coord[0] = coordH;
            barcoTam[numBarco][i].coord[1] = coordV+i;
        }
    }
    else // Vertical
    {
        while( !validacao(tabuleiro, gabarito, coordH + barco[0], coordV) ||
               !validacao(tabuleiro, gabarito, coordH + barco[1], coordV) ||
               !validacao(tabuleiro, gabarito, coordH + barco[2], coordV) ||
               !validacao(tabuleiro, gabarito, coordH + barco[3], coordV)) // Enquanto nao for valido
        {
            coordH = rand()%100;
            coordV = rand()%100;
        }

        for(int i = 0; i < tamBarco; i++) // Cadastrando as coordenadas
        {
            gabarito[coordH+i][coordV] = BARCO;

            barcoTam[numBarco][i].coord[0] = coordH+i;
            barcoTam[numBarco][i].coord[1] = coordV;
        }
    }
}

void criacao(char tabuleiro[TAM][TAM], char gabarito[TAM][TAM], DadosCoordBarco barcoTam[][4], int numBarcos, int dificuldade) // CRIA��O DOS NAVIOS
{

    int barco[4][4] = {{0, 1, 2, 3},  // NAVIO DE 4
                       {0, 1, 2, 0},  // NAVIO DE 3
                       {0, 1, 0, 0},  // NAVIO DE 2
                       {0, 0, 0, 0}}; // NAVIO DE 1

    if(dificuldade == 4)
        if(numBarcos <= 5)
            dificuldade = 5;

    switch(dificuldade)
    {
    case 1: // FACIL
        for(int i = 0; i < 10; i++)
        {
            switch(i)
            {
            case 0 ... 2:
                escolhaBarco(4, tabuleiro, gabarito, barco[0], barcoTam, i);
                break;
            case 3 ... 5:
                escolhaBarco(3, tabuleiro, gabarito, barco[1], barcoTam, i);
                break;
            case 6 ... 7:
                escolhaBarco(2, tabuleiro, gabarito, barco[2], barcoTam, i);
                break;
            case 8 ... 9:
                escolhaBarco(1, tabuleiro, gabarito, barco[3], barcoTam, i);
                break;
            }
        }
        break;
    case 2: case 4: // MEDIO OU SURPREENDA-ME NO MEDIO
        for(int i = 0; i < numBarcos; i++)
        {
            switch(i)
            {
            case 0:
                escolhaBarco(4, tabuleiro, gabarito, barco[0], barcoTam, i);
                break;
            case 1 ... 2:
                escolhaBarco(3, tabuleiro, gabarito, barco[1], barcoTam, i);
                break;
            case 3 ... 5:
                escolhaBarco(2, tabuleiro, gabarito, barco[2], barcoTam, i);
                break;
            case 6 ... 9:
                escolhaBarco(1, tabuleiro, gabarito, barco[3], barcoTam, i);
                break;
            }
        }
        break;
    case 3: case 5: // DIFICIL OU SURPREENDA-ME NO DIFICIL
        for(int i = 0; i < 5; i++)
        {
            switch(i)
            {
            case 0:
                escolhaBarco(3, tabuleiro, gabarito, barco[1], barcoTam, i);
                break;
            case 1 ... 2:
                escolhaBarco(2, tabuleiro, gabarito, barco[2], barcoTam, i);
                break;
            case 3 ... 4:
                escolhaBarco(1, tabuleiro, gabarito, barco[3], barcoTam, i);
                break;
            }
        }
        break;
    }

}

// JOGADABILIDADE //
int jogada(int num, char tabuleiro[][TAM], int coord[], DadosCoordBarco barcoTam[][4], DadosJogador jogador[], int barcosDestruidos[], int NumBarcoDestruido[], int dificuldade, int numBarcos)
{
    bool acerto = true;

    while(acerto)
    {
        tabuleiro[coord[0]][coord[1]] =  ERRO;

        acerto = false;
        for(int i = 0; i < numBarcos; i++)
        {
            if(barcosDestruidos[i] == -1)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(barcoTam[i][j].coord[0] == coord[0] && barcoTam[i][j].coord[1] == coord[1])
                    {
                        acerto = true;
                        jogador[num].pontos++;
                        NumBarcoDestruido[1]++;

                        barcoTam[i][j].atacado = true;
                        barcoTam[i][j].jogadorAtacante = jogador[num].NumJogador;

                        bomba(NumBarcoDestruido[1]);

                        bombinha(tabuleiro, jogador, dificuldade, coord);

                        if( (barcoTam[i][0].atacado == true || barcoTam[i][0].coord[0] == -1) &&
                            (barcoTam[i][1].atacado == true || barcoTam[i][1].coord[0] == -1) &&
                            (barcoTam[i][2].atacado == true || barcoTam[i][2].coord[0] == -1) &&
                            (barcoTam[i][3].atacado == true || barcoTam[i][3].coord[0] == -1))
                            {

                                tabuleiroImprimir(tabuleiro, jogador, dificuldade);
                                jogador[num].pontos++;

                                if( (barcoTam[i][0].jogadorAtacante == jogador[num].NumJogador || barcoTam[i][0].coord[0] == -1) &&
                                    (barcoTam[i][1].jogadorAtacante == jogador[num].NumJogador || barcoTam[i][1].coord[0] == -1) &&
                                    (barcoTam[i][2].jogadorAtacante == jogador[num].NumJogador || barcoTam[i][2].coord[0] == -1) &&
                                    (barcoTam[i][3].jogadorAtacante == jogador[num].NumJogador || barcoTam[i][3].coord[0] == -1))
                                    jogador[num].pontos++;

                                barcosDestruidos[i] = 0;
                                NumBarcoDestruido[0]++;

                            }

                        cout << "Parabens, " <<  jogador[num].Nome << "! Voce acertou uma parte de um navio, agora tera mais uma chance.\n\n";
                        cout << "Sua vez, " <<  jogador[num].Nome << ". Digite uma coordenada ou um comando: ";

                        return 0;
                    }

                }
            }
        }
    }

    return 1;
}

bool fim(char tabuleiro[][TAM], int barcosDestruidos[], int numBarcos) // FINALIZACAO DO LOOP
{
    int fim = 0, fim2 = 0;

    for(int i = 0; i < numBarcos; i++)
    {
        if(barcosDestruidos[i] == 0)
            fim++;
    }

    for(int i = 0; i < TAM; i++)
        for(int j = 0; j < TAM; j++)
            if(tabuleiro[i][j] == PONTO)
                fim2++;

    if(fim == numBarcos || fim2 == 0)
        return true;
    else
        return false;
}

// main() do jogo BATALHA NAVAL
int BATALHA_NAVAL()
{

    srand(time(NULL));

    char tabuleiro[TAM][TAM];
    char gabarito[TAM][TAM];

    for(int i = 0; i < TAM; i++)
        for(int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = PONTO;
            gabarito[i][j] = PONTO;
        }

    int dificuldade;

    DadosJogador jogador[2];
    jogador[0].NumJogador = 1;
    jogador[1].NumJogador = 2;

    int rodada = 1;
    int par = 0, aux1 = 0;

    dificuldade = inicio(true);
    if(dificuldade == 0)
        return 0;
    while(dificuldade == -1)
        dificuldade = inicio(false);

    int numBarcos;
    switch (dificuldade)
    {
    case 1:
        numBarcos = 10;
        break;
    case 2:
        numBarcos = 10;
        break;
    case 3:
        numBarcos = 5;
        break;
    case 4:
        numBarcos = rand()%9+1;
        break;
    }

    DadosCoordBarco barcoTam[numBarcos][4]; // [qual de barco] [tamanho do barco]
    int barcosDestruidos[numBarcos] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int NumBarcoDestruido[2] = {1, 0};

    cout << "    Qual o número de jogadores (1/2)? ";
    char res[4]; cin >> res;

    while(!(res[0] == '1' || res[0] == '2'))
    {
        cout << "    Digite um comando válido: ";
        cin >> res;
    }

    bool multiplayer = true;
    if(res[0] == '1')
    {
        multiplayer = false;
        strcpy(jogador[1].Nome, "Computador");
    }

    if(definicaoJogadores(jogador, multiplayer) == 0)
        return 0;

    bomba(0);

    criacao(tabuleiro, gabarito, barcoTam, numBarcos, dificuldade);

    tabuleiroImprimir(tabuleiro, jogador, dificuldade);

    cout << rodada << "a rodada:\n" << "Vez do Jogador 1. Digite a coordenada ou o comando: ";
    int coord[2];

    while(!fim(tabuleiro, barcosDestruidos, numBarcos))
    {
        switch(conversao(tabuleiro, gabarito, res, coord, jogador[par].Nome))
        {
        case 0:
            if(multiplayer || par == 0)
            {
                cout << "Ops, voce digitou um codigo ou coordenada invalida";
                aux1++;

                if(aux1 > 5)
                {
                    cout << ". Sugiro rever as regras de digitacao apertando R: ";
                    aux1 = 0;
                }
                else
                    cout << ", digite novamente: ";
            }
            break;
        case 1: //RESPOSTA FOI UMA COORDENADA
            if(jogada(par, tabuleiro, coord, barcoTam, jogador, barcosDestruidos, NumBarcoDestruido, dificuldade, numBarcos))
            {
                rodada++;
                par = (rodada % 2 == 0);

                tabuleiroImprimir(tabuleiro, jogador, dificuldade);
                cout << rodada << "a Rodada:\n" << "Vez do Jogador " << par+1 << ". Digite a coordenada ou o comando: ";
            }
            break;
        case 2:
            regras();
            cout << endl << "Para retornar digite (V): ";
            break;
        case 3:
            cout << "Tem certeza que deseja sair? :( (Sim/Nao) ";
            cin >> res;
            while(!(((res[0] == 'S' || res[0] == 's') && res[1] == 'i' && res[2] == 'm') || ((res[0] == 'N' || res[0] == 'n') && res[1] == 'a' && res[2] == 'o')))
            {
                cout << "Digite uma resposta valido, Sim ou Nao: ";
                cin >> res;
            }
            if((res[0] == 'S' || res[0] == 's') && res[1] == 'i' && res[2] == 'm')
                return 0;
            else
                cout << "Para retornar digite (V): ";
            break;
        case 4:
            tabuleiroImprimir(tabuleiro, jogador, dificuldade);
            cout << rodada << "a Rodada:\n" << "Vez do Jogador " << !par+1 << ". Digite a coordenada ou o comando: ";
            break;
        case 5:
            tabuleiroImprimir(gabarito, jogador, dificuldade);
            cout << "Para retornar digite (V): ";
            break;
        case 6:
            cout << "Ao mudar de nível o jogo será reiniciado, tem certeza que deseja isto? :( (Sim/Nao) ";
            cin >> res;
            while(!(((res[0] == 'S' || res[0] == 's') && res[1] == 'i' && res[2] == 'm') || ((res[0] == 'N' || res[0] == 'n') && res[1] == 'a' && res[2] == 'o')))
            {
                cout << "Digite uma resposta válido, Sim ou Nao: ";
                cin >> res;
            }
            if((res[0] == 'S' || res[0] == 's') && res[1] == 'i' && res[2] == 'm')
                return 1;
            else
                cout << "Para retornar digite (V): ";
            break;
        case 7:
            comoJogar();
            cout << endl << "Para retornar digite (V): ";
            break;
        default:
                break;
        }
    }

    cout << "Fim";

    final(jogador);
    
    cout << endl << "Deseja jogar novamente, Sim ou Nao? ";
    cin >> res;
    if((res[0] == 'S' || res[0] == 's') && res[1] == 'i' && res[2] == 'm')
        return 1;
    else
        return 0;
}

/*******************************************************************************************/
/*                                    JOGO DA VELHA                                        */

void impressao(char tabuleiro[][3], char mapa[][3], char jog[]) // IMPRESSÃO DO TABULEIRO
{
    clear();

    for(int i = 0; i < MARGEM; i++)
        cout << "=";

    cout << endl << endl;

        
    cout << spc << "  ____  _____  ___  _____    ____    __      _  _  ____  __    _   _    __   \n";
    cout << spc << " (_  _)(  _  )/ __)(  _  )  (  _ \\  /__\\    ( \\/ )( ___)(  )  ( )_( )  /__\\  \n";
    cout << spc << ".-_)(   )(_)(( (_-. )(_)(    )(_) )/(__)\\    \\  /  )__)  )(__  ) _ (  /(__)\\ \n";
    cout << spc << "\\____) (_____)\\___/(_____)  (____/(__)(__)    \\/  (____)(____)(_) (_)(__)(__)\n";

    cout << endl << endl;
    cout << spc << spc << spc << "Tabuleiro:                            Coordenadas:\n\n";

    for(int i = 0; i < 3; i++)
    {
        cout << "                  " << " " << tabuleiro[i][0] << " | " << tabuleiro[i][1] << " | " << tabuleiro[i][2] << "                           " << "  " << mapa[i][0] << " | " << mapa[i][1] << " | " << mapa[i][2] << endl;
        if(i < 2)
            cout << "                  " << BARRA << BARRA1 << BARRA << BARRA1 << BARRA << "                           " << BARRA << BARRA1 << BARRA << BARRA1 << BARRA << endl;
    }

    cout << endl << endl;
    cout << spc << "Jogador 1: " << jog[0] << endl << endl;
    cout << spc << "Jogador 2: " << jog[1] << "                                        Digite (S) para sair" << endl << endl;

    for(int i = 0; i < MARGEM; i++)
        cout << "=";

    cout << endl << endl;
}

char fimDaPartida(char matriz[][3]) // ANALISE DO FINAL
{
    for(int i = 0; i < 3; i++)
    {
        if((matriz[i][0] == matriz[i][1]) && (matriz[i][0] == matriz[i][2]))
            return matriz[i][0];
        if((matriz[0][i] == matriz[1][i]) && (matriz[0][i] == matriz[2][i]))
            return matriz[0][i];
        if((matriz[0][0] == matriz[1][1]) && (matriz[0][0] == matriz[2][2]))
            return matriz[0][0];
        if((matriz[0][2] == matriz[1][1]) && (matriz[0][2] == matriz[2][0]))
            return matriz[0][2];
    }
    return ' ';
}

char posicao(int coord, char matriz[][3]) // CONVERSAO
{
    char pos;
    switch(coord)
    {
    case 1:
        pos = matriz[0][0];
        break;
    case 2:
        pos = matriz[0][1];
        break;
    case 3:
        pos = matriz[0][2];
        break;
    case 4:
        pos = matriz[1][0];
        break;
    case 5:
        pos = matriz[1][1];
        break;
    case 6:
        pos = matriz[1][2];
        break;
    case 7:
        pos = matriz[2][0];
        break;
    case 8:
        pos = matriz[2][1];
        break;
    case 9:
        pos = matriz[2][2];
        break;
    }
    return pos;
}

int ocupacao(char tabuleiro[][3]) // VERIFICAR RESPOSTA
{
    char coord;
    cin >> coord;


    while((coord < '1' || coord > '9') && !(coord == 's' || coord == 'S'))
    {
        cout << spc << "Digite uma coordenada válida: ";
        cin >> coord;
    }

    while(true)
    {
        if(coord == 's' || coord == 'S')
            return 0;
        if(posicao(coord-'0', tabuleiro) == ' ')
            return coord-'0';
        else
        {
            cout << spc << "Posição já ocupada, digite outra: ";
            cin >> coord;
        }
    }
}

void substituicao(char matriz[][3], char jog, int coord) // JOGADA
{
    switch(coord)
    {
    case 1:
        matriz[0][0] = jog;
        break;
    case 2:
        matriz[0][1] = jog;
        break;
    case 3:
        matriz[0][2] = jog;
        break;
    case 4:
        matriz[1][0] = jog;
        break;
    case 5:
        matriz[1][1] = jog;
        break;
    case 6:
        matriz[1][2] = jog;
        break;
    case 7:
        matriz[2][0] = jog;
        break;
    case 8:
        matriz[2][1] = jog;
        break;
    case 9:
        matriz[2][2] = jog;
        break;
    }
}

int multipy(char matriz[][3], char jog[]) // GERACAO MULTIPLAYER
{
    if(((matriz[0][1] == matriz[0][2] && matriz[0][1] == jog[1]) ||
        (matriz[1][0] == matriz[2][0] && matriz[1][0] == jog[1]) ||
        (matriz[1][1] == matriz[2][2] && matriz[1][1] == jog[1])) && posicao(1, matriz) == ' ') 
        return 1;
    if(((matriz[0][0] == matriz[0][2] && matriz[0][0] == jog[1]) ||
        (matriz[1][1] == matriz[2][1] && matriz[1][1] == jog[1])) && posicao(2, matriz) == ' ')
        return 2;
    if(((matriz[0][0] == matriz[0][1] && matriz[0][0] == jog[1]) ||
        (matriz[1][2] == matriz[2][2] && matriz[1][2] == jog[1]) ||
        (matriz[1][1] == matriz[2][0] && matriz[1][1] == jog[1])) && posicao(3, matriz) == ' ') 
        return 3;
    if(((matriz[0][0] == matriz[2][0] && matriz[0][0] == jog[1]) ||
        (matriz[1][1] == matriz[1][2] && matriz[1][1] == jog[1])) && posicao(4, matriz) == ' ')
        return 4;
    if(((matriz[1][0] == matriz[1][2] && matriz[1][0] == jog[1]) ||
        (matriz[0][1] == matriz[2][1] && matriz[0][1] == jog[1]) ||
        (matriz[0][0] == matriz[2][2] && matriz[0][0] == jog[1])) && posicao(5, matriz) == ' ') 
        return 5;
    if(((matriz[1][0] == matriz[1][1] && matriz[1][0] == jog[1]) ||
        (matriz[0][2] == matriz[2][2] && matriz[0][2] == jog[1])) && posicao(6, matriz) == ' ') 
        return 6;
    if(((matriz[0][0] == matriz[1][0] && matriz[0][0] == jog[1]) ||
        (matriz[1][1] == matriz[0][2] && matriz[1][1] == jog[1]) ||
        (matriz[2][1] == matriz[2][2] && matriz[2][1] == jog[1])) && posicao(7, matriz) == ' ') 
        return 7;
    if(((matriz[2][0] == matriz[2][2] && matriz[2][0] == jog[1]) ||
        (matriz[1][1] == matriz[0][1] && matriz[1][1] == jog[1])) && posicao(8, matriz) == ' ') 
        return 8;
    if(((matriz[2][0] == matriz[2][1] && matriz[2][0] == jog[1]) ||
        (matriz[1][2] == matriz[0][2] && matriz[1][2] == jog[1]) ||
        (matriz[1][1] == matriz[0][0] && matriz[1][1] == jog[1])) && posicao(9, matriz) == ' ') 
        return 9;
    
    if(((matriz[0][1] == matriz[0][2] && matriz[0][1] == jog[0]) ||
        (matriz[1][0] == matriz[2][0] && matriz[1][0] == jog[0]) ||
        (matriz[1][1] == matriz[2][2] && matriz[1][1] == jog[0])) && posicao(1, matriz) == ' ') 
        return 1;
    if(((matriz[0][0] == matriz[0][2] && matriz[0][0] == jog[0]) ||
        (matriz[1][1] == matriz[2][1] && matriz[1][1] == jog[0])) && posicao(2, matriz) == ' ')
        return 2;
    if(((matriz[0][0] == matriz[0][1] && matriz[0][0] == jog[0]) ||
        (matriz[1][2] == matriz[2][2] && matriz[1][2] == jog[0]) ||
        (matriz[1][1] == matriz[2][0] && matriz[1][1] == jog[0])) && posicao(3, matriz) == ' ') 
        return 3;
    if(((matriz[0][0] == matriz[2][0] && matriz[0][0] == jog[0]) ||
        (matriz[1][1] == matriz[1][2] && matriz[1][1] == jog[0])) && posicao(4, matriz) == ' ')
        return 4;
    if(((matriz[1][0] == matriz[1][2] && matriz[1][0] == jog[0]) ||
        (matriz[0][1] == matriz[2][1] && matriz[0][1] == jog[0]) ||
        (matriz[0][0] == matriz[2][2] && matriz[0][0] == jog[0])) && posicao(5, matriz) == ' ') 
        return 5;
    if(((matriz[1][0] == matriz[1][1] && matriz[1][0] == jog[0]) ||
        (matriz[0][2] == matriz[2][2] && matriz[0][2] == jog[0])) && posicao(6, matriz) == ' ') 
        return 6;
    if(((matriz[0][0] == matriz[1][0] && matriz[0][0] == jog[0]) ||
        (matriz[1][1] == matriz[0][2] && matriz[1][1] == jog[0]) ||
        (matriz[2][1] == matriz[2][2] && matriz[2][1] == jog[0])) && posicao(7, matriz) == ' ') 
        return 7;
    if(((matriz[2][0] == matriz[2][2] && matriz[2][0] == jog[0]) ||
        (matriz[1][1] == matriz[0][1] && matriz[1][1] == jog[0])) && posicao(8, matriz) == ' ') 
        return 8;
    if(((matriz[2][0] == matriz[2][1] && matriz[2][0] == jog[0]) ||
        (matriz[1][2] == matriz[0][2] && matriz[1][2] == jog[0]) ||
        (matriz[1][1] == matriz[0][0] && matriz[1][1] == jog[0])) && posicao(9, matriz) == ' ') 
        return 9;
    
    int num = rand()%10+1;

    while(posicao(num, matriz) != ' ')
        num = rand()%9+1;
    
    return num;
}

// main() do JOGO DA VELHA
int JOGO_DA_VELHA()
{
    clear();

    char tabuleiro[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    char coordenadas[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
    
    char jog[2] = {' ', ' '};

    impressao(tabuleiro, coordenadas, jog);
    cout << spc << "Qual o número de jogadores (1/2)? ";
    char res; cin >> res;

    while(res != '1' && res != '2')
    {
        cout << spc << "Digite um comando válido: ";
        cin >> res;
    }

    bool multiplayer = false;
    if(res == '1')
        multiplayer = true;

    impressao(tabuleiro, coordenadas, jog);
    cout << spc << "O Jogador 1 deseja ser X ou O? ";
    cin >> res;
    
    while(res != 'X' && res != 'x' && res != 'O' && res != 'o' && res != 'S' && res != 's')
    {
        cout << spc << "Digite um comando válido: ";
        cin >> res;
    }

    switch (res)
    {
    case 'X': case 'x':
        jog[0] = 'X';
        jog[1] = 'O';
        break;
    case 'O': case 'o':
        jog[0] = 'O';
        jog[1] = 'X';
        break;
    case 'S': case 's':
        return 0;
    default:
        break;
    }

    impressao(tabuleiro, coordenadas, jog);
    cout << spc << "O Jogador 1 será " << jog[0] << " e o Jogador 2 será " << jog[1] << ".";
    cout << spc << "O tabuleiro está separado como nas coordenadas acima. Para jogar o jogador deve\n";
    cout << spc << "dizer qual coordenada ele quer escolher.\n\n";

    int jogada = 1;
    while(fimDaPartida(tabuleiro) == ' ')
    {
        impressao(tabuleiro, coordenadas, jog);

        if(jogada > 9)
        {
            cout << endl << spc << "Deu velha, boa sorte na próxima :(\n";
            cout << spc << "Digite alguma teclar para voltar: ";
            cin >> res;

            return 0;
        }
        else
        {
            cout << spc << "Jogada n. " << jogada << ". ";

            if((jogada % 2 != 0) || (jogada == 1))
            {
                cout << "Vez do Jogador 1. Digite a coordenada: ";
                
                res = ocupacao(tabuleiro);
                if(res == 0)
                    return 0;

                substituicao(tabuleiro, jog[0], res);
            }
            else
            {
                if(!multiplayer)
                {
                    cout << "Vez do Jogador 2. Digite a coordenada: ";
                    
                    res = ocupacao(tabuleiro);
                    if(res == 0)
                        return 0;

                    substituicao(tabuleiro, jog[1], res);
                }
                else
                    substituicao(tabuleiro, jog[1], multipy(tabuleiro, jog));
            }

            jogada++;
        }
    }

    impressao(tabuleiro, coordenadas, jog);

    cout << endl;
    if(fimDaPartida(tabuleiro) == jog[0])
        cout << spc << "Parabéns, Jogador 1 ganhou!\n";
    if(fimDaPartida(tabuleiro) == jog[1])
        cout << spc << "Parabéns, Jogador 2 ganhou!\n";

    cout << spc << "Digite alguma teclar para voltar: ";
    cin >> res;

    return 0;
}

/******************************************************************************************/

int main()
{
    while(true)
    {
        clear();

        for(int i = 0; i < MARGEM; i++)
            cout << "=";

        cout << endl << endl << endl;

        cout << "                        " << "   __    ____   ___    __    ____  ____ \n";
        cout << "                        " << "  /__\\  (  _ \\ / __)  /__\\  (  _ \\( ___)\n";
        cout << "                        " << " /(__)\\  )   /( (__  /(__)\\  )(_) ))__) \n";
        cout << "                        " << "(__)(__)(_)\\_) \\___)(__)(__)(____/(____)\n";

        cout << endl << endl << endl << endl;

        cout << "               " << " X " << BARRA1 << "   " << BARRA1 << "   " << "                                  " << "      _~      \n";
        cout << "               " << BARRA << BARRA1 << BARRA << BARRA1 << BARRA << "                                  " << "   _~)_)_~    \n";
        cout << "               " << "   " << BARRA1 << " O " << BARRA1 << " X " << "                                  " << "  )_))_))_)   \n";
        cout << "               " << BARRA << BARRA1 << BARRA << BARRA1 << BARRA << "                                  " << "  _!__!__!_   \n";
        cout << "               " << " O " << BARRA1 << " X " << BARRA1 << " O " << "                                  " << "  \\______t/  \n";

        cout << "\n          Digite (V) para jogar                          Digite (N) para jogar";
        cout << "\n          --- JOGO DA VELHA ---                          --- BATALHA NAVAL ---";

        cout << endl << endl << endl;
        cout << "                                                                 Digite (S) para sair";
        cout << endl << endl;

        for(int i = 0; i < MARGEM; i++)
            cout << "=";
        
        cout << endl << endl << spc << "Digite o comando (V/N/S): ";
        char res; cin >> res;

        switch (res)
        {
        case 'V': case 'v':
            JOGO_DA_VELHA();
            break;
        case 'N': case 'n':
            while(BATALHA_NAVAL());
            break;
        case 'S': case 's':
            return 0;
        default:
            cout << spc << "Digite um comando válido: ";
            cin >> res;
            break;
        }
    }
    
    return 0;
}