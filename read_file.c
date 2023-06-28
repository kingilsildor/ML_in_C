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
    float iris_values[MAX_NUM_COLUMN - 1];
    char *iris_class;
};

int main(){
    char line[MAX_LINE_LENGTH];    
    struct Iris_Data data[MAX_NUM_ROWS];
    char *token;
    

    // Open file and check if file is valid.
    FILE* file = fopen("data/iris_dataset.csv", "r");
    if (file == NULL) {
        perror("Failed to open the file.\n");
        return 1;
    }

    // Process the lines in the csv file
    int numRows = 0; 

    while (fgets(line, sizeof(line), file) != NULL) {
        char *values[MAX_NUM_COLUMN];
        int numValues = 0;

        token = strtok(line, ",");
        while (token != NULL && numValues < MAX_NUM_COLUMN) {          
            values[numValues] = token;             
            
            float temp_float = atof(values[numValues]);
            data[numRows].iris_values[numValues] = floor(temp_float * 100) / 100;

            if (numValues == MAX_NUM_COLUMN - 1) {
                // Clean the string to remove the \n
                size_t length = strcspn(values[numValues], "\n");
                values[numValues][length] = '\0'; 
                    
                data[numRows].iris_class = values[numValues];
            }

            numValues++; 
            token = strtok(NULL, ",");
        }
        numRows++;               
    } 

    // for (int i = 1; i < 10; i++) {
    //     printf("Element %d:\n", i);
    //     printf("iris_values[0]: %.2f\n", data[i].iris_values[0]);
    //     printf("iris_values[1]: %.2f\n", data[i].iris_values[1]);
    //     printf("iris_values[2]: %.2f\n", data[i].iris_values[2]);
    //     printf("iris_values[3]: %.2f\n", data[i].iris_values[3]);
    //     printf("iris_class: %s\n", data[i].iris_class);
    // }

    

    fclose(file);
    return 0;
}