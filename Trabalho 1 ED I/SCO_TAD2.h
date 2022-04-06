								//          SCC0223 - Estrutura de Dados 1          //
								//      Trabalho 1: Sistema de Compra Online (SCO)   //
		//  Alunos: Anderson Lavinscky, n°USP 9045195; Joao Bienotti, n°USP 11218452; Stefane Oliveira, n°USP 10829970.  //


			//  Versao: Dinamica-Encadeada  //


//  Implementacao do codigo  //




///   Funcoes do Menu   ///

// Funcao para imprimir o menu na tela :
void menuOpcoes();


//Funcao que imprime explicacoes de como usar todas as opcoes do leilao:
void ajuda(void);



///  TAD PILHA  ///

//  Variaveis  //
// Declaracao da variavel de Pilha:
typedef float elem_p;


// Declaracao da struct "No":
typedef struct noP {
    elem_p info;
    struct noP *prox;
} NoP;


// Declaracao de struct "Pilha dinamica-encadeada (PDEnc)":
typedef struct {
    NoP *topo;
} PDEnc;



//  Funcoes  //
// Funcao de criacao de pilha:
PDEnc* Criar_PDEnc (void);


// Funcao de destruicao2 da pilha:
void DestroirPenc2 (PDEnc *PE);


// Funcao de verificacao se pilha encontra-se vazia:
int Estavazia_PDEnc (PDEnc *PE);


// Funcao de insercao de elementos na pilha:
void Insere_PDEnc (PDEnc *PE, elem_p *X, int *erro);


// Funcao que remove elemento na pilha:
void Remove_PDEnc (PDEnc *PE, elem_p *X, int *erro);



///  TAD FILA  ///

//  Variaveis  //
// Declaracao da variavel de Fila:
typedef char elem_f;


// Declaracao da struct "No":
typedef struct noF {
    elem_f *info;
    struct noF *prox;
} NoF;


// Declaracao da struct "fila dinamica-encadeada (FDEnc)":
typedef struct {
    elem_f itens;
    NoF *inicio;
    NoF *fim;
    int total;
} FDEnc;


// Funcao que cria a fila:
FDEnc* Criar_FDEnc (void);


//Funcao que verifica se a fila esta vazia
int fila_vazia(FDEnc *FE);


// Funcao de procura de elemento na fila:
int Proc_FDEnc (FDEnc *FE, elem_f *X);


// Funcao de destruicao da fila:
void Destroir_FDEnc (FDEnc *FE);


// Funcao de insercao de elemento na fila:
void Insere_FDEnc (FDEnc *FE, elem_f *X, int *erro);


// Funcao que remove um elemento da fila:
elem_f* Rem_FDEnc (FDEnc *FE, int *erro);


// Funcao que inverte uma fila:
void invertFila(FDEnc *FE);



///  TAD LISTA  ///

//  Variaveis  //
// Declaracao da variavel de Lista:
typedef char elem_l;


// Declaracao da struct "No":
typedef struct noL {
    elem_l *info;
    struct noL *prox;
    PDEnc *lances;
    FDEnc *nomes;
} NoL;


// Declaracao de struct "Lista dinamica-encadeada (LDEnc)":
typedef struct {
    NoL *inicio;
    NoL *fim;
    int total;
} LDEnc;


// Funcao de criacao de lista:
LDEnc* criarL(void);


// Funcao de destruicao da lista:
void destroirL(LDEnc *L_prod);


// Funcao de inserir produto na lista:
void inserir_produto(LDEnc *L_prod, elem_l *objeto, int *erro);


// Funcao que remove um elemento da lista
void Remover_LDEnc(LDEnc *L_prod, elem_f *X, int *erro);


// Funcao que lista os produtos com lances:
void listar_produtos(LDEnc *L_prod, int *erro);


// Funcao que insere um lance em um produto:
void inserir_lance(LDEnc *L_prod, char objeto[], float lance, char nome[], int *erro);


// Funcao que recomenda a uma pessoa produtos para dar lance:
void recomendacao(LDEnc *L_prod, char pessoa[]);


// Funcao que acha o ganhador de um produto:
void ganhador(LDEnc *L_prod, elem_l *produto, char *gan, int *erro);


// Funcao que encerra o leilao e acha os compradores dos produtos:
void encerrarLeilao(LDEnc *L_prod);


//Funcao que imprime explicacoes de como usar todas as opcoes do leilao:
void ajuda(void);