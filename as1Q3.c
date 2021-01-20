#include <stdio.h>
#include <stdlib.h>

void penUp(int x, int y);
void penDown(int x, int y);
int turnRight(void);
int turnLeft(void);
int move(void);
void printPic(void);
int end(void);

int canvas[50][50];

int main() {

    for (int j = 0; j < 50; j++) {
        for (int i = 0; i < 50; i++) {
            canvas[i][j] = 0;
        }
    }

    int x = 0, y = 0;
    canvas[x][y] = 0;

    int in;
    do {
        printf("Enter command: ");
        scanf("%d", &in);

        switch (in) {
            case 1:
                penUp(x, y);
                break;

            case 2:
                penDown(x, y);
                break;

            case 6:
                printPic();
                break;

            case 9:
                exit(0);
        }

    } while (in != 0);

    return 0;
}

void penDown(int x, int y){
    if (canvas[x][y] == 0) {
        canvas[x][y] = 1;
    }
}

void penUp(int x, int y){
    if (canvas[x][y] == 1) {
        canvas[x][y] = 0;
    }
}

void printPic(void) {

    for (int j = 0; j < 50; j++) {
        for (int i = 0; i < 50; i++) {
            switch (canvas[i][j]) {
                case 0:
                printf("%c", '0');
                break;

                case 1:
                printf("%c", '1');
                break;
            }
        }
    }
}
