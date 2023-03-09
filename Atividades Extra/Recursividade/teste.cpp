#include <bits/stdc++.h>

using namespace std;

vector<int> increasing(int n) {
    if(n == 0) return vector<int>();

    vector<int> ret = increasing(n-1);

    ret.push_back(n);
}