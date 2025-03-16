// Baka Fizzbuzz
#include<stdio.h>

int main(void) {
  for(int i = 0; i < 101; i++) {
    i%15 == 0 ? printf("FizzBuzz\n") : i%3 == 0 ? printf("Fizz\n") : i%5 == 0 ? printf("Buzz\n") : printf("%d\n",i);
  }
  return 0;
}
