#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

	int num = 250000;
	int sum;
	for(int i=1;i<num; i++){
	if(i%2==0){
		sum+=i;
	}
	else{
		sum-=i;
	}
	
	}
	printf("Valor %d\n", sum);
	
	int num1 = 500000;
	int sum1;
	for(int i=250000;i<num1; i++){
	if(i%2==0){
		sum1+=i;
	}
	else{
		sum1-=i;
	}
	
	}
	printf("Valor %d\n", sum1);
	
	int num2 = 750000;
	int sum2;
	for(int i=500000;i<num2; i++){
	if(i%2==0){
		sum2+=i;
	}
	else{
		sum2-=i;
	}
	
	}
	printf("Valor %d\n", sum2);
	
	int num3 = 1000000;
	int sum3;
	for(int i=750000;i<num3; i++){
	if(i%2==0){
		sum3+=i;
	}
	else{
		sum3-=i;
	}
	
	}
	printf("Valor %d\n", sum3);


	int num4 = 1000000;
	int sum4;
	for(int i=1;i<num4; i++){
	if(i%2==0){
		sum4+=i;
	}
	else{
		sum4-=i;
	}
	
	}
	printf("Valor %d\n", sum4);

}
