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
    float * vector;
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
    Vector * regression_vector;
}LinearReg;


static Vector  * vector_constructor(float * array, int len){
    Vector * vec = (Vector*)malloc(sizeof(Vector));
    vec->vector = (float*)malloc(sizeof(float) * len);
    vec->len = (int*)malloc(sizeof(int));
    vec->sum = (float*)malloc(sizeof(float));
    vec->mean = (float*)malloc(sizeof(float));
    vec->std = (float*)malloc(sizeof(float));
     
    float sum = 0.0;

    float deviation = 0.0;

    vec->vector = (float*)malloc(sizeof(float) * (len));


    for (int idx = 0; idx < len; idx++){        
        vec->vector[idx] = array[idx];
        sum += vec->vector[idx];

            printf("\n%d:%0.f ",idx,vec->vector[idx]);
    }


    float mean = sum / len;

    for (int idx = 0; idx < len ; idx++){
        deviation += powf(vec->vector[idx] - mean,2);
    }


    float variance = deviation/((float)len - 1.0);
    float std = sqrtf(variance);
   
    *vec->len = len;
    *vec->sum = sum;
    *vec->mean = mean;
    *vec->std = std;

    return vec;


}

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
    
    vec->vector = (float*)malloc(sizeof(float) * (*vec_size));

    for (i = min, idx = 0; i <= (float)max; i = i + step, idx++){        
        vec->vector[idx] = i;
        sum += vec->vector[idx];

            printf("\n%d:%0.f ",idx,vec->vector[idx]);
    }

    float mean = sum / *vec_size ;

    for (idx = 0; idx < *vec_size; idx++){
        deviation += powf(vec->vector[idx] - mean,2);
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

    printf("\nlen:%d", x_len);


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
    Vector * regression_vector = (Vector*)malloc(sizeof(Vector));

    regression->regression_vector = regression_vector;
     float * vector = (float*)malloc(sizeof(float)*(*x->len));

    int x_len = *x->len, y_len = *y->len, i;
    
    if (x_len == y_len){
        for (i = 0; i < x_len; i++){
            vector[i] = *regression->intercept + (*regression->slope * (x->vector[i]));
            printf("\n%0.f", vector[i]);
        }
    }
    regression->regression_vector = vector_constructor(vector, *x->len);

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
typedef struct Tensor3d{
    float* vector;
    int* z;
    int* y;
    int* x;
}Tensor3d;


static Tensor3d* tensor_init(int x , int y, int z){
    Tensor3d* empty = (Tensor3d*)malloc(sizeof(Tensor3d));
    empty->x = (int*)malloc(sizeof(int));
    empty->y = (int*)malloc(sizeof(int));
    empty->z = (int*)malloc(sizeof(int));
    empty->vector = (float*)malloc((x*y*z)*(sizeof(float)));    

    *empty->x = x;
    *empty->y = y;
    *empty->z = z;

    for (int i = 0; i < x * y * z; i++) {
        empty->vector[i] = (float)i;  // or some other function of i
        printf("Index %2d: %.2f\n", i, empty->vector[i]);

    }



    return empty;
}


static void print_tensor(){
    Tensor3d* tensor3d = tensor_init(1, 3, 4);

    // PLANES INDEXING 0 -> Iter = plane[0] iter1-> iter2 = plane[1] ...
    // ROW INDEXING 0 -> Iter = 
    int planes = *tensor3d->z;
    int plane_size = (*tensor3d->x) * (*tensor3d->y);

    int* plane = (int*)malloc(sizeof(int) * planes);
    for (int i = 0; i < planes; i++) {
        plane[i] = plane_size * (i + 1);
        printf("\nPlane %d upper limit index: %d", i + 1, plane[i]);
    }

    int stride = 3, a =0 ;
    int idx_row = 0;

    for (int idx=0;idx < 12; idx++ ){
        if (a == stride){
            printf("\nY_Val:%2.f", tensor3d->vector[idx]);
            printf("\nLast x:%2.f", tensor3d->vector[idx-1]);
            idx_row += 1;
            printf("\nidx_row = %d\n", idx_row);
            a = 0;
        }
        a+=1;
        printf("\n---%d : %d---\n", a, idx);
    }

}






#endif
