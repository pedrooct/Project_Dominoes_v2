#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../func_h/data.h"
#include "../func_h/lib_util.h"


#define works 1
#define dworks 0



/** \brief  Função generate_fac server para gerar o factorial do numero de peças
 *
 * \param number int
 * \param nfac int
 * \return int nfac
 *
 */
int generate_fac(int number,int nfac)
{
    nfac=number;
    int i=0;
    /** \brief i=number-1, para evitar a multiplicação de do fatorial duas vezes (evitar: 5*5*4*3*2)
     *
     * \param i-- i=number-1; i>1;
     *
     */
    for(i=number-1; i>1; i--)
    {
        nfac=nfac*i;
    }
    return nfac;
}
/** \brief Funcao tem como principal funcao guardar todas a jogadas válidas de jogo.
 *
 * \param matrix_tab[][2] int
 * \param count int
 * \return void
 *
 */
void save_file_part1(int matrix_tab[][2],int count)
{
    int k;
    FILE * fe;
    FILE * fr;
    fe=fopen("regist.txt","a+");
    fr=fopen("registbn.bin","ab+");
    if(fe!=NULL && fr!=NULL)
    {
        /** \brief Permite guardar sequencias num ficheiro binario
         *
         * \param k++ k=0; k<=count;
         *
         */
        for(k=0; k<count; k++)
        {
            fprintf(fe,"|%d|%d| ",matrix_tab[k][0],matrix_tab[k][1]);
            fwrite(&matrix_tab[k][0],sizeof(int),1,fr);
            fwrite(&matrix_tab[k][1],sizeof(int),1,fr);
        }
        fprintf(fe,"|f|f|\n");
        fwrite("\n",sizeof(char),1,fr);
    }
    fclose(fe);
    fclose(fr);
}
/** \brief Esta função vai a um ficheiro do tipo texto e procura uma sequência introduzida pelo utilizador, se nao encontrar retorna o valor dworks (0), se encontar retorna o valor de v, que corresponde à linha onde a sequência foi encontrada. Baseado KMP
 *
 * \param matrix_main[][2] int
 * \param n int
 * \return int
 *
 */
int find_sequence()
{
    int i=-1,j=0,k,v=0,n;
    int ite=0;
    int count=0,count2=0;
    char matrix_aux[28][2]= {};
    int  matrix_int[28][2]= {};
    int matrix_main[28][2]= {};
    FILE *fe;
    fe=fopen("regist.txt","r");
    if(fe!=NULL)
    {
        printf(" ____________________________________________________\n");
        printf("|insira 1 para procurar peca ou sequencia.           |\n");
        printf("|insira 2 para procurar todas as pecas ou sequencias.|\n");
        printf("|insira 3 para procurar por valor.                   |\n");
        printf("|____________________________________________________|\n");
        scanf("%d",&ite);
        if(ite==1)
        {
            printf(" ____________________________________________________\n");
            printf("|Quantas pecas deseja procurar.                      |\n");
            printf("|____________________________________________________|\n");
            scanf("%d",&n);
            for(j=0; j<n; j++)
            {
                printf(" ____________________________________________________\n");
                printf("|Insira a peca %d                                    |\n",j+1);
                printf("|____________________________________________________|\n");
                scanf("%d %d",&matrix_main[j][0],&matrix_main[j][1]);
            }
            while(!feof(fe))
            {
                i=-1;
                do
                {
                    i++;
                    fscanf(fe,"%*c%c%*c%c%*c%*c",&matrix_aux[i][0],&matrix_aux[i][1]);

                }
                while(matrix_aux[i][0]!='f' ||matrix_aux[i][1]!='f' );
                v++;
                for(j=0; j<i; j++)
                {
                    matrix_int[j][0]=(matrix_aux[j][0])-'0';
                    matrix_int[j][1]=(matrix_aux[j][1])-'0';
                }
                for(j=0; j<i; j++)
                {
                    for(k=0; k<n; k++)
                    {

                        if((matrix_main[k][0]==matrix_int[j][0] && matrix_main[k][1]==matrix_int[j][1]) || (matrix_main[k][0]==matrix_int[j][1] && matrix_main[k][1]==matrix_int[j][0]))
                        {
                            count++;
                            if(count==n)
                                printf("sequencia ou peca encontrada na linha %d\n",v);
                                return v;
                        }
                    }
                }
            }
        }
        if(ite==2)
        {
            printf(" ____________________________________________________\n");
            printf("|Quantas pecas deseja procurar.                      |\n");
            printf("|____________________________________________________|\n");
            scanf("%d",&n);
            for(j=0; j<n; j++)
            {
                printf(" ____________________________________________________\n");
                printf("|Insira a peca %d                                    |\n",j+1);
                printf("|____________________________________________________|\n");
                scanf("%d %d",&matrix_main[j][0],&matrix_main[j][1]);
            }
            while(!feof(fe))
            {
                i=-1;
                count2=0;
                count=0;
                do
                {
                    i++;
                    fscanf(fe,"%*c%c%*c%c%*c%*c",&matrix_aux[i][0],&matrix_aux[i][1]);
                    count2++;

                }
                while(matrix_aux[i][0]!='f' ||matrix_aux[i][1]!='f' );
                v++;
                count2--;
                for(j=0; j<i; j++)
                {
                    matrix_int[j][0]=(matrix_aux[j][0])-'0';
                    matrix_int[j][1]=(matrix_aux[j][1])-'0';
                }
                for(j=0; j<i; j++)
                {
                    for(k=0; k<n; k++)
                    {

                        if((matrix_main[k][0]==matrix_int[j][0] && matrix_main[k][1]==matrix_int[j][1]) || (matrix_main[k][0]==matrix_int[j][1] && matrix_main[k][1]==matrix_int[j][0]))
                        {
                            count++;
                            if(count==n)
                            {
                                printf("sequencia ou peca encontrada na linha %d\n",v);
                            }
                        }
                    }
                }
            }
        }
        if(ite==3)
        {
            printf(" ____________________________________________________\n");
            printf("|Quantas pecas deseja que tenha a sequencia?         |\n");
            printf("|____________________________________________________|\n");
            scanf("%d",&n);
            while(!feof(fe))
            {
                i=-1;
                do
                {
                    i++;
                    fscanf(fe,"%*c%c%*c%c%*c%*c",&matrix_aux[i][0],&matrix_aux[i][1]);
                    count++;

                }
                while(matrix_aux[i][0]!='f' ||matrix_aux[i][1]!='f' );
                v++;
                count--;
                if(count==n)
                {
                    printf("sequencia ou peca encontrada na linha %d com %d pecas\n",v,n);
                }
                else
                    count=0;


            }
        }
    }
    fclose(fe);
    return dworks;
}
/** \brief Esta funcao tenta ordenar as subsequencias dos ficheiro para o ficheiro order.
 *
 * \return int
 * \bug não completa a subsequencia e tem erros
 */
