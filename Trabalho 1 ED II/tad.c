#include "tad.h"

//----------LENDO O ARQUIVO E FAZENDO A LISTA---------

// funcao criar: aloca a lista e contabiliza a quantidade de linhas no arquivo
// de entrada
LISTA *criar() {
	LISTA *L;
	int total = 0;
	char Linha[100], *result, c;
	FILE *arq;

	L = (LISTA *)malloc(sizeof(LISTA)); // inicializa a lista
	if (L != NULL) {
		L->quantidade = 0; // inicializa o contador de dados da lista
	}

	// verificando quantos registros o arquivo tem
	arq = fopen("covid_19_clean_complete.csv", "r"); // le o arquivo
	if (arq == NULL) { // confere se abriu o arquivo corretamente
		printf("Problemas na abertura do arquivo\n");
	}
	result = fgets(Linha, 100, arq); // le a primeira linha para desconsidera-la
	while (!feof(arq)) {
		result = fgets(Linha, 100, arq);
		total++; // total eh o contador para a quantidade de linhas
	}
	fclose(arq);

	printf("Arquivo de entrada tem %d registros\n", total);
	L->itens = (elem *)malloc(
		total * sizeof(elem)); // aloca a lista de forma sequencial com a
							   // quantidade certa para guardar todos os dados
							   // do arquivo (quantidade de linhas)
	L->total = total;		// guarda a quantidade de linhas para uso posterior
	if (L->itens == NULL) { // confere se alocou corretamente
		printf("ERRO ao gerar lista de registros\n");
	}
	return L;
}

// funcao inserir: insere dados na lista em algum campo
int inserir(
	LISTA *L,
	char *provincia,
	char *pais,
	char *latitude,
	char *longitude,
	char *data,
	char *confirmados,
	char *mortes,
	char *recuperados) {
	if (L == NULL) { // confere se existe uma lista passada por parametro
		return 1;
	}

	// insere todos os dados na primeira posicao vazia
	strcpy(L->itens[L->quantidade].provincia, provincia);
	strcpy(L->itens[L->quantidade].pais, pais);
	strcpy(L->itens[L->quantidade].latitude, latitude);
	strcpy(L->itens[L->quantidade].longitude, longitude);
	strcpy(L->itens[L->quantidade].data, data);
	strcpy(L->itens[L->quantidade].confirmados, confirmados);
	strcpy(L->itens[L->quantidade].mortes, mortes);
	strcpy(L->itens[L->quantidade].recuperados, recuperados);
	L->quantidade++; // contabiliza a proxima posicao vazia para uma posterior
					 // insercao
	return 0;
}

// funca copiainfor_v: funcao auxiliar que copia a parte da linha na string
// certa para caso a informacao terminar em virgula
void copiainfo_v(char *linha, char *dado, int i) {
	int j = -1; // contador da posicao da string dado
	// i: contador da linha, onde i comeca do inicio ou apos alguma virgula
	do {
		j++;
		i++;
		dado[j] = linha[i]; // insere na string dado
	} while (
		dado[j] !=
		44); // enquanto for diferente de virgula ("," == 44 na tabela ascii)
	strcpy(&dado[j], " "); // substitui a virgula por um espaco
}

// funca copiainfor_l: funcao auxiliar que copia a parte da linha na string
// certa para caso a informacao for a ultima da linha (recuperados)
void copiainfo_l(char *linha, char *dado, int i) {
	int j = -1; // contador da posicao da string dado
	// i: contador da linha, onde i comeca apos a ultima virgula
	do {
		j++;
		i++;
		dado[j] = linha[i]; // insere na string dado
	} while (
		dado[j] !=
		'\n'); // enquanto for diferente de virgula ("," == 44 na tabela ascii)
	strcpy(&dado[j - 1], " "); // substitui o enter ("\n") por um espaco
}

