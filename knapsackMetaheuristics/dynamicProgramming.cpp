#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <random>
#include <time.h>
#include <iomanip>

using namespace std;

class Item
{
public:
  int id;
  int peso;
  int beneficio;
  double ratio;
  bool position = 0;
};

class Mochila
{
public:
  int capacidade;
  int total = 0;
  vector<Item> itens;
};

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

Mochila scant_test(char const *file_name, int *n_items, int *capacidad)
{

  Mochila knapsack;

  ifstream test_file;
  test_file.open("test");

  if (!test_file.is_open())
  {
    cout << "UNABLE TO LOCATE FILE";
    exit(0);
  }

  test_file >> *n_items;
  test_file >> *capacidad;

  knapsack.capacidade = *capacidad;

  for (int i = 0; i < *n_items; i++)
  {
    int pes, ben;
    test_file >> ben;
    test_file >> pes;
    Item item;
    item.id = i;
    item.peso = pes;
    item.beneficio = ben;
    item.ratio = (double)ben / (double)pes;

    knapsack.itens.push_back(item);
  }

  return knapsack;
}

int main(int argc, char const *argv[])
{
  clock_t start, end;

  int n_items, capacidad;

  Mochila knapsack;

  knapsack = scant_test(argv[1], &n_items, &capacidad);

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
