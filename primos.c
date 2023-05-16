#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_primes(void* arg) {
    int n = *((int*)arg);
    for (int i = 1; i <= n; i++) {
        int is_prime = 1;
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            printf("%d ", i);
        }
    }
    printf("\n");
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: ./primos <numero>\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("O número deve ser maior que zero.\n");
        return 1;
    }

    pthread_t thread;
    pthread_create(&thread, NULL, print_primes, (void*)&n);
    pthread_join(thread, NULL);

    return 0;
}