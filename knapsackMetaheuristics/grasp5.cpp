#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <random>

using namespace std;


//task: improve time complexity 

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

Mochila pertubate(Mochila ks, int rate)
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

Mochila busca_local(Mochila ks, int itr)
{
  Mochila temp;
  int r = 2;
  for (int i = 0; i < itr; i++)
  {
    temp = pertubate(ks, r);
    if (ks.total < temp.total && temp.capacidade >= 0)
    {
      return temp;
    }
    r++;
  }
  return ks;
}

Mochila guloso_aleatorio(Mochila ks, float alfa)
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
    temp_solution = guloso_aleatorio(ks, alfa);
    temp_solution = busca_local(temp_solution, ils_itr);
    if (temp_solution.total > solution.total)
    {
      solution = temp_solution;
    }
  }

  return solution;
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

  int n_items, capacidad;

  Mochila knapsack;

  /*
  if (argc != 3)
  {
    printf("Uso: %s <nome do arquivo de entrada> <algoritmo>\n", argv[0]);
    return 1;
  }
  */

  knapsack = scant_test(argv[1], &n_items, &capacidad);

  knapsack = grasp(knapsack, 0.95, 5, 50) ;

  cout << "Total: " << knapsack.total << endl;

  // imprimir_items(items, n_items);

  return 0;
}
