#include "Item.h"
#include <vector>



class Itens {
  private:
    int quantidade;
    std::vector<Item *> itens;

  public:
    Itens(int o_quantidade){
      quantidade = o_quantidade;
    }  

    void setQuantidade(int o_quantidade){
      quantidade = o_quantidade;
    }

    void setItem(Item *o_item){
      itens.push_back(o_item);
    }

    int getQuantidade(){
      return quantidade;
    }

    Item* getItem(int o_index){
      return itens.at(o_index);
    }

    int getLength(){
      return itens.size();
    }

    std::vector<Item *> getList(){
      return itens;
    }

    bool isGreater(Item *item1, Item *item2){
      return item1->getRatio()>item2->getRatio();
    }

};
