#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void table1(int len, int arr[], char c, char str[]);
//void table2();
//void table3();
//void table4();
//void table5();
//void printToFile();

int main(){
	const int MAX = 250;
	char str[MAX];
	char str2[MAX];
	char c;
	

	int count = 0;
	int i, len, choice;
	int occurence[256] = {0};
	
	FILE *f1, *f2, *f3, *f4;
	char fileName[MAX];
	char fileOut[MAX];
	
	printf("What file should be opened?\n");
	scanf("%s", fileName);


	f1 = fopen(fileName, "r");
	if (f1 == NULL){
		printf("Could not open file\n");
		exit(-1);
	}
	fscanf(f1, "%[^\n]", str);
	len = strlen(str);
	printf("The sentence is: \" %s \"\n", str);
	printf("Which table do you want to print? Enter 1-5, or 6 if you wish to write to a file.");
	scanf("%d", &choice);
	switch(choice){
		case 1:
			table1(len, occurence, c, str);
			break;
		case 2: 
	//		table2();
			break;
		case 3:
	//		table3();
			break;
		case 4:
	//		table4();
			break;
		case 5:
	//		table5();
			break;
	/*	case 6:
			printf("Enter the file name designated for output.");
			scanf("%s", fileOut);
			printf("Which table do you want to write to the file? Enter 1-5.");
			scanf("%d", &choice);
			switch(choice){
				case 1:             
					table1(len, occurence, c, str);
                	        	break;
                		case 2:
                        	//	table2();
                        		break;
                		case 3:
                      		//	table3();
                        		break;
               			case 4:
                        	//	table4();
                        		break;
                		case 5:
                        	//	table5();
                        		break;

			}
			break;	*/
		default:
			printf("Invalid choice.\n");
			exit(-1);
	}
	return 0;
}

void table1(int len, int arr[], char c, char str[]){
	int i;
	for (i = 0; i < len; i++){
        	c = str[i];
                if (!isalpha(c)){
           	     continue;
                }
                arr[(int)(tolower(str[i])-'a')]++;
        }
        for (i = 0; i < 256; i++){
        	if (arr[i] != 0){
                	printf("The %c character has %d occurences.\n",
				       	i + 'a', arr[i]);
                }
        }

}
