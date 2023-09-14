#include <iostream>
#include <vector>
#include "cldraw.h"

using namespace std;

struct Button {
    int x;
    int y;
    string text;
    int color;
};

int main() {
    Button button{ 3, 3, "Start", BACKGROUND_RED };

    create_console();
    while (true) {
        console_clear();

        console_flip();
    }
    return 0;
}