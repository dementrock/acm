#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

struct SegTree {
    int left, right, is_shortcut;
    int max_left, max_right, max_tot;
} t[50000];

void build_tree(int pos, int left, int right) {
    t[pos].left = left, t[pos].right = right;
    t[pos].max_left = t[pos].max_right = t[pos].max_tot = right - left + 1; 
    if (left == right) {
        return;
    }
    int mid = left + right >> 1;
    build_tree(pos * 2, left, mid);
    build_tree(pos * 2 + 1, mid + 1, right); 
}

void update(int pos) {
    int t_left = t[pos].left, t_right = t[pos].right;
    int mid = t_left + t_right >> 1;
    SegTree *now = &t[pos], *left_t = &t[pos * 2], *right_t = &t[pos * 2 + 1];
    now -> max_left = left_t -> max_left;
    if (left_t -> max_left >= mid - t_left + 1) {
        now -> max_left += right_t -> max_left;
    }
    now -> max_right = right_t -> max_right;
    if (right_t -> max_right >= t_right - mid) {
        now -> max_right += left_t -> max_right;
    }
    now -> max_tot = now -> max_left;
    now -> max_tot = max(now -> max_tot, now -> max_right);
    now -> max_tot = max(now -> max_tot, left_t -> max_tot);
    now -> max_tot = max(now -> max_tot, right_t -> max_tot);
    now -> max_tot = max(now -> max_tot, left_t -> max_right + right_t -> max_left);
    //printf("%d %d %d %d %d %d\n", pos, t[pos].left, t[pos].right, t[pos].max_left, t[pos].max_right, t[pos].max_tot);
}

void transfer(int pos) {
    t[pos * 2].is_shortcut = 1;
    t[pos * 2 + 1].is_shortcut = 1;
    t[pos * 2].max_left = t[pos * 2].max_right = t[pos * 2].max_tot = (t[pos].max_tot) ? (t[pos * 2].right - t[pos * 2].left + 1) : 0;
    t[pos * 2 + 1].max_left = t[pos * 2 + 1].max_right = t[pos * 2 + 1].max_tot = (t[pos].max_tot) ? (t[pos * 2 + 1].right - t[pos * 2 + 1].left + 1) : 0;
    t[pos].is_shortcut = 0;
}

void occupy(int pos, int t_left, int t_right, int m_left, int m_right) {
    if (t_left == t_right) {
        t[pos].max_left = t[pos].max_right = t[pos].max_tot = 0;
        t[pos].is_shortcut = 0;
        return;
    }
    if (m_left == t_left && m_right == t_right) { // Exactly this interval
        t[pos].max_left = t[pos].max_right = t[pos].max_tot = 0;
        t[pos].is_shortcut = 1;
        return;
    }
    if (t[pos].is_shortcut) {
        transfer(pos);
    }
    int mid = t_left + t_right >> 1;
    if (m_right <= mid) { // Completely in the left subtree
        occupy(pos * 2, t_left, mid, m_left, m_right);
    } else if (m_left >= mid + 1) { // Completely in the right subtree
        occupy(pos * 2 + 1, mid + 1, t_right, m_left, m_right);
    } else { // In both
        occupy(pos * 2, t_left, mid, m_left, mid);
        occupy(pos * 2 + 1, mid + 1, t_right, mid + 1, m_right);
    }
    update(pos);
}

void release(int pos, int t_left, int t_right, int m_left, int m_right) {
    if (t_left == t_right) {
        t[pos].max_left = t[pos].max_right = t[pos].max_tot = 1;
        t[pos].is_shortcut = 0;
        return;
    }
    if (m_left == t_left && m_right == t_right) { // Exactly this interval
        t[pos].max_left = t[pos].max_right = t[pos].max_tot = t_right - t_left + 1;
        t[pos].is_shortcut = 1;
        return;
    }
    if (t[pos].is_shortcut) {
        transfer(pos);
    }
    int mid = t_left + t_right >> 1;
    if (m_right <= mid) { // Completely in the left subtree
        release(pos * 2, t_left, mid, m_left, m_right);
    } else if (m_left >= mid + 1) { // Completely in the right subtree
        release(pos * 2 + 1, mid + 1, t_right, m_left, m_right);
    } else { // In both
        release(pos * 2, t_left, mid, m_left, mid);
        release(pos * 2 + 1, mid + 1, t_right, mid + 1, m_right);
    }
    update(pos);
}


int main() {
    int n, p;
    scanf("%d%d", &n, &p);
    build_tree(1, 1, n);
    for (int i = 1, c, I, M; i <= p; ++i) {
        scanf("%d", &c);
        switch(c) {
            case 1:
                scanf("%d%d", &I, &M);
                occupy(1, 1, n, I, I + M - 1);
                break;
            case 2:
                scanf("%d%d", &I, &M);
                release(1, 1, n, I, I + M - 1);
                break;
            case 3:
                printf("%d\n", t[1].max_tot);
                break;
        }
        //printf("\n");
    }
    return 0;
}
