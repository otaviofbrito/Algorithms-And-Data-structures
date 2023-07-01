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

/*
 r = porcentagem de itens aleatorios.

 A funcao coloca os itens na mochila (define 'position' para 1 se ele cabe) e incrementa o total de beneficio.

uma parte eh feita de maneira aleatoria (para diversificar o espaço de busca que será feito na busca local).

*/
void guloso_aleatorio(Mochila *ks, float r = 0)
{
  int qtdRandom;
  int len = ks->itens.size();
  vector<Item *> temp_itens = ks->itens;  //copia o conjunto de itens

  qtdRandom = len * r; //define quantidade de itens aleatorios
  cout << "\n " << qtdRandom << endl;

  sort(ks->itens.begin(), ks->itens.end(), comparePointers); //ordena por razao descrescente


  //parte gulosa aleatoria
  int c = 0;
  while (c < qtdRandom)
  {
    int r_index = rand() % temp_itens.size(); //seleciona um item aleatorio do conjunto

     //quando um item eh consultado, ele eh removido do conjunto p/ evitar consultas repetidas 
    if (ks->capacidade - temp_itens.at(r_index)->peso >= 0 && temp_itens.at(r_index)->position == 0)
    {
      ks->capacidade -= temp_itens.at(r_index)->peso;
      ks->total += temp_itens.at(r_index)->beneficio;
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

  //parte gulosa padrao
  for (int i = 0; i < len; i++)
  {
    if (ks->capacidade - ks->itens.at(i)->peso >= 0 && ks->itens.at(i)->position == 0)
    {
      ks->capacidade -= ks->itens.at(i)->peso;
      ks->total += ks->itens.at(i)->beneficio;
      ks->itens.at(i)->position = 1;
    }
  }
}

Mochila *scant_test(char const *file_name, int *n_items, int *capacidad)
{

  Mochila *knapsack = new Mochila();

  ifstream test_file;
  test_file.open("f1_l-d_kp_10_269");

  if (!test_file.is_open())
  {
    cout << "UNABLE TO LOCATE FILE";
    exit(0);
  }

  test_file >> *n_items;
  test_file >> *capacidad;

  knapsack->capacidade = *capacidad;

  for (int i = 0; i < *n_items; i++)
  {
    int pes, ben;
    test_file >> ben;
    test_file >> pes;
    Item *item = new Item();
    item->peso = pes;
    item->beneficio = ben;
    item->ratio = (double)ben / (double)pes;

    knapsack->itens.push_back(item);
  }

  return knapsack;
}

int main(int argc, char const *argv[])
{

  int n_items, capacidad;

  Mochila *knapsack;

  /*
  if (argc != 3)
  {
    printf("Uso: %s <nome do arquivo de entrada> <algoritmo>\n", argv[0]);
    return 1;
  }
  */

  knapsack = scant_test(argv[1], &n_items, &capacidad);

  guloso_aleatorio(knapsack);

  cout << "Total: " << knapsack->total << endl;

  // imprimir_items(items, n_items);

  return 0;
}
