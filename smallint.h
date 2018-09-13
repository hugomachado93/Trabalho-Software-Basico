#include <stdio.h>

typedef unsigned VetSmallInt;

/* Cria um vetor de SmallInt a partir dos valores fornecidos */
VetSmallInt vs_new(int val[]);

/* Soma dois vetores de Small Int */
VetSmallInt vs_add(VetSmallInt v1, VetSmallInt v2);

/* Imprime um vetor de Small Int */
void vs_print(VetSmallInt v);

/* Shift lógico para a direita */
VetSmallInt vs_shr(VetSmallInt v, int n);

/* Shift aritmético para a direita */
VetSmallInt vs_sar(VetSmallInt v, int n);

/* Shift para a esquerda */
VetSmallInt vs_shl(VetSmallInt v, int n);

/* Lê um vetor de small ints */
VetSmallInt vs_read(FILE *f);

/* Grava um vetor de small ints */
int vs_write(VetSmallInt v, FILE *f);

/* Função auxiliar para por em bigendian */
void dump1(void *p, int n, unsigned char vet[]);

