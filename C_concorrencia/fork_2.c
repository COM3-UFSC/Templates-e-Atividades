/**
Copyright [2021] Bernardo Borges Sandoval
Programa dedicado a mostrar o uso de Fork em C
**/

/**
Explicacao de Exit:
Encerra o processo, recebe um inteiro pra mandar como codigo de saida
**/

/**
Explicacao de Wait e Waitpid:
Wait recebe como parametro o endereco de um inteiro no qual colocora um exit status
O wait espera um processo filho arbitrario do processo que chamou o wait finalizar (atraves de um exit por exemplo)
O wait tambem retorna o pid deste filho. O wait espera o primeiro processo filho que chegar
O Waitpid recebe como parametro o pid do filho que espera, o endereco do exit status e 0 (confia)
Ele espera um processo especifico finalizar
**/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void novo_filho(int *filho_pid, int num) {
    fflush(stdout);
    *filho_pid = fork();
    if (*filho_pid == 0) {
        printf("[Filho] Vou esperar 5 segundos e morrer retornando %d como exit status\n", num);
        sleep(5);
        exit(num); ///Numero arbitrario
    }
}

void novo_filho_lento(int *filho_pid, int num) {
    fflush(stdout);
    *filho_pid = fork();
    if (*filho_pid == 0) {
        printf("[Filho] Vou esperar 7 segundos e morrer retornando %d como exit status\n", num);
        sleep(7);
        exit(num); ///Numero arbitrario
    }
}

int main() {
    int filho_pid_1, filho_pid_2, filho_pid_3, exit_status;
    novo_filho(&filho_pid_1, 1);
    novo_filho(&filho_pid_2, 2);
    novo_filho(&filho_pid_3, 3);
    printf("[Pai] Vou esperar um filho qualquer finalizar\n");
    wait(&exit_status);
    printf("[Pai] Finalizou! Recebi %d como exit status\n", exit_status/256); ///Tem que dividir por 256 por algum motivo

    int filho_pid_4, filho_pid_5;
    novo_filho(&filho_pid_4, 4);
    novo_filho_lento(&filho_pid_5, 5);
    sleep(1);
    printf("[Pai] Vou esperar especificamente o filho que retorna 5 finalizar\n");
    waitpid(filho_pid_5, &exit_status, 0);
     printf("[Pai] Finalizou! Recebi %d como exit status\n", exit_status/256); ///Tem que dividir por 256 por algum motivo
}
