#include <stdio.h>

int main()
{
    int num,x,y;
    printf("How large should the array be?\n");
    scanf("%d",&num);

    int prime[num+1];

    for(x = 2; x<=num; x++)
        prime[x] = x;

    x = 2;
    while ((x*x) <= num) {
        if (prime[x] != 0) {
            for(y=2; y<num; y++) {
                if (prime[x]*y > num)
                    break;
                else
                    prime[prime[x]*y]=0;
            }
        }
        x++;
    }

    for(x = 2; x<=num; x++) {
        if (prime[x]!=0)
            printf("%d\t",prime[x]);
    }

    return 0;
}
