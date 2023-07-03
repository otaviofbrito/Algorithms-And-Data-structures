#include <fstream>
#include <iostream>
#include <vector>


#include "mochila.h"

using namespace std;

Mochila scan_file(char const *file_name, int *n_items, int *capacidad)
{

  Mochila knapsack;

  ifstream test_file;
  test_file.open("./dependencies/input_file");

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