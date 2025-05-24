int partition(int *arr, int low, int high, long long *comparacoes) {
    int pivot = arr[high], i = low - 1;

    for (int j = low; j < high; j++) {
        (*comparacoes)++;
        if (arr[j] <= pivot) {
            i++;
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    int tmp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = tmp;
    return i + 1;
}

void quick_sort(int *arr, int low, int high, long long *comparacoes) {
    if (low < high) {
        int pi = partition(arr, low, high, comparacoes);
        quick_sort(arr, low, pi - 1, comparacoes);
        quick_sort(arr, pi + 1, high, comparacoes);
    }
}
