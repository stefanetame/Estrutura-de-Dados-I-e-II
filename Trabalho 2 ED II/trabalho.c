#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalho.h"

/* LISTA */
LISTA* criar_lista(void){
	LISTA *L = (LISTA*)malloc(sizeof(LISTA)); //aloca-se a lista
    if(L != NULL){ //se houve a alocacao, seus ponteiros inicio e fim apontam para null
		L->inicio = NULL;
	    L->fim = NULL;
	}
	return(L);
}

int inserir_lista(LISTA *L, char *titul){
    NOL *p = (NOL*)malloc(sizeof(NOL)); //aloca um noh da lista
	NOL *ant, *at; //anterior, atual

	if (p == NULL){ //verifica se ha uma lista alocada
		return(1);
	}
	else{
		p->titulo = (char*)malloc(sizeof(char)*50); //aloca um espaço para uma string
        strcpy(p->titulo, titul); 

        //os if's a seguir insere de forma ordenada alfabeticamente na lista, usando a funcao strcmp da biblioteca string
		if(L->inicio == NULL || strcmp(L->inicio->titulo, titul) > 0){
			p->prox = L->inicio;
			L->inicio = p;
		}
        else if(strcmp(L->inicio->titulo, titul) == 0){ //nao insere um filme se ja haver na lista na cabeca da lista
            return(2);
        }
		else{
			ant = NULL;
			at = L->inicio;
			while(at != NULL && strcmp(at->titulo, titul) <= 0){
                if(strcmp(at->titulo, titul) == 0){//nao insere um filme se ja haver na lista na cauda da lista
                    return(2);
                }
                //a seguir, serve para percorrer a lista ate encontrar a posicao de se inserir o filme (de forma ordenada)
				ant = at;
				at = at->prox;
			}
			p->prox = at;
			ant->prox = p;
		}
        return(0);
	}
}

void destroi_lista(LISTA *L){
	NOL *p = L->inicio;
	while(p != NULL){
		L->inicio = L->inicio->prox;
        free(p->titulo); //desaloca a string
		free(p); //desaloca o noh da lista
		p = L->inicio; //percorre a lista para desalocar
	}
	free(L); // desaloca a lista
}

int procura_lista(LISTA *L, char *titul){
	NOL *p = L->inicio;

	while(p != NULL){ //percorre a lista, noh por noh
		if(strcmp(p->titulo, titul) == 0){ //se houver o filme na lista, retorna 1
			return(1);
		}
		else{
			p = p->prox;
		}
	}
	return(0); //caso contrario, retorna 0
}

int remover_lista(LISTA *L, char *titul){
    NOL *atual, *ant;
    int teste = 0;

    atual = L->inicio;

    while ((atual != NULL) && (!teste)) { //percorre a lista, ate encontrar noh que corresponde com o filme que precisa ser removido
        if (strcmp(atual->titulo, titul) != 0){ //se nao encontrar, entra no if
            ant = atual;
            atual = atual->prox;
        }
        else { //se encontrar, entra no else
            if (atual == L->inicio) { //se o filme estiver no inicio da fila 
                L->inicio = L->inicio->prox;
                if (L->inicio == NULL){
                    L->fim = NULL;
                }
            }
            else if (atual == L->fim) { //se o filme estiver no fim da fila
                L->fim = ant; 
                L->fim->prox = NULL;
            }
            else {//se o filme estiver no meio da fila
                ant->prox = atual->prox;
            }
            free(atual->titulo); //desaloca a string associada
            free(atual); //desaloca o noh
            teste = 1;
        }
	}

    return(!teste);
}

/* ARVORE */

ARV* criar(void){
	ARV *aux = (ARV*)malloc(sizeof(ARV)); //aloca-se a arvore
	if(aux != NULL){ //se a alocacao da arvore tiver dado certo
		aux->raiz = NULL; //seu ponteiro de raiz aponta pra null
	}
	return(aux);
}

//1)CRIAR UM CADASTRO NA ARVORE PEDINDO AS INFOS NECESSARIAS 

