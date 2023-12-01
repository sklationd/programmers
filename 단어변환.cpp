#include <string>
#include <vector>
#include <queue>

using namespace std;

int word_diff(string s1, string s2) {
    if( s1.size() != s2.size() ) return -1;
    
    int diff_count = 0;
    for(int i=0; i<s1.size(); i++) {
        if(s1[i] != s2[i]) diff_count++;
    }
    
    return diff_count;
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    vector<bool> isVisit(words.size(), false);
    queue<pair<string, int>> Q;
    Q.push({begin, 0});
    
    while(!Q.empty()) {
        auto curr = Q.front();
        Q.pop();
        if(curr.first.compare(target) == 0) {
            return curr.second;
        }
        
        for(int i=0; i<words.size(); i++) {
            if(!isVisit[i] && word_diff(curr.first, words[i]) == 1) {
                Q.push({words[i], curr.second + 1});
                isVisit[i] = true;
            }
        }
    }
    
    return 0;
}