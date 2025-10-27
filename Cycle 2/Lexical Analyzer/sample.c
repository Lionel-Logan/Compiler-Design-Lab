#include <stdio.h>

int main() {
    int i = 0;
    int sum = 0;

    while (i < 5) {
        if (i % 2 == 0)
            sum += i;
        else
            sum -= i;
        i++;
    }

    for (int j = 0; j < 5; j++) {
        sum += j;
    }

    printf("Final sum = %d\n", sum);
    return 0;
}
