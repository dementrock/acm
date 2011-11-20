#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
struct DpStatus {
    int t;
    string plan[100];
    int len_plan;
} f[100][100];

int vis[100][100], len_str;

string str;

void print_plan(DpStatus nowf) {
    for (int i = 1; i <= nowf.len_plan ; ++i) {
        printf("%s ", nowf.plan[i].c_str());
    }
    printf("\n");
}


int clearf() {
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            f[i][j].t = f[i][j].len_plan = 0;
            for (int k = 0; k < 100; ++k) {
                f[i][j].plan[k] = "";
            }
        }
    }
}

int iszero(string a) {
    for (int i = 0; i < a.length(); ++i) {
        if (a[i] != '0') {
            return 0;
        }
    }
    return 1;
}

int startpos(string a) {
    for (int i = 0; i < a.length(); ++i) {
        if (a[i] != '0') {
            return i;
        }
    }
}

int numcmp (string a, string b) {
    int zeroa = iszero(a), zerob = iszero(b);
    if (zeroa && zerob) {
        return 0;
    }
    if (zeroa) {
        return -1;
    }
    if (zerob) {
        return 1;
    }
    int a_startpos = startpos(a), b_startpos = startpos(b);
    int a_len = a.length() - a_startpos, b_len = b.length() - b_startpos;
    if (a_len < b_len) {
        return -1;
    }
    if (a_len > b_len) {
        return 1;
    }
    for (int i = 0; i < a_len; ++i) {
        if (a[a_startpos + i] < b[b_startpos + i]) {
            return -1;
        }
        if (a[a_startpos + i] > b[b_startpos + i]) {
            return 1;
        }
    }
    return 0;
}

int cmpplan(DpStatus f1, DpStatus f2) {
    for (int i = 1; i <= min(f1.len_plan, f2.len_plan); ++i) {
        int tmp = numcmp(f1.plan[i], f2.plan[i]);
        if (tmp) {
            return tmp;
        }
    }
    return 0;
}

int update_plan(DpStatus &f1, DpStatus &f2) {
    for (int i = 0; i < 100; ++i) {
        f1.plan[i] = f2.plan[i];
    }
    f1.len_plan = f2.len_plan;
}

int dp(int pos, int last_len) {
    cout << pos << " " << last_len << endl;
    if (vis[pos][last_len]) {
        return f[pos][last_len].t;
    }
    vis[pos][last_len] = 1;
    if (pos < last_len - 1) {
        return f[pos][last_len].t = 0;
    }
    if (pos == last_len - 1) {
        //cout << "here" << " " << pos << " " << last_len << " " << f[pos][last_len].len_plan << endl;
        f[pos][last_len].len_plan = 1;
        f[pos][last_len].plan[1] = str.substr(0, last_len);
        //cout << "here" << endl;
        return f[pos][last_len].t = 1;
    } else {
        string cur_num = str.substr(pos + 1 - last_len, last_len);
        int new_endpoint = pos - last_len;
        for (int new_len = 1; new_len <= new_endpoint + 1; ++new_len) {
            string pre_num = str.substr(new_endpoint + 1 - new_len, new_len);
            if (numcmp(pre_num, cur_num) == -1) {
                int res = dp(new_endpoint, new_len);
                if (res) {
                    cout << "possible: " << pos << " " << last_len << endl;
                    if (!f[pos][last_len].t || cmpplan(f[new_endpoint][new_len], f[pos][last_len]) == 1){
                        f[pos][last_len].t = 1;
                        cout << "before: ";
                        print_plan(f[pos][last_len]);
                        update_plan(f[pos][last_len], f[new_endpoint][new_len]);
                        cout << "after: ";
                        print_plan(f[pos][last_len]);
                        f[pos][last_len].plan[++f[pos][last_len].len_plan] = str.substr(pos + 1 - last_len, last_len);
                    }
                }
            }
        }
    }
    return f[pos][last_len].t;
}



int main(){
    freopen("test.in", "r", stdin);

    char input_str[100];

    while (scanf("%s", input_str) != EOF) {
        if (strlen(input_str) == 1 && input_str[0] == '0') {
            break;
        }
        str = string(input_str);
        len_str = strlen(input_str);
        //cout << str << endl;
        for (int i = 1; i <= len_str; ++i) {
            clearf();
            memset(vis, 0, sizeof(vis));
            //cout << i << endl;
            if (dp(len_str - 1, i)) {
                print_plan(f[len_str - 1][i]);
                break;
            }
        }
    }
    return 0;
}
