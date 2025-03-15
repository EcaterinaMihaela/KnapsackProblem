def knapsack(capacity, sizes, values, n):
    dp = [[0 for _ in range(capacity + 1)] for _ in range(n + 1)]

    for i in range(1, n + 1):
        for w in range(1, capacity + 1):
            if sizes[i - 1] <= w:
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - sizes[i - 1]], dp[i - 1][w])
            else:
                dp[i][w] = dp[i - 1][w]

    max_value = dp[n][capacity]

    return dp, max_value
