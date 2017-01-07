
//projeto feito por : Pedro Costa N31179 Paulo Bento N33959
/**< Projeto feito por : Pedro Costa Nº31179, Paulo Bento Nº33959  */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "func_h/data.h"


/**< Macros definidas ser possivel melhor compreensão na função de gerar sequencia */
#define works 1
#define dworks 0



/** \brief A função menu server unica e exclusivamente para gerir o input do utilizador, Fazendo isso atraves de de switch case e de if's
 *
 * \return void
 *
 */
void main_menu()
{
    GAME start;
    HAND *paux = NULL;
    int i,n,n_player,j=1,k=0;
    char option='\0';
    int matrix_main[28][2]= {}; /**< Matrix principal , ou seja matrix usada para gerar e armazenar as peças que vao ser usadas */
    int matrix_player[28][2]= {}; /**< Matrix_player usada para o armazenar a mão do jogador 1 */
    int matrix_aux[255][2]= {};
    int matrix_tab[28][2]= {}; /**< Matrix_tab onde vai ser feita a sequencia de jogo */
    int matrix_vmax[28][2]= {}; /**< Matrix_vmax que vai ser armazenada a melhor hipotese possivel de sequencia */
    int pecas_disponivel=28; /**< int pecas_disponivel pecas que ainda podem ser retiradas da matrix baralho */
    int itera=0; /**< Peca de auxilio */
    int id=0;
    int aux_aux=0;/**< variavel usada para auxiliar no registo das possiveis sequencias extras */
    int id_player=0;/**< Numero de pecas de maos */
    int count=0;
    int vmax=0;
    int nfac=0;
    int number=0; /**< int number Numero de pecas que o utilizador pretenda jogar */
    int pecas=1; /**< int pecas Esta variavel determina o numero de peças que a mão ainda pode jogar */
    int pecas2=0;
    int vmax_checker=0;
    FILE *fp;
    FILE *fd;
    FILE *fa;


    while (option !='c')
    {

        /**< Inicio do menu */
        printf(" ______________________________________________\n");
        printf("|**Bem vindos ao dominoes**                    |\n");
        printf("|   **Vamos comecar !                          |\n");
        printf("|   **clique (a) para iniciar a parte 1 **     |\n");
        printf("|   **clique (b) para iniciar a parte 2 **     |\n");
        printf("|   **Clique (c) para sair do programa **      |\n");
        printf("|______________________________________________|\n");
        scanf(" %c",&option);
        option=tolower(option);
        switch(option)
        {
        case 'a':
        {

            matrix_aux[0][0]=-1;
            matrix_aux[255][0]=-1;
            srand((unsigned)time(NULL)); /**< O srand server para permitir gerar valores aleatórios para atribuir a mão do jogador */
            generate_deck(matrix_main,28,2);

            printf(" ________________________________________\n");
            printf("|Insira o numero de jogadores            |\n");
            printf("|1 a 4 jogadores                         |\n");
            printf("|________________________________________|\n");
            printf("|Procurar uma sequencia ou ordenado ?    |\n");
            printf("|Clique 0                                |\n");
            printf("|________________________________________|\n");

            scanf("%d",&n);
            n_player=n;


            if(n == 1)
            {
                printf(" __________________________________\n");
                printf("|Qual o metodo de insercao de dados|\n");
                printf("|1- Gerado automaticamente         |\n");
                printf("|2- Escolha as pecas               |\n");
                printf("|3- Escolha as peças em modo file  |\n");
                printf("|__________________________________|\n");
                scanf("%d",&n);
                if(n==1)
                {
                    printf(" _______________________________________________\n");
                    printf("|**Insira o numero de pecas que pretende jogar**|\n");
                    printf("|_______________________________________________|\n");
                    scanf("%d",&number);
                    if(number>1 && number<28)
                    {

                        pecas_disponivel=generate_hand(matrix_main,matrix_player,number,pecas_disponivel);

                        nfac=generate_fac(number,nfac);
                        system("cls");
                        printf("\t _____________________\t\n");
                        printf("\t|Mao de jogo gerada!  |\t\n");
                        printf("\t|_____________________|\t\n");
                        print_deck(matrix_player,number,2);

                        printf("\t _____________________________\t\n");
                        printf("\t|Prentende guardar a mao      |\t\n");
                        printf("\t|t->texto, i->binario, n->sair|\t\n");
                        printf("\t|_____________________________|\t\n");
                        scanf(" %c",&option);
                        option=tolower(option);
                        if(option=='t')
                        {
                            fp=fopen("dominoes.txt","w+");
                            if(fp!=NULL)
                            {
                                for(i=0; i<number; i++)
                                {
                                    fprintf(fp,"%d %d\n",matrix_player[i][0],matrix_player[i][1]);
                                }
                            }
                            else
                            {
                                printf(" __________________________________________\n");
                                printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                printf("|__________________________________________|\n");
                            }
                            fclose(fp);
                        }
                        if(option=='i')
                        {
                            fd=fopen("dominoesbin.bin","wb");
                            if(fd!=NULL)
                            {
                                for(i=0; i<number; i++)
                                {
                                    fwrite(&matrix_player[i][0],sizeof(int),1,fd);
                                    fwrite(&matrix_player[i][1],sizeof(int),1,fd);
                                }
                            }
                            else
                            {
                                printf(" __________________________________________\n");
                                printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                printf("|__________________________________________|\n");
                            }
                            fclose(fd);
                        }

                        printf("\t ________________________________\t\n");
                        printf("\t|Prentende ordenar a mao? (s/n)  |\t\n");
                        printf("\t|________________________________|\t\n");
                        scanf(" %c",&option);
                        option=tolower(option);
                        if(option=='s')
                        {
                            printf("\t ______________\t\n");
                            printf("\t|jogo ordenado!|\t\n");
                            printf("\t|______________|\t\n");
                            ordena_hand(matrix_player,number);
                            print_deck(matrix_player,number,2);
                        }
                        fa=fopen("regist.txt","w+");
                        fclose(fa);
                        count = play_recursive(matrix_tab,matrix_player,matrix_aux,matrix_vmax,number,count,vmax,nfac,pecas,itera,id,aux_aux);
                        vmax_checker=vmax_checker_func(matrix_tab,matrix_player,matrix_vmax,number);
                        if(vmax_checker != number)
                        {
                            printf("\t _____________________________\t\n");
                            printf("\t|Maior sequencia de %d pecas !|\t\n",vmax_checker);
                            printf("\t|_____________________________|\t\n");
                            print_deck(matrix_vmax,vmax_checker,2);
                        }

                        if(matrix_aux[0][0]!=-1)
                        {
                            printf(" ____________________________\n");
                            printf("|Deseja ver outras opcoes?s/n|\n");
                            printf("|____________________________|\n");
                            scanf(" %c",&option);
                            option=tolower(option);
                            if(option == 's')
                            {
                                print_deck(matrix_aux,number,2);
                            }
                        }
                    }
                    else
                    {
                        printf(" ___________________________________________________\n");
                        printf("|Ultrapassa o numero de pecas possivel para o jogo**|\n");
                        printf("|___________________________________________________|\n");

                    }
                }
                else if (n==2)
                {
                    printf(" _____________________________________________\n");
                    printf("|Insira o numero de pecas que pretende jogar  |\n");
                    printf("|_____________________________________________|\n");
                    scanf("%d",&number);
                    if(number>1 && number<28)
                    {

                        for(i=0; i<number; i++)
                        {
                            printf(" ________________\n");
                            printf("|Insira a %d peca |\n",i+1);
                            printf("|________________|\n");
                            scanf("%d %d",&matrix_player[i][0],&matrix_player[i][1]);
                        }
                        if(valid_hand(matrix_main,matrix_player,number)==works)
                        {
                            nfac=generate_fac(number,nfac);
                            system("cls");
                            printf("\t ___________________\t\n");
                            printf("\t|Mao de jogo gerada!|\t\n");
                            printf("\t|___________________|\t\n");
                            print_deck(matrix_player,number,2);

                            printf("\t _____________________________\t\n");
                            printf("\t|Prentende guardar a mao      |\t\n");
                            printf("\t|t->texto, i->binario, n->sair|\t\n");
                            printf("\t|_____________________________|\t\n");
                            scanf(" %c",&option);
                            option=tolower(option);
                            if(option=='t')
                            {
                                fp=fopen("dominoes.txt","w+");
                                if(fp!=NULL)
                                {
                                    for(i=0; i<number; i++)
                                    {
                                        fprintf(fp,"%d %d\n",matrix_player[i][0],matrix_player[i][1]);
                                    }
                                }
                                else
                                {
                                    printf(" __________________________________________\n");
                                    printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                    printf("|__________________________________________|\n");
                                }
                                fclose(fp);
                            }
                            if(option=='i')
                            {
                                fd=fopen("dominoesbin.bin","wb");
                                if(fd!=NULL)
                                {
                                    for(i=0; i<number; i++)
                                    {
                                        fwrite(&matrix_player[i][0],sizeof(int),1,fd);
                                        fwrite(&matrix_player[i][1],sizeof(int),1,fd);
                                    }
                                }
                                else
                                {
                                    printf(" __________________________________________\n");
                                    printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                    printf("|__________________________________________|\n");
                                }
                                fclose(fd);
                            }
                            printf("\t ________________________________\t\n");
                            printf("\t|Prentende ordenar a mao? (s/n)  |\t\n");
                            printf("\t|________________________________|\t\n");
                            scanf(" %c",&option);
                            option=tolower(option);
                            if(option=='s')
                            {
                                printf("\t ______________\t\n");
                                printf("\t|jogo ordenado!|\t\n");
                                printf("\t|______________|\t\n");
                                ordena_hand(matrix_player,number);
                                print_deck(matrix_player,number,2);
                            }
                            fa=fopen("regist.txt","w+");
                            fclose(fa);
                            count = play_recursive(matrix_tab,matrix_player,matrix_aux,matrix_vmax,number,count,vmax,nfac,pecas,itera,id,aux_aux);
                            vmax_checker=vmax_checker_func(matrix_tab,matrix_player,matrix_vmax,number);
                            if(vmax_checker != number)
                            {
                                printf("\t _____________________________\t\n");
                                printf("\t|Maior sequencia de %d pecas !|\t\n",vmax_checker);
                                printf("\t|_____________________________|\t\n");
                                print_deck(matrix_vmax,vmax_checker,2);
                            }
                            if(matrix_aux[0][0]!=-1)
                            {
                                printf(" ____________________________\n");
                                printf("|Deseja ver outras opcoes?s/n|\n");
                                printf("|____________________________|\n");
                                scanf(" %c",&option);
                                option=tolower(option);
                                if(option == 's')
                                {
                                    print_deck(matrix_aux,number,2);
                                }
                            }
                        }
                    }
                    else
                    {
                        printf(" __________________________________________________\n");
                        printf("|Ultrapassa o numero de pecas possivel para o jogo |\n");
                        printf("|__________________________________________________|\n");

                    }
                }
                if(n==3)
                {
                    fp= fopen("dominoes.txt","r");
                    if(fp!=NULL)
                    {
                        printf(" _____________________________\n");
                        printf("|Introduza o numero de pecas: |\n");
                        printf("|_____________________________|\n");
                        scanf("%d",&number);
                        system("cls");
                        nfac=generate_fac(number,nfac);
                        for(i=0; i<number; i++)
                        {
                            fscanf(fp, "%d %d", &matrix_player[i][0],&matrix_player[i][1]);

                        }
                        if(valid_hand(matrix_main,matrix_player,number)==works)
                        {
                            printf(" _____________________\n");
                            printf("|Jogo lido com sucesso!|\n");
                            printf("|______________________|\n");
                            print_deck(matrix_player,number,2);

                            printf("\t _____________________________\t\n");
                            printf("\t|Prentende guardar a mao      |\t\n");
                            printf("\t|t->texto, i->binario, n->sair|\t\n");
                            printf("\t|_____________________________|\t\n");
                            scanf(" %c",&option);
                            option=tolower(option);
                            if(option=='t')
                            {
                                fp=fopen("dominoes.txt","w+");
                                if(fp!=NULL)
                                {
                                    for(i=0; i<number; i++)
                                    {
                                        fprintf(fp,"%d %d\n",matrix_player[i][0],matrix_player[i][1]);
                                    }
                                }
                                else
                                {
                                    printf(" __________________________________________\n");
                                    printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                    printf("|__________________________________________|\n");
                                }
                                fclose(fp);
                            }
                            if(option=='i')
                            {
                                fd=fopen("dominoesbin.bin","wb");
                                if(fd!=NULL)
                                {
                                    for(i=0; i<number; i++)
                                    {
                                        fwrite(&matrix_player[i][0],sizeof(int),1,fd);
                                        fwrite(&matrix_player[i][1],sizeof(int),1,fd);
                                    }
                                }
                                else
                                {
                                    printf(" __________________________________________\n");
                                    printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                    printf("|__________________________________________|\n");
                                }
                                fclose(fd);
                            }

                            printf("\t ________________________________\t\n");
                            printf("\t|Prentende ordenar a mao? (s/n)  |\t\n");
                            printf("\t|________________________________|\t\n");
                            scanf(" %c",&option);
                            option=tolower(option);
                            if(option=='s')
                            {
                                printf("\t ______________\t\n");
                                printf("\t|jogo ordenado!|\t\n");
                                printf("\t|______________|\t\n");
                                ordena_hand(matrix_player,number);
                                print_deck(matrix_player,number,2);
                            }
                            fa=fopen("regist.txt","w+");
                            fclose(fa);
                            count = play_recursive(matrix_tab,matrix_player,matrix_aux,matrix_vmax,number,count,vmax,nfac,pecas,itera,id,aux_aux);
                            vmax_checker=vmax_checker_func(matrix_tab,matrix_player,matrix_vmax,number);
                            if(vmax_checker != number)
                            {
                                printf("\t _____________________________\t\n");
                                printf("\t|Maior sequencia de %d pecas !|\t\n",vmax_checker);
                                printf("\t|_____________________________|\t\n");
                                print_deck(matrix_vmax,vmax_checker,2);
                            }
                            if(matrix_aux[0][0]!=-1)
                            {
                                printf(" ____________________________\n");
                                printf("|Deseja ver outras opcoes?s/n|\n");
                                printf("|____________________________|\n");
                                scanf(" %c",&option);
                                option=tolower(option);
                                if(option == 's')
                                {
                                    print_deck(matrix_aux,number,2);
                                }
                            }
                            fclose(fp);

                        }
                    }
                    else
                    {
                        printf(" __________________________________________\n");
                        printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                        printf("|__________________________________________|\n");

                    }
                }
            }
            else if(n==2 || n==3 || n==4)
            {
                printf(" __________________________________\n");
                printf("|Qual o metodo de insercao de dados|\n");
                printf("|1- Gerado automaticamente         |\n");
                printf("|2- Escolha as pecas               |\n");
                printf("|3- Escolha as peças em modo file  |\n");
                printf("|__________________________________|\n");
                scanf("%d",&n);
                if(n==1)
                {
                    printf(" ____________________________________________________\n");
                    printf("|Insira o numero de pecas que pretende jogar         |\n");
                    printf("|*O numeros de peças vai se aplicar aos dois baralhos|\n");
                    printf("|____________________________________________________|\n");
                    scanf("%d",&number);
                    id_player=number;
                    number=number*n_player;
                    if(number>1 && number<28)
                    {
                        generate_hand(matrix_main,matrix_player,number,pecas_disponivel);
                        printf("\t ______________\t\n");
                        printf("\t|jogo gerado!  |\t\n");
                        printf("\t|______________|\t\n");
                        print_deck(matrix_player,number,2);
                        nfac=generate_fac(number,nfac);
                        printf("\t _____________________________\t\n");
                        printf("\t|Prentende guardar a mao      |\t\n");
                        printf("\t|t->texto, i->binario, n->sair|\t\n");
                        printf("\t|_____________________________|\t\n");
                        scanf(" %c",&option);
                        option=tolower(option);
                        if(option=='t')
                        {
                            fp=fopen("dominoes.txt","w+");
                            if(fp!=NULL)
                            {
                                for(i=0; i<number; i++)
                                {
                                    fprintf(fp,"%d %d\n",matrix_player[i][0],matrix_player[i][1]);
                                }
                            }
                            else
                            {
                                printf(" __________________________________________\n");
                                printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                printf("|__________________________________________|\n");
                            }
                            fclose(fp);
                        }
                        if(option=='i')
                        {
                            fd=fopen("dominoesbin.bin","wb");
                            if(fd!=NULL)
                            {
                                for(i=0; i<number; i++)
                                {
                                    fwrite(&matrix_player[i][0],sizeof(int),1,fd);
                                    fwrite(&matrix_player[i][1],sizeof(int),1,fd);
                                }
                            }
                            else
                            {
                                printf(" __________________________________________\n");
                                printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                printf("|__________________________________________|\n");
                            }
                            fclose(fd);
                        }
                        fa=fopen("regist.txt","w+");
                        fclose(fa);
                        count = play_recursive_more(matrix_tab,matrix_player,matrix_aux,matrix_vmax,number,count,vmax,nfac,pecas,pecas2,itera,id,id_player,n_player);
                        vmax_checker=vmax_checker_func(matrix_tab,matrix_player,matrix_vmax,number);
                        if(vmax_checker != number)
                        {
                            printf("\t _____________________________\t\n");
                            printf("\t|Maior sequencia de %d pecas !|\t\n",vmax_checker);
                            printf("\t|_____________________________|\t\n");
                            print_deck(matrix_vmax,vmax_checker,2);
                        }

                    }
                    else
                    {
                        printf(" __________________________________________________\n");
                        printf("|Ultrapassa o numero de pecas possivel para o jogo!|\n");
                        printf("|__________________________________________________|\n");

                    }

                }
                if(n==2)
                {
                    printf(" ____________________________________________________\n");
                    printf("|Insira o numero de pecas que pretende jogar         |\n");
                    printf("|*O numeros de peças vai se aplicar aos dois baralhos|\n");
                    printf("|____________________________________________________|\n");
                    scanf("%d",&number);
                    id_player=number;
                    if(number>=1 && number*n_player<28)
                    {
                        for(i=0; i<number*n_player; i++)
                        {
                            printf(" _______________________________\n");
                            printf("|Insira o %d valor para a mao %d|\n",i+1,j);
                            printf("|_______________________________|\n");
                            scanf("%d %d",&matrix_player[i][0],&matrix_player[i][1]);
                            k++;
                            if(k==number)
                            {
                                j++;
                                k=0;
                            }
                        }
                        if(valid_hand(matrix_main,matrix_player,number)==works)
                        {
                            number=number*n_player;
                            print_deck(matrix_player,number,2);
                            nfac=generate_fac(number,nfac);
                            printf("\t _____________________________\t\n");
                            printf("\t|Prentende guardar a mao      |\t\n");
                            printf("\t|t->texto, i->binario, n->sair|\t\n");
                            printf("\t|_____________________________|\t\n");
                            scanf(" %c",&option);
                            option=tolower(option);
                            if(option=='t')
                            {
                                fp=fopen("dominoes.txt","w+");
                                if(fp!=NULL)
                                {
                                    for(i=0; i<number; i++)
                                    {
                                        fprintf(fp,"%d %d\n",matrix_player[i][0],matrix_player[i][1]);
                                    }
                                }
                                else
                                {
                                    printf(" __________________________________________\n");
                                    printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                    printf("|__________________________________________|\n");
                                }
                                fclose(fp);
                            }
                            if(option=='i')
                            {
                                fd=fopen("dominoesbin.bin","wb");
                                if(fd!=NULL)
                                {
                                    for(i=0; i<number; i++)
                                    {
                                        fwrite(&matrix_player[i][0],sizeof(int),1,fd);
                                        fwrite(&matrix_player[i][1],sizeof(int),1,fd);
                                    }
                                }
                                else
                                {
                                    printf(" __________________________________________\n");
                                    printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                    printf("|__________________________________________|\n");
                                }
                                fclose(fd);
                            }
                            fa=fopen("regist.txt","w+");
                            fclose(fa);
                            count=play_recursive_more(matrix_tab,matrix_player,matrix_aux,matrix_vmax,number,count,vmax,nfac,pecas,pecas2,itera,id,id_player,n_player);
                            vmax_checker=vmax_checker_func(matrix_tab,matrix_player,matrix_vmax,number);
                            if(vmax_checker != number)
                            {
                                printf("\t _____________________________\t\n");
                                printf("\t|Maior sequencia de %d pecas !|\t\n",vmax_checker);
                                printf("\t|_____________________________|\t\n");
                                print_deck(matrix_vmax,vmax_checker,2);
                            }
                        }
                    }
                    else
                    {
                        printf(" __________________________________________________\n");
                        printf("|Ultrapassa o numero de pecas possivel para o jogo!|\n");
                        printf("|__________________________________________________|\n");
                    }
                }
                if(n==3)
                {
                    fp = fopen("dominoes.txt","r");
                    if(fp!=NULL)
                    {
                        printf(" _____________________________\n");
                        printf("|Introduza o numero de pecas: |\n");
                        printf("|_____________________________|\n");
                        scanf("%d",&number);
                        id_player=number;
                        if(number>=1 && number*n_player<28)
                        {
                            number=number*n_player;
                            nfac=generate_fac(number,nfac);
                            for(i=0; i<number; i++) // le todas as peças
                            {
                                fscanf(fp, "%d %d", &matrix_player[i][0],&matrix_player[i][1]);

                            }
                            if(valid_hand(matrix_main,matrix_player,number)==works)
                            {
                                printf(" _____________________\n");
                                printf("|Jogo lido com sucesso|\n");
                                printf("|_____________________|\n");
                                print_deck(matrix_player,number,2);
                                fa=fopen("regist.txt","w+");
                                fclose(fa);
                                count=play_recursive_more(matrix_tab,matrix_player,matrix_aux,matrix_vmax,number,count,vmax,nfac,pecas,pecas2,itera,id,id_player,n_player);
                                vmax_checker=vmax_checker_func(matrix_tab,matrix_player,matrix_vmax,number);
                                if(vmax_checker != number)
                                {
                                    printf("\t _____________________________\t\n");
                                    printf("\t|Maior sequencia de %d pecas !|\t\n",vmax_checker);
                                    printf("\t|_____________________________|\t\n");
                                    print_deck(matrix_vmax,vmax_checker,2);
                                }
                                fclose(fp);
                            }
                        }
                        else
                        {
                            printf(" __________________________________________________\n");
                            printf("|Ultrapassa o numero de pecas possivel para o jogo!|\n");
                            printf("|__________________________________________________|\n");
                        }
                    }
                    else
                    {
                        printf(" ______________________________\n");
                        printf("|Não conseguiu abriu o ficheiro|\n");
                        printf("|______________________________|\n");
                    }
                }
            }
            if(n==0)
            {
                printf(" __________________________________________\n");
                printf("|Ordenar as subsequencias  ? s/n           |\n");
                printf("|__________________________________________|\n");
                scanf(" %c",&option);
                option=tolower(option);
                if(option=='s')
                {
                    ordena_file();
                }
                printf(" ______________________________\n");
                printf("|Procurar sequencia a mao ?s/n |\n");
                printf("|______________________________|\n");
                scanf(" %c",&option);
                option=tolower(option);
                if(option=='s')
                {
                    find_sequence();
                }
            }
            break;
        }
        case 'b':
        {
            srand((unsigned)time(NULL)); /**< O srand server para permitir gerar valores aleatórios para atribuir a mão do jogador */
            inicializer(&start);
            generate_deck_sturct(&start);
            printf(" ____________________________\n");
            printf("|Insira o numero de jogadores|\n");
            printf("|1 a 4 jogadores             |\n");
            printf("|____________________________|\n");
            printf("|Procurar uma sequencia ?    |\n");
            printf("|Clique 0                    |\n");
            printf("|____________________________|\n");
            scanf("%d",&n);
            start.n_player=n;
            if(n == 1)
            {
                printf(" __________________________________\n");
                printf("|Qual o metodo de insercao de dados|\n");
                printf("|1- Gerado automaticamente         |\n");
                printf("|2- Escolha as pecas               |\n");
                printf("|3- Escolha as peças em modo file  |\n");
                printf("|__________________________________|\n");
                scanf("%d",&n);
                if(n==1)
                {
                    printf(" _______________________________________________\n");
                    printf("|**Insira o numero de pecas que pretende jogar**|\n");
                    printf("|_______________________________________________|\n");
                    scanf("%d",&start.number);
                    if(start.number>1 && start.number<28)
                    {
                        generate_fac_struct(&start);
                        generate_hand_struct(&start);
                        printf("\t ______________\t\n");
                        printf("\t|jogo gerado!  |\t\n");
                        printf("\t|______________|\t\n");
                        print_deck_hand(start);
                        printf("\t _____________________________\t\n");
                        printf("\t|Prentende guardar a mao      |\t\n");
                        printf("\t|t->texto, i->binario, n->sair|\t\n");
                        printf("\t|_____________________________|\t\n");
                        scanf(" %c",&option);
                        option=tolower(option);
                        paux=start.hand_game;
                        if(option=='t')
                        {
                            fp=fopen("dominoes.txt","w+");
                            if(fp!=NULL)
                            {
                                for(i=0; i<start.number; i++)
                                {
                                    fprintf(fp,"%d %d\n",((paux+i)->hand_esquerda),((paux+i)->hand_direita));
                                }
                            }
                            else
                            {
                                printf(" __________________________________________\n");
                                printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                printf("|__________________________________________|\n");
                            }
                            fclose(fp);
                        }
                        if(option=='i')
                        {
                            fd=fopen("dominoesbin.bin","wb");
                            if(fd!=NULL)
                            {
                                for(i=0; i<start.number; i++)
                                {
                                    fwrite(&(paux+i)->hand_esquerda,sizeof(int),1,fd);
                                    fwrite(&(paux+i)->hand_direita,sizeof(int),1,fd);
                                }
                            }
                            else
                            {
                                printf(" __________________________________________\n");
                                printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                printf("|__________________________________________|\n");
                            }
                            fclose(fd);
                        }
                        fa=fopen("registpar2.txt","w+");
                        fclose(fa);
                        start.count=play_recursive_struct(&start);
                        start.vmax_checker=vmax_checker_func_struct(&start);
                        if(start.vmax_checker != start.number || start.vmax_checker== start.vmax|| start.id==0)
                        {
                            printf("\t _____________________________\t\n");
                            printf("\t|Maior sequencia de %d pecas !|\t\n",start.vmax_checker);
                            printf("\t|_____________________________|\t\n");
                            print_deck_vmax(start);
                        }
                        else
                        {
                            printf("\t ______________\t\n");
                            printf("\t|jogo gerado!  |\t\n");
                            printf("\t|______________|\t\n");
                            print_deck_tab(start);
                        }
                    }
                    break;
                }
                if(n==2)
                {

                    printf(" ____________________________________________________\n");
                    printf("|Insira o numero de pecas que pretende jogar         |\n");
                    printf("|____________________________________________________|\n");
                    scanf("%d",&start.number);

                    if(start.number>1 && start.number<28)
                    {
                        generate_fac_struct(&start);
                        for(i=0; i<start.number; i++)
                        {
                            printf(" _______________________________\n");
                            printf("|Insira a %d peca!              |\n",i+1);
                            printf("|_______________________________|\n");
                            scanf("%d %d",&(paux->hand_esquerda),&(paux->hand_direita));
                            paux++;
                        }
                        printf(" _____________________\n");
                        printf("|Jogo lido com sucesso|\n");
                        printf("|_____________________|\n");
                        print_deck_hand(start);
                        printf("\t _____________________________\t\n");
                        printf("\t|Prentende guardar a mao      |\t\n");
                        printf("\t|t->texto, i->binario, n->sair|\t\n");
                        printf("\t|_____________________________|\t\n");
                        scanf(" %c",&option);
                        option=tolower(option);
                        paux=start.hand_game;
                        if(option=='t')
                        {
                            fp=fopen("dominoes.txt","w+");
                            if(fp!=NULL)
                            {
                                for(i=0; i<start.number; i++)
                                {
                                    fprintf(fp,"%d %d\n",((paux+i)->hand_esquerda),((paux+i)->hand_direita));
                                }
                            }
                            else
                            {
                                printf(" __________________________________________\n");
                                printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                printf("|__________________________________________|\n");
                            }
                            fclose(fp);
                        }
                        if(option=='i')
                        {
                            fd=fopen("dominoesbin.bin","wb");
                            if(fd!=NULL)
                            {
                                for(i=0; i<start.number; i++)
                                {
                                    fwrite(&(paux+i)->hand_esquerda,sizeof(int),1,fd);
                                    fwrite(&(paux+i)->hand_direita,sizeof(int),1,fd);
                                }
                            }
                            else
                            {
                                printf(" __________________________________________\n");
                                printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                printf("|__________________________________________|\n");
                            }
                            fclose(fd);
                        }
                        fa=fopen("registpar2.txt","w+");
                        fclose(fa);
                        start.count=play_recursive_struct(&start);
                        start.vmax_checker=vmax_checker_func_struct(&start);
                        if(start.vmax_checker != start.number || start.vmax_checker== start.vmax|| start.id==0)
                        {
                            printf("\t _____________________________\t\n");
                            printf("\t|Maior sequencia de %d pecas !|\t\n",start.vmax_checker);
                            printf("\t|_____________________________|\t\n");
                            print_deck_vmax(start);
                        }
                        else
                        {
                            printf("\t ______________\t\n");
                            printf("\t|jogo gerado!  |\t\n");
                            printf("\t|______________|\t\n");
                            print_deck_tab(start);
                        }

                    }
                    break;
                }
                if(n==3)
                {
                    paux=start.hand_game;
                    fp = fopen("dominoes.txt","r");
                    if(fp!=NULL)
                    {
                        printf(" _____________________________\n");
                        printf("|Introduza o numero de pecas: |\n");
                        printf("|_____________________________|\n");
                        scanf("%d",&start.number);
                        start.id_player=start.number;
                        if(start.number>1 && start.number<28)
                        {
                            start.nfac=generate_fac_struct(&start);
                            for(i=0; i<start.number; i++) // le todas as peças
                            {
                                fscanf(fp,"%d %d",&(paux->hand_esquerda),&(paux->hand_direita));
                                paux++;

                            }
                            if(valid_hand_struct(&start)==works)
                            {
                                printf(" _____________________\n");
                                printf("|Jogo lido com sucesso|\n");
                                printf("|_____________________|\n");
                                print_deck_hand(start);
                                fa=fopen("registpar2.txt","w+");
                                fclose(fa);
                                start.count=play_recursive_struct(&start);
                                start.vmax_checker=vmax_checker_func_struct(&start);
                                if(start.vmax_checker != start.number || start.vmax_checker== start.vmax||start.id==0)
                                {
                                    printf("\t _____________________________\t\n");
                                    printf("\t|Maior sequencia de %d pecas !|\t\n",start.vmax_checker);
                                    printf("\t|_____________________________|\t\n");
                                    print_deck_vmax(start);
                                }
                                else
                                {
                                    printf("\t ______________\t\n");
                                    printf("\t|jogo gerado!  |\t\n");
                                    printf("\t|______________|\t\n");
                                    print_deck_tab(start);
                                }
                                fclose(fp);
                            }
                        }
                        else
                        {
                            printf(" __________________________________________________\n");
                            printf("|Ultrapassa o numero de pecas possivel para o jogo!|\n");
                            printf("|__________________________________________________|\n");
                        }
                    }
                    else
                    {
                        printf(" ______________________________\n");
                        printf("|Não conseguiu abriu o ficheiro|\n");
                        printf("|______________________________|\n");
                    }
                    break;
                }
            }
            else if(n==2 || n==3 || n==4)
            {
                printf(" __________________________________\n");
                printf("|Qual o metodo de insercao de dados|\n");
                printf("|1- Gerado automaticamente         |\n");
                printf("|2- Escolha as pecas               |\n");
                printf("|3- Escolha as peças em modo file  |\n");
                printf("|__________________________________|\n");
                scanf("%d",&n);
                if(n==1)
                {
                    printf(" ____________________________________________________\n");
                    printf("|Insira o numero de pecas que pretende jogar         |\n");
                    printf("|*O numeros de peças vai se aplicar aos dois baralhos|\n");
                    printf("|____________________________________________________|\n");
                    scanf("%d",&start.number);
                    start.id_player=start.number;
                    start.number=start.number*start.n_player;
                    if(start.number>1 && start.number<28)
                    {
                        generate_hand_struct(&start);/**< \bug {Por vezes gera a peça -1 -1 sendo essa peca inexistente no jogo, essa peça provem de quando geramos a primeira mao } */
                        printf("\t ______________\t\n");
                        printf("\t|jogo gerado!  |\t\n");
                        printf("\t|______________|\t\n");
                        print_deck_hand(start);
                        start.nfac=generate_fac_struct(&start);
                        printf("\t _____________________________\t\n");
                        printf("\t|Prentende guardar a mao      |\t\n");
                        printf("\t|t->texto, i->binario, n->sair|\t\n");
                        printf("\t|_____________________________|\t\n");
                        scanf(" %c",&option);
                        option=tolower(option);
                        paux=start.hand_game;
                        if(option=='t')
                        {
                            fp=fopen("dominoes.txt","w+");
                            if(fp!=NULL)
                            {
                                for(i=0; i<start.number; i++)
                                {
                                    fprintf(fp,"%d %d\n",((paux+i)->hand_esquerda),((paux+i)->hand_direita));
                                }
                            }
                            else
                            {
                                printf(" __________________________________________\n");
                                printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                printf("|__________________________________________|\n");
                            }
                            fclose(fp);
                        }
                        if(option=='i')
                        {
                            fd=fopen("dominoesbin.bin","wb");
                            if(fd!=NULL)
                            {
                                for(i=0; i<start.number; i++)
                                {
                                    fwrite(&(paux+i)->hand_esquerda,sizeof(int),1,fd);
                                    fwrite(&(paux+i)->hand_direita,sizeof(int),1,fd);
                                }
                            }
                            else
                            {
                                printf(" __________________________________________\n");
                                printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                printf("|__________________________________________|\n");
                            }
                            fclose(fd);
                        }
                        fa=fopen("registpar2.txt","w+");
                        fclose(fa);
                        start.count = play_recursive_more_struct(&start);
                        start.vmax_checker=vmax_checker_func_struct(&start);
                        if(start.vmax_checker != start.number || start.vmax_checker== start.vmax || start.id==0)
                        {
                            printf("\t _____________________________\t\n");
                            printf("\t|Maior sequencia de %d pecas !|\t\n",start.vmax_checker);
                            printf("\t|_____________________________|\t\n");
                            print_deck_vmax(start);
                        }
                        else
                        {
                            printf("\t ______________\t\n");
                            printf("\t|jogo gerado!  |\t\n");
                            printf("\t|______________|\t\n");
                            print_deck_tab(start);
                        }

                    }
                    else
                    {
                        printf(" __________________________________________________\n");
                        printf("|Ultrapassa o numero de pecas possivel para o jogo!|\n");
                        printf("|__________________________________________________|\n");
                    }
                    break;
                }
                if(n==2)
                {
                    paux=start.hand_game;
                    printf(" ____________________________________________________\n");
                    printf("|Insira o numero de pecas que pretende jogar         |\n");
                    printf("|*O numeros de peças vai se aplicar aos dois baralhos|\n");
                    printf("|____________________________________________________|\n");
                    scanf("%d",&start.number);
                    start.id_player=start.number;
                    if(start.number>1 && start.number*start.n_player<28)
                    {
                        for(i=0; i<start.number*start.n_player; i++)
                        {
                            printf(" _______________________________\n");
                            printf("|Insira o %d peca para a mao %d |\n",i+1,j);
                            printf("|_______________________________|\n");
                            scanf("%d %d",&(paux+i)->hand_esquerda,&(paux+i)->hand_direita);
                            k++;
                            if(k==start.number)
                            {
                                j++;
                                k=0;
                            }
                        }
                        if(valid_hand_struct(&start)==works)
                        {
                            start.number=start.number*start.n_player;
                            printf(" _____________________\n");
                            printf("|Jogo lido com sucesso|\n");
                            printf("|_____________________|\n");
                            print_deck_hand(start);
                            start.nfac=generate_fac_struct(&start);
                            printf("\t _____________________________\t\n");
                            printf("\t|Prentende guardar a mao      |\t\n");
                            printf("\t|t->texto, i->binario, n->sair|\t\n");
                            printf("\t|_____________________________|\t\n");
                            scanf(" %c",&option);
                            option=tolower(option);
                            paux=start.hand_game;
                            if(option=='t')
                            {
                                fp=fopen("dominoes.txt","w+");
                                if(fp!=NULL)
                                {
                                    for(i=0; i<start.number; i++)
                                    {
                                        fprintf(fp,"%d %d\n",(paux+i)->hand_esquerda,(paux+i)->hand_direita);
                                    }
                                }
                                else
                                {
                                    printf(" __________________________________________\n");
                                    printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                    printf("|__________________________________________|\n");
                                }
                                fclose(fp);
                            }
                            if(option=='i')
                            {
                                fd=fopen("dominoesbin.bin","wb");
                                if(fd!=NULL)
                                {
                                    for(i=0; i<start.number; i++)
                                    {
                                        fwrite(&(paux+i)->hand_esquerda,sizeof(int),1,fd);
                                        fwrite(&(paux+i)->hand_direita,sizeof(int),1,fd);
                                    }
                                }
                                else
                                {
                                    printf(" __________________________________________\n");
                                    printf("|Nao foi possivel ler o conteudo o ficheiro|\n");
                                    printf("|__________________________________________|\n");
                                }
                                fclose(fd);
                            }
                            fa=fopen("registpar2.txt","w+");
                            fclose(fa);
                            start.count=play_recursive_more_struct(&start);
                            start.vmax_checker=vmax_checker_func_struct(&start);
                            if((start.vmax_checker != start.number || start.vmax_checker== start.vmax) && start.id==0)
                            {
                                printf("\t _____________________________\t\n");
                                printf("\t|Maior sequencia de %d pecas !|\t\n",start.vmax_checker);
                                printf("\t|_____________________________|\t\n");
                                print_deck_vmax(start);
                            }
                            else
                            {
                                printf("\t ______________\t\n");
                                printf("\t|jogo gerado!  |\t\n");
                                printf("\t|______________|\t\n");
                                print_deck_tab(start);
                            }
                        }
                    }
                    else
                    {
                        printf(" __________________________________________________\n");
                        printf("|Ultrapassa o numero de pecas possivel para o jogo!|\n");
                        printf("|__________________________________________________|\n");
                    }
                    break;
                }
                if(n==3)
                {
                    paux=start.hand_game;
                    fp = fopen("dominoes.txt","r");
                    if(fp!=NULL)
                    {
                        printf(" _____________________________\n");
                        printf("|Introduza o numero de pecas: |\n");
                        printf("|_____________________________|\n");
                        scanf("%d",&start.number);
                        start.id_player=start.number;
                        if(start.number>1 && start.number*start.n_player<28)
                        {
                            start.number=start.number*start.n_player;
                            start.nfac=generate_fac_struct(&start);
                            for(i=0; i<start.number; i++) // le todas as peças
                            {
                                fscanf(fp, "%d %d", &(paux->hand_esquerda),&(paux->hand_direita));
                                paux++;

                            }
                            if(valid_hand_struct(&start)==works)
                            {
                                printf(" _____________________\n");
                                printf("|Jogo lido com sucesso|\n");
                                printf("|_____________________|\n");
                                print_deck_hand(start);
                                fa=fopen("registpar2.txt","w+");
                                fclose(fa);
                                start.count=play_recursive_more_struct(&start);
                                start.vmax_checker=vmax_checker_func_struct(&start);
                                if(start.vmax_checker != start.number || start.vmax_checker== start.vmax ||start.id==0 )
                                {
                                    printf("\t _____________________________\t\n");
                                    printf("\t|Maior sequencia de %d pecas !|\t\n",start.vmax_checker);
                                    printf("\t|_____________________________|\t\n");
                                    print_deck_vmax(start);
                                }
                                else
                                {
                                    printf("\t ______________\t\n");
                                    printf("\t|jogo gerado!  |\t\n");
                                    printf("\t|______________|\t\n");
                                    print_deck_tab(start);
                                }
                                fclose(fp);
                            }
                        }
                        else
                        {
                            printf(" __________________________________________________\n");
                            printf("|Ultrapassa o numero de pecas possivel para o jogo!|\n");
                            printf("|__________________________________________________|\n");
                        }
                    }
                    else
                    {
                        printf(" ______________________________\n");
                        printf("|Não conseguiu abriu o ficheiro|\n");
                        printf("|______________________________|\n");
                    }
                }
                break;
            }
            if(n==0)
            {
                find_sequence(&start);
            }
            break;
        }
        case 'c':
        {
            break;
        }
        default:
        {
            printf(" __________________________\n");
            printf("|Letra ou caracter invalido|\n");
            printf("|__________________________|\n");
            system("pause");
            system("cls");
            break;
        }
        }
    }
}
int main() /**< Só chama a função main_menu */
{
    main_menu();
    system("cls");
    printf(" __________________________________\n");
    printf("|ERROR 404: USER DISCONNECTED      |\n");
    printf("|__________________________________|\n");
    system("ping www.google.pt");
    return 0;
}
