#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;

enum Chessboard { WIDTH=80,HEIGHT=20 };
enum Direction { LEFT, DOWN, UP, RIGHT, CENTER };
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO CursorInfo={1,0};

class Snake {
    public:
        Snake();
        ~Snake();
        void FrameWork();
        void InitBoard();
        void NewFruit();
        void Action();
        void GameOver();
        void Eat();
        void Crawl();
    private:
        char board[WIDTH+1][HEIGHT+1];
        queue<COORD> Q;
        int speed;
        int move;
        int length;
        int score;
        int headx, heady;
};

Snake::Snake() {
    FrameWork();
    InitBoard();
    length=1;
    score=0;
    speed=100;
    move=CENTER;
}
Snake::~Snake(){
    CloseHandle(hOut);
}
void Snake::FrameWork(){
    system("cls");
    SetConsoleCursorPosition(hOut,COORD{0,0});
    cout<<"╔";
    SetConsoleCursorPosition(hOut,COORD{0,HEIGHT});
    cout<<"╚";
    for (int i = 2; i <= WIDTH; i += 2) {
		SetConsoleCursorPosition(hOut,COORD{i,0});
		cout << "═";
		SetConsoleCursorPosition(hOut,COORD{i,HEIGHT});
		cout << "═";
	}
    SetConsoleCursorPosition(hOut,COORD{WIDTH,0});
    cout<<"╗";
    SetConsoleCursorPosition(hOut,COORD{WIDTH,HEIGHT});
    cout<<"╝";
    for (int i = 1; i < HEIGHT; i ++) {
		SetConsoleCursorPosition(hOut,COORD{0,i});
		std::cout << "║";
		SetConsoleCursorPosition(hOut,COORD{WIDTH,i});
		std::cout << "║";
	}
    SetConsoleCursorPosition(hOut,COORD{WIDTH+15,1});
    cout<<"Some directions:";
    SetConsoleCursorPosition(hOut,COORD{WIDTH+2,2});
    cout<<"1. Control the direction by tabing direction keys";
    SetConsoleCursorPosition(hOut,COORD{WIDTH+2,3});
    cout<<"2. Tab space key to have a timeout.";
    SetConsoleCursorPosition(hOut,COORD{WIDTH+2,4});
    cout<<"3. Tab ESC to qiut game.";
    SetConsoleCursorPosition(hOut,COORD{WIDTH+2,5});
    cout<<"4. Eating the fruit will earn you some points according to";
    SetConsoleCursorPosition(hOut,COORD{WIDTH+2,6});
	cout<<"the length and speed of the snake.";
    SetConsoleCursorPosition(hOut,COORD{WIDTH+10,7});
    cout<<"Your current score: "<<score;
}
void Snake::InitBoard(){
    for(int i=0;i<=WIDTH;i++) for(int j=0;j<=HEIGHT;j++) board[i][j]=' ';
    for(int i=0;i<=WIDTH;i++){
        board[i][0]='@';
        board[i][HEIGHT]='@';
    }
    for(int i=0;i<=HEIGHT;i++){
        board[0][i]='@';
        board[WIDTH][i]='@';
    }
    while(Q.size()) Q.pop();
    srand(time(NULL));
    headx = rand() % (WIDTH - 5) + 3;
    heady = rand() % (HEIGHT - 5) + 3;
    board[headx][heady] = '*';
    Q.push(COORD{headx,heady});
    SetConsoleCursorPosition(hOut,COORD{headx,heady});
    cout<<"*";
    NewFruit();
}
void Snake::NewFruit(){
    int x, y;
    srand(time(NULL));
    do {
        x = rand() % (WIDTH - 5) + 3;
        y = rand() % (HEIGHT - 5) + 3;
    } while(board[x][y] != ' ');
    board[x][y] = '$';
    SetConsoleCursorPosition(hOut,COORD{x,y});
    cout<<"$";
}
void Snake::Action(){
    while(1){
        if(kbhit()){
            switch(getch()){
                case 'W':
                case 'w':move=UP;break;
                case 'S':
                case 's':move=DOWN;break;
                case 'A':
                case 'a':move=LEFT;break;
                case 'D':
                case 'd':move=RIGHT;break;
                case ' ':move=CENTER;break;
                case 27:GameOver();return;
            }
        }else{
            if(move==CENTER) continue;
            switch(move){
                case LEFT:headx--;break;
                case DOWN:heady++;break;
                case UP:heady--;break;
                case RIGHT:headx++;break;
            }
            if(board[headx][heady]=='*'||board[headx][heady]=='@'){GameOver();return ;}
            else if(board[headx][heady]=='$') Eat();
            else Crawl();
            SetConsoleCursorPosition(hOut,COORD{WIDTH+10,7});
            cout<<"Your current score: "<<score;
            if(move==LEFT||move==RIGHT) Sleep((speed*3)/length);
            else Sleep((speed*4.5)/length);
        }
    }
}
void Snake::GameOver(){
    SetConsoleCursorPosition(hOut,COORD{WIDTH/2,HEIGHT/2});
    cout<<"The game has ended.";
}
void Snake::Eat(){
    SetConsoleCursorPosition(hOut,COORD{headx,heady});
    cout<<"*";
    board[headx][heady]='*';
    Q.push(COORD{headx,heady});
    NewFruit();
    score+=speed*length/100;
    length++;
}
void Snake::Crawl(){
    SetConsoleCursorPosition(hOut,COORD{headx,heady});
    cout<<"*";
    board[headx][heady]='*';
    Q.push(COORD{headx,heady});
    COORD tail=Q.front();
    Q.pop();
    SetConsoleCursorPosition(hOut,tail);
    cout<<" ";
    board[tail.X][tail.Y]=' ';
}

int main() {
    system("title 贪吃蛇");
	system("mode con cols=150 lines=30");
    Snake snake;
    Sleep(2000);
    snake.Action();
}
