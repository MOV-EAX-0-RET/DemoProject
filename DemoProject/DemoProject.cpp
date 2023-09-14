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
        console_rect(button.x, button.y, 20, 3, ' ', button.color);
        console_text(button.text, button.x + 1, button.y + 1, 
                     button.color | FOREGROUND_WHITE);
        console_flip();
    }
    return 0;
}