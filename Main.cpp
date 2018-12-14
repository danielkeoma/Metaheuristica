#include <stdio.h>
#include <stdlib.h> 
//#include <windows.h>
//#include <conio.h>
#include <iostream>
#include "tp_eletiva.h"
using namespace std;


int main (int argc, char **argv){
    //argumento como entrada
    int temp, malas, particao, aux, opcao = 0, opcao2 = 0;
	printf("%s",argv[1]);
	FILE *arquivo = fopen(argv[1],"r"); 
    if (arquivo== NULL){
        printf("ERRO: arquivo de entrada nao encontrado\n");
        return(EXIT_FAILURE);

    }else{
        
        fscanf(arquivo,"%d %d %d",&temp, &malas, &particao);

        //aloco espaco para os vetores de malas
        int *vetormalas = ((int *)calloc(malas,sizeof(int)));
        //aloco espaco para o vetor solucao
        int *vetorsolucao = ((int *)calloc(malas,sizeof(int)));
        //aloco espaco para o vetor de peso das particao
        int *vetorpesoparticao = ((int *)calloc(particao,sizeof(int)));

        //peso inicial das particao eh zero
        for(int i=0; i<particao; i++){
            vetorpesoparticao[i] = 0;
        }

        for(int i=0; i<malas; i++){
            fscanf(arquivo,"%d",&aux);
            vetormalas[i] = aux;
        }

        //realizo os calculos
        while((opcao < 1) || (opcao > 8)){
            cout << "1 - Solucao Construtiva" << endl << "2 - Solucao Aleatoria" << endl;
            cout << "3 - Best Improvement - Realocacao de particao" << endl << "4 - Best Improvement - Troca de Malas entre 2 particao" << endl;
            cout << "5 - Simulated Annealing" << endl << "6 - Variable Neighborhood Descent" << endl; 
            cout << "7 - Variable Neighborhood Search "<< endl <<"8 - Iterated local Search" << endl << endl;
            cin >> opcao;
            while((opcao < 1) || (opcao > 8)){
                cin >> opcao;
            }
            cout << endl;
            switch(opcao){
                case 1:
                    solucao_construtiva(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                break;
                
                case 2:
                    solucao_aleatoria(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                break;

                case 3:
                    opcao2 = 0;
                    while((opcao2 < 1) || (opcao2 > 2)){
                        cout << "Qual a solucao inicial desejada para o metodo Best Improvement 1?" << endl;
                        cout << "1 - Solucao Construtiva" << endl << "2 - Solucao Aleatoria" << endl << endl;
                        cin >> opcao2;
                        while((opcao2 < 1) || (opcao2 > 2)){
                            cin >> opcao2;
                        }
                        switch(opcao2){
                            case 1:
                                solucao_construtiva(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                            break;

                            case 2:
                                solucao_aleatoria(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                            break;
                        }
                    }
                    best_improvement_1mov(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                break;

                case 4:
                    opcao2 = 0;
                    while((opcao2 < 1) || (opcao2 > 2)){
                        cout << "Qual a solucao inicial desejada para o metodo Best Improvement 2?" << endl;
                        cout << "1 - Solucao Construtiva" << endl << "2 - Solucao Aleatoria" << endl << endl;
                        cin >> opcao2;
                        while((opcao2 < 1) || (opcao2 > 2)){
                            cin >> opcao2;
                        }
                        switch(opcao2){
                            case 1:
                                solucao_construtiva(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                            break;

                            case 2:
                                solucao_aleatoria(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                            break;
                        }
                    }
                    best_improvement_2mov(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                break;

                case 5:
                    opcao2 = 0;
                    while((opcao2 < 1) || (opcao2 > 2)){
                        cout << "Qual a solucao inicial desejada para o metodo Simulatred Annealing?" << endl;
                        cout << "1 - Realocacao" << endl << "2 - Troca" << endl << endl;
                        cin >> opcao2;
                        while((opcao2 < 1) || (opcao2 > 2)){
                            cin >> opcao2;
                        }
                        switch(opcao2){
                            case 1:
                                solucao_aleatoria(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                                best_improvement_1mov(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                            break;

                            case 2:
                                solucao_aleatoria(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                                best_improvement_2mov(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                            break;
                        }
                    }
                    simulated_annealing(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                break;

                case 6: 
                    opcao2 = 0;
                    while((opcao2 < 1) || (opcao2 > 2)){
                        cout << "Qual a solucao inicial desejada para o metodo Variable Neighborhood Descent?" << endl;
                        cout << "1 - Realocacao" << endl << "2 - Troca" << endl << endl;
                        cin >> opcao2;
                        while((opcao2 < 1) || (opcao2 > 2)){
                            cin >> opcao2;
                        }
                        switch(opcao2){
                            case 1:
                                solucao_aleatoria(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                                best_improvement_1mov(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                            break;

                            case 2:
                                solucao_aleatoria(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                                best_improvement_2mov(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                            break;
                        }
                    }
                    variable_neighborhood_descent(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                break;

                case 7:
                    opcao2 = 0;
                    while((opcao2 < 1) || (opcao2 > 2)){
                        cout << "Qual a solucao inicial desejada para o metodo Variable Neighborhood Search?" << endl;
                        cout << "1 - Realocacao" << endl << "2 - Troca" << endl << endl;
                        cin >> opcao2;
                        while((opcao2 < 1) || (opcao2 > 2)){
                            cin >> opcao2;
                        }
                        switch(opcao2){
                            case 1:
                                solucao_aleatoria(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                                best_improvement_1mov(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                            break;

                            case 2:
                                solucao_aleatoria(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                                best_improvement_2mov(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                            break;
                        }
                    }
                    variable_neighborhood_search(vetormalas, vetorsolucao, malas, vetorpesoparticao, particao);
                break;

                default:
                break;
            }
        }    

        //desalocacao de memoria 
        free(vetormalas);
        free(vetorsolucao);
        free(vetorpesoparticao);
    }
    //fecha o arquivo texto
    fclose(arquivo);
    getchar();
    return (EXIT_SUCCESS);
}
