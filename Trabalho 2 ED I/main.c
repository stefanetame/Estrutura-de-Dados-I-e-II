#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalho.h"

int main(void) {
    int op = 0, erro, i, nf = 1, nusp, tam;
    char *nome, **titulos, c;
    ARV *arvore;

    //Aloca-se as variaveis necessarias
    nome = (char*)malloc(sizeof(char)*50);   
    arvore = criar();

    //Opcoes de menu para os usuarios do sistema
    printf("Operacoes disponiveis para o sistema de cadastros:  \n");
    printf("1) Cadastrar aluno \n");
    printf("2) Listar alunos e seus numero usp\n");
    printf("3) Verificar se um aluno X esta cadastrado \n");
    printf("4) Listar todos filmes prediletos dos alunos \n");
    printf("5) Verificar se um filme X esta no cadastro de algum aluno \n");
    printf("6) Identificar algum aluno que tem mais filmes em comum com o aluno X \n");
    printf("7) Identificar algum aluno que tem menos filmes em comum com o aluno X \n");
    printf("8) Produzir um arquivo com as informacoes cadastradas no sistema \n");
    printf("9) Exibir (arvore de cadastros): numero de nos; a altura; maior diferenca de alturas \n");
    printf("10) Retirar algum aluno cadastrado \n");
    printf("11) Inserir filme predileto do aluno X \n");
    printf("12) Remover filme predileto do aluno X \n");
    printf("13) Sair \n");
    
    //menu:
    do {
        printf("O que deseja fazer? (Escolha uma das opcoes acima entre 1 e 13) \n");
        scanf("%d", &op);

        switch (op) {
            //Cada caso representa as funcoes disponiveis com seus respectivos numeros
            case 1: {
                printf("Digite o nome do aluno: ");
                scanf("%s", nome);
                tam = strlen(nome);
                //Do {} while: serve para conseguir ler espaços e considerar tudo como uma string
                do {
                    scanf("%c", &c);
                    nome[tam++] = c;
                } while (c != '\n');
                nome[tam-1] = 0;

                printf("Digite o numero usp do aluno: ");
                scanf("%d", &nusp);

                do{
                    printf("Quantos filmes deseja inserir? (Pelo menos um): ");
                    scanf("%d", &nf);
                }while(nf < 1);

                //Aloca-se a vetor titulos do tamanho que o usuario informar: 
                titulos = (char**)malloc(sizeof(char*)*nf);
                for(i = 0; i < nf; i++){
                    titulos[i] = (char*)malloc(sizeof(char)*50);
                    printf("Digite o filme %d: ", i+1);
                    scanf("%s", titulos[i]);
                    tam = strlen(titulos[i]);
                    //Do {} while: serve para conseguir ler espaços e considerar tudo como uma string
                    do {
                        scanf("%c", &c);
                        titulos[i][tam++] = c;
                    } while (c != '\n');
                    titulos[i][tam-1] = 0;
                }

                //chama a funcao de inserir na arvore do sistema
                erro = inserir(arvore, nusp, nome, titulos, nf); 
                
                if(erro == 0){ //confere o erro que eh retornado da funcao
                    printf("Aluno cadastrado com sucesso\n");
                }
                else{
                    printf("Aluno ja cadastrado\n");
                }

                //Ja desaloca-se o vetor titulos, para poder ser usado novamente no tamanho certo a cada chamada
                for(i = 0; i < nf; i++){
                   free(titulos[i]); 
                }
                free(titulos);

                break;
            }

            case 2: {        
                //chama a funcao que lista os alunos e seus respectivos n usp
                erro = listar_alunos(arvore);

                if(erro == 0){ //confere o erro que eh retornado da funcao
                    printf("Listagem completa com sucesso\n");
                }
                else{
                    printf("Nao ha alunos cadastrados\n");
                }

                break;
            }

            case 3: {    
                printf("Digite o numero usp do aluno a ser procurado\n");
                scanf("%d", &nusp);

                //chama a funcao que verifica se um aluno esta na arvore do sistema
                erro = procura_aluno(arvore, nusp);

                if(erro == 1){ //confere o erro que eh retornado da funcao
                    printf("Este aluno esta cadastrado no sistema\n");
                }
                else{
                    printf("Este aluno nao esta cadastrado no sistema\n");
                }

                break;
            }

            case 4: {
                //chama a funcao que lista os filmes do sistema, sem repeticao
                listar_filmes(arvore);

                break;
            }

            case 5: {
                printf("Digite o filme a ser procurado\n");
                scanf("%s", nome);
                tam = strlen(nome);
                //Do {} while: serve para conseguir ler espaços e considerar tudo como uma string
                do {
                    scanf("%c", &c);
                    nome[tam++] = c;
                } while (c != '\n');
                nome[tam-1] = 0;

                //chama a funcao que verifica se o filme foi encontrado no sistema
                erro = buscar_filme(arvore, nome);

                if(erro == 1){ //confere o erro que eh retornado da funcao
                    printf("Filme encontrado em algum cadastrado\n");
                }
                else{
                    printf("Filme nao encontrado\n");
                }

                break;
            }

            case 6: {
                printf("Digite o numero usp do aluno\n");
                scanf("%d", &nusp);

                //chama a funcao que indica a pessoa com mais filmes em comum 
                indicar_pessoa_mais(arvore, nusp);
                
                break;    
            }

            case 7: {
                printf("Digite o numero usp do aluno\n");
                scanf("%d", &nusp);

                //chama a funcao que indica a pessoa com menos filmes em comum
                indicar_pessoa_menos(arvore, nusp);
                
                break;    
            }

            case 8: {
                //chama a funcao que cria um arquivo com os dados do sistema
                criar_arquivo(arvore);

                break;
            }

            case 9: {
                //chama a funcao que mostra pro usuario informacoes da arvore do sistema
                dados_sistema(arvore); 

                break;
            }

            case 10: {
                printf("Digite o numero usp do aluno a ser retirado\n");
                scanf("%d", &nusp);

                //chama a funcao que retira um aluno da arvore de sistema
                erro = retirar_aluno(arvore, nusp);

                if(erro == 1){ //confere o erro que eh retornado da funcao
                    printf("Aluno nao encontrado no sistema\n");
                }
                else{
                    printf("Aluno removido com sucesso\n");
                }

                break;
            }
    
            case 11: {
                printf("Digite o numero usp do aluno\n");
                scanf("%d", &nusp);
                printf("Digite o titulo do filme a ser inserido\n");
                scanf("%s", nome);
                tam = strlen(nome);
                //Do {} while: serve para conseguir ler espaços e considerar tudo como uma string
                do {
                    scanf("%c", &c);
                    nome[tam++] = c;
                } while (c != '\n');
                nome[tam-1] = 0;

                //chama a funcao de inserir filme em um aluno
                erro = inserir_filme(arvore, nusp, nome);

                if(erro == 1){ //confere o erro que eh retornado da funcao
                    printf("Erro de alocacao\nTente novamente\n");
                }
                else if(erro == 2){
                    printf("Filme ja inserido\n");
                }
                else if(erro == 3){
                    printf("Nao sera possivel inserir, pois nao foi encontrado o cadastro do aluno");
                }
                else{
                    printf("Filme inserido no cadastrado com sucesso\n");
                }

                break;
            }

            case 12: {
                printf("Digite o numero usp do aluno\n");
                scanf("%d", &nusp);
                printf("Digite o titulo do filme a ser removido\n");
                scanf("%s", nome);
                tam = strlen(nome);
                //Do {} while: serve para conseguir ler espaços e considerar tudo como uma string
                do {
                    scanf("%c", &c);
                    nome[tam++] = c;
                } while (c != '\n');
                nome[tam-1] = 0;

                //chama a funcao de remover filme de um aluno
                erro = remover_filme(arvore, nusp, nome);

                if(erro == 2){ //confere o erro que eh retornado da funcao
                    printf("Filme nao pode ser retirado pois so ha um cadastrado no sistema\n");
                }
                else if(erro == 1){
                    printf("Nao foi possivel remover o filme\n");
                }
                else if(erro == 3){
                    printf("Nao sera possivel remover, pois nao foi encontrado o cadastro do aluno");
                }
                else{
                    printf("Remocao feita com sucesso\n");
                }

                break;
            }

            case 13: {
                //finaliza o programa
                printf("Obrigado por usar o nosso sistema de cadastro! \n");

                return(13);
            }

            default: {
                printf("Operacao invalida.");
                printf("Tente uma das opcoes validas (1 a 13).\n");

                break;
            }
        }  
    } while (op != 13);

    //desolaca-se a variavel nome e arvore usada para o sistema
    free(nome);
    destroi(arvore); 
      
    return (0);
}