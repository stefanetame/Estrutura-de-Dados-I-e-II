#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* LISTA */
typedef struct bloco_lista{
    char *titulo; //variavel que guarda o titulo do filme
    struct bloco_lista *prox; //ponteiro para o proximo
}NOL;

typedef struct{
    NOL *inicio, *fim; //ponteiros para os nohs da lista
}LISTA;

/* ARVORE */
typedef struct bloco_arvore{
	int chave; //variavel que guarda o n usp do aluno
    char *aluno; //variavel que guarda o nome do aluno
    LISTA *filmes; //lista que guarda a lista de filmes prediletos do aluno respectivo do noh
	struct bloco_arvore *esq, *dir; //ponteiro pra esquerda e direita
}NO;

typedef struct arv{
	NO *raiz; //ponteiro para a raiz da arvore
}ARV;

ARV* criar(void);

int inserir(ARV *A, int ch, char *nome, char **film, int nf); //1

int listar_alunos(ARV *A); //2

int procura_aluno(ARV *A, int nusp); //3

void listar_filmes(ARV *A); //4

int buscar_filme(ARV *A, char *titul); //5

void indicar_pessoa_mais(ARV *A, int nusp); //6

void indicar_pessoa_menos(ARV *A, int nusp); //7

void criar_arquivo(ARV *A); //8

void dados_sistema(ARV *A); //9

int retirar_aluno(ARV *A, int nusp); //10

int inserir_filme(ARV *A, int nusp, char *titul); //11

int remover_filme(ARV *A, int nusp, char *titul); //12

void destroi(ARV *A); 