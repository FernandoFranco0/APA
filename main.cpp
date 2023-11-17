#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;


int sortFunction(vector<int> &i, vector<int> &j) {
  return i[1] / (float)i[2] < j[1] / (float)j[2];
}

vector<vector<int>> densidade(int linhas, int colunas,vector<vector<int>> matrizHorarios,int minimoDeJogos) {
  // densidade[i][0] = id do elemento i
  // densidade[i][1] = quantidade de possiveis jogos para o elemento i
  // densidade[i][2] = quantidade minima de jogos do elemento i

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

int main(int argc , char **argv) {
  string entrada , saida;

  if (argc == 1){
    cout << "Arquivo de entrada : ";
    cin >> entrada;
    cout << "Arquivo de saida : ";
    cin >> saida;
  } else if (argc == 2){
    entrada = argv[1];
    cout << "Arquivo de saida : ";
    cin >> saida;
  } else{
    entrada = argv[1];
    saida = argv[2];
  }

  fstream input(entrada, ios:: in);
  fstream output(saida, ios:: out);

  if(!(input.is_open())){
    cout << "Erro na abertura do arquivo de entrada";
    return 1;
  }
  if(!(output.is_open())){
    cout << "Erro na abertura do arquivo de saida";
    return 1;
  }
  int c;

  int numeroJuizes, numJogos, x, horas, y;

  input >> numeroJuizes;
  input >> horas;

  vector<vector<int>> matrizHorarios(numeroJuizes, vector<int>(horas, 0));

  for (int i = 0; i < numeroJuizes; i++) {
    for (int j = 0; j < horas; j++) {
      input >> matrizHorarios[i][j];
    }
  }

  input >> numJogos;

  int jogos[numJogos];
  for (int i = 0; i < numJogos; i++) {
    input >> jogos[i];
  }
  input >> x;
  input >> y;

  vector<int> horasMaximas(numeroJuizes, y);


  vector<vector<int>> den = densidade(numeroJuizes, numJogos, matrizHorarios, x);
  sort(den.begin(), den.end(), sortFunction);

  bool found;

  vector<vector<int>> juizesEscolhidos(numJogos, vector<int>(5, -1));

  for (int jogo = 0; jogo < numJogos; jogo++) {

    for (int numJuizes = 0; numJuizes < 5; numJuizes++) {

      found = false;
      if (den.size() > 0)/*j*n^2logn*/ {
        for (int i = 0; i < den.size(); i++) {
          if (matrizHorarios[den[i][0]][jogos[jogo]] == 1 &&
              horasMaximas[den[i][0]] > 0) {
            den[i][1] -= 1;
            den[i][2] -= 1;

            horasMaximas[den[i][0]] -= 1;


            juizesEscolhidos[jogo][numJuizes] = den[i][0];
            found = true;
            matrizHorarios[den[i][0]][jogos[jogo]] = 0;

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
        for (int i = 0; i < numeroJuizes; i++) {
          if (matrizHorarios[i][jogos[jogo]] == 1 && horasMaximas[i] > 0) {
            found = true;
            juizesEscolhidos[jogos[jogo]][numJuizes] = i;
            matrizHorarios[i][jogos[jogo]] = 0;
            horasMaximas[i] -= 1;
            break;
          }
        }
        if (!found) {
          output << "Não existe juizes o suficiente para o jogo numero " << jogo + 1 << endl;
          for (int i = 0; i < numJogos; i++) {
            output << "Jogo na hora : " << jogos[i] << "  Juizes escolhidos:   ";
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
    }
  }

  for (int i = 0; i < numJogos; i++) {
    output << "Jogo na hora : " << jogos[i] << "  Juizes escolhidos:   ";
    for (int j = 0; j < 5; j++) {
      output << juizesEscolhidos[i][j] << " ";
    }
    output << endl;
  }
  input.close();
  output.close();
  return 0;
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