#include <stdlib.h>
#include "knapsack.h"

// Function to calculate the maximum of two numbers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Function to calculate the maximum value of the catch
int** knapsack(int capacity, int* sizes, int* values, int numOfLobsters, int* max_value)
{
    int **dp = (int**)malloc((numOfLobsters + 1) * sizeof(int*));
    for (int i = 0; i <= numOfLobsters; i++)
    {
        dp[i] = (int*)malloc((capacity + 1) * sizeof(int));
    }

    for (int i = 0; i <= numOfLobsters; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (sizes[i - 1] <= w)
            {
                dp[i][w] = (values[i - 1] + dp[i - 1][w - sizes[i - 1]] > dp[i - 1][w]) ?
                           values[i - 1] + dp[i - 1][w - sizes[i - 1]] : dp[i - 1][w];
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    *max_value = dp[numOfLobsters][capacity];

    return dp;
}
