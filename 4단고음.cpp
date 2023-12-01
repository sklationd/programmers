#include <cmath>
#include <iostream>

using namespace std;

void dfs(int curr, int plus_count, int mul_count, int &answer) {
    // cout << curr << endl;
    if(curr == 1) {
        if(plus_count == 2 * mul_count) {
            answer++;
        }
        return;
    }

    int remain_mul_count = ((plus_count - 2 * mul_count) + 1) / 2;
    
    // +
    if(curr > pow(3, remain_mul_count)) {
        // cout << "+" << endl;
        dfs(curr-1, plus_count + 1, mul_count, answer);
    }
    
    // *
    if(curr % 3 == 0 && plus_count - 2 * mul_count >= 2) {
        // cout << "*" << endl;
        dfs(curr / 3, plus_count, mul_count + 1, answer);
    }
}

int solution(int n) {
    int answer = 0;
    dfs(n, 0, 0, answer);
    return answer;
}

int main() {
    cout << solution(15) << endl;
    cout << solution(24) << endl;
    cout << solution(41) << endl;
    cout << solution(2147483647) << endl;
}