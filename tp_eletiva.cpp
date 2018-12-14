#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <iostream>
#include "tp_eletiva.h"
using namespace std;

int comparacao(const void *a, const void *b){
    return( *(int*)b - *(int*)a );
}

void imprime(int *vetor, int n){
    //imprimo na tela
    for(int i=0; i<n; i++){
        cout << vetor[i] << " ";
    }
    cout << endl;
}

int verificamenorparticao(int *vetor, int n){
    int menor, particao;
    //menor vai ser a primeira particao de malas que sera usada para comparacao
    menor = vetor[0];
    particao = 0;

    //faco a verificacao
    for(int i=1; i<n; i++){
        if(vetor[i] < menor){
            menor = vetor[i];
            particao = i;
        }
    }
    return particao;
}

int verificamaiorparticao(int *vetor, int n){
    int maior, particao;
    //maior vai ser a primeira particao de malas que sera usada para comparacao
    maior = vetor[0];
    particao = 0;

    //faco a verificacao
    for(int i=1; i<n; i++){
        if(vetor[i] > maior){
            maior = vetor[i];
            particao = i;
        }
    }
    return particao;
}

int funcaoObjetivo(int *vetormalas, int malas, int *vetorpeso, int particoes){
    int x = verificamenorparticao(vetorpeso, particoes);
    int y = verificamaiorparticao(vetorpeso, particoes);
    return(vetorpeso[y] - vetorpeso[x]);
}

void solucao_construtiva(int *vetormalas, int *vetorsolucao, int malas, int *vetorpeso, int particoes){
    //ordeno decrescentemente
    qsort (vetormalas, malas, sizeof(int), comparacao);

    int x = verificamenorparticao(vetorpeso, particoes);

    for(int i=0; i<malas; i++){
        //calcular o menor peso das particoes
        x = verificamenorparticao(vetorpeso, particoes);
        
        //incrementar nela a mala, ou seja:
        //alocar a mala mais pesada ainda não alocada à partição com menor peso
        vetorsolucao[i] = x;
        
        //incremento no peso da particao o peso desta mala
        vetorpeso[x] += vetormalas[i];
    }
    cout << endl << "------------------------------------------------------" << endl;
    cout << endl << "Solucao inicial construtiva" << endl;
    cout << endl << "------------------------------------------------------" << endl;
    imprime(vetorsolucao, malas);

    cout << endl << "Peso das particoes" << endl;
    imprime(vetorpeso, particoes);

    x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
    cout << endl <<"Funcao Objetivo = "<< x << endl << endl;
}

void solucao_aleatoria(int *vetormalas, int *vetorsolucao, int malas, int *vetorpeso, int particoes){
    //ordeno decrescentemente
    qsort (vetormalas, malas, sizeof(int), comparacao);

    //faco uma solucao aleatoria para as particoes
    srand(time(NULL));
    for(int i=0; i<malas; i++){
        vetorsolucao[i] = rand()%particoes+0;
        //atualizo o vetor de peso da particao que foi gerada com a mala da posicao i
        vetorpeso[vetorsolucao[i]] += vetormalas[i];
    }
    cout << endl << "------------------------------------------------------" << endl;
    cout << endl << "Solucao Aleatoria" << endl;
    cout << endl << "------------------------------------------------------" << endl;
    imprime(vetorsolucao, malas);

    cout << endl << "Peso das particoes" << endl;
    imprime(vetorpeso, particoes);

    int x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
    cout << endl <<"Funcao Objetivo = "<< x << endl << endl;
}

void best_improvement_1mov(int *vetormalas, int *vetorsolucao, int malas, int *vetorpeso, int particoes){
    int particao_original, x, y;
    //laco para percorrer todas as malas
    for(int i=0; i<malas; i++){
        //salvo a particao original da mala da posicao i
        particao_original = vetorsolucao[i];
        //laco para percorrer todas as particoes
        for(int j=0; j<particoes; j++){
            //verifico a funcao objetivo atual
            x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
            //coloco o if para nao entrar na solucao inicial ja gerada anteriormente e descartar operacoes desnecessarias
            if(vetorsolucao[i] != j){
                //peso na particao original sera o peso menos o peso da mala da posicao i
                vetorpeso[particao_original] -= vetormalas[i];

                //peso na particao de destino sera o peso mais o peso da mala da posicao i
                vetorpeso[j] += vetormalas[i];

                y = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
                //se a funcao objetivo da vizinhanca for melhor que o atual, eu altero o vetor de solucao com a vizinhanca atual
                if(y < x){
                    //altero o vetor solucao com a particao destino (j) da mala na posicao i
                    vetorsolucao[i] = j;
                    //atualizo a particao original
                    particao_original = j;
                }
                //senao eu desfaco as alteracoes feitas
                else{
                    vetorpeso[particao_original] += vetormalas[i];
                    vetorpeso[j] -= vetormalas[i];
                }
            }
            
        }
        //volto a mala da posicao i para a sua particao inicial
        //caso seja feita algmuma melhora eu salvo a particao inicial acima
        vetorsolucao[i] = particao_original;
    }
    cout << endl << "------------------------------------------------------" << endl;
    cout << endl << "Best Improvement - 1 Movimento - Realocacao de particao" << endl;
    cout << endl << "------------------------------------------------------" << endl;
    imprime(vetorsolucao, malas);

    cout << endl << "Peso das particoes" << endl;
    imprime(vetorpeso, particoes);

    x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
    cout << endl <<"Funcao Objetivo = "<< x << endl << endl;
}

