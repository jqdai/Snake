#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;

enum Chessboard { WIDTH=80,HEIGHT=20 };
enum Direction { LEFT, DOWN, UP, RIGHT, CENTER };
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

class Snake {
    public:
        Snake();
        ~Snake();
        void FrameWork();
        void InitBoard();
        void NewFruit();
        void Action();
        void GameOver();
    private:
        vector<COORD> V;
        int speed;
        int move;
        int length;
        int score;
        int fruitx,fruity;
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
    cout<<"4. Getting the fruit will earn you some points according to the length and speed of the snake.";
    SetConsoleCursorPosition(hOut,COORD{WIDTH+10,6});
    cout<<"Your current score: "<<score;
}
void Snake::InitBoard(){
    NewFruit();
    srand(time(NULL));
    int headx=WIDTH/2,heady=HEIGHT/2;
    V.push_back(COORD{headx,heady});
    SetConsoleCursorPosition(hOut,COORD{headx,heady});
    cout<<"*";
}
void Snake::NewFruit(){
    srand(time(NULL));
    fruitx = rand() % (WIDTH - 5) + 3;
    fruity = rand() % (HEIGHT - 5) + 3;
    SetConsoleCursorPosition(hOut,COORD{fruitx,fruity});
    cout<<"$";
}
void Snake::Action(){
    while(1){
        if(V[0].X==0||V[0].Y==0||V[0].X==WIDTH||V[0].Y==HEIGHT){
            GameOver();
            return ;
        }else if(kbhit()){
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
                case 27:GameOver();return ;
            }
        }else{
            if(move==CENTER) continue;
            for(int i=0;i<length;i++){
                SetConsoleCursorPosition(hOut,COORD{V[i].X,V[i].Y});
                cout<<" ";
            }
            for(int i=length-1;i>0;i--){
                V[i].X=V[i-1].X;
                V[i].Y=V[i-1].Y;
            }
            switch(move){
                case LEFT:V[0].X--;break;
                case DOWN:V[0].Y++;break;
                case UP:V[0].Y--;break;
                case RIGHT:V[0].X++;break;
            }
            if(V[0].X==fruitx&&V[0].Y==fruity){
                V.push_back(COORD{V[length-1].X,V[length-1].Y});
                NewFruit();
                score+=length*speed;
                length++;
            }
            for(int i=0;i<length;i++){
                SetConsoleCursorPosition(hOut,COORD{V[i].X,V[i].Y});
                cout<<"*";
            }
            SetConsoleCursorPosition(hOut,COORD{WIDTH+10,6});
            cout<<"Your current score: "<<score;
            if(move==LEFT||move==RIGHT) Sleep((speed*3)/length);
            else Sleep((speed*4.5)/length);
        }
    }
}
void Snake::GameOver(){
    SetConsoleCursorPosition(hOut,COORD{WIDTH/2,HEIGHT/2});
    cout<<"The game has ended.";
    for(int i=0;i<WIDTH-WIDTH/2-1;i++) cout<<endl<<"║";
    cout<<endl<<"║"<<endl<<endl;
}

int main() {
    system("title 贪吃蛇");
	system("mode con cols=150 lines=30");
    Snake snake;
    Sleep(2000);
    snake.Action();
}
