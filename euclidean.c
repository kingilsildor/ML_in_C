#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_NUM_ROWS 256
#define MAX_NUM_COLUMN 5
#define MAX_TOKEN_LENGTH 100

// Array data: [x1, x2, x3, x4, y]

float distance(float* array1, float* array2, int column_len) {
    float distance = 0.0;

    for (size_t i = 0; i < column_len; i++) {
        distance += powf(array1[i] - array2[i], 2);
    }

    return sqrtf(distance);  
}

int main() { 
    
    float point1[][4] = {{3.5, 2.5, 0.5, 0.5},
                        {4.5, 2.5, 1.0, 3.0}};

    int numRows = sizeof(point1) / sizeof(point1[0]);
    int numColumns = sizeof(point1[0]) / sizeof(point1[0][0]);
    
    float* point2 = point1[1];   
    float distance_list[numRows]; 

    for (size_t i = 0; i < numRows; i++)
    {
        if(i + 1 > numRows){
            break;
        }

        distance_list[i] = distance((float*)point1[i], (float*)point1[i + 1], numColumns);
        printf("distance = %f, i = %d\n", distance_list[i], i);
    }
    
    
    float distance_int = distance((float*)point1[0], (float*)point2, numColumns);
    
    return 0;
}
