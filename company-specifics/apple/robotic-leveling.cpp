#include<bits/stdc++.h>
using namespace std;

/*
You control a mechanical claw moving left and right across $N$ stacks of boxes.Goal: Distribute all boxes as evenly as possible from left to right.State Parameters:clawPos: Current index of the claw ($0$-indexed).boxes: Array of integers representing the number of boxes in each stack.boxInClaw: Boolean indicating if the claw is currently carrying a box.Valid Return Commands: "LEFT", "RIGHT", "PICK", or "PLACE".
explanation of problem:
Imagine you are operating a mechanical claw in a warehouse. Below the claw is a row of stacks of boxes.
Some stacks are too high (they have extra boxes).
Some stacks are too short (they need more boxes).
Your goal is to move boxes around until every stack is as even in height as possible.
If the total number of boxes doesn't divide perfectly across all stacks, the extra leftover boxes must end up in the leftmost stacks.
Every second, the system hands you three pieces of information:
clawPos: Which stack the claw is currently standing above.
boxes: An array showing how many boxes are in each stack right now.
boxInClaw: Whether the claw is currently holding a box (true) or empty (false).
You must return one single action per second: "LEFT", "RIGHT", "PICK", or "PLACE".
*/

/*
Approach:
(1) figure out the ideal height of every stack : count the total number of boxes (including the one in the claw, if holding one). Divide total boxes by total stacks to get the average height. Calculate any remainder boxes. For eg, if u have 7 boxes and 3 stacks - the average height is 2 with remainder of 1. The ideal height becomes [3, 2, 2] (extra box got the leftmost stack at index 0)

(2) decide the action based on what the claw is holding:
(i) if the claw is holding a box (boxInClaw = true) : 
-- check if the current stack needs a box (is box[clawPos] < expected[clawPos] ? ) if yes, return "PLACE".
-- if the current stack doesn't need a box search left and right (clawPos +- i) to find the nearest stack that needs a box, and move toward it ("LEFT" or "RIGHT")
(ii) if the claw is EMPTY (boxInClaw = false)
-- check if the current stack has extra boxes (is boxes[clawPos] > expected[clawPos] ? If yes, return "PICK".
-- if the current stack doesn't have extra boxes, search left and right (clawPos +- i) to find the nearest stack with extra boxes, and move toward it ("LEFT" or "RIGHT")

O(n)
*/

string solve(int clawPos, vector<int>& boxes, bool boxInClaw) {
    int n = boxes.size();

    // calculate total boxes (include the one currently held in the claw)
    int totalBoxes = accumulate(boxes.begin(), boxes.end(), 0);
    if (boxInClaw) {
        totalBoxes++;
    }

    // determine target height for each stack
    // remainder boxes are placed left-to-right (stacks 0 to remainder - 1)
    int average = totalBoxes / n;
    int remainder = totalBoxes % n;

    vector<int> expected(n);
    for (int i = 0; i < n; i++) {
        expected[i] = average + (i < remainder ? 1 : 0);
    }

    // carrying a box -> find closest deficit stack
    if (boxInClaw) {
        if (boxes[clawPos] < expected[clawPos]) {
            return "PLACE";
        }
        for (int i = 1; i < n; i++) {
            if (clawPos - i >= 0 && boxes[clawPos - i] < expected[clawPos - i]) {
                return "LEFT";
            }
            if (clawPos + i < n && boxes[clawPos + i] < expected[clawPos + i]) {
                return "RIGHT";
            }
        }
    }

    // claw empty -> find closest surplus stack
    else {
        if (boxes[clawPos] > expected[clawPos]) {
            return "PICK";
        }
        for (int i = 1; i < n; i++) {
            if (clawPos - i >= 0 && boxes[clawPos - i] > expected[clawPos - i]) {
                return "LEFT";
            }
            if (clawPos + i < n && boxes[clawPos + i] > expected[clawPos + i]) {
                return "RIGHT";
            }
        }
    }

    return "";
}

int main() {
    return 0;
}
