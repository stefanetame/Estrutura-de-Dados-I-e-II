								//          SCC0223 - Estrutura de Dados 1          //
								//      Trabalho 1: Sistema de Compra Online (SCO)   //
		//  Alunos: Anderson Lavinscky, n°USP 9045195; Joao Bienotti, n°USP 11218452; Stefane Oliveira, n°USP 10829970.  //


			//  Versao: Dinamica-Encadeada  //


//  Implementacao do codigo  //



//Bibliotecas utilizadass neste trabalho:
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "SCO_TAD2.h"



//Declaracao de variavel:
#define TAM 20



///   Funcoes do Menu   ///

// Funcao para imprimir o menu na tela :
void menuOpcoes() {

	printf("\n");
	printf("#####			Sistema de Compra Online (SCO)			#####\n");
	printf("   Operacoes disponiveis no SCO:  \n");
	printf("   1) Cadastrar um produto \n");
	printf("   2) Remover um produto \n");
	printf("   3) Efetuar um lance \n");
	printf("   4) Listar produtos e lances \n");
	printf("   5) Indicar outros produtos para lances \n");
	printf("   6) Encerrar leilao \n");
	printf("   7) Ajuda \n");
	printf("   8) Sair \n");

	return;
}


//Funcao que imprime explicacoes de como usar todas as opcoes do leilao:
void ajuda(void) {

	printf("Opcao 1) Cadastrar um produto: \n");
	printf("        O usuario cadastrara um produto por vez especificando alguma(s) caracteristica(s) do mesmo, podendo realizar novamente outro cadastro. A cada cadastro a lista de produtos e atualizada. \n\n");
	printf("Opcao 2) Remover um produto: \n");
	printf("	    O usuario removera um produto especifico por vez constado na lista de produtos, podendo remover outro produto novamente. \n\n");
	printf("Opcao 3) Efetuar um lance:  \n");
	printf("        O usuario efetuara um lance por vez em um produto, podendo este efetivar novo lance no mesmo produto ou em outro de sua escolha. \n\n");
	printf("Opcao 4) Listar produtos e lances: \n");
	printf("        Sera(o) exibido(s) o(s) produto(s) disponivel(eis) em leilao seguido do(s) lance(s) e o(s) cliente(s) que o(s) efetivou(ram).  \n");
	printf("Opcao 5) Indicar outros produtos para lances: \n");
	printf("        O usuario entrara com seu nome e lhe sera(o) apresentado(s) outro(s) produto(s) disponivel(is) a lance(s). \n\n");
	printf("Opcao 6) Encerrar leilao: \n");
	printf("	    Verifica e imprime cada produto em leilao com o lance efetivado vencedor e o seu respectivo ganhador. Os demais produtos que nao receberam lance(s) tambem sao impressos, mostrando um panorama final do Sistema de Compras Online (SCO). \n\n");
	printf("Opcao 7) Ajuda: \n");
	printf("        Imprime na tela esta breve explicacao sobre o Sistema de Compras Online (SCO). \n\n");
	printf("Opcao 8) Sair: \n");
	printf("        Saida completa do Sistema de Compras Online (SCO). \n\n");

	return;
}



///  Funcoes da TAD PILHA  ///

// Funcao de criacao de pilha:
PDEnc* Criar_PDEnc(void) {
    PDEnc *PE = (PDEnc*)malloc(sizeof(PDEnc)); //Alocacao da pilha

    if (PE == NULL) { //Verifica a alocacao
        return (0);
    }
    else {
        PE->topo = NULL;
        return (PE); //Retorna a pilha alocada na memoria
    }
}


// Funcao de destruicao2 da pilha:
void DestroirPDEnc2(PDEnc *PE) {
    NoP *aux = PE->topo;

    //Dentro do while: percorre todos os nos da pilha para desalocar da memoria
    while (aux != NULL) {
        PE->topo = PE->topo->prox;    
        free(aux);
        aux = PE->topo;     
    }
    
	//Por fim, desaloca a pilha
    free(PE);

    return;
}


// Funcao de verificacao se pilha encontra-se vazia:
int Estavazia_PDEnc(PDEnc *PE) {
    if (PE->topo == NULL) { //Retorna se a pilha esta vazia
        return (1);
    }
    else {
        return (0);
    }
}


