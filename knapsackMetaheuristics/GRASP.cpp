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


bool compare(const Item obj1, const Item obj2)
{
  return obj1.ratio > obj2.ratio;
}

/*

Busca local, recebe uma solução parcial 'perturbada' obitda na ILS
 realiza a troca de 2 bits da solução como função de vizinhança
Implementado com base no First improvement, retorna a primeira solução aprimorante
*/
Mochila local_search(Mochila ks)
{

  Mochila temp = ks;
  int len = ks.itens.size();
  for (int r = 0; r < len; r++)
  {

    if (temp.itens.at(r).position == 0)
    {
      temp.itens.at(r).position = 1;
      temp.total += temp.itens.at(r).beneficio;
      temp.capacidade -= temp.itens.at(r).peso;
    }
    else
    {
      temp.itens.at(r).position = 0;
      temp.total -= temp.itens.at(r).beneficio;
      temp.capacidade += temp.itens.at(r).peso;
    }

    if (temp.itens.at((len - 1) - r).position == 0)
    {
      temp.itens.at((len - 1) - r).position = 1;
      temp.total += temp.itens.at((len - 1) - r).beneficio;
      temp.capacidade -= temp.itens.at((len - 1) - r).peso;
    }
    else
    {
      temp.itens.at((len - 1) - r).position = 0;
      temp.total -= temp.itens.at((len - 1) - r).beneficio;
      temp.capacidade += temp.itens.at((len - 1) - r).peso;
    }

    if (temp.total > ks.total)
    {
      return temp;
    }
    else
    {
      temp = ks;
    }
  }
  return ks;
}

/*
Função de perturbação da ILS, altera aleatoriamente o estado dos itens da mochila, aumenta o nível de perturbaçao gradativamente.
*/
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

/*
ILS, utilizada com o intuito de escapar de ótimos locais, em busca do ótimo global.
*/
Mochila Iterated_Local_Search(Mochila ks, int itr)
{
  Mochila temp;
  int r = 2;
  for (int i = 0; i < itr; i++)
  {
    temp = perturbate(ks, r);
    temp = local_search(temp);
    if (ks.total < temp.total && temp.capacidade >= 0)
    {
      return temp;
    }
    r++;
  }
  return ks;
}

/*
Algoritmo guloso-aleatório, recebe um alfa como parâmetro que define sua aleatoriedade, quanto mais próximo de 1 mais de característica gulosa é a solução, quanto mais próximo de 0 mais aleatória.
Utiliza de um vetor RCL(Restricted candidate list), uma lista dos melhores canditados para serem selecionados, tem impacto direto na aleatoriedade e gulosidade da solução.
*/

Mochila Greedy_Randomized_Construction(Mochila ks, float alfa)
{
  mt19937 rng(std::random_device{}());

  vector<Item *> temp_itens;
  for (int j = 0; j < ks.itens.size(); j++)
  {
    temp_itens.push_back(&ks.itens.at(j));
  }

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

    uniform_int_distribution<int> distribution(0, RCL.size() - 1);
    int r_index = distribution(rng);
    Item *r_item = RCL.at(r_index);

    if (ks.capacidade - r_item->peso >= 0 && r_item->position == 0)
    {
      ks.capacidade -= r_item->peso;
      ks.total += r_item->beneficio;
      r_item->position = 1;
    }

    auto itr = std::remove_if(temp_itens.begin(), temp_itens.end(), [&](Item *a)
                              { return a->id == RCL.at(r_index)->id; });

    temp_itens.erase(itr, temp_itens.end());
  }
  return ks;
}


/*
Método grasp, alfa representa a aleatoridade da solução gulosa obtida na fase de construção, GRASPmax representa a quantidade iteração do método e ILSmax representa a quantidade de iteração da busca local, no caso ILS.
*/
Mochila grasp(Mochila ks, float alfa, int GRASPmax, int ILSmax)
{
  sort(ks.itens.begin(), ks.itens.end(), compare);
  Mochila solution = ks;
  Mochila temp_solution;

  for (int k = 0; k < GRASPmax; k++)
  {
    temp_solution = Greedy_Randomized_Construction(ks, alfa);
    temp_solution = Iterated_Local_Search(temp_solution, ILSmax);
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
  knapsack = grasp(knapsack, 0.9, 10, 100);

  end = clock();

  cout << "Total: " << knapsack.total << endl;
  double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

  cout << "\n\nTime taken : " << fixed
       << time_taken * 1000 << setprecision(5);
  cout << " ms \n\n " << endl;

  return 0;
}