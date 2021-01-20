#include <stdio.h>

int power (int base, int exp);

int main(){
	int base, exp, result;
	printf("Base: \n");
	scanf("%d", &base);
	printf("Exponent: \n");
	scanf("%d", &exp);

	result = power(base, exp);

	printf("%d", result);

	return 0;
}

int power (int base, int exp){
	if(exp != 0)
		return (base * power(base, exp-1));
	else
		return 1;
}
