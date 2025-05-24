#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void embaralhar(int *vetor, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = tmp;
    }
}

void gerar_arquivo(int n, const char *tipo) {
    int *vetor = malloc(n * sizeof(int));
    if (!vetor) {
        printf("Erro de alocação\n");
        exit(1);
    }

    // Preencher vetor
    if (strcmp(tipo, "sorted") == 0) {
        for (int i = 0; i < n; i++)
            vetor[i] = i + 1;
    } else if (strcmp(tipo, "reverse") == 0) {
        for (int i = 0; i < n; i++)
            vetor[i] = n - i;
    } else if (strcmp(tipo, "random") == 0) {
        for (int i = 0; i < n; i++)
            vetor[i] = i + 1;
        embaralhar(vetor, n);
    } else {
        printf("Tipo inválido: %s\n", tipo);
        free(vetor);
        return;
    }

    // Nome do arquivo
    char nome_arquivo[100];
    sprintf(nome_arquivo, "entradas/entrada_%d_%s.txt", n, tipo);

    // Gravar arquivo
    FILE *fp = fopen(nome_arquivo, "w");
    if (!fp) {
        perror("Erro ao criar arquivo");
        free(vetor);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", vetor[i]);
    }

    fclose(fp);
    free(vetor);
    printf("Arquivo gerado: %s\n", nome_arquivo);
}

int main() {
    srand(time(NULL));

    int tamanhos[] = {1000, 10000, 100000, 500000, 1000000};
    const char *tipos[] = {"sorted", "random", "reverse"};

    for (int i = 0; i < sizeof(tamanhos)/sizeof(int); i++) {
        for (int j = 0; j < 3; j++) {
            gerar_arquivo(tamanhos[i], tipos[j]);
        }
    }

    return 0;
}