int inserir_arv(NO **p, int ch, char *nome, char **film, int nf){
    int i, e;

	if(*p == NULL){ //se a arvore estiver vazia
		*p = (NO*)malloc(sizeof(NO)); //aloca um noh pra arvore
        (*p)->aluno = (char*)malloc(sizeof(char)*50); //aloca uma string para o noh da arvore
		(*p)->chave = ch; //insere o n usp
        strcpy((*p)->aluno, nome); //insere o nome do aluno
		(*p)->esq = NULL; //ponteiro de esquerda e direita apontam pro nulo
		(*p)->dir = NULL;
        (*p)->filmes = criar_lista(); //aloca a lista associada ao noh da arvore
        for(i = 0; i < nf; i++){ //insere filme por filme
            e = inserir_lista((*p)->filmes, film[i]);
            if(e == 2){ ////confere o erro que eh retornado da funcao
                printf("Filme %d nao cadastrado por repeticao\n", i+1);
            }
            else if(e == 1){
                printf("Erro de alocacao na lista\n");
            }
        }
		return (0);
	}
	else if(ch < (*p)->chave){ //se o n usp for menor do que a raiz da subarvore da funcao, chama novamente a funcao inserir
		return(inserir_arv(&(*p)->esq, ch, nome, film, nf));
	}
	else if(ch > (*p)->chave){ //se o n usp for maior do que a raiz da subarvore da funcao, chama novamente a funcao inserir
		return(inserir_arv(&(*p)->dir, ch, nome, film, nf));
	}
	else{
		return(1); //caso a arvore nao esteja aloca corretamente
	}
}

int inserir(ARV *A, int ch, char *nome, char **film, int nf){ //funcao auxiliar que recebe a arvore para chamar a funcao recursiva que trabalha com nohs
    return(inserir_arv(&A->raiz, ch, nome, film, nf));
}

/*----------------FIM----------------*/

//2)LISTAR ALUNOS (USANDO ALGUM ALG DE PERCURSO DE ARV)

int listar_alunos_arv(NO *p){
	if(p != NULL){ 
        listar_alunos_arv(p->esq); //percorre a arvore de forma ordenada esq/raiz/dir
		printf("N° USP: %d e aluno(a): %s\n", p->chave, p->aluno); //imprime o nome e o n usp dos alunos
		listar_alunos_arv(p->dir);
        return(0);
    }
    else{
        return(1);
    }
}

int listar_alunos(ARV *A){ //funcao auxiliar que recebe a arvore para chamar a funcao recursiva que trabalha com nohs
    return(listar_alunos_arv(A->raiz));
}

/*----------------FIM----------------*/

//3)BUSCAR UM ALUNO (POR NOME OU N USP, N SEI) E RETORNAR SE SIM OU NAO

int busca_nusp(NO *p, int nusp){
	if(p == NULL){ //se o noh eh nulo
		return(0); //nao encontrado
	}
	else if(p->chave == nusp){ //se o n usp for igual ao n usp do noh atual
		return(1); //encontrado
	}
	else if(nusp < p->chave){ //se o n usp for menor ao n usp do noh atual
		return(busca_nusp(p->esq, nusp)); //chama a funcao novamente
	}
	else{ //se o n usp for maior ao n usp do noh atual
		return(busca_nusp(p->dir, nusp)); //chama a funcao novamente
	}
}

int procura_aluno(ARV *A, int nusp){ //funcao auxiliar que recebe a arvore para chamar a funcao recursiva que trabalha com nohs
    return(busca_nusp(A->raiz, nusp));
}

/*----------------FIM----------------*/

//4)LISTAR TODOS OS FILMES EM ORDEM ALFABETICA QUE HA NA ARVORE SEM REPETICOES 

void listar_filmes_arv(NO **p, LISTA *l){
    NOL *list;
    int a;
    
    if((*p) != NULL){ 
        list =  (*p)->filmes->inicio; //list eh um noh da lista que vai auxiliar a percorrer todos os nohs da lista de filmes associadas ao noh atual p 
        while(list != NULL){ //percorre toda a lista
            a = inserir_lista(l, list->titulo); //insere todos os filmes do noh atual p 
            list = list->prox;
        }
        listar_filmes_arv(&(*p)->esq, l);//percorre todos os nohs da arv (esq e dir)
        listar_filmes_arv(&(*p)->dir, l);
    }
}

void listar_filmes(ARV *A){
    LISTA *L; //cria uma lista para guardar todos os filmes da arvore do sistema 
    int i = 1;
    L = criar_lista(); //aloca a lista
    NOL *list;

    //chama a funcao recursiva a seguir para inserir na lista L todos os filmes da arvore do sistema sem repeticao
    listar_filmes_arv(&A->raiz, L);
    list = L->inicio;

    printf("Listagem de filmes:\n");
    while(list != NULL){ //percorre a lista para imprimir todos os filmes
        printf("%d) %s\n", i, list->titulo);
        list = list->prox;
        i++;
    }

    destroi_lista(L); //desaloca a lista
}

