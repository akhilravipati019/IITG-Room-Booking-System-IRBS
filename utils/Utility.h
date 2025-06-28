#ifndef UTILITY_H
#define UTILITY_H
#include <string>
#include <regex>
#include <algorithm>
using namespace std;
class Utility {
public:
    static bool isTimeConflict(const string& t1, const string& t2) {
        int h1, m1, h2, m2, h3, m3, h4, m4;
        sscanf(t1.c_str(), "%d:%d to %d:%d", &h1, &m1, &h2, &m2);
        sscanf(t2.c_str(), "%d:%d to %d:%d", &h3, &m3, &h4, &m4);
        int start1 = h1 * 60 + m1, end1 = h2 * 60 + m2;
        int start2 = h3 * 60 + m3, end2 = h4 * 60 + m4;
        return max(start1, start2) < min(end1, end2);
    }

    static bool isValidTimeFormat(const string& time) {
        return regex_match(time, regex("^(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$"));
    }
};
#endif