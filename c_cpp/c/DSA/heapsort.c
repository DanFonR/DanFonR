#include <stdio.h>
#define swap(a, b) { int temp = (a); (a) = (b); (b) = temp; }

void print_arr(int arr[], size_t size) {
    putchar('{');

    for (size_t i = 0; i < size; i++)
        printf("%d, ", arr[i]);

    puts("\b\b}");
}

void heapify(int array[], const size_t size, size_t root_index) {
    size_t largest, left, right, max_child;

    while (1) {
        largest = root_index;
        left = 2*root_index + 1;
        right = left + 1;

        if (left < size && array[left] > array[largest])
            largest = left;
        if (right < size && array[right] > array[largest])
            largest = right;

        if (largest == root_index) return;

        swap(array[root_index], array[largest]);

        root_index = largest;
    }

}

void heapsort(int array[], size_t size) {
    if (size < 2) return;

    for (size_t node = size / 2 - 1; ; node--) {
        heapify(array, size, node);

        if (node == 0) break;
    }

    while (--size > 0) {
        swap(array[0], array[size]);

        heapify(array, size, 0);
    }
}

int main() {
    int a[] = {6, 2, 3, 3, 2, 1, 2, 2, 4};
    size_t size = sizeof(a)/sizeof(a[0]);

    heapsort(a, size);
    print_arr(a, size);

    return 0;
}