void troca(int *vetormalas, int *vetorsolucao, int malas, int *vetorpeso, int particoes){
    int particao_original, x, y;
    //laco para percorrer todas as malas
    for(int i=0; i<malas; i++){
        //salvo a particao original da mala da posicao i
        particao_original = vetorsolucao[i];
        //laco para percorrer todas as particoes
        for(int j=0; j<particoes; j++){
            //verifico a funcao objetivo atual
            x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
            //coloco o if para nao entrar na solucao inicial ja gerada anteriormente e descartar operacoes desnecessarias
            if(vetorsolucao[i] != j){
                //peso na particao original sera o peso menos o peso da mala da posicao i
                vetorpeso[particao_original] -= vetormalas[i];

                //peso na particao de destino sera o peso mais o peso da mala da posicao i
                vetorpeso[j] += vetormalas[i];

                y = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
                //se a funcao objetivo da vizinhanca for melhor que o atual, eu altero o vetor de solucao com a vizinhanca atual
                if(y < x){
                    //altero o vetor solucao com a particao destino (j) da mala na posicao i
                    vetorsolucao[i] = j;
                    //atualizo a particao original
                    particao_original = j;
                }
                //senao eu desfaco as alteracoes feitas
                else{
                    vetorpeso[particao_original] += vetormalas[i];
                    vetorpeso[j] -= vetormalas[i];
                }
            } 
        }
        //volto a mala da posicao i para a sua particao inicial
        //caso seja feita algmuma melhora eu salvo a particao inicial acima
        vetorsolucao[i] = particao_original;
    } 
}

void best_improvement_2mov(int *vetormalas, int *vetorsolucao, int malas, int *vetorpeso, int particoes){
    int x, y, aux; 
    //laco para percorrer todas as malas
    for(int i=0; i<malas-1; i++){

        //laco para percorrer todas as malas (para realizar a troca)
        for(int j=i+1; j<malas; j++){

            x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
            //verifico se as particoes sao diferentes para realizar a troca
            if(vetorsolucao[i] != vetorsolucao[j]){
                
                //subtraio do vetor de pesos a mala da posicao i
                vetorpeso[vetorsolucao[i]] -= vetormalas[i];
                //subtraio do vetor de pesos a mala da posicao j
                vetorpeso[vetorsolucao[j]] -= vetormalas[j];

                //incremento no vetor de pesos a mala de peso j
                vetorpeso[vetorsolucao[i]] += vetormalas[j];
                //incremento no vetor de pesos a mala de peso j
                vetorpeso[vetorsolucao[j]] += vetormalas[i];

                //realizo a troca
                aux = vetorsolucao[i];
                vetorsolucao[i] = vetorsolucao[j];
                vetorsolucao[j] = aux;

                //verifico a solucao objetivo atual
                y = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);

                if(y > x){
                    //desfaco a troca
                    aux = vetorsolucao[i];
                    vetorsolucao[i] = vetorsolucao[j];
                    vetorsolucao[j] = aux;

                    //desfaco os incrementos e subtracoes feitas anteriormente
                    vetorpeso[vetorsolucao[i]] -= vetormalas[j];
                    vetorpeso[vetorsolucao[j]] -= vetormalas[i];

                    vetorpeso[vetorsolucao[i]] += vetormalas[i];
                    vetorpeso[vetorsolucao[j]] += vetormalas[j];    
                }
            }
        }
    }
    cout << endl << "------------------------------------------------------" << endl;
    cout << endl << "Best Improvement - 2 Movimentos - Troca de malas entre 2 particoes" << endl;
    cout << endl << "------------------------------------------------------" << endl;
    imprime(vetorsolucao, malas);

    cout << endl << "Peso das particoes" << endl;
    imprime(vetorpeso, particoes);

    x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
    cout << endl <<"Funcao Objetivo = "<< x << endl << endl;
}

