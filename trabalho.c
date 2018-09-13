/*Gabriel de Araujo Carvalho 1413294*/
/*Hugo de Barros Pimentel Dultra Machado 1410530*/

#include <stdio.h>
#include <stdlib.h>
#include "smallint.h"

typedef unsigned VetSmallInt;

/* Inicio Função: vs_new */
VetSmallInt vs_new(int vet[]){
	int ov[4];
	unsigned int smallInt = 0;
	int i, j;
	int intn[4];
	
	/*Fazendo o deslocamento do vetor*/
	
	for(i=0,j=18;i<4;i++,j-=6)
		intn[i] = vet[i] << j;

	/*Teste para, caso de overflow, sera alocado no vetor*/

	for(i=0;i<4;i++){
		if(vet[i] > 63)
			ov[i] = 1;
		else 
			ov[i] = 0;
	}

	/*Arrumando o Inteiro*/

	
	intn[0] = intn[0] & 0xfc0000;
	intn[1] = intn[1] & 0x3f000;
	intn[2] = intn[2] & 0xfc0;
	intn[3] = intn[3] & 0x3f;
	

	/*Deslocando o ov para o local correto*/

	for(i=0,j=31;i<4;i++,j--)
		ov[i] = ov[i] << j;
	
	/*Fazendo a junção entre os ov's e os inteiros*/

	for(i=0;i<4;i++){
		smallInt = smallInt | ov[i];
		smallInt = smallInt | intn[i];
	}

	return smallInt;
} /* Fim Função: vs_new */


/* Inicio Função: dump */
void dump(void *p, int n){
	unsigned char *p1 = p;
	while(n--){
		printf("%p - %02x\n", p1, *p1);
		p1++;
	}
}/* Fim Função: dump */


/* Inicio Função Auxiliar: dump1 */
//função usada na vs_write
void dump1(void *p, int n, unsigned char vet[])
{

	unsigned char *p1 = p;
	while(n--){
		vet[n] = *p1;
		p1++;
	}
}/* Fim Função: dump1 */



/* Inicio Função: vs_add */
VetSmallInt vs_add(VetSmallInt v1, VetSmallInt v2){
	
	int i,j;

	VetSmallInt intv1[4];
	VetSmallInt intv2[4];
	VetSmallInt ov[4];
	VetSmallInt somaInt[4];
	VetSmallInt total = 0;

	/*Colocando cada inteiro no seu respectivo vetor*/

	intv1[3] = v1 & 0x3f;
	intv1[2] = v1 & 0xfc0;
	intv1[1] = v1 & 0x3f000;
	intv1[0] = v1 & 0xfc0000;
	
	intv2[3] = v2 & 0x3f;
	intv2[2] = v2 & 0xfc0;
	intv2[1] = v2 & 0x3f000;
	intv2[0] = v2 & 0xfc0000;


/*Usando shift a direta para fazer a soma dos inteiros 0 1 2 3*/ 

	for(i=0,j=18;i<4;i++,j-=6){
		intv1[i] = intv1[i] >> j;
		intv2[i] = intv2[i] >> j;
	}

	/*Fazendo a soma dos inteiross de cada smallInt e mostrando se ocorre overflow ou nao*/

	for(i=0;i<4;i++){
		somaInt[i] = intv1[i] + intv2[i];
		if(somaInt[i] > 63)
			ov[i] = 1;
		else 
			ov[i] = 0;		
	}

	/*Ajeitando os inteiros e overflows com shift*/

	for(i=0,j=18;i<4;i++,j-=6)
		somaInt[i] = somaInt[i] << j; 
	
	for(i=0,j=31;i<4;i++,j--)
		ov[i] = ov[i] << j;
	
	/*Arrumando os Inteiros*/
	
	somaInt[0] = somaInt[0] & 0xfc0000;
	somaInt[1] = somaInt[1] & 0x3f000;
	somaInt[2] = somaInt[2] & 0xfc0;
	somaInt[3] = somaInt[3] & 0x3f;

	/*Fazendo a junção de todos os vetores de inteiros e overflows para virar um novo VetSmallInt*/

	for(i=0;i<4;i++){
		total = total | somaInt[i];
		total = total | ov[i];
	}

	return total;
} /* Fim Função: vs_add */


/* Inicio Função: vs_print */
void vs_print(VetSmallInt v){
	
	int i,j;
	VetSmallInt testaov;
	int imprimeint;
	VetSmallInt corrigeInt[4];

	/*Confirma se ocorreu overflow e printa os resultados*/

    printf("Overflow:\t");

	for(i=0;i<4;i++){
		testaov=v;
		testaov = testaov << i;
		testaov = testaov >> 31;
		if(testaov == 0)
			printf("nao");
		else
			printf("sim");
		printf("\t");
	}
	printf("\n");

	/*Corrige os inteiros para terem apenas os bits originais e shifita cada um deles j vezes para a direita, para poderem estar nas 6 primeiras posições, sem zero antes*/
	
	corrigeInt[0] = v & 0xfc0000;
	corrigeInt[1] = v & 0x3f000;
	corrigeInt[2] = v & 0xfc0;
	corrigeInt[3] = v & 0x3f;
	
	for(i=0,j=18;i<4,j>0;i++,j-=6)
		corrigeInt[i] = corrigeInt[i] >> j;
	

	/*Printa cada um dos inteiros como decimal e hexadecimal*/
	
	printf("Valores:\t");
	for(i=8,j=0;i<27,j<4;i+=6,j++){
		imprimeint=v;
		imprimeint = imprimeint << i;
		imprimeint = imprimeint >> 26;
		printf("%d (%x)\t", imprimeint, corrigeInt[j]);
	}	
	printf("\n");

}/* Fim Função: vs_print */


