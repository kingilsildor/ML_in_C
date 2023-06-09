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

/* y = x *  w;
    y = output
    x = input
    w = parameter
*/

float rand_float(void){
    return (float) rand() / (float) RAND_MAX;
}

float cost(float w){
    float result = 0.0f;

    for(size_t i = 0; i < train_count; i++){
        float x = train[i][0];
        float y = x * w;
        float distance = y - train[i][1];
        result += distance * distance;
        // printf("%f, %f, %f, %f, %f\n", w, x, y, distance, result);
    }
    result /= train_count;
    return result;
}

int main(){   
    srand(69);
    float w = rand_float()*10.0f;

    float eps = 1e-3;
    float learning_rate = 1e-3;
    int iterations = 500;

    for (size_t i = 0; i < iterations; i++){
        float dcost = (cost(w + eps) - cost(w)) / eps;      
        w -= learning_rate * dcost;
        printf("cost = %f, w = %f\n", cost(w), w);
    }
    // printf("W: %f\n", w);

    return 0;
}