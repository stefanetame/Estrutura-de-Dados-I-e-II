#include <stdio.h>
#include <string.h>
#include "tad.h"

int main(void) {
    int caso, tam, erro, i, v;
    char nome[30], amigo[30], c;

    printf("/// ---  REDE SOCIAL DE \"AMIZADE VERDADEIRA\" ---///\n\n");
    Grafo *G = ler_arquivo(&erro); //le o arquivo de dados, cria um grafo e insere os dados no grafo
    if(erro == 1){
        printf("Erro ao ler arquivo");
    }

    //ve qual usuario esta acessando o sistema
    v = log_in (G, nome);

    do{
        //Interface: opcoes para o usuario
        printf("\nCaro(a) %s, suas opcoes sao:", nome);
        printf("\n  1)  Fazer um convite de amizade");
        printf("\n  2)  Ver solicitacoes de amizade para aceitar ou recusar");
        printf("\n  3)  Ver sugestoes de amigos verdadeiros");
        printf("\n  4)  Consultar amigos que nao sao amigos verdadeiros");
        printf("\n  5)  Encontrar namorade ideal");
        printf("\n  6)  Ver listas de amigos");
        printf("\n  7)  Trocar de perfil");
        printf("\n  8)  Encerrar programa");
        printf("\n\nO que deseja fazer?\n");
        printf("Sua resposta: ");
        scanf("%d", &caso);

        switch (caso){
            case 1:{
                fazer_convite(G,v);
                break;
            }

            case 2:{
                ver_solicitacoes(G, v);
                break;
            }

            case 3:{
                sugestoes(G, v);
                break;
            }

            case 4:{
                amigos_nao_verdadeiros(G, v);
                break;
            }

            case 5:{
                namorade_ideal(G, v);
                break;
            } 

            case 6:{
                lista_amigos(G, v);
                break;
            } 

            case 7:{
                v = log_in(G, nome);
                break;
            }

            //caso 8: finaliza o programa
            case 8:{
                printf("\nAté logo\n");
                break;
            }
                        
            default:{
                printf("\nErro. Tente novamente.\n");
                break;
            }
        }
        printf("\n");
    }while(caso!=8);

    liberar_memoria(G); //libera memoria que o grafo alocou

    return 0;
}