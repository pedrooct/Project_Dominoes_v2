#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../func_h/data.h"

#define works 1
#define dworks 0

/** \brief Esta função tem como objetivo principal, inicializar e alocar espaço para as variaveis e arrays dinamicos , respetivamente.
 *
 * \param start GAME*
 * \return void
 *
 */
void inicializer(GAME * start)
{
    int i =0;
    PECA *paux=NULL;
    HAND *paux2=NULL;
    HAND_VMAX *paux3=NULL;
    TAB *paux4=NULL;
    SAVER * paux5=NULL;

    start->pecas_game=(PECA*)malloc(sizeof(PECA)*28);
    start->hand_game=(HAND*)malloc(sizeof(HAND)*28);
    start->tab_game=(TAB*)malloc(sizeof(TAB)*28);
    start->vmax_game=(HAND_VMAX*)malloc(sizeof(HAND_VMAX)*28);
    start->saver=(SAVER*)malloc(sizeof(SAVER)*28);
    start->count=0;
    start->id=0;
    start->id_player=0;
    start->n_player=0;
    start->itera=0;
    start->nfac=0;
    start->number=4;
    start->pecas=1;
    start->pecas2=0;
    start->pecas_disponivel=28;
    start->vmax=0;
    start->vmax_checker=0;
    start->lines_pecas=0;
    start->saver_values=0;
    start->find_sequence=0;
    paux= start->pecas_game;
    paux2= start->hand_game;
    paux3=start->vmax_game;
    paux4=start->tab_game;
    paux5=start->saver;
    for(i=0; i<28; i++)
    {
        paux->pinta_direita=-1;
        paux->pinta_esquerda=-1;
        paux++;
        paux2->hand_direita=-1;
        paux2->hand_esquerda=-1;
        paux2++;
        paux3->vhand_direita=-1;
        paux3->vhand_esquerda=-1;
        paux++;
        paux4->tab_direita=-1;
        paux4->tab_esquerda=-1;
        paux4++;
        paux5->saver_direita=-1;
        paux5->saver_esquerda=-1;
        paux5++;

    }
}


/** \brief Esta função serve para gerar o factorial , vai assim guarda-lo na varivel nfac na função GAME
 *
 * \param GAME*start
 * \return int
 *
 */
int generate_fac_struct(GAME*start)
{
    start->nfac=start->number;
    int i=0;
    for(i=start->number-1; i>1; i--)
    {
        start->nfac=start->nfac*i;
    }
    return start->nfac;
}

/** \brief Esta função vai gerar a o baralho ao jogador.
 *
 * \param start GAME*
 * \return void
 *
 */
void generate_deck_sturct(GAME * start)
{
    PECA * paux=NULL;
    int i=0,j=0,max=6;
    paux=start->pecas_game;
    if(start->pecas_game!=NULL)
    {
        for(i=6; i>=0; i--)
        {
            for(j=0; j<=max; j++)
            {
                paux->pinta_direita=j;
                paux->pinta_esquerda=i;
                start->lines_pecas++;
                paux++;
            }
            max--;/**< Esta decrementação permite que assim que comece do valor mais elevado 6 ate 0 */
        }
    }
}
/** \brief Imprime o tabuleiro de jogo ou seja a estrutura com o array dinamico TAB
 *
 * \param start GAME
 * \return void
 *
 */
void print_deck_tab(GAME start)
{
    int i=0;
    TAB * pnew= start.tab_game;
    for(i=0; i<start.number; i++)
    {
        printf("-------\n");
        printf("|%2d|%2d|",pnew->tab_esquerda,pnew->tab_direita);
        printf("\n-------");
        printf("\n");
        pnew++;
    }
}
/** \brief Esta funcao imprime a mão do jogo do jogador do array dinamico HAND
 *
 * \param start GAME
 * \return void
 *
 */
void print_deck_hand(GAME start)
{
    int i=0;
    HAND * pnew= start.hand_game;
    for(i=0; i<start.number; i++)
    {
        printf("-------\n");
        printf("|%2d|%2d|",pnew->hand_esquerda,pnew->hand_direita);
        printf("\n-------");
        printf("\n");
        pnew++;
    }
}
/** \brief Serve para imprimir do array dinamico da estrutura HAND_VMAX a maior mão de jogo possivel
 *
 * \param start GAME
 * \return void
 *
 */
