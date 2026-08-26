#include <bits/stdc++.h>
using namespace std;

/*
Problem StatementAn avatar moves on a grid of size width $\times$ height starting at an initial position position = [x, y].Movements are driven by a sequence of commands in a string moves, composed of characters 'U' (up), 'D' (down), 'R' (right), and 'L' (left).There are two paired portals located at portal_A = [x1, y1] and portal_B = [x2, y2].If moving into a cell containing a portal, the avatar immediately teleports to the other portal's cell before the next move.Moves attempting to cross the outer boundary of the grid are ignored (the avatar stays in place).Return the final coordinates [x, y] after executing all moves.
*/

vector<int> compute_final_position(int width, int height, vector<int> position, vector<int> portal_A, vector<int> portal_B, string moves) {
    int x = position[0], y = position[1];

    for (char move : moves) {
        int nx = x, ny = y;

        if (move == 'U') ny--;
        else if (move == 'D') ny++;
        else if (move == 'L') nx--;
        else if (move == 'R') nx++;

        if (nx < 0 || nx >= width || ny < 0 || ny >= height) {
            continue;
        }

        x = nx;
        y = ny;

        // teleportation check
        if (x == portal_A[0] && y == portal_A[1]) {
            x = portal_B[0];
            y = portal_B[1];
        } else if (x == portal_B[0] && y == portal_B[1]) {
            x = portal_A[0];
            y = portal_A[1];
        }
    }

    return {x, y};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
