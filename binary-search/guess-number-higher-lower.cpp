#include<bits/stdc++.h>
using namespace std;
/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessNumber(int n) {
        int left = 0, right = n;
        while (left <= right) {
            int middle = (left + right) / 2;
            int x = guess(middle);
            if (x == 0) return middle;
            else if (x == 1) left = middle + 1;
            else right = middle - 1;
        }
    }
};
