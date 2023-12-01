#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

bool is_possible(long long time_limit, int a, int b, vector<int> g, vector<int> s, vector<int> w, vector<int> t) {
    long long max_g =0;
    long long max_s = 0;
    long long max_gs = 0;
    
    for(int i=0; i<g.size(); i++) {
        long long remain_time = time_limit - t[i];
        long long max_round_trip = (remain_time / (2*t[i]));
        long long max_amount = (max_round_trip + 1) * w[i];
        cout << max_amount <<endl;
        max_g += min((long long)g[i], max_amount);
        max_s += min((long long)s[i], max_amount);
        max_gs += min((long long)(g[i] + s[i]), max_amount);
    }
    
    cout << "time limit: " << time_limit << endl;
    cout << "max_g: " << max_g << endl;
    cout << "max_s: " << max_s << endl;
    cout << "max_gs: " << max_gs << endl;
    
    return max_g >= a && max_s >= b && max_gs >= a + b;
}

long long solution(int a, int b, vector<int> g, vector<int> s, vector<int> w, vector<int> t) {
    long long answer = -1;
    long long min_t = 0;
    long long max_t = 4 * pow(10, 14) + 1;
    
    while(min_t < max_t) {
        long long mid = (min_t + max_t) / 2;
        if(is_possible(mid, a, b, g, s, w, t)) {
            cout << "possible: " << mid << endl;
            max_t = mid;
        } else {
            min_t = mid + 1;
        }
    }
    
    return min_t;
}

int main() {
    cout << solution(10, 10, {100}, {100}, {7}, {10}) <<endl;
}