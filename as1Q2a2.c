#include <stdio.h>

int main(){
	int i, j, isPrime;
	isPrime = 0;
	printf("List of every prime number between 1 and 10000: ");
	for (i = 2; i <= 10000; i++){
		isPrime = 0;
		for (j = 2; j <= i / 2; ++j){
                	if (i % j == 0){
                        	isPrime = 1;
                        	break;
                	}
        	}
		if (isPrime == 0)
                	printf("%d\t", i);
	
	}	
	
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

