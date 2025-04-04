
#ifndef KMATH
#define KMATH


#include <math.h>
#include <stdbool.h>



#define EULER 2.71828

static inline int power(int x, int y) {
    int result = 1;
    for (int i = 0; i < y; ++i) {
        result *= x;
    }
    return result;
}


static float powerf(float x, int y){
    int pow = 1;
    for(int i=1;i <= y; i++ ){
        pow *= x;
    };
    return pow;
}

static double powerd(double x, int y){
    int pow = 1;
    for(int i=1;i <= y; i++ ){
        pow *= x;
    };
    return pow;
}

static char powerc(char x, int y){
    int pow = 1;
    for(int i=1;i <= y; i++ ){
        pow *= x;
    };
    return pow;
}

// Absolute value of a float if(x < 0) then -(x)
static float absf(float x){

    if (x<0){
        x = -(x);
    }

    return x;
}


// Squareroot of a int -> float
static int sqroot(int n) {
    float x = 0.0;
    float step = 0.00001;

    while (x * x <= n) {
        if (absf(x * x - n) < step) {
            return x;
        }
        x += step;
    }

    return x;
}

static float sqrootf(float n) {
    // Squareroot of a float -> float
    if (n<0){
        return NAN;
    }

    float x = 0.0;
    float step = 0.00001;

    while (x * x <= n) {
        if (absf(x * x - n) < step) {
            return x;
        }
        x += step;
    }

    return x;
}

#endif