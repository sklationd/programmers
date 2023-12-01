#include <string>
#include <vector>

using namespace std;

int check(vector<int> &cookie, int first_last) {
    if(first_last < 0 || first_last >= cookie.size() - 1) return 0;
    
    int l = first_last;
    int r = l + 1;
    int l_sum = cookie[l];
    int r_sum = cookie[r];
    
    int max_sum = 0;
    
    while(l>=0 && r<cookie.size()) {
        if(l_sum == r_sum) {
            max_sum = l_sum;
            l--;
            if(l>=0) {
                l_sum += cookie[l];
            }
        } else if(l_sum < r_sum) {
            l--;
            if(l>=0) {
                l_sum += cookie[l];
            } else {
                break;
            }
        } else {
            r++;
            if(r<cookie.size()) {
                r_sum += cookie[r];
            } else {
                break;
            }
        }
    }
    
    return max_sum;
}

int solution(vector<int> cookie) {
    int answer = 0;
    for(int i=0; i<cookie.size() - 1; i++) {
        int t = check(cookie, i);
        answer = max(answer, t);
    }
    return answer;
}