#ifndef HEADERF_H
#define HEADERF_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <stdbool.h>

struct snake;
typedef struct snake SNAKE;
typedef SNAKE* ADRES;

char** create_field();

ADRES snakeGrowth(ADRES pocz,char segm, int x, int y);

void snake_na_planszy(char** plansza, ADRES snake,int valy, int valx);

void view_snake(ADRES pocz);

void view(char** plansza);

void presskey(char** plansza, ADRES snake);

void add_apple(char** plansza);

bool eat_apple(char** plansza, ADRES snake, int x, int y);

void zwolnij_pamiec(char** plansza);

void left(char** plansza, ADRES snake, int* x, int* y);

void right(char** plansza, ADRES snake, int* x, int* y);

void up(char** plansza, ADRES snake, int* x, int* y);

void down(char** plansza, ADRES snake, int* x, int* y);

void read_move();

bool touched_border(ADRES snake, char** plansza);

bool snake_collision(ADRES snake, char** plansza);

int score(ADRES snake);

void free_memo(ADRES snake, char** plansza);


#endif