#include <iostream>
#include <stdio.h>
#define MAXN 1000

struct RLE {
    int pixel;
    int len;
} input_list[MAXN];

struct PixelBlock {
    int pixel;
    int len;
    int line_id;
} pixel_block;

int input_len = 0, width;

void init(void) {
    int start_index = 0;
    for (int i = 0; i < input_len; ++i) {
        p_list[i] = input_list[i];
        if (p_list[i].len > 3 * width - start_index) {
            int start_len = (width - start_index);
            int tail_len = (p_list[i].len - start_index) % width;
            p_list[i].len = start_len + 2 * width + tail_len;
        }
        start_index = (start_index + p_list[i].len) % width;
    }
}

int main() {
    while (scanf("%d", &width)) {
        if (!width) {
            break;
        }
        int pixel, len;
        while(scanf("%d%d", &pixel, &len)) {
            if (!pixel && !len) {
                break;
            }
            input_list[input_len].pixel = pixel;
            input_list[input_len++].len = len;
        }
        init();
    }
    return 0;
}
    
