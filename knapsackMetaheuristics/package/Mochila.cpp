#include "Item.h"
#include <vector>

class Mochila
{
private:
  int capacidade;
  std::vector<Item *> itens;

public:
  Mochila(int o_capacidade)
  {
    capacidade = o_capacidade;
  }

  void setCapacidade(int o_capacidade)
  {
    capacidade = o_capacidade;
  }

  void setItem(Item *o_item)
  {
    if (capacidade - o_item->getPeso() >= 0)
    {
      itens.push_back(o_item);
    }
  }

  int getCapaciade()
  {
    return capacidade;
  }

  Item *getItem(int o_index)
  {
    return itens.at(o_index);
  }

  int getLength()
  {
    return itens.size();
  }
};
