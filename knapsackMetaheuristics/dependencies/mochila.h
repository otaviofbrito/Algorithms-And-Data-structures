#ifndef MOCHILA
#define MOCHILA

#include <vector>

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
  std::vector<Item> itens;
};

#endif
