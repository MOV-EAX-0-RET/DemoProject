#include <iostream>
#include <vector>
#include "cldraw.h"

using namespace std;

int main() {
    vector<int> xs;
    vector<int> ys;
    vector<char> chars;

    for (int i = 0; i < 100; i++) {
        xs.push_back(rand() % 120);
        ys.push_back(rand() % 30);
        chars.push_back('0' + (rand() % 100));
    }

    create_console();
    while (true) {
        console_clear();
        for (int i = 0; i < xs.size(); i++) {
            xs[i] += rand() % 3 - 1;
            ys[i] += rand() % 3 - 1;
            console_pixel(xs[i], ys[i], chars[i]);
        }
        console_flip();
    }
    return 0;
}