/*----------------FIM----------------*/

//5)BUSCAR UM FILME E RETORNAR SE HA OU NAO EM ALGUM CADASTRO

int buscar_filme_arv(NO *p, char *titul){
    if(p != NULL){ //se o noh atual for diferente de nulo
        if (procura_lista(p->filmes, titul) == 1){ //se o filme procurado estiver na lista de filme do noh atual (usando a funcao procura_lista)
            return(1); //encontrado
        }
        else{ //caso contrario:
            //primeiro confere quais filhos o noh atual tem para chamar a funcao busca novamente ate encontrar o filme ou ate zerar a arvore
            if(p->esq == NULL && p->dir != NULL){ 
                return(buscar_filme_arv(p->dir, titul));
            }
            else if(p->esq != NULL && p->dir == NULL){
                return(buscar_filme_arv(p->esq, titul));
            }
            else if(p->dir != NULL && p->esq != NULL){
                return(buscar_filme_arv(p->esq, titul) + buscar_filme_arv(p->dir, titul)); 
            }
            else{
                return(0);
            }
        }
    }
    else{ // se o noh atual for igual a nulo
        return(0);
    }
}

int buscar_filme(ARV *A, char *titul){//funcao auxiliar que recebe a arvore para chamar a funcao recursiva que trabalha com nohs
    return(buscar_filme_arv(A->raiz, titul));
}

/*----------------FIM----------------*/

//6)ACHAR A PARTIR DE UMA PESSOA OUTRA PESSOA QUE TEM MAIS FILMES EM COMUM COM A PRIMEIRA EM TODA A ARVORA

NO* busca_nusp_no(NO *p, int nusp){ //funcao que acha o noh do aluno a partir de seu n usp
	if(p == NULL){
		return(p);
	}
	else if(p->chave == nusp){
		return(p);
	}
	else if(nusp < p->chave){ //percorre de forma inteligente, pois a arvore eh binaria. Se o numero usp for menor que o noh atual: entra na sub arvore esquerda
		return(busca_nusp_no(p->esq, nusp));
	}
	else{ //Se o numero usp for maior que o noh atual: entra na sub arvore esquerda
		return(busca_nusp_no(p->dir, nusp));
	}
}

int numero_nos(NO *p){
    if(p != NULL){ //funcao que percorre toda a arvore contando a quantidade de nohs da arvore
        return(numero_nos(p->esq) + numero_nos(p->dir) + 1);
    }
    else{
        return(0);
    }
} 

int quantidade(NO *arv, NO *pessoa){
    int count = 0, a;
    NOL *l = pessoa->filmes->inicio;

    while(l != NULL){ //percorre toda a lista de filmes do aluno usado para a procura
        a = procura_lista(arv->filmes, l->titulo); //confere se o filme do noh atual da lista esta na lista de filmes do outro aluno
        if(a == 1){
            count++; //contador cada vez que tiver um filme na lista
        }
        l = l->prox;
    }

    return(count); //retorna a quantidade
}

void achar_quantidade_filmes(NO *arv, NO *pessoa, int *qtdd, int *num_usp){
    int i = 0;
    if(arv != NULL){
        if(pessoa->chave != arv->chave){ //verificacao para nao ser o noh do aluno que esta sendo usado para a procura
            while(qtdd[i] != 0){//acha a primeira posicao do vetor vazia pra preencher
                i++;
            }
            num_usp[i] = arv->chave; //insere o n usp do aluno do noh atual
            qtdd[i] = quantidade(arv, pessoa); //insere a qtdd de filme em comum usando a funcao quantidade
        }
        achar_quantidade_filmes(arv->esq, pessoa, qtdd, num_usp); //percorre todos os nohs da arv (esq e dir)
        achar_quantidade_filmes(arv->dir, pessoa, qtdd, num_usp);
    }
}

