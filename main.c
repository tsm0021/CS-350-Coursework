#include <stdio.h>

int main(){
	int small_radius;
	int big_radius;
	float pi = 3.142;

	printf("Enter the smaller radius.");
	scanf("%d", &small_radius);
	printf("Enter the larger radius.");
	scanf("%d", &big_radius);

	printf("Your area is : %f", (pi*(big_radius*big_radius)/4)-(pi*(small_radius*small_radius)/4));

	return 0;	
}
