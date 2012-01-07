#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int expmod (int a, int b, int c) { // Calculate a ^ b mod c
    long long ans = 1, mult = a;
    while (b) {
        if (b & 1) {
            ans = (ans * mult) % c;
        }
        mult = (mult * mult) % c;
        b >>= 1;
    }
    return (int) ans;
}
