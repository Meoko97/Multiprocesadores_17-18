#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>


// Función de intersección, recorre el array A y para cada
// posicion, recorre el array B, si ambas son iguales incrementa
// sumIntersection. Para acabar, devuelve sumIntersection, que es 
// la cantidad de numeros repetidos en ambos arrays




int f_intersection(int* vA, int lA, int* vB, int lB){
	
	int sumIntersection=0;
	int i, j;
	
	for(i=0; i<lA; i++){
		for(j=0; j<lB; j++){
			if(vA[i]==vB[j]){
				sumIntersection++;
				// Para versiones posteriores, utilizar break; justo aquí. Reduce el tiempo en 40%
			}		  	
		}				 
	}
	
	return sumIntersection;
	
}


// Función para simplicar el proceso de obtener el instante de tiempo

double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}


// Función un union, es muy simple, sumamos las longitudes de los
// vectores y restamos lo que nos pasa por parámetro, que es el resultado
// de f_intersection ejecutada anteriormente,
// pues si sumamos todos los numeros y eliminamos los repetidos, tenemos 1 
// de cada cual. [0,1,2,3,4] [0,2,4,6,8] --> 5 + 5 - 3 = 7

int f_union(int lA, int lB, int intersection){
	
	int sumUnion=0;
	int i, j;
	
	sumUnion = lA + lB;
	
	return (sumUnion - intersection);
}

int main(int argc, char *argv[]){
	system("clear");			/* Limpiamos terminal */
	int i, lengthA, lengthB;		/* Inicializamos variables para longitud */
	int *vectorA;				/* Inicializamos puntero vectorA */
	int *vectorB;				/* Inicializamos puntero vectorB */

    	double start, end;			/* Inicializamos variables para */
    							/* el calculo del tiempo */
	
	printf("Insert the length of vector A: ");
	scanf("%d", &lengthA);
	printf("\nInsert the length of vector B: ");
	scanf("%d", &lengthB);
	
	// El problema nos dice que debemos trabajar para testear el programa
	// con valores de entrada de 0..n, pero claro, si insertamos 20, nuestro
	// array no va a llegar hasta 0..n-1, debemos de sumar +1 a los valores
	// introducidos por pantalla.
	
	lengthA+=1;
	lengthB+=1;
	           
	           
	start = get_wall_time();       /* get initial time */
    							/*    in seconds    */
	
	
	vectorA = malloc(sizeof(int*)*lengthA);	// Reservamos memoria dinámicamente	    
	for(i=0; i<lengthA; i++){				// y rellenamos el puntero con valores  
		vectorA[i] = i;					// de 0..lengthA					
	}
	
	vectorB = malloc(sizeof(int)*lengthB);	// Reservamos memoria dinámicamente
	for(i=0; i<lengthB; i++){				// y rellenamos el puntero con valores
		vectorB[i] = 2*i;				// de 0x2..lengthBx2
	}
	
	// Guardo en intersection y en unions, el resultaodo de f_intersection y 
	// f_union respectivamente para luego hacerles un casting a double y dividirlas
	// para imprimir su resultado con formato
	
	int intersection = f_intersection(vectorA, lengthA, vectorB, lengthB);
	int unions = f_union(lengthA,lengthB, intersection);
	printf("\nJaccard's distance is %.2f\n", (double)intersection/(double)unions);	
	
	// Liberamos memória que previamente hemos reservado dinámicamente
	
	free(vectorB);
	free(vectorA);
	
 	end = get_wall_time();       	/*   get end time 	*/
    							/*    in seconds    */
    							
    	printf("The elapsed time is %.6fs seconds\n", 	// Imprimimos por pantalla el tiempo
    	end-start); 								// en segundos de lo que ha tardado
											// en ejecutar secuencialmente desde
											// que se insertan los datos por pantalla
											// hasta que se muestra el valor de Jaccard
									
}