void indicar_pessoa_mais(ARV *A, int nusp){
    NO *p, *q;
    int n, *qtdd, *num_usp, i, maior, indice = 0;
    
    //n sera o numero de nos da arvore do sistema, ou seja, o numero de alunos cadastrados no sistema
    n = numero_nos(A->raiz);

    if(n == 1){//se houver apenas um cadastro na arvore do sistema
        printf("Nao ha mais alunos cadastrados\n");
        return;
    }
    else if(n == 0){//se nao houver nenhum cadastro na arvore do sistema
        printf("Nao ha nenhum aluno cadastrado no sistema\n");
        return;
    }

    //aloca-se os vetores que representarao qtdd: quantidade de filmes em comum com o aluno a ser usado na procura e num_usp: o numero usp do aluno respectivo a quantidade de filme do outro vetor, ou seja, cada indice dos vetores representa o mesmo aluno 
    qtdd = (int*)malloc(sizeof(int)*(n-1));
    num_usp = (int*)malloc(sizeof(int)*(n-1));  

    //zera-se todo o vetor de quantidades
    for(i = 0; i < n-1; i++){
        qtdd[i] = 0;
    }

    //p eh o noh do aluno a ser usado na procura
    p = busca_nusp_no(A->raiz, nusp);  

    //funcao que preenche os vetores com suas informacoes (qtdd de filmes em comum e seu n usp respectivo)
    achar_quantidade_filmes(A->raiz, p, qtdd, num_usp);

    //percorre o vetor ate achar o maior numero
    maior = qtdd[0];
    for(i = 1; i < n-1; i++){
        if(maior < qtdd[i]){
            maior = qtdd[i];
            indice = i;
        }
    }

    //se o maior numero for 0, nao ha alunos com filmes em comum
    if(maior == 0){
        printf("Nao ha alunos com filmes em comum com voce\n");
        return;
    }

    //q eh o noh do aluno achado que tem mais filmes em comum
    q = busca_nusp_no(A->raiz, num_usp[indice]);
    printf("A pessoa com mais filmes em comum que voce eh: %s\n", q->aluno);
}

/*----------------FIM----------------*/

//7)ACHAR A PARTIR DE UMA PESSOA OUTRA PESSOA QUE TEM O MINIMO DE FILMES EM COMUM COM A PRIMEIRA EM TODO A ARVORE

void indicar_pessoa_menos(ARV *A, int nusp){
    NO *p, *q;
    int n, *qtdd, *num_usp, i, menor, indice = 0, X = 0;
    NOL *l;
    
    //n sera o numero de nos da arvore do sistema, ou seja, o numero de alunos cadastrados no sistema
    n = numero_nos(A->raiz);

    if(n == 1){ //se houver apenas um cadastro na arvore do sistema
        printf("Nao mais alunos cadastrados\n");
        return;
    }
    else if(n == 0){ //se nao houver nenhum cadastro na arvore do sistema
        printf("Nao ha nenhum aluno cadastrado no sistema\n");
        return;
    }

    //aloca-se os vetores que representarao qtdd: quantidade de filmes em comum com o aluno a ser usado na procura e num_usp: o numero usp do aluno respectivo a quantidade de filme do outro vetor, ou seja, cada indice dos vetores representa o mesmo aluno 
    qtdd = (int*)malloc(sizeof(int)*(n-1));
    num_usp = (int*)malloc(sizeof(int)*(n-1));  

    //zera-se todo o vetor de quantidades
    for(i = 0; i < n-1; i++){
        qtdd[i] = 0;
    }

    //p eh o noh do aluno a ser usado na procura
    p = busca_nusp_no(A->raiz, nusp);  

    //funcao que preenche os vetores com suas informacoes (qtdd de filmes em comum e seu n usp respectivo)
    achar_quantidade_filmes(A->raiz, p, qtdd, num_usp);

    //percorre o vetor ate achar o menor numero
    menor = qtdd[0];
    for(i = 1; i < n-1; i++){
        if(menor > qtdd[i]){
            menor = qtdd[i];
            indice = i;
        }
    }

     
    l = p->filmes->inicio;
    while(l != NULL){ //while: conta o numero de filmes do aluno usado na procura
        X++;
        l = l->prox;
    }

    if(menor == X){ //se o menor numero de filmes em comum for igual a quantidade de filmes do aluno, retorna que todos os outros alunos cadastrados tem a mesma quantidade de filmes e que nao ha um aluno sem filmes em comum com ele
        printf("Nao ha alunos sem filmes em comum com voce\n");
        return;
    }

    //q eh o noh do aluno achado que tem mais filmes em comum
    q = busca_nusp_no(A->raiz, num_usp[indice]);
    printf("A pessoa com menos filmes em comum que voce eh: %s\n", q->aluno);
}

/*----------------FIM----------------*/

//8)PRODUZIR UM ARQUIVO TEXTO COM TODAS AS INFOS DO SISTEMA

