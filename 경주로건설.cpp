#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int direction(pair<int, int> from, pair<int, int> to) {
    if(to.second - from.second == 1) return 0;
    else if(from.second - to.second == 1) return 1;
    else if(to.first - from.first == 1) return 2;
    else if(from.first - to.first == 1) return 3;
    return 0;
}

int solution(vector<vector<int>> board) {
    int n = board.size();
    vector<vector<vector<int>>> min_cost(n, vector<vector<int>>(n, vector<int>(4, 100000000)));
    min_cost[0][0][0] = 0; // up
    min_cost[0][0][1] = 0; // down
    min_cost[0][0][2] = 0; // left
    min_cost[0][0][3] = 0; // right

    vector<pair<int, int>> offsets = {
        {-1, 0}, 
        {1, 0},
        {0, -1}, 
        {0, 1}, 
    };

    queue<pair<pair<int, int>, pair<int, int>>> Q;
    Q.push({{0, 0}, {0, 0}});

    while(!Q.empty()) {
        auto curr = Q.front();
        Q.pop();
        int prevX = curr.second.first;
        int prevY = curr.second.second;
        int currX = curr.first.first;
        int currY = curr.first.second;

        for(auto offset: offsets) {
            int newX = currX + offset.first;
            int newY = currY + offset.second;
            if(newX == prevX && newY == prevY) continue;
            if(newX < 0 || newX >= n || newY < 0 || newY >= n) continue;
            if(board[newY][newX] == 1) continue;

            bool isCorner = abs(newY - currY) == 1 ? abs(currX - prevX) == 1 : abs(currY - prevY) == 1;
            int prevDirectionIndex = direction({prevX, prevY}, {currX, currY});
            int cost = isCorner ? min_cost[currY][currX][prevDirectionIndex] + 600 : min_cost[currY][currX][prevDirectionIndex] + 100;
            
            int newDirectionIndex = direction({currX, currY}, {newX, newY});
            if(cost < min_cost[newY][newX][newDirectionIndex]) {
                min_cost[newY][newX][newDirectionIndex] = cost;
                Q.push({{newX, newY}, {currX, currY}});
            }
        }
    }

    return min(min_cost[n-1][n-1][0], min_cost[n-1][n-1][2]); 
}

int main() {
    // vector<vector<int>> board = {
    //     {0,0,0,0,1},
    //     {0,0,1,0,0},
    //     {0,0,0,0,1},
    //     {1,1,0,0,1},
    //     {0,0,0,0,0}
    // };

    // vector<vector<int>> board = {
    //     {0,1,0,0},
    //     {0,0,0,1},
    //     {0,1,0,0},
    //     {0,0,0,0}
    // };

    vector<vector<int>> board = {
        {0,0,0,0,0,0},
        {1,1,1,1,1,0},
        {0,0,1,1,1,0},
        {0,0,0,0,0,0},
        {0,1,1,1,1,1},
        {0,0,0,0,0,0}
    };


    cout << solution(board) << endl;
    return 0;
}