int ordena_file()
{
    int i=-1,j=0,k;
    int count=0,count2=0;
    int min=0;
    char matrix_aux[28][2]= {};
    char matrix_aux2[28][2]= {};
    int  matrix_int[28][2]= {};
    int  matrix_int2[28][2]= {};
    int matrix_min[28][2]= {};
    FILE *fe;
    FILE * fo;
    long pos,pos2;
    fe=fopen("regist.txt","r");
    fo=fopen("order.txt","a+");
    if(fe!=NULL)
    {
        while(!feof(fe))
        {
            i=-1;
            do
            {
                i++;
                fscanf(fe,"%*c%c%*c%c%*c%*c",&matrix_aux[i][0],&matrix_aux[i][1]);
            }
            while(matrix_aux[i][0]!='f' || matrix_aux[i][1]!='f');
            pos = ftell(fe);
            for(j=0; j<i; j++)
            {
                matrix_int[j][0]=(matrix_aux[j][0])-'0';
                matrix_int[j][1]=(matrix_aux[j][1])-'0';
                count++;
            }
            min=count;
            while(!feof(fe))
            {
                k=-1;
                do
                {
                    k++;
                    fscanf(fe,"%*c%c%*c%c%*c%*c",&matrix_aux2[k][0],&matrix_aux2[k][1]);
                }
                while(matrix_aux2[k][0]!='f' ||matrix_aux2[k][1]!='f');
                for(j=0; j<k; j++)
                {
                    matrix_int2[j][0]=(matrix_aux2[j][0])-'0';
                    matrix_int2[j][1]=(matrix_aux2[j][1])-'0';
                    count2++;
                }
                if(min<count2)
                {
                    min=count2;
                    for(j=0; j<min; j++)
                    {
                        matrix_min[j][0]=matrix_int2[j][0];
                        matrix_min[j][1]=matrix_int2[j][1];

                    }
                    for(j=0; j<k; j++)
                    {
                        fprintf(fo,"|%d|%d| ",matrix_min[j][0],matrix_min[j][1]);
                    }
                    fprintf(fo,"\n");
                    pos2= ftell(fe);
                    fseek(fe,pos,SEEK_SET);
                    count2=0;
                    break;
                }
            }
        }
    }
    fclose(fe);
    return dworks;
}
/** \brief Vai gerar o baralho. Esta função permite gerar todas as peças do baralho.
 *
 * \param matrix_main[][2] int
 * \param lines int
 * \param columns int
 * \return int
 *
 */
int generate_deck(int matrix_main[][2], int lines, int columns) //gera o baralho
{
    int i=0,j=0,max=6,peca=0;
    //int matrix_peca[28][2] = {{0,0},{1,0},{1,1},{2,0},{2,1},{2,2},{3,0},{3,1},{3,2},{3,3},{4,0},{4,1},{4,2},{4,3},{4,4},{5,0},{5,1},{5,2},{5,3},{5,4},{5,5},{6,0},{6,1},{6,2},{6,3},{6,4},{6,5},{6,6}};
    /** \brief Assegura que gera valores iguais e menores que 6, tais como as peças de dominó
     *
     * \param i-- i=6; i>=0;
     *
     */
    for(i=6; i>=0; i--)
    {
        for(j=0; j<=max; j++) //insere as peças na matriz
        {
            matrix_main[peca][0]=i;
            matrix_main[peca][1]=j;
            peca++;
            //matrix_main[i][0]=j; //primeira coluna
            //matrix_main[i+1][1]=j-1; //segunda coluna
        }
        max--; //decrementa o numero da peça do baralho, de 6 passa para as peças 5, etc
    }
    return 0;
}

