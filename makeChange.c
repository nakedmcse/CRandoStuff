// Find the average number of coins to make change
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#define MAXCHANGER 60
#define MAXCHANGEDP 99

// Recursive solution
long makeChangeRecursive(int value, int coins, bool solutions) {
    coins++;
    if (value > MAXCHANGER) return 0;                        // Bust
    if (value == MAXCHANGER) return solutions ? 1 : coins;   // Change made
    return makeChangeRecursive(value+1, coins, solutions) + makeChangeRecursive(value+5, coins, solutions) +
        makeChangeRecursive(value+10, coins, solutions) + makeChangeRecursive(value+25, coins, solutions);
}

// Dynamic Programming solution
long makeChangeDP(bool solutions) {
    long dp[MAXCHANGEDP + 1] = {0};
    long coins[MAXCHANGEDP + 1] = {0};

    dp[1] = 1; // There is one way to make change for 0 value
    coins[0] = 1; // Start with one coin

    // Fill the DP table using the coin denominations
    for (int i = 1; i <= MAXCHANGEDP; i++) {
        if (i >= 1) {
            dp[i] += dp[i - 1];
            coins[i] += coins[i - 1] + dp[i - 1];
        }
        if (i >= 5) {
            dp[i] += dp[i - 5];
            coins[i] += coins[i - 5] + dp[i - 5];
        }
        if (i >= 10) {
            dp[i] += dp[i - 10];
            coins[i] += coins[i - 10] + dp[i - 10];
        }
        if (i >= 25) {
            dp[i] += dp[i - 25];
            coins[i] += coins[i - 25] + dp[i - 25];
        }
    }

    return solutions ? dp[MAXCHANGEDP] : coins[MAXCHANGEDP];
}

int main(void) {
    clock_t start_time = clock();
    long totalCoins = makeChangeRecursive(1, 1, false);
    long totalSolutions = makeChangeRecursive(1, 1, true);
    double elapsedR = (double)(clock() - start_time) / CLOCKS_PER_SEC;

    start_time = clock();
    long totalCoinsDP = makeChangeDP(false);
    long totalSolutionsDP = makeChangeDP(true);
    double elapsedDP = (double)(clock() - start_time) / CLOCKS_PER_SEC;

    printf("%d max change\n", MAXCHANGER);
    printf("%ld avg coins\n", totalCoins/totalSolutions);
    printf("%ld total coins and %ld recursive solutions in %fs\n", totalCoins, totalSolutions, elapsedR);

    printf("%d max change\n", MAXCHANGEDP);
    printf("%ld avg coins\n", totalCoinsDP/totalSolutionsDP);
    printf("%ld total coins and %ld DP solutions in %fs\n", totalCoinsDP, totalSolutionsDP, elapsedDP);

    return 0;
}