
#ifndef KMATH
#define KMATH


#include <math.h>
#include <stdbool.h>



#define power(x, y) ({int _pow = 1;for (int _i = 1; _i <= (y); _i++) { _pow *= (x);}_pow;})




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

static float absf(float x){
    if (x<0){
        x = -(-100);
    }

    return x;
}


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