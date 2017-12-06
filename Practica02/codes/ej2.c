#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function( void *ptr );

int main(){
	
	int i;
	
	// Pedir por pantalla el número de Thread
	int nThread;
	printf("Inserte el número de Thread que se quieren crear:\n");
	scanf("%d", &nThread); 
	
	// Inicializar Thread
	
	char** mensajes = malloc(sizeof(char*)*nThread);
	
	pthread_t *thread;
	thread = (pthread_t*)malloc(sizeof(pthread_t)*nThread);
	for(i = 1; i <= nThread; i++){
		mensajes[i] = malloc(sizeof(char)*20);
		sprintf(mensajes[i], "Thread %d", i);
		pthread_create ( &thread[i], NULL, print_message_function, (void*) mensajes[i]);
	}

	for(i = 1; i <= nThread; i++){
		pthread_join( thread[i], NULL);
	}
	
	for(i = 1; i <= nThread; i++){
		printf("Thread %d returns\n", i);
	}
	
	free(thread);
	for(i = 1; i <= nThread; i++){
		free(mensajes[i]);
	}
	free(mensajes);
	
	
	exit(0);
}

void *print_message_function( void *ptr ){
	//char *message;
	//message = (char *) ptr;
	//printf("%s \n", message);
	printf("%s\n", (char*) ptr);
	return 0;
} 
