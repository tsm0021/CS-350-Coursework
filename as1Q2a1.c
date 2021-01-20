#include <stdio.h>

int main(){
	
	int number, x, prime;
	prime = 0;
	printf("Enter a number: ");
	scanf("%d", &number);

	for (x=2; x <= number / 2; ++x){
		if (number % x == 0){
			prime = 1;
			break;
		}
	}

	if (prime == 0)
		printf("The number is prime.");
	else
		printf("The number is not prime.");


	return 0;

}
