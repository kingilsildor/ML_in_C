#include <stdio.h>
#include <math.h>

float train[][4] = {
    {3,2,0,0},
    {2,1,1,0},
};

#define row_count sizeof(train)/sizeof(train[0])
#define column_count sizeof(train[0]) / sizeof(train[0][0])

float distance(float* array1, float* array2, int column_len) {
    float distance = 0.0;

    for (size_t i = 0; i < column_len; i++) {
        distance += pow(array1[i] - array2[i], 2);
    }

    return sqrt(distance);  
}

int main(){
    float distance_array[row_count];
    // d = sqrt((p1 - q1)**2 + (p2 - q2)**2)
    for (size_t i = 0; i < row_count; i++){
        for (size_t j = 0; j < row_count; j++) {
            if (i > j){
                distance_array[i] = distance(train[i], train[j], column_count);
                printf("%f\n", distance_array[i]);
            }
        }           
    }
    
    // float d = sqrt(pow((euq[0][1]- euq[1][1]),2));
    // printf("%f", d);


    return 0;
}