// funcao ler_arquivo: funcao que le o arquivo e o percorre para salvar todos os
// dados na lista
int ler_arquivo(LISTA *L) {
	int erro, i, j, c;
	FILE *arquivo;
	char linha[100];
	char provincia[50], pais[50], data[50], latitude[50], longitude[50],
		confirmados[50], mortes[50], recuperados[50];

	arquivo = fopen("covid_19_clean_complete.csv", "rt"); // le o arquivo
	if (arquivo ==
		NULL) { // confere se a abertura do arquivo ocorreu corretamente
		return 1;
	}

	fgets(linha, 100, arquivo); // desconsidera a primeira linha

	while (!feof(arquivo)) {
		fgets(linha, 100, arquivo); // salva linha por linha na string linha

		// salva cada informacao da linha nas strings adequadas
		copiainfo_v(linha, provincia, -1);
		copiainfo_v(linha, pais, (strlen(provincia) - 1));
		copiainfo_v(linha, latitude, (strlen(provincia) + strlen(pais) - 1));
		copiainfo_v(
			linha,
			longitude,
			(strlen(provincia) + strlen(pais) + strlen(latitude) - 1));
		copiainfo_v(
			linha,
			data,
			(strlen(provincia) + strlen(pais) + strlen(latitude) +
			 strlen(longitude) - 1));
		copiainfo_v(
			linha,
			confirmados,
			(strlen(provincia) + strlen(pais) + strlen(latitude) +
			 strlen(longitude) + strlen(data) - 1));
		copiainfo_v(
			linha,
			mortes,
			(strlen(provincia) + strlen(pais) + strlen(latitude) +
			 strlen(longitude) + strlen(data) + strlen(confirmados) - 1));
		copiainfo_l(
			linha,
			recuperados,
			(strlen(provincia) + strlen(pais) + strlen(latitude) +
			 strlen(longitude) + strlen(data) + strlen(confirmados) +
			 strlen(mortes) - 1));

		// insere na lista cada dado de cada linha
		erro = inserir(
			L,
			provincia,
			pais,
			latitude,
			longitude,
			data,
			confirmados,
			mortes,
			recuperados);
		if (erro == 1) { // confere se ocorreu corretamente a insercao na lista
			return erro;
		}
	}

	fclose(arquivo);

	return 0;
}

//-----------FUNCOES DE ORDENACAO-----------

// funcao compare: compara dois numeros. Como os dados sao inseridos como
// strings, a funcao transforma em numeros para compara-los.
int compare(char *numero1, char *numero2) {
	float num1, num2;

	// transfere os dados da string em variaveis float
	sscanf(numero1, "%f ", &num1);
	sscanf(numero2, "%f ", &num2);

	if (num1 == num2) {
		return 0; // se forem iguais, retorna zero
	} else if (num1 > num2) {
		return 1; // se a primeiro for maior, retorna 1
	} else {
		return -1; // se a segundo for maior, retorna -1
	}
}

// funcao compareTo: compara duas datas. Como os dados sao inseridos como
// strings, a funcao transforma as datas em numeros para compara-los.
int compareTo(char *data1, char *data2) {
	int dia1, dia2, mes1, mes2, ano1, ano2;

	// transfere os dados da string em variaveis int
	sscanf(data1, "%d/%d/%d ", &mes1, &dia1, &ano1);
	sscanf(data2, "%d/%d/%d ", &mes2, &dia2, &ano2);

	if ((dia1 == dia2) && (mes1 == mes2)) {
		return 0; // se forem iguais, retorna zero
	} else if ((mes2 < mes1) || ((mes2 == mes1) && (dia2 < dia1))) {
		return 1; // se a primeira data for depois da segunda, retorna 1
	} else {
		return -1; // se a segunda data for depois da primeira, retorna -1
	}
}

// ORDENACAO SIMPLES: INSERTION-SORT
// funcao ordenar_pais_s: ordena em ordem alfabetica os paises
void ordenar_pais_s(elem v[], int n) {
	int i, j;
	elem aux;

	for (i = 1; i < n; i++) { // percorre todo o vetor
		aux = v[i]; // no i-esimo passo, guarda numa variavel o i-esimo noh da
					// lista
		j = i - 1;
		while ((j >= 0) &&
			   (strcmp(aux.pais, v[j].pais) <
				0)) { // acha a posicao correta do v[i] (considerando os paises
					  // de casa noh) dentro do vetor v[0], ..., v[i-1], que ja
					  // foi ordenado
			v[j + 1] = v[j]; // vai descolando o vetor ate encontrar a posicao
							 // certa de v[i]
			j--;
		}
		v[j + 1] = aux; // insere v[i] na posicao correta
	}
}

