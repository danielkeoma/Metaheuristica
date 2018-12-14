#ifndef TP_ELETIVA_H
#define TP_ELETIVA_H

int comparacao(const void*, const void*);
void imprime(int*, int);
int verificamenorparticao(int *, int);
int verificamaiorparticao(int *, int);
int funcaoObjetivo(int *, int, int *, int);
void solucao_construtiva(int*, int*, int, int*, int);
void solucao_aleatoria(int*, int*, int, int*, int);
void best_improvement_1mov(int*, int*, int, int*, int);
void troca(int*, int*, int, int*, int);
void best_improvement_2mov(int*, int*, int, int*, int);
void substituicao(int*, int*, int, int*, int);
void simulated_annealing(int*, int*, int, int*, int);
void variable_neighborhood_descent(int*, int*, int, int*, int);
void variable_neighborhood_search(int*, int*, int, int*, int);


#endif