void print_deck_vmax(GAME start)
{
    int i=0;
    HAND_VMAX * pnew= start.vmax_game;
    for(i=0; i<start.vmax; i++)
    {
        printf("-------\n");
        printf("|%2d|%2d|",pnew->vhand_esquerda,pnew->vhand_direita);
        printf("\n-------");
        printf("\n");
        pnew++;
    }
}
/** \brief Esta função valida uma mão escolhida pelo jogador ou lida de um ficheiro. Esta função verifica se a mão é valida para o baralho e se não tem peças repetidas, pela respetiva ordem , se na mão uma peca tiver reptida esta deixa alterar a peca sem ter de inserir todas as pecas de novo.
 *
 * \param start GAME*
 * \return int
 *
 */
int valid_hand_struct(GAME * start)
{
    PECA * paux=NULL;
    HAND * pauxhand=NULL;
    int i=0,j=0,count=0;
    paux=start->pecas_game;
    pauxhand=start->hand_game;
    for(i=28; i>0; i--)
    {
        for(j=0; j<start->number; j++)
        {
            if((paux+i)->pinta_esquerda == (pauxhand+j)->hand_esquerda && (paux+i)->pinta_direita == (pauxhand+j)->hand_direita)
            {
                count++;
                if(count==start->number)
                {
                    break;
                }
            }
        }
    }
    if(count!=start->number)
    {
        printf(" _________________________\n");
        printf("|Error: peca invalida     |\n");
        printf("|Volte a inserir o baralho|\n");
        printf("|_________________________|\n");
        return dworks ;
    }
    paux=start->pecas_game;
    pauxhand=start->hand_game;
    for(i=0; i<start->number; i++)
    {
        for(j=i+1; j<start->number; j++)
        {
            if((pauxhand+i)->hand_esquerda == (pauxhand+j)->hand_esquerda && (pauxhand+i)->hand_direita == (pauxhand+j)->hand_direita)
            {
                printf(" __________________________\n");
                printf("|Error: peca %d repetida   |\n",j+1);
                printf("|__________________________|\n");
                scanf("%d %d",&(pauxhand+j)->hand_esquerda,&(pauxhand+i)->hand_direita);
                i=0;
                j=i+1;
                pauxhand=start->hand_game;
            }
        }
    }
    return works;
}
/** \brief Esta funcao vai procurar em todas as jogadas efetuadas pelo o utilizador uma sequencia ou peca especifica usada para a respetiva jogada.
 *
 * \param start GAME*
 * \return int
 *
 */
