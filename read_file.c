#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_NUM_ROWS 256
#define MAX_NUM_COLUMN 5
#define MAX_TOKEN_LENGTH 40



struct Iris_Data{
    /*
    iris_values1 = sepal length (cm)  iris_values2 = sepal width (cm)
    iris_values3 = petal length (cm)  iris_values4 = petal width (cm)
    */
    int iris_values[MAX_NUM_COLUMN - 1];
    char *iris_class;
};

struct Euclidean_Distance{
    float distance;
    char *compared_iris_class;
};

float distance(float *data_one, float *data_two, int column_size) {
    float distance = 0.0;
    const int SQUARED = 2;

    for (size_t i = 0; i < column_size; i++){
        distance += powf(data_one[i] - data_two[i], SQUARED);
    }

    return sqrtf(distance); 
}

int main(){
    char line[MAX_LINE_LENGTH];    
    struct Iris_Data dataset[MAX_LINE_LENGTH];
    char *token;
    int numRows = 0;
    
    // Open file and check if file is valid.
    FILE* file = fopen("data/iris_dataset.csv", "r");
    if (file == NULL) {
        perror("Failed to open the file.\n");
        return 1;
    }

    // Skip header
    fgets(line, sizeof(line), file);   
    

    // Process the lines in the csv file
    while (fgets(line, sizeof(line), file) != NULL) {   
        token = strtok(line, ",");        

        int numValues = 0;
        char *csv_values[MAX_NUM_COLUMN];
        while (token != NULL && numValues < MAX_NUM_COLUMN) {          
            csv_values[numValues] = token;  

            float temp_float_save = atof(csv_values[numValues]);           
            dataset[numRows].iris_values[numValues] = round(temp_float_save * 100);
            
            if (numValues == MAX_NUM_COLUMN - 1) {
                // Clean the string to remove the \n
                size_t length = strcspn(csv_values[numValues], "\n");
                csv_values[numValues][length] = '\0'; 
                    
                dataset[numRows].iris_class = csv_values[numValues];
            }

            numValues++; 
            token = strtok(NULL, ",");
        }
        numRows++;               
    }

    for (size_t i = 0; i < numRows; i++){
        printf("Element %d:\n", i);
        printf("iris_values[0]: %d\n", dataset[i].iris_values[0]);
        printf("iris_values[1]: %d\n", dataset[i].iris_values[1]);
        printf("iris_values[2]: %d\n", dataset[i].iris_values[2]);
        printf("iris_values[3]: %d\n", dataset[i].iris_values[3]);
        printf("iris_class: %s\n\n", dataset[i].iris_class);
    }
      

    fclose(file);
    return 0;
}