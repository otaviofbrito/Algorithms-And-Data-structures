#include <string.h>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <time.h>
#include <iomanip>
#include <vector>

#include "./dependencies/mochila.h"
#include "./dependencies/scanFile.cpp"


using namespace std;


bool compare(const Item obj1, const Item obj2)
{
  return obj1.ratio > obj2.ratio;
}


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


int main(int argc, char const *argv[])
{
  clock_t start, end;

  int n_items, capacidad;

  Mochila knapsack;

  knapsack = scan_file(argv[1], &n_items, &capacidad);

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
