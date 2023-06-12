#include <stdio.h>

#define MAX_LINE_LENGTH 30
#define MAX_TOKEN_LENGTH 100

int main(void){
    FILE *file;
    char line[MAX_LINE_LENGTH];

    file = fopen("data/iris_dataset.csv", "r");
    if (file == NULL){
        perror("Error opening file");
        return(-1);
    }
    
    while(fgets(line, sizeof(line), file)){
        char *token = strtok(line, ",");

        while(token != NULL){
            printf("%s\n",token);
            token = strtok(NULL, ",");
        }
    }

    fclose(file);
    
    return 0;
}
