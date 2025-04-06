#ifndef KMATH
#define KMATH
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* - Vector structure,
 * - Dynamically allocated 1D array,
 * - Stores basic information needed for calculations
 */
typedef struct Vector {
    int* vector;
    int* len;
    float* mean;
    float* sum;
    float* std;
    //void linearreg
}Vector;

/* - Allocate the Pointers to essential infos of the linear regression
 */
typedef struct LinearReg{
    float* intercept;
    float* slope;
    float* regression_vector;
}LinearReg;

typedef struct Vectorf {
    float* vector;
    float* len;
    float* mean;
    float* sum;
    float* std;
}Vectorf;


/* Linear Array, 
 * returning the Vector type with all struct info
*/
static inline Vector* linear_array(int min,int max,float step){

    int idx;
    float i; 
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

    for (i = min, idx = 0; i <= (float)max; i = i + step, idx++){
        
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


static inline float ols_intercept(float slope, float x_mean, float y_mean){
    float intercept =y_mean - (slope*x_mean);
    return intercept;
}

static inline LinearReg* ols_slope_intercept(Vector* x, Vector* y){
    
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


static inline LinearReg* linear_reg(Vector* x, Vector* y){
    
    LinearReg* regression = ols_slope_intercept(x, y);
    float* y_pred = (float*)malloc(*x->len * sizeof(y_pred));
    float* regression_vector = (float*)malloc((*x->len) * sizeof(float));

    regression->regression_vector = regression_vector;

    int x_len = *x->len, y_len = *y->len, i;
    
    if (x_len == y_len){
        for (i = 0; i < x_len; i++){
            regression->regression_vector[i] = *regression->intercept + (*regression->slope * (x->vector[i]));
            printf("\n%f", regression->regression_vector[i]);
        }
    }
    return regression;
}


static inline void free_vec(Vector** x) {
    if (x && *x) {
        if ((*x)->mean) {free((*x)->mean);(*x)->mean = NULL;};
        if ((*x)->std) {free((*x)->std);(*x)->std = NULL;};
        if ((*x)->vector) {free((*x)->vector);(*x)->vector = NULL;};
        if ((*x)->sum) {free((*x)->sum);(*x)->sum = NULL;};
        if ((*x)->len) {free((*x)->len);(*x)->len = NULL;};
        free(*x);*x = NULL;
    }
}

#endif