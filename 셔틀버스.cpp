#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int strtimeToInt(string time) {
    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));
    return hour * 60 + minute;
}

string inttimeToStr(int time) {
    int hour = time / 60;
    int minute = time % 60;
    string result = "00:00";
    result[0] = to_string(hour / 10)[0];
    result[1] = to_string(hour % 10)[0];
    result[3] = to_string(minute / 10)[0];
    result[4] = to_string(minute % 10)[0];
    return result;
}


bool isPossible(int n, int t, int m, vector<int> &timetable, int at) {
    int index = 0;
    int wait_count = 0;
    int prev_arrival = 0;

    vector<bool> isVisit(timetable.size(), false);

    for(int i=0; i<n; i++) {
        int arrival_time = 540 + t * i;
        for(int j=0; j<timetable.size(); j++) {
            if(prev_arrival < timetable[j] && timetable[j] <= arrival_time && timetable[j] <= at && !isVisit[j]) {
                wait_count++;
                isVisit[j] = true;
            }
        }

        prev_arrival = arrival_time;

        if(at <= arrival_time && m - wait_count > 0) {
            return true;
        } else {
            wait_count = max(0, wait_count - m);
        }
    }

    return false;
}

string solution(int n, int t, int m, vector<string> timetable) {
    vector<int> int_timetable;
    for(string time : timetable) {
        int_timetable.push_back(strtimeToInt(time));
    }
    int min_time = 0; // 00:00
    int max_time = 1439; // 23:59

    while(min_time < max_time) {
        int mid_time = (min_time + max_time) / 2;
        if(isPossible(n, t, m, int_timetable, mid_time)) {
            min_time = mid_time + 1;
        } else {
            max_time = mid_time;
        }
    }

    return inttimeToStr(min_time - 1);
}

int main() {
    // cout << solution(1, 1, 5, {"08:00", "08:01", "08:02", "08:03"}) << endl;
    // cout << solution(2, 10, 2, {"09:10", "09:09", "08:00"}) << endl;
    cout << solution(20, 1, 2, {"00:01", "00:02", "00:02"}) << endl;
    return 0;
}