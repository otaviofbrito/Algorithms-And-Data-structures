#include <string.h>
#include <iostream>
#include <fstream>
#include "Mochila.cpp"
#include "Itens.cpp"
#include "Item.cpp"



using namespace std;



int main(int argc, char const *argv[])
{
  

  Mochila *bag = new Mochila(100);
  Itens *itens = new Itens(3);

  Item *item1 = new Item(10, 4);
  item1->setRatio(item1->getBeneficio()/item1->getPeso());

  Item *item2 = new Item(55, 95);
  item2->setRatio((double)item2->getBeneficio()/(double)item2->getPeso());

  Item *item3 = new Item(5, 32);
  item3->setRatio(item3->getBeneficio()/item3->getPeso());


  bag->setItem(item1);
  itens->setItem(item1);
  item1->setPosition(1);
  bag->setItem(item2);
  itens->setItem(item2);
  item2->setPosition(1);
  bag->setItem(item3);
  itens->setItem(item1);
  item3->setPosition(1);


  cout << "MOCHILA: " << bag->getCapaciade() << " volume: " << bag->getLength() << endl;
  for(int i=0; i < bag->getLength(); i++){
    Item x = *bag->getItem(i);
   
    cout << "ITEM " << i <<": \n" << " Peso: " << x.getPeso() << " Beneficio: " << x.getBeneficio() << endl;
    cout << "ESTA? :" << x.getPosition() << " RATIO: " << x.getRatio() << endl;
  }


  return 0;
}
