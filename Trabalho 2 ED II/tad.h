#define MaxNumVertices 100
#define sem_aresta 0
#define peso_infinito 99999999

//registro que contem todos os dados do usuario
typedef struct usuarios{
    char nome[30],cidade[30],filme[30],time[20],cor[20];
    int idade;
} usuario;

typedef int elem;

//registro que contem todas as amizades de uma pessoa, ou seja, todas as arestas conectadas
typedef struct no_aresta{
	int v; //eh o numero associado ao vertice do amigo
	elem peso; //eh o numero de amigos
	struct no_aresta *prox;
} no_aresta;

//registro que contem a lista de pessoas que mandaram solicitacoes de amizade
typedef struct amigos{
    int amigo; //eh o numero associado ao vertice da pessoa que mandou solicitacao
    struct amigos *prox;
}solicitacoes;

//registro que contem cada vertice do grafo, ou seja, cada usuario
typedef struct{
	no_aresta *inicio, *fim; //lista de amigos do usuario
    usuario pessoa; //dados do usuario
    solicitacoes *comeco; //solicitacoes do usuario
} no_vertice;

//registro do grafo
typedef struct grafo{
	no_vertice Adj[MaxNumVertices];
	int NumVertices; //numero total de usuarios
} Grafo;

//---------FUNCOES----------//
Grafo* ler_arquivo(int *erro);

int log_in (Grafo *G, char *nome);

void fazer_convite(Grafo *G, int v);

void ver_solicitacoes(Grafo *G, int v);

void sugestoes(Grafo *G, int v);

void amigos_nao_verdadeiros(Grafo *G, int v);

void namorade_ideal(Grafo *G, int v);

void lista_amigos(Grafo *G, int v);

void liberar_memoria(Grafo *G);