#include <ncurses.h>
#include "game.h"
#include <stdlib.h>


struct jugador jug1 = {12, 5, "<0>"};
struct enemy enemy[7] = {0,0,'*', 0,3,'*', 0,6,'*',0,9,'*', 0,12,'*', 0,15,'*', 0,18,'*'};
struct enemy *enemigo = enemy;
struct jugador *player = &jug1;


int num = 3;//Numero de colisiones permitidas, se resta en 1 por cada colision.
int EXIT = 0;//flag para salir del juego.
int ramdom;



WINDOW *wnd;


int init() {
    

    wnd = initscr();
    cbreak();
    noecho();
    /*This option enables ncurses to interpret 
    action keys, rather than print out escape sequences.*/
    keypad(wnd, true);
    /*This disables blocking when using wgetch(). 
    It's important if we want to animate something 
    while still listening for input.*/
    nodelay(wnd, true);
    /*Simply tells ncurses to make the cursor invisible*/
    curs_set(0);


    return 0;
}
    

void run() {
    
    while(1)
    {
        update();
        moverJugador(&EXIT, player);
        logicaEnemigo(enemigo);
        
        if (EXIT)break;
            
    }
}


void closer() {
    endwin();
}


void dibujarJugador(struct jugador *jugador)
{
    mvprintw(jugador->pos.y, jugador->pos.x, jugador->mono);
    refresh();
}


void limiteJugador(struct jugador* player)
{
    if(player->pos.x < 0) player->pos.x+=1;
    else if(player->pos.x > 18) player->pos.x-=1;
}

void moverJugador(int *EXIT, struct jugador *player)
{
    
    int caracter;
    caracter = wgetch(wnd);
        borrarJugador(player);
        switch(caracter) {
            case 'q':
                *EXIT = 1;
                break;
            case KEY_UP:
            case 'w':
                player->pos.y -= 1;
                break;
            case KEY_DOWN:
            case 's':
                player->pos.y += 1;
                break;
            case KEY_LEFT:
            case 'a':
                player->pos.x -= 1;
                break;
            case KEY_RIGHT:
            case 'd':
                player->pos.x += 1;
                break;
            default:
                break;
        }
        limiteJugador(player);
        dibujarJugador(player);
}

void borrarJugador(struct jugador *jugador)
{
    mvprintw(jugador->pos.y, jugador->pos.x, "     ");
    refresh();
}


void dibujarEnemigo(struct enemy *enemigo)
{
    enemigo->pos.y += 1;
    mvaddch(enemigo->pos.y, enemigo->pos.x, enemigo->caracter);
    refresh();

}

void moverEnemigo(struct enemy *enemigo)
{
    borrarEnemigo(enemigo);
    dibujarEnemigo(enemigo);
    colision(enemigo, player, &num, &EXIT);
    limiteEnemigo(enemigo);
    
}


void borrarEnemigo(struct enemy *enemigo)
{
    mvaddch(enemigo->pos.y, enemigo->pos.x, ' ');
    refresh();
}

void logicaEnemigo(struct enemy *enemigo)
{
    ramdom = rand()%7;
    moverEnemigo(&enemigo[ramdom]);



}

void limiteEnemigo(struct enemy *enemigo)
{
    if (enemigo->pos.y > 14)
    {
        borrarEnemigo(enemigo);
        enemigo->pos.y = 0;
        
    }
    
}


void colision(struct enemy* enemigo, struct jugador* jugador, int*num, int*EXIT)
{
    move(0,30);
    printw("%d", *num);
    refresh();
    if(enemigo->pos.x == jugador->pos.x && enemigo->pos.y == jugador->pos.y ||
    enemigo->pos.x-1 == jugador->pos.x+1 && enemigo->pos.y == jugador->pos.y ||
    enemigo->pos.x == jugador->pos.x+1 && enemigo->pos.y == jugador->pos.y) 
    {
        borrarJugador(player);
        borrarEnemigo(enemigo);
        jugador->pos.x = 5;
        enemigo->pos.y = 0;
        *num -= 1;
        move(0,30);
        printw("%d", *num);
        refresh();
    }
    if(*num == 0) *EXIT = 1;
    
}
void update(void)
{
    napms(34);
}