void substituicao(int *vetormalas, int *vetorsolucao, int malas, int *vetorpeso, int particoes){
    int x, y, aux; 
    //laco para percorrer todas as malas
    for(int i=0; i<malas-1; i++){

        //laco para percorrer todas as malas (para realizar a troca)
        for(int j=i+1; j<malas; j++){

            x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
            //verifico se as particoes sao diferentes para realizar a troca
            if(vetorsolucao[i] != vetorsolucao[j]){
                
                //subtraio do vetor de pesos a mala da posicao i
                vetorpeso[vetorsolucao[i]] -= vetormalas[i];
                //subtraio do vetor de pesos a mala da posicao j
                vetorpeso[vetorsolucao[j]] -= vetormalas[j];

                //incremento no vetor de pesos a mala de peso j
                vetorpeso[vetorsolucao[i]] += vetormalas[j];
                //incremento no vetor de pesos a mala de peso j
                vetorpeso[vetorsolucao[j]] += vetormalas[i];

                //realizo a troca
                aux = vetorsolucao[i];
                vetorsolucao[i] = vetorsolucao[j];
                vetorsolucao[j] = aux;

                //verifico a solucao objetivo atual
                y = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);

                if(y > x){
                    //desfaco a troca
                    aux = vetorsolucao[i];
                    vetorsolucao[i] = vetorsolucao[j];
                    vetorsolucao[j] = aux;

                    //desfaco os incrementos e subtracoes feitas anteriormente
                    vetorpeso[vetorsolucao[i]] -= vetormalas[j];
                    vetorpeso[vetorsolucao[j]] -= vetormalas[i];

                    vetorpeso[vetorsolucao[i]] += vetormalas[i];
                    vetorpeso[vetorsolucao[j]] += vetormalas[j];    
                }
            }
        }
    } 
}

void simulated_annealing(int *vetormalas, int *vetorsolucao, int malas, int *vetorpeso, int particoes){ /////arrumar
    int particao_original, x, y;
    /*
    para escolher um vizinho qualquer de uma solução,
    basta primeiramente escolher aleatoriamente uma vizinhança
    // * /
    solucao inicial = 

    */
    for(int i=0; i<malas; i++){
        
        //laco para percorrer todas as particoes
        for(int j=0; j<particoes; j++){
            //verifico a funcao objetivo atual
            x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
            //coloco o if para nao entrar na solucao inicial ja gerada anteriormente e descartar operacoes desnecessarias
            if(vetorsolucao[i] != j){
                //peso na particao original sera o peso menos o peso da mala da posicao i
                vetorpeso[particao_original] -= vetormalas[i];

                //peso na particao de destino sera o peso mais o peso da mala da posicao i
                vetorpeso[j] += vetormalas[i];

                y = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
                //se a funcao objetivo da vizinhanca for melhor que o atual, eu altero o vetor de solucao com a vizinhanca atual
                if(y < x){
                    //altero o vetor solucao com a particao destino (j) da mala na posicao i
                    vetorsolucao[i] = j;
                    //atualizo a particao original
                    particao_original = j;
                }
                //senao eu desfaco as alteracoes feitas
                else{
                    vetorpeso[particao_original] += vetormalas[i];
                    vetorpeso[j] -= vetormalas[i];
                }
            }
            
        }
        //volto a mala da posicao i para a sua particao inicial
        //caso seja feita algmuma melhora eu salvo a particao inicial acima
        vetorsolucao[i] = particao_original;
    }

    cout << endl << "------------------------------------------------------" << endl;
    cout << endl << "Simulated Annealing" << endl;
    cout << endl << "------------------------------------------------------" << endl;
    imprime(vetorsolucao, malas);

    cout << endl << "Peso das particoes" << endl;
    imprime(vetorpeso, particoes);

    x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
    cout << endl <<"Funcao Objetivo = "<< x << endl << endl;
}

void variable_neighborhood_descent(int *vetormalas, int *vetorsolucao, int malas, int *vetorpeso, int particoes){
    int x;

    //substituicao
    substituicao(vetormalas, vetorsolucao, malas, vetorpeso, particoes);
    //troca
    troca(vetormalas, vetorsolucao, malas, vetorpeso, particoes);
    
    x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);

    cout << endl << "------------------------------------------------------" << endl;
    cout << endl << "Variable Neighborhood Descend" << endl;
    cout << endl << "------------------------------------------------------" << endl;
    imprime(vetorsolucao, malas);

    cout << endl << "Peso das particoes" << endl;
    imprime(vetorpeso, particoes);

    x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
    cout << endl <<"Funcao Objetivo = "<< x << endl << endl;
}

void variable_neighborhood_search(int *vetormalas, int *vetorsolucao, int malas, int *vetorpeso, int particoes){////////// arrumar (ta igual o vnd)
    int x;
    //substituicao
    substituicao(vetormalas, vetorsolucao, malas, vetorpeso, particoes);
    //troca
    troca(vetormalas, vetorsolucao, malas, vetorpeso, particoes);
    
    x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);

    cout << endl << "------------------------------------------------------" << endl;
    cout << endl << "Variable Neighborhood Descend" << endl;
    cout << endl << "------------------------------------------------------" << endl;
    imprime(vetorsolucao, malas);

    cout << endl << "Peso das particoes" << endl;
    imprime(vetorpeso, particoes);

    x = funcaoObjetivo(vetormalas, malas, vetorpeso, particoes);
    cout << endl <<"Funcao Objetivo = "<< x << endl << endl;
}