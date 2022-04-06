#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tad.h"

int main(void) {
    LISTA *L;
    TABELA T[B];
    int erro, caso, i, teste;
    double TEMPO=0;
    char data[50], data2[50];

    //inicializa a lista e a tabela hash utilizadas para armazenar os dados
    L = criar();
    inicializar(T);

    //chama a funcao ler_arquivo que insere todos os dados do arquivo na lista
    erro = ler_arquivo(L);
    if(erro == 1){ //confere se leu e inseriu na lista corretamente 
        printf("Erro ao ler o arquivo\n");
    }

    do{
        //Interface: opcoes para o usuario
        printf("Caro usuario, suas opcoes sao:");
        printf("\n  1)  Ordenar com metodo simples");
        printf("\n  2)  Ordenar com metodo complexo");
        printf("\n  3)  Gerar arquivo da ordenacao");
        printf("\n  4)  Consultar numero de casos, mortes e curas por pais/regiao e data");
        printf("\n  5)  Verificar qual pais teve o maior numero de mortos em determinado tempo");
        printf("\n  6)  Encerrar programa");
        printf("\n\nO que deseja fazer?\n");
        printf("Sua resposta: ");
        scanf("%d", &caso);

        switch (caso){
            //caso 1: ordena os dados com um metodo simples (insertion sort: algoritmo simples), porem de maior complexidade de tempo
            case 1:{
                TEMPO = ordenar_simples(L);
                printf("Concluido em %.2lfs\n", TEMPO);
                break;
            }

            //caso 2: ordena os dados com um metodo avancado (quick sort: algoritmo complexo), porem de menor complexidade de tempo
            case 2:{
                TEMPO = ordenar_avancado(L);
                printf("Concluido em %.2lfs\n", TEMPO);
                break;
            }

            //caso 3: gera um arquivo a partir dos dados armazenados na lista
            case 3:{
                erro = imprimir(L, TEMPO);
                if(erro == 1){
                    printf("Erro ao gerar o arquivo\n");
                }
                else{
                    printf("Concluido\n\n");
                }
                break; 
            }

            //caso 4: consulta nos dados da lista um determinado pais/regiao e uma determinada data informados pelo usuario e mostra quantos casos, mortes e curas teve no dia neste local.
            case 4:{
                //chama a funcao hash que insere todos os dados da lista (que sao todos os dados do arquivo) e insere na tabela hash
                erro = hash(T, L);
                if(erro == 1){ //confere se inseriu na tabela corretamente
                    printf("Erro ao armazenar\n");
                }
                buscar(T);
                printf("\nConcluido\n\n");
                break; 
            }

            //caso 5: mostra o pais/regiao com a maior quantidade de mortes e a quantidade de mortes em um determinado tempo informado pelo usuario
            case 5:{
                printf("Digite a data inicial(modelo: M/D/AA): ");
                scanf("%s", data);
                printf("Digite a data final(modelo: M/D/AA): "); 
                scanf("%s", data2); 
                maior_mortes(L, data, data2);
                printf("Concluido\n\n");
                break;
            } 

            //caso 6: finaliza o programa
            case 6:{
                printf("\nAté logo\n");
                break;
            }
                
            default:{
                printf("\nErro. Tente novamente.\n");
                break;
            }
        }
    }while(caso!=6);

    //chama a funcao destruir que realiza free no ponteiro da lista
    destruir(L);

    return 0;
}