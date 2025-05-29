#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Declaracoes dos algoritmos
void bubble_sort(int *arr, int n, long long *comparacoes);
void insertion_sort(int *arr, int n, long long *comparacoes);
void merge_sort(int *arr, int l, int r, long long *comparacoes);
void quick_sort(int *arr, int l, int r, long long *comparacoes);

#define REPETICOES 5

// Leitura do arquivo
int* ler_arquivo(const char *nome, int *tamanho) {
    FILE *fp = fopen(nome, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    int capacidade = 1000;
    int *vetor = malloc(capacidade * sizeof(int));
    if (!vetor) {
        fprintf(stderr, "Erro: falta de memoria ao alocar vetor\n");
        fclose(fp);
        exit(1);
    }

    int val, count = 0;
    while (fscanf(fp, "%d", &val) == 1) {
        if (count >= capacidade) {
            capacidade *= 2;
            int *novo = realloc(vetor, capacidade * sizeof(int));
            if (!novo) {
                fprintf(stderr, "Erro: realloc falhou\n");
                free(vetor);
                fclose(fp);
                exit(1);
            }
            vetor = novo;
        }
        vetor[count++] = val;
    }

    fclose(fp);
    *tamanho = count;
    return vetor;
}

void copiar_array(int *origem, int *destino, int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

void testar_algoritmo(const char *arquivo, const char *algoritmo, FILE *saida) {
    int n;
    int *original = ler_arquivo(arquivo, &n);
    int *copia = malloc(n * sizeof(int));
    if (!copia) {
        fprintf(stderr, "Erro: nao foi possivel alocar memoria para copia (n = %d)\n", n);
        free(original);
        exit(1);
    }

    long long total_comparacoes = 0;
    double total_tempo = 0.0;

    printf("Executando algoritmo '%s' no arquivo '%s' com %d elementos (%d repeticoes)\n",
           algoritmo, arquivo, n, REPETICOES);

    for (int i = 0; i < REPETICOES; i++) {
        copiar_array(original, copia, n);

        long long comparacoes = 0;
        clock_t ini = clock();

        if (strcmp(algoritmo, "bubble") == 0)
            bubble_sort(copia, n, &comparacoes);
        else if (strcmp(algoritmo, "insertion") == 0)
            insertion_sort(copia, n, &comparacoes);
        else if (strcmp(algoritmo, "merge") == 0)
            merge_sort(copia, 0, n - 1, &comparacoes);
        else if (strcmp(algoritmo, "quick") == 0)
            quick_sort(copia, 0, n - 1, &comparacoes);
        else {
            printf("Algoritmo invalido\n");
            free(original);
            free(copia);
            return;
        }

        clock_t fim = clock();
        total_comparacoes += comparacoes;
        total_tempo += (double)(fim - ini) / CLOCKS_PER_SEC;
    }

    int tamanho;
    char tipo[20];
    sscanf(arquivo, "entradas/entrada_%d_%[^.].txt", &tamanho, tipo);

    fprintf(saida, "%s,%s,%d,%.0f,%.6f\n", algoritmo, tipo, tamanho,
            (double)total_comparacoes / REPETICOES,
            total_tempo / REPETICOES);

    fflush(saida);  // forca gravacao no disco

    free(original);
    free(copia);

    printf("Concluido: %s em %s\nMedia de comparacoes: %.2f\nTempo medio: %.10f s\n\n",
           algoritmo, arquivo,
           (double)total_comparacoes / REPETICOES,
           total_tempo / REPETICOES);
}

int main() {
    const char *algoritmos[] = { "bubble", "insertion", "merge", "quick" };
    const char *tipos[] = { "sorted", "random", "reverse" };
    int tamanhos[] = { 1000, 10000, 100000, 500000, 1000000 };

    printf("Iniciando testes de performance dos algoritmos...\n");
    FILE *saida = fopen("resultados/resultados_5rep.csv", "w");
    if (!saida) {
        perror("Erro ao abrir arquivo CSV");
        return 1;
    }

    fprintf(saida, "algoritmo,tipo,tamanho,comparacoes,tempo\n");

    for (int a = 0; a < 4; a++) {
        for (int t = 0; t < 3; t++) {
            for (int s = 0; s < 5; s++) {
                char nome_arquivo[100];
                sprintf(nome_arquivo, "entradas/entrada_%d_%s.txt", tamanhos[s], tipos[t]);
                printf("Rodando %s em %s...\n", algoritmos[a], nome_arquivo);
                testar_algoritmo(nome_arquivo, algoritmos[a], saida);
                printf("----------\n");
            }
        }
    }

    fclose(saida);
    printf("Todos os resultados foram salvos em 'resultados/resultados_5rep.csv'\n");
    printf("Fim da execucao.\n");
    return 0;
}
