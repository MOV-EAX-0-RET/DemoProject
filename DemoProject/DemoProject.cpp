#include <iostream>
#include <vector>
#include "cldraw.h"

using namespace std;

struct Fly {
    int x;
    int y;
    char c;
    int color;
};

int main() {
    vector<Fly> flies;

    for (int i = 0; i < 150; i++) {
        Fly fly;
        fly.x = rand() % 120;
        fly.y = rand() % 30;
        fly.c = '0' + (rand() % 100);
        fly.color = FOREGROUND_RED + rand() % 64;
        flies.push_back(fly);
    }

    create_console();
    while (true) {
        console_clear();
        for (Fly& fly : flies) {
            fly.x += rand() % 3 - 1;
            fly.y += rand() % 3 - 1;
            console_pixel(fly.x, fly.y, fly.c, fly.color);
        }
        console_flip();
    }
    return 0;
}