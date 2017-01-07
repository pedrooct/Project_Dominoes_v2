#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#define works 1 /**< Se a verificacao devolver verdadeira devolve work 1 */
#define dworks 0 /**< Se a verificacao devolver falso devolve dworks 0 */
#define MAX100 100

/** \brief Esta estrutura guarda todas as peças do baralho
 */
typedef struct peca
{
    int pinta_esquerda;
    int pinta_direita;

}PECA;

/** \brief Estrutura para armazenar as mãos do jogador
 */
typedef struct hand
{
    int hand_direita;
    int hand_esquerda;
}HAND;
/** \brief Estrutura para guardar a maior sequencia possivel
 */
typedef struct hand_vmax
{
    int vhand_direita;
    int vhand_esquerda;

}HAND_VMAX;
/** \brief Estrutura para tabuleiro de jogo
 */
typedef struct tab
{
    int tab_direita;
    int tab_esquerda;

}TAB;
/** \brief Estrutura que vai guardar todas as sequencias possiveis
 */
typedef struct saver
{
    int saver_direita;
    int saver_esquerda;


}SAVER;

/** \brief Estrutura principal com todas as variaveis necessarias para o jogo.
 */
typedef struct game
{
    int nfac; /**< Guardar factorial */
    int count; /**< posicao para jogar no tabuleiro */
    int number; /**< Numero total de pecas do utilizador */
    int pecas; /**< variavel auxiliar que permite descobrir o de pecas que ainda pode jogar  */
    int pecas2;/**< Variavel usada para descobrir a mao */
    int vmax;/**< Valor maximo de pecas validas  */
    int vmax_checker;
    int pecas_disponivel;/**< pecas disponiveis ou ainda disponiveis para jogo */
    int id_player;
    int n_player; /**< Armazena o numero de jogadores que vao entrar no jogo */
    int id;/**< Varivael auxiliar que ajuda a chegar ao factorial da peca do jogo */
    int itera;/**< Variavel auxiliar que armazena o valor de I para assim ser mais facil para rodar as pecas na mao */
    int lines_pecas;
    int aux_aux;
    int find_sequence; /**< serve para guardar a posicao onde encontrou a sequencia no ficheiro */
    int matrix_aux[255][2];
    int saver_values; /**< Guarda o numero de pecas guardadas na estrutura saver */
    PECA * pecas_game;/**< Apontador para a estrutura PECA */
    HAND * hand_game;/**< Apontador para a estrutura HAND */
    TAB * tab_game; /**< Apontador para a estrutura TAB */
    HAND_VMAX* vmax_game; /**< Apontador para a estrutura HAND_VAMX  */
    SAVER * saver;/**< Apontador para a estrutura SAVER  */


}GAME;
// estruturas indeviduais ...

void inicializer(GAME * start);
void print_deck_hand(GAME  start);
void print_deck_tab(GAME start);
void print_deck_vmax(GAME start);
int generate_fac_struct(GAME * start);
void generate_deck_sturct(GAME * start);
int generate_hand_struct(GAME * start);
int valid_hand_struct(GAME * start);
int verified_struct(GAME * start);
int verified_ns_struct(GAME * start);
int resizesaver(GAME * start);
void save_file(GAME start);
int find_sequence_struct(GAME * start);
int play_recursive_struct(GAME * start);
int play_recursive_more_struct(GAME * start);
int vmax_func_struct(GAME *start);
int vmax_checker_func_struct(GAME * start);




int generate_fac(int number,int nfac);
int generate_deck(int matrix_main[][2], int lines, int columns);
void print_deck(int matrix_main[][2], int lines, int columns);
int uniforme(int rand_min_val, int rand_max_val);
int find_sequence();
int ordena_file();
void save_file_part1(int matrix_tab[][2],int count);
int generate_hand(int matrix_main[][2],int matrix_player[][2],int number, int pecas_disponiveis);
int valid_hand(int matrix_main[][2],int matrix_player[][2],int number);
int vmax_checker_func(int matrix_tab[][2],int matrix_player[][2],int matrix_vmax[][2],int number);
int vmax_func(int matrix_tab[][2],int matrix_vmax[][2],int count,int vmax);
int verified(int matrix_tab[][2], int matrix_player [][2],int matrix_vmax[][2],int number,int count,int vmax,int nfac,int pecas,int itera,int id);
int verified_ns(int matrix_tab[][2], int matrix_player [][2],int matrix_vmax[][2],int number,int count,int vmax,int nfac,int pecas,int pecas2,int itera,int id,int player);
int play_recursive(int matrix_tab[][2],int matrix_player[][2],int matrix_aux[][2],int matrix_vmax[][2],int number,int count,int vmax,int nfac,int pecas,int itera,int id,int aux_aux);
int play_recursive_more(int matrix_tab[][2],int matrix_player[][2],int matrix_aux[][2],int matrix_vmax[][2],int number,int count,int vmax,int nfac,int pecas,int pecas2,int itera,int id,int id_player,int n_player);
void ordena_hand(int matrix_player[][2],int number);

#endif // DATA_H_INCLUDED
