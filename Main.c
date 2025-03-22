#include "headerf.h"

#define size 30


/*          WĄŻ         */

struct snake{
    char body;
    int x;
    int y;
    struct snake *next;
};
ADRES snakeGrowth(ADRES pocz,char segm, int x, int y){      
    ADRES new = (ADRES)malloc(sizeof(SNAKE));
    new->body=segm;
    new->x=x;
    new->y=y;
    new->next=NULL;
    if(pocz!=NULL) {
        ADRES obecny=pocz;
        while(obecny->next!=NULL){
            obecny=obecny->next;
        }
        obecny->next=new;
    }
    return new;
}

void view_snake(ADRES pocz){
    ADRES pom=pocz;
    int i=0;
    while(pom!=NULL){
        printf("%d. ",(i++));
        printf("%d %d\n",pom->x,pom->y);
        pom=pom->next;
    }
}

void snake_na_planszy(char** plansza, ADRES snake,int valy, int valx){
    ADRES pom = snake;
    int popx;
    int popy;
    while(pom!=NULL){
        if(pom->next==NULL){
            plansza[snake->x-valy][snake->y-valx]=' ';
        }
        if(pom != NULL && pom->next == NULL) {
        plansza[pom->x][pom->y] = ' ';
    }
        pom=pom->next;
    }
    pom=snake;
    ADRES pom2 = snake->next;
    int tempX;
    int tempY;
    int prevX = pom->x;
    int prevY = pom->y;
    while(pom2!=NULL){
        tempX = pom2->x;
        tempY = pom2->y;
        pom2->x = prevX;
        pom2->y = prevY;
        plansza[pom2->x][pom2->y]=pom2->body;
        prevX = tempX;
        prevY = tempY;
        pom=pom->next;
        pom2=pom2->next;
    }
    plansza[snake->x][snake->y]=snake->body;
}


/*          PLANSZA         */

char** create_field(){
    char** arr = (char**)malloc(size*sizeof(char*));
    for(int i=0;i<size;i++){
        arr[i]=(char*)malloc(size*sizeof(char));
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(i==0 || i==size-1){
                arr[i][j]='=';
                continue;
            }
            if(j==0 || j==size-1){
                arr[i][j]='|';
            }else{
                arr[i][j]=' ';
            }
        }
    }
    return arr;
}

void view(char** plansza){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            printw("%c",plansza[i][j]);
        }
        printw("\n");
    }
}

void presskey(char** plansza, ADRES snake){
    // 22 znaki
    char text[] = "Press any key to start";
    int kek=0;
    for(int i=size/2-7;i<size/2+7;i++){
        plansza[size/2-1][i] = text[kek++];
    }
    for(int i=size/2-4;i<size/2+4;i++){
        plansza[size/2+1][i] = text[kek++];
    }
    view(plansza);
    score(snake);
    getch();
    for(int i=size/2-7;i<size/2+7;i++){
        plansza[size/2-1][i] = ' ';
    }
    for(int i=size/2-4;i<size/2+4;i++){
        plansza[size/2+1][i] = ' ';
    }
    refresh();
    clear();
}


/*          JABŁKO          */

void add_apple(char** plansza){
    srand(time(NULL));
    int x=rand()%size;
    int y=rand()%size;
    while(plansza[x][y]!=' '){
        x=rand()%size;
        y=rand()%size;
    }
    plansza[x][y]='@';
}

bool eat_apple(char** plansza, ADRES snake, int x, int y){
    if(plansza[x][y]=='@'){
        add_apple(plansza);
        return true;
    }else{
        return false;
    }
}

/*          RUCH            */


void right(char** plansza, ADRES snake, int* x, int* y){
    if(eat_apple(plansza,snake,*x,*y+1)){
        snakeGrowth(snake,'o',*x,*y);
    }
    snake->y+=1;
    snake_na_planszy(plansza,snake,0,1);
    *y+=1;
}
void left(char** plansza, ADRES snake, int* x, int* y){
    if(eat_apple(plansza,snake,*x,*y-1)){
        snakeGrowth(snake,'o',*x,*y);
    }
    snake->y-=1;
    snake_na_planszy(plansza,snake,0,-1);
    *y-=1;
}
void up(char** plansza, ADRES snake, int* x, int* y){
    if(eat_apple(plansza,snake,*x-1,*y)){
        snakeGrowth(snake,'o',*x,*y);
    }
    snake->x-=1;
    snake_na_planszy(plansza,snake,-1,0);
    *x-=1;
}

