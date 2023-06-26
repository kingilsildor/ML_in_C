#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_COLUMN 5
#define MAX_NUM_ROWS 256
#define MAX_LINE_LENGTH 100

struct Data {
    float x[MAX_NUM_COLUMN - 1];
    char* y;
};

int main() {
    char line[MAX_LINE_LENGTH];
    char* token;
    struct Data data[MAX_NUM_ROWS];

    // Allocate memory for y in each data element
    for (int i = 0; i < MAX_NUM_ROWS; i++) {
        data[i].y = malloc(MAX_LINE_LENGTH * sizeof(char));
        if (data[i].y == NULL) {
            // Handle allocation error
            printf("Memory allocation failed for y in data[%d]\n", i);
            exit(1);  // Terminate program
        }
    }

    // Rest of your code...

    // Free allocated memory
    for (int i = 0; i < MAX_NUM_ROWS; i++) {
        free(data[i].y);
    }

    return 0;
}
