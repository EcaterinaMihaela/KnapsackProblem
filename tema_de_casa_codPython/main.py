import random
import time
from knapsack import knapsack

MAX_SIZE = 30
MAX_VALUE = 200
MAX_NO_LOBSTERS = 10000

def main():
    numOfLobsters = int(input("Enter the number of lobsters: \n"))

    # Use an output file to display the information
    try:
        outputFile = open("Data/output.txt", "w")
    except IOError:
        print("Failed to open the file.")
        return

    #Verify if the number of lobsters is a positive number
    if numOfLobsters < 0:
        outputFile.write("The number of lobsters has to be a positive number!")
        return
    
    # Error if the number of lobsters exceeds maximum allowed size
    if numOfLobsters > MAX_NO_LOBSTERS:
        outputFile.write(f"Too many lobsters! (maximum {MAX_NO_LOBSTERS}).")
        return

    # Declare a list of size equal to the number of lobsters to store the size (in cm) of each lobster
    sizes = [0] * numOfLobsters
    values = [0] * numOfLobsters

    random.seed(time.time())

    # Generate random sizes and values for the lobsters
    outputFile.write("Lobsters sizes and values:\n")
    for i in range(numOfLobsters):
        sizes[i] = random.randint(1, MAX_SIZE)
        values[i] = random.randint(1, MAX_VALUE)
        outputFile.write(f"Lobster {i + 1}: Size = {sizes[i]} cm, Value = {values[i]} gold coins\n")

    # Enter from keyboard the capacity
    capacity = int(input("Enter the capacity of the bag: "))
    outputFile.write("\n");
    outputFile.write(f"The capacity of the bag is {capacity}\n")
    outputFile.write("\n");

    # Error if the capacity is negative
    if capacity < 0:
        outputFile.write("Capacity has to be a natural number (in cm!)\n")
        return

    dp, max_value = knapsack(capacity, sizes, values, numOfLobsters)

    outputFile.write(f"The max value is: {max_value}\n")
    outputFile.write("\n");
    # Also we calculate & display the favorable combination of lobsters which maximize the total value
    outputFile.write("Selected lobsters:\n")
    currentCapacity = capacity
    for i in range(numOfLobsters, 0, -1):
        if dp[i][currentCapacity] != dp[i - 1][currentCapacity]:
            outputFile.write(f"Lobster {i}: Size = {sizes[i - 1]} cm, Value = {values[i - 1]} gold coins\n")
            currentCapacity -= sizes[i - 1]
            max_value -= values[i - 1]

    outputFile.close()

if __name__ == "__main__":
    main()
