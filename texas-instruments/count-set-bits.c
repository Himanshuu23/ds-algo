#include <stdio.h>

int solve(int n) {
    int ct = 0;
    while (n) {
        ct += (n & 1);
        n >>= 1;
    }
    return ct;
}

int main() {
    int n; scanf("%d", &n);
    printf("%d\n", solve(n));

    return 0;
}
