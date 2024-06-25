#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 1
#define GROWTH_FACTOR 2

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector *vec) {
    vec->data = malloc(sizeof(int) * INITIAL_CAPACITY);
    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
}

void vector_free(Vector *vec) {
    free(vec->data);
    vec->size = 0;
    vec->capacity = 0;
}

void vector_push_back(Vector *vec, int value) {
    if (vec->size >= vec->capacity) {
        // Resize the vector's capacity
        size_t new_capacity = vec->capacity * GROWTH_FACTOR;
        vec->data = realloc(vec->data, sizeof(int) * new_capacity);
        if (vec->data == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        vec->capacity = new_capacity;
    }

    // Add the new value at the end of the vector
    vec->data[vec->size] = value;
    vec->size++;
}

int main() {
    Vector vec;
    vector_init(&vec);

    // Add elements to the vector
    vector_push_back(&vec, 10);
    vector_push_back(&vec, 20);
    vector_push_back(&vec, 30);

    // Print the contents of the vector
    printf("Vector contents: ");
    for (size_t i = 0; i < vec.size; i++) {
        printf("%d ", vec.data[i]);
    }
    printf("\n");

    // Free the vector memory
    vector_free(&vec);

    return 0;
}
