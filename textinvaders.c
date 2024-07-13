// Text based Space Invaders
#include<stdio.h>
#include<stdbool.h>
#include<ncurses.h>

// Defs
#define BULLET_UP 0
#define BULLET_DOWN 1
#define MAX_PLAYER_BULLETS 5

// Types
typedef struct bullet {
    int oldX, oldY, X, Y;
    bool active;
    int direction;
} bullet;

typedef struct player {
    int oldX, oldY, X, Y, maxX, maxY;
    bullet bullets[MAX_PLAYER_BULLETS];
} player;

// Funcs

void drawBases() {
    // TODO: Bases rendering code
    return;
}

void drawPlayer(player Player) {
    mvprintw(Player.oldY, Player.oldX-2, "     ");
    mvprintw(Player.Y, Player.X-2, "--!--");
    Player.oldX = Player.X;
    Player.oldY = Player.Y;
    return;
}

void drawInvaders() {
    // TODO: Invader rendering code
    return;
}

void drawBullets(player *Player) {
    int b = 0;
    for(b = 0; b < MAX_PLAYER_BULLETS; b++) {
        if(Player->bullets[b].active) {
            mvprintw(Player->bullets[b].oldY, Player->bullets[b].oldX, " ");
            mvprintw(Player->bullets[b].Y, Player->bullets[b].X, ".");
            Player->bullets[b].oldX = Player->bullets[b].X;
            Player->bullets[b].oldY = Player->bullets[b].Y;
        }
    }
    return;
}

void moveBullets(player *Player) {
    int b = 0;
    for(b = 0; b < MAX_PLAYER_BULLETS; b++) {
        if(Player->bullets[b].active) {
            switch(Player->bullets[b].direction) {
                case BULLET_UP:
                    if(Player->bullets[b].Y > 0) {
                        Player->bullets[b].oldY = Player->bullets[b].Y;
                        Player->bullets[b].Y--;
                        break;
                    }
                    Player->bullets[b].active = false;
                    mvprintw(Player->bullets[b].Y, Player->bullets[b].X, " ");
                    break;
                case BULLET_DOWN:
                    if(Player->bullets[b].Y < Player->maxY) {
                        Player->bullets[b].oldY = Player->bullets[b].Y;
                        Player->bullets[b].Y++;
                        break;
                    }
                    Player->bullets[b].active = false;
                    mvprintw(Player->bullets[b].Y, Player->bullets[b].X, " ");
                    break;
            }
        }
    }
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

bool pollInput(player *Player) {
    int ch = getch();
    int b = 0;
    bool quit = false;

    switch((char)ch) {
        case 'z':
            if(Player->X-1 > 2) {
                Player->oldX = Player->X;
                Player->X--;
            }
            break;
        case 'x':
            if(Player->X+1 < Player->maxX-2) {
                Player->oldX = Player->X;
                Player->X++;
            }
            break;
        case 'q':
            quit = true;
            break;
        case ' ':
            for(b = 0; b < MAX_PLAYER_BULLETS; b++) {
                if(Player->bullets[b].active == false) {
                    Player->bullets[b].oldX = Player->X;
                    Player->bullets[b].oldY = Player->Y-1;
                    Player->bullets[b].X = Player->X;
                    Player->bullets[b].Y = Player->Y;
                    Player->bullets[b].active = true;
                    break;
                }
            }
            break;
    }

    return !quit;
}

int main(void) {
    bool isRunning = true;
    int rows, cols, frame_timer;
    player Player;

    initscr();
    getmaxyx(stdscr, rows, cols);
    clear();
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    refresh();

    // Init locs
    Player.maxX = cols;
    Player.maxY = rows-1;
    Player.oldX = cols/2;
    Player.oldY = rows-1;
    Player.X = cols/2;
    Player.Y = rows-1;
    frame_timer = 0;

    // Main Loop
    while(isRunning) {
        drawBases();
        drawPlayer(Player);
        moveInvaders();
        drawInvaders();
        drawBullets(&Player);
        isRunning = checkCollisions();
        if(frame_timer  == 0) moveBullets(&Player);
        drawScores();
        isRunning = pollInput(&Player);
        refresh();
        frame_timer++;
        frame_timer = frame_timer % 1000;
    }

    endwin();
    return 0;
}