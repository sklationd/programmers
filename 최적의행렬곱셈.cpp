#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> matrix_sizes) {
    // 200 ^ 4
    int n = matrix_sizes.size();
    vector<vector<int>> dp(n, vector<int>(n, 1600000000));
    for(int i=0; i<n; i++) {
        dp[i][i] = 0;
    }

    for(int i=0; i<n-1; i++) {
        dp[i][i+1] = matrix_sizes[i][0] * matrix_sizes[i][1] * matrix_sizes[i+1][1];
    }


    for(int L=2; L<=n-1; L++) {
        for(int from=0; from < n-L; from++) {
            int to = from + L;
            for(int mid=from; mid<to; mid++) {
                cout << dp[from][mid] << " " << dp[mid+1][to] << " " << matrix_sizes[from][0] * matrix_sizes[mid][1] * matrix_sizes[to][0] << endl;
                dp[from][to] = min(dp[from][to], dp[from][mid] + dp[mid+1][to] + matrix_sizes[from][0] * matrix_sizes[mid][1] * matrix_sizes[to][1] );
                cout << dp[from][to] << endl;
            }
        }
    }

    return dp[0][n-1];
}

int main() {
    cout << solution({{5,3},{3,10},{10,6}}) << endl;
}