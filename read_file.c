#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256
#define INITIAL_CAPACITY 10
#define MAX_NUM_COLUMN 5
#define MAX_TOKEN_LENGTH 40

struct Iris_Data{
    /*
    iris_values1 = sepal length (cm)  iris_values2 = sepal width (cm)
    iris_values3 = petal length (cm)  iris_values4 = petal width (cm)
    */
    int iris_values[MAX_NUM_COLUMN - 1];
    char* iris_class;
};

struct Euclidean_Distance{
    float distance;
    int element_one;
    int element_two;
};

float euclidean_distance(struct Iris_Data* point_one, struct Iris_Data* point_two, int column_len) {
    int distance = 0;
    const int SQUARED = 2;

    for (size_t i = 0; i < column_len; i++){
        distance += powf(point_one->iris_values[i] - point_two->iris_values[i], SQUARED);
    }
    return sqrtf(distance); 
}

int main(){
    struct Iris_Data* dataset = malloc(INITIAL_CAPACITY * sizeof(struct Iris_Data));
    char line[MAX_LINE_LENGTH];  
    int capacity = INITIAL_CAPACITY;
    char* token;
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
        char* csv_values[MAX_NUM_COLUMN];        

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

        // Check if the dataset array needs to be expanded
        if (numRows == capacity) {
            capacity *= 2;
            struct Iris_Data* temp = realloc(dataset, capacity * sizeof(struct Iris_Data));

            if (temp == NULL) {
                perror("Memory reallocation failed.\n");
                free(dataset);
                fclose(file);
                return 1;
            }
            dataset = temp;
        }               
    }

    fclose(file);  


    // Train test split
    const float TRAIN_PERCENTAGE = 0.7;
    const int DATASET_SIZE = numRows;
    const int TRAIN_SIZE = DATASET_SIZE * TRAIN_PERCENTAGE;
    const int TEST_SIZE = DATASET_SIZE - TRAIN_SIZE; 
 
    struct Iris_Data* train_data = malloc(TRAIN_SIZE * sizeof(struct Iris_Data));
    struct Iris_Data* test_data = malloc(TEST_SIZE * sizeof(struct Iris_Data));

    // Shuffle the dataset
    for (int i = 0; i < DATASET_SIZE; i++) {
        int j = rand() % (i + 1);
        struct Iris_Data temp = dataset[i];
        dataset[i] = dataset[j];
        dataset[j] = temp;
    }

    for (int i = 0; i < TRAIN_SIZE; i++) {
        train_data[i] = dataset[i];
    }

    for (int i = 0; i < TEST_SIZE; i++) {
        test_data[i] = dataset[TRAIN_SIZE + i];
    }
        
    free(dataset);


    struct Euclidean_Distance distance_array[numRows];
    for (size_t i = 0; i < numRows; i++) {
        if (i == 0){
            continue;;
        }

        distance_array[i].distance = euclidean_distance(&dataset[0], &dataset[i], MAX_NUM_COLUMN - 1);
        distance_array[i].element_one = 0;
        distance_array[i].element_two = i;         
    }

    for (size_t i = 1; i < numRows; i++){
        printf("Element %d:\n", i);
        printf("distance: %.2f\n", distance_array[i].distance);
        printf("element one: %d\n", distance_array[i].element_one);
        printf("element two: %d\n", distance_array[i].element_two);
        printf("\n");
    }

    
    free(train_data);
    free(test_data);
    return 0;
}