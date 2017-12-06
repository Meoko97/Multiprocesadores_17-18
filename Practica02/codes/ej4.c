#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


// Estructura para pasar al hilo

struct parametros {
	int inicio; ;
	int fin ;
	int nh;
	double *vector;
	// int sumaTotal;
};


void *suma_vector_function( void *arg );

int main(){


	// Pedir por pantalla
	int i;
	int longitud;
	printf("Inserte la longitud de su vector:\n");
	scanf("%d", &longitud);
	
	//Vector declado dinamicamente
	
	double *vector;
	vector = malloc(sizeof(double*)*longitud);
	
	// Estructura que rellena el vector
	
	double contador;
	for(int i = 0; i < longitud; i++ ){
		contador+=1.0;
		vector[i]= contador;
	}
	

	int nThread = 4; // Nos pide el ejercicio que sea igual a 4
	pthread_t *thread;
	thread = (pthread_t*)malloc(sizeof(pthread_t)*nThread);




	// Ejecución de hilos para determinado sector


	int elementos = longitud;
	int nHilos = nThread;
	
	int paquete = elementos / nHilos;
	int excedente = elementos % nHilos;
	
	int fin = 0;
	int inicio = 0;
	
	struct parametros parametros_array[nHilos];
	
	for(int i = 0; i<nHilos; i++){
		parametros_array[i].vector = vector;
		fin = inicio + paquete;
		if(excedente > 0){
			fin++;
			excedente--;
		}
		
		parametros_array[i].inicio = inicio;
		parametros_array[i].fin = fin;
		parametros_array[i].nh = i;
		pthread_create ( &thread[i], NULL, suma_vector_function, (void*)&parametros_array[i]);
		inicio = fin;
	}
	
	
	
	for(int i = 0; i<nHilos; i++){
		pthread_join( thread[i], NULL);
	}
	
	// printf("\nEl resultado de la suma del vector es ", sumaTotal)
	
	// Limpiamos
	
	free(vector);
	free(thread);
	return 0;
}
	
	
	
	

void *suma_vector_function( void *arg ){

	struct parametros * p;
	p = ( struct parametros *) arg ;	
	
	double suma;
	 
	for(int i = (p -> inicio); i < (p -> fin); i++){
		suma += (p -> vector[i]);
	}
	printf("\nHilo %d -> Inicio: %d ; Fin: %d, resultado de la suma = %f\n", (p -> nh), (p -> inicio), (p -> fin), suma); 
	
	// sumaTotal+= suma;
	
	return 0;

}