// Funcao de insercao de elementos na pilha:
void Insere_PDEnc(PDEnc *PE, elem_p *X, int *erro) {
    NoP *aux = (NoP *)malloc(sizeof(NoP)); //Aloca um noh para a pilha

    if (aux == NULL) { //Verifica a alocacao
        *erro = 1;         
    }
    else {
        aux->info = *X; //Insere o elemento desejado no noh alocado
        aux->prox = PE->topo;
        PE->topo = aux; //Insere elemento no topo da pilha
        *erro = 0;
    }

    return;
}


// Funcao que remove elemento na pilha:
void Remove_PDEnc(PDEnc *PE, elem_p *X, int *erro) {
    NoP *aux;
    int teste = 0;

    if (Estavazia_PDEnc(PE)) {		//Verifica se a pilha esta vazia antes de retirar algum elemento
        *erro = !teste;
    }
    else {
        *erro = teste;
        *X = PE->topo->info;			//Salva o elemento do topo em X 
        aux = PE->topo; 
        PE->topo = PE->topo->prox;		//Aponta o novo topo para o seguinte elemento
        free(aux);						//Desaloca o no da pilha que continha o topo a ser retirado
    }
    
	return;
}



///  Funcoes da TAD FILA  ///

// Funcao que cria a fila:
FDEnc* Criar_FDEnc (void) {
    FDEnc *FE = (FDEnc*)malloc(sizeof(FDEnc)); //Alocacao da fila

    if (FE == NULL) {   //Teste de alocacao
        return (0);
    }
    else{
        FE->inicio = NULL;
        FE->fim = NULL;
        FE->total = 0; //Inicializa o total da fila

        return (FE); //Retorna a fila alocada na memoria
    }
}


//Funcao que verifica se a fila esta vazia
int fila_vazia (FDEnc *FE) {

    if(FE->inicio == NULL){ //Retorna se a fila esta vazia
        return (1); 
    }
    else{
        return (0);
    }
}


// Funcao de procura de elemento na fila:
int Proc_FDEnc (FDEnc *FE, elem_f *X) {
    NoF *fe = FE->inicio;

    while ((fe != NULL) && (strcmp(fe->info, X)) != 0) {
        fe = fe->prox; //Percorre todo no da fila a fim de achar o elemento
    }

    if (fe != NULL) { //Retorna se encontrou o elemento procurado na fila
        return (1);
    }
    else {
		return (0);
    }
}


// Funcao de destruicao da fila:
void Destroir_FDEnc (FDEnc *FE) {
    NoF *fe = FE->inicio;

    //Dentro do while: percorre todos os nos da fila para desalocar da memoria
    while (fe != NULL) {
        FE->inicio = FE->inicio->prox;
        free(fe);
        fe = FE->inicio;
    }

    //Por fim, desaloca a fila
    free(FE);

    return;
}


// Funcao de insercao de elemento na fila:
void Insere_FDEnc (FDEnc *FE, elem_f *X, int *erro) {
    NoF *fe = (NoF *)malloc(sizeof(NoF));		//Alocacao de um noh para a fila

    if (fe == NULL) {    //Teste de alocacao
        *erro = 1;
    }
    else {
        *erro = 0;
        fe->prox = NULL;
        fe->info = (elem_f*)malloc(sizeof(char)*20);	//Alocacao de uma cadeia de char para o noh

        if(FE->inicio == NULL) {	 //Se a fila estiver vazia:
            if (fe == NULL) {		 //Verifica se ponteiro aponta para NULL
                *erro = 1;
            }
            else {
                strcpy(fe->info, X);	 //Atribui no noh o elemento a ser inserido
                FE->inicio = fe;		 //O inicio aponta para este noh
            }
        }
        else {					  //Se a fila nao estives vazia
            if (fe == NULL) {     //Verifica se ponteiro aponta para NULL
                *erro = 1;
            }
            else {
                strcpy(fe->info, X);	//Atribui no noh o elemento a ser inserido
                FE->fim->prox = fe;		//O ultimo elemento da fila aponta para o noh inserido
            }
        }

        FE->fim = fe;		//O fim aponta para o novo noh
        FE->total++;

        return;
    }
}


// Funcao que remove um elemento da fila:
elem_f* Rem_FDEnc(FDEnc *FE, int *erro) {
    NoF *p;
    elem_f *X;
    
    if(fila_vazia(FE)) {		 //Verifica se a fila esta vazia
        *erro = 1;
    }
    else {
        X = FE->inicio->info;	//Salva o elemento do inicio em X
        p = FE->inicio;
        FE->inicio = p->prox;	//O inicio aponta para o seguinte elemento do inicial
        free(p);				//Desaloca o noh da fila que continha o elemento inicial
        *erro = 0;
    }

    FE->total--;

    return(X);
}


