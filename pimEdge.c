#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "iplib2New.c"

#define FILTER_SIZE 3

image_ptr read_pnm(char *filename, int *rows, int *cols, int *type);
int getnum(FILE *fp);
void write_pnm(image_ptr ptr, char *filename, int rows, int cols, int magic_number);

int hori_filter(unsigned char sub_block[FILTER_SIZE][FILTER_SIZE], int sobel_hori[FILTER_SIZE][FILTER_SIZE]);
int vert_filter(unsigned char sub_block[FILTER_SIZE][FILTER_SIZE], int sobel_vert[FILTER_SIZE][FILTER_SIZE]);

int bin_hori_filter(unsigned char sub_block[FILTER_SIZE][FILTER_SIZE], int sobel_hori[FILTER_SIZE][FILTER_SIZE]);
int bin_vert_filter(unsigned char sub_block[FILTER_SIZE][FILTER_SIZE], int sobel_vert[FILTER_SIZE][FILTER_SIZE]);

int main(int argc, char **argv){
    int f_des[2];
    static int img_info[8];
    int pid, childpid;
    int rows, cols, type, row_pos, col_pos, pixel_loc;
    image_ptr imagePtr, imagePtr2; //image pointer types
    
    int sobel_hori[FILTER_SIZE][FILTER_SIZE] = { -1, -2, -1, 0, 0, 0, 1, 2, 1};
    int sobel_vert[FILTER_SIZE][FILTER_SIZE] = { -1, 0, 1, -2, 0, 2, -1, 0, 1};

    unsigned char sub_block[FILTER_SIZE][FILTER_SIZE]; //sub block for image
    int i = 0, j = 0, x = 0, y = 0, p = 0, k = 0, l = 0, m = 0,
    value_hori = 0, value_vert = 0, value_both = 0, value_bhori = 0, value_bvert = 0, value_bboth = 0, magic_num;
    //double edge_mean, edge_std_dev, edge_threshold; //for binary
    double median;
   
    if (pipe(f_des) == -1)
    {
        printf("Pipe failed.");
    }
//pipe made
    if (argc != 9)
    {
        printf("Invalid inputs\n");
    }
//check for correct inputs
    imagePtr = read_pnm(argv[1], &rows, &cols, &type);

    printf("\nImage rendering complete.\n");
    printf("Image Info : rows = %d, cols = %d, type = %d\n", rows, cols, type);

    unsigned char hori_edge[rows][cols];
    unsigned char vert_edge[rows][cols];
    unsigned char both_edges[rows][cols];
    unsigned char bin_hori_edge[rows][cols];
    unsigned char bin_vert_edge[rows][cols];
    unsigned char bin_both_edges[rows][cols];

    //int *calc_values = malloc((rows*cols)*sizeof(*calc_values));
    //for(m = 0; m < rows*cols; m++){
    //	calc_values[x] = imagePtr[x];
    //}
    
    //median = calc_values[(rows*cols)/2]; //median calculation

    //printf("median : %f \n", median);
    //start creating processes
    p = atoi(argv[8]);
    
    for (k = 0; k < p; k++){
        if ((childpid = fork()) <= 0) break;
    }
    //make children

    pixel_loc = 0;

    if (childpid == 0){
	//<0 = parent, >0 = fail, ==0 = child
	close(f_des[0]); //closing one end of pipe
	if (pixel_loc % p == k){
        for (i = 0; i < rows; i++){
            for (j = 0; j < cols; j++){
                    for (y = 0; y < FILTER_SIZE; y++){
                        for (x = 0; x < FILTER_SIZE; x++){
                            sub_block[x][y] = imagePtr[(i + x) * cols + (j + y)];
			    pixel_loc++;
                        }
                    }
	    
	
	
                value_hori = hori_filter(sub_block, sobel_hori);
                value_vert = vert_filter(sub_block, sobel_vert);
                value_both = value_hori + value_vert;
		value_bhori = bin_hori_filter(sub_block, sobel_hori);
		value_bvert = bin_vert_filter(sub_block, sobel_vert);
		value_bboth = value_bhori + value_bvert;
		

                row_pos = i;
                col_pos = j;

                img_info[0] = row_pos;
                img_info[1] = col_pos;
                img_info[2] = value_hori;
                img_info[3] = value_vert;
                img_info[4] = value_both;
		img_info[5] = value_bhori;
		img_info[6] = value_bvert;
		img_info[7] = value_bboth;

                if (write(f_des[1], img_info, sizeof(img_info)) != -1){
    //                printf("Writing to pipe.\n");
                    fflush(stdout);
                }
                else{
                    perror("Write:");
                }
		}
	    }    
	}   
    }
    else{
	close(f_des[1]);
	printf("Attempting to read pipe.\n");
        for (i = 0; i < rows; i++){
            for (j = 0; j < cols; j++){
                if (read(f_des[0], img_info, sizeof(img_info)) != -1){
                    fflush(stdout);
                }
                else{
                    perror("Read:");
                }

                hori_edge[img_info[0]][img_info[1]] = (unsigned char)abs(img_info[2]);
                vert_edge[img_info[0]][img_info[1]] = (unsigned char)abs(img_info[3]);
                both_edges[img_info[0]][img_info[1]] = (unsigned char)abs(img_info[4]);
		bin_hori_edge[img_info[0]][img_info[1]] = (unsigned char)abs(img_info[5]);
		bin_vert_edge[img_info[0]][img_info[1]] = (unsigned char)abs(img_info[6]);
		bin_both_edges[img_info[0]][img_info[1]] = (unsigned char)abs(img_info[7]);
            }
        }

        //Now begin writing the image file
        magic_num = 5;
        imagePtr2 = (image_ptr)hori_edge; //Assign pointer to write image
        printf("\nHorizontal Filter...\n");
        write_pnm(imagePtr2, argv[2], rows, cols, magic_num); //Create the horizontal edge
        imagePtr2 = (image_ptr)vert_edge; //Reassigng pointer
        printf("\nVertical Filter...\n");
        write_pnm(imagePtr2, argv[3], rows, cols, magic_num); //Create the vertical edge
        imagePtr2 = (image_ptr)both_edges; //Reassign the pointer
        printf("\nBoth Filters...\n");
        write_pnm(imagePtr2, argv[4], rows, cols, magic_num); //Create the image of both edges
	imagePtr2 = (image_ptr)bin_hori_edge; //Reassign the pointer
        printf("\nBinary Horizontal...\n");
        write_pnm(imagePtr2, argv[5], rows, cols, magic_num); //Create the image of binary horizontal edges
	imagePtr2 = (image_ptr)bin_vert_edge; //Reassign the pointer
        printf("\nBinary Vertical...\n");
        write_pnm(imagePtr2, argv[6], rows, cols, magic_num); //Create the image of binary vertical edges
	imagePtr2 = (image_ptr)bin_both_edges; //Reassign the pointer
        printf("\nBoth Binary Filters...\n");
        write_pnm(imagePtr2, argv[7], rows, cols, magic_num); //Create the image of both binary edges


    }
   
    return 0;
}//end of main

