#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

pthread_mutex_t llave;

int SumaIntersection = 0; // Variable global donde almacenaremos la suma de
					// la intersección, usaremos mutex para evitar errores

// Estructura para pasar al hilo

struct parametros {			// Definimos una estructura con los parámetros
	int inicio; ;			// necesarios que necesitaremos pasarle a nuestro
	int fin ;				// hilo. Esto incluye 3 variables tipo int, que 		
	int distancia;			// indicaran, principio, fin, y un puntero de tipo
	int *vectorPrim;		// double, que será el array mas pequeño. Y un 
	int *vectorSec;			// puntero de tipo double, que será el array más
};						// grande. 						






// funcion para simplicar el proceso de obtener el instante de tiempo
double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}



// Función de intersección, recorre el array A, que previamente 
// se ha dividido para cada hilo y se asignan un inicio y final
// del array, recorre el array B, si ambas son iguales incrementa
// sumIntersection. Para acabar, devuelve sumIntersection, que es 
// la cantidad de numeros repetidos en ambos arrays.

int f_intersection(int* vA, int inicio, int fin, int* vB, int lB){
	
	int sumIntersection=0;
	int i, j;
	
	for(i=inicio; i<fin; i++){
		for(j=0; j<lB; j++){
			if(vA[i]==vB[j]){
				sumIntersection++;
			}
		}
	}
	
	return sumIntersection;
	
}


// Función un union, es muy simple, sumamos las longitudes de los
// vectores y restamos el valor de la variable global,
// pues si sumamos todos los numeros y eliminamos los repetidos, tenemos 1 
// de cada cual. [0,1,2,3,4] [0,2,4,6,8] --> 5 + 5 - 3 = 7	
//			   | | | | |         | | --> 7


double f_union(int lA, int lB){
	
	int sumUnion=0;
	int i, j;
	
	sumUnion = lA + lB;
	
	return (sumUnion - SumaIntersection);
}


void *do_work( void *arg );


int main(int argc, char *argv[]){
	system("clear");		/* Limpiamos terminal */
	int i, lengthA, lengthB,			// Inicializamos variables	
	nHilos, resultadoIntersection,		// varias de tipo int
	paquete, excedente;
	int *vectorA;			/* Inicializamos puntero vectorA */
	int *vectorB;			/* Inicializamos puntero vectorB */
	double start, end;		/* Inicializamos variables para */
						/* el calculo del tiempo */
						
						
	printf("Insert the length of vector A: ");	// Pedimos por pantalla los
	scanf("%d", &lengthA);					// valores de longitud de
	printf("\nInsert the length of vector B: ");	// los vectores A y B;
	scanf("%d", &lengthB);					// y el número de hilos
	printf("\nInsert the number of threads: ");	// con los que se trabajarán
	scanf("%d", &nHilos);
	
	
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
	


	// Creamos un hilo y reservamos con tantos hilos como nos haya pasado por
	// parámetro	
	
	pthread_t *thread;
	thread = (pthread_t*)malloc(sizeof(pthread_t)*nHilos);
	
	// Paquete guarda la división entre el número de celdas que tiene nuestro array
	// entre el número de hilos, para saber cuantas celdas le corresponde a cada uno
	
	paquete = lengthA / nHilos;
	
	// Excedente recoge el resto para balancear la carga
	
	excedente = lengthA % nHilos;
	
	// Inicializamos las variables fin e inicio, que usaremos para informar donde empieza
	// y acaba el trabajo de cada hilo en el vector
	
	int fin = 0;
	int inicio = 0;

	// Creamos un array de parámetros, de tamaño cuantos hilos tengamos pues estos van
	//a ser los datos con los que trabaje cada uno, que se les pasará cuando se inicialicen 

	struct parametros parametros_array[nHilos];
	
	// Bucle for que rellena los parámetros con inicio, fin del hilo y crea el hilo,
	// esto se repite en cada iteración con nuevos valores

	for(int i = 0; i<nHilos; i++){
		parametros_array[i].vectorPrim = vectorA;
		parametros_array[i].vectorSec = vectorB;
		parametros_array[i].distancia = lengthB;
		fin = inicio + paquete;
		if(excedente > 0){
			fin++;
			excedente--;
		}
		parametros_array[i].inicio = inicio;
		parametros_array[i].fin = fin;
		pthread_create ( &thread[i], NULL, do_work, (void*)&parametros_array[i]);
		inicio = fin;
	}
	
	
	// Esperamos a que todos los hilos acaben
	
	for(int i = 0; i<nHilos; i++){
		pthread_join( thread[i], NULL);
	}
	
	

	printf("\nJaccard's distance is %.2f\n", ((double)SumaIntersection/f_union(lengthA, lengthB)));
	
	// liberamos memoria reservada dinámicamente y eliminamos la llave
	
	pthread_mutex_destroy(&llave);	
    	free(thread);
    	free(vectorA);
    	free(vectorB);
	
	end = get_wall_time();
    	printf("The elapsed time is %.6fs seconds\n", 	// Imprimimos por pantalla el tiempo
    	end-start); 								// en segundos de lo que ha tardado
											// en ejecutar secuencialmente desde
											// que se insertan los datos por pantalla
											// hasta que se muestra el valor de Jaccard
}

void *do_work(void *arg){
	
	int sum;
	
	struct parametros * p;			// Mediante un casting creamos una estructura de tipo
	p = ( struct parametros *) arg ;	// parametros que recibe los valores que le hemos pasado
								// al crear el hilo (inicio, fin, vectorPrim, vectorSec,
								// resultadoParcial)

	sum = f_intersection(p->vectorPrim,p->inicio, p->fin, p->vectorSec, p->distancia);
	
	
	
	pthread_mutex_lock(&llave); 			// Cerramos la llave para que otros
									// hilos no puedan acceder temporalmente
									
	SumaIntersection += sum;				// Guardamos la suma local en la suma global
	
	pthread_mutex_unlock(&llave); 			// Abrimos la llave para que accedan a el
	
	pthread_exit((void*) p);
	} 