// Funcao que inverte os elementos da Fila:
void invertFila(FDEnc *FE) {
    //Declaracao de variavel:
    elem_f *X;
    elem_f **v;
    int erro;
    int i;
    int aux = FE->total;

    v = (elem_f**)malloc(sizeof(elem_f)*FE->total);

    for(i=0; i < FE->total; i++){
        v[i] = (elem_f*)malloc(sizeof(elem_f)*50);	//Aloca todos espacos do vetor de char
    }
    
    X = (elem_f*)malloc(sizeof(elem_f)*50);

    for (i = 0; i < aux; i++) {
        X = Rem_FDEnc(FE, &erro);               //Removendo elemento da Fila
        strcpy(v[i], X);                //Adicionando o elemento em um vetor auxiliar
    }

    for (i = aux - 1; i > -1; i--) { //Contador i realiza a inversao
        strcpy(X, v[i]);                //Removendo o elemento do vetor auxiliar de forma invertida
        Insere_FDEnc(FE, X, &erro);             //Adicionando o elemento a Fila
    }

    return;
}



///  Funcoes da TAD LISTA  ///

// Funcao de criacao de lista:
LDEnc* criarL(void) {
    LDEnc *L_prod = (LDEnc*)malloc(sizeof(LDEnc)); //Alocacao da lista

    if (L_prod == NULL) { //Verifica a alocacao
        return (0);
    }

    L_prod->inicio = NULL;
    L_prod->fim = NULL;
    L_prod->total = 0;		//Inicializa o total da lista

    return (L_prod);		//Retorna a lista alocada na memoria
}


// Funcao de destruicao da lista:
void destruirL(LDEnc *L_prod) {
    NoL *le = L_prod->inicio;

    //Dentro do while: percorre toda a lista, noh por noh, para desalocar os nohs
    //Desaloca a pilha e a fila associada ao noh. E depois desaloca o noh

    while (le != NULL) {
        L_prod->inicio = L_prod->inicio->prox;
        Destroir_FDEnc (le->nomes);
        DestroirPDEnc2 (le->lances);
        free(le);
        le = L_prod->inicio;
    }

    //Por fim, desaloca a lista
    free(L_prod);

    return;
}


// Funcao de inserir produto na lista:
void inserir_produto(LDEnc *L_prod, elem_f *objeto, int *erro) {
    NoL *ant, *at, *p;

    p = (NoL*)malloc(sizeof(NoL)); //Alocacao de um noh da lista

    if(p == NULL){	//Verifica a alocacao 
        *erro = 1;
    }
    else{
        *erro = 0;
        p->info = (char*)malloc(sizeof(50));	//Aloca uma cadeia de char para o noh
        strcpy(p->info, objeto);				//Atribui neste noh alocado o produto a ser inserido

        if ((L_prod->inicio == NULL) || strcmp(L_prod->inicio->info, objeto) > 0) {
            //Se a lista estiver vazia ou
            //Se o produto a ser inserido eh anterior na ordem alfabetica que o elemento inicial da lista
            p->prox = L_prod->inicio; //Insere o noh no inicio
            L_prod->inicio = p;
        }
        else if (strcmp(L_prod->inicio->info, objeto) == 0) {
            //Se o produto a ser inserido eh igual ao produto inicial, retorna erro
            *erro = 2;            
        }
        else { 
            //Se o produto a ser inserido eh posterior na ordem alfabetica que o elemento inicial da lista
            ant = NULL; //ant = anterior
            at = L_prod->inicio; //at = atual
            
			//Dentro do while: percorre a lista ate encontrar os nohs anterior e posterior
            //Para inserir o novo noh entre eles   
            while (at != NULL && strcmp(at->info, objeto) <= 0) {
                if (strcmp(at->info, objeto) == 0) {
                    //Se o produto a ser inserido eh igual ao atual, retorna erro
                    *erro = 2;
                }
                ant = at;
                at = at->prox;
            }

            //Insere o novo noh no meio dos nohs anterior e posterior
            p->prox = at;
            ant->prox = p;
        }

        if (*erro==0) {
            //Se houve maneira de inserir o novo noh
            //Aloca a pilha e a fila associada a este noh
            p->lances = Criar_PDEnc();
            p->nomes = Criar_FDEnc();
            L_prod->total++;
        }
    }

    return;
}


