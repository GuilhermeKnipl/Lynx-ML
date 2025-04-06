#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "vectors.h"

int main(){
    Vector* yarray = linear_array(0, 10, 2);
    Vector* xarray = linear_array(5, 10, 1);

    LinearReg* a = ols_slope_intercept(xarray, yarray);
    
    linear_reg(xarray, yarray);

    //printf("\n%f", *a->intercept);
    //printf("\n%f", *a->slope);

    free_vec(&xarray);free_vec(&yarray);
    return 0;
}