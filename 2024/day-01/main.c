#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int * data;
    size_t capacity;
    size_t count;
} ints_t;

void array_init(ints_t * array){
    array->capacity = 2;
    array->count = 0;
    array->data = (int*)malloc(array->capacity * sizeof(array->data[0]));
}

void array_expand(ints_t * a, ints_t * b){
    a->capacity *= 2;
    b->capacity *= 2;
    int * new_data_a = (int*)realloc(a->data, a->capacity * sizeof(a->data[0]));
    a->data = new_data_a;
    int * new_data_b = (int*)realloc(b->data, b->capacity * sizeof(b->data[0]));
    b->data = new_data_b;
}

void split_arrays(ints_t * a, ints_t * b, int first, int second){
    if (a->count >= a->capacity) array_expand(a, b);
    a->data[a->count++] = first;
    b->data[b->count++] = second;
}

int compare_ints(const void * a, const void * b){
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int sum(ints_t * a, ints_t * b){
    int sum = 0;
    for (size_t i = 0; i < a->count; i ++){
        if (a->data[i] < b->data[i]){
            sum += b->data[i] - a->data[i];
        } else if (a->data[i] > b->data[i]){
            sum += a->data[i] - b->data[i];
        } else {
            sum += 0;
        }
    }
    return sum;
}

void array_destroy(ints_t * array){
    free(array->data);
}

int multiply_arrays(ints_t * a, ints_t * b){
    int sum = 0;
    for (size_t i = 0; i < a->count; i++){
        int count = 0;
        for (size_t j = 0; j < b->count; j++){
            if (a->data[i] == b->data[j]) count++;
        }
        sum += a->data[i] * count; 
    }
    return sum;
}

int main(){
    ints_t a;
    ints_t b;
    array_init(&a);
    array_init(&b);
    while (1){
        int first = 0;
        int second = 0;
        int ret = scanf("%d   %d", &first, &second);
        if (ret == EOF) break;
        split_arrays(&a, &b, first, second);
    }

    qsort(a.data, a.count, sizeof(int), compare_ints);
    qsort(b.data, b.count, sizeof(int), compare_ints);

    printf("sum: %d\n", sum(&a, &b));
    printf("multiply: %d\n", multiply_arrays(&a, &b));
    array_destroy(&a);
    array_destroy(&b);
    return 0;
}