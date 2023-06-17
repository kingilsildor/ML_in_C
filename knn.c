#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_NUM_ROWS 256
#define MAX_NUM_COLUMN 5
#define MAX_TOKEN_LENGTH 100

struct Data{
    // Array data: [x1, x2, x3, x4, y]
    float x[MAX_NUM_COLUMN - 1];
    char* y;
};


int main(){
    char line[MAX_LINE_LENGTH];
    char *token;
    struct Data data[MAX_NUM_ROWS];
    // char data[MAX_NUM_ROWS][MAX_NUM_COLUMN][MAX_LINE_LENGTH];
    int numRows = 0; 

    // Open file and check if file is valid.
    FILE* file = fopen("data/iris_dataset.csv", "r");
    if (file == NULL) {
        perror("Failed to open the file.\n");
        fclose(file);
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
            // skip the header
            for (size_t i = 0; i < numValues - 1; i++) {
                data[numRows].x[i] = atof(values[i]); 
            }
        }
        numRows++;          
    }

    for (int i = 1; i < 10; i++) {
        printf("Element %d:\n", i);
        printf("x[0]: %f\n", data[i].x[0]);
        printf("x[1]: %f\n", data[i].x[1]);
        printf("x[2]: %f\n", data[i].x[2]);
        printf("x[3]: %f\n", data[i].x[3]);
    }

    fclose(file);
    return 0;
}
