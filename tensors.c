
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
//#include <stdlib.h>
#include <stdbool.h>
//
#include <stdlib.h>
//#include <string.h>
//#include <wchar.h>


/* 
void zero_matrix(int row, int col){
    int matrix[row][col];
    int *matrix_ptr = calloc(row*col, sizeof(int));

    for (int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            matrix_ptr[i * col + j];
        };


    }

}
*/



typedef struct {
    int* Vec;
    int lenght;
    float mean;
    float sum;
    float max;
}New_Vector;


void vector_mean(int* vec_ptr){
    int lenght = sizeof(&vec_ptr)/sizeof(int);
    printf("\n--%d",lenght);
}


int* linear_arr(int min,int max,int step, New_Vector vec){

    int i,idx;
    int *ptr;

    if (max < min) {
        int new_max = max;
        max = min;
        min = new_max;
    }
    int vec_size = ((max-min)/step)+1;

    ptr = (int*)malloc(vec_size* sizeof(int));

    for (i = min, idx = 0; i <= max; i = i + step, idx++){
        ptr[idx] = i;
    }

    for (int item = 0; item < vec_size; item++ ){
        printf("%d\n", ptr[item]);
    }
    
    printf("\n%d",  vec_size );
    return ptr;
}


/*
int* linear_arr(int min,int max,int step){

    int i,idx;
    int *ptr;

    if (max < min) {
        int new_max = max;
        max = min;
        min = new_max;
    }
    int vec_size = ((max-min)/step)+1;

    ptr = (int*)malloc(vec_size* sizeof(int));

    for (i = min, idx = 0; i <= max; i = i + step, idx++){
        ptr[idx] = i;
    }

    for (int item = 0; item < vec_size; item++ ){
        printf("%d\n", ptr[item]);
    }
    
    printf("\n%d",  vec_size );
    return ptr;
}
    */


int** zero_matrix(int row, int col){
    int i, j;
    int** aa;

    //row += 1, col+=1;

    aa = malloc(row * sizeof(int*));




    for (i=0; i < row;i++){
        aa[i] = calloc(col, sizeof(int));
    }


    for (i=0; i < row;i++){
        for (j=0; j < col;j++){
            printf("%d ",aa[i][j]);
        }
        printf("\n");
    } 


    return aa;
}



int (*simple_int_matrix())[3] {  // Return pointer to 3-element int arrays
    static int matrix[3][3] = {  // Static array (not freed after function returns)
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    return matrix;  // ✅ Works: Static memory persists
}

float** basic_matrix(){
    float **aa;
    const char row = 3, col = 3;
    int i;

    float temp[3][3] = {
        {1.0, 2.1, 3.2},
        {4.0, 5.1, 6.2},
        {7.0, 8.1, 9.2},
    };

    aa = (float **)malloc((unsigned) row * sizeof(float*));

    for(i = 0; i < row; i++){
        aa[i] = (float*)malloc(col * sizeof(float));
    }


    for (i = 0; i < row; i++){
        for (int j = 0; j < row; j++){
            aa[i][j] = temp[i][j];

        }
    }

    printf("\n--After allocating-- \n");
    if (aa != NULL){
        for (int id = 0; id < 3; id++){
            printf("%.1f %.1f %.1f\n",
                aa[id][0], 
                aa[id][1], 
                aa[id][2]);
        }
    }



    printf("\n-In address %p",(void*)aa );

    return aa;
}

void free_matrix(int row, float** ptr){
    for (int i = 0; i < row; i++){
        free(ptr[i]); 
        ptr[i]=NULL;
    }
    free(ptr);
    ptr = NULL;  

    printf("\n----- Matrix Memory Freed and set to null -----\n\n");
}

void free_vec(int row, int** ptr){
    for (int i = 0; i < row; i++){
        free(ptr[i]); 
        ptr[i]=NULL;
    }
    free(ptr);
    ptr = NULL;  

    printf("\n----- Vector Memory Freed and set to null -----");
}

int main(){
    
    printf("%d", (int)sizeof(float*)*3);
    float **ptr_to_ptr = basic_matrix();

    


    free_matrix(3, ptr_to_ptr);


    zero_matrix(1,1);


    int (*mat)[3] = simple_int_matrix();

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    

    int a[2][2][2] = {
        {{10,11},{21,22}},
        {{12 ,23} ,{24,5}},
    };
 

    New_Vector newvec;  

    int* lin_array = linear_arr(-2, 2, 1, newvec);

    vector_mean(lin_array);

    return 0;
}
