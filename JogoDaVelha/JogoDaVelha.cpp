
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
#define ERRO ' '
#define TAM 10
#define MARGEM TAM*TAM-30+(3*6)
#define spc "      "

using namespace std;

void clear() // LIMPAR O TERMINAL
{
    #ifdef _WIN32
        system("cls");  // Comando para limpar o terminal no Windows
    #else
        system("clear");  // Comando para limpar o terminal em sistemas baseados em Unix (Linux, macOS)
    #endif
}

int BATALHA_NAVAL(){return 0;}

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
    clear();

    for(int i = 0; i < MARGEM; i++)
        cout << "=";

    cout << endl << endl << endl;

    cout << "                        " << "   __    ____   ___    __    ____  ____ \n";
    cout << "                        " << "  /__\\  (  _ \\ / __)  /__\\  (  _ \\( ___)\n";
    cout << "                        " << " /(__)\\  )   /( (__  /(__)\\  )(_) ))__) \n";
    cout << "                        " << "(__)(__)(_)\\_) \\___)(__)(__)(____/(____)\n";

    cout << endl << endl << endl << endl;

    cout << "                                      " << " X " << BARRA1 << "   " << BARRA1 << "\n";
    cout << "                                      " << BARRA << BARRA1 << BARRA << BARRA1 << BARRA << "\n";
    cout << "                                      " << "   " << BARRA1 << " O " << BARRA1 << " X " << "\n";
    cout << "                                      " << BARRA << BARRA1 << BARRA << BARRA1 << BARRA << "\n";
    cout << "                                      " << " O " << BARRA1 << " X " << BARRA1 << " O " << "\n";
    
    cout << "\n                                Digite (V) para jogar";
    cout << "\n                                --- JOGO DA VELHA ---";

    cout << endl << endl << endl;
    cout << "                                                                 Digite (S) para sair";
    cout << endl << endl;

    for(int i = 0; i < MARGEM; i++)
        cout << "=";
    
    cout << endl << endl << spc << "Digite o comando (V/S): ";
    char res; cin >> res;

    switch (res)
    {
    case 'V': case 'v':
        JOGO_DA_VELHA();
        break;
    case 'S': case 's':
        return 0;
    default:
        cout << spc << "Digite um comando valido: ";
        cin >> res;
        break;
    }
    
    return 0;
}