#include <stdio.h>
#include <limits.h>

int solve(int *arr, int n) {
    if (n < 2) return INT_MIN;
    int mx = INT_MIN, secmx = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] > mx) {
            if (mx != INT_MIN) secmx = mx;
            mx = arr[i];
        } else if (arr[i] != mx && arr[i] > secmx) secmx = arr[i];
    }
    return secmx;
}

int main() {
    int n; scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int ans = solve(arr, n);
    if (ans == INT_MIN) printf("Not Found \n");
    else printf("Second largest = %d\n", ans);

    return 0;
}
