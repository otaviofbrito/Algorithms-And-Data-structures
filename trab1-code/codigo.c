#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

typedef struct
{
    unsigned int peso;
    int beneficio;
} type_item;

int max(int a, int b) { return (a > b) ? a : b; }

// sorting for greedy algorithim
void merge(type_item arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    type_item L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if ((double)L[i].beneficio / L[i].peso >= (double)R[j].beneficio / R[j].peso)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(type_item arr[], int l, int r)
{
    if (l < r)
    {

        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// dinamica bottom-up
int algoritmo_1(int capacidade, type_item items[], int n)
{
    int i, j;
    int tabela[2][capacidade + 1];

    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= capacidade; j++)
        {
            if (i == 0 || j == 0)
                tabela[i % 2][j] = 0;
            else if (items[i - 1].peso <= j)
                tabela[i % 2][j] = max(items[i - 1].beneficio + tabela[(i - 1) % 2][j - items[i - 1].peso],
                                       tabela[(i - 1) % 2][j]);
            else
                tabela[i % 2][j] = tabela[(i - 1) % 2][j];
        }
    }
    return tabela[n % 2][capacidade];
}

// bruteforce
int algoritmo_2(int capacidade, type_item items[], int n)
{
    int bestPeso = 0;
    int bestBenefico = 0;
    int *ar = (int *)calloc(capacidade, sizeof(int));
    int j;
    for (int i = 0; i < pow(2, n); i++)
    {
        int j = n - 1;
        int tempPeso = 0;
        int tempBeneficio = 0;
        int k;

        while (ar[j] != 0 && j > 0)
        {
            ar[j] = 0;
            j--;
        }

        ar[j] = 1;

        for (k = 0; k < n; k++)
        {
            if (ar[k] == 1)
            {
                tempPeso = tempPeso + items[k].peso;
                tempBeneficio = tempBeneficio + items[k].beneficio;
            }
        }
        if ((tempBeneficio > bestBenefico) && (tempPeso <= capacidade))
        {
            bestBenefico = tempBeneficio;
        }
    }
    free(ar);
    return bestBenefico;
}

// greedy
int algoritmo_3(int capacidade, type_item items[], int n)
{
    int solution = 0;
    int i = 0;

    mergeSort(items, 0, n);
    for (int k = 0; k < n; k++)
    {
        if (items[k].peso <= capacidade)
        {
            solution = solution + items[k].beneficio;
            capacidade = capacidade - items[k].peso;
        }
    }

    return solution;
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
    if (fp == NULL)
    {
        puts("Não foi possível abrir o arquivo");
        exit(0);
    }

    fscanf(fp, "%d %d", n_items, capacidad);
    printf("Número de elementos: %d, Capacidade: %d\n", *n_items, *capacidad);

    type_item *items = (type_item *)malloc(*n_items * sizeof(type_item));

    for (int i = 0; i < *n_items; i++)
    {
        fscanf(fp, "%d %d", &items[i].beneficio, &items[i].peso);
    }

    fclose(fp);

    return items;
}

int main(int argc, char *argv[])
{
    // time benchmark
    clock_t start_time = clock();

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
        printf("%d\n", algoritmo_1(capacidad, items, n_items));
    }
    else if (strcmp(argv[2], "2") == 0)
    {
        printf("%d\n", algoritmo_2(capacidad, items, n_items));
    }
    else if (strcmp(argv[2], "3") == 0)
    {
        printf("%d\n", algoritmo_3(capacidad, items, n_items));
    }
    else
    {
        printf("\nSelecione um algoritmo\n");
        return 1;
    }
    free(items);

    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Done in %f ms\n", elapsed_time * 1000);

    return 0;
}

/// usr/bin/time -v myapp
// valgrind myapp
