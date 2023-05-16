#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_THREADS 16

typedef struct {
    int start;
    int end;
} parameters;

int *array;
int *sorted_array;
int array_size;

void* sort_array(void* params) {
    parameters* p = (parameters*) params;
    int i, j, temp;

    for (i = p->start; i <= p->end; i++) {
        for (j = i + 1; j <= p->end; j++) {
            if (array[j] < array[i]) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    pthread_exit(NULL);
}

void* merge_arrays(void* params) {
    int i = 0, j = array_size / 2, k = 0;

    while (i < array_size / 2 && j < array_size) {
        if (array[i] < array[j]) {
            sorted_array[k] = array[i];
            i++;
        } else {
            sorted_array[k] = array[j];
            j++;
        }
        k++;
    }

    while (i < array_size / 2) {
        sorted_array[k] = array[i];
        i++;
        k++;
    }

    while (j < array_size) {
        sorted_array[k] = array[j];
        j++;
        k++;
    }

    pthread_exit(NULL);
}

double get_execution_time(struct timeval start, struct timeval end) {
    double start_sec = (double)start.tv_sec * 1000000.0 + (double)start.tv_usec;
    double end_sec = (double)end.tv_sec * 1000000.0 + (double)end.tv_usec;

    return (end_sec - start_sec) / 1000000.0;
}

void test_program(int size) {
    array_size = size;
    array = (int*)malloc(sizeof(int) * array_size);
    sorted_array = (int*)malloc(sizeof(int) * array_size);

    for (int i = 0; i < array_size; i++) {
        array[i] = rand() % 100;  // preenche o array com valores aleatórios
    }

    pthread_t threads[MAX_THREADS];
    parameters params[MAX_THREADS];

    int num_threads = array_size % 2 == 0 ? array_size / 2 : (array_size + 1) / 2;

    struct timeval start_time, end_time;
    double execution_time;

    gettimeofday(&start_time, NULL);  // inicia contagem de tempo

    // Cria threads classificadoras
    for (int i = 0; i < num_threads; i++) {
        params[i].start = i * (array_size / num_threads);
        params[i].end = (i + 1) * (array_size / num_threads) - 1;
        pthread_create(&threads[i], NULL, sort_array, (void*)&params[i]);
    }

    // Aguarda finalização das threads classificadoras
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Cria thread de mesclagem
    pthread_create(&threads[num_threads], NULL, merge_arrays, NULL);
    pthread_join(threads[num_threads], NULL);

    gettimeofday(&end_time, NULL);  // finaliza contagem de tempo

    execution_time = get_execution_time(start_time, end_time);
    printf("Tempo de execução para o array de tamanho %d: %.6f segundos\n", array_size, execution_time);

    free(array);
    free(sorted_array);
    }

    int main() {
    srand(time(NULL));
    // Teste do programa com diferentes tamanhos de array
    test_program(1000000);
    test_program(1500000);
    test_program(2500000);
    test_program(3000000);
    test_program(3500000);
    test_program(4000000);
    test_program(4500000);
    test_program(5000000);
    test_program(5500000);
    test_program(6000000);

    return 0;
    }