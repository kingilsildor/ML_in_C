#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_NUM_ROWS 256
#define MAX_NUM_COLUMN 5
#define MAX_TOKEN_LENGTH 100

int main(){
    char line[MAX_LINE_LENGTH];
    char *token;
    char data[MAX_NUM_ROWS][MAX_NUM_COLUMN][MAX_LINE_LENGTH];
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
            for (size_t i = 0; i < numValues; i++) {
                strcpy(data[numRows][i], values[i]);
            }

            numRows++;
            if (numRows >= MAX_NUM_ROWS) {
                perror("Maximum number of rows reached.\n");
                break;
            }
        } else {
            perror("Line does not have the expected number of columns.\n");
        }
   
    }

    fclose(file);
    return 0;
}