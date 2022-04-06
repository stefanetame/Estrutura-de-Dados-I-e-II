#include "tad.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//funcao criar_grafo: aloca um grafo e insere os dados dos usuarios
Grafo* criar_grafo(int *NumVertices, int *erro, usuario *dados){
	if(*NumVertices >= MaxNumVertices){
		*erro = 1;
		return(NULL);
	}
	else{
		Grafo *G = (Grafo*)malloc(sizeof(Grafo)); //alocacao do grafo
		if(!G){
			*erro = 1;
		}
		else{
			*erro = 0;
			G->NumVertices = *NumVertices;
			int i;
			for(i = 0; i < G->NumVertices; i++){ //insere os dados e aloca as listas de amigos e de solicitacoes
				G->Adj[i].inicio = (no_aresta*)malloc(sizeof(no_aresta));
				G->Adj[i].inicio->peso = 0;
				G->Adj[i].inicio->prox = NULL;
				G->Adj[i].fim = G->Adj[i].inicio;
                G->Adj[i].pessoa = dados[i];
                G->Adj[i].comeco = (solicitacoes*)malloc(sizeof(solicitacoes));
                G->Adj[i].comeco->amigo = -1;
                G->Adj[i].comeco->prox = NULL; 
			}
		}
		return(G);
	}
}

// funcao ler_arquivo: funcao que le o arquivo e o percorre para salvar todos os dados no grafo
Grafo* ler_arquivo(int *erro) {
	int i=0, k, tam;
	FILE *arquivo;
	char linha[30], c;
    usuario dados[MaxNumVertices];

	arquivo = fopen("dados.txt", "rt"); // le o arquivo
	if (arquivo == NULL) { // confere se a abertura do arquivo ocorreu corretamente
		*erro = 1;
        return NULL;
	}

    while (!feof(arquivo)) {
        fgets(linha, 30, arquivo); //pega todos os dados na linha
        strcpy(dados[i].nome, linha); //insere no lugar devido
        k = strlen(dados[i].nome);
        dados[i].nome[k-1] = '\0'; //finaliza a string para desconsiderar o enter ('\n') quando ha quando se le a linha completa

        dados[i].idade = atoi(fgets(linha, 50, arquivo)); //pega a idade, que se trata de um inteiro

        fgets(linha, 30, arquivo); 
        strcpy(dados[i].cidade, linha);
        k = strlen(dados[i].cidade);
        dados[i].cidade[k-1] = '\0';

        fgets(linha, 30, arquivo); 
        strcpy(dados[i].filme, linha);
        k = strlen(dados[i].filme);
        dados[i].filme[k-1] = '\0';

        fgets(linha, 30, arquivo); 
        strcpy(dados[i].time, linha);
        k = strlen(dados[i].time);
        dados[i].time[k-1] = '\0';

        fgets(linha, 30, arquivo); 
        strcpy(dados[i].cor, linha);
        k = strlen(dados[i].cor);
        dados[i].cor[k-1] = '\0';

        fgets(linha, 30, arquivo); //descosidera a linha vazia que ha entre os usuarios no txt
        
        i++; //i: contabiliza o numero de usuarios
	}

	fclose(arquivo);

    //criando grafo e inserindo dados
    Grafo *G = criar_grafo(&i, erro, dados);

    return (G);
}

//funcao le_string: le uma string ate o enter (\n)
char* le_string(int caso){
    char *nome, c;
    int tam, k, i=0;

    nome = (char*)malloc(sizeof(char));

    scanf("%s", nome); //le ate o espaco
    tam = strlen(nome); 
    k = tam;
    do {
      scanf("%c", &c);
      nome[tam++] = c;
    } while (c != '\n'); // le a string ate o enter, caso a string tenha espaços
    nome[tam-1] = '\0'; //finaliza a string pra desconsiderar o enter

    //UNIFICAO DE DADOS EM LETRAS MAISCULAS E MINUSCULAS:
    //coloca a string inteira em letras minusculas:
    while(i < tam-1){
        if(isupper(nome[i])){
            nome[i] = tolower(nome[i]);
        }
        i++;
    }

    //coloca a primeira letra maiscula
    nome[0] = toupper(nome[0]);

    if(caso == 1){ //caso for o nome da pessoa, coloca o segundo nome com a primeira letra maiuscula
        nome[k+1] = toupper(nome[k+1]);
    }

    return(nome);
}