int find_sequence_struct(GAME * start)
{
    HAND * paux=start->hand_game;
    int i=-1,j=0,k,n;
    int ite=0;
    int count=0,count2=0;
    char matrix_aux[28][2]= {};
    int  matrix_int[28][2]= {};
    int matrix_main[28][2]= {};
    FILE *fe;
    fe=fopen("registpar2.txt","r");
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
                start->find_sequence++;
                for(j=0; j<i; j++)
                {
                    matrix_int[j][0]=(matrix_aux[j][0])-'0';
                    matrix_int[j][1]=(matrix_aux[j][1])-'0';
                }
                for(j=0; j<i; j++)
                {
                    for(k=0; k<n; k++)
                    {
                        if(((paux+k)->hand_esquerda==matrix_int[j][0] && (paux+k)->hand_direita==matrix_int[j][1]) || ((paux+k)->hand_esquerda==matrix_int[j][1] && (paux+k)->hand_direita==matrix_int[j][0]))
                        {
                            count++;
                            if(count==n)
                                return start->find_sequence;
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
                start->find_sequence++;
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
                        if(((paux+k)->hand_esquerda==matrix_int[j][0] && (paux+k)->hand_direita==matrix_int[j][1]) || ((paux+k)->hand_esquerda==matrix_int[j][1] && (paux+k)->hand_direita==matrix_int[j][0]))
                        {
                            count++;
                            if(count==n && count2==n)
                            {
                                printf("sequencia ou peca encontrada na linha %d\n",start->find_sequence);
                                count=0;
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
                start->find_sequence++;
                count--;
                if(count==n)
                {
                    printf("sequencia ou peca encontrada na linha %d com %d pecas\n",start->find_sequence,n);
                }
                else
                    count=0;
            }
        }
    }
    fclose(fe);
    return dworks;
}

/** \brief Esta funcao vai gerar uma mão aleatoria para o jogador
 *
 * \param start GAME*
 * \return int
 *
 */
int generate_hand_struct(GAME * start)
{
    int i=0,aux=0, max=0,j=0;
    PECA * paux=start->pecas_game;
    HAND *pnew=NULL;
    start->hand_game=(HAND*)malloc(sizeof(HAND)*(start->number));
    pnew=start->hand_game;
    for(i=0; i<(start->number); i++)
    {
        pnew->hand_direita=-1;
        pnew->hand_esquerda=-1;
        pnew++;
    }
    max = start->pecas_disponivel-1;
    pnew=start->hand_game;
    for(i=0; i<(start->number); i++) //atribuir as pecas
    {
        aux=uniforme(0,max);
        paux=paux+aux; //gera um indice de uma peca aleatorio
        pnew->hand_esquerda=paux->pinta_esquerda;
        pnew->hand_direita=paux->pinta_direita;
        for(j=aux; j<max; j++)
        {
            paux->pinta_esquerda=(paux+1)->pinta_esquerda;
            paux->pinta_direita=(paux+1)->pinta_direita;
            (paux+(max-aux))->pinta_esquerda=-1;
            (paux+(max-aux))->pinta_direita=-1;
        }
        paux=start->pecas_game;
        paux=paux+aux;
        pnew++;
        paux=paux-aux;
        max--;
    }
    start->pecas_disponivel=start->pecas_disponivel-start->number;

    return start->pecas_disponivel;
}
/** \brief Esta funcao tem a unica funcao de guardar a maior mão de jogo possivel, fax isso verificando sempre que uma nova peca vailda e jogada
 *
 * \param start GAME*
 * \return int
 *
 */
int vmax_func_struct(GAME *start)
{
    int v;
    HAND_VMAX*phand=start->vmax_game;
    TAB * ptab=start->tab_game;

    if(start->vmax<start->count)
    {
        start->vmax=start->count;
        for(v=0; v<start->vmax; v++)
        {
            (phand+v)->vhand_esquerda=(ptab+v)->tab_esquerda;
            (phand+v)->vhand_direita=(ptab+v)->tab_direita;
        }
    }
    return start->vmax;
}
/** \brief Verifica se a jogada com o maior numero de pecas guardado é válida..
 *
 * \param start GAME*
 * \return int
 *
 */
int vmax_checker_func_struct(GAME * start)
{
    int i =0,j=0;
    int count=0;
    HAND * paux= NULL;
    HAND_VMAX * paux2=NULL;

    paux = start->hand_game;
    paux2=start->vmax_game;
    for(i=0; i<start->number; i++)
    {
        for(j=0; j<start->number; j++)
        {
            if(((((paux+i)->hand_esquerda)==(paux2+j)->vhand_esquerda) && ((paux+i)->hand_direita)==((paux2+j)->vhand_direita)) ||  ((((paux+i)->hand_direita)==((paux2+j)->vhand_esquerda)) && (((paux+i)->hand_esquerda)==((paux2+j)->vhand_direita)))) //|| ((&&(matrix_player[i][0]==matrix_vmax[j][1])))
                count++;
        }

    }
    return count;
}

/** \brief Esta funcao aloca espaco para a estrutura SAVER, para esta puder guardar todas as jogadas validas que a mão do jogador possa ter.
 *
 * \param start GAME*
 * \return int
 *
 */
int resizesaver(GAME * start)
{
    int i =0;
    SAVER * paux = start->saver;
    int matrix_aux[MAX100][2];
    int j = start->saver_values;
    //start->saver=(SAVER*)malloc(sizeof(SAVER)*28);
    for(i=0; i<start->saver_values; i++)
    {
        matrix_aux[i][0]=paux->saver_esquerda;
        matrix_aux[i][1]=paux->saver_direita;
        paux++;
    }
    paux=(SAVER*)malloc(sizeof(SAVER)*j);
    for(i=0; i<j; i++)
    {
        paux->saver_esquerda=matrix_aux[i][0];
        paux->saver_direita=matrix_aux[i][1];
        paux++;
    }
    for(i=j; i<j+start->saver_values; i++)
    {
        paux->saver_esquerda=-1;
        paux->saver_direita=-1;
        paux++;
    }
    //free(start->saver);
    return 0;
}
/** \brief Guarda para um ficheiro todas as pecas validas jogadas.
 *
 * \param start GAME
 * \return void
 *
 */
void save_file(GAME start)
{
    int k =0;
    FILE * fe;
    fe=fopen("registpar2.txt","a+");
    TAB *paux2= NULL;
    if(fe!=NULL)
    {
        paux2=start.tab_game;
        for(k=0; k<start.count; k++)
        {
            fprintf(fe,"|%d|%d| ",(*(paux2+k)).tab_esquerda,(*(paux2+k)).tab_direita);
        }
        fprintf(fe,"|f|f|\n");
    }
    fclose(fe);
}
/** \brief Esta funcao verifica se a peca jogada e valida no tabuleiro
 *
 * \param start GAME*
 * \return int
 *
 */
int verified_struct(GAME * start)
{
    int switchp;
    int paux,paux2,paux3,paux4;
    int j,i;
    HAND * paux_hand;
    TAB *paux2_tab;
    int count = start->count;

    paux_hand=start->hand_game;
    paux2_tab=start->tab_game;

    if(start->count == 0 ) /**< A primeira peça encaixa sempre. */
    {
        /** \brief Isto permite rodar as peças para evitar\repetir
         *
         * \param j++ j=itera; j<number;
         *
         */
        for(j=start->itera; j<(start->number)-(start->pecas); j++)
        {
            paux=(paux_hand+j)->hand_esquerda;
            paux2=(paux_hand+j)->hand_direita;
            (paux_hand+j)->hand_esquerda=(paux_hand+j+1)->hand_esquerda;
            (paux_hand+j)->hand_direita=(paux_hand+j+1)->hand_direita;

            (paux_hand+j+1)->hand_esquerda=paux;
            (paux_hand+j+1)->hand_direita=paux2;

        }
        return works;

    }
    /** \brief Permite que nunca repita peças.Conseguimos isto usando o ciclo for para verificar todas as peças do baralho.
     *
     * \param (paux2_tab+(count-i))->tab_esquerda == (paux2_tab+(count))->tab_esquerda) && ((paux2_tab+(count-i))->tab_direita== (paux2_tab+(count))->tab_direita)) || (((paux2_tab+(count-i))->tab_esquerda == (paux2_tab+(count))->tab_direita) && ((paux2_tab+(count-i))->tab_direita == (paux2_tab+(count))->tab_esquerda)))
     * \return else
     *
     */
    for(i=1; i<=start->count; i++)
    {
        if((((paux2_tab+(count-i))->tab_esquerda == (paux2_tab+(count))->tab_esquerda) && ((paux2_tab+(count-i))->tab_direita== (paux2_tab+(count))->tab_direita)) || (((paux2_tab+(count-i))->tab_esquerda == (paux2_tab+(count))->tab_direita) && ((paux2_tab+(count-i))->tab_direita == (paux2_tab+(count))->tab_esquerda)))  //&& matrix_tab[count-1][1]==matrix_tab[count][0]) )
        {
            return dworks;
        }
    }
    /** \brief Este permite rodar a primeira peca , pois a primeira peca não corresponde a nenhuma peca acima dela.
     *
     * \param (count-1==0 && ((paux2_tab+(count-1))->tab_esquerda == (paux2_tab+count)->tab_direita))
     * \return works
     *
     */
    if(count-1==0 && ((paux2_tab+(count-1))->tab_esquerda == (paux2_tab+count)->tab_direita))
    {
        switchp = (paux2_tab+(count-1))->tab_direita;
        (paux2_tab+(count-1))->tab_direita=(paux2_tab+(count-1))->tab_esquerda;
        (paux2_tab+(count-1))->tab_esquerda= switchp;

        switchp = (paux2_tab+(count))->tab_esquerda;
        (paux2_tab+(count))->tab_esquerda=(paux2_tab+(count))->tab_direita;
        (paux2_tab+(count))->tab_direita = switchp;
        for(j=start->itera; j<start->number-start->pecas; j++)
        {
            paux=(paux_hand+j)->hand_esquerda;
            paux2=(paux_hand+j)->hand_direita;
            (paux_hand+j)->hand_esquerda=(paux_hand+j+1)->hand_esquerda;
            (paux_hand+j)->hand_direita=(paux_hand+j+1)->hand_direita;
            (paux_hand+j+1)->hand_esquerda=paux;
            (paux_hand+j+1)->hand_direita=paux2;

        }

        return works;
    }
    /** \brief Esta função vai permitir rodar a peça anterior a ela, mas só se a primeira peça for 0 , para não compremeter o resto do jogo.
     *
     * \param (count-1==0 && (paux2_tab+(count-1))->tab_esquerda == (paux2_tab+(count))->tab_esquerda)
     * \return works
     *
     */
    else if(count-1==0 && (paux2_tab+(count-1))->tab_esquerda == (paux2_tab+(count))->tab_esquerda)
    {
        switchp = (paux2_tab+(count-1))->tab_direita;
        (paux2_tab+(count-1))->tab_direita=(paux2_tab+(count-1))->tab_esquerda;
        (paux2_tab+(count-1))->tab_esquerda=switchp;
        for(j=start->itera; j<start->number-start->pecas; j++)
        {
            paux=(paux_hand+j)->hand_esquerda;
            paux2=(paux_hand+j)->hand_direita;
            (paux_hand+j)->hand_esquerda=(paux_hand+j+1)->hand_esquerda;
            (paux_hand+j)->hand_direita=(paux_hand+j+1)->hand_direita;
            (paux_hand+j+1)->hand_esquerda=paux;
            (paux_hand+j+1)->hand_direita=paux2;

        }
        return works;
    }
    /** \brief Verifica se a peça encaixa normalmente
     *
     * \param ((paux2_tab+(count))->tab_esquerda==(paux2_tab+(count-1))->tab_direita)
     * \return works
     *
     */
    else if((paux2_tab+(count))->tab_esquerda==(paux2_tab+(count-1))->tab_direita)
    {
        for(j=start->itera; j<start->number-start->pecas; j++)
        {
            paux=(paux_hand+j)->hand_esquerda;
            paux2=(paux_hand+j)->hand_direita;
            (paux_hand+j)->hand_esquerda=(paux_hand+j+1)->hand_esquerda;
            (paux_hand+j)->hand_direita=(paux_hand+j+1)->hand_direita;
            (paux_hand+j+1)->hand_esquerda=paux;
            (paux_hand+j+1)->hand_direita=paux2;
        }
        return works;
    }
    /** \brief Este if permite verificar se , se rodarmos a peça ela pode encaixar na peça anterior
     *
     * \param ((paux2_tab+(count))->tab_direita==(paux2_tab+(count-1))->tab_direita)
     * \return works
     *
     */
    else if((paux2_tab+(count))->tab_direita==(paux2_tab+(count-1))->tab_direita)
    {
        switchp = (paux2_tab+(count))->tab_direita;
        (paux2_tab+(count))->tab_direita=(paux2_tab+(count))->tab_esquerda;
        (paux2_tab+(count))->tab_esquerda= switchp;
        for(j=start->itera; j<start->number-start->pecas; j++)
        {
            paux=(paux_hand+j)->hand_esquerda;
            paux2=(paux_hand+j)->hand_direita;
            (paux_hand+j)->hand_esquerda=(paux_hand+j+1)->hand_esquerda;
            (paux_hand+j)->hand_direita=(paux_hand+j+1)->hand_direita;
            (paux_hand+j+1)->hand_esquerda=paux;
            (paux_hand+j+1)->hand_direita=paux2;
        }

        return works;
    }
    /** \brief Permite inserir uma peca à cabeca do jogo ou seja substitui a primeira peca.
     *
     * \param count
     *
     */
    if((paux2_tab+(count))->tab_direita==paux2_tab->tab_esquerda)
    {
        paux3=(paux2_tab+count)->tab_esquerda;
        paux4=(paux2_tab+count)->tab_direita;
        for(j=count-1; j>=0; j--)
        {
            paux=(paux2_tab+j)->tab_esquerda;
            paux2=(paux2_tab+j)->tab_direita;
            (paux2_tab+j)->tab_esquerda=(paux2_tab+j+1)->tab_esquerda;
            (paux2_tab+j)->tab_direita=(paux2_tab+j+1)->tab_direita;
            (paux2_tab+j+1)->tab_esquerda=paux;
            (paux2_tab+j+1)->tab_esquerda=paux2;
        }
        paux2_tab->tab_esquerda=paux3;
        paux2_tab->tab_direita=paux4;

        paux3=(paux_hand+count)->hand_esquerda;
        paux4=(paux_hand+count)->hand_direita;
        for(j=count-1; j>=0; j--)
        {
            paux=(paux_hand+j)->hand_esquerda;
            paux2=(paux_hand+j)->hand_direita;
            (paux_hand+j)->hand_esquerda=(paux_hand+j+1)->hand_esquerda;
            (paux_hand+j)->hand_direita=(paux_hand+j+1)->hand_direita;
            (paux_hand+j+1)->hand_esquerda=paux;
            (paux_hand+j+1)->hand_direita=paux2;
        }
        paux_hand->hand_esquerda=paux3;
        paux_hand->hand_direita=paux4;
        return works;
    }
    /** \brief Esta peca faz a mesma accao que o if anterior mas roda a peca caso ela não encaixe na posicao original
     *
     * \param paux2_tab+count
     *
     */
    if((paux2_tab)->tab_esquerda==(paux2_tab+count)->tab_esquerda)
    {
        switchp =(paux2_tab+count)->tab_direita;
        (paux2_tab+count)->tab_direita=(paux2_tab+count)->tab_esquerda;
        (paux2_tab+count)->tab_esquerda=switchp;

        paux3=(paux2_tab+count)->tab_esquerda;
        paux4=(paux2_tab+count)->tab_direita;

        for(j=count-1; j>=0; j--)
        {
            paux=(paux2_tab+j)->tab_esquerda;
            paux2=(paux2_tab+j)->tab_direita;
            (paux2_tab+j)->tab_esquerda=(paux2_tab+j+1)->tab_esquerda;
            (paux2_tab+j)->tab_direita=(paux2_tab+j+1)->tab_direita;
            (paux2_tab+j+1)->tab_esquerda=paux;
            (paux2_tab+j+1)->tab_direita=paux2;
        }
        paux2_tab->tab_esquerda=paux3;
        paux2_tab->tab_direita=paux4;

        paux3=(paux_hand+count)->hand_esquerda;
        paux4=(paux_hand+count)->hand_direita;
        for(j=count-1; j>=0; j--)
        {
            paux=(paux_hand+j)->hand_esquerda;
            paux2=(paux_hand+j)->hand_direita;
            (paux_hand+j)->hand_esquerda=(paux_hand+j+1)->hand_esquerda;
            (paux_hand+j)->hand_direita=(paux_hand+j+1)->hand_direita;
            (paux_hand+j+1)->hand_esquerda=paux;
            (paux_hand+j+1)->hand_direita=paux2;
        }
        paux_hand->hand_esquerda=paux3;
        paux_hand->hand_direita=paux4;

        return works;
    }
    return dworks;
}
/** \brief Esta funcao destina-se a procurar sequencias de pecas para mais de 1 mao.Para mais de 1 mao não rodamos as pecas na mao visto que cria bastantes erros
 *
 * \param start GAME*
 * \return int
 * \bug por vezes o programa crasha ou encontra uma sequencia errada
 */
int verified_ns_struct(GAME * start)
{
    int switchp,i;
    TAB * paux2_tab=start->tab_game;

    int count= start->count;

    if(start->count == 0 ) /**< A primeira peça encaixa sempre. */
    {
        return works;

    }
    /** \brief Este for faz com que o programa verifique se existem pecas repetidas.
     *
     * \param i++ i=1; i<=start->count;
     *
     */
    for(i=1; i<=start->count; i++)
    {
        if((((paux2_tab+(count-i))->tab_esquerda == (paux2_tab+(count))->tab_esquerda) && ((paux2_tab+(count-i))->tab_direita== (paux2_tab+(count))->tab_direita)) || (((paux2_tab+(count-i))->tab_esquerda == (paux2_tab+(count))->tab_direita) && ((paux2_tab+(count-i))->tab_direita == (paux2_tab+(count))->tab_esquerda)))  //&& matrix_tab[count-1][1]==matrix_tab[count][0]) )
        {
            return dworks;
        }
    }
    if(count-1==0 && ((paux2_tab+(count-1))->tab_esquerda == (paux2_tab+count)->tab_direita))
    {
        switchp = (paux2_tab+(count-1))->tab_direita;
        (paux2_tab+(count-1))->tab_direita=(paux2_tab+(count-1))->tab_esquerda;
        (paux2_tab+(count-1))->tab_esquerda= switchp;

        switchp = (paux2_tab+(count))->tab_esquerda;
        (paux2_tab+(count))->tab_esquerda=(paux2_tab+(count))->tab_direita;
        (paux2_tab+(count))->tab_direita = switchp;

        return works;
    }
    else if(count-1==0 && (paux2_tab+(count-1))->tab_esquerda == (paux2_tab+(count))->tab_esquerda)
    {
        switchp = (paux2_tab+(count-1))->tab_direita;
        (paux2_tab+(count-1))->tab_direita=(paux2_tab+(count-1))->tab_esquerda;
        (paux2_tab+(count-1))->tab_esquerda=switchp;


        return works;
    }
    else if((paux2_tab+(count))->tab_esquerda==(paux2_tab+(count-1))->tab_direita)
    {
        return works;

    }
    else if((paux2_tab+(count))->tab_direita==(paux2_tab+(count-1))->tab_direita)
    {
        switchp = (paux2_tab+(count))->tab_direita;
        (paux2_tab+(count))->tab_direita=(paux2_tab+(count))->tab_esquerda;
        (paux2_tab+(count))->tab_esquerda= switchp;

        return works;
    }
    return dworks;
}
/** \brief Esta função aplica a recursividade para determinar uma sequencia de peças valida , se encontrar vai a procura demais sequencias, e ao mesmo tempo que faz isso vai guardando a maior sequencia possivel.
 *
 * \param start GAME*
 * \return int
 * \bug por vezes a funcao entra numa busca infnita por pecas e causa erros ou mesmo o crash do programa.
 */
int play_recursive_struct(GAME * start)
{
    char option;
    int v;
    int i;
    int test;
    HAND* paux= start->hand_game;
    TAB * paux2= start->tab_game;
    SAVER* paux4= start->saver;

    if(start->id >=start->nfac) /**< Vai verificar se tem mais sequencias válidas */
    {
        return start->count;
    }
    if(start->count ==start->number)
    {
        if(start->id==0)
        {
            printf("\t ____________\t\n");
            printf("\t|jogo gerado!|\t\n");
            printf("\t|____________|\t\n");
            print_deck_tab(*start);
        }
        /** \brief Guarda todas a sequencias finais validas. se não tiver espaço suficiente , é alocado mais .
         *
         * \param paux4->saver_esquerda==-1 && (start->id!=0 || start->id ==start->number
         *
         */
        if(paux4->saver_esquerda==-1 && (start->id!=0 || start->id ==start->number))
        {
            for(v=start->aux_aux; v<=start->aux_aux+start->number; v++)
            {
                (paux4+v)->saver_esquerda=(paux2+v)->tab_esquerda;
                (paux4+v)->saver_direita=(paux2+v)->tab_esquerda;
                start->saver_values++;
            }
            start->aux_aux=start->aux_aux+start->number;
        }
        else if(paux4->saver_esquerda!=-1)
        {
            printf(" _____________________________________\n");
            printf("|Armazenamento cheio ou invalido!     |\n");
            printf("|Deseja criar mais espaço para alocar?|\n");
            printf("|_____________________________________|\n");
            scanf("%c",&option);
            if(option=='s')
            {
                resizesaver(start);
                printf(" _____________________________________\n");
                printf("|Armazenamento alocado!               |\n");
                printf("|_____________________________________|\n");
            }
        }
        start->id=start->id+start->number;
        start->count=0;
        start->pecas=1;
    }
    for (i=0; i<=start->number-start->pecas; i++)
    {
        start->itera=i;
        (paux2+start->count)->tab_esquerda=(paux+i)->hand_esquerda;
        (paux2+start->count)->tab_direita=(paux+i)->hand_direita;
        if (verified_struct(start) == works)
        {
            start->pecas++;
            start->count++;
            start->vmax=vmax_func_struct(start);
            save_file(*start);
            test = play_recursive_struct(start);
            if(test != dworks)
            {
                return test;
            }
            start->pecas--;
            start->count--;
        }
    }
    return dworks;
}
/** \brief Funcao para jogada de mais de 1 mao de jogo
 *
 * \param start GAME*
 * \return int
 *
 */
int play_recursive_more_struct(GAME * start)
{
    int i;
    int test;
    HAND * paux=NULL;
    TAB * paux2=NULL;

    paux=start->hand_game;
    paux2=start->tab_game;

    /** \brief Verifica se o id é maior ou igual a nfac
     *
     * \param id >=nfac
     * \bug por vezes a funcao entra numa busca infnita por pecas e causa erros ou mesmo o crash do programa.
     */
    if(start->id>= start->nfac)
    {
        return start->count;
    }
    if (start->count > start->vmax)/**< Serve para armazenar a maior sequencia encontrada */
    {
        start->vmax=start->count;

        start->vmax=vmax_func_struct(start);
    }
    if(start->count == start->number)/**< Serve apresentar a sequencia que encontrou e fazer reset as variaveis. */
    {
        if(start->id==0)
        {
            printf("\t ______________\t\n");
            printf("\t|jogo gerado!  |\t\n");
            printf("\t|______________|\t\n");
            print_deck_tab(*start);
        }
        start->id=start->id+start->number;
        start->count=0;
        start->pecas=1;
        start->pecas2=0;
    }
    if(start->pecas2==start->number || start->count==start->number)/**< Acaba o programa se nao encontrar mais sequencias */
    {
        return start->count;
    }
    for(i=start->pecas2 ; i<start->number; i++)
    {
        (paux2+start->count)->tab_esquerda=(paux+i)->hand_esquerda;
        (paux2+start->count)->tab_direita=(paux+i)->hand_direita;
        /** \brief  Verifica se a peça é válida e retorna 1(works) se assim o for, senão retorna 0 (dowrks)
         *
         * \param start
         * \return if
         *
         */
        if (verified_ns_struct(start)== works)
        {
            if(start->count!=0 && (start->count%2!=0) && (start->n_player==2 || start->n_player==4))/**< Garante que a primeira mão joga sempre e so multiplos de dois podem jogar(segunda mao) */
            {
                start->pecas2=(((start->number)-(start->id_player))/start->pecas2);
            }
            else if(start->count !=0 && (start->count%3!=0)&& (start->n_player==3 || start->n_player==4))/**< Garante que a primeira mão joga sempre e so multiplos de tres podem jogar(terceira mao) */
            {
                start->pecas2=(((start->number)-(start->id_player))/start->pecas2);
            }
            else
            {
                start->pecas2=((start->pecas2)+((start->number)-(start->id_player)));
            }
            if (start->count > start->vmax)
            {
                start->vmax=start->count;
                start->vmax=vmax_func_struct(start);
            }
            start->pecas++;
            start->count++;
            save_file(*start);/**< Guarda todas as jogadas validas para o ficheiro */
            test = play_recursive_more_struct(start);
            if(test != dworks)
            {
                return test;
            }
            start->pecas--;
            start->count--;

        }
    }
    return dworks;
}
