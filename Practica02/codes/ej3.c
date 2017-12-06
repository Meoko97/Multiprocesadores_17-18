#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//pthread_mutex_t llave;

int longitud;

void *suma_vector_function( void *longitud );


int main(){

	int i;

	
	printf("Inserte la longitud de su vector:\n");
	scanf("%d", &longitud);
	
	double *vector;
	vector = malloc(sizeof(double)*longitud);
	double contador;
	for(int i = 0; i < longitud; i++ ){
		contador+=1.0;
		vector[i]= contador;
	}

	int nThread = 1;

	pthread_t *thread;
	thread = (pthread_t*)malloc(sizeof(pthread_t)*nThread);
	for(i = 1; i <= nThread; i++){
		pthread_create ( &thread[i], NULL, suma_vector_function, (void*)vector);
	}
	
	
	for(i = 1; i <= nThread; i++){
		pthread_join( thread[i], NULL);
	}

	printf("\nEl programa ha finalizado\n");
	return 0;
}

void *suma_vector_function( void *array ){
	
	double *vector = (double *) array;
	double suma;

	for(int i = 0; i < longitud ; i++){
	
	suma += vector[i];
	}
	printf("\nEl resultado de la suma del vector es %f\n", suma);
	return 0;
}
