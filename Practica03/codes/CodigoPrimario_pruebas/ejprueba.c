#include <pthread.h>
#include <stdio.h>

#define ARRAYSIZE   1000000000

double  sum = 0.0, a[ARRAYSIZE];

void init_vec(){
	int i = 0;
	for (i = 0; i < ARRAYSIZE ; i++){
		a[i] = i * 1.0;
	}
}

void* do_work(){
	int i;
	double mysum=0.0;
 
	for (i = 0; i < ARRAYSIZE ; i++) {
		if(i%2==0) mysum += a[i];
		else	mysum -= a[i];
	}
	sum = mysum;//Escritura global

	return 0;
}

int main(int argc, char *argv[]){
	init_vec();
	do_work();
  	printf ("Done. Sum= %lf \n", sum);
	//Comprobacion:
	sum=0.0;
	int i = 0;	
	for (i=0;i<ARRAYSIZE;i++){ 
  		if(i%2 == 0) sum += a[i];
		else	sum -= a[i];
	}
  	printf("Check Sum= %lf\n",sum);
}
