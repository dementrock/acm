#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>
#include <map>
using namespace std;

map<string, int> treemap;
map<string, int>::iterator iter;

int main() {
    freopen("test.in", "r", stdin);
    string str;
    int sum = 0;
    while (getline(cin, str)) {
        ++treemap[str], ++sum;
    }
    for (iter = treemap.begin(); iter != treemap.end(); ++iter) {
        printf("%s %.4f\n", iter -> first.c_str(), iter -> second * 100.0 / sum);
        //cout << (*iter).first << " " << (*iter).second << endl;
    }
    return 0;
}
