#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "knapsack.h"

#define MAX_SIZE 30
#define MAX_VALUE 200
#define MAX_NO_LOBSTERS 10000

int main()
{
    int numOfLobsters;
    printf("Enter the number of lobsters: \n");
    scanf("%d", &numOfLobsters);

    //Use an output file to display the information
    FILE *outputFile = fopen("Data/output.txt", "w");
    if (outputFile == NULL)
    {
        printf("Failed to open the file.\n");
        return -1;
    }

    ///Verify the number of lobsters to be a positive number
    if(numOfLobsters < 0)
    {
        fprintf(outputFile,"The number of lobsters has to be a positive number!\n");
        return -1;
    }

    /// Error if the number of lobsters exceeds maximum allowed size
    if (numOfLobsters > MAX_NO_LOBSTERS)
    {
        fprintf(outputFile,"Too many lobsters! (maximum %d).\n", MAX_NO_LOBSTERS);
        return -1;
    }

    ///Declare a vector of size equal to the number of lobsters to store the size (in cm) of each lobster
    int *sizes = (int*)malloc(numOfLobsters * sizeof(int));

    /// Declare a vector of size equal to the number of lobsters to store the value of each lobster    int *values = (int*)malloc(numOfLobsters * sizeof(int));
    int *values = (int*)malloc(numOfLobsters * sizeof(int));
    /// Check if memory allocation failed
    if(sizes == NULL || values == NULL)
    {
        printf("Memory allocation failed!\n");
        free(sizes); // Free the previously allocated memory
        free(values);
        return -1;
    }
    srand(time(NULL));

    /// Generate random sizes and values for the lobsters
    fprintf(outputFile,"Lobsters sizes and values:\n");
    for(int i = 0; i<numOfLobsters; i++)
    {
        sizes[i] = rand() % MAX_SIZE + 1;
        values[i] = rand() % MAX_VALUE + 1;
        fprintf(outputFile,"Lobster %d: Size = %d cm, Value = %d gold coins\n", i + 1, sizes[i], values[i]);
    }

    int capacity;
    printf("Enter the capacity of the bag: ");
    scanf("%d", &capacity);
    fprintf(outputFile,"\n");
    fprintf(outputFile,"The capacity of the bag is %d\n",capacity);
    fprintf(outputFile,"\n");


    /// Error if the capacity is negative
    if (capacity < 0)
    {
        fprintf(outputFile,"Capacity has to be a natural number(in cm!)");
        return -1;
    }

    int max_value;
    int **dp = knapsack(capacity, sizes, values, numOfLobsters, &max_value);

    //Display the maximaze value in the output file
    fprintf(outputFile,"The max value is: %d\n", max_value);
    fprintf(outputFile,"\n");

    //Also we calculate & display the favorable combination of lobsters which maximize the total value
    fprintf(outputFile,"Selected lobsters:\n");
    int currentCapacity = capacity;
    for (int i = numOfLobsters; i > 0 && max_value > 0; i--)
    {
        if (dp[i][currentCapacity] != dp[i - 1][currentCapacity])
        {
            fprintf(outputFile,"Lobster %d: Size = %d cm, Value = %d gold coins\n", i, sizes[i - 1], values[i - 1]);
            currentCapacity -= sizes[i - 1];
            max_value -= values[i - 1];
        }
    }

    fclose(outputFile);

    //Free the memory allocation
    for (int i = 0; i <= numOfLobsters; i++)
    {
        free(dp[i]);
    }
    free(dp);
    free(sizes);
    free(values);

    return 0;
}
