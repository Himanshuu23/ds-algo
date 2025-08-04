#include <stdio.h>
#include <stdbool.h>

bool solve(int n) {
    return n && ((n & (n - 1)) == 0 );
}

int main() {
    int n; scanf("%d", &n);
    puts(solve(n) ? "Yes" : "No");

    return 0;
}
