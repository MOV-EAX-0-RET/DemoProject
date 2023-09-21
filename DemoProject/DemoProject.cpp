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

struct Obstacle {
    int x;
    int interval;
    int height;
};

struct Player {
    int score;
    int x;
    float y;
    float velocity;
};

void flight() {
    vector<Obstacle> obstacles;
    for (int i = 0; i < 3; i++) {
        Obstacle obs {i * 40, 8, 5 + rand() % 8};
        obstacles.push_back(obs);
    }

    Player player{0, 2, 0, 0.0};
    float gravity = 0.05;

    while (true) {
        console_clear(0x00FF);
        console_rect(player.x, player.y, 2, 1, ' ', BACKGROUND_RED);

        player.velocity += gravity;
        player.y += player.velocity;
        if (player.y < 0) {
            player.y = 0;
            player.velocity *= -1;
        }
        if (player.y >= HEIGHT - 1) {
            player.y = HEIGHT - 1;
        }
        player.score++;
        if (console_just_pressed(VK_SPACE)) {
            player.velocity -= 0.8;
        }

        for (Obstacle& obs : obstacles) {
            obs.x--;
            if (obs.x <= -3) {
                obs.x += WIDTH;
                obs.height = 5 + rand() % 8;
            }
            if (obs.x == player.x && 
                (player.y < obs.height || player.y > obs.height + obs.interval)) {
                flight();
                return;
            }
            console_rect(obs.x, 0, 3, obs.height, ' ', BACKGROUND_GREEN);
            console_rect(obs.x, obs.height+obs.interval, 3, 20, ' ', BACKGROUND_GREEN);
        }
        console_text("Score: " + to_string(player.score), WIDTH-15, 0);
        console_flip();
    }
}

void menu() {
    Menu menu;
    menu.buttons.push_back(Button{ 3, 3, 20, "Start", BACKGROUND_GREEN, flight });
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
}

int main() {
    menu();
    return 0;
}