// Funcao que remove um elemento da lista
void Remover_LDEnc (LDEnc *L_prod, elem_f *X, int *erro) {
	NoL* atual;
	NoL *ant;
    int teste = 0;

    atual = L_prod->inicio;

    while ((atual != NULL) && (!teste)) {
        if (strcmp(atual->info, X) != 0) {
            //Percorre a lista ate encontrar o noh do produto a ser removido
            ant = atual;
            atual = atual->prox;
        }
        else {
            //Quando acha o noh do produto a ser removido, entra nesse else
            if (atual == L_prod->inicio) {
                //Se o produto a ser removido esta no inicio da fila
                L_prod->inicio = L_prod->inicio->prox; //O produto inicial passa a ser o seguinte
                if (L_prod->inicio == NULL) {
                    L_prod->fim = NULL;//Se havia apenas um noh na lista, inicio e fim aponta pra nulo
                }
            }
            else if (atual == L_prod->fim) {
                //Se o produto a ser removido esta no fim da fila
                L_prod->fim = ant; //O produto inicial passa a ser o anterior
                L_prod->fim->prox = NULL;
            }
            else {
                //Se o produto a ser removido esta no meio da fila
                //O anterior aponta para o seguinte do noh a ser removido
                ant->prox = atual->prox;
            }
            //Desaloca a pilha e a fila associada aquele produto e desaloca o noh do produto
            Destroir_FDEnc (atual->nomes);
            DestroirPDEnc2 (atual->lances);
            free(atual);
            teste = 1;
        }
    }

    if (atual == NULL) {
        //Se nao foi encontrado o produro para remover, retorna erro
        *erro = 1;
    }

    *erro = !teste;
    L_prod->total--;

    return;
}


// Funcao que lista os produtos com lances:
void listar_produtos(LDEnc *L_prod, int *erro) {
    int i = 1;
    elem_p X1;
    elem_f *X2;
    NoL *aux = L_prod->inicio;
    PDEnc *p_aux;

    p_aux = Criar_PDEnc();	//Cria uma pilha auxiliar

    if (X2 == NULL) {		//Teste de alocacao
        *erro = 1;
    }

    *erro = 0;
    if (aux == NULL) {		//Verifica se a lista esta vazia
        *erro = 1;
    }
    else {
        //Dentro do while: percorre todos nohs da lista para imprimir os produtos e seus respectivos lances
        while (aux != NULL) {
            //Inverte a fila para listar os nomes na ordem do lance maior para o lance menor
            invertFila(aux->nomes);
            printf("Produto %d: %s\n", i, aux->info);
            i++;
            //Dentro do while: remove toda a pilha ate que nao haja mais elementos
            while (aux->lances->topo != NULL) {
                Remove_PDEnc (aux->lances, &X1, erro); //Remove o elemento da pilha (lances)        
                X2 = Rem_FDEnc(aux->nomes, erro); //Remove o elemento da fila (nomes)
                printf("%s deu lance de %.2f\n", X2, X1); //Imprimi o nome da pessoa e seu respectivo lance
                Insere_FDEnc(aux->nomes, X2, erro); //Insere novamente na fila
                //Devido ao F.I.F.O, nao acarreta em desordenacao na fila
                Insere_PDEnc(p_aux, &X1, erro);//Insere o elemento da pilha na pilha auxiliar
                //Isso implica em que a pilha auxiliar eh a pilha invertida
            }

            //Dentro do while: remove toda a pillha auxiliar ate que nao haja mais elementos
            while (p_aux->topo != NULL) {
                Remove_PDEnc (p_aux, &X1, erro);//Remove o elemento da pilha auxiliar
                Insere_PDEnc(aux->lances, &X1, erro);//E insere na pilha 
                //Voltando a pilha inicial na mesma ordem
            }
            //Inverte a fila de novo para voltar ao estado inicial
            invertFila(aux->nomes);
            aux = aux->prox;
        }
    }
    //Desaloca a pilha auxiliar
    DestroirPDEnc2(p_aux);
}


