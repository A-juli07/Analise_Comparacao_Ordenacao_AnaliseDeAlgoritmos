#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int l, int m, int r, long long *comparacoes) {
    int n1 = m - l + 1;
    int n2 = r - m;

    if (n1 <= 0 || n2 <= 0) {
        fprintf(stderr, "Erro: Tamanhos inválidos (n1=%d, n2=%d)\n", n1, n2);
        exit(EXIT_FAILURE);
    }

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória (n1=%d, n2=%d)\n", n1, n2);
        free(L); 
        free(R); 
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        (*comparacoes)++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(int *arr, int l, int r, long long *comparacoes) {
    if (l < r) {
        int m = l + (r - l) / 2; 
        merge_sort(arr, l, m, comparacoes);
        merge_sort(arr, m + 1, r, comparacoes);
        merge(arr, l, m, r, comparacoes);
    }
}
