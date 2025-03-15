#ifndef KNAPSACK_H
#define KNAPSACK_H

// Function to find the maximum of two numbers
int max(int a, int b);

// Function to maximize the total value of the catch
int** knapsack(int capacity, int* sizes, int* values, int numOfLobsters, int* max_value);
#endif // KNAPSACK_H
