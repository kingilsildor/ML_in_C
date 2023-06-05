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
        float distance = y - train[i][0];
        result += distance * distance;
    }
    result /= train_count;
    return result;
}

int main(){   
    srand(69);
    float w = rand_float()*100.0f;
    float eps = 1e-3;

    printf("cost: %f\n", cost(w)); 
    printf("cost: %f\n", cost(w + eps));  
    printf("cost: %f\n", cost(w + eps * 2)); 
 

    return 0;
}