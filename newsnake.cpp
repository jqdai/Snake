#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <time.h>
#include <conio.h>
#include <windows.h>
#define m 20
using namespace std;
enum Chessboard { WIDTH=80,HEIGHT=20 };
enum Direction { LEFT = 72, DOWN = 75, UP = 77, RIGHT = 80, CENTER };
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

class Snake {
    public:
        Snake();
        ~Snake();
        void FrameWork();
        bool Alive(int,int);
        void NewFruit();
        void Ini();
        int Action();
        void GameOver();
        void Eat();
        void Crawl();
        void Instruct();
    private:
        char board[WIDTH][HEIGHT];
        queue<pair<int,int> > Q;
        int move;
        int length;
        int score;
        int headx, heady;
};

Snake::Snake() {
    FrameWork();
    srand(time(NULL));
    headx = 0;
    heady = 0;
    length = 1;
    score = 0;
    move=CENTER;
    queue<pair<int,int> > empty;
    swap(empty,Q);
    Ini();
    NewFruit();
}
Snake::~Snake(){
    CloseHandle(hOUT);
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
    cout<<"4. Getting the fruit will earn you 10 points.";
    SetConsoleCursorPosition(hOut,COORD{WIDTH+10,6});
    cout<<"Your current score: "<<score;
}
bool Snake::Alive(int x,int y){
    return !(x*y==0||x==WIDTH||y==HEIGHT);
}
void Snake::NewFruit() {
    int x, y;
    srand(time(NULL));
    do {
        x = rand() % (m - 2) + 1;
        y = rand() % (m - 2) + 1;
    } while(board[x][y] != ' ');
    board[x][y] = '$';
}
void Snake::Ini(){
    move=CENTER;
    srand(time(NULL));
    headx = rand() % (m - 6) + 3;
    heady = rand() % (m - 6) + 3;
    board[headx][heady] = '*';
    Q.push(make_pair(headx,heady));
}
int Snake::Action(){
    switch(move){
        case LEFT:headx--;break;
        case DOWN:heady--;break;
        case UP:heady++;break;
        case RIGHT:headx++;break;
    }
    switch(board[headx][heady]){
        case '@':
        case '*':GameOver();return 0;
        case '$':Eat();break;
        case ' ':Crawl();break;
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++) cout<<board[i][j]<<" ";
        cout<<endl;
    }
    Instruct();
    return 1;
}
void Snake::GameOver(){
    cout<<endl<<endl<<"The game has ended.\nInput an positive integer if you want to restart,and a negative one if you don`t."<<endl;
    int ss;
    cin>>ss;
    if(!(ss>0)){
        cout<<"Game over.See you next time!"<<endl;
        exit(0);
    }
}
void Snake::Eat(){
    board[headx][heady]='*';
    Q.push(make_pair(headx,heady));
    NewFruit();
}
void Snake::Crawl(){
    board[headx][heady]='*';
    Q.push(make_pair(headx,heady));
    pair<int,int> tail=Q.front();
    Q.pop();
    board[tail.first][tail.second]=' ';
}
void Snake::Instruct(){
	clock_t timeBegin = clock();
    char c;
    while(1){
        if(kbhit()) c=getch();
        else if (clock() - timeBegin >= 1000) break;//why?????
    }
    if(c==72||c==75||c==77||c==80) move=c;
}

int main() {
    system("title 贪吃蛇");
	system("mode con cols=150 lines=30");
    int sig;
    while (1) {
        cout<<"Welcome to TAN CHI SHE!sisisisisisisisisi"<<endl<<endl;
        cout << "Tab any number key to start he game.<<<<<<>>>>>>Tab any other keys to exit." << endl;
        cin >> sig;
        if (!(sig >= 0)) {
            cout << "Successfully exited.See you next time." << endl;
            exit(0);
        }
        Snake snake;
        while(snake.Action()) ;
    }
}
