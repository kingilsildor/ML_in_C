#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256
#define INITIAL_CAPACITY 10
#define MAX_NUM_COLUMN 5
#define MAX_TOKEN_LENGTH 40
#define K 5

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

int compare(const void* point_one, const void* point_two){
    const struct Euclidean_Distance* array_one = (const struct Euclidean_Distance* ) point_one;
    const struct Euclidean_Distance* array_two = (const struct Euclidean_Distance* ) point_two;

    if(array_one->distance > array_two->distance){
        return 1;
    }
    
    if(array_one->distance < array_two->distance){
        return -1;
    }

    if (array_one->distance == array_two->distance){
        return 0;
    }
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

            float float_to_int_save = atof(csv_values[numValues]);           
            dataset[numRows].iris_values[numValues] = round(float_to_int_save * 100);
            
            if (numValues == MAX_NUM_COLUMN - 1) {
                // Clean the string to remove the \n
                size_t length = strcspn(csv_values[numValues], "\n");
                csv_values[numValues][length] = '\0'; 

                dataset[numRows].iris_class = malloc((length) * sizeof(char));
                strcpy(dataset[numRows].iris_class, csv_values[numValues]);
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
    for (int i = numRows - 1; i > 0; i--) {
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

    for (size_t i = 0; i < numRows; i++) {
        free(dataset[i].iris_class);
    }
    free(dataset);


    struct Euclidean_Distance distance_array[numRows];
    const int ELEMENT = 50;
    for (size_t i = 0; i < TRAIN_SIZE; i++) {
        if (i == ELEMENT){
            continue;
        }

        distance_array[i].distance = euclidean_distance(&train_data[ELEMENT], &train_data[i], MAX_NUM_COLUMN - 1);
        distance_array[i].element_one = ELEMENT;
        distance_array[i].element_two = i;         
    }

    qsort(distance_array, TRAIN_SIZE, sizeof(struct Euclidean_Distance), compare);
    for (size_t i = 1; i < K; i++) {
        int temp = distance_array[i].element_two;
        printf("%s\n", train_data[temp].iris_class);
    }

   
    free(train_data);
    free(test_data);
    return 0;
}