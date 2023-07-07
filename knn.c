#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256
#define INITIAL_CAPACITY 10
#define MAX_NUM_COLUMN 5
#define K 5

typedef struct {
    // features = sepal length (cm), sepal width (cm), petal length (cm), petal width (cm)
    int* features;
    char* label;
} DataPoint;

typedef struct {
    DataPoint* dataPoints;
    int numRows;
    int capacity;
} DataSet;

typedef struct {
    float distance;
    char* label;
} Distance;

void freeDataSet(DataSet* dataset) {
    for (size_t i = 0; i < dataset->numRows; i++) {
        free(dataset->dataPoints[i].features);
        free(dataset->dataPoints[i].label);
    }
    free(dataset->dataPoints);
}

void resizeDataSet(DataSet* dataset) {
    dataset->capacity *= 2;
    dataset->dataPoints = realloc(dataset->dataPoints, dataset->capacity * sizeof(DataPoint));

    if (dataset->dataPoints == NULL) {
        perror("Memory reallocation failed.\n");
        freeDataSet(dataset);
        exit(1);
    }
}

void shuffleDataSet(DataSet* dataset) {
    for (size_t i = 0; i < dataset->numRows; i++) {
        DataPoint temp;
        int j = rand() % (i + 1);

        temp = dataset->dataPoints[i];
        dataset->dataPoints[i] = dataset->dataPoints[j];
        dataset->dataPoints[j] = temp;
    }
}

void fillSet(DataSet* originalSet, DataSet* filledSet, int size, int startnumber) {
    for (size_t i = 0; i < size; i++){
        filledSet->dataPoints[i].features = malloc((MAX_NUM_COLUMN - 1) * sizeof(int));
        memcpy(filledSet->dataPoints[i].features,
         originalSet->dataPoints[startnumber + i].features, ((MAX_NUM_COLUMN - 1) * sizeof(int)));

        filledSet->dataPoints[i].label = malloc(strlen(originalSet->dataPoints[startnumber + i].label) * sizeof(char));
        strcpy(filledSet->dataPoints[i].label, originalSet->dataPoints[startnumber + i].label);
    }
}

void splitDataSet(DataSet* originalSet, float splitRatio, DataSet* trainingSet, DataSet* testSet) {
    const int TRAIN_SIZE = originalSet->numRows * splitRatio;
    const int TEST_SIZE = originalSet->numRows - TRAIN_SIZE;

    trainingSet->dataPoints = malloc(TRAIN_SIZE * sizeof(DataPoint));
    trainingSet->numRows = TRAIN_SIZE;
    testSet->dataPoints = malloc(TEST_SIZE * sizeof(DataPoint));
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

float euclidean_distance(DataPoint* featureList_one, DataPoint* featureList_two, int column_len) {
    float distance = 0.0;
    const int SQUARED = 2;

    for (size_t i = 0; i < column_len; i++) {
        distance += powf(featureList_one->features[i] - featureList_two->features[i], SQUARED);
    }
    return sqrtf(distance); 
}

void trainKNN(Distance* distance, DataPoint* testFeatures, DataSet* trainingSet) {    
    // for (size_t i = 0; i < testFeatures->numRows; i++) {
    for (size_t j = 0; j < trainingSet->numRows; j++) {
       distance[j].distance = euclidean_distance(testFeatures->features, trainingSet->dataPoints[j].features, MAX_NUM_COLUMN - 1);
    }
    // }   
}


int main() {
    DataSet dataset;
    dataset.numRows = 0;
    dataset.capacity = INITIAL_CAPACITY;
    dataset.dataPoints = malloc(dataset.capacity * sizeof(DataPoint));

    // Open file and check if file is valid.
    char line[MAX_LINE_LENGTH];
    FILE* file = fopen("data/iris_dataset.csv", "r");
    if (file == NULL) {
        perror("Failed to open the file.\n");
        return 1;
    }

    // Skip header
    fgets(line, sizeof(line), file);

    // Process the lines in the csv file
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, ",");
        int numValues = 0;
        char* csv_values[MAX_NUM_COLUMN];

        while (token != NULL && numValues < MAX_NUM_COLUMN) {
            csv_values[numValues] = token;
            numValues++;
            token = strtok(NULL, ",");
        }

        // Resize dataset if necessary
        if (dataset.numRows == dataset.capacity) {
            resizeDataSet(&dataset);
        }

        dataset.dataPoints[dataset.numRows].features = malloc((MAX_NUM_COLUMN - 1) * sizeof(int));
        for (size_t i = 0; i < MAX_NUM_COLUMN - 1; i++) {
            float float_to_int_save = atof(csv_values[i]);
            dataset.dataPoints[dataset.numRows].features[i] = round(float_to_int_save * 100);
        }

        // Clean the string to remove the \n
        size_t length = strcspn(csv_values[MAX_NUM_COLUMN - 1], "\n");
        csv_values[MAX_NUM_COLUMN - 1][length] = '\0';
        dataset.dataPoints[dataset.numRows].label = malloc((length) * sizeof(char));
        strcpy(dataset.dataPoints[dataset.numRows].label, csv_values[MAX_NUM_COLUMN - 1]);

        dataset.numRows++;
    }

    // Close the file
    fclose(file);

    DataSet trainingSet;
    DataSet testSet;
    const float SPLITRATIO = 0.7;

    splitDataSet(&dataset, SPLITRATIO, &trainingSet, &testSet);
    freeDataSet(&dataset);

    Distance* neighbors;
    trainKNN(neighbors, &testSet.dataPoints[1], &trainingSet);

    return 0;
}