/** \brief Esta função, verifica se a peça que o jogador está a inserir é válida, e retorna works (1), se não for válida, retorna dworks (0)
 *
 * \param matrix_main[][2] int
 * \param matrix_player[][2] int
 * \param number int
 * \return int
 *
 */
int valid_hand(int matrix_main[][2],int matrix_player[][2],int number)
{
    int i=0,j=0,count=0;
    for(i=28; i>0; i--)
    {
        for(j=0; j<number; j++)
        {
            /** \brief Verifica se a peça na matriz principal é igual à peça na mão do jogador
             *
             * \param matrix_main[i][1]==matrix_player[j][1] matrix_main[i][0]==matrix_player[j][0] &&
             *
             */
            if(matrix_main[i][0]==matrix_player[j][0] && matrix_main[i][1]==matrix_player[j][1])
            {
                count++;
                if(count==number)
                {
                    break;
                }

            }
        }
    }
    if(count!=number)
    {
        printf(" _________________________\n");
        printf("|Error: peca invalida     |\n");
        printf("|Volte a inserir o baralho|\n");
        printf("|_________________________|\n");
        return dworks;
    }
    for(i=0; i<number; i++)
    {
        for(j=i+1; j<number; j++)
        {
            if(matrix_player[i][0] == matrix_player[j][0] && matrix_player[i][1]==matrix_player[j][1])
            {
                printf(" __________________________\n");
                printf("|Error: peca repetida      |\n");
                printf("|Volte a inserir a peca %d |\n",j+1);
                printf("|__________________________|\n");
                scanf("%d %d",&matrix_player[j][0],&matrix_player[j][1]);
                i=0;
                j=i+1;
            }
        }
    }
    return works;
}

/** \brief Serve para imprimir o baralhos
 *
 * \param matrix_main[][2] int
 * \param lines int
 * \param columns int
 * \return void
 *
 */
void print_deck(int matrix_main[][2], int lines, int columns)
{
    int i=0,j=0;


    printf("---------\n");
    /** \brief Percorre todas as linhas
     *
     * \param i++ i=0; i<lines;
     *
     */
    for(i=0; i<lines; i++)
    {
        printf("|");
        /** \brief Percorre todas as colunas
         *
         * \param j++ j=0; j<columns;
         *
         */
        for(j=0; j<columns; j++)
        {
            printf("%2d |", matrix_main[i][j]);
        }
        printf("\n--------");
        printf("\n");
    }
}
/** \brief Esta função encontra a maior sequência de peças da mão de um jogador num jogo
 *
 * \param matrix_tab[][2] int
 * \param matrix_player[][2] int
 * \param number int
 * \return int
 * \bug por vezes apresenta pecas de outra jogada
 * \bug por vezes apresenta maior sequencia mesmo tendo sido uma sequencia valida completa atingida
 */
int vmax_checker_func(int matrix_tab[][2],int matrix_player[][2],int matrix_vmax[][2],int number)
{
    int i =0,j=0;
    int count=0;
    for(i=0; i<number; i++)
    {
        for(j=0; j<number; j++)
        {
            /** \brief Verifica se a peça que se encontra na mao do jogador é igual à peça que se encontra no tabuleiro
            *
            * \param matrix_player[i][0]==matrix_vamx[i][1]
            * \return if(((matrix_player[i][0]==matrix_vmax[j][0])&&(matrix_player[i][1]==matrix_vmax[j][1]))||
            *
            */
            if(((matrix_player[i][0]==matrix_vmax[j][0])&&(matrix_player[i][1]==matrix_vmax[j][1])) || ((matrix_player[i][1]==matrix_vmax[j][0])&&(matrix_player[i][0]==matrix_vmax[j][1])))
                count++;
        }

    }
    return count;
}

/** \brief A função uniforme permite gerar peças aleatórias atraves do srand, que é iniciado antes da funcao
 *
 * \param rand_min_val int
 * \param rand_max_val int
 * \return int
 *
 */
int uniforme(int rand_min_val, int rand_max_val) //Nao concluida nao gera numero distintos
{

    //rand : This function returns an integer value between 0 and RAND_MAX. - "+1 to avoid being exclusive"
    return rand_min_val + rand() % (rand_max_val - rand_min_val + 1);
}

/** \brief Generate_hand é a função que vai atribuir ao utilizador uma mão de jogo aleatória
 *  Esta função atinge este fim graças a função uniforme que retorna um valor aleatório que é atribuido a um indice, depois copia essa peça para o fim e coloca a -1-1 para que não possa ser utilizada.
 * \param matrix_main[][2] int
 * \param matrix_player[][2] int
 * \param number int
 * \param pecas_disponiveis int
 * \return int
 *
 */
