#include <iostream>
#include <windows.h>

using namespace std;

// função do menu inicial
int inicio() {
  int opcao;
  cout << "\t\tJOGO DA VELHA!" << endl;
  cout << "Sejam bem-vindos! Gostariam de jogar?" << endl;
  cout << "1. Sim." << endl;
  cout << "2. Não.\n"
       << endl;

  cout << "Opção: ";
  cin >> opcao;
  return opcao;
}

// função da tabela
void most_tabela(char tabela[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
    }
    cout << endl;
  }
  cout << "  " << tabela[0][0] << "  |  " << tabela[0][1] << "  |  " << tabela[0][2] << "  " << endl;
  cout << "_____|_____|_____" << endl;
  cout << "     |     |     " << endl;
  cout << "  " << tabela[1][0] << "  |  " << tabela[1][1] << "  |  " << tabela[1][2] << "  " << endl;
  cout << "_____|_____|_____" << endl;
  cout << "     |     |     " << endl;
  cout << "  " << tabela[2][0] << "  |  " << tabela[2][1] << "  |  " << tabela[2][2] << "  " << endl;

  cout << endl;
}

// função de checar se houve uma vitória
bool chec_vitoria(char tabela[3][3], char jogador) {
  // checagem das linhas
  for (int i = 0; i < 3; i++) {
    if (tabela[i][0] == jogador && tabela[i][1] == jogador && tabela[i][2] == jogador) {
      return true;
    }
  }
  // checagem de colunas
  for (int j = 0; j < 3; j++) {
    if (tabela[0][j] == jogador && tabela[1][j] == jogador && tabela[2][j] == jogador) {
      return true;
    }
  }
  // checagem das diagonais
  if (tabela[0][0] == jogador && tabela[1][1] == jogador && tabela[2][2] == jogador) {
    return true;
  }
  if (tabela[0][2] == jogador && tabela[1][1] == jogador && tabela[2][0] == jogador) {
    return true;
  }
  return false;
}

// função de checar se houve empate
bool chec_empate(char tabela[3][3]) {
  int num_jogadas = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (tabela[i][j] != ' ') {
        num_jogadas++;
      }
    }
  }
  return (num_jogadas == 9);
}

// função de reiniciar a tabela
void limpar_tab(char tabela[][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      tabela[i][j] = ' ';
    }
  }
}

int main() {
  UINT CPAGE_UTF8 = 65001;
  SetConsoleOutputCP(CPAGE_UTF8);

  // definição das variáveis do jogo
  char tabela[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
  char jogador1 = 'x';
  char jogador2 = 'o';
  char jogador_atual = jogador1;
  int linha, coluna;
  int opcao;

  // caso escolha uma opcao errada no menu inicial
  do {
    system("cls");
    opcao = inicio();
    if (opcao < 1 || opcao > 3) {
      cout << "Opção inválida. Tente novamente: ";
      cin >> opcao;
      Sleep(1000);
    }
  } while (opcao < 1 || opcao > 3);

  // opções do menu
  switch (opcao) {
  case 1:
    system("cls");
    most_tabela(tabela);
    break;
  case 2:
    system("cls");
    cout << "Que pena! Talvez mais tarde.";
    return 0;
    break;

  default:
    cout << "Opção inválida. Tente novamente: ";
    break;
  }

  // partida do jogo
  while (true) {
    // jogada atual
    cout << "Jogador " << jogador_atual << ", qual posição da linha você deseja (1 a 3)? ";
    cin >> linha;

    cout << "Jogador " << jogador_atual << ", qual posição da coluna você deseja (1 a 3)? ";
    cin >> coluna;

    // limpar a tela após a jogada
    system("cls");

    // checar se a jogada é válida
    if (tabela[linha - 1][coluna - 1] == ' ') {
      tabela[linha - 1][coluna - 1] = jogador_atual;
      most_tabela(tabela);

      // checar se o jogador atual venceu
      if (chec_vitoria(tabela, jogador_atual)) {
        cout << "Parabéns, o jogador " << jogador_atual << " venceu!\n" << endl;

        // opção de jogar novamente
        cout << "\t\tJOGAR NOVAMENTE?" << endl;
        cout << "1. Sim." << endl;
        cout << "2. Não.\n" << endl;

        int opcao2;
        cout << "Opção: ";
        cin >> opcao2;
        
        //se escolher reiniciar o jogo
        if (opcao2 == 1) {
          system("cls");
          limpar_tab(tabela);
          most_tabela(tabela);
        } 
        //se escolher não reiniciar o jogo
        else if (opcao2 == 2) { 
          cout << "Que pena! Talvez mais tarde.";
          break;
        } else {
          cout << "Opção inválida. Tente novamente: ";
          cin >> opcao2;
        } //se digitar um número inválido
      }

      // trocar de jogador a cada jogada
      if (jogador1 == jogador_atual) {
        jogador_atual = jogador2;
      } else {
        jogador_atual = jogador1;
      }
    }
    // caso o número inserido for inválido
    else if (linha < 0 || linha > 3) {
      cout << "Jogada inválida. Tente novamente!" << endl;
      cout << endl;
      most_tabela(tabela);
    }
    else if (coluna < 0 || coluna > 3) {
      cout << "Jogada inválida. Tente novamente!" << endl;
      cout << endl;
      most_tabela(tabela);
    } else {
      // caso a posição escolhida já esteja ocupada
      cout << "Jogada inválida. Tente novamente!" << endl;
      cout << endl;
      most_tabela(tabela);
    }

    // caso haja um empate
    if (chec_empate(tabela)) {
      cout << "Houve um empate. Fim do jogo!\n" << endl;

      // opção de jogar novamente
      cout << "\t\tJOGAR NOVAMENTE?" << endl;
      cout << "1. Sim." << endl;
      cout << "2. Não.\n" << endl;

      int opcao2;
      cout << "Opção: ";
      cin >> opcao2;

      if (opcao2 == 1) {
        system("cls");
        limpar_tab(tabela);
        most_tabela(tabela);
      }
      else if (opcao2 == 2) {
        cout << "Que pena! Talvez mais tarde.";
        break;
      } else {
        cout << "Opção inválida. Tente novamente: ";
        cin >> opcao2;
      }
    }
  }

  cout << endl;
  return 0;
}