// funcao ordenar_latitude_s: ordena em ordem crescente as latitudes dos paises
void ordenar_latitude_s(elem v[], int n) {
	int i, j;
	elem aux;

	for (i = 1; i < n; i++) { // percorre todo o vetor
		aux = v[i]; // no i-esimo passo, guarda numa variavel o i-esimo noh da
					// lista
		j = i - 1;
		while ((j >= 0) &&
			   (compare(aux.latitude, v[j].latitude) <
				0)) { // acha a posicao correta do v[i] (considerando as
					  // latitudes de casa noh) dentro do vetor v[0], ...,
					  // v[i-1], que ja foi ordenado
			v[j + 1] = v[j]; // vai descolando o vetor ate encontrar a posicao
							 // certa de v[i]
			j--;
		}
		v[j + 1] = aux; // insere v[i] na posicao correta
	}
}

// funcao ordenar_longitude_s: ordena em ordem crescente as longitudes dos
// paises
void ordenar_longitude_s(elem v[], int n) {
	int i, j;
	elem aux;

	for (i = 1; i < n; i++) { // percorre todo o vetor
		aux = v[i]; // no i-esimo passo, guarda numa variavel o i-esimo noh da
					// lista
		j = i - 1;
		while ((j >= 0) &&
			   (compare(aux.longitude, v[j].longitude) <
				0)) { // acha a posicao correta do v[i] (considerando as
					  // latitudes de casa noh) dentro do vetor v[0], ...,
					  // v[i-1], que ja foi ordenado
			v[j + 1] = v[j]; // vai descolando o vetor ate encontrar a posicao
							 // certa de v[i]
			j--;
		}
		v[j + 1] = aux; // insere v[i] na posicao correta
	}
}

// funcao ordenar_simples: recebe do usuario de qual forma ele quer ordenar (por
// pais, por latitude ou por longitude) e chama a funcao adequada, considerando
// o metodo insertion-sort
double ordenar_simples(LISTA *L) {
	int caso;
	double TEMPO;
	clock_t end, start;
	start = clock(); // inicia o contador do tempo

	// o usuario escolhe o criterio de ordenacao
	printf("Deseja ordenar por:\n\n");
	printf("  1) Pais/regiao\n");
	printf("  2) Latitude\n");
	printf("  3) Longitude\n");
	printf("\nSua resposta: ");
	scanf("%d", &caso);

	switch (caso) {
	case 1: {
		ordenar_pais_s(L->itens, L->quantidade);
		break;
	}
	case 2: {
		ordenar_latitude_s(L->itens, L->quantidade);
		break;
	}
	case 3: {
		ordenar_longitude_s(L->itens, L->quantidade);
		break;
	}
	default: {
		printf("\nErro. Tente novamente.\n");
		break;
	}
	}
	// ordenacao estavel: a data se mantem ordenada

	end = clock(); // finaliza o contador do tempo
	TEMPO = (double)(end - start) / (double)(CLOCKS_PER_SEC);
	return TEMPO; // retorna o tempo para fins posteriores
}

