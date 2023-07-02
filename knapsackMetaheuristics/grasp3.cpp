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

int busca_local(Mochila *ks)
{
  double ratio_sum = (double)0;
  for(int i = 0; i < ks->itens.size(); i++){
    ratio_sum += ks->itens.at(i)->ratio;
  }

  for (int i = 0; i < ks->itens.size(); i++)
  {
    double temp_rs = (double)0;
    if (ks->itens.at(i)->position == 0)
    {
      ks->itens.at(i)->position = 1;
    }
    else
    {
      ks->itens.at(i)->position = 0;
    }


    for(int j = 0; j < ks->itens.size(); j++){
      if(ks->itens.at(j)->position == 1){
        temp_rs = ks->itens.at(j)->ratio;
      }
    }

    if(temp_rs < ratio_sum){
      ks->itens.at(i)->position = !ks->itens.at(i)->position;
    }

  }

  return ks->total;
}

void guloso_aleatorio(Mochila *ks, float alfa = 1)
{

  sort(ks->itens.begin(), ks->itens.end(), comparePointers); // ordena por razao descrescente
  vector<Item *> temp_itens = ks->itens;

  while (!temp_itens.empty())
  {
    double c_min = temp_itens.back()->ratio;
    double c_max = temp_itens.front()->ratio;

    // Create RCL
    vector<Item *> RCL;
    for (int i = 0; i < temp_itens.size(); i++)
    {
      Item *item = temp_itens.at(i);
      double c = item->ratio;
      if (c >= c_min + alfa * (c_max - c_min))
      {
        RCL.push_back(item);
      }
    }

    int r_index = rand() % RCL.size();
    Item *r_item = RCL.at(r_index);

    if (ks->capacidade - r_item->peso >= 0 && r_item->position == 0)
    {
      ks->capacidade -= r_item->peso;
      ks->total += r_item->beneficio;
      r_item->position = 1;
    }

    auto itr = std::remove_if(temp_itens.begin(), temp_itens.end(), [&](Item *a)
                              { return a == RCL.at(r_index); });

    temp_itens.erase(itr, temp_itens.end());
  }
}

int grasp(Mochila *ks, float alfa, int itr){
  int sol = 0;

  for(int k = 0; k<itr; k++){
    guloso_aleatorio(ks, alfa);

    int temp_sol = busca_local(ks);
    if(temp_sol > sol){
      sol = temp_sol;
    }

    for(int i = 0; i<ks->itens.size(); i++){
      ks->itens.at(i)->position = 0;
    }
  }

  return sol;
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

  int sol = grasp(knapsack, 0.8, 100);

  cout << "Total: " << sol << endl;

  // imprimir_items(items, n_items);

  return 0;
}
