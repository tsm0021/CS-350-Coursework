#include <stdio.h>

int integerPower(int, int);



int main(){
        printf("%d \n", integerPower(5,4));
        return 0;

}

int integerPower(int base, int power){
        int result = base;
        for (int x = 1; x < power; x++){
                result = result*base;
        }
        return result;
}
