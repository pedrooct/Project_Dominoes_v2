#include <stdio.h>
#include <stdlib.h>
#include "../func_h/menu.h"
#include "../func_h/data.h"

int main_menu(int n, char data, char option)
{
    printf("   Bem vindos ao dominoes \n");
    printf("    (a) Opcao para o numero de jogadores \n");
    printf("    (b) Opcao para o metodo de escolha de insercao de dados \n");
    printf("    (c) Jogar ! \n");
    scanf(" %c",&option);
    switch(option)
    {
    case 'a':
        printf("Insira o numero de jogadores\n");
        scanf("%d",&n);
        if(n <= 1|| n >= 2)
        {
            printf("O numero Maximo de jogadores e 2 , insira outro valor \n");
            main_menu(n,data,option);

        }
        main_menu(n,data,option);
        break;

    case 'b':

        printf("Insira o metodo para atribuir os dominos\n ");
        printf("(a)escolha a para ficheiro txt\n");
        printf("(b)escolha b para aleatorio\n ");
        scanf(" %c",&data);
        main_menu(n,data,option);
        break;

    case 'c':
        printf("Let the games begin ! \n");
        //main_menu(n,data,option);
        break;
    }
    return 1;
}
