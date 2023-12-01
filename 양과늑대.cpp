#include <string>
#include <vector>
#include <iostream>

using namespace std;

void dfs(int curr, int sheep, int wolf, vector<bool> &cand, vector<vector<int>> &graph, vector<int> &info, int &max_sheep) {
    int new_sheep = sheep + (info[curr] ^ 1);
    int new_wolf = wolf + info[curr];

    if(new_sheep <= new_wolf) {
        return;    
    }
    
    max_sheep = max(max_sheep, new_sheep);
    
    for(int next : graph[curr]) {
        cand[next] = true;
    }
    
    for(int i=0; i<cand.size(); i++) {
        if(cand[i]) {
            vector<bool> prev_cand = cand;
            cand[i] = false;
            dfs(i, new_sheep, new_wolf, cand, graph, info, max_sheep);  
            cand = prev_cand;
        }
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    vector<vector<int>> graph(info.size(), vector<int>());
    for(auto edge : edges) graph[edge[0]].push_back(edge[1]);
    
    int max_sheep = 0;
    vector<bool> cand(info.size(), false);

    dfs(0, 0, 0, cand, graph, info, max_sheep);
    
    return max_sheep;
}

int main() {
    vector<int> info = {0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1};
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {1, 4}, {0, 8}, {8, 7}, {9, 10}, {9, 11}, {4, 3}, {6, 5}, {4, 6}, {8, 9}};

    // vector<int> info = {0, 0, 1, 0, 0};
    // vector<vector<int>> edges = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};

    int result = solution(info, edges);
    cout << result << endl;

    return 0;
}