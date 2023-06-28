#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_NUM_COLUMN 5
#define MAX_NUM_ROWS 256

struct Iris_Data{
    /*
    iris_values1 = sepal length (cm)  iris_values2 = sepal width (cm)
    iris_values3 = petal length (cm)  iris_values4 = petal width (cm)
    */
    float iris_values[MAX_NUM_COLUMN - 1];
    char *iris_class;
};


float distance(float *array1, float *array2, int column_len) {
    float distance = 0.0;

    for (size_t i = 0; i < column_len; i++) {
        distance += powf(array1[i] - array2[i], 2);
    }

    return sqrtf(distance);  
}

int main(){

    struct Iris_Data data[MAX_NUM_ROWS];
    data[0].iris_values[0] = 5.1;
    data[0].iris_values[1] = 3.5;
    data[0].iris_values[2] = 1.4;
    data[0].iris_values[3] = 0.2;
    data[0].iris_class = 'Iris-setosa';

    data[1].iris_values[0] = 4.9;
    data[1].iris_values[1] = 3.0;
    data[1].iris_values[2] = 1.4;
    data[1].iris_values[3] = 0.2;
    data[1].iris_class = 'Iris-setosa';

    data[2].iris_values[0] = 5.1;
    data[2].iris_values[1] = 3.5;
    data[2].iris_values[2] = 1.4;
    data[2].iris_values[3] = 0.2;
    data[2].iris_class = 'Iris-setosa';


    float distance_list[3]; 
    for (size_t i = 0; i < 3; i++){
        for (size_t i = 0; i < 4; i++){
            
        }
        
    }
    
}


