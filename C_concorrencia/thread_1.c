/**
Copyright [2021] Bernardo Borges Sandoval
Programa dedicado a mostrar o uso de Fork em C
**/

/**
IMPORTANTE: COMPILE COM A SEGUINTE LINHA:
gcc -pthread thread_1.c -o thread_1
PRECISA DO -pthread
**/

/**
Explicacao pthread_t
Tipo de uma thread, pense: int pra 10, char pra 't', float pra 10.4, pthread_t pra thread
esse "_t" geralmente entrega que eh um tipo, eh t de tipo
**/

/**
Explicacao de pthread_create
Recebe 4 parametros:
1. A thread em si (declarada com pthread_t)
2. NULL (eh coisa pra multiplos processos e multiplas threads, so confia)
3. A funcao que a thread vai rodar
    repare que tem que chamar o endereco e fazer o casting (void *) (Nem sempre eh necessario mas eh boa pratica)
    repare tambem que a funcao eh void *funcao e nao void funcao
    isso eh devido ao fato de que a thread recebe a propria funcao como parametro e nao uma chamada a ela
4. Argumentos da thread (Exploro isso no proximo arquivo)
**/

/**
Explicacao do pthread_join
Como wait so que pra threads, ele espera aquela thread especifica parar antes de continuar
**/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h> ///BIBLIOTECA PTHREAD

int contador_global = 0;

void *funcao_thread(){
    for (int i = 0; i < 100; ++i)
        contador_global++;
    return NULL; //tem que retornar NULL ou uma ponteira contendo null, void* eh diferente de void como funcao.
}


int main() {

    pthread_t nova_thread; //Criacao da thread

    pthread_create(&nova_thread, NULL, (void *)&funcao_thread, NULL);

    pthread_join(nova_thread, NULL);

    printf("Contador: %d\n", contador_global);
    return 0;
}