// Funcao que insere um lance em um produto:
void inserir_lance(LDEnc *L_prod, char objeto[], float lance, char nome[], int *erro) {
    int i = 0;
    NoL *p;

    p = L_prod->inicio;
    //Dentro do while: percorre a lista ate encontrar o noh do produto a inserir o lance
    while (strcmp(p->info, objeto) != 0) {
        p = p->prox;
        i++; //Contador auxiliar
    }
    if (i >= L_prod->total) {
        //Se nao foi encontrado o produro para inserir lance, retorna erro
        *erro = 3;
    }
    else if ( Estavazia_PDEnc(p->lances) || (p->lances->topo->info <= lance)) {
        //Se a pilha estiver vazia OU se o lance for maior ou igual aos lances dados anteriormente:
        //Insere o nome da pessoa e seu respectivo lance
        Insere_FDEnc(p->nomes, nome, erro);
        Insere_PDEnc(p->lances, &lance, erro);
    }
    else {
        //Caso contrario, o lance eh menor que os lances dados anteriomente, retorna erro
        *erro = 2;
    }
}


// Funcao que recomenda a uma pessoa produtos para dar lance:
void recomendacao(LDEnc *L_prod, char pessoa[]) {
    NoL *p;
    int i;

    printf("para %s: nao gostaria de dar um lance pela\n", pessoa);

    p = L_prod->inicio;
    //Dentro do while: percorre os nohs da lista a fim de encontrar produtos que a pessoa nao tenha dado lance ainda
    while (p != NULL) {
        i = Proc_FDEnc(p->nomes, pessoa);
        if(i == 0){ //Se o nome da pessoa nao tiver na fila associada ao noh do produto
            printf("%s ", p->info); //Entao, imprime o nome do produto
        }
        p = p->prox;
    }

    printf("?\n");
}


// Funcao que acha o ganhador de um produto:
void ganhador(LDEnc *L_prod, elem_l *produto, char *gan, int *erro) {
    NoL *p;
    NoP *aux;
    elem_f *X;
	float maior;
	float X1;
	int count = 0;
	int total;

    X = (elem_f*)malloc(sizeof(elem_f)*50); //Aloca uma cadeia de char para a variavel X
    p = L_prod->inicio;

    //Dentro do while: percorre os nohs da lista ate encontrar o produto desejado
    while (p != NULL && strcmp(p->info, produto) != 0) {
        p = p->prox;
    }
    if (p==NULL) { //Verifica se existe nohs na lista
        *erro = 1;
    }
    else {
        if (p->lances->topo != NULL) { //Verifica se existe elemento na pilha associada ao noh da lista
            maior = p->lances->topo->info; //maior lance dado
            //A inversao da fila ocorre pelo seguinte:
            //Ao inverter a fila, quando retira um elemento da pilha e um elemento da fila
            //Ambos sao associados ao outro, ou seja, 
            //O lance que sair da pilha refere-se a pessoa que sair da lista
            invertFila(p->nomes);

            while(p->lances->topo->info == maior){		//Enquanto o lance do topo da fila for igual ao maior
                Remove_PDEnc (p->lances, &X1, erro);	//Remove o elemento do topo da pilha
                X = Rem_FDEnc(p->nomes, erro);			//Remove o elemento do inicio da fila
                if(p->lances->topo == NULL){ 
                    //Se apos remover o elemento do topo da pilha e esta ficar vazia
                    break; //Encerra o while
                }
            }
            
			//Retorna na variavel gan a primeira pessoa que deu o maior lance, guardada na variavel X
            strcpy (gan, X);
        }
    }
}


// Funcao que encerra o leilao e acha os compradores dos produtos:
void encerrarLeilao(LDEnc* L_prod)	{    //só coloquei o comando "free" da lista
    NoL *aux;
    elem_f *pessoa;
    int erro = 0;

    aux = L_prod->inicio;

    printf("Leilao Encerrado\n");
    //Dentro do while: percorre todos os nohs da lista para achar seu ganhador e encerrar
    while (aux != NULL)	{
        if ((aux->lances != NULL && !Estavazia_PDEnc(aux->lances)))	{
            //Se a pilha nao estiver vazia e ela existir:
            //Aloca uma cadeia de char para a variavel pessoa
            pessoa = (elem_f*)malloc(sizeof(elem_f)*50);
            //Chama a funcao ganhador para indicar quem ganhou o produto do noh atual(aux)
            ganhador(L_prod, aux->info, pessoa, &erro);
            printf("%s comprou o produto %s\n", pessoa, aux->info);
        }
        else {
            //Caso a pilha estiver vazia, imprime que nao ha lances
            printf("Nao foi dado lances para o produto '%s'\n", aux->info);
        }
        aux = aux->prox;
    }
    //Destroi a lista antiga e inicializa outra, caso o usuario queira comecar outro leilao
    destruirL (L_prod);
    L_prod = criarL();
    
	return;
}