int generate_hand(int matrix_main[][2],int matrix_player[][2],int number, int pecas_disponiveis)
{
    int i=0,aux=0, max=0,j=0;
    max = pecas_disponiveis-1;
    for(i=0; i<number; i++) //atribuir as pecas
    {
        aux=uniforme(0,max); //gera um indice de uma peca aleatorio
        matrix_player[i][0]=matrix_main[aux][0];
        matrix_player[i][1]=matrix_main[aux][1];

        /** \brief Este ciclo vai de uma posição gerada aleatoriamente (aux) até à posição max, que é decrementada para nao repetir peças na mão do jogador
         *
         * \param j++ j=aux; j<max;
         *
         */
        for(j=aux; j<max; j++)
        {
            matrix_main[j][0]=matrix_main[j+1][0];
            matrix_main[j][1]=matrix_main[j+1][1];

            matrix_main[j+1][0]=-1; //inicializa-se a peça retirada a -1
            matrix_main[j+1][1]=-1;
        }

        max--; //ja gerei uma peça ate 27, logo, ja nao quero gerar 27 peças, mas sim 26
    }
    /** \brief Atualiza o valor de peças disponiveis e retorna esse resultado, para os casos com mais que um jogador
     *
     * \param
     * \param
     * \return
     *
     */
    pecas_disponiveis=pecas_disponiveis-number;

    return pecas_disponiveis;
}
/** \brief Esta função ordena a mão, colocando a peça com maior prioridade em cima, verificando a parte esquerda da peça primeiro e se for igual verifica a parte direita da peça e repete o processo para todas as peças da mao, baseado no insertion sort
 *
 * \param matrix_player[][2] int
 * \param number int
 * \return void
 *
 */
void ordena_hand(int matrix_player[][2],int number)
{
    int matrix_aux2[28][2]= {};
    int i=0,j=0;
    for(i=0; i<number; i++)
    {
        for(j=i; j<number; j++)
        {
            /** \brief Verifica a parte esquerda da peça atual com a peça seguinte
             *
             * \param matrix_player[i][0]<matrix_player[j][0]
             *
             */
            if(matrix_player[i][0]<matrix_player[j][0])
            {
                matrix_aux2[i][0]=matrix_player[i][0];
                matrix_aux2[i][1]=matrix_player[i][1];
                matrix_player[i][0]=matrix_player[j][0];
                matrix_player[i][1]=matrix_player[j][1];
                matrix_player[j][0]=matrix_aux2[i][0];
                matrix_player[j][1]=matrix_aux2[i][1];
            }
            /** \brief Verifica se a parte esquerda das peças for igual, verifica se a parte direita da peça atual for menor que a parte direita da peça seguinte
             *
             * \param matrix_player[i][0]==matrix_player[j][0]&& matrix_player[i][1]<matrix_player[j][1]
             * \return else
             *
             */
            else if(matrix_player[i][0]==matrix_player[j][0]&& matrix_player[i][1]<matrix_player[j][1])
            {
                matrix_aux2[i][0]=matrix_player[i][0];
                matrix_aux2[i][1]=matrix_player[i][1];
                matrix_player[i][0]=matrix_player[j][0];
                matrix_player[i][1]=matrix_player[j][1];
                matrix_player[j][0]=matrix_aux2[i][0];
                matrix_player[j][1]=matrix_aux2[i][1];
            }
        }
    }
}
/** \brief Função que vai verificar se uma peça é válida para jogo, se for ele vai devolver works senão devolve dowrks. Se a peça encaixar entao ele vai para a proxima posicao senão tenta outra peça
 *
 * \param matrix_tab[][2] int
 * \param [][2] int matrix_player
 * \param matrix_vmax[][2] int
 * \param number int
 * \param count int
 * \param vmax int
 * \param nfac int
 * \param pecas int
 * \param itera int
 * \param id int
 * \return int
 * Esta função verifica todas as condições possiveis para ser uma peça válida ou não, devolvendo em macros works ou dworks
 */