void down(char** plansza, ADRES snake, int* x, int* y){
    if(eat_apple(plansza,snake,*x+1,*y)){
        snakeGrowth(snake,'o',*x,*y);
    }
    snake->x+=1;
    snake_na_planszy(plansza,snake,1,0);
    *x+=1;
}

int kierunek = KEY_RIGHT;

void read_move(){
    int key = getch();
    if(key == KEY_UP && kierunek!=KEY_DOWN){
        kierunek = key;
    }
    if(key == KEY_DOWN && kierunek!=KEY_UP){
        kierunek = key;
    }
    if(key == KEY_LEFT && kierunek!=KEY_RIGHT){
        kierunek = key;
    }
    if(key == KEY_RIGHT && kierunek!=KEY_LEFT){
        kierunek = key;
    }
}

/*          KONIEC GRY          */
bool touched_border(ADRES snake, char** plansza){
    ADRES pom = snake;
    int n=1;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(i==0 || i==size-1){
                if(plansza[i][j]=='O'){
                    while(pom!=NULL){
                        clear();
                        view(plansza);
                        n+=2;
                        napms(100-(n));
                        if(pom->x==i){
                            plansza[pom->x][pom->y]='=';
                            pom=pom->next;
                            refresh();
                            continue;
                        }
                        plansza[pom->x][pom->y]=' ';
                        pom=pom->next;
                        refresh();
                    }
                    clear();
                    return false;
                }
            }
            if(j==0 || j==size-1){
                if(plansza[i][j]=='O'){
                    while(pom!=NULL){
                        clear();
                        view(plansza);
                        n+=2;
                        napms(100-(n));
                        if(pom->y==j){
                            plansza[pom->x][pom->y]='|';
                            pom=pom->next;
                            refresh();
                            continue;
                        }
                        plansza[pom->x][pom->y]=' ';
                        pom=pom->next;
                        refresh();
                    }
                    clear();
                    return false;
                };
            }
        }
    }
    return true;
}

bool snake_collision(ADRES snake, char** plansza){
    ADRES pom = snake;
    int n=1;
    while(pom!=NULL){
        if(pom->body=='o'){
            if(snake->x==pom->x && snake->y==pom->y){
                plansza[pom->x][pom->y]='o';
                pom=snake;
                while(pom!=NULL){
                    clear();
                    view(plansza);
                    n+=2;
                    napms(100-(n));
                    napms(50);
                    plansza[pom->x][pom->y]=' ';
                    pom=pom->next;
                    refresh();
                }
                clear();
                return false;
            }
        }
        pom=pom->next;
    }
    return true;
}


/*                WYNIK                 */

int score(ADRES snake){
    int score=-1;
    int l=0;
    while(snake->next!=NULL){
        score+=10*(++l)-10;
        snake=snake->next;
    }
    score++;
    printw("Score: %d", score);
    return score;
}


/*          ZWALNIANIE PAMIĘCI          */

void free_memo(ADRES snake, char** plansza){
    for(int i=0;i<size;i++){
        free(plansza[i]);
    }
    free(plansza);
    ADRES pom=snake;
    while(pom!=NULL){
        snake=pom->next;
        free(pom);
        pom=snake;
    }
}




int main(){
    char **plansza=create_field();
    ADRES snake = NULL;
    snake = snakeGrowth(snake,'O',size/2,size/2);
    snakeGrowth(snake,'O',size/2,size/2);
    int wynik;
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    *x=size/2;
    *y=size/2;


    initscr();
    noecho();
    presskey(plansza,snake);
    nodelay(stdscr, TRUE);              // pozwala żeby getch() nie czekało na wciśnięcie klawisza
    keypad(stdscr, TRUE);               // obsługa klawiszy strzałek
    add_apple(plansza);
    while(touched_border(snake,plansza)!=false && snake_collision(snake, plansza)!=false){
        napms(100);
        view(plansza);
        wynik = score(snake);
        read_move();
        switch(kierunek){
        case KEY_UP:
            up(plansza,snake,x,y);
            break;
        case KEY_DOWN:
            down(plansza,snake,x,y);
            break;
        case KEY_LEFT:
            left(plansza,snake,x,y);
            break;
        case KEY_RIGHT:
            right(plansza,snake,x,y);
            break;
        }
        refresh();
        clear();
        }
    nodelay(stdscr, FALSE);
    printw("\n\n!! G A M E   O V E R !!\n\n");
    printw("Your score: %d\n\n\n\n", wynik);
    getch();
    endwin();


    // view_snake(snake);
    free_memo(snake,plansza);
    return 0;
}