void percorre_emordem(NO *p, FILE *file){
    NOL *l;
    if(p != NULL){ // funcao que percorre a arvore toda em ordem (esq/raiz/dir)
        percorre_emordem(p->esq, file);
        l = p->filmes->inicio;
        //a partir daqui: preenche o arquivo com todos os dados do noh atual
        fprintf(file, "N USP: ");
        fprintf(file, "%d\n", p->chave);
        fprintf(file, "Nome do aluno(a): ");
        fprintf(file, "%s\n", p->aluno);
        fprintf(file, "Lista de filmes prediletos:\n");
        while(l != NULL){
            fprintf(file, "- %s\n", l->titulo);
            l = l->prox;
        }
        fprintf(file, "\n");

        percorre_emordem(p->dir, file);
    }
}

void criar_arquivo(ARV *A){
    FILE *file;
    file = fopen("sistema.txt", "w"); //inicia o arquivo chamado sistema

    fprintf(file, "Sistema de Cadastros de Alunos\n\n");
    percorre_emordem(A->raiz, file); //chama a funcao que insere todos os dados de forma recursiva

    fclose(file);
} 

/*----------------FIM----------------*/

/*9)EXIBIR
    (a) o número de nós existentes na árvore
    (b) a altura total da árvoree
    (c) a maior diferença entre alturas que existe entre as sub-árvores de algum nó da árvore;
*/

int altura(NO *p){
	int alt_esq, alt_dir;
	if(p == NULL){ //se o noh atual apontar pro nulo, retorna 0
		return(0);
	}
	else{ //caso contrario
		alt_esq = altura(p->esq); //acha a altura da sub arvore esquerda
		alt_dir = altura(p->dir); //acha a altura da sub arvore direita
		if(alt_esq > alt_dir){ //acha a maior altura e retorna seu valor
			return(1+alt_esq);
		}
		else{
			return(1+alt_dir);
		}
	}
}

int dif_alt(NO *p){ //maior diferenca de alturas de todas as subarvores
    int alt_esq, alt_dir, dif, dif1, dif2;
    if(p == NULL){ //retorna 0 se o noh atual apontar pro nulo
        return(0);
    }
    else{
        alt_esq = altura(p->esq); //acha a altura da sub arvore esquerda
		alt_dir = altura(p->dir); //acha a altura da sub arvore direita
        dif = alt_dir - alt_esq; //acha a diferenca de altura
        dif1 = dif_alt(p->esq); //acha a maior difenca altura da sub arvore esquerda
        dif2 = dif_alt(p->dir); //acha a maior difenca altura da sub arvore direita
        if(dif < 0){
            dif = (-1)*dif; //retorna a maior diferenca em modulo
        }

        //as condicoes a seguir servem para verificar qual eh a maior diferenca, entre as 3 diferencas encontradas (dif, dif1 e dif2) e retornar seu valor
        if((dif > dif1 && dif > dif2) || (dif == dif1 && dif > dif2) || (dif == dif2 && dif > dif1) || (dif2 == dif1 && dif2 < dif)){
            return(dif);
        }
        else if((dif1 > dif && dif1 > dif2) || (dif == dif2 && dif < dif1)){
            return(dif1);
        }
        else if((dif2 > dif1 && dif2 > dif) || (dif == dif1 && dif < dif2) || (dif2 == dif1 && dif2 > dif)){
            return(dif2);
        }
        else{
            return(dif);
        }
    }
}

void dados_sistema(ARV *A){
    int num, alt, maior;

    //imprime todos os dados do sistemas usando as funcoes respectivas
    num = numero_nos(A->raiz); 
    printf("O numero de nohs existentes na arvore eh: %d\n", num);

    alt = altura(A->raiz);
    printf("A altura da arvore eh: %d\n", alt-1);

    maior = dif_alt(A->raiz);
    printf("A maior diferenca entre alturas que existe entre as sub-arvores de algum noh da arvore: %d\n", maior);
}

/*----------------FIM----------------*/

//10)RETIRAR UM CADASTRO E REESTRUTURAR A ARVORE

NO* busca_maior(NO **p){
	NO *aux;
	aux = *p;
	while(aux->dir != NULL){ //percorre os nohs pela direita para achar a maior chave, ou seja, maior n usp
		aux = aux->dir;
	}
	return(aux);
}

