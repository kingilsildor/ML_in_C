#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_NUM_COLUMNS 5
#define MAX_NUM_ROWS 100

int main() {
    FILE* file = fopen("../data/iris_dataset.csv", "r"); // Open the CSV file for reading
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    char* token;
    char data[MAX_NUM_ROWS][MAX_NUM_COLUMNS][MAX_LINE_LENGTH];
    int numRows = 0;

    // Read the header line (optional)
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Failed to read the header line.\n");
        fclose(file);
        return 1;
    }

    // Process the remaining lines
    while (fgets(line, sizeof(line), file) != NULL) {
        // Tokenize the line based on the comma delimiter
        char* values[MAX_NUM_COLUMNS];
        int numValues = 0;

        token = strtok(line, ",");
        while (token != NULL && numValues < MAX_NUM_COLUMNS) {
            values[numValues] = token;
            numValues++;
            token = strtok(NULL, ",");
        }

        // Check if the line has the expected number of columns
        if (numValues == MAX_NUM_COLUMNS) {
            // Copy the values to the 2D array
            for (int i = 0; i < numValues; i++) {
                strcpy(data[numRows][i], values[i]);
            }

            // Increase the number of rows
            numRows++;
            if (numRows >= MAX_NUM_ROWS) {
                printf("Maximum number of rows reached.\n");
                break;
            }
        } else {
            printf("Line does not have the expected number of columns.\n");
        }
    }

    // Print the data
    for (int i = 0; i < numRows; i++) {
        printf("Data[%d]:\n", i + 1);
        for (int j = 0; j < MAX_NUM_COLUMNS; j++) {
            printf("Column %d: %s\n", j + 1, data[i][j]);
        }
        printf("\n");
    }

    fclose(file); // Close the file

    return 0;
}
