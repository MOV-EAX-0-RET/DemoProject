#include <iostream>
#include <vector>
#include <functional>
#include "cldraw.h"

using namespace std;

struct Button {
    int x;
    int y;
    int width;
    string text;
    int color;
    function<void()> action;

    void draw() {
        console_rect(x, y, width, 3, ' ', color);
        console_text(text, x + 1, y + 1,
            color | FOREGROUND_WHITE);
    }
};

struct Menu {
    vector<Button> buttons;
    int selected = 0;

    void control() {
        if (console_just_pressed(VK_DOWN)) {
            selected++;
            if (selected >= buttons.size()) {
                selected = 0;
            }
        }
        if (console_just_pressed(VK_UP)) {
            selected--;
            if (selected < 0) {
                selected = buttons.size() - 1;
            }
        }

        if (console_just_pressed(VK_RETURN)) {
            Button& button = buttons[selected];
            if (button.action) {
                button.action();
            }
        }
    }
};

void action_exit() {
    exit(0);
}

int main() {
    Menu menu;
    menu.buttons.push_back(Button{ 3, 3, 20, "Start", BACKGROUND_GREEN });
    menu.buttons.push_back(Button{ 3, 7, 20, "Exit", BACKGROUND_RED, action_exit });

    create_console();
    while (true) {
        menu.control();

        console_clear();
        for (Button& button : menu.buttons) {
            button.draw();
        }
        Button& selectedButton = menu.buttons[menu.selected];
        console_pixel(selectedButton.x - 2, selectedButton.y+1, '>');


        for (int x = 40; x < 110; x++) {
            for (int y = 2; y < 26; y++) {
                srand(x * 37 + y - console_timer * 45);
                int z = rand() + rand();
                console_pixel(x, y, ' '+(rand() % 60), FOREGROUND_GREEN);
            }
        }

        console_flip();
    }
    return 0;
}