#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_NUM_ROWS 256
#define MAX_NUM_COLUMN 5
#define MAX_TOKEN_LENGTH 100

struct Data{
    // Array data: [x1, x2, x3, x4, y]
    float x[MAX_NUM_COLUMN - 1];
    char *y;
};

int main(){
    char line[MAX_LINE_LENGTH];
    char *token;
    struct Data data[MAX_NUM_ROWS];
    int numRows = 0; 

    // Open file and check if file is valid.
    FILE* file = fopen("data/iris_dataset.csv", "r");
    if (file == NULL) {
        perror("Failed to open the file.\n");
        return 1;
    }

    // Process the lines in the csv file
    while (fgets(line, sizeof(line), file) != NULL) {
        char * values[MAX_NUM_COLUMN];
        int numValues = 0;

        token = strtok(line, ",");
        while (token != NULL && numValues < MAX_NUM_COLUMN) {          
            values[numValues] = token;
            numValues++;  
            token = strtok(NULL, ",");
        }

        if (numValues == MAX_NUM_COLUMN) {
            for (size_t i = 0; i < numValues; i++) {

                if (i == MAX_NUM_COLUMN - 1) {
                    // Clean the string to remove the \n
                    size_t length = strcspn(values[i], "\n");
                    values[i][length] = '\0';
                    
                    data[numRows].y = malloc(sizeof(char) * 20);
                    data[numRows].y = values[i];

                    if(data[numRows].y == NULL){
                        printf("Memory allocation failed for data[%d].y\n", i);
                    }
                } 
                data[numRows].x[i] = atof(values[i]);
            }
        }

        numRows++;          
    }
    fclose(file);

    for (int i = 1; i < 10; i++) {
        // printf("Element %d:\n", i);
        // printf("x[0]: %f\n", data[i].x[0]);
        // printf("x[1]: %f\n", data[i].x[1]);
        // printf("x[2]: %f\n", data[i].x[2]);
        // printf("x[3]: %f\n", data[i].x[3]);
        // printf("y: %s\n", data[i].y);
    }

    return 0;
}