#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float sigmoidf(float x){
    return 1.f / (1.f + expf(-x));
}

// OR-gate
float train[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1},
};

// AND-gate
// float AND_train[][3] = {
//     {0, 0, 1},
//     {1, 0, 0},
//     {0, 1, 0},
//     {1, 1, 1},
// }

#define train_count (sizeof(train)/sizeof(train[0]))

float cost(float w1, float w2){
    float result = 0.0f;

    for(size_t i = 0; i < train_count; i++){
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = sigmoidf(x1*w1 + x2*w2);
        float distance = y - train[i][2];
        result += distance * distance;
    }
    
    result /= train_count;
    return result;
}

float rand_float(void){
    return (float) rand() / (float) RAND_MAX;
}

int main(void){    
    
    srand(45);
    float w1 = rand_float();
    float w2 = rand_float();
    float eps = 1e-3;
    float learning_rate = 1e-2;
    int iterations = 500;

    for(size_t i = 0; i < iterations; i++){ 
        float c = cost(w1, w2);
        float dw1 = (cost(w1 + eps, w2) - c) / eps;
        float dw2 = (cost(w1, w2 + eps) - c) / eps;
        w1 -= learning_rate * dw1;
        w2 -= learning_rate * dw2;
        printf("cost = %f, w1 = %f, w2 = %f\n", c, w1, w2);    
    }

    
}
