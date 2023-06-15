#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_NUM_COLUMNS 5

struct Data {
    float x1;
    float x2;
    float x3;
    float x4;
    char y[15];
};

int main() {
    FILE* file = fopen("data/iris_dataset.csv", "r"); // Open the CSV file for reading
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    char* token;
    struct Data* dataArray = NULL;
    int numData = 0;

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
            // Create a new struct Data instance
            struct Data newData;

            // Copy the values to the struct members
            // Convert string to float            
            newData.x1 = atof(values[0]); 
            newData.x2 = atof(values[1]);
            newData.x3 = atof(values[2]);
            newData.x4 = atof(values[3]); 
            strcpy(newData.y, values[4]);

            // Increase the size of the dataArray
            numData++;
            dataArray = (struct Data*)realloc(dataArray, numData * sizeof(struct Data));
            if (dataArray == NULL) {
                printf("Failed to allocate memory.\n");
                fclose(file);
                return 1;
            }

            // Add the new struct Data instance to the dataArray
            dataArray[numData - 1] = newData;
        } else {
            printf("Line does not have the expected number of columns.\n");
        }
    }

    // Print the data
    for (int i = 0; i < numData; i++) {
        printf("Data[%d]:\n", i + 1);
        printf("Column 1: %f\n", dataArray[i].x1);
        printf("Column 2: %f\n", dataArray[i].x2);
        printf("Column 3: %f\n", dataArray[i].x3);
        printf("Column 4: %f\n", dataArray[i].x4);
        printf("Column 5: %s\n", dataArray[i].y);
        printf("\n");
    }

    // Free the memory allocated for the dataArray
    free(dataArray);

    fclose(file); // Close the file

    return 0;
}
