#include <complex.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "vectors.h"

// Means squared Error
float mse(Vector * y, Vector * y_pred){
    if (*y->len != *y_pred->len)
        printf("Vectors has different Length");
    float summation = 0.0;
    for(int i = 0; *y->len <= i; i++){
        float subtraction = (y->vector[i]) - (y_pred->vector[i]);
    
        summation += powf(subtraction, 2.0); 

    }
    
    float mean_squared_error = summation / *y->len;
    
    printf("\n MSE: %f\n", mean_squared_error);
    return mean_squared_error;
}

//float regression_toarray(LinearReg->
//}

int main(){

    // Vector Debugging
    Vector * yarray = linear_array(0, 10, 2);
    Vector * xarray = linear_array(5, 10, 1);
    
    LinearReg* Regression = linear_reg(xarray, yarray);

    
    float meansquarederror = mse(yarray, Regression->regression_vector);
    printf("%2.f",meansquarederror );
    printf("\nReg:%2.f",Regression->regression_vector->vector[5]);
    
    free_vec(&xarray);free_vec(&yarray);
    printf("\n");
    return 0;
}
