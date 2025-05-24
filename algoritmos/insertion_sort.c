void insertion_sort(int *arr, int n, long long *comparacoes) {
    for (int i = 1; i < n; i++) {
        int chave = arr[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;
            if (arr[j] > chave) {
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = chave;
    }
}
