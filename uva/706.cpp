#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#define MAXN 10
using namespace std;

int s, len;

char number[MAXN];

int input_data(){
    scanf("%d %s\n", &s, number);
    if (s == 0) {
        return 0;
    } else {
        return 1;
    }
}

void rprint(char c, int times) {
    for (int i = 1; i <= times; ++i) {
        printf("%c", c);
    }
}

void print_middle() {
    printf(" ");
    rprint('-', s);
    printf(" ");
}

void print_blank() {
    rprint(' ', s + 2);
}

void print_double_bar() {
    printf("|");
    rprint(' ', s);
    printf("|");
}

void print_right_bar() {
    rprint(' ', s + 1);
    printf("|");
}

void print_left_bar() {
    printf("|");
    rprint(' ', s + 1);
}

void print_row(char digit, int row) {
    switch (digit) {
        case '0':
            if (row == 1 || row == 2 * s + 3) {
                print_middle();
            } else if (row == s + 2) {
                print_blank();
            } else {
                print_double_bar();             
            }
            break;
        case '1':
            if (row == 1 || row == s + 2 || row == 2 * s + 3) {
                print_blank();
            } else {
                print_right_bar();             
            }
            break;
        case '2':
            if (row == 1 || row == 2 * s + 3 || row == s + 2) {
                print_middle();
            } else if (2 <= row && row <= s + 1) {
                print_right_bar();
            } else if (s + 3 <= row && row <= 2 * s + 2) {
                print_left_bar();
            }
            break;
        case '3':
            if (row == 1 || row == 2 * s + 3 || row == s + 2) {
                print_middle();
            } else {
                print_right_bar();
            }
            break;
        case '4':
            if (row == 1 || row == 2 * s + 3) {
                print_blank();
            } else if (2 <= row && row <= s + 1) {
                print_double_bar();
            } else if (row == s + 2) {
                print_middle();
            } else {
                print_right_bar();
            }
            break;
        case '5':
            if (row == 1 || row == 2 * s + 3 || row == s + 2) {
                print_middle();
            } else if (2 <= row && row <= s + 1) {
                print_left_bar();
            } else if (s + 3 <= row && row <= 2 * s + 2) {
                print_right_bar();
            }
            break;
        case '6':
            if (row == 1 || row == s + 2 || row == 2 * s + 3) {
                print_middle();
            } else if (2 <= row && row <= s + 1) {
                print_left_bar();
            } else {
                print_double_bar();
            }
            break;
        case '7':
            if (row == 1) {
                print_middle();
            } else if (row == s + 2 || row == 2 * s + 3) {
                print_blank();
            } else {
                print_right_bar();
            }
            break;
        case '8':
            if (row == 1 || row == s + 2 || row == 2 * s + 3) {
                print_middle();
            } else {
                print_double_bar();
            }
            break;
        case '9':
            if (row == 1 || row == s + 2 || row == 2 * s + 3) {
                print_middle();
            } else if (2 <= row && row <= s + 1) {
                print_double_bar();
            } else {
                print_right_bar();
            }
            break;
    }
}

void print_result(){
    for (int i = 1; i <= 2 * s + 3; ++i) {
        for (int j = 0; j < strlen(number); ++j) {
            print_row(number[j], i);
            if (j + 1 < strlen(number)) {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    while(input_data()){
        print_result();
    }
    return 0;
}
