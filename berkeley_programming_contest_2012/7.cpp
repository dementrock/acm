#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXS 10000

using namespace std;

struct info {
  int sum, val, step;
  int type; // 0: left parenthesis; 1: right parenthesis; 2: other
};

info calc(string s) {
  info stack[MAXS];
  int cntstack = 0;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == '(') { // push to stack
      ++cntstack;
      stack[cntstack].type = 0;
    } else if (s[i] == ')') { // pop stack
      int newsum = 0, newstep = 0, newval = 0;
      int leftpos = cntstack;
      while (leftpos >= 1 && stack[leftpos].type != 0) --leftpos;
      for (int j = leftpos + 1; j <= cntstack; ++j) {
        newsum += stack[j].step * newval + stack[j].sum;
        newstep += stack[j].step;
        newval += stack[j].val;
      }
      cntstack = leftpos; // override directly on the previous left parenthesis element
      stack[cntstack].type = 2;
      stack[cntstack].step = newstep;
      stack[cntstack].val = newval;
      stack[cntstack].sum = newsum;
    } else if ('0' <= s[i] && s[i] <= '9') { // number: perform calculation on last element of stack
      int n = 0;
      for (i; i < s.length() && '0' <= s[i] && s[i] <= '9'; ++i) {
        n = n * 10 + (s[i] - '0');
      }
      if (s[i] < '0' || s[i] > '9') {
        --i;
      }
      stack[cntstack].sum = n * stack[cntstack].sum + n * (n - 1) / 2 * stack[cntstack].step * stack[cntstack].val;
      stack[cntstack].val *= n;
      stack[cntstack].step *= n;
    } else { // calc and then push to stack
      ++cntstack;
      stack[cntstack].type = 2;
      stack[cntstack].step = 1;
      if (s[i] == '+') {
        stack[cntstack].val = 1;
      } else if (s[i] == '.') {
        stack[cntstack].val = 0;
      } else if (s[i] == '-') {
        stack[cntstack].val = -1;
      } else { // shouldn't happen..
        cout << "error!" << endl;
      }
      stack[cntstack].sum = stack[cntstack].val;
    }
  }
  info ans;
  ans.sum = ans.step = ans.val = 0;
  for (int i = 1; i <= cntstack; ++i) {
    ans.sum += stack[i].step * ans.val + stack[i].sum;
    ans.step += stack[i].step;
    ans.val += stack[i].val;
  }
  return ans;
}

double avg(string s) {
  info calced = calc(s);
  return 1.0 * calced.sum / (calced.step + 1);
}

int main() {
  string s;
  cout.setf(ios::fixed,ios::floatfield);
  cout.precision(2);
  while (cin >> s) {
    cout << "Average value of " << s << " is " << avg(s) << endl;
  }
  return 0;
}
