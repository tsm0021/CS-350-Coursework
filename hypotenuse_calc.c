#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	int counter = 0;
	char sentinelCheck;
       	while (counter <= 5){
		float side_1 = 0;
		float side_2 = 0;
        	float side_3 = 0;
		float hypotenuse = 0;

        	printf("Enter the first side of the triangle.");
        	scanf("%f", &side_1);
		while (side_1 <= 0){
			printf("Invalid input, please enter a value greater than 0.");
        		scanf("%f", &side_1);
		}
        	printf("Enter the second side.");
        	scanf("%f", &side_2);
		while (side_2 <= 0){
                	printf("Invalid input, please enter a value greater than 0.");
                	scanf("%f", &side_2);
        	}

		printf("Enter the hypotenuse.");
        	scanf("%f", &side_3);
		while (side_3 <= side_2 || side_3 <= side_1){
                	printf("Invalid input, please enter a value greater than the other two sides.");
                	scanf("%f", &side_3);
       		}
	
		hypotenuse = sqrtf((side_2*side_2)+(side_1*side_1));

		printf("First Side: %f.\n", side_1);
		printf("Second Side: %f.\n", side_2);
		printf("Hypotenuse: %f.\n", side_3);

		if (side_3 == hypotenuse){
                	printf("These values present a valid triangle. Enter 'q' to exit.\n");
        	}

        	else{
                	printf("Values invalid for a triangle. Enter 'q' to exit.\n");
        	}
		scanf("%c", &sentinelCheck);
		if (sentinelCheck == 'q'){
			exit(0);
		}
		counter = counter + 1;
		}



        return 0;
}
