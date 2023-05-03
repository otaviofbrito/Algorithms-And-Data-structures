#include <stdlib.h>
#include <stdio.h>

typedef struct {
    unsigned int peso;
    int beneficio;
} type_item;


int max(int a, int b) { return (a > b) ? a : b; }

//dinamica bottom-up
int algoritmo_1(int capacidade, type_item items[], int n) {
    int i, w;
    int K[n+1][capacidade+1];

    for(i=0; i<=n;i++){
        for(w = 0; w <= capacidade; w++){
            if(i==0 || w==0){
                K[i][w] = 0;
            }else if(items[i-1].peso <= w){
                K[i][w] = max(items[i-1].beneficio + K[i-1][w - items[i-1].peso], K[i-1][w]);
            }else{
                K[i][w] = K[i-1][w];
            }
        }
    }

    return K[n][capacidade];
 }






void algoritmo_2(void) { }
void algoritmo_3(void) { }

void imprimir_items(type_item *items, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("Peso: %d, Beneficio: %d\n", items[i].peso, items[i].beneficio);
    }
}

type_item *ler_items(char *filename, int *n_items, int *capacidad) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        puts("Não foi possível abrir o arquivo");
        exit(0);
    }

    fscanf(fp, "%d %d", n_items, capacidad);
    printf("Número de elementos: %d, Capacidade: %d\n", *n_items, *capacidad);

    type_item *items = (type_item *)malloc(*n_items * sizeof(type_item));

    for (int i = 0; i < *n_items; i++) {
        fscanf(fp, "%d %d", &items[i].peso, &items[i].beneficio);
    }

    fclose(fp);

    return items;
}


int main(int argc, char *argv[]) {
    int n_items, capacidad;

    if (argc != 3) {
        printf("Uso: %s <nome do arquivo de entrada> <algoritmo>\n", argv[0]);
        return 1;  
    }

    type_item *items = ler_items(argv[1], &n_items, &capacidad);
    imprimir_items(items, n_items);

    if (argv[2] == "1") {
        printf("teste");
       printf("%d", algoritmo_1(capacidad, items, n_items) );
    } else if (argv[2] == "2") {
        algoritmo_2();
    } else if (argv[2] == "3") {
        algoritmo_3();
    } else {
        printf("%d\n", algoritmo_1(capacidad, items, n_items));
        return 1;
    }
    free(items);
    return 0;
}