#include <vector>
#include <string>
#include <iostream>

using namespace std;

int solution(vector<string> arr)
{
    int answer = -1;
    int num_count = (arr.size() + 1) / 2;
    vector<vector<int>> min_dp(num_count, vector<int>(num_count, 100001));
    vector<vector<int>> max_dp(num_count, vector<int>(num_count, -100001));

    for(int i=0; i<num_count; i++) {
        min_dp[i][i] = stoi(arr[2*i]);
        max_dp[i][i] = stoi(arr[2*i]);
    }
    
    for(int L=1; L<num_count; L++) {
        // interval length : L + 1
        for(int from=0; from<num_count - L; from++) {
            int to = from + L;
            for(int mid=from; mid<to; mid++) {
                // from~mid, mid+1~to
                char op = arr[2*mid+1][0];
                if(op == '+') {
                    min_dp[from][to] = min(min_dp[from][to], min_dp[from][mid] + min_dp[mid+1][to]);
                    max_dp[from][to] = max(max_dp[from][to], max_dp[from][mid] + max_dp[mid+1][to]);
                } else {
                    min_dp[from][to] = min(min_dp[from][to], min_dp[from][mid] - max_dp[mid+1][to]);
                    max_dp[from][to] = max(max_dp[from][to], max_dp[from][mid] - min_dp[mid+1][to]);
                }
            }
        }
    }

    return max_dp[0][num_count-1];
}

int main() {
    // 1
    cout << solution({"1", "-", "3", "+", "5", "-", "8"}) << endl;

    // 3
    cout << solution({"5", "-", "3", "+", "1", "+", "2", "-", "4"}) << endl;
    
    // 5
    cout << solution({"5"}) << endl;

    // 9
    cout << solution({"5", "-", "3", "-", "1", "-", "2", "-", "4"}) << endl;

    // 9
    cout << solution({"5", "-", "3", "-", "1", "-", "2", "+", "4"}) << endl;

    return 0;
}