int remover(NO **p, int nusp){
	NO *aux;
    NOL *l;
    int a;

	if(*p == NULL){ //se o noh atual apontar para o nulo, ou seja, nao foi encontrado o aluno a ser removido, retorna erro
		return (1);
	}
	else if(nusp < (*p)->chave){ //se o aluno a ser removido tem n usp menor que do noh atual, chama a funcao novamente pela esquerda
		return(remover(&(*p)->esq, nusp));
	}
	else if(nusp > (*p)->chave){ //se o aluno a ser removido tem n usp maior que do noh atual, chama a funcao novamente pela direita
		return(remover(&(*p)->dir, nusp));
	}
	else{
		//Caso 1: Nó sem filhos
		if(((*p)->esq == NULL) && ((*p)->dir == NULL)){
			destroi_lista((*p)->filmes); //destroi a lista de filme associada
            free((*p)->aluno); //desaloca a string
            free((*p)); //desaloca o noh
			(*p) = NULL;
            return(0);
		}
		//Caso 2.1: Só filho direito
		else if((*p)->esq == NULL){
			aux = (*p);
			(*p) = (*p)->dir; //nao perde a sub-arvore direita
            destroi_lista(aux->filmes); //destroi a lista de filme associada
			free(aux->aluno); //desaloca a string
            free(aux); //desaloca o noh
			return(0);
		}
		//Caso 2.2: Só filho esquerdo
		else if((*p)->dir == NULL){
			aux = (*p);
			(*p) = (*p)->esq; //nao perde a sub-arvore esquerda
            destroi_lista(aux->filmes); //destroi a lista de filme associada
			free(aux->aluno); //desaloca a string
            free(aux); //desaloca o noh
			return(0);
		}
		//Caso 3: Nó com 2 filhos
		else{
            aux = busca_maior(&(*p)->esq); //acha o noh com a maior chave da subarvore esquerda do noh atual
            (*p)->chave = aux->chave; //insere a chave encontrada no noh atual
            strcpy((*p)->aluno, aux->aluno); //insere o nome do aluno encontrado no noh atual
            destroi_lista((*p)->filmes); //zerar a lista de filmes do noh atual
            (*p)->filmes = criar_lista(); //aloca a lista de filmes novamente zerada
            l = aux->filmes->inicio; 
            while(l != NULL){ //percorre a lista de filmes no noh encontrado para inserir no noh atual
                a = inserir_lista((*p)->filmes, l->titulo);
                l = l->prox;
            }
            aux->chave = nusp; //insere no noh com a maior chave encontrado acima o n usp para remocao na sub arvore esquerda do noh atual usado no return abaixo
            return(remover(&(*p)->esq, nusp));
        }
	}
}

int retirar_aluno(ARV *A, int nusp){ //funcao auxiliar que recebe a arvore para chamar a funcao recursiva que trabalha com nohs
    return(remover(&A->raiz, nusp));
}

/*----------------FIM----------------*/

//11) INSERIR FILME EM ALGUM ALUNO

int inserir_filme(ARV *A, int nusp, char *titul){
    NO *p;
    //acha o noh a ser trabalhado
    p = busca_nusp_no(A->raiz, nusp);
    if(p == NULL){
        return(3);
    }

    return(inserir_lista(p->filmes, titul)); //retorna usando a funcao que remove na lista de filmes
}

/*----------------FIM----------------*/

//12) REMOVER FILME EM ALGUM ALUNO

int remover_filme(ARV *A, int nusp, char *titul){
    NO *p;

    //acha o noh a ser trabalhado
    p = busca_nusp_no(A->raiz, nusp);

    if(p == NULL){
        return(3);
    }    
    
    if(p->filmes->inicio->prox == NULL){// verificacao: lista de filmes n pode ter menos de um filme
        return (2);
    }

    return(remover_lista(p->filmes, titul)); //retorna usando a funcao que remove na lista de filmes
}

/*----------------FIM----------------*/

void destroi_arv(NO *p){
    if(p != NULL){
        destroi_arv(p->esq); //destroi a sub arvore esquerda do noh atual
        destroi_arv(p->dir); //destroi a sub arvore direita do noh atual
        destroi_lista(p->filmes); //destroi a lista de filmes associadas ao noh atual
        free(p->aluno); //desaloca a string
        free(p); //por fim, desaloca o noh
    }
}

void destroi(ARV *A){ //funcao auxiliar que recebe a arvore para chamar a funcao recursiva que trabalha com nohs
    destroi_arv(A->raiz);
    free(A);
}