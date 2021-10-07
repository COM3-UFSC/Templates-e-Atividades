/**
Copyright [2021] Bernardo Borges Sandoval
Programa dedicado a mostrar o uso de mutex em C
**/

/**
Basico de mutex
1. criacao:
pthread_mutex_t mutex
declaracao preferencialmente em escopo global, ou escopo em que todas as funcoes que o usam tenham acesso
2. inicializacao:
pthread_mutex_init(&mutex,NUll)
o mutex tem de ser inicializado antes de ser usado. Recebe o endereco do mutex como parametro e NULL (confia)
3. finalizacao:
pthread_mutex_destroy(&mutex)
o mutex tem que ser finalizado antes do fim do programa mas depois de ser usado. Recebe apenas o endereco do mutex como parametro
**/

/**
Explicacao lock e unlock
tanto o lock quanto unlock recebem como parametro o endereco de um mutex
um mutex pode estar travado ou aberto
quando uma thread encontra o lock e o mutex esta aberto, ela trava o mutex e continua rodando
quando ela encontra o unlock ela abre o mutex e continua rodando
quando uma thread encontra o lock e o mutex esta travado ela espera ate ele abrir pra entao trava-lo e prosseguir
isso faz com que apenas uma thread execute o codigo entre o lock e unlock por vez
**/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

#define n_threads 15
#define n_loops 10

int contador_global = 0;
pthread_mutex_t mtx; //Mutex


void *incrementador() {
    for (int i = 0; i < n_loops; i++) {

        pthread_mutex_lock(&mtx);
        contador_global += 1;
        pthread_mutex_unlock(&mtx);

    }
    return NULL; // ou return NULL;
}

int main() {

    pthread_t threads[n_threads];

    pthread_mutex_init(&mtx, NULL); //Inicializacao do mutex

    for (int i = 0; i < n_threads; i++)
        pthread_create(&threads[i], NULL, (void *)&incrementador, NULL);

    for (int i = 0; i < n_threads; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mtx); //Finalizacao do mutex

    printf("Contador: %d\n", contador_global);
    return 0;
}
