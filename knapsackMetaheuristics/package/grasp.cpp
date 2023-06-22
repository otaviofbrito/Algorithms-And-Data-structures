#include <string.h>
#include <iostream>
#include <fstream>
#include "Mochila.cpp"
#include "Itens.cpp"


using namespace std;

Itens *scant_test(char const *file_name, int *n_items, int *capacidad)
{

  Itens *itens = new Itens(*n_items);

  ifstream test_file;
  test_file.open(file_name);

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
    itens->setItem(item);
  }


  return itens;
}

int main(int argc, char const *argv[])
{

  int n_items, capacidad;


  Itens *itens;

  if (argc != 3)
  {
    printf("Uso: %s <nome do arquivo de entrada> <algoritmo>\n", argv[0]);
    return 1;
  }

  itens = scant_test(argv[1], &n_items, &capacidad);
  // imprimir_items(items, n_items);

  return 0;
}
