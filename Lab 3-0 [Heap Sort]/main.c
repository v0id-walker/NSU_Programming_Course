#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sift_down(int array[], int size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && array[left] > array[largest]) {
        largest = left;
    }

    if (right < size && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != index) {
        swap(&array[index], &array[largest]);
        sift_down(array, size, largest);
    }
}

void heap_sort(int array[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        sift_down(array, size, i);
    }

    for (int i = size - 1; i >= 0; i--) {
        swap(&array[0], &array[i]);
        sift_down(array, i, 0);
    }
}

void print_array(int array[], int size) {
    printf("%d", array[0]);

    for (int i = 1; i < size; i++) {
        printf(" %d", array[i]);
    }
}


int main() {

    int array_size = 0;
    if (scanf("%d", &array_size) != 1) {
        return 1;
    }
    int array[array_size];

    for (int i = 0; i < array_size; i++) {
        if (scanf("%d", &array[i]) != 1) {
            return 1;
        }
    }

    heap_sort(array, array_size);

    print_array(array, array_size);

    return 0;
}
