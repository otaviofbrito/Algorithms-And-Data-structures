#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm> 

#include "Mochila.cpp"
#include "Itens.cpp"
#include "Item.cpp"


using namespace std;


struct less_than_key
{
    inline bool operator() (const Item &item1, const Item &item2)
    {
        return (item1.getRatio() > item2.getRatio());
    }
};


Mochila *guloso_aleatorio(Itens *itens, float r = 0.1){

  sort(itens->getList().begin(), itens->getList().end(), itens->isGreater());

}

Itens *scant_test(char const *file_name, int *n_items, int *capacidad)
{

  Itens *itens = new Itens(*n_items);

  ifstream test_file;
  test_file.open("f1_l-d_kp_10_269");

  if (!test_file.is_open())
  {
    cout << "UNABLE TO LOCATE FILE";
    exit(0);
  }

  test_file >> *n_items;
  test_file >> *capacidad;

  itens->setQuantidade(*n_items);

  for(int i = 0; i < *n_items; i++){
    int pes, ben;
    test_file >> pes;
    test_file >> ben;
    Item *item = new Item(pes, ben);
    item->setRatio((double)item->getBeneficio()/(double)item->getPeso());
    itens->setItem(item);
  }


  return itens;
}

int main(int argc, char const *argv[])
{

  int n_items, capacidad;


  Itens *itens;

  /*
  if (argc != 3)
  {
    printf("Uso: %s <nome do arquivo de entrada> <algoritmo>\n", argv[0]);
    return 1;
  }
  */



  itens = scant_test(argv[1], &n_items, &capacidad);

    cout << "MOCHILA: " << itens->getQuantidade() << " volume: " << itens->getLength() << endl;

  for(int i=0; i < itens->getLength(); i++){
    Item x = *itens->getItem(i);
   
    cout << "ITEM " << i <<": \n" << " Peso: " << x.getPeso() << " Beneficio: " << x.getBeneficio() << endl;
    cout << "ESTA? :" << x.getPosition() << " RATIO: " << x.getRatio() << endl;
  }
  // imprimir_items(items, n_items);

  return 0;
}