int verified(int matrix_tab[][2], int matrix_player [][2],int matrix_vmax[][2],int number,int count,int vmax,int nfac,int pecas,int itera,int id)
{
    int switchp;
    int paux,paux2,paux3,paux4;
    int j,i;

    if(count == 0 ) /**< A primeira peça encaixa sempre. */
    {
        /** \brief Isto permite rodar as peças para evitar\repetir
         *
         * \param j++ j=itera; j<number;
         *
         */
        for(j=itera; j<number-pecas; j++)
        {
            paux=matrix_player[j][0];
            paux2=matrix_player[j][1];
            matrix_player[j][0]=matrix_player[j+1][0];
            matrix_player[j][1]=matrix_player[j+1][1];

            matrix_player[j+1][0]=paux; //inicializa-se a peça retirada a -1
            matrix_player[j+1][1]=paux2;
        }
        return works;

    }
    /** \brief Permite que nunca repita peças.
     *
     * \param matrix_tab[count-1][1]==matrix_tab[count][1] matrix_tab[count-1][0]==matrix_tab[count][0] &&
     * \return else
     *
     */
    for(i=1; i<=count; i++)
    {
        if((matrix_tab[count-i][0]==matrix_tab[count][0] && matrix_tab[count-i][1]==matrix_tab[count][1]) || (matrix_tab[count-i][0]==matrix_tab[count][1] && matrix_tab[count-i][1]==matrix_tab[count][0]) )
        {
            return dworks;
        }
    }
    /** \brief Verifica se a posição anterior é igual à posição atual de count
     *
     * \param count-1==0 && matrix_tab[count-1][0] == matrix_tab[count][1]
     * \return else
     *
     */
    if(count-1==0 && (matrix_tab[count-1][0]!=matrix_tab[count-1][1]) && (matrix_tab[count-1][0] == matrix_tab[count][1]))
    {
        switchp = matrix_tab[count-1][1];
        matrix_tab[count-1][1]= matrix_tab[count-1][0];
        matrix_tab[count-1][0]= switchp;

        switchp = matrix_tab[count][1];
        matrix_tab[count][1]= matrix_tab[count][0];
        matrix_tab[count][0]= switchp;

        for(j=itera; j<number-pecas; j++)
        {
            paux=matrix_player[j][0];
            paux2=matrix_player[j][1];
            matrix_player[j][0]=matrix_player[j+1][0];
            matrix_player[j][1]=matrix_player[j+1][1];

            matrix_player[j+1][0]=paux; //inicializa-se a peça retirada a -1
            matrix_player[j+1][1]=paux2;
        }

        return works;
    }
    /** \brief Esta função vai permitir rodar a peça anterior a ela, mas só se a primeira peça for 0 , para não compremeter o resto do jogo.
     *
     * \param matrix_tab[count][0] count-1==0 &&matrix_tab[count-1][0]==
     * \return else
     *
     */
    if(count-1==0 && (matrix_tab[count-1][0]!=matrix_tab[count-1][1]) && (matrix_tab[count-1][0] == matrix_tab[count][0]))
    {
        switchp = matrix_tab[count-1][1];
        matrix_tab[count-1][1]= matrix_tab[count-1][0];
        matrix_tab[count-1][0]= switchp;

        for(j=itera; j<number-pecas; j++)
        {
            paux=matrix_player[j][0];
            paux2=matrix_player[j][1];
            matrix_player[j][0]=matrix_player[j+1][0];
            matrix_player[j][1]=matrix_player[j+1][1];

            matrix_player[j+1][0]=paux; //inicializa-se a peça retirada a -1
            matrix_player[j+1][1]=paux2;
        }
        return works;
    }
    /** \brief Verifica se a peça encaixa normalmente
     *
     * \param matrix_tab[count][0]==matrix_tab[count-1][1]
     * \return else
     *
     */
    if(matrix_tab[count][0]==matrix_tab[count-1][1])
    {
        for(j=itera; j<number-pecas; j++)
        {
            paux=matrix_player[j][0];
            paux2=matrix_player[j][1];
            matrix_player[j][0]=matrix_player[j+1][0];
            matrix_player[j][1]=matrix_player[j+1][1];

            matrix_player[j+1][0]=paux; //inicializa-se a peça retirada a -1
            matrix_player[j+1][1]=paux2;
        }
        return works;

    }
    /** \brief Este if permite verificar se , se rodarmos a peça ela pode encaixar na peça anterior
     *
     * \param matrix_tab[count][1]==matrix_tab[count-1][1]
     * \return else
     *
     */
    if(matrix_tab[count][1]==matrix_tab[count-1][1])
    {
        switchp = matrix_tab[count][1];
        matrix_tab[count][1]= matrix_tab[count][0];
        matrix_tab[count][0]= switchp;

        for(j=itera; j<number-pecas; j++)
        {
            paux=matrix_player[j][0];
            paux2=matrix_player[j][1];
            matrix_player[j][0]=matrix_player[j+1][0];
            matrix_player[j][1]=matrix_player[j+1][1];

            matrix_player[j+1][0]=paux; //inicializa-se a peça retirada a -1
            matrix_player[j+1][1]=paux2;
        }

        return works;
    }
    /** \brief Verifica se a parte direita da peça na posição atual (count), é igual à primeira peça no tabuleiro
     *
     * \param matrix_tab[count][1]==matrix_tab[0][0]
     *
     */
    if(matrix_tab[count][1]==matrix_tab[0][0])
    {
        paux3=matrix_tab[count][0];
        paux4=matrix_tab[count][1];
        for(j=count-1; j>=0; j--)
        {
            paux=matrix_tab[j][0];
            paux2=matrix_tab[j][1];
            matrix_tab[j][0]=matrix_tab[j+1][0];
            matrix_tab[j][1]=matrix_tab[j+1][1];
            matrix_tab[j+1][0]=paux; //inicializa-se a peça retirada a -1
            matrix_tab[j+1][1]=paux2;
        }
        matrix_tab[0][0]=paux3;
        matrix_tab[0][1]=paux4;

        paux3=matrix_player[count][0];
        paux4=matrix_player[count][1];
        for(j=count-1; j>=0; j--)
        {
            paux=matrix_player[j][0];
            paux2=matrix_player[j][1];
            matrix_player[j][0]=matrix_player[j+1][0];
            matrix_player[j][1]=matrix_player[j+1][1];
            matrix_player[j+1][0]=paux;
            matrix_player[j+1][1]=paux2;
        }
        matrix_player[0][0]=paux3;
        matrix_player[0][1]=paux4;

        return works;
    }
    /** \brief Verifica se a parte esquerda da peça na posição atual (count), é igual à primeira peça no tabuleiro
     *
     * \param matrix_tab[count][0]==matrix_tab[0][0]
     *
     */
    if(matrix_tab[count][0]==matrix_tab[0][0])
    {
        switchp = matrix_tab[count][1];
        matrix_tab[count][1]= matrix_tab[count][0];
        matrix_tab[count][0]= switchp;

        paux3=matrix_tab[count][0];
        paux4=matrix_tab[count][1];
        for(j=count-1; j>=0; j--)
        {
            paux=matrix_tab[j][0];
            paux2=matrix_tab[j][1];
            matrix_tab[j][0]=matrix_tab[j+1][0];
            matrix_tab[j][1]=matrix_tab[j+1][1];
            matrix_tab[j+1][0]=paux; //inicializa-se a peça retirada a -1
            matrix_tab[j+1][1]=paux2;
        }
        matrix_tab[0][0]=paux3;
        matrix_tab[0][1]=paux4;

        paux3=matrix_player[count][0];
        paux4=matrix_player[count][1];
        for(j=count-1; j>=0; j--)
        {
            paux=matrix_player[j][0];
            paux2=matrix_player[j][1];
            matrix_player[j][0]=matrix_player[j+1][0];
            matrix_player[j][1]=matrix_player[j+1][1];
            matrix_player[j+1][0]=paux;
            matrix_player[j+1][1]=paux2;
        }
        matrix_player[0][0]=paux3;
        matrix_player[0][1]=paux4;

        return works;
    }
    return dworks;
}
/** \brief Esta função guarda a maior sequência válida possóvel de uma jogada num ficheiro texto
 *
 * \param matrix_tab[][2] int
 * \param matrix_vmax[][2] int
 * \param count int
 * \param vmax int
 * \return int
 *
 */
