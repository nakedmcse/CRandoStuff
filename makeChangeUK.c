// Make change for 2 pounds in UK
// https://projecteuler.net/problem=31

#include <stdio.h>
#include <time.h>

// This will EVENTUALLY work
int makeChangeUKLoop() {
    int solutions = 1;  // 200 is a solution
    for (int hundred = 0; hundred <= 2; hundred++) {
        for (int fifty = 0; fifty <= 4; fifty++) {
            for (int twenty = 0; twenty <= 10; twenty++) {
                for (int ten = 0; ten <= 20; ten++) {
                    for (int five = 0; five <= 40; five++) {
                        for (int two = 0; two <= 100; two++) {
                            for (int one = 0; one <= 200; one++) {
                                if ((hundred*100)+(fifty*50)+(twenty*20)+(ten*10)+(five*5)+(two*2)+one == 200) solutions++;
                            }
                        }
                    }
                }
            }
        }
    }
    return solutions;
}

// This will run in one loop iteration
int makeChangeUKDP() {
    int coins[] = {1, 2, 5, 10, 20, 50, 100, 200};
    int dp[201] = {0};
    dp[0] = 1;  // There is one way to make change for 0 - initial condition
    for (int c = 0; c < 8; c++) {
        for (int i = coins[c]; i < 201; i++) dp[i] += dp[i - coins[c]];
    }
    return dp[200];
}

int main(void) {
    clock_t start_time = clock();
    int solutions_loop = makeChangeUKLoop();
    double elapsedLoop = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    start_time = clock();
    int solutions_dp = makeChangeUKDP();
    double elapsedDP = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Number of ways to make 2 pounds (Simple Loop - %fs): %d\n", elapsedLoop, solutions_loop);
    printf("Number of ways to make 2 pounds (Dynamic Programming - %fs): %d\n", elapsedDP, solutions_dp);
}