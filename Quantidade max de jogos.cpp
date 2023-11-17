#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void printMatriz(int numeroJuizes, int jogos,
                 vector<vector<int>> matrizHorarios) {
  cout << endl << "Matriz de entrada" << endl;
  for (int i = 0; i < numeroJuizes; i++) {
    for (int j = 0; j < jogos; j++) {
      cout << matrizHorarios[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

// Função de verificação da entrada
// vai ser usada ?
int verificar(int n, int m, int x, vector<vector<int>> matrizHorarios) {
  // 5m>=nx
  if (5 * m < n * x) {
    printf("O número de árbitros por partida é menor do que o número de "
           "árbitros vezes o número mínimo de partidas\n");
    return 1;
  }
  // soma de cada linha da matriz >= x
  int somal;
  for (int i = 0; i < n; i++) {
    somal = 0;
    for (int j = 0; j < m; j++) {
      somal += matrizHorarios[i][j];
    }
    if (somal < x) {
      printf("O árbitro %d possui menos jogos disponíveis do que o número "
             "mínimo\n",
             i);
      return 1;
    }
  }
  // soma de cada coluna da matriz >= 5

  int somac;
  for (int j = 0; j < m; j++) {
    somac = 0;
    for (int i = 0; i < n; i++) {
      somac += matrizHorarios[i][j];
    }
    if (somac < 5) {
      printf("O jogo %d possui menos árbitros disponíveis do que o número "
             "mínimo\n",
             j);
      return 1;
    }
  }
  return 0;
}

int sortFunction(vector<int> &i, vector<int> &j) {
  return i[1] / (float)i[2] < j[1] / (float)j[2];
}

vector<vector<int>> densidade(int linhas, int colunas,
                              vector<vector<int>> matrizHorarios,
                              int minimoDeJogos) {

  vector<vector<int>> densidade(linhas, vector<int>(3, 0));
  int count;

  for (int i = 0; i < linhas; i++) {
    count = 0;
    densidade[i][0] = i;

    for (int j = 0; j < colunas; j++) {
      if (matrizHorarios[i][j]) {
        count++;
      }
    }
    densidade[i][1] = count;
    densidade[i][2] = minimoDeJogos;
  }

  return densidade;
}

int main(int argc, char **argv) {
  string entrada, saida;

  if (argc == 1) {
    cout << "Arquivo de entrada : ";
    cin >> entrada;
    cout << "Arquivo de saida : ";
    cin >> saida;
  } else if (argc == 2) {
    entrada = argv[1];
    cout << "Arquivo de saida : ";
    cin >> saida;
  } else if (argc == 3) {
    entrada = argv[1];
    saida = argv[2];
  }

  fstream input(entrada, ios::in);
  fstream output(saida, ios::out);

  if (!(input.is_open())) {
    cout << "Erro na abertura do arquivo de entrada";
    return 1;
  }
  if (!(output.is_open())) {
    cout << "Erro na abertura do arquivo de saida";
    return 1;
  }
  int c;

  int numeroJuizes, numJogos, x, horas, y;

  // cout << "Numero de juizes: ";
  input >> numeroJuizes;
  // output << numeroJuizes << " ";
  // cout << "Horas Trabalhadas";
  input >> horas;
  // output << horas<< " ";

  vector<vector<int>> matrizHorarios(numeroJuizes, vector<int>(horas, 0));

  for (int i = 0; i < numeroJuizes; i++) { // O(n*h)
    // cout << "Juizes " << i << " Horarios" << endl;
    for (int j = 0; j < horas; j++) {
      input >> matrizHorarios[i][j];
      // output << matrizHorarios[i][j]<< " ";
    }
  }
  // cout << "Numero de jogos: ";
  input >> numJogos;
  // output << numJogos<< " ";
  // cout << "Horario dos jogos: ";
  int jogos[numJogos];
  for (int i = 0; i < numJogos; i++) { // O(j)
    input >> jogos[i];
    // output << jogos[i]<< " ";
  }
  // cout << "Quantidade minima de jogos: ";
  input >> x;
  // output << x<< " ";
  // cout << "Quantidade maxima de jogos: ";
  input >> y;
  // output << y<< " ";

  vector<int> horasMaximas(numeroJuizes, y); // 0(n) ?
  /*
    cout << endl << "Matriz de entrada" << endl;
    for (int i = 0; i < numeroJuizes; i++) {
      for (int j = 0; j < numJogos; j++) {
        cout << matrizHorarios[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
  */
  /*if (verificar(numeroJuizes, numJogos, x, matrizHorarios) == 1) {
    printf("Impossível continuar\n");
    return 1;
  }*/

  vector<vector<int>> den =
      densidade(numeroJuizes, numJogos, matrizHorarios, x); // O(n*h)
  sort(den.begin(), den.end(), sortFunction); // O(nlogn)

  /*
  cout <<endl << "Matriz de densidade" << endl;
    for (int i = 0; i < numeroJuizes; i++) {
      for (int j = 0; j < 3; j++) {
        cout << den[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
*/
  /*
        cout << "Anterios sao Debug" << endl;*/

  bool found;

  vector<vector<int>> juizesEscolhidos(numJogos, vector<int>(5, -1));


  
  for (int jogo = 0; jogo < numJogos; jogo++)/*O(j*5n)*/ {

    for (int numJuizes = 0; numJuizes < 5; numJuizes++) /* O(5n)*/ {

      found = false;
      // esse loop <= n
      if (den.size() > 0) {
        for (int i = 0; i < den.size(); i++) { 
          if (matrizHorarios[den[i][0]][jogos[jogo]] == 1 &&
              horasMaximas[den[i][0]] > 0) {
            den[i][1] -= 1;
            den[i][2] -= 1;

            horasMaximas[den[i][0]] -= 1;
            /*cout << "jogo " << jogo << " numJuizes " << numJuizes <<"     ";
            for (int i = 0; i < escolhido.size(); i++) {
              cout << escolhido[i] << " ";
            }
            cout << endl;
            */

            juizesEscolhidos[jogo][numJuizes] = den[i][0];
            found = true;
            matrizHorarios[den[i][0]][jogo] = 0;

            if (den[i][2] == 0) {
              den.erase(den.begin());
            } else {
              sort(den.begin(), den.end(), sortFunction);
            }

            break;
          }
        }
      }

      if (!found) {
        // esse loop <= n
        for (int i = 0; i < numeroJuizes; i++) {
          if (matrizHorarios[i][jogos[jogo]] == 1 && horasMaximas[i] > 0) {
            // cout << "Achou" << endl;
            found = true;
            juizesEscolhidos[jogos[jogo]][numJuizes] = i;
            matrizHorarios[i][jogos[jogo]] = 0;
            horasMaximas[i] -= 1;
            break;
          }
        }
        if (!found) {
          output << "Não existe juizes o suficiente para o jogo numero "
                 << jogo + 1 << endl;
          for (int i = 0; i < numJogos; i++) {
            output << "Jogo na hora : " << i << "  Juizes escolhidos:   ";
            for (int j = 0; j < 5; j++) {
              output << juizesEscolhidos[i][j] << " ";
            }
            output << endl;
          }
          input.close();
          output.close();
          return 1;
        }
      }

      // printMatriz(numeroJuizes,numJogos,matrizHorarios);
    }
  }

  for (int i = 0; i < numJogos; i++) /*O(5j)*/ {
    output << "Jogo na hora : " << i << "  Juizes escolhidos:   ";
    for (int j = 0; j < 5; j++) {
      output << juizesEscolhidos[i][j] << " ";
    }
    output << endl;
  }
  input.close();
  output.close();
  return 0;

  //O(nlogn) + O(j) + O(n*h) + O(j*5n) + O(5j)

  
}

/*





teste 1

Tem solução
8 4
1 1 1 0
1 0 0 1
1 1 1 0
0 1 1 0
1 0 1 1
0 1 0 1
1 1 0 1
0 0 1 1
4
0 1 2 3
2
3



teste 2

Não tem solução
8 4
1 1 1 0
1 0 0 1
1 1 1 0
0 1 1 0
1 0 1 1
0 1 0 1
1 1 0 1
0 0 1 1
5
0 1 2 3 1
2
2

teste 3

Tem solução
10 9
1 1 1 0 1 1 1 1 0
1 1 0 1 1 1 0 0 1
1 0 0 1 0 1 1 0 1
1 0 1 0 0 0 0 0 1
1 1 0 1 1 0 1 1 0
1 0 1 0 1 1 0 1 0
1 1 0 1 0 1 1 0 1
1 1 1 0 0 1 0 1 0
1 0 0 1 1 0 1 0 1
1 0 1 0 1 0 0 1 1
9
0 1 2 3 4 5 6 7 8
3
5

teste 4

10 9
1 1 1 0 1 1 1 1 0
1 1 0 1 1 1 0 0 1
1 0 0 1 0 1 1 0 1
1 0 1 0 0 0 0 0 1
1 1 0 1 1 0 1 1 0
1 0 1 0 1 1 0 1 0
1 1 0 1 0 1 1 0 1
1 1 1 0 0 1 0 1 0
1 0 0 1 1 0 1 0 1
1 0 1 0 1 0 0 1 1
9
0 1 2 3 4 5 6 7 8
1
5


*/