int vmax_func(int matrix_tab[][2],int matrix_vmax[][2],int count,int vmax)
{
    int v;
    /** \brief Vai verificar e guardar a maior sequencia que encontrar.
    *
    * \param v++ v=0; v<vmax;
    *  Se o count for maior que o valor de vmax anterior entao ele vai guardar o valor e vai copiar a sequencia para a matrix_vmax
    * @bug por vezes repete uma peca ou dá ate mesmo uma sequencia invalida de jogo
    */
    for(v=0; v<vmax; v++)
    {
        matrix_vmax[v][0]=matrix_tab[v][0];
        matrix_vmax[v][1]=matrix_tab[v][1];
    }
    return vmax;
}
/** \brief Esta função aplica a recursividade para determinar uma sequencia de peças valida , se encontrar vai a procura demais sequencias, e ao mesmo tempo que faz isso vai guardando a maior sequencia possivel.
 *
 * \param matrix_tab[][2] int
 * \param [][2] int matrix_player
 * \param matrix_vmax[][2] int
 * \param number int
 * \param count int
 * \param vmax int
 * \param nfac int
 * \param pecas int
 * \param itera int
 * \param id int
 * \return int
 * \bug {Por vezes não devolve a maior sub-sequencia possivel }
 */
int play_recursive(int matrix_tab[][2], int matrix_player [][2],int matrix_aux[][2],int matrix_vmax[][2],int number,int count,int vmax,int nfac,int pecas,int itera,int id,int aux_aux)
{
    int v;
    int i;
    int test;
    if(id >= nfac) /**< Vai verificar se tem mais sequencias válidas */
    {
        return count;
    }
    /** \brief Giarda uma sequencia completa no ficheiro
     *
     * \param number count ==
     *
     */
    if(count == number)
    {
        save_file_part1(matrix_tab,count);
        if(id==0)
        {
            printf("\t ____________\t\n");
            printf("\t|jogo gerado!|\t\n");
            printf("\t|____________|\t\n");
            print_deck(matrix_tab,number,2);

        }
        /** \brief Verifica se a matriz auxiliar na posição esquerda é diferente de -1 e o id é diferente de 0 e igual a number
         *
         * \param matrix_aux[255][0]!=-1 && (id!=0 || id == number
         *
         */
        if(matrix_aux[255][0]!=-1 && (id!=0 || id == number))
        {
            for(v=aux_aux; v<= aux_aux+number; v++)
            {
                matrix_aux[v][0]=matrix_tab[v][0];
                matrix_aux[v][1]=matrix_tab[v][1];
            }
            aux_aux=aux_aux+number;
        }
        else if(matrix_aux[255][0]==-1)
        {
            printf(" ________________________________\n");
            printf("|Armazenamento cheio ou invalido!|\n");
            printf("|________________________________|\n");
            return works;
        }
        id=id+number;
        count=0;
        pecas=1;
    }
    for (i=0; i<=number-pecas; i++)
    {
        itera=i;
        matrix_tab[count][0] = matrix_player[i][0];
        matrix_tab[count][1] = matrix_player[i][1];
        /** \brief Verifica se a peça é válida e retorna 1
         *
         * \param matrix_tab
         * \param matrix_player
         * \param matrix_vmax
         * \param number
         * \param count
         * \param vmax
         * \param nfac
         * \param pecas
         * \param itera
         * \param id
         * \return works
         *
         */
        if (verified(matrix_tab,matrix_player,matrix_vmax,number,count,vmax,nfac,pecas,itera,id) == works)
        {
            if (count > vmax)
            {
                vmax=count;
                /** \brief Retorna e atribui a vmax o valor retornado pela função vmax_func
                *
                * \param matrix_tab
                * \param matrix_vmax
                * \param count
                * \param vmax
                * @bug  por vezes repete a peça na chamada da recursividade.
                */
                vmax=vmax_func(matrix_tab,matrix_vmax,count,vmax);
            }
            pecas++;
            count++;
            save_file_part1(matrix_tab,count);
            /** \brief Retorna e atribui a test o valor retornado pela função play_recursive
             *
             * \param matrix_tab
             * \param matrix_player
             * \param matrix_aux
             * \param matrix_vmax
             * \param number
             * \param count
             * \param vmax
             * \param nfac
             * \param pecas
             * \param itera
             * \param id
             * \param aux_aux
             *
             */
            test = play_recursive(matrix_tab,matrix_player,matrix_aux,matrix_vmax,number,count,vmax,nfac,pecas,itera,id,aux_aux);
            if(test != dworks)
            {
                return test;
            }
            pecas--;
            count--;
        }
    }

    return dworks;
}
/** \brief Função que vai verificar se uma peça é válida para jogo, se for ele vai devolver works senão devolve dowrks. Se a peça encaixar entao ele vai para a proxima posicao senão tenta outra peça. Para 2 ou mais jogadores
 *
 * \param matrix_tab[][2] int
 * \param [][2] int matrix_player
 * \param matrix_vmax[][2] int
 * \param number int
 * \param count int
 * \param vmax int
 * \param nfac int
 * \param pecas int
 * \param pecas2 int
 * \param itera int
 * \param id int
 * \param id_player int
 * \return int
 *
 */
