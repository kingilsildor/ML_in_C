#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LINE_LENGTH 256
#define MAX_NUM_FEATURES 10
#define MAX_NUM_INSTANCES 100

struct Instance {
    double features[MAX_NUM_FEATURES];
    int label;
};

double calculateEuclideanDistance(double* instance1, double* instance2, int numFeatures) {
    double distance = 0.0;

    for (int i = 0; i < numFeatures; i++) {
        distance += pow((instance1[i] - instance2[i]), 2);
    }

    return sqrt(distance);
}

int predictLabel(struct Instance* instances, int numInstances, double* testInstance, int numFeatures, int k) {
    double distances[MAX_NUM_INSTANCES];
    int labels[MAX_NUM_INSTANCES] = { 0 };

    // Calculate distances from testInstance to all training instances
    for (int i = 0; i < numInstances; i++) {
        distances[i] = calculateEuclideanDistance(instances[i].features, testInstance, numFeatures);
    }

    // Sort the distances in ascending order
    for (int i = 0; i < numInstances - 1; i++) {
        for (int j = i + 1; j < numInstances; j++) {
            if (distances[i] > distances[j]) {
                double temp = distances[i];
                distances[i] = distances[j];
                distances[j] = temp;

                int tempLabel = instances[i].label;
                instances[i].label = instances[j].label;
                instances[j].label = tempLabel;
            }
        }
    }

    // Count the labels of the k nearest neighbors
    for (int i = 0; i < k; i++) {
        labels[instances[i].label]++;
    }

    // Find the majority label
    int maxLabelCount = 0;
    int predictedLabel = -1;
    for (int i = 0; i < numInstances; i++) {
        if (labels[i] > maxLabelCount) {
            maxLabelCount = labels[i];
            predictedLabel = i;
        }
    }

    return predictedLabel;
}

int main() {
    FILE* file = fopen("data.csv", "r"); // Open the CSV file for reading
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    double features[MAX_NUM_FEATURES];
    struct Instance instances[MAX_NUM_INSTANCES];
    int numInstances = 0;
    int numFeatures = 0;

    // Read the CSV file
    while (fgets(line, sizeof(line), file) != NULL && numInstances < MAX_NUM_INSTANCES) {
        char* token = strtok(line, ",");
        int col = 0;

        while (token != NULL && col < MAX_NUM_FEATURES + 1) {
            if (col < MAX_NUM_FEATURES) {
                features[col] = atof(token);
                col++;
            }
            else {
                instances[numInstances].label = atoi(token);
            }
            token = strtok(NULL, ",");
        }

        // Check if the number of features is consistent
        if (numInstances == 0) {
            numFeatures = col;
        }
        else if (col != numFeatures) {
            printf("Inconsistent number of features in the dataset.\n");
            fclose(file);
            return 1;
        }

        // Copy the features to the instance
        for (int i = 0; i < numFeatures; i++) {
            instances[numInstances].features[i] = features[i];
        }

        numInstances++;
    }

    fclose(file); // Close the file

    // Test a new instance
    double testInstance[MAX_NUM_FEATURES] = { 6.3, 2.7, 4.9, 1.8 }; // Modify this with your own test instance
    int k = 3; // Number of neighbors to consider

    int predictedLabel = predictLabel(instances, numInstances, testInstance, numFeatures, k);

    printf("Predicted label: %d\n", predictedLabel);

    return 0;
}