// ORDENACAO AVANCADA: QUICK-SORT (NAO ESTAVEL)
// funcao ordenar_pais: ordena em ordem alfabetica os paises
void ordenar_pais(elem *v, int inf, int sup) {
	elem aux, pivo;

	if (inf < sup) {
		int meio = (inf + sup) / 2; // acha a posicao central
		// inverte o noh da posicao central com o ultimo noh do vetor
		pivo = v[meio];
		v[meio] = v[sup];
		v[sup] = pivo;

		int i = inf - 1;
		int j = sup;
		do {
			do {
				i++; // contador que acha todos os nohs que sao maiores que o
					 // noh central (considerando o pais) que estao antes dele
			} while (strcmp(v[i].pais, pivo.pais) < 0);

			do {
				j--; // contador que acha todos os nohs que sao menores que o
					 // noh central (considerando o pais) que estao depois dele
			} while ((strcmp(pivo.pais, v[j].pais) < 0) && (j > inf));

			if (i < j) {
				// se i for menor que j, inverte esses nohs i e j, para ficarem
				// na ordem certa de acordo com o noh central
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		} while (
			i <
			j); // faz isso ate que todos os nohs antes do noh central sejam
				// menores que ele e todos os nohs depois do noh central sejam
				// maiores que ele, ou seja, faz ate que i e j se encontrem

		//"desinverte" o noh central e o ultimo noh, para o noh central ficar na
		// posicao correta
		v[sup] = v[i];
		v[i] = pivo;

		// chama esta funcao novamente para ordenar os subvetores antes e depois
		// do noh central
		ordenar_pais(v, inf, i - 1);
		ordenar_pais(v, i + 1, sup);
	}
}

// funcao ordenar_latitude: ordena em ordem crescente a latitude dos paises
void ordenar_latitude(elem *v, int inf, int sup) {
	elem aux, pivo;

	if (inf < sup) {
		int meio = (inf + sup) / 2; // acha a posicao central
		// inverte o noh da posicao central com o ultimo noh do vetor
		pivo = v[meio];
		v[meio] = v[sup];
		v[sup] = pivo;

		int i = inf - 1;
		int j = sup;
		do {
			do {
				i++; // contador que acha todos os nohs que sao maiores que o
					 // noh central (considerando a latitude) que estao antes
					 // dele
			} while (compare(v[i].latitude, pivo.latitude) < 0);

			do {
				j--; // contador que acha todos os nohs que sao menores que o
					 // noh central (considerando a latitude) que estao depois
					 // dele
			} while ((compare(pivo.latitude, v[j].latitude) < 0) && (j > inf));

			if (i < j) {
				// se i for menor que j, inverte esses nohs i e j, para ficarem
				// na ordem certa de acordo com o noh central
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		} while (
			i <
			j); // faz isso ate que todos os nohs antes do noh central sejam
				// menores que ele e todos os nohs depois do noh central sejam
				// maiores que ele, ou seja, faz ate que i e j se encontrem

		//"desinverte" o noh central e o ultimo noh, para o noh central ficar na
		// posicao correta
		v[sup] = v[i];
		v[i] = pivo;

		// chama esta funcao novamente para ordenar os subvetores antes e depois
		// do noh central
		ordenar_latitude(v, inf, i - 1);
		ordenar_latitude(v, i + 1, sup);
	}
}

// funcao ordenar_longitude: ordena em ordem crescente a longitude dos paises
void ordenar_longitude(elem *v, int inf, int sup) {
	elem aux, pivo;

	if (inf < sup) {
		int meio = (inf + sup) / 2; // acha a posicao central
		// inverte o noh da posicao central com o ultimo noh do vetor
		pivo = v[meio];
		v[meio] = v[sup];
		v[sup] = pivo;

		int i = inf - 1;
		int j = sup;
		do {
			do {
				i++; // contador que acha todos os nohs que sao maiores que o
					 // noh central (considerando a longitude) que estao antes
					 // dele
			} while (compare(v[i].longitude, pivo.longitude) < 0);

			do {
				j--; // contador que acha todos os nohs que sao menores que o
					 // noh central (considerando a longitude) que estao depois
					 // dele
			} while ((compare(pivo.longitude, v[j].longitude) < 0) &&
					 (j > inf));

			if (i < j) {
				// se i for menor que j, inverte esses nohs i e j, para ficarem
				// na ordem certa de acordo com o noh central
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		} while (
			i <
			j); // faz isso ate que todos os nohs antes do noh central sejam
				// menores que ele e todos os nohs depois do noh central sejam
				// maiores que ele, ou seja, faz ate que i e j se encontrem

		//"desinverte" o noh central e o ultimo noh, para o noh central ficar na
		// posicao correta
		v[sup] = v[i];
		v[i] = pivo;

		// chama esta funcao novamente para ordenar os subvetores antes e depois
		// do noh central
		ordenar_longitude(v, inf, i - 1);
		ordenar_longitude(v, i + 1, sup);
	}
}

// funcao ordenar_data: ordena em ordem crescente as datas
void ordenar_data(elem *v, int inf, int sup) {
	elem aux, pivo;

	if (inf < sup) {
		int meio = (inf + sup) / 2; // acha a posicao central
		// inverte o noh da posicao central com o ultimo noh do vetor
		pivo = v[meio];
		v[meio] = v[sup];
		v[sup] = pivo;

		int i = inf - 1;
		int j = sup;
		do {
			do {
				i++; // contador que acha todos os nohs que sao maiores que o
					 // noh central (considerando a data) que estao antes dele
			} while (compareTo(v[i].data, pivo.data) < 0);

			do {
				j--; // contador que acha todos os nohs que sao menores que o
					 // noh central (considerando a data) que estao depois dele
			} while ((compareTo(pivo.data, v[j].data) < 0) && (j > inf));

			if (i < j) {
				// se i for menor que j, inverte esses nohs i e j, para ficarem
				// na ordem certa de acordo com o noh central
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		} while (
			i <
			j); // faz isso ate que todos os nohs antes do noh central sejam
				// menores que ele e todos os nohs depois do noh central sejam
				// maiores que ele, ou seja, faz ate que i e j se encontrem

		//"desinverte" o noh central e o ultimo noh, para o noh central ficar na
		// posicao correta
		v[sup] = v[i];
		v[i] = pivo;

		// chama esta funcao novamente para ordenar os subvetores antes e depois
		// do noh central
		ordenar_data(v, inf, i - 1);
		ordenar_data(v, i + 1, sup);
	}
}

// funcao ordena_data: eh a funcao que chama a funcao ordenar_data para cada
// caso; por exemplo, se o usuario decidir ordenar por pais, tera posicoes
// seguidas do mesmo pais, no entanto de forma desordenada por data. A funcao
// ordena_data seleciona todos as posicoes com o mesmo pais e ordena por data.
void ordena_data(LISTA *L, int caso) {
	int i = 0, j = 0;
	while (i < L->total) {
		if (caso == 1) {
			while ((strcmp(L->itens[i].pais, L->itens[i + 1].pais) == 0) &&
				   (i < L->total - 1)) {
				i++; // contador que acha ate qual posicao eh o mesmo pais
			}
		}
		if (caso == 2) {
			while (
				(strcmp(L->itens[i].latitude, L->itens[i + 1].latitude) == 0) &&
				(i < L->total - 1)) {
				i++; // contador que acha ate qual posicao eh a mesma latitude
			}
		}
		if (caso == 3) {
			while ((strcmp(L->itens[i].longitude, L->itens[i + 1].longitude) ==
					0) &&
				   (i < L->total - 1)) {
				i++; // contador que acha ate qual posicao eh a mesma longitude
			}
		}
		ordenar_data(
			L->itens, j, i); // chama a funcao para ordenar intervalo desejado
		i++;
		j = i; // inicializa o inicio do proximo noh diferente
	}
}

// funcao ordenar_avancado: recebe do usuario de qual forma ele quer ordenar
// (por pais, por latitude ou por longitude) e chama a funcao adequada,
// considerando o metodo quick-sort
double ordenar_avancado(LISTA *L) {
	int caso;
	double TEMPO;
	clock_t end, start;
	start = clock(); // inicia o contador do tempo

	// o usuario escolhe o criterio de ordenacao
	printf("Deseja ordenar por:\n\n");
	printf("  1) Pais/regiao\n");
	printf("  2) Latitude\n");
	printf("  3) Longitude\n");
	printf("\nSua resposta: ");
	scanf("%d", &caso);
	switch (caso) {
	case 1:
		ordenar_pais(L->itens, 0, L->quantidade);
		ordena_data(L, caso);
		break;
	case 2:
		ordenar_latitude(L->itens, 0, L->quantidade);
		ordena_data(L, caso);
		break;
	case 3:
		ordenar_longitude(L->itens, 0, L->quantidade);
		ordena_data(L, caso);
		break;
	default:
		printf("\nErro. Tente novamente.\n");
		break;
	}

	end = clock(); // finaliza o contador do tempo
	TEMPO = (double)(end - start) / (double)(CLOCKS_PER_SEC);
	return TEMPO; // retorna o tempo para fins posteriores
}

// funcao imprimir: gera o arquivo a partir dos dados da lista
int imprimir(LISTA *L, double TEMPO) {
	int i, j;
	FILE *arquivo;

	arquivo = fopen("arquivo_ordenado.csv", "w"); // abre o arquivo para escrita

	if (arquivo == NULL) { // confere se ocorreu corretamente a abertura
		return 1;
	}

	// insere os dados:
	fprintf(arquivo, "Tempo de ordenacao: %lfs\n", TEMPO);
	fprintf(
		arquivo,
		"Province/State,Country/"
		"Region,Lat,Long,Date,Confirmed,Deaths,Recovered\n");
	for (i = 0; i < L->total;
		 i++) { // percorre toda a lista para insercao no arquivo novo
		// substitui todo espaco no fim da string por virgula para ficar igual
		// ao arquivo original
		j = strlen(L->itens[i].provincia);
		L->itens[i].provincia[j - 1] = ',';
		j = strlen(L->itens[i].pais);
		L->itens[i].pais[j - 1] = ',';
		j = strlen(L->itens[i].latitude);
		L->itens[i].latitude[j - 1] = ',';
		j = strlen(L->itens[i].longitude);
		L->itens[i].longitude[j - 1] = ',';
		j = strlen(L->itens[i].data);
		L->itens[i].data[j - 1] = ',';
		j = strlen(L->itens[i].confirmados);
		L->itens[i].confirmados[j - 1] = ',';
		j = strlen(L->itens[i].mortes);
		L->itens[i].mortes[j - 1] = ',';

		fprintf(
			arquivo,
			"%s%s%s%s%s%s%s%s\n",
			L->itens[i].provincia,
			L->itens[i].pais,
			L->itens[i].latitude,
			L->itens[i].longitude,
			L->itens[i].data,
			L->itens[i].confirmados,
			L->itens[i].mortes,
			L->itens[i].recuperados);

		// retorna o espaco no final das strings
		j = strlen(L->itens[i].provincia);
		L->itens[i].provincia[j - 1] = ' ';
		j = strlen(L->itens[i].pais);
		L->itens[i].pais[j - 1] = ' ';
		j = strlen(L->itens[i].latitude);
		L->itens[i].latitude[j - 1] = ' ';
		j = strlen(L->itens[i].longitude);
		L->itens[i].longitude[j - 1] = ' ';
		j = strlen(L->itens[i].data);
		L->itens[i].data[j - 1] = ' ';
		j = strlen(L->itens[i].confirmados);
		L->itens[i].confirmados[j - 1] = ' ';
		j = strlen(L->itens[i].mortes);
		L->itens[i].mortes[j - 1] = ' ';
	}

	fclose(arquivo);

	return (0);
}

//-----------FUNCOES DE BUSCA------------

// funcao inicializar: funcao que inicializa a tabela
void inicializar(TABELA *T) {
	int i;

	for (i = 0; i < B; i++) {
		T[i].pos = -1;		// indica que a posicao i esta vazia
		T[i].inicio = NULL; // inicia o ponteiro para uma lista, caso ha
							// colisoes (hash aberto)
	}
}

// funcao h (funcao hash): retorna o valor hash da string pais, neste caso. este
// valor retornado eh usado como endereco para armazenar a informacao na tabela
// hash, cuja a chave eh pais/data
int h(char *pais, char *data) {
	int k = 0, j = 0;

	while (pais[j] != 0) {
		k = k + pais[j];
		j++;
	}

	j = 0;
	while (data[j] != 0) {
		k = k + data[j];
		j++;
	}
	/*for(j=0; j<50; j++){
		k = k + (pais[j] * data[j]);
	}*/
	return ((k) % B);
}

// funcao inserir_hash: insere cada noh na tabela hash
int inserir_hash(TABELA *T, elem *no) {
	int j;
	elem *aux;

	j = h(no->pais, no->data); // calcula o valor hash do noh

	if (T[j].pos ==
		-1) { // se a posicao na tabela tiver vazia, preenche no inicio
		T[j].pos = 0;
		T[j].inicio = no;
	} else { // caso contrario, preenche no final da lista associada a posicao
			 // da tabela
		aux = T[j].inicio;
		while (aux->prox != NULL) {
			aux = aux->prox;
		}
		aux->prox = no;
	}
	return (j);
}

// funcao hash: funcao que insere todos os nohs da lista na tabela hash,
// utilizando da funcao auxiliar inserir_hash
int hash(TABELA *T, LISTA *L) {
	int i;
	for (i = 0; i < L->total; i++) { // percorre toda a lista
		inserir_hash(T, &L->itens[i]);
	}
	return 0;
}

// funcao buscar: recebe do usuario um pais e uma data e informa tudo sobre o
// pais no dia desejado
void buscar(TABELA *T) {
	int j, k, achou = 0, tam;
	char data[50], pais[50], c;
	elem *aux;

	// pega os dados com o usuario
	printf("Digite o pais/regiao: ");
	scanf("%s", pais);
	tam = strlen(pais);
	// Do {} while: serve para conseguir ler espaços e considerar tudo como uma
	// string soh
	do {
		scanf("%c", &c);
		pais[tam++] = c;
	} while (c != '\n'); // le a string ate o enter, caso a string tenha espaços
	pais[tam - 1] = ' '; // insere espaço no final
	pais[tam] = 0;		 // garante q a string termina
	printf("Digite a data: ");
	scanf("%s", data);

	// para comparar com os dados na lista, ja que os dados possuem espaco no
	// final
	k = strlen(data);
	data[k] = ' ';   // insire espaco no final
	data[k + 1] = 0; // garante q a string termina

	j = h(
		pais,
		data); // acha o valor da posicao na tabela hash a partir da funcao hash
	aux = T[j].inicio;
	while (aux != NULL) { // percorre a lista associada a posicao j
		// imprime todos os dados que tiverem a mesma data e o mesmo pais
		// informados pelo usuario
		if ((strcmp(aux->pais, pais) == 0) &&
			(compareTo(aux->data, data) == 0)) {
			printf("\nProvincia/Estado: %s\n", aux->provincia);
			printf("Numero de casos: %s\n", aux->confirmados);
			printf("Numero de mortes: %s\n", aux->mortes);
			printf("Numero de recuperados: %s\n", aux->recuperados);
			achou = 1;
		}
		aux = aux->prox;
	}

	if (aux == NULL &&
		achou ==
			0) { // caso nao encontre o pais ou a data informada pelo usuario
		printf("Pais ou data nao encontrados\n");
	}
}

// funcao calculo: funcao auxiliar que recebe duas strings, transforma em
// inteiros e retorna a diferença numerica
int calculo(char *numero1, char *numero2, int caso) {
	int num1, num2, calc;

	// transfere os dados da string em variaveis int
	sscanf(numero1, "%d ", &num1);
	sscanf(numero2, "%d ", &num2);
	if (caso == 1) {
		calc = num2 - num1;
	}

	return calc;
}

// funcao maior_mortes: dado um periodo informado pelo usuario, a funcao imprime
// o pais com a maior quantidade de mortes bem como esta quantidade. Se houver
// empate, imprime a lista de paises
void maior_mortes(LISTA *L, char *data1, char *data2) {
	int i = 0, j = 0, k, maior = 0, dif, soma1 = 0, soma2 = 0, m1, m2;
	elem *aux = &L->itens[0], *aux2;

	// para comparar com os dados na lista, ja que os dados possuem espaco no
	// final
	k = strlen(data1);
	data1[k] = ' ';   // insiro espaco no final
	data1[k + 1] = 0; // garanto que a string finalize
	k = strlen(data2);
	data2[k] = ' ';   // insiro espaco no final
	data2[k + 1] = 0; // garanto que a string finalize

	// ordena por data para facilitar no processo de busca por datas
	ordenar_data(L->itens, 0, L->total);

	// a cada bloco de datas iguais, ordena por pais com o seguinte while
	while (i < L->total) {
		while ((compareTo(L->itens[i].data, L->itens[i + 1].data) == 0) &&
			   (i < L->total - 1)) { // enquanto a data eh a mesma e nao chegou
									 // ao fim do vetor da lista
			i++; // contador que acha ate qual posicao eh a mesma data
		}
		ordenar_pais(
			L->itens, j, i); // chama a funcao para ordenar intervalo desejado
		i++;
		j = i; // inicializa o inicio do proximo noh diferente
	}

	i = 0;
	// se colocar < ai msm q nao tenha a data especifica, ele para de pular
	// quando passar da data,nao?
	while ((i < L->total) && (compareTo(L->itens[i].data, data1) != 0)) {
		i++; // contador que acha a primeira posicao que tem a data inicial do
			 // periodo que o usuario quer
	}
	k = i; // k: inicio da data1;

	if (i == L->total) { // caso i seja igual ao numero maximo de dados, nao
						 // encontrou o inicio do periodo
		printf("Periodo nao encontrado\n");
		return;
	}

	while ((i < L->total) && (compareTo(L->itens[i].data, data1) == 0)) {
		i++;
	} // i vai parar na primeira posicao que nao eh da data1, isto eh, data
	  // inicial do periodo

	j = i; // inicio outro contador a partir de i
	while ((j < L->total) && (compareTo(L->itens[j].data, data2) != 0)) {
		j++; // contador que acha a primeira posicao que tem a data final do
			 // periodo que o usuario quer
	}		 // j: inicio da data2;

	if (j == L->total) { // caso j seja igual ao numero maximo de dados, nao
						 // encontrou o inicio do periodo
		printf("Periodo nao encontrado\n");
		return;
	}

	// k representa a posicao inicial do bloco de datas1
	// j representa a posicao inicial do bloco de data2
	// i representa a posicao final do bloco de data1
	while (k < i) { // quando k = i significa que chegou numa posicao de data
					// diferente de data1
		if (strcmp(L->itens[k].pais, L->itens[k + 1].pais) ==
			0) { // se o pais da posicao k por igual ao pais da proxima posicao:
			while (strcmp(L->itens[k].pais, L->itens[k + 1].pais) ==
				   0) { // enquanto o pais for o mesmo que a proxima posicao:
				sscanf(
					L->itens[k].mortes,
					"%d ",
					&m1); // transformo valor de mortes em int da posicao k
				sscanf(
					L->itens[j].mortes,
					"%d ",
					&m2); // transformo valor de mortes em int da posicao j

				soma1 = soma1 + m1; // soma os valores de acordo com k
				soma2 = soma2 + m2; // soma os valores de acordo com j
				k++;
				j++; // contador das posicoes de data1 e data2, conforme vai
					 // somando
			}
			sscanf(
				L->itens[k].mortes,
				"%d ",
				&m1); // transformo valor de mortes em int da ultima vez q o
					  // pais aparece
			sscanf(L->itens[j].mortes, "%d ", &m2);
			soma1 = soma1 + m1;  // soma os valores de acordo com k
			soma2 = soma2 + m2;  // soma os valores de acordo com j
			dif = soma2 - soma1; // calculo a diferença
		} else { // caso o pais nao eh dividido em provincias, ou seja, so tem
				 // um noh com o nome dele:
			dif = calculo(
				L->itens[k].mortes,
				L->itens[j].mortes,
				1); // calculo a diferenca com auxilio da funcao calculo
		}

		if (dif > maior) { // se a diferenca for maior que a guardada em maior
			maior = dif;   // renovo o valor da minha variavel auxiliar maior
			aux = &L->itens[j]; // inicio uma nova lista guardando o noh
			aux->prox = NULL;
		} else if (dif == maior) { // caso o numero de mortes seja o mesmo
			aux2 = aux->prox;
			while (aux2 != NULL) { // acha o fim da lista
				aux2 = aux2->prox;
			}
			aux2 = &L->itens[j]; // e insere o noh no fim da lista
		}
		k++;
		j++; // contador das posicoes de data1 e data2, conforme o while
		// eu garanto que k e j andam juntos ao ordenar por data e, depois, por
		// pais a cada data. Isso significa que a cada data, estah ordenado por
		// pais, entao k e j seguem as posicoes de afghanistan, albania, algeria
		// e assim por diante, com as datas referentes
	}

	aux2 = aux;
	while (aux2 != NULL) { // percorre toda a lista criada de paises com o mesmo
						   // e maior numero de mortes
		printf("O pais/regiao %scom %d mortes\n", aux2->pais, maior);
		aux2 = aux2->prox;
	}
}

// funcao destruir: desolaca a lista
void destruir(LISTA *L) {
	free(L->itens);
	free(L);
}