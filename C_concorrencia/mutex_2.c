/**
Copyright [2021] Bernardo Borges Sandoval
Programa dedicado a mostrar o uso de mutex em C
**/

/**
Explicacao trylock
o trylock funciona de forma similar ao lock com 2 principais diferencas
1. Mesmo que ele nao obtenha o lock (mutex travado) a thread nao para
2. Quando ele obtem o lock a funcao retorna 0, caso contrario retorna um valor erro que geralmente nao importa
**/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

#define n_threads 5000

int c1 = 0, c2 = 0, c3 = 0;
pthread_mutex_t mtx_1, mtx_2, mtx_3; //Mutex


/**
Isso aqui eh um busywait e o professor vai te dar esporro se tu fizer isso
Isso eh so pra passar a ideia
**/
void *funcao() {
    while(1) {
        if (pthread_mutex_trylock(&mtx_1) == 0) {
            // printf("[Thread] Entrei em 1!\n");
            c1++;
            usleep(1);
            pthread_mutex_unlock(&mtx_1);
            break;
        }
        if (pthread_mutex_trylock(&mtx_2) == 0) {
            // printf("[Thread] Entrei em 2!\n");
            c2++;
            usleep(2);
            pthread_mutex_unlock(&mtx_2);
            break;
        }
        if (pthread_mutex_trylock(&mtx_3) == 0) {
            // printf("[Thread] Entrei em 3!\n");
            c3++;
            usleep(4);
            pthread_mutex_unlock(&mtx_3);
            break;
        }
        sleep(1);
    }

    return NULL; // ou return NULL;
}

int main() {

    pthread_t threads[n_threads];

    //Inicializacao do mutex
    pthread_mutex_init(&mtx_1, NULL);
    pthread_mutex_init(&mtx_2, NULL);
    pthread_mutex_init(&mtx_3, NULL);

    for (int i = 0; i < n_threads; i++)
        pthread_create(&threads[i], NULL, (void *)&funcao, NULL);

    for (int i = 0; i < n_threads; i++)
        pthread_join(threads[i], NULL);

    //Finalizacao do mutex
    pthread_mutex_destroy(&mtx_1);
    pthread_mutex_destroy(&mtx_2);
    pthread_mutex_destroy(&mtx_3);

    printf("c1: %d\tc2: %d\tc3: %d\n", c1, c2, c3);
    return 0;
}
