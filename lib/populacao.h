#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define TAM 10
#define POP 5
#define TAXA_CROSS 0.6f;

/* Data we'll be working on */
struct Intervalo{
	int max;
	int min;
};

struct Individuo{
	int cromossomo[TAM];
	int fenotipo;
	struct Intervalo *intervalo;
};

struct ListaAux {
	int val[TAM];
	int n;
};

int total = 0;
char palavra1[TAM], palavra2[TAM], palavra3[TAM], palavrafinal[30];

void gerencia(struct Individuo *populacao, int op);
void coletaDados();
void inicLista (struct ListaAux *aux);
void deletaElemLista (struct ListaAux *aux, int val);
int retornaElemLista (struct ListaAux *aux, int val);
int geraPopulacao (struct ListaAux *aux, struct Individuo *populacao);
void removeRep(char *s);
void calcularFenotipo(struct Individuo *populacao, char* p1, char* p2, char* p3, char* palavrafinal);
void geraRoleta(struct Individuo *populacao);
int getRandomNumber(int total);
struct Individuo* sorteioComRoleta(struct Individuo* populacao);
void crossoverCiclicoPais(struct Individuo* populacao);


/* Functions we'll make use of */
void gerencia(struct Individuo *populacao, int op){
	/* List to help to randomize*/
	struct ListaAux *aux;
	int i;

	aux = (struct ListaAux*)malloc(sizeof(struct ListaAux));

	/* Get the input */
	coletaDados();

	/* Removes the repeated letters from the palavrafinal and stores the result in it */
	removeRep(palavrafinal);

	/* Generates the population */
	geraPopulacao(aux, populacao);


	/* Calculates Funcao de aptidao for each individual based on the words provided */
	for (i = 0; i < POP; i++)
	{
		calcularFenotipo(&populacao[i], palavra1, palavra2, palavra3, palavrafinal);
	}

	switch(op){
		case 1:
			geraRoleta(populacao);
			/*for (i=0; i<(TAXA_CROSS * POP)/2; i++){
				crossoverCiclicoPais(populacao);
			}
			*/
			break;
		default:
			break;
	}

}

void coletaDados(){
	/* Get input */
	printf ("Digite a primeira palavra: ");
	scanf("%s", palavra1);

	strcpy(palavrafinal,palavra1);

	printf ("Digite a segunda palavra: ");
	scanf("%s", palavra2);
	
	strcat(palavrafinal,palavra2);
	
	printf ("Digite a palavra soma: ");
	scanf("%s", palavra3);
	
	strcat(palavrafinal,palavra3);
}

void inicLista (struct ListaAux *aux){
	int i;
	
	for (i=0; i<TAM; i++){
		aux->val[i] = i;
	}
	aux->n = TAM-1;
}

void deletaElemLista (struct ListaAux *aux, int val){
	int a = val;
	int b = val +1;
	
	if (b == TAM){
		aux->n = aux->n-1;
	}
	else {
		while (b != TAM){
			aux->val[a] = aux->val[b];
			a++;
			b++;
		}
		aux->n = aux->n-1;
	}	
}

int retornaElemLista (struct ListaAux *aux, int val){
	return aux->val[val];
}

int geraPopulacao (struct ListaAux *aux, struct Individuo *populacao){
	int i, j, val;
	int num = TAM;
	
	srand( (unsigned)time(NULL) );
	
	/*srand(someChangingVariable);*/
	inicLista(aux);
	
	
	for (i= 0; i< POP; i++){
		for (j=0; j< TAM; j++ ){
			val = rand()%num;
			populacao[i].cromossomo[j] = retornaElemLista(aux, val);
			populacao[i].fenotipo = -1;
			populacao[i].intervalo = (struct Intervalo*)malloc(sizeof(struct Intervalo));
			deletaElemLista(aux, val);
			num--;
		}
		inicLista(aux);
		num = TAM;
	}

	
	return 0;
}

void removeRep(char *s){
	int i=0, j, z;

	while(s[i] != '\0'){
		char c = s[i];
		j = i+1;

		while(s[j] != '\0'){
			if(c == s[j]){
				z = j;
				do{
					s[z] = s[z+1];
					z++;
				}while(s[z] != '\0');
			}
			else{
				j++;
			}
		}
		i++;
	}
}

