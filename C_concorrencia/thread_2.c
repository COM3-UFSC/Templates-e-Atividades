/**
Copyright [2021] Bernardo Borges Sandoval
Programa dedicado a mostrar o uso de Fork em C
**/

/**
Passando parametros pra threads
Independente do tipo em pthread_create tem que fazer casting com (void *) pra virar uma ponteira de void
A funcao recebe a ponteira de void
Quando usar a variavel na funcao tem que fazer o castind pro tipo original (int *) e fazer a deferencia *(int *)
**/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

#define num 10

void *funcao_thread(void *parametro){
    printf("[Thread %d] rodando...\n", *(int *)parametro);
    sleep(1);
    return NULL;
}

int main() {

    pthread_t thread[num]; //Criacao da thread

    /**
    Essa gambiarra eh uma solucao pra um problema que vai te assombrar. (experimenta passar i direto como parametro, roda alguma vezes.
    Tem numero que repete e numero faltando, esquisito neh? poise, tenta entender o porquê)
    **/
    int parametro[num];
    for (int i = 0; i < num; ++i)
        parametro[i] = i;

    /**
    Repare como as threads sao executadas em ordem "aleatoria"
    **/

    // Criacao de 100 threads
    for (int i = 0; i < num; ++i) {
        pthread_create(&thread[i], NULL, (void *)&funcao_thread, (void *)&parametro[i]);
    }

    // Join das 100 threads
    for (int i = 0; i < num; ++i)
        pthread_join(thread[i], NULL);

    printf("Todas as threads finalizadas!\n");
    return 0;
}
