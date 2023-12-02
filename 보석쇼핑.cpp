#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>

using namespace std;

vector<int> solution(vector<string> gems) {
    set<string> unique_gem;
    unordered_map<string, queue<int>> gem_pos;
    for(string gem : gems) {
        if(unique_gem.find(gem) == unique_gem.end()) {
            unique_gem.insert(gem);
            queue<int> Q;
            gem_pos[gem] = Q;
        }
    }

    if(unique_gem.size() == 1) return {1, 1};

    int begin = 0;
    gem_pos[gems[begin]].push(begin);
    int gem_count = 1;
    int end = 0;

    vector<int> result = {0, (int)(gems.size() - 1)};

    while(end + 1 < gems.size()) {
        end++;
        if(gems[begin].compare(gems[end]) == 0) {
            gem_pos[gems[begin]].push(end);
            while(gem_pos[gems[begin]].size() > 1) {
                gem_pos[gems[begin]].pop();
                begin++;
            }
        } else {
            if(gem_pos[gems[end]].size() == 0) {
                gem_count++;
            }
            gem_pos[gems[end]].push(end);
        }

        if(gem_count == unique_gem.size()) {
            if(end - begin + 1 < result[1] - result[0] + 1) {
                result[0] = begin;
                result[1] = end;
            }
        }
    }
    
    return {result[0] + 1, result[1] + 1};
}

int main() {
    // vector<string> input = {"A", "B", "B", "B", "C", "B", "A", "B", "C", "D"};
    // vector<string> input = {"A", "B", "B", "A", "A", "D", "AA", "DD", "B", "A"};
    vector<string> input = {"XYZ", "XYZ", "XYZ"};
    vector<int> result = solution(input);
    cout << result[0] << " " << result[1] << endl;
}