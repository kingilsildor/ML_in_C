#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256
#define INITIAL_CAPACITY 10
#define MAX_NUM_COLUMN 5

typedef struct {
    // features = sepal length (cm), sepal width (cm), petal length (cm), petal width (cm)
    int *features;
    char *label;
} DataPoint;

typedef struct {
    DataPoint *dataPoints;
    int numRows;
    int capacity;
} DataSet;

typedef struct {
    float distance;
    char *label;
} Distance;

typedef struct {
    Distance *distance;
    int numRows;
    int capacity;
} Neighborhood;

void freeDataSet(DataSet *dataset) {
    for (size_t i = 0; i < dataset->numRows; i++) {
        free(dataset->dataPoints[i].features);
        free(dataset->dataPoints[i].label);
    }
    free(dataset->dataPoints);
}

void freeNeighborhood(Neighborhood *neighborhood){
    for (size_t i = 0; i < neighborhood->numRows; i++){
        free(&neighborhood->distance[i]);
    }
    free(neighborhood->distance);
}

void resizeDataSet(DataSet *dataset) {
    dataset->capacity *= 2;
    dataset->dataPoints = realloc(dataset->dataPoints, dataset->capacity  * sizeof(DataPoint));

    if (dataset->dataPoints == NULL) {
        perror("Memory reallocation failed.\n");
        freeDataSet(dataset);
        exit(1);
    }
}

void resizeNeighborhood(Neighborhood *neighbors) {
    neighbors->capacity *= 2;
    neighbors->distance = realloc(neighbors->distance, neighbors->capacity  * sizeof(Distance));
}

void shuffleDataSet(DataSet *dataset) {
    for (size_t i = 0; i < dataset->numRows; i++) {
        DataPoint temp;
        int j = rand() % (i + 1);

        temp = dataset->dataPoints[i];
        dataset->dataPoints[i] = dataset->dataPoints[j];
        dataset->dataPoints[j] = temp;
    }
}

void fillSet(DataSet *originalSet, DataSet *filledSet, int size, int startnumber) {
    for (size_t i = 0; i < size; i++){
        filledSet->dataPoints[i].features = malloc((MAX_NUM_COLUMN - 1)  * sizeof(int));
        memcpy(filledSet->dataPoints[i].features,
         originalSet->dataPoints[startnumber + i].features, ((MAX_NUM_COLUMN - 1)  * sizeof(int)));

        filledSet->dataPoints[i].label = malloc(strlen(originalSet->dataPoints[startnumber + i].label)  * sizeof(char));
        strcpy(filledSet->dataPoints[i].label, originalSet->dataPoints[startnumber + i].label);
    }
}

void splitDataSet(DataSet *originalSet, float splitRatio, DataSet *trainingSet, DataSet *testSet) {
    const int TRAIN_SIZE = originalSet->numRows  *splitRatio;
    const int TEST_SIZE = originalSet->numRows - TRAIN_SIZE;

    trainingSet->dataPoints = malloc(TRAIN_SIZE  * sizeof(DataPoint));
    trainingSet->numRows = TRAIN_SIZE;
    testSet->dataPoints = malloc(TEST_SIZE  * sizeof(DataPoint));
    testSet->numRows = TEST_SIZE;

    if (trainingSet->dataPoints == NULL || testSet->dataPoints == NULL){
        perror("Memory allocation failed.\n");
        freeDataSet(originalSet);
        freeDataSet(trainingSet);
        freeDataSet(testSet);
        exit(1);
    }

    shuffleDataSet(originalSet);
    fillSet(originalSet, trainingSet, TRAIN_SIZE, 0);
    fillSet(originalSet, testSet, TEST_SIZE, TRAIN_SIZE);
}

float euclidean_distance(DataPoint *featureList_one, DataPoint *featureList_two, int column_len) {
    float distance = 0.0;
    const int SQUARED = 2;

    for (size_t i = 0; i < column_len; i++) {
        distance += powf(featureList_one->features[i] - featureList_two->features[i], SQUARED);
    }
    return sqrtf(distance); 
}

int compareDistances(const void *a, const void *b){
    const Distance* point_one = (const Distance*)a;
    const Distance* point_two = (const Distance*)b;

    if(point_one->distance > point_two->distance){
        return 1;
    }
    
    if(point_one->distance < point_two->distance){
        return -1;
    }

    if (point_one->distance == point_two->distance){
        return 0;
    }
}

void trainKNN(Neighborhood *neighbors, DataPoint *testFeatures, DataSet *trainingSet, int K) {
    for (size_t i = 0; i < trainingSet->numRows; i++) {
        if(neighbors->numRows == neighbors->capacity){
            resizeNeighborhood(neighbors);
        }       
        
        neighbors->distance[i].distance = euclidean_distance(testFeatures, &trainingSet->dataPoints[i], MAX_NUM_COLUMN - 1);
        // neighbors->distance[i].label = trainingSet->dataPoints[i].label;
        neighbors->distance[i].label = malloc(strlen(trainingSet->dataPoints[i].label) * sizeof(char));
        strcpy(neighbors->distance[i].label, trainingSet->dataPoints[i].label);
        neighbors->numRows++;
    }

    qsort(neighbors->distance, neighbors->numRows, sizeof(Distance), compareDistances);

    if (neighbors->numRows > K) {
        for (int i = K; i < neighbors->numRows; i++) {
            free(neighbors->distance[i].label);
        }
        neighbors->numRows = K;
    }
}


int main() {
    DataSet dataset;
    dataset.numRows = 0;
    dataset.capacity = INITIAL_CAPACITY;
    dataset.dataPoints = malloc(dataset.capacity  * sizeof(DataPoint));

    // Open file and check if file is valid.
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen("data/iris_dataset.csv", "r");
    if (file == NULL) {
        perror("Failed to open the file.\n");
        return 1;
    }

    // Skip header
    fgets(line, sizeof(line), file);

    // Process the lines in the csv file
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ",");
        int numValues = 0;
        char *csv_values[MAX_NUM_COLUMN];

        while (token != NULL && numValues < MAX_NUM_COLUMN) {
            csv_values[numValues] = token;
            numValues++;
            token = strtok(NULL, ",");
        }

        // Resize dataset if necessary
        if (dataset.numRows == dataset.capacity) {
            resizeDataSet(&dataset);
        }

        dataset.dataPoints[dataset.numRows].features = malloc((MAX_NUM_COLUMN - 1)  * sizeof(int));
        for (size_t i = 0; i < MAX_NUM_COLUMN - 1; i++) {
            float float_to_int_save = atof(csv_values[i]);
            dataset.dataPoints[dataset.numRows].features[i] = round(float_to_int_save  *100);
        }

        // Clean the string to remove the \n
        size_t length = strcspn(csv_values[MAX_NUM_COLUMN - 1], "\n");
        csv_values[MAX_NUM_COLUMN - 1][length] = '\0';
        dataset.dataPoints[dataset.numRows].label = malloc((length)  * sizeof(char));
        strcpy(dataset.dataPoints[dataset.numRows].label, csv_values[MAX_NUM_COLUMN - 1]);

        dataset.numRows++;
    }

    // Close the file
    fclose(file);

    DataSet trainingSet;
    DataSet testSet;
    const float SPLITRATIO = 0.7;

    splitDataSet(&dataset, SPLITRATIO, &trainingSet, &testSet);
    // freeDataSet(&dataset);

    
    Neighborhood neighbors;
    neighbors.numRows = 0;
    neighbors.capacity = INITIAL_CAPACITY;
    neighbors.distance = malloc(neighbors.capacity  * sizeof(Distance));   
    const int ELEMENT = 0;
    const int K = 5;
    trainKNN(&neighbors, &testSet.dataPoints[ELEMENT], &trainingSet, K);

    for (size_t i = 0; i < neighbors.numRows; i++) {
        printf("Label[%d]: %s, %2.f\n", i, neighbors.distance[i].label, neighbors.distance[i].distance);
    }
    



    return 0;
}
