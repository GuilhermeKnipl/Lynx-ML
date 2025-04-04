
#include <cassert>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
//#include <stdlib.h>
#include <stdbool.h>
#include "kmath.h"
#include <stdlib.h>
#include <math.h>
//#include <string.h>
//#include <wchar.h>


typedef struct Vector {
    int* vector;
    int* len;
    //float mean;
    //float sum;
    // float max;
}Vector;

typedef struct Vectorf {
    float* vector;
    float* len;
    //float mean;
    //float sum;
    // float max;
}Vectorf;


void vector_mean(Vector *vec_ptr){
    int lenght = *vec_ptr->len;
    int sum = 0;
    float mean;

    for (int i = 0; i < lenght; i++){
        sum += vec_ptr->vector[i];;
    };
    mean = (float)sum/(float)lenght;

    float deviation = 0.0;

    for (int i = 0; i < lenght; i++){
        deviation += powerf((float)vec_ptr->vector[i] - mean,2);
    };
    
    float variance = deviation/((float)lenght -1.0);
    float std = sqrootf(variance);

    printf("\nTotal sum of array is: %d",sum);
    printf("\nTotal mean of array is: %.2f",mean);
    printf("\nStandard Deviation %.2f", std);
}



Vector* linear_arr(int min,int max,int step){

    int i,idx;
    Vector* vec = (Vector*)malloc(sizeof(Vector)); 


    if (max < min) {
        int new_max = max;
        max = min;
        min = new_max;
    }

    int* vec_size = (int*)malloc(sizeof(int));
    
    *vec_size = ((max-min)/step)+1;

    vec->vector = (int*)malloc(sizeof(int));

    for (i = min, idx = 0; i <= max; i = i + step, idx++){
        vec->vector[idx] = i;
        printf(" %d:%d ",idx,vec->vector[idx]);
    }
    
    vec->len = vec_size;

    return vec;
}

Vector new_vec();



Vector* linear_reg(Vector* x, Vector* y){
    int x_len = *x->len, y_len = *y->len, i;
    float intercept, slope;

    if (x_len == y_len){
        for (i = 0; i < x_len; i++){
            intercept
        }
    }


}

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

    
    float **ptr_to_ptr = basic_matrix();

    free_matrix(3, ptr_to_ptr);

    zero_matrix(1,1);

    Vector* xarray = linear_arr(5, 10, 1);
    Vector* yarray = (Vector*)malloc(sizeof(Vector));
    
    int* vec_size = (int*)malloc(sizeof(int));
    
    vec_size = xarray->vector;

    yarray->vector = (int*)malloc(sizeof(int));
    
    for(int i; i < *xarray->len; i++ ){
        yarray->vector[i] = power(xarray->vector[i],2);
        printf(":%d ", yarray->vector[i]);
    }



    return 0;
}