/* Inicio Função: vs_shr */
VetSmallInt vs_shr(VetSmallInt v, int n){
	
	VetSmallInt intn[4];
	int i,j;
	VetSmallInt shr = 0;
	
	/*Separa cada inteiro em um espaço específico do vetor*/

	intn[0] = v & 0xfc0000;
	intn[1] = v & 0x3f000;
	intn[2] = v & 0xfc0;
	intn[3] = v & 0x3f;

	/*Shifta os inteiros para o começo, até que os 6 primeiros bits tenham os 6 bits originais do número e depois shifta n vezes para a direita*/

	for(i=0,j=18;i<4;i++,j-=6)
		intn[i] = intn[i] >> j;
	
	for(i=0;i<4;i++)
		intn[i] = intn[i] >> n;
	
	
	/*Shifta os inteiros de volta ao lugar certo no SmallInt*/

	for(i=0,j=18;i<4;i++,j-=6)
		intn[i] = intn[i] << j;
	

	/*Junta os inteiros em um só VetSmallInt*/
	for(i=0;i<4;i++)
		shr = shr | intn[i];

	return shr;
}/* Fim Função: sh_shr */


/* Inicio Função: vs_shl */
VetSmallInt vs_shl(VetSmallInt v, int n){
	
	VetSmallInt intn[4];
	int i,j;
	VetSmallInt shl = 0;

	/*Separa cada inteiro em um espaço específico do vetor*/

	intn[0] = v & 0xfc0000;
	intn[1] = v & 0x3f000;
	intn[2] = v & 0xfc0;
	intn[3] = v & 0x3f;

	/*Shifta os inteiros para o começo, até que os 6 primeiros bits tenham os 6 bits originais do número e depois shifta n vezes para a esquerda*/

	for(i=0,j=8;i<4;i++,j+=6)
		intn[i] = intn[i] << j;
	
	
	for(i=0;i<4;i++)
		intn[i] = intn[i] << n;
	
	/*Shifta os inteiros de volta ao lugar certo no SmallInt*/	

	for(i=0,j=8;i<4;i++,j+=6)
		intn[i] = intn[i] >> j;

	/*Junta os inteiros em um só VetSmallInt*/

	for(i=0;i<4;i++)
		shl = shl | intn[i];

	return shl;
}/* Fim Função: vs_shl */


/* Inicio Função: vs_sar */
VetSmallInt vs_sar(VetSmallInt v, int n){
	
	VetSmallInt intn[4];
	int i,j;
	VetSmallInt sar = 0;
	
	/*Passa para um vetor de 4 posições cada um dos 4 inteiros*/
	intn[0] = v & 0xfc0000;
	intn[1] = v & 0x3f000;
	intn[2] = v & 0xfc0;
	intn[3] = v & 0x3f;
		
	/*Arruma a posição deles, shifitando-os e deixando com os 6 bits originais*/
	for(i=0,j=18;i<4;i++,j-=6)
		intn[i] = intn[i] >> j;
	
	
	/*For que verifica cada um dos inteiros e faz o shift aritimético*/
	for(i=0;i<4;i++){

	/*Confirma se o byet mais significativo é 1 ou 0*/ 
	    if((intn[i] >> 5 ) == 0x01){ 

	/*Se for 1, shifita 1 para direita n vezes e faz um OU para substituir o 0 por 1*/
	      for(j=0;j<n;j++){ 
		    intn[i]=intn[i] >> 1;
		    intn[i]=intn[i] | 0x20;
		}

	   }	


	/*Shifita para direita normal n vezes*/
	  else  	
		intn[i]=intn[i] >> n; 
	}	

	/*Arruma cada um dos Inteiros para a posição certa*/
	intn[0] = intn[0] << 18;
	intn[1] = intn[1] << 12;
	intn[2] = intn[2] << 6;	
     
	/*Bota cada um dos inteiros na VetSmallInt sar*/
	for(i=0;i<4;i++)
		sar = sar | intn[i];

	return sar;
}/* Fim Função: vs_sar */


/* Inicio Função: vs_write */
int vs_write(VetSmallInt v, FILE *f){
	
	int i;
	unsigned char vet[4];
	unsigned char x;

	/*Testa erro no fopen*/
	if(f == NULL){
		printf("Erro ao abrir o arquivo");
		return -1;
	}	

	/*Bota em Big Endian*/ 

	dump1(&v, sizeof(VetSmallInt), vet );
	
    /*Escreve No Arquivo e usa o x para verificar se está certo*/ 
	for(i=3; i>=0;i--){
		x = fputc(vet[i],f);
		if (x != vet[i])
			return -1;
	}
	
	return 0;
}/* Fim Função: vs_write */

/* Inicio Função: vs_read*/
VetSmallInt vs_read(FILE *f){

 int i,j;
 VetSmallInt vetInt;
 VetSmallInt vet[4];

 	/*Testa erro no fopen*/
	if(f == NULL){
		printf("Erro ao abrir o arquivo");
		return 0xFFFFFFFF;
	}	

 /*Lê de f todos os bytes*/
 for(i=0;i<4;i++)
  vet[i] = fgetc(f);
 
 /*Arruma no vetor para criar o novo VetSmallInt*/
 for(i=0,j=0;i<4;i++,j+=8)
  vet[i] = vet[i] << j;

 for(i=0;i<4;i++)
  vetInt = vetInt | vet[i];
 
 return vetInt;
}/* Fim Função: vs_read */


/*******************FIM**********************/

