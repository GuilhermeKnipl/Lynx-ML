
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
//#include <stdlib.h>
#include <stdbool.h>
//#include "kmath.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
//#include <string.h>
//#include <wchar.h>


typedef struct Vector {
    int* vector;
    int* len;
    float* mean;
    float* sum;
    float* std;
}Vector;

typedef struct LinearReg{
    float* intercept;
    float* slope;
}LinearReg;


typedef struct Vectorf {
    float* vector;
    float* len;
    float* mean;
    float* sum;
    float* std;
}Vectorf;



Vector* linear_array(int min,int max,int step){

    int i,idx;
    Vector* vec = (Vector*)malloc(sizeof(Vector)); 
    int* vec_size = (int*)malloc(sizeof(int));
    vec->sum = (float*)malloc(sizeof(float));
    vec->std = (float*)malloc(sizeof(float));
    vec->mean = (float*)malloc(sizeof(float)); 
    
    float sum = 0.0;

    float deviation = 0.0;

    if (max < min) {
        int new_max = max;
        max = min;
        min = new_max;
    }
    
    *vec_size = ((max-min)/step)+1;
    
    vec->vector = (int*)malloc(sizeof(int) * (*vec_size));

    float mean = sum / *vec_size ;

    for (i = min, idx = 0; i <= max; i = i + step, idx++){
        
        vec->vector[idx] = i;
        deviation += powf(vec->vector[idx] - mean,2);
        sum += vec->vector[idx];

        printf(" %d:%d ",idx,vec->vector[idx]);
    }


    float variance = deviation/((float)*vec_size - 1.0);
    float std = sqrtf(variance);
    
    vec->len = vec_size;
    *vec->sum = sum;
    *vec->mean = sum/(float)*vec_size ;
    *vec->std = std;

    return vec;
}


float ols_intercept(float slope, float x_mean, float y_mean){
    float intercept =y_mean - (slope*x_mean);
    return intercept;
}

LinearReg* ols_slope_intercept(Vector* x, Vector* y){
    
    LinearReg* regression = (LinearReg*)malloc(sizeof(LinearReg));
    regression->intercept = (float*)malloc(sizeof(float));
    regression->slope = (float*)malloc(sizeof(float));

    if (!x || !y) {
        printf("\nVec is null or invalid");
        return NULL;
    }

    int x_len = *x->len;
    int y_len = *y->len;

    float cov_summation = 0.0f, var_summation = 0.0f;

    printf("%d", x_len);


    if (x_len == y_len){
        for (int i = 0; i < x_len; i++){
            float x_diff = (float)x->vector[i] - *x->mean;
            float y_diff = (float)y->vector[i] - *y->mean;

            cov_summation += x_diff * y_diff;
            var_summation += x_diff * x_diff;
        }
        float slope = cov_summation / var_summation;
     
        *regression->intercept = ols_intercept(slope, *x->mean, *y->mean);
        *regression->slope = slope;
        
        return regression;
    } else {
        printf("Vectors have different lengths!\n");
        return NULL;
    }

    
}




void linear_reg(Vector* x, Vector* y){
    
    LinearReg* regression = ols_slope_intercept(x, y);
    float* y_pred = (float*)malloc(*x->len * sizeof(y_pred));


    int x_len = *x->len, y_len = *y->len, i;
    float intercept, slope;

    if (x_len == y_len){
        for (i = 0; i < x_len; i++){
            y_pred[i] = *regression->intercept + (*regression->slope * (x->vector[i]));
            printf("\n%f", y_pred[i]);
        }
    }
}


void free_vec(Vector** x) {
    if (x && *x) {
        if ((*x)->mean) {free((*x)->mean);(*x)->mean = NULL;};
        if ((*x)->std) {free((*x)->std);(*x)->std = NULL;};
        if ((*x)->vector) {free((*x)->vector);(*x)->vector = NULL;};
        if ((*x)->sum) {free((*x)->sum);(*x)->sum = NULL;};
        if ((*x)->len) {free((*x)->len);(*x)->len = NULL;};
        free(*x);*x = NULL;
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

int main(){

    
    //float **ptr_to_ptr = basic_matrix();

    //free_matrix(3, ptr_to_ptr);

    //zero_matrix(1,1);
    Vector* yarray = linear_array(0, 10, 2);
    Vector* xarray = linear_array(5, 10, 1);

    LinearReg* a = ols_slope_intercept(xarray, yarray);
    
    linear_reg(xarray, yarray);

    //printf("\n%f", *a->intercept);
    //printf("\n%f", *a->slope);

    free_vec(&xarray);free_vec(&yarray);
    return 0;
}


/*    Vector* yarray = (Vector*)malloc(sizeof(Vector));

int* vec_size = (int*)malloc(sizeof(int));

yarray->vector = (int*)malloc(sizeof(int));

*vec_size = *xarray->len;

yarray->len = vec_size;

for(int i = 0; i < *xarray->len; i++ ){
    yarray->vector[i] = pow(xarray->vector[i],2);
    printf(":%d ", yarray->vector[i]);
}*/