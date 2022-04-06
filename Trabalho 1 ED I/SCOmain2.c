								//          SCC0223 - Estrutura de Dados 1          //
								//      Trabalho 1: Sistema de Compra Online (SCO)   //
		//  Alunos: Anderson Lavinscky, n°USP 9045195; Joao Bienotti, n°USP 11218452; Stefane Oliveira, n°USP 10829970.  //


			//  Versao: Dinamica-Encadeada  //


//  Interface Main  //



//Bibliotecas utilizadass neste trabalho:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SCO_TAD2.h"



//Declaracao de variavel:
#define TAM 20



// Codigo principal //

int main(){
    //Declaracao de variaveis utilizadas
    int erro = 0, op = 0;
    elem_p valor = 0;                   
    elem_f *nome;
    elem_l *produtos;     
    LDEnc *L_prod;       

    L_prod = criarL();

    nome = (elem_f*)malloc(sizeof(elem_f)*TAM);
    produtos = (elem_l*)malloc(sizeof(elem_l)*TAM);
    
       
    do {

		menuOpcoes();

		printf("\n	O que deseja fazer? (Escolha uma das opcoes acima entre 1 e 8) \n");
        scanf("%d", &op);		//Entrando com a opcao do menu

        switch (op) {			//Tratando a entrada da opcao

            case 1: { 

				printf("	Entre com o nome do produto:  ");
                scanf("%s", produtos);       
                
				//Insere um produto na lista de forma ordenada   
                inserir_produto(L_prod, produtos, &erro);		

                if(erro == 2){
					printf("	Produto ja cadastrado. \n ");
					printf("	Favor colocar um outro produto. \n\n");
                }
                else{
					printf("	Produto cadastrado com sucesso! \n");
                }

                break;
            }

            case 2: {

                do {
					printf("	Entre com o nome do produto:  ");
                    scanf("%s", produtos); 
                    
					//Remove um produto da lista           
                    Remover_LDEnc(L_prod, produtos, &erro);
                    
                    if (erro == 1) {
						printf("	Produto nao cadastrado. \n ");
						printf("	Favor entrar com um outro produto; se a opcao 4. \n\n");
                    }
                    else {
                        printf("	Produto retirado com sucesso! \n");
                    }
                } while (erro == 1);

                break;
            }

            case 3: {  

                printf("	Entre com o seu nome: ");          
                scanf("%s", nome);                      //Armazenando nome

                printf("	Entre com o nome do produto: ");
                scanf("%s", produtos);                    //Armazenando produto

                printf("	Entre com o valor do lance: ");
                scanf("%elem_p", &valor);                     //Armazenando valor

                //Insere o lance e o nome da pessoa para o produto selecionado
                inserir_lance(L_prod, produtos, valor, nome, &erro);

                while (erro == 2) {
                    printf("\n	Seu lance pela %s não foi aceito. Você precisa dar um lance maior!\n", produtos);
                    printf("	Entre com um novo valor do lance: ");
                    scanf("%elem_f", &valor);
                    
					//Inserir/tratar o valor do lance, que deve ser maior ou igual ao anterior, e inserir nome da pessoa para o produto selecionado
                    inserir_lance(L_prod, produtos, valor, nome, &erro);
                }

                if (erro == 3) {
                    printf("Produto nao encontrado na lista\n");
                }

                if (erro == 0) {
                    printf("Lance dado com sucesso! \n");
                }

                break;
            }

            case 4: {

                listar_produtos(L_prod, &erro);   

                if (erro == 1) {
                    printf("	Nao ha produto. \n");
                }
                else {
                    printf("	Listagem completa! \n");                
                }

                break;
            }

            case 5: {

                printf("	Entre com o seu nome:  ");
                scanf("%s", nome);
                recomendacao(L_prod, nome);     

                break;
            }

            case 6: {
                encerrarLeilao(L_prod);   //Mostra: usuario(s) e o lance ganhador p/ cada produto; reinicializa o sistema
                
                break;
            }

            case 7: {

                ajuda();

                break;
            }

            case 8: {

                printf("	Obrigado por usar nosso programa\n");

                break;
            }

            default: {

                printf("	Operacao invalida.");
                printf("	Tente uma das opcoes validas (1 a 8).\n");

                break;
            }
        }    
    } while (op != 8);
      
    return(0);
}