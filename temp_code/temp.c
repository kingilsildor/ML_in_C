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

struct Distance{
    float distance;
    char *iris_class_one;
    char *iris_class_two;
};

float distance(float *data_one, float *data_two) {
    float distance = 0.0;

    for (size_t i = 0; i < 4; i++){
        distance += powf(data_one[i] - data_two[i], 2);
    }

    return sqrtf(distance); 
}

int main(){
    struct Distance distance_array[MAX_NUM_ROWS];
    struct Iris_Data data[MAX_NUM_ROWS];
    data[0].iris_values[0] = 5.1;
    data[0].iris_values[1] = 3.5;
    data[0].iris_values[2] = 1.4;
    data[0].iris_values[3] = 0.2;
    data[0].iris_class = "Iris-setosa";

    data[1].iris_values[0] = 4.9;
    data[1].iris_values[1] = 3.0;
    data[1].iris_values[2] = 1.4;
    data[1].iris_values[3] = 0.2;
    data[1].iris_class = "Iris-setosa";

    data[2].iris_values[0] = 6.3;
    data[2].iris_values[1] = 3.3;
    data[2].iris_values[2] = 6.0;
    data[2].iris_values[3] = 2.5;
    data[2].iris_class = "Iris-virginica";


    float distance_list[3]; 
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 3; j++){
            if(i == j){
                break;
            }
            distance_array[i].iris_class_one = data[i].iris_class;
            distance_array[i].iris_class_two = data[j].iris_class;
            distance_array[i].distance = distance(data[i].iris_values, data[j].iris_values);

            printf("distance: %.2f, from %s to %s\n", distance_array[i].distance, distance_array[i].iris_class_one, distance_array[i].iris_class_two);
        }
    }
    
}