int verified_ns(int matrix_tab[][2], int matrix_player [][2],int matrix_vmax[][2],int number,int count,int vmax,int nfac,int pecas,int pecas2,int itera,int id,int id_player)
{
    int switchp;
    int i;
    if(count == 0 ) /**< A primeira peça encaixa sempre. */
    {
        return works;
    }
    /** \brief Permite que nunca repita peças.Ele vai ver todas as pecas anteriormente jogadas , para confirmar que não repete nenhuma.
     *
     * \param matrix_tab[count-1][1]==matrix_tab[count][1] matrix_tab[count-1][0]==matrix_tab[count][0] &&
     * \return else
     *
     */
    for(i=1; i<=count; i++)
    {
        if((matrix_tab[count-i][0]==matrix_tab[count][0] && matrix_tab[count-i][1]==matrix_tab[count][1]) || (matrix_tab[count-i][0]==matrix_tab[count][1] && matrix_tab[count-i][1]==matrix_tab[count][0]) )
        {
            return dworks;
        }
    }
    /** \brief Esta funcao permite rodar a primeira peca e a peca que vai encaixar para assim cobrir o maximo de hipoteses possivel
     *
     * \param count-1==0 && matrix_tab[count-1][0] == matrix_tab[count][1]
     *
     */
    if(count-1==0 && matrix_tab[count-1][0] == matrix_tab[count][1])
    {
        switchp = matrix_tab[count-1][1];
        matrix_tab[count-1][1]= matrix_tab[count-1][0];
        matrix_tab[count-1][0]= switchp;

        switchp = matrix_tab[count][1];
        matrix_tab[count][1]= matrix_tab[count][0];
        matrix_tab[count][0]= switchp;

        return works;
    }
    /** \brief Esta função vai permitir rodar a peça anterior a ela, mas só se a primeira peça for 0 , para não compremeter o resto do jogo.
     *
     * \param matrix_tab[count][0] count-1==0 &&matrix_tab[count-1][0]==
     * \return else
     *
     */
    else if(count-1==0 && matrix_tab[count-1][0] == matrix_tab[count][0])
    {
        switchp = matrix_tab[count-1][1];
        matrix_tab[count-1][1]= matrix_tab[count-1][0];
        matrix_tab[count-1][0]= switchp;


        return works;
    }
    /** \brief Verifica se a peça encaixa normalmente
     *
     * \param matrix_tab[count][0]==matrix_tab[count-1][1]
     * \return else
     *
     */
    else if(matrix_tab[count][0]==matrix_tab[count-1][1])
    {
        return works;

    }
    /** \brief Este if permite verificar se , se rodarmos a peça ela pode encaixar na peça anterior
     *
     * \param matrix_tab[count][1]==matrix_tab[count-1][1]
     * \return else
     *
     */
    else if(matrix_tab[count][1]==matrix_tab[count-1][1])
    {
        switchp = matrix_tab[count][1];
        matrix_tab[count][1]= matrix_tab[count][0];
        matrix_tab[count][0]= switchp;

        return works;
    }
    return dworks;
}
/** \brief Esta função aplica a recursividade para determinar uma sequencia de peças valida , se encontrar vai a procura demais sequencias, e ao mesmo tempo que faz isso vai guardando a maior sequencia possivel. Para 2 ou mais jogadores.
 *
 * \param matrix_tab[][2] int
 * \param matrix_player[][2] int
 * \param matrix_aux[][2] int
 * \param matrix_vmax[][2] int
 * \param number int
 * \param count int
 * \param vmax int
 * \param nfac int
 * \param pecas int
 * \param pecas2 int
 * \param itera int
 * \param id int
 * \param id_player int
 * \return int
 * \bug por vezes o programa crasha ou encontra uma sequencia errada
 * \bug joga primeiro a ultima e depois sobe ate a primeira mao
 *
 */
