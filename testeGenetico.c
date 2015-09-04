#include <stdio.h>
#include <stdlib.h>
#include "lib/populacao.h"

int main(){

	int i,j;
	int op;
	/* Population */
	struct Individuo populacao[POP];
	
	printf("1. Roleta / Ciclico / Melhores Pais e Filhos\n\n");
	printf("2. Torneio Simples / Ciclico / Melhores Pais e Filhos\n\n");
	printf("3. Roleta / PMX / Melhores Pais e Filhos\n\n");
	printf("4. Torneio Simples / PMX / Melhores Pais e Filhos\n\n");
	printf("5. Roleta / Ciclico / Reinsercao Pura Elitismo 20%\n\n");
	printf("6. Torneio Simples / Ciclico / Reinsercao Pura Elitismo 20%\n\n");
	printf("7. Roleta / PMX / Reinsercao Pura Elitismo 20%\n\n");
	printf("8. Torneio Simples / PMX / Reinsercao Pura Elitismo 20%\n\n");
	printf("Choose an option: ");
	scanf("%d", &op);

	
	
	gerencia(populacao, op);


	/* Provides OUTPUT to the user */
	for ( i = 0; i < POP; i++)
	{
		printf("I[%d]\t= ", i);
		for ( j = 0; j <TAM; j++)
		{
			printf("%d | ", populacao[i].cromossomo[j]);
		}
		printf(" --->>> Fenotipo: %d\n", populacao[i].fenotipo);
	}
	
	/*geraRoleta(populacao);
	crossoverPais();*/
	return 0;
}