//funcao criar_perfil: cria um perfil pra um usuario novo, insere no grafo e insere no arquivo texto de dados
int criar_perfil(Grafo *G, char *nome){
    usuario dados;
    int r;
    FILE *arquivo;
    char idade[5];

    //pega os dados com o usuario
    strcpy(dados.nome,nome);
    printf("Digite sua idade: ");
    scanf("%s", idade);
    sscanf( idade, "%d\n", &dados.idade );
    printf("Digite sua cidade: ");
    strcpy(dados.cidade, le_string(0));
    printf("Digite seu filme predileto: ");
    strcpy(dados.filme, le_string(0));
    printf("Digite seu time predileto: ");
    strcpy(dados.time, le_string(0));
    printf("Digite sua cor predileta: ");
    strcpy(dados.cor, le_string(0));

    //acrescenta os dados no grafo
    r = G->NumVertices;
    G->Adj[r].inicio = (no_aresta*)malloc(sizeof(no_aresta));
    G->Adj[r].inicio->peso = 0;
    G->Adj[r].inicio->prox = NULL;
    G->Adj[r].fim = G->Adj[r].inicio;
    G->Adj[r].pessoa = dados;
    G->Adj[r].comeco = (solicitacoes*)malloc(sizeof(solicitacoes));
    G->Adj[r].comeco->amigo = -1;
    G->Adj[r].comeco->prox = NULL;
    G->NumVertices++;  

    //acrescenta os dados no arquivo
    arquivo = fopen("dados.txt", "at"); // le o arquivo
    if (arquivo == NULL) { // confere se a abertura do arquivo ocorreu corretamente
        printf("Erro ao abrir o arquivo para inclusao de perfil\n");
        return -1;
    }

    fputs("\n", arquivo);
    fputs(dados.nome, arquivo);
    fputs("\n", arquivo);
    fputs(idade, arquivo);
    fputs("\n", arquivo);
    fputs(dados.cidade, arquivo);
    fputs("\n", arquivo);
    fputs(dados.filme, arquivo);
    fputs("\n", arquivo);
    fputs(dados.time, arquivo);
    fputs("\n", arquivo);
    fputs(dados.cor, arquivo);
    fputs("\n", arquivo);

    fclose(arquivo);

    return r;
}

//funcao log_in: faz LOG IN do usuario
int log_in (Grafo *G, char *nome){
    int i=0, r;

    printf("Digite seu nome para acesso a seus dados\n");
    strcpy(nome, le_string(1));

    while(strcmp(G->Adj[i].pessoa.nome, nome) != 0){ //procura o numero do vertice associado ao nome que o usuario digitou
        if (i<G->NumVertices){
            i++;
        }
        else{
            printf("Este nome nao foi encontrado.\n");
            printf("Deseja criar um perfil?\n1.sim 2.nao\n");
            scanf("%d", &r);
            if(r == 1){ //da a opcao para o usuario criar um novo perfil
                i = criar_perfil(G, nome);
                break;
            }
            else{
                printf("Por favor, insira o nome novamente.\nNome: ");
                strcpy(nome, le_string(1));
                i = 0;
            }
        }
    }
    return (i);
}

//funcao existe_aresta: verifica se ha aresta entre dois vertices, ou seja, se ha amizade entre dois usuarios
int existe_aresta(Grafo *G, int *V1, int *V2, int *erro){
	if((*V1 >= G->NumVertices) || (*V2 >= G->NumVertices)){
		*erro = 1;
		return 0;
	}
	else{
		*erro = 0;
		int encontrou = 0;
		no_aresta *aux = G->Adj[*V1].inicio->prox;
		while((aux != NULL) && (!encontrou)){
			if(aux->v == *V2){
				encontrou = 1;
			}
			else{
				aux = aux->prox;
			}
		}
		return(encontrou);
	}
}

