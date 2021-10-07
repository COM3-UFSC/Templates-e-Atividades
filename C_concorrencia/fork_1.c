/**
Copyright [2021] Bernardo Borges Sandoval
Programa dedicado a mostrar o uso de Fork em C
**/

/**
Explicacao de Fork:
Fork cria um novo processo com o mesmo codigo base que o processo que o invocou
A partir daquele momento ambos processos executam concorrentemente
Para o processo pai/originial a funcao fork() retorna o id do processo criado
Para o processo filho/criado a funcao fork() retorna 0
Assim eh possivel permitir que so um deles execute certa parte do codigo, comparando a saida com 0
**/

/**
Explicacao de Getpid e Getppid:
Getpid (Get Process ID) retorna um inteiro com o ID do processo
Getppid (Get Parent Process ID) retorna um inteiro com o ID do processo pai
**/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    if (fork() == 0) /// Apenas o processo criado pelo fork entra aqui
        printf("Sou o processo filho, este eh meu Process ID: %d e esse eh o Process ID do meu pai: %d\n", getpid(), getppid());
    else ///Apenas o processo original enra aqui
        printf("Sou o processo pai, este eh meu Process ID: %d\n", getpid());
    ///Ambos executam essa linha
    printf("Processo finalizado, este eh meu Process ID: %d\n", getpid());
}