int play_recursive_more(int matrix_tab[][2],int matrix_player[][2],int matrix_aux[][2],int matrix_vmax[][2],int number,int count,int vmax,int nfac,int pecas,int pecas2,int itera,int id,int id_player,int n_player)
{
    int i;
    int test;
    /** \brief Verifica se o id é maior ou igual a nfac
     *
     * \param id >=nfac
     *
     */
    if(id >= nfac)
    {
        return count;
    }
    if (count > vmax)
    {
        vmax=count;
        /** \brief Retorna e atribui a vmax o valor retornado pela função vmax_func
         *
         * \param matrix_tab
         * \param matrix_vmax
         * \param count
         * \param vmax
         *
         */
        vmax=vmax_func(matrix_tab,matrix_vmax,count,vmax);
    }
    /** \brief Permite guardar a sequencia valida que encontrou e continuar a procurar por mais sequencias.
     *
     * \param number count ==
     *
     */
    if(count == number)
    {
        save_file_part1(matrix_tab,count);
        if(id==0)
        {
            printf("\t ______________\t\n");
            printf("\t|jogo gerado!  |\t\n");
            printf("\t|______________|\t\n");
            print_deck(matrix_tab,number,2);
        }
        id=id+number;
        count=0;
        pecas=1;
        pecas2=0;
    }
    if(pecas2==number)
    {
        return count;
    }
    for(i=pecas2 ; i<number; i++)
    {
        matrix_tab[count][0] = matrix_player[i][0];
        matrix_tab[count][1] = matrix_player[i][1];
        /** \brief Verifica se a peça é válida e retorna 1
         *
         * \param matrix_tab
         * \param matrix_player
         * \param matrix_vmax
         * \param number
         * \param count
         * \param vmax
         * \param nfac
         * \param pecas
         * \param pecas2
         * \param itera
         * \param id
         * \param id_player
         * \return if
         *
         */
        if (verified_ns(matrix_tab,matrix_player,matrix_vmax,number,count,vmax,nfac,pecas,pecas2,itera,id,id_player) == works)
        {
            /** \brief Estes if's permitem determinar que mao vai jogar a seguir.
             *
             * \param (count%2!=0 count!=0 &&
             *
             */
            if(count!=0 && (count%2!=0) && (n_player==2 || n_player==4))
            {
                pecas2=(number-id_player)/pecas2;
            }
            else if(count !=0 && (count%3!=0) && (n_player==3 || n_player==4))
            {
                pecas2=(number-id_player)/pecas2;
            }
            else
            {
                pecas2=pecas2+(number-id_player);
            }
            pecas++;
            count++;
            save_file_part1(matrix_tab,count);
            /** \brief Retorna e atribui a test o valor retornado pela função play_recursive_more
             *
             * \param matrix_tab
             * \param matrix_player
             * \param matrix_aux
             * \param matrix_vmax
             * \param number
             * \param count
             * \param vmax
             * \param nfac
             * \param pecas
             * \param pecas2
             * \param itera
             * \param id
             * \param id_player
             *
             */
            test = play_recursive_more(matrix_tab,matrix_player,matrix_aux,matrix_vmax,number,count,vmax,nfac,pecas,pecas2,itera,id,id_player,n_player);
            if(test != dworks)
            {
                return test;
            }
            pecas--;
            count--;
        }

    }
    /** \brief Se o id é igual a 0 e count for diferente de number
     *
     * \param id==0 && count != number
     *
     */
    return dworks;
}