//funcao contador: calcula COMPATIBILIDADE entre dois usuarios
int contador(usuario x, usuario y, int caso){
    int c=0, i=0, j=0;
    char sobrenome1[20], sobrenome2[20]; 

    do{
        i++;
    }while(x.nome[i] != 32); //acha o lugar que ha espaco na string, ou seja, ate o fim do nome, antes do sobrenome da pessoa
    i++;
    while(x.nome[i] != '\0'){ //entao guarda o restando na string sobrenome
        sobrenome1[j] = x.nome[i];
        i++; j++;
    }

    i = 0; j = 0;
    do{
        i++;
    }while(y.nome[i] != 32);
    i++;
    while(y.nome[i] != '\0'){
        sobrenome2[j] = y.nome[i];
        i++; j++;
    }

    if(strncmp(sobrenome1, sobrenome2, strlen(sobrenome1)-1) == 0){
        c = c + 10; //se os sobrenomes forem iguais, ganha 10% de compatibilidade
    }

    if((caso == 0) && (strncmp(sobrenome1, sobrenome2, strlen(sobrenome1)-1) == 0)){
        return 0; //se os sobrenomes forem iguais, supostamente parentes mas a pessoa ta procurando o namorade ideal, retorna 0 de compatibilidade para descosiderar o parente
    }

    if(abs(x.idade-y.idade) < 5){//se as idades forem iguais, ganha 20% de compatibilidade, se forem proximas ate 4 anos, ganha um pouco de porcentagem de compatibilidade
      c = 20 - 4*(abs(x.idade-y.idade));
    }
    if(strcmp(x.cidade, y.cidade) == 0){
      c = c+20;
    }
    if(strcmp(x.filme, y.filme) == 0){
      c = c+20;
    }
    if(strcmp(x.time, y.time) == 0){
      c = c+20;
    }
    if(strcmp(x.cor, y.cor) == 0){
      c = c+10;
    }
    return c;
}

