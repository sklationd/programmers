#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <tuple>

using namespace std;

// priority queue with coordinate(x, y)
struct cmp {
    bool operator()(tuple<int, int, int> a, tuple<int, int, int> b) {
        if(get<2>(a) < get<2>(b)) {
            return true;
        } else if(get<2>(a) == get<2>(b)) {
            return get<1>(a) > get<1>(b);
        } else {
            return false;
        }
    }
};

void find_parent(int root, vector<vector<int>> &graph, int index, int x) {
    int curr_x = graph[root][0];
    if(x < curr_x) {
        if(graph[root][1] > 0) { // left exists
            find_parent(graph[root][1], graph, index, x);
        } else {
            graph[root][1] = index;
            graph[root][2] = x;
        }
    } else if(x > curr_x) {
        if(graph[root][3] > 0) { // right exists
            find_parent(graph[root][3], graph, index, x);
        } else {
            graph[root][3] = index;
            graph[root][4] = x;
        }
    }
}

void pre_traversal(int root, vector<vector<int>> &graph, vector<int> &result) {
    if(root < 0) return;
    result.push_back(root);
    pre_traversal(graph[root][1], graph, result);
    pre_traversal(graph[root][3], graph, result);
}

void post_traversal(int root, vector<vector<int>> &graph, vector<int> &result) {
    if(root < 0) return;
    post_traversal(graph[root][1], graph, result);
    post_traversal(graph[root][3], graph, result);
    result.push_back(root);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, cmp> PQ;
    vector<vector<int>> graph(nodeinfo.size() + 1, {-1, -1, -1, -1, -1}); // curr_x, left_index, left_x, right_index, right_x
    
    for(int i=0; i<nodeinfo.size(); i++) {
        PQ.push({i+1, nodeinfo[i][0], nodeinfo[i][1]});
        graph[i+1][0] = nodeinfo[i][0];
    }

    // root
    auto root = PQ.top();

    while(!PQ.empty()) {
        auto top = PQ.top();
        PQ.pop();
        find_parent(get<0>(root), graph, get<0>(top), get<1>(top));
    }

    vector<vector<int>> answer(2);

    pre_traversal(get<0>(root), graph, answer[0]);
    post_traversal(get<0>(root), graph, answer[1]);

    return answer;
}

int main() {
    vector<vector<int>> nodeinfo = {{5,3}, {11,5}, {13,3}, {3,5}, {6,1}, {1,3}, {8,6}, {7,2}, {2,2}};

    vector<vector<int>> result = solution(nodeinfo);
    for(auto v : result) {
        for(int i : v) {
            cout << i << " ";
        } 
        cout << endl;
    }
    return 0;
}