#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define B 5477 //tamanho maximo da tabela hash sequencial e estatica 

//registro que guarda todas as informacoes de um determinado dia de um pais 
typedef struct elem{
    char provincia[50];
    char pais[50];
    char latitude[50];
    char longitude[50];
    char data[50];
    char confirmados[50];
    char mortes[50];
    char recuperados[50];
    struct elem *prox; //usado na TABELA T
} elem;

//registro da lista
typedef struct{
    int quantidade;
    int total;
    elem *itens;
} LISTA;

//registro da tabela
typedef struct{
    int pos;
    elem *inicio;
}TABELA;

typedef struct noP{
  char pais[50];
  int morte1, morte2, dif;
  struct noP *prox;
}noP;

typedef struct {
  noP *inicio, *fim;
  int total;
}ListaP;

//Funcoes da lista
LISTA* criar();

int ler_arquivo(LISTA *L);

double ordenar_simples(LISTA *L);

double ordenar_avancado(LISTA *L);

int imprimir(LISTA *L, double TEMPO);

void inicializar(TABELA *T);

int hash(TABELA *T, LISTA *L);

void buscar(TABELA *T);

ListaP* criaP();

void inserirPF(ListaP *P, noP *x);

void maior_mortes(LISTA *L, char *data1, char *data2);

void destruir(LISTA *L);