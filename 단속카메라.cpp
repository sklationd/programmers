#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> get_overlap(vector<int> &a, vector<int> &b) {
    return {
        max(a[0], b[0]),
        min(a[1], b[1])
    };
}

bool is_overlap(vector<int> &a, vector<int> &b) {
    vector<int> overlap = get_overlap(a, b);
    return overlap[0] <= overlap[1];
}

bool cmp(vector<int> a, vector<int> b) {
    return a[0] < b[0] || (a[0] == b[0] && a[1] <= b[1]);
}

int solution(vector<vector<int>> routes) {    
    sort(routes.begin(), routes.end(), cmp);
    
    int result = 1;
    vector<int> overlap = {-30000, 30000};
    for(auto route : routes) {
        if(is_overlap(route, overlap)) {
            overlap = get_overlap(route, overlap);
        } else {
            result++;
            overlap[0] = route[0];
            overlap[1] = route[1];
        }
    }
    
    return result;
}