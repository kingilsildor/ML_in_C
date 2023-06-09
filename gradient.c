#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
};
#define train_count (sizeof(train)/sizeof(train[0]))

float rand_float(){
    return (float) rand() / (float) RAND_MAX;
}

float cost_function(float w){
    float result = 0.0f;

    for (size_t i = 0; i < train_count; i++){
        float x = train[i][0];
        float y = x * w;
        float distance = y - train[i][0];
        result += distance * distance;
    }

    result /= train_count;
    return result;
}

float derivative(float w){
    float result = 0.0f;

    for (size_t i = 0; i < train_count; i++){
        float x = train[i][0];
        float y = x * w;
        float distance = y - train[i][0];
        result += -2 * distance
    }
    
    result /= train_count;
}

float gradient_step(w, eps){
    w = w - (eps * derivative(w));
    return w;
}

float gradient_descent()

int main(){
    
    return 0;
}
