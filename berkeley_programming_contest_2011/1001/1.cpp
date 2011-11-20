#include"contest.h"
#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
using namespace std;

string mapcolor[100];

int vis[100][100], color, row, col;

int colored[100][100];

int move[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

char mapcolorcolor[5] = {'h', 'R', 'G', 'B', 'Y'};

void floodfill(int x, int y, char cur) {
    vis[x][y] = color;
    for (int i = 0; i < 4; ++i) {
        int tox = x + move[i][0], toy = y + move[i][1];
        if (0 <= tox && tox < row && 0 <= toy && toy < col && !vis[tox][toy] && mapcolor[tox][toy] == cur) {
            floodfill(tox, toy, cur);
        }
    }
}

void paint(int x, int y, int color) {
    colored[x][y] = color;
    for (int i = 0; i < 4; ++i) {
        int tox = x + move[i][0], toy = y + move[i][1];
        if (0 <= tox && tox < row && 0 <= toy && toy < col && vis[tox][toy] == vis[x][y] && !colored[tox][toy]) {
            paint(tox, toy, color);
        }
    }
}

void unpaint(int x, int y) {
    colored[x][y] = 0;
    for (int i = 0; i < 4; ++i) {
        int tox = x + move[i][0], toy = y + move[i][1];
        if (0 <= tox && tox < row && 0 <= toy && toy < col && vis[tox][toy] == vis[x][y] && colored[tox][toy]) {
            unpaint(tox, toy);
        }
    }
}

int ok() {
    for (int x = 0; x < row; ++x) {
        for (int y = 0; y < col; ++y) {
            if (colored[x][y]) {
                for (int i = 0; i < 4; ++i) {
                    int tox = x + move[i][0], toy = y + move[i][1];
                    if (0 <= tox && tox < row && 0 <= toy && toy < col) {
                        if (vis[x][y] != vis[tox][toy] && colored[x][y] == colored[tox][toy]) {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}


void work() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (!vis[i][j]) {
                ++color;
                floodfill(i, j, mapcolor[i][j]);
            }
        }
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (!colored[i][j]) {
                for (int k = 1; k <= 4; ++k) {
                    paint(i, j, k);
                    if (ok()) {
                        break;
                    } else {
                        unpaint(i, j);
                    }
                }
            }
        }
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%c", mapcolorcolor[colored[i][j]]);
        }
        printf("\n");
    }
}

int main() {
    char str[100];
    while(cin.getline(str, 100)) {
        mapcolor[row++] = string(str);
    }
    col = mapcolor[0].length();
    work();
    exit(0);
}