//funcao solitacao_ja_feita: verifica se o amigo ja mandou solicitacoa pra pessoa (nome)
int solicitacao_ja_feita(Grafo *G, int nome, int amigo){
    solicitacoes *aux;
    aux = G->Adj[nome].comeco;
    while(aux != NULL){ //percorre a lista de solicitacoes para ver se o amigo esta la
        if(aux->amigo == amigo){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

//funcao fazer_convite: faz o convite para o usuario q a pessoa deseja
void fazer_convite(Grafo *G, int v){
    int i, tam, k, erro;
    char c, amigo[30];
    solicitacoes *aux, *aux2;
    //solicitacoes *aux, *aux2, *nova;

    printf("\nDigite o nome da pessoa que deseja mandar um convite de amizade: ");
    strcpy(amigo, le_string(1)); //pega o nome do amigo para mandar o convite

    i = 0;
    while(strcmp(G->Adj[i].pessoa.nome, amigo) != 0){ //percorre o grafo pra encontrar o vertice associado ao amigo
        if (i<G->NumVertices){
            i++;
        }
        else{ //caso nao encontrar o amigo, apos percorrer todos os vertices
            printf("Este nome nao foi encontrado. Gostaria de tentar outro nome?\n 1)Sim\n 2)Nao\n");
            scanf("%d", &i);
            if (i==1){
                printf("\nDigite o nome da pessoa que deseja mandar um convite de amizade:\n");
                strcpy(amigo, le_string(1));
                i = 0;
            }
            else {
                return;
            }
        }
    }

    if(existe_aresta(G, &v, &i, &erro)){ //verifica se eles ja sao amigos
        printf("Voces ja sao amigos\n");
        return;
    }

    if(solicitacao_ja_feita(G, v, i)){ //verifica se o amigo desejado ja mandou convite de amizade
        printf("%s ja te mandou solicitacao de amizade anteriormente.\nVerifique suas solicitacoes\n", G->Adj[i].pessoa.nome);
        return;
    }

    if(solicitacao_ja_feita(G, i, v)){ //verifica se a pessoa ja mandou convite de amizade para o amigo desejado
        printf("Voce ja mandou solicitacao de amizade anteriormente para %s.\n", G->Adj[i].pessoa.nome);
        return;
    }

    //insere na lista de solicitacoes do amigo desejado
    if(G->Adj[i].comeco->amigo == -1){ //primeiro da lista
        G->Adj[i].comeco->amigo = v;
        G->Adj[i].comeco->prox = NULL;
    }
    else{ //percorre a lista ate encontrar o fim para inserir
        aux = (solicitacoes*)malloc(sizeof(solicitacoes));
        if (aux == NULL){
            printf("Erro ao fazer solicitacao\n");
            return;
        }
        aux->amigo = v;
        aux->prox = NULL;

        aux2 = G->Adj[i].comeco;
        while(aux2->prox != NULL){
            aux2 = aux2->prox;
        }
        aux2->prox = aux;
    }
    
    printf("Solicitacao enviada!\n");
}

//funcao inserir_aresta: insere uma aresta entre dois vertices, ou seja, faz uma amizade entre dois usuarios
void inserir_aresta(Grafo *G, int *V1, int *V2, elem *P, int *erro){
	if((*V1 >= G->NumVertices) || (*V1 >= G->NumVertices)){
		*erro = 1;
	}
	else{
		*erro = 0;
        //insere os dados de ambas as partes:
		G->Adj[*V1].inicio->peso++; //grau indicado no sentinela
		G->Adj[*V1].fim->prox = (no_aresta*)malloc(sizeof(no_aresta));
		G->Adj[*V1].fim = G->Adj[*V1].fim->prox;
		G->Adj[*V1].fim->v = *V2;
		G->Adj[*V1].fim->peso = *P;
		G->Adj[*V1].fim->prox = NULL;

        G->Adj[*V2].inicio->peso++; //grau indicado no sentinela
		G->Adj[*V2].fim->prox = (no_aresta*)malloc(sizeof(no_aresta));
		G->Adj[*V2].fim = G->Adj[*V2].fim->prox;
		G->Adj[*V2].fim->v = *V1;
		G->Adj[*V2].fim->peso = *P;
		G->Adj[*V2].fim->prox = NULL;	
	}
}

//funcao ver_solicitacoes: permite que usuario aceite ou recuse solicitacoes de amizade
void ver_solicitacoes(Grafo *G, int v){
    char resposta[5];
    int c;
    elem P;
    int erro;
    solicitacoes *aux;
    
    if ((G->Adj[v].comeco == NULL) || (G->Adj[v].comeco->amigo == -1)){ //verifica se ha alguem na lista de solicitacoes
      printf("Voce nao tem solicitacoes de amizade\n");
    }
    else{
        while(G->Adj[v].comeco != NULL){ //percorre a lista de solicitacoes e pergunta para o usuario se deseja ser amigo da pessoa ou nao
            c = contador(G->Adj[v].pessoa, G->Adj[G->Adj[v].comeco->amigo].pessoa, 1);
            printf("A pessoa %s te mandou um convite de amizade\n", G->Adj[G->Adj[v].comeco->amigo].pessoa.nome);
            printf("Chance de compatibilidade: %d%%\n", c);
            printf("Deseja aceitar? (sim/nao): ");
            scanf("%s", resposta); 
            if(strcmp(resposta, "sim") == 0){
                inserir_aresta(G, &v, &G->Adj[v].comeco->amigo, &P, &erro);
            }
            else if((strcmp(resposta, "sim") != 0) && (strcmp(resposta, "nao") != 0)){
                printf("ERROR\n");
                break;
            }
            aux = G->Adj[v].comeco;
            G->Adj[v].comeco = G->Adj[v].comeco->prox;
            free(aux);
        }
    }
}

//funcao sugestoes: faz sugestao de AMIZADES de acordo com compatibilidade
void sugestoes(Grafo *G, int v){
    int i, erro, count, j=0, maior=0;
    int melhores[G->NumVertices];

    for(i=0; i<G->NumVertices; i++){
        melhores[i] = -1; //zera o vetor melhores, que vai servir de auxiliar
    }

    //percorre a lista de usuarios
    for(i=0; i<G->NumVertices; i++){
        if((i == v) || (existe_aresta(G, &v, &i, &erro))){
            continue;
        }
        else{
            count = contador(G->Adj[v].pessoa, G->Adj[i].pessoa, 1); //count: porcentagem de compatibilidade da pessoa v e i
            if(count > maior){ //se for maior, reinicia o vetor e guarda a pessoa i
                maior = count;
                melhores[0] = i;
                j = 1;
            }
            else if(count == maior){ //se for igual, acrescenta no vetor e guarda a pessoa i
                melhores[j] = i;
                j++;
            }
        } 
    } 

    printf("Sugestoes de amizades verdadeiras:\n"); //imprime toda a lista de sugestoes
    for(i=0; i < j; i++){
        printf("%s, com %d%% de compatibilidade\n", G->Adj[melhores[i]].pessoa.nome, maior);
    }
}

//funcao retirar_aresta: retira uma aresta entre dois vertices, ou seja, retira a amizade entre dois usuarios
void retirar_aresta(Grafo *G, int *V1, int *V2, elem *P, int *erro){
	if((*V1 >= G->NumVertices) || (*V2 >= G->NumVertices)){
		*erro = 1;
	}
	else{
        //retira os dados de V1 em V2 e de V2 em V1
		int encontrou = 0;
		no_aresta *ant = G->Adj[*V1].inicio;
		no_aresta *aux = G->Adj[*V1].inicio->prox;
		while((aux!=NULL) && (!encontrou)){ //percorre a lista de adjacencias
			if(aux->v == *V2){
				G->Adj[*V1].inicio->peso--;
				encontrou = 1;
				*P = aux->peso;
				ant->prox = aux->prox;
				if(G->Adj[*V1].fim == aux){
					G->Adj[*V1].fim = ant;
				}
				free(aux);
			}
			else{
				ant = ant->prox;
				aux = aux->prox;
			}
		}

        encontrou = 0;
		ant = G->Adj[*V2].inicio;
		aux = G->Adj[*V2].inicio->prox;
		while((aux!=NULL) && (!encontrou)){ 
			if(aux->v == *V1){
				G->Adj[*V2].inicio->peso--;
				encontrou = 1;
				*P = aux->peso;
				ant->prox = aux->prox;
				if(G->Adj[*V2].fim == aux){
					G->Adj[*V2].fim = ant;
				}
				free(aux);
			}
			else{
				ant = ant->prox;
				aux = aux->prox;
			}
		}
	}
}

//funcao ListaAdjVazia: verifica se o vertice tem alguma aresta, ou seja, verifica se um usuario tem algum amigo
int ListaAdjVazia(Grafo *G, int *V, int *erro){
	if(*V >= G->NumVertices){
		*erro = 1;
		return(1);
	}
	else{
		*erro = 0;
		if(G->Adj[*V].inicio->prox == NULL){
			return 1;
		}
		else{
			return 0;
		}
	}
}

//funcao PrimeiroListaAdj: retorna o primeiro vertice da lista de adjacencias de algum vertice, ou seja, retorna o primeiro amigo da lista de amigos de algum usuario
void PrimeiroListaAdj(Grafo *G, int *V, no_aresta **Adj, elem *P, int *erro){
	if(*V >= G->NumVertices){
		*erro = 1;
	}
	else{
		*erro = 0;
	}
	*Adj = G->Adj[*V].inicio->prox;
	*P = (*Adj)->peso;
}

//funcao ProxAdj: retorna o proximo vertice da lista de adjacencias de algum vertice, ou seja, retorna o proximo amigo da lista de amigos de algum usuario
void ProxAdj(Grafo *G, no_aresta **Adj, elem *P, int *erro){
	*erro = 0;
	*Adj = (*Adj)->prox;
	if(*Adj != NULL){
		*P = (*Adj)->peso;
	}
	else{
		*P = -1;
	}
}

//funcao amigos_nao_verdadeiros: imprime amigos menos compativeis com usuario logado e pergunta se usuario quer excluir essas amizades
void amigos_nao_verdadeiros(Grafo *G, int v){
    int piores[G->NumVertices];
    int erro, menor=100, count, i, j=0, r;
    elem P;
    no_aresta *aux;

    for(i=0; i<G->NumVertices; i++){
        piores[i] = -1; //vetor auxiliar
    }

    //verifica se a lista esta vazia
    if(ListaAdjVazia(G, &v, &erro)){
        printf("Nao ha amigos na sua lista\n");
        return;
    }
    else{
        PrimeiroListaAdj(G, &v, &aux, &P, &erro); //percorre a lista de adjacencias
        while(aux != NULL){
            i = aux->v;
            count = contador(G->Adj[v].pessoa, G->Adj[i].pessoa, 1);
            if(count < menor){ //se for menor, reinicia o vetor e inseri a pessoa i
                menor = count;
                piores[0] = i;
                j = 1;
            }
            else if(count == menor){ //se for igual, acrescenta no vetor a pessoa i
                piores[j] = i;
                j++;
            }
            ProxAdj(G, &aux, &P, &erro);
        }

        printf("Lista de amigos que nao sao amigos verdadeiros:\n");// imprime a lista de amigos
        for(i=0; i < j; i++){
            printf("%s, com %d%% de compatibilidade\n", G->Adj[piores[i]].pessoa.nome, menor);
        }
        printf("\n");
        for(i=0; i < j; i++){ //da a opcao de excluir as amizades
            printf("Deseja excluir sua amizade com %s?\n1.sim 2.nao\n", G->Adj[piores[i]].pessoa.nome);
            scanf("%d", &r);
            if(r == 1){
                retirar_aresta(G, &v, &i, &P, &erro);
                printf("Amizade removida com sucesso\n");
            }
        }
    }
}

//funcao namorade_ideal: encontra perfil fora da familia mais conpativel com usuario 
void namorade_ideal(Grafo *G, int v){
    int i, j, k=0, maior=0, count, noh=-1;

    for(i=0; i<G->NumVertices; i++){ //percorre todo o grafo
        if(i == v){
            continue;
        }
        else{
            count = contador(G->Adj[v].pessoa, G->Adj[i].pessoa, 0);
            //se achar um mais compativel e c sobrenome diferente
            if(count > maior){
                maior = count;
                noh = i; 
                
            }
        }
    }
    printf("Namorade ideal eh %s, com %d%% de compatibilidade\n", G->Adj[noh].pessoa.nome, maior);
}

//funcao lista_amigos: imprime lista de amigos do usuario
void lista_amigos(Grafo *G, int v){
    int erro, i;
    elem P;
    no_aresta *aux;

    if(ListaAdjVazia(G, &v, &erro)){
        printf("Nao ha amigos na sua lista\n");
        return;
    }
    else{
        printf("Lista de amigos:\n");
        PrimeiroListaAdj(G, &v, &aux, &P, &erro); //percorre toda lista de amigos, ou seja, lista de adjacencias
        while(aux != NULL){
            i = aux->v;
            printf("%s\n", G->Adj[i].pessoa.nome);
            ProxAdj(G, &aux, &P, &erro);
        }
    }
}

//funcao liberar_memoria: desaloca o grafo e desaloca as listas de adjacencias e solicitacoes
void liberar_memoria(Grafo *G){
	no_aresta *aux;
    solicitacoes *aux2;
	for(int i=0; i < G->NumVertices; i++){
		while(G->Adj[i].inicio != NULL){
			aux = G->Adj[i].inicio;
			G->Adj[i].inicio = G->Adj[i].inicio->prox;
			free(aux); 
		}
        while(G->Adj[i].comeco != NULL){
			aux2 = G->Adj[i].comeco;
			G->Adj[i].comeco = G->Adj[i].comeco->prox;
			free(aux2); 
		}
	}
	free(G);
}