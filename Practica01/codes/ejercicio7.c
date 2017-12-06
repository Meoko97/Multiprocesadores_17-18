#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){

	//Declaración de variables

	int tamano = 10000;
	
	int *p_vector;
	p_vector = malloc(sizeof(int)*tamano);	//Reservamos el espacio dinámicamente
	for(int i=0; i<tamano; i++) {				//Inicializar a 1 el vector
		p_vector[i] = 1;
	}
	
	int *p_matriz;
	p_matriz = malloc(sizeof(int)*(tamano*tamano));	//Reservamos el espacio dinámicamente
	for(int i = 0; i < (tamano*tamano); i++){
		p_matriz[i]= 2;								//Inicializar a 2 la matriz
	}

	int resultado=0;
	int contador=0;
	
	for(int i = 0; i<tamano; i++) {
		for(int j = 0; j<tamano; j++){
			resultado += (p_vector[i])*(p_matriz[contador]);
			contador++;
		}
	}
	
	printf("El resultado es %d\n", resultado);

    
    // Liberamos memoria
    
    	free(p_vector);
	free(p_matriz);
    
} 

