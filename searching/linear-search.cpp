#include <bits/stdc++.h>

using namespace std;

int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
         if (arr[i] == key) 
            return i;
    }
    return -1;
}

int main() {
    int n, key;
    cin >> n;
    
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "Enter the element you want to search for: ";
    cin >> key;
    cout << linearSearch(arr, n, key) << endl;
    return 0;
}
