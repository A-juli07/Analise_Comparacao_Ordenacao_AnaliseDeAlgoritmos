int median_of_three(int *arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) {
        int tmp = arr[low]; arr[low] = arr[mid]; arr[mid] = tmp;
    }
    if (arr[mid] > arr[high]) {
        int tmp = arr[mid]; arr[mid] = arr[high]; arr[high] = tmp;
    }
    if (arr[low] > arr[mid]) {
        int tmp = arr[low]; arr[low] = arr[mid]; arr[mid] = tmp;
    }
    return mid; 
}

int partition(int *arr, int low, int high, long long *comparacoes) {
    int pivot_idx = median_of_three(arr, low, high);
    int tmp = arr[pivot_idx]; arr[pivot_idx] = arr[high]; arr[high] = tmp;

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        (*comparacoes)++;
        if (arr[j] <= pivot) {
            i++;
            tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    tmp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = tmp;
    return i + 1;
}

void quick_sort(int *arr, int low, int high, long long *comparacoes) {
    while (low < high) {
        int pi = partition(arr, low, high, comparacoes);

        if (pi - low < high - pi) {
            quick_sort(arr, low, pi - 1, comparacoes);
            low = pi + 1;
        } else {
            quick_sort(arr, pi + 1, high, comparacoes);
            high = pi - 1;
        }
    }
}
