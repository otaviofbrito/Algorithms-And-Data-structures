#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <random>
#include <time.h>
#include <iomanip>

#include "./dependencies/mochila.h"
#include "./dependencies/scanFile.cpp"

using namespace std;

inline int max(int a, int b) { return (a > b) ? a : b; }

int progDinamica(Mochila ks)
{
  int i, j;
  int tabela[2][ks.capacidade + 1];

  for (i = 0; i <= ks.itens.size(); i++)
  {
    // Preenche a tabela[][] de baixo para cima
    for (j = 0; j <= ks.capacidade; j++)
    {
      // Caso base
      if (i == 0 || j == 0)
        tabela[i % 2][j] = 0;
      else if (ks.itens.at(i - 1).peso <= j)
        tabela[i % 2][j] = max(ks.itens.at(i - 1).beneficio + tabela[(i - 1) % 2][j - ks.itens.at(i - 1).peso],
                               tabela[(i - 1) % 2][j]);
      else
        tabela[i % 2][j] = tabela[(i - 1) % 2][j];
    }
  }
  // Retorna o valor máximo que pode ser colocado na mochila
  return tabela[ks.itens.size() % 2][ks.capacidade];
}


int main(int argc, char const *argv[])
{
  clock_t start, end;

  int n_items, capacidad;

  Mochila knapsack;

  knapsack = scan_file(argv[1], &n_items, &capacidad);

  start = clock();

  int sol = progDinamica(knapsack);

  end = clock();

  cout << "Total: " << sol << endl;
  double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

  cout << "\n\nTime taken : " << fixed
       << time_taken << setprecision(5);
  cout << " sec \n\n " << endl;


  return 0;
}
