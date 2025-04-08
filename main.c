#include <complex.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "vectors.h"


typedef struct Tensor3d{
    float* vector;
    int* z;
    int* y;
    int* x;
}Tensor3d;


Tensor3d* tensor_init(int x , int y, int z){
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



int main(){

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

    /*
    for (int r = 1; r <= plane[planes - 1]; r++) {
        if (r <= plane[0]) {
            printf("\nPlane 1: r = %d (index = %d)", r, *tensor3d->x * r);
        } else if (r <= plane[1]) {
            printf("\nPlane 2: r = %d (index = %d)", r, *tensor3d->x * r);
        }
    }
   */
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




    // Vector Debugging
    Vector* yarray = linear_array(0, 10, 2);
    Vector* xarray = linear_array(5, 10, 1);
    
    LinearReg* Regression = linear_reg(xarray, yarray);
    printf("\nReg:%2.f", *Regression->slope);
    
    free_vec(&xarray);free_vec(&yarray);
    return 0;
}