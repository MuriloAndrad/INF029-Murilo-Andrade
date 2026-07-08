#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct {
    int *auxiliar;
    int tamanho;
    int quantidade;
} Estrutura;

Estrutura vetorPrincipal[TAM];

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    if (posicao < 1 || posicao > 10)
    {
        return POSICAO_INVALIDA;
    }
    else
    {
        return SUCESSO;
    }
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/
void inicializar()
{
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i].auxiliar = NULL;
        vetorPrincipal[i].tamanho = 0;
        vetorPrincipal[i].quantidade = 0;
    }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (tamanho < 1) return TAMANHO_INVALIDO;
    if (vetorPrincipal[posicao - 1].auxiliar != NULL) return JA_TEM_ESTRUTURA_AUXILIAR;

    vetorPrincipal[posicao - 1].auxiliar = (int *)malloc(tamanho * sizeof(int));
    if (vetorPrincipal[posicao - 1].auxiliar == NULL) return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[posicao - 1].tamanho = tamanho;
    vetorPrincipal[posicao - 1].quantidade = 0;

    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].auxiliar == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao - 1].quantidade >= vetorPrincipal[posicao - 1].tamanho) return SEM_ESPACO;

    int qtd = vetorPrincipal[posicao - 1].quantidade;
    vetorPrincipal[posicao - 1].auxiliar[qtd] = valor;
    vetorPrincipal[posicao - 1].quantidade++;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].auxiliar == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao - 1].quantidade == 0) return ESTRUTURA_AUXILIAR_VAZIA;

    vetorPrincipal[posicao - 1].quantidade--;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].auxiliar == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao - 1].quantidade == 0) return ESTRUTURA_AUXILIAR_VAZIA;

    int i, found = 0;
    int qtd = vetorPrincipal[posicao - 1].quantidade;

    for (i = 0; i < qtd; i++) {
        if (vetorPrincipal[posicao - 1].auxiliar[i] == valor) {
            found = 1;
            break;
        }
    }

    if (!found) return NUMERO_INEXISTENTE;

    for (int j = i; j < qtd - 1; j++) {
        vetorPrincipal[posicao - 1].auxiliar[j] = vetorPrincipal[posicao - 1].auxiliar[j + 1];
    }

    vetorPrincipal[posicao - 1].quantidade--;

    return SUCESSO;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].auxiliar == NULL) return SEM_ESTRUTURA_AUXILIAR;

    int qtd = vetorPrincipal[posicao - 1].quantidade;
    for (int i = 0; i < qtd; i++) {
        vetorAux[i] = vetorPrincipal[posicao - 1].auxiliar[i];
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].auxiliar == NULL) return SEM_ESTRUTURA_AUXILIAR;

    int qtd = vetorPrincipal[posicao - 1].quantidade;
    
    for (int i = 0; i < qtd; i++) {
        vetorAux[i] = vetorPrincipal[posicao - 1].auxiliar[i];
    }

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (vetorAux[j] > vetorAux[j + 1]) {
                int temp = vetorAux[j];
                vetorAux[j] = vetorAux[j + 1];
                vetorAux[j + 1] = temp;
            }
        }
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int idx = 0;
    int temElemento = 0;
    
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].auxiliar != NULL && vetorPrincipal[i].quantidade > 0) {
            temElemento = 1;
            for (int j = 0; j < vetorPrincipal[i].quantidade; j++) {
                vetorAux[idx] = vetorPrincipal[i].auxiliar[j];
                idx++;
            }
        }
    }
    
    if (!temElemento) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }
    
    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int idx = 0;
    int temElemento = 0;
    
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].auxiliar != NULL && vetorPrincipal[i].quantidade > 0) {
            temElemento = 1;
            for (int j = 0; j < vetorPrincipal[i].quantidade; j++) {
                vetorAux[idx] = vetorPrincipal[i].auxiliar[j];
                idx++;
            }
        }
    }
    
    if (!temElemento) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }
    
    for (int i = 0; i < idx - 1; i++) {
        for (int j = 0; j < idx - i - 1; j++) {
            if (vetorAux[j] > vetorAux[j + 1]) {
                int temp = vetorAux[j];
                vetorAux[j] = vetorAux[j + 1];
                vetorAux[j + 1] = temp;
            }
        }
    }
    
    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].auxiliar == NULL) return SEM_ESTRUTURA_AUXILIAR;
    
    int tamanhoAtual = vetorPrincipal[posicao - 1].tamanho;
    int tamanhoFinal = tamanhoAtual + novoTamanho;
    
    if (tamanhoFinal < 1) return NOVO_TAMANHO_INVALIDO;
    
    int *novoAux = (int *)realloc(vetorPrincipal[posicao - 1].auxiliar, tamanhoFinal * sizeof(int));
    if (novoAux == NULL) return SEM_ESPACO_DE_MEMORIA;
    
    vetorPrincipal[posicao - 1].auxiliar = novoAux;
    vetorPrincipal[posicao - 1].tamanho = tamanhoFinal;
    
    if (vetorPrincipal[posicao - 1].quantidade > tamanhoFinal) {
        vetorPrincipal[posicao - 1].quantidade = tamanhoFinal;
    }
    
    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].auxiliar == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao - 1].quantidade == 0) return ESTRUTURA_AUXILIAR_VAZIA;
    
    return vetorPrincipal[posicao - 1].quantidade;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    int temElemento = 0;
    
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].auxiliar != NULL && vetorPrincipal[i].quantidade > 0) {
            temElemento = 1;
            break;
        }
    }
    
    if (!temElemento) return NULL;
    
    No *cabecote = (No *)malloc(sizeof(No));
    if (cabecote == NULL) return NULL;
    cabecote->prox = NULL;
    
    No *atual = cabecote;
    
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].auxiliar != NULL) {
            for (int j = 0; j < vetorPrincipal[i].quantidade; j++) {
                No *novo = (No *)malloc(sizeof(No));
                if (novo != NULL) {
                    novo->conteudo = vetorPrincipal[i].auxiliar[j];
                    novo->prox = NULL;
                    atual->prox = novo;
                    atual = novo;
                }
            }
        }
    }
    
    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    if (inicio == NULL || inicio->prox == NULL) return;
    
    No *atual = inicio->prox;
    int idx = 0;
    
    while (atual != NULL) {
        vetorAux[idx] = atual->conteudo;
        idx++;
        atual = atual->prox;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    if (inicio == NULL || *inicio == NULL) return;
    
    No *atual = *inicio;
    No *prox;
    
    while (atual != NULL) {
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
    
    *inicio = NULL;
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/
void finalizar()
{
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].auxiliar != NULL) {
            free(vetorPrincipal[i].auxiliar);
            vetorPrincipal[i].auxiliar = NULL;
        }
        vetorPrincipal[i].tamanho = 0;
        vetorPrincipal[i].quantidade = 0;
    }
}