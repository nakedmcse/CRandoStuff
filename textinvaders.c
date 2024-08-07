// Text based Space Invaders
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<ncurses.h>

// Defs
#define BULLET_UP 0
#define BULLET_DOWN 1
#define INVADER_LEFT -1
#define INVADER_RIGHT 1
#define MAX_PLAYER_BULLETS 5
#define MAX_PLAYER_LIVES 3
#define MAX_INVADERS 48

// Types
typedef struct bullet {
    int oldX, oldY, X, Y;
    bool active;
    int direction;
} bullet;

typedef struct player {
    int oldX, oldY, X, Y, maxX, maxY, lives, score;
    bullet bullets[MAX_PLAYER_BULLETS];
} player;

typedef struct invader {
    int oldX, oldY, X, Y;
    bool active;
    bullet bullet;
} invader;

// Funcs
void initBases(int rows, int cols) {
    int i = 0;
    int perLine = (cols - 20)/10;
    for(i = 0; i<perLine; i++) {
        mvprintw(rows-4, (i*10)+10, "#####");
        mvprintw(rows-3, (i*10)+10, "#####");
    }
}

void drawPlayer(player Player) {
    mvprintw(Player.oldY, Player.oldX-2, "     ");
    mvprintw(Player.Y, Player.X-2, "--!--");
    Player.oldX = Player.X;
    Player.oldY = Player.Y;
}

void initPlayer(player *Player, int rows, int cols) {
    int i = 0;
    Player->maxX = cols;
    Player->maxY = rows-2;
    Player->oldX = cols/2;
    Player->oldY = rows-2;
    Player->X = cols/2;
    Player->Y = rows-2;
    Player->lives = MAX_PLAYER_LIVES;
    Player->score = 0;
    for(i=0; i<MAX_PLAYER_BULLETS; i++) {
        Player->bullets[i].active = false;
    }
}

void drawInvaders(invader *Invaders) {
    int i = 0;
    for(i = 0; i < MAX_INVADERS; i++) {
        if(!Invaders[i].active) continue;
        mvprintw(Invaders[i].oldY, Invaders[i].oldX-2, "     ");
        mvprintw(Invaders[i].Y, Invaders[i].X-2, "(-O-)");
        Invaders[i].oldX = Invaders[i].X;
        Invaders[i].oldY = Invaders[i].Y;
    }
}

void moveInvaders(invader *Invaders, int *direction, int maxCol) {
    int i = 0;
    bool moveDown = false;
    for(i = 0; i < MAX_INVADERS; i++) {
        if(!Invaders[i].active) continue;
        Invaders[i].oldX = Invaders[i].X;
        Invaders[i].oldY = Invaders[i].Y;
        Invaders[i].X += *direction;
        moveDown = (Invaders[i].X == 0 || Invaders[i].X == maxCol-5 || moveDown);
    }
    if (moveDown) {
        *direction = 0-*direction;
        for(i = 0; i < MAX_INVADERS; i++) {
            if(!Invaders[i].active) continue;
            Invaders[i].Y++;
        }
    }
}

void initInvaders(invader *Invaders, int maxCols) {
    int i = 0;
    int perLine = (maxCols - 20)/10;
    for(i = 0; i < MAX_INVADERS; i++) {
        Invaders[i].active = true;
        Invaders[i].X = ((i % perLine) * 10) + 10;
        Invaders[i].Y = (i / perLine) * 2;
        Invaders[i].oldX = Invaders[i].X;
        Invaders[i].oldY = Invaders[i].Y;
    }
}

void drawBullets(player *Player) {
    int b = 0;
    for(b = 0; b < MAX_PLAYER_BULLETS; b++) {
        if(Player->bullets[b].active) {
            mvprintw(Player->bullets[b].oldY, Player->bullets[b].oldX, " ");
            mvprintw(Player->bullets[b].Y, Player->bullets[b].X, "|");
            Player->bullets[b].oldX = Player->bullets[b].X;
            Player->bullets[b].oldY = Player->bullets[b].Y;
        }
    }
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
}

void drawScores(player *Player, int maxCols) {
    char hud[maxCols+1];
    int i = 0;
    for(i = 0; i<maxCols; i++) hud[i] = ' ';
    hud[maxCols] = 0;
    snprintf(hud, sizeof(hud), " Text Invaders!  SCORE:%05d  LIVES: ", Player->score);
    for(i = 0; i<Player->lives; i++) strcat(hud, "--!--   ");
    hud[strlen(hud)] = ' ';
    attron(A_REVERSE);
    mvprintw(Player->maxY+1,0,hud);
    attroff(A_REVERSE);
}

void initScreen(int *actRows, int* actCols) {
    initscr();
    getmaxyx(stdscr, *actRows, *actCols);
    clear();
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    refresh();
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
                    Player->bullets[b].Y = Player->Y-1;
                    Player->bullets[b].active = true;
                    Player->bullets[b].direction = BULLET_UP;
                    break;
                }
            }
            break;
    }

    return !quit;
}

int main(void) {
    bool isRunning = true;
    int rows, cols;
    int frame_timer = 0;
    int invaderDirection = INVADER_LEFT;
    player Player;
    invader Invaders[MAX_INVADERS];

    // Init Game
    initScreen(&rows, &cols);
    initInvaders(&Invaders[0], cols);
    initPlayer(&Player, rows, cols);
    initBases(rows, cols);

    // Main Loop
    while(isRunning) {
        drawPlayer(Player);
        if(frame_timer == 0) moveInvaders(&Invaders[0], &invaderDirection, cols);
        drawInvaders(&Invaders[0]);
        drawBullets(&Player);
        isRunning = checkCollisions();
        if(frame_timer == 0) moveBullets(&Player);
        drawScores(&Player, cols);
        isRunning = pollInput(&Player);
        refresh();
        frame_timer++;
        frame_timer = frame_timer % 1000;
    }

    endwin();
    return 0;
}