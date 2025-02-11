#include "pch.h"
#include "DynamicLib.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void insertKB(string& str) {
    sort(str.rbegin(), str.rend());
    string newString;

    for (char c : str)
        if (c % 2 == 0)
            newString += "KB";
        else
            newString += c;
    str.assign(newString);
}

int sumString(const string str) {
    int sum = 0;
    for (char c : str) {
        if (isdigit(c))
            sum += c - '0';
    }
    return sum;
}

bool stringLength(const string str) {
    if (str.length() >= 2 && stoi(str) % 32 == 0)
        return true;
    return false;
}