#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

class Item
{
public:
  int peso;
  int beneficio;
  double ratio;
  bool position = 0;
};

bool comparePointers(const Item *obj1, const Item *obj2)
{
  return obj1->ratio > obj2->ratio;
}

class Mochila
{
public:
  int capacidade;
  int total = 0;
  vector<Item *> itens;
};

void guloso_aleatorio(Mochila *itens, float r = 1)
{
  int qtdRandom;
  int len = itens->itens.size();
  vector<Item *> temp_itens = itens->itens;

  qtdRandom = len * r;
  cout << "\n " << qtdRandom << endl;

  sort(itens->itens.begin(), itens->itens.end(), comparePointers);

  int c = 0;
  while (c < qtdRandom)
  {
    int r_index = rand() % temp_itens.size();

    if (itens->capacidade - temp_itens.at(r_index)->peso >= 0 && temp_itens.at(r_index)->position == 0)
    {
      itens->capacidade -= temp_itens.at(r_index)->peso;
      itens->total += temp_itens.at(r_index)->beneficio;
      temp_itens.at(r_index)->position = 1;

      auto itr = std::remove_if(temp_itens.begin(), temp_itens.end(), [&](Item *a)
                                { return a == temp_itens.at(r_index); });

      temp_itens.erase(itr, temp_itens.end());
    } else {
      auto itr = std::remove_if(temp_itens.begin(), temp_itens.end(), [&](Item *a)
                                { return a == temp_itens.at(r_index); });

      temp_itens.erase(itr, temp_itens.end());
    }
    c++;
  }

  for (int i = 0; i < len; i++)
  {
    if (itens->capacidade - itens->itens.at(i)->peso >= 0 && itens->itens.at(i)->position == 0)
    {
      itens->capacidade -= itens->itens.at(i)->peso;
      itens->total += itens->itens.at(i)->beneficio;
      itens->itens.at(i)->position = 1;
    }
  }
}

Mochila *scant_test(char const *file_name, int *n_items, int *capacidad)
{

  Mochila *bag = new Mochila();

  ifstream test_file;
  test_file.open("f1_l-d_kp_10_269");

  if (!test_file.is_open())
  {
    cout << "UNABLE TO LOCATE FILE";
    exit(0);
  }

  test_file >> *n_items;
  test_file >> *capacidad;

  bag->capacidade = *capacidad;

  for (int i = 0; i < *n_items; i++)
  {
    int pes, ben;
    test_file >> ben;
    test_file >> pes;
    Item *item = new Item();
    item->peso = pes;
    item->beneficio = ben;
    item->ratio = (double)ben / (double)pes;

    bag->itens.push_back(item);
  }

  return bag;
}

int main(int argc, char const *argv[])
{

  int n_items, capacidad;

  Mochila *bag;

  /*
  if (argc != 3)
  {
    printf("Uso: %s <nome do arquivo de entrada> <algoritmo>\n", argv[0]);
    return 1;
  }
  */

  bag = scant_test(argv[1], &n_items, &capacidad);

  guloso_aleatorio(bag);

  cout << "Total: " << bag->total << endl;

  // imprimir_items(items, n_items);

  return 0;
}