int hori_filter(unsigned char sub_block[FILTER_SIZE][FILTER_SIZE], int sobel_hori[3][3]){
    int x = 0;
    int y = 0;
    int hori_pixel = 0;
    for (x = 0; x < 3; x++){
        for (y = 0; y < 3; y++){
            hori_pixel += sobel_hori[x][y] * sub_block[x][y];
        }
    }
    abs(hori_pixel);
    return hori_pixel;
}

int vert_filter(unsigned char sub_block[FILTER_SIZE][FILTER_SIZE], int sobel_vert[3][3]){
    int x = 0;
    int y = 0;
    int vert_pixel = 0;
    for (x = 0; x < 3; x++){
        for (y = 0; y < 3; y++){
            vert_pixel += sobel_vert[x][y] * sub_block[x][y];
        }
    }
    abs(vert_pixel);
    return vert_pixel;
}

int bin_hori_filter(unsigned char sub_block[FILTER_SIZE][FILTER_SIZE], int sobel_hori[3][3]){
	int x = 0;
    	int y = 0;
    	int bin_hori_pixel = 0;
    	for (x = 0; x < 3; x++){
        	for (y = 0; y < 3; y++){
         		bin_hori_pixel += sobel_hori[x][y] * sub_block[x][y];
        	}
    	}
	abs(bin_hori_pixel);
    return bin_hori_pixel;
 
}

int bin_vert_filter(unsigned char sub_block[FILTER_SIZE][FILTER_SIZE], int sobel_vert[3][3]){
        int x = 0;
        int y = 0;
        int bin_vert_pixel = 0;
        for (x = 0; x < 3; x++){
                for (y = 0; y < 3; y++){
                        bin_vert_pixel += sobel_vert[x][y] * sub_block[x][y];
                }
        }
	abs(bin_vert_pixel);
    return bin_vert_pixel;

}