void calcularFenotipo(struct Individuo* individual, char* p1, char* p2, char* p3, char* palavrafinal){
	/* Array to store number digits of palavra1 */
	int v1[10];
	int len1;
	int integer1;

	/* Array to store number digits of palavra2 */
	int v2[10];
	int len2;
	int integer2;

	/* Array to store number digits of palavra3 */
	int v3[10];
	int len3;
	int integer3;

	/* Variable that travels across the arrays v1, v2 and v3*/
	int pos;
	int i, j, z;
	
	pos = 0;
	/* palavra1 */
	for (j = 0; j < strlen(p1); j++)
	{
		z = 0;
		while(palavrafinal[z] != '\0'){
			if(p1[j] == palavrafinal[z]){
				v1[pos] = individual->cromossomo[z];
				pos++;
				break;
			}
			else{
				z++;
			}
		}

	}

	pos = 0;
	/* palavra2 */
	for (j = 0; j < strlen(p2); j++)
	{
		z = 0;
		while(palavrafinal[z] != '\0'){
			if(p2[j] == palavrafinal[z]){
				v2[pos] = individual->cromossomo[z];
				pos++;
				break;
			}
			else{
				z++;
			}
		}

	}

	pos = 0;
	/* palavra3 */
	for (j = 0; j < strlen(p3); j++)
	{
		z = 0;
		while(palavrafinal[z] != '\0'){
			if(p3[j] == palavrafinal[z]){
				v3[pos] = individual->cromossomo[z];
				pos++;
				break;
			}
			else{
				z++;
			}
		}
	}

	/* Turn the vectors of numbers into a integer number */

	/* First word p1 */
	/* Reset the variables before computing them again */
	integer1 = 0;
	len1 = strlen(p1);
	for(i = 0; i<strlen(p1); i++){
		integer1 += v1[i]*pow(10, --len1) + 0.5;
	}
	
	/* Second word p2 */
	/* Reset the variables before computing them again */
	integer2 = 0;
	len2 = strlen(p2);
	for(i = 0; i<strlen(p2); i++){
		integer2 += v2[i]*pow(10, --len2) + 0.5;
	}
	
	/* Third word p3 */
	/* Reset the variables before computing them again */
	integer3 = 0;
	len3 = strlen(p3);
	for(i = 0; i<strlen(p3); i++){
		integer3 += v3[i]*pow(10, --len3) + 0.5;
	}
	

	individual->fenotipo = abs(integer3 - (integer1 + integer2));
	
}

void geraRoleta(struct Individuo *populacao){
	/*	achar o maior_fenotipo
		biggest = maior_fenotipo + 1;
		para cada fenotipo dos individuos
			calcular o numero de casas (min e maximo do intervalo) na roleta */
	int max = populacao[0].fenotipo;
	int i;
	int biggest;
	

	for(i=1;i<POP;i++){
		populacao[i].fenotipo > max ? max = populacao[i].fenotipo : 0;
	}

	biggest = max + 1;
	total += (biggest - populacao[0].fenotipo);
	populacao[0].intervalo->min = 0;
	populacao[0].intervalo->max = (populacao[0].intervalo->min + (biggest - populacao[0].fenotipo)) - 1;

	printf("\n\n");
	printf("Min[%d] = %d & Max[%d] = %d\n", 0, populacao[0].intervalo->min, 0, populacao[0].intervalo->max);
	
	for (i = 1; i < POP; i++)
	{
		populacao[i].intervalo->min = populacao[i-1].intervalo->max + 1;
		populacao[i].intervalo->max = (populacao[i].intervalo->min + (biggest - populacao[i].fenotipo)) - 1;
		total += (biggest - populacao[i].fenotipo);
		printf("Min[%d] = %d & Max[%d] = %d\n", i, populacao[i].intervalo->min, i, populacao[i].intervalo->max);
	}
	printf("\nTotal: %d\n\n", total);
}

/* !!!!!!!!!!!!!!!!!!! IN PROGRESS !!!!!!!!!!!!!!!!!!! (RANDOM PROBLEM)*/
struct Individuo* sorteioComRoleta(struct Individuo* populacao){
	struct Individuo* ind;
	int num;
	int i;
	ind = (struct Individuo*)malloc(sizeof(struct Individuo));

	/*srand((unsigned)time(NULL));*/ /* CAUTION! <<<< Not sure whether calling srand again will interfer on the srand previously coded above*/
	num = rand()%total;
	
	for(i=0;i<POP;i++){
		if(num > populacao[i].intervalo->max){
			i++;
		}
		else{
			break;
		}
	}

	ind = &populacao[i];
	return ind;
}

/* !!!!!!!!!!!!!!!!!! IN PROGRESS !!!!!!!!!!!!!!!!!!! (NEEDS TO ADD THE CHILDREN INTO THE POPULATION)*/
void crossoverCiclicoPais(struct Individuo* populacao){
	/* Sorteia pai1
	 * Sorteia pai2
	 * Cruza pai1 x pai2, gerando 2 filhos (filho1 e filho2) 
	 * Acrescenta filho1 e filho2 a POPULACAO 
	*/
	struct Individuo pai1;
	struct Individuo pai2;
	struct Individuo filho1;
	struct Individuo filho2;

	int posToCross;
	int primeiroElementoCross;
	int temp, i;

	pai1 = *sorteioComRoleta(populacao);
	pai2 = *sorteioComRoleta(populacao);

	filho1 = pai1;
	filho2 = pai2;

	posToCross = rand()%TAM;

	primeiroElementoCross = filho1.cromossomo[posToCross];

	temp = filho2.cromossomo[posToCross];
	filho2.cromossomo[posToCross] = filho1.cromossomo[posToCross];
	filho1.cromossomo[posToCross] = temp;

	while(temp != primeiroElementoCross){
		for(i=0;i<TAM;i++){
		 	if(filho1.cromossomo[i] == temp && i != posToCross){
		 		posToCross = i;
		 		temp = filho2.cromossomo[posToCross];
		 		filho2.cromossomo[posToCross] = filho1.cromossomo[posToCross];
		 		filho1.cromossomo[posToCross] = temp;
		 	}
		}
	}

	calcularFenotipo(&filho1, palavra1, palavra2, palavra3, palavrafinal);
	calcularFenotipo(&filho2, palavra1, palavra2, palavra3, palavrafinal);

	/* Ainda falta adicionar os filhos a populacao */
}






