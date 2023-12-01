#include <string>
#include <vector>

using namespace std;

void dfs(int total, int open_left, int curr_complete, int &result) {
    if(curr_complete == total) {
        result++;
        return;
    }

    // close if possible
    if(open_left > 0) {
        dfs(total, open_left - 1, curr_complete + 1, result);
    }
    // open new if possible
    if(curr_complete + open_left < total) {
        dfs(total, open_left + 1, curr_complete, result);
    }
}

int solution(int n) {
    int result = 0;
    dfs(n, 0, 0, result);
    return result;
}