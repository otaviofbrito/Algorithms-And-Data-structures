#include <iostream>
#include <algorithm>
#include <vector>


using namespace std; 


class type_item 
{
public:
    unsigned int peso;
    int beneficio;
    double ratio;

    bool is_greater(const type_item &item1, const type_item &item2) {
        if (item1.ratio > item2.ratio) {
            return 1;
        } else {
            return 0;
        }
    }
}







type_item greedyRandom(int capacidade, std::vector<type_item> items, int n, float r = 0.1){
    int solution = 0;
    int i = 0;
   
    std::vector<type_item> items;
    for (auto i : items) {
        i.ratio = i.beneficio/i.peso;
    }
    
    sort (items, sizeof(items)/sizeof(items[0]), &is_greater);
     




    // for(int i = 0; i < n; i++){
    //     ratio[i] = new type_item;
    //     ratio[i]->ratio = (items->beneficio/items->peso);
    // }

    //     sort(ratio, ratio + n, &is_greater);







}
void imprimir_items(type_item *items, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Peso: %d, Beneficio: %d\n", items[i].peso, items[i].beneficio);
    }
}


type_item *ler_items(char *filename, int *n_items, int *capacidad)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)void imprimir_items(type_item *items, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Peso: %d, Beneficio: %d\n", items[i].peso, items[i].beneficio);
    }
}

    {
        puts("Não foi possível abrir o arquivo");
        exit(0);
    }is_greater
    {
        fscanf(fp, "%d %d", &items[i].beneficio, &items[i].peso);
    }

    fclose(fp);

    return items;void imprimir_items(type_item *items, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Peso: %d, Beneficio: %d\n", items[i].peso, items[i].beneficio);
    }
}

}



int main(int argc, char *argv[])
{
    // time benchmark

    int n_items, capacidad;

    if (argc != 3)
    {
        printf("Uso: %s <nome do arquivo de entrada> <algoritmo>\n", argv[0]);
        return 1;
    }

    type_item *items = ler_items(argv[1], &n_items, &capacidad);
    imprimir_items(items, n_items);

    if (strcmp(argv[2], "1") == 0)
    {
        //printf("%d\n", progDinamica(capacidad, items, n_items));
    }
    else if (strcmp(argv[2], "2") == 0)
    {
        //printf("%d\n", forcaBruta(capacidad, items, n_items));
    }
    else if (strcmp(argv[2], "3") == 0)
    {
        //printf("%d\n", algGuloso(capacidad, items, n_items));
    }
    else
    {
        printf("\nSelecione um algoritmo\n");
        return 1;
    }
    delete(items);


    return 0;
}


