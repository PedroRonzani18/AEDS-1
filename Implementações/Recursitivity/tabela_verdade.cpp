#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

string decimal_to_binary(int n) {

    if(n == 0 or n == 1) {
        return to_string(n);
    }

    return decimal_to_binary(n/2) + to_string(n%2);
}

vector<string> binaryString(int n) {

    vector<string> ret;

    for(int i=0; i < pow(2,n); i++) {
        string str = decimal_to_binary(i);
    }
/*
    vector<int> erases;
    
    for(int i=0; i<ret.size(); i++) {
        for(int j=0; j<ret[i].size(); j++) {
            
            if(ret[i][j] == ret[i][j+1] and ret[i][j+1] == '1') {
                erases.push_back(i);
                break;
            }
        }
    }
    
    for(int i = erases.size()-1; i>=0; i--) {
        ret.erase(ret.begin() + erases[i]);
    }
*/
    for(string& str : ret) {
        if(str.size() < n) {
            string current = str;
            str = string(n-str.size(), '0') + current;
        }
    }

    return ret;
}

int main() {
   
   for(auto x : binaryString(5))
       cout << x << endl;
}