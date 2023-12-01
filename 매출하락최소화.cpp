#include <string>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

struct cmp {
    bool operator()(int a, int b){ 
        return a > b;
    }
};

void solve(
    int sub_root,
    vector<int> &sales,
    vector<vector<int>> &graph,
    vector<vector<int>> &dp
) {
    // leaf
    if(graph[sub_root].size() == 0) {
        dp[sub_root][0] = 0;
        dp[sub_root][1] = sales[sub_root - 1];
        return;
    }
    
    int sum = 0;
    
    priority_queue<int, vector<int>, cmp> PQ;
    for(int child : graph[sub_root]) {
        solve(child, sales, graph, dp);
        sum += min(dp[child][0], dp[child][1]);
        if(dp[child][0] < dp[child][1]) {
            PQ.push(dp[child][1] - dp[child][0]);
        }
    }

    int complementary = PQ.size() == graph[sub_root].size() ? PQ.top() : 0;

    dp[sub_root][0] = sum + complementary;
    dp[sub_root][1] = sum + sales[sub_root - 1];

    cout << "min exclude " << sub_root << ": " << dp[sub_root][0] << endl;
    cout << "min include " << sub_root << ": " << dp[sub_root][1] << endl;
}

int solution(vector<int> sales, vector<vector<int>> links) {
    const int n = sales.size();
    vector<vector<int>> graph(n+1);
    for(auto v : graph) v.reserve(16);
    
    for(auto link : links) {
        graph[link[0]].push_back(link[1]);
    }
    
    vector<vector<int>> dp = vector<vector<int>>(n+1, vector<int>(2, INT_MAX));

    solve(1, sales, graph, dp);
    return min(dp[1][0], dp[1][1]);
}

int main() {
    vector<int> sales = {14, 17, 15, 18, 19, 14, 13, 16, 28, 17};
    vector<vector<int>> links = {{10, 8}, {1, 9}, {9, 7}, {5, 4}, {1, 5}, {5, 10}, {10, 6}, {1, 3}, {10, 2}};

    int result = solution(sales, links);
    cout << result << endl;
}