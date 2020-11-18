#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define BUBBLE 0
#define SELECTION 1
#define MERGE 2

void random_numbers(int numbers[], int index);

void bubble_sort (int numbers[], int index);
void selection_sort (int numbers[], int index);
void merge_sort (int numbers[], int p, int r);

void swap (int *a, int *b);

void merge (int numbers[], int p, int q, int r);

int main (void)
{
    char *index_str = malloc(10);
    int index = -1;
    do {
        printf("How many numbers would you like to sort? : ");
        fgets(index_str, 10, stdin);
        index = atoi(index_str);
    } while (index < 2 || index > 1000000);
    free(index_str);

    char *sort_type = malloc(30);
    int sorting_algorithms = -1;
    do {
        printf("Which sorting algorithm would you like to use? : ");
        fgets(sort_type, 30, stdin);
        for (int i = 0; sort_type[i] != '\0'; i++) {
            sort_type[i] = tolower(sort_type[i]);
        }
        if (!strcmp(sort_type, "bubble sort\n")) {
            sorting_algorithms = BUBBLE;
        } else if (!strcmp(sort_type, "selection sort\n")) {
            sorting_algorithms = SELECTION;
        } else if (!strcmp(sort_type, "merge sort\n")) {
            sorting_algorithms = MERGE;
        } else {
            sorting_algorithms = -1;
        }
    } while (sorting_algorithms != BUBBLE && sorting_algorithms != SELECTION && sorting_algorithms != MERGE);
    free(sort_type);

    int numbers[index];
    random_numbers(numbers, index);

    time_t start = time(NULL);
    if (sorting_algorithms == BUBBLE) {
        bubble_sort(numbers, index);
    } else if (sorting_algorithms == SELECTION) {
        selection_sort(numbers, index);
    } else if (sorting_algorithms == MERGE) {
        merge_sort(numbers, 0, index);
    } else {
        return 1;
    }
    time_t end = time(NULL);

    for (int i = 0; i < index; i++) {
        printf("%d\t", numbers[i]);
    }

    printf("\n");

    printf("The sorting took: %ld seconds\n", end - start);

    return 0;
}

void random_numbers(int numbers[], int index)
{
    time_t t;
    srand((unsigned) time(&t));

    for (int i = 0; i < index; i++) {
        numbers[i] = rand() % 100;
    }
}

void swap (int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort (int numbers[], int index)
{
    for (int i = 0, n = index - 1; i <= n; i++) {
        for (int j = 0, m = index - 2; j <= m; j++) {
            if (numbers[j] > numbers[j+1]) {
                swap(&numbers[j], &numbers[j+1]);
            }
        }
    }
}

void selection_sort (int numbers[], int index)
{
    int minimum;
    for (int i = 0, n = index - 1; i <= n; i++) {
        minimum = i;
        for (int j = i; j < n; j++) {
            if (numbers[j] < numbers[minimum]) {
                minimum = j;
            }
        }
        swap(&numbers[i], &numbers[minimum]);
    }
}

void merge_sort (int numbers[], int p, int r)
{
    if (p >= r) {
        return;
    }

    int q = (p + r) / 2;

    merge_sort(numbers, p, q);
    merge_sort(numbers, q + 1, r);
    merge(numbers, p, q, r);
}

void merge (int numbers[], int p, int q, int r)
{
    int left[q - p + 1];
    int right[r - q];

    for (int i = 0; i < (q - p + 1); i++) {
        left[i] = numbers[p + i];
    }
    for (int i = 0; i < (r - q); i++) {
        right[i] = numbers[q + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = p;
    while (i < (q - p + 1) && j < (r - q)) {
        if (left[i] <= right[j]) {
            numbers[k] = left[i];
            i++;
        } else {
            numbers[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < (q - p + 1)) {
        numbers[k] = left[i];
        i++;
        k++;
    }
    while (j < (r - q)) {
        numbers[k] = right[j];
        j++;
        k++;
    }
}