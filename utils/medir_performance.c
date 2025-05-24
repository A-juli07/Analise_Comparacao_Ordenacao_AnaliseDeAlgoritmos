#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Declarações dos algoritmos
void bubble_sort(int *arr, int n, long long *comparacoes);
void insertion_sort(int *arr, int n, long long *comparacoes);
void merge_sort(int *arr, int l, int r, long long *comparacoes);
void quick_sort(int *arr, int l, int r, long long *comparacoes);

// Leitura do arquivo
int* ler_arquivo(const char *nome, int *tamanho) {
    FILE *fp = fopen(nome, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    int capacidade = 1000;
    int *vetor = malloc(capacidade * sizeof(int));
    if (!vetor) exit(1);

    int val, count = 0;
    while (fscanf(fp, "%d", &val) == 1) {
        if (count >= capacidade) {
            capacidade *= 2;
            vetor = realloc(vetor, capacidade * sizeof(int));
        }
        vetor[count++] = val;
    }

    fclose(fp);
    *tamanho = count;
    return vetor;
}

// Executa e mede
void testar_algoritmo(const char *arquivo, const char *algoritmo, FILE *saida) {
    int n;
    int *vetor = ler_arquivo(arquivo, &n);
    long long comparacoes = 0;
    clock_t ini, fim;

    ini = clock();
    if (strcmp(algoritmo, "bubble") == 0)
        bubble_sort(vetor, n, &comparacoes);
    else if (strcmp(algoritmo, "insertion") == 0)
        insertion_sort(vetor, n, &comparacoes);
    else if (strcmp(algoritmo, "merge") == 0)
        merge_sort(vetor, 0, n - 1, &comparacoes);
    else if (strcmp(algoritmo, "quick") == 0)
        quick_sort(vetor, 0, n - 1, &comparacoes);
    else {
        printf("Algoritmo inválido\n");
        free(vetor);
        return;
    }
    fim = clock();

    double tempo = (double)(fim - ini) / CLOCKS_PER_SEC;

    // Extrai nome e tipo do arquivo
    int tamanho;
    char tipo[20];
    sscanf(arquivo, "entradas/entrada_%d_%[^.].txt", &tamanho, tipo);

    fprintf(saida, "%s,%s,%d,%lld,%.6f\n", algoritmo, tipo, tamanho, comparacoes, tempo);

    free(vetor);
}

int main() {
    const char *arquivos[] = {
        "bubble", "insertion", "merge", "quick"
    };

    FILE *saida = fopen("resultados/resultados.csv", "w");
    if (!saida) {
        perror("Erro ao abrir CSV");
        return 1;
    }

    fprintf(saida, "algoritmo,tipo,tamanho,comparacoes,tempo\n");

    for (int a = 0; a < 4; a++) {
        for (int t = 0; t < 3; t++) {
            const char *tipo[] = {"sorted", "random", "reverse"};
            for (int s = 0; s < 5; s++) {
                int tamanhos[] = {1000, 10000, 100000, 500000, 1000000};
                char nome_arquivo[100];
                sprintf(nome_arquivo, "entradas/entrada_%d_%s.txt", tamanhos[s], tipo[t]);
                printf("Executando %s em %s...\n", arquivos[a], nome_arquivo);
                testar_algoritmo(nome_arquivo, arquivos[a], saida);
            }
        }
    }

    fclose(saida);
    printf("Resultados salvos em resultados/resultados.csv\n");

    return 0;
}
