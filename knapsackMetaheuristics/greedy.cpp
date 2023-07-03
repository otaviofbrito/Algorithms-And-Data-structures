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

bool compare(const Item obj1, const Item obj2)
{
  return obj1.ratio > obj2.ratio;
}

class Mochila
{
public:
  int capacidade;
  int total = 0;
  vector<Item> itens;
};

Mochila greedy(Mochila ks)
{
  sort(ks.itens.begin(), ks.itens.end(), compare);

  for (int i = 0; i < ks.itens.size(); i++)
  {
    if (ks.capacidade - ks.itens.at(i).peso >= 0 && !ks.itens.at(i).position)
    {
      ks.capacidade -= ks.itens.at(i).peso;
      ks.total += ks.itens.at(i).beneficio;
      ks.itens.at(i).position = 1;
    }
  }

  return ks;
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

  knapsack = greedy(knapsack);

  end = clock();

  cout << "Total: " << knapsack.total << endl;
  double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

  cout << "\n\nTime taken : " << fixed
       << time_taken << setprecision(5);
  cout << " sec \n\n " << endl;

  return 0;
}
