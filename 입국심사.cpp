#include <string>
#include <vector>

using namespace std;

const long long MAX_CUSTOMER = 1000000000;
const long long MAX_JUDGE_TIME = 1000000000;

bool check(int n, vector<int> &times, long long time_limit) {
    long long count = 0;
    for(int time : times) {
        count += time_limit / time;
    }
    return count >= n;
}

long long solution(int n, vector<int> times) {
    long long answer = 0;
    
    long long min_time = 0;
    long long max_time = MAX_CUSTOMER * MAX_JUDGE_TIME + 1;
    
    while(min_time < max_time) {
        long long mid = (min_time + max_time) / 2;
        if(check(n, times, mid)) {
            max_time = mid;
        } else {
            min_time = mid + 1;
        }    
    }
    
    return min_time;
}