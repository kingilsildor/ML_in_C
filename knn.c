#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_TOKEN_LENGTH 100

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    
    file = fopen("data/iris_dataset.csv", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        // Tokenize the line using commas as delimiters
        char *token;
        token = strtok(line, ",");
        
        while (token != NULL) {
            // Process each token here
            printf("Token: %s\n", token);

            // Move to the next token
            token = strtok(NULL, ",");
        }
    }
    
    fclose(file);
    
    return 0;
}
