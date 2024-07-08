// Text based Space Invaders
#include<stdio.h>
#include<stdbool.h>
#include<ncurses.h>

void drawBases() {
    // TODO: Bases rendering code
    return;
}

void drawPlayer() {
    // TODO: Player rendering code
    return;
}

void drawInvaders() {
    // TODO: Invader rendering code
    return;
}

void drawBullets() {
    // TODO: Bullet rendering code
    return;
}

void drawScores() {
    // TODO: Score/HUD rendering code
    return;
}

void moveInvaders() {
    // TODO: Invader movement code
    return;
}

bool checkCollisions() {
    // TODO: Add collision checking code for invaders and bullets
    return true;
}

bool pollInput() {
    // TODO: Add input handling (keyboard/controller)
}

int main(void) {
    bool isRunning = true;

    initscr();
    clear();
    refresh();

    // Main Loop
    while(isRunning) {
        drawBases();
        drawPlayer();
        moveInvaders();
        drawInvaders();
        drawBullets();
        isRunning = checkCollisions();
        drawScores();
        isRunning = pollInput();
    }

    return 0;
}