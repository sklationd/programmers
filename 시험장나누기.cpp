#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

const int MAX_K = 10000;
const int MAX_NUM = 10000;

int find_root(int num, vector<vector<int>> &links) {
    int total = num * (num - 1) / 2;

    for(int i=0; i<links.size(); i++) { 
        if(links[i][0] >= 0) {
            total -= links[i][0];
        }
        
        if(links[i][1] >= 0) {
            total -= links[i][1];
        }
    }
    
    return total;
}

void check(
    int root,
    vector<int> &num,
    vector<vector<int>> &links,
    int L,
    vector<int> &min_k,
    vector<int> &min_root_sum
) {
    if(root < 0) return;

    cout << "check: " << root << endl;

    int left = links[root][0];
    int right = links[root][1];

    if(left < 0 && right < 0) {
        min_root_sum[root] = num[root];
        if(num[root] <= L) {
            min_k[root] = 1;
        } else {
            min_k[root] = MAX_K + 1;
        }

        return;
    }

    check(left, num, links, L, min_k, min_root_sum);
    check(right, num, links, L, min_k, min_root_sum);

    int mk_l = left >= 0 ? min_k[left] : 1;
    int mk_r = right >= 0 ? min_k[right] : 1;
    int mrs_l = left >= 0 ? min_root_sum[left] : 0;
    int mrs_r = right >= 0 ? min_root_sum[right] : 0;

    if(mrs_l + mrs_r + num[root] <= L) {
        min_k[root] = mk_l + mk_r - 1;
        min_root_sum[root] = mrs_l + mrs_r + num[root];
    } else if(mrs_l + num[root] <= L || mrs_r + num[root] <= L) {
        min_k[root] = mk_l + mk_r;
        min_root_sum[root] = min(mrs_l, mrs_r) + num[root];
    } else if(num[root] <= L) {
        min_k[root] = mk_l + mk_r + 1;
        min_root_sum[root] = num[root];
    } else {
        min_k[root] = MAX_K + 1;
    }

    cout << "min_k for " << root << ": " << min_k[root] << endl;
    cout << "min_s for " << root << ": " << min_root_sum[root] << endl;
}

int solution(int k, vector<int> num, vector<vector<int>> links) {
    int root = find_root(num.size(), links);
    cout << "root: " << root << endl;
    int min_l = 0;
    int max_l = MAX_K * MAX_NUM + 1;
    
    while(min_l < max_l) {
        int mid = (min_l + max_l) / 2;
        
        cout << "----------------------------" << endl;
        cout << "test for: " << mid << endl;
        cout << "----------------------------" << endl;

        // is possible to divide tree with maximum of partial sum is less than `mid`;
        vector<int> min_root_sum(num.size(), 0);
        vector<int> min_k(num.size(), -1);

        check(root, num, links, mid, min_k, min_root_sum);

        if(min_k[root] <= k) {
            max_l = mid;
        } else {
            min_l = mid + 1;
        }
    }
    
    return min_l;
}

int main() {
    // int k = 3;
    // vector<int> num = {12, 30, 1, 8, 8, 6, 20, 7, 5, 10, 4, 1};
    // vector<vector<int>> links = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {8, 5}, {2, 10}, {3, 0}, {6, 1}, {11, -1}, {7, 4}, {-1, -1}, {-1, -1}};

    // int k = 4;
    // vector<int> num = {4, 32, 7, 26};
    // vector<vector<int>> links = {{1, 2}, {-1, -1}, {-1, 3}, {-1, -1} };

    int k = 2;
    vector<int> num = {10, 8, 9, 3, 7, 5};
    vector<vector<int>> links = {{-1, -1}, {0, -1}, {1, 3}, {-1, -1}, {2, 5}, {-1, -1}};

    cout << solution(k, num, links) << endl;
    
    return 0;
}