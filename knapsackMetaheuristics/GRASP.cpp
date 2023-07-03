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

// task: improve time complexity (greedy randomized)


bool compare(const Item obj1, const Item obj2)
{
  return obj1.ratio > obj2.ratio;
}


Mochila perturbate(Mochila ks, int rate)
{
  mt19937 rng(std::random_device{}());
  uniform_int_distribution<int> distribution(0, ks.itens.size() - 1);

  for (int r = 0; r < rate; r++)
  {
    int r_index = distribution(rng);

    if (ks.itens.at(r_index).position == 0)
    {
      ks.itens.at(r_index).position = 1;
      ks.total += ks.itens.at(r_index).beneficio;
      ks.capacidade -= ks.itens.at(r_index).peso;
    }
    else
    {
      ks.itens.at(r_index).position = 0;
      ks.total -= ks.itens.at(r_index).beneficio;
      ks.capacidade += ks.itens.at(r_index).peso;
    }
  }

  return ks;
}

Mochila Iterated_Local_Search(Mochila ks, int itr)
{
  Mochila temp;
  int r = 2;
  for (int i = 0; i < itr; i++)
  {
    temp = perturbate(ks, r);
    if (ks.total < temp.total && temp.capacidade >= 0)
    {
      return temp;
    }
    r++;
  }
  return ks;
}

Mochila Greedy_Randomized_Construction(Mochila ks, float alfa)
{
  mt19937 rng(std::random_device{}());

  vector<Item> temp_itens = ks.itens;

  while (!temp_itens.empty())
  {
    double c_min = temp_itens.back().ratio;
    double c_max = temp_itens.front().ratio;

    // Create RCL
    vector<Item> RCL;
    for (int i = 0; i < temp_itens.size(); i++)
    {
      Item item = temp_itens.at(i);
      double c = item.ratio;
      if (c >= c_min + alfa * (c_max - c_min))
      {
        RCL.push_back(item);
      }
    }

    uniform_int_distribution<int> distribution(0, RCL.size() - 1);
    int r_index = distribution(rng);
    Item r_item = RCL.at(r_index);

    if (ks.capacidade - r_item.peso >= 0 && r_item.position == 0)
    {
      ks.capacidade -= r_item.peso;
      ks.total += r_item.beneficio;
      for (int j = 0; j < ks.itens.size(); j++)
      {
        if (ks.itens.at(j).id == r_item.id)
        {
          ks.itens.at(j).position = 1;
        }
      }
    }

    auto itr = std::remove_if(temp_itens.begin(), temp_itens.end(), [&](Item a)
                              { return a.id == RCL.at(r_index).id; });

    temp_itens.erase(itr, temp_itens.end());
  }
  return ks;
}

Mochila grasp(Mochila ks, float alfa, int itr, int ils_itr)
{
  sort(ks.itens.begin(), ks.itens.end(), compare);
  Mochila solution = ks;
  Mochila temp_solution;

  for (int k = 0; k < itr; k++)
  {
    temp_solution = Greedy_Randomized_Construction(ks, alfa);
    temp_solution = Iterated_Local_Search(temp_solution, ils_itr);
    if (temp_solution.total > solution.total)
    {
      solution = temp_solution;
    }
  }

  return solution;
}


int main(int argc, char const *argv[])
{
  clock_t start, end;

  int n_items, capacidad;

  Mochila knapsack;

  knapsack = scan_file(argv[1], &n_items, &capacidad);

  start = clock();
  // grasp(knapsack, alfa, graspMaxIteration, ilsMaxIteration)
  knapsack = grasp(knapsack, 0.95, 10, 20);

  end = clock();

  cout << "Total: " << knapsack.total << endl;
  double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

  cout << "\n\nTime taken : " << fixed
       << time_taken << setprecision(5);
  cout << " sec \n\n " << endl;

  return 0;
}
