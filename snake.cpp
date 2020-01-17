#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <time.h>
#include <conio.h>
#define m 80

using namespace std;

class Snake {
    public:
        Snake();
        void NewFruit();
        void Ini();
        void Show();
        int Action();
        void GameOver();
        void Eat();
        void Crawl();
        void Instruct();
    private:
        char board[m][m];
        int move;
        int headx, heady;
};
queue<pair<int,int>> Q;

Snake::Snake() {
    cout<<"Welcome to TAN CHI SHE!sisisisisisisisisi"<<endl;
    headx = 0;
    heady = 0;
    for (int i = 0; i < m; i++) {  //initialize chessboard
        board[0][i] = '@';
        board[i][0] = '@';
        board[m - 1][i] = '@';
        board[i][m - 1] = '@';
    }
    for (int i = 0; i < m - 1; i++) for (int j = 0; j < m - 1; j++) board[i][j] = ' ';
    Ini();
    NewFruit();
    Show();
}
void Snake::NewFruit() {
    int x, y;
    srand(time(NULL));
    do {
        x = rand() % (m - 2) + 1;
        y = rand() % (m - 2) + 1;
    } while(board[x][y] == ' ');
    board[x][y] = '$';
}
void Snake::Ini(){
    int x, y, inimov = rand() % 4 + 1;
    switch (inimov) {
        case 1:move = 72;break;
        case 2:move = 75;break;
        case 3:move = 78;break;
        case 4:move = 80;break;
    }
    srand(time(NULL));
    x = rand() % (m - 6) + 3;
    y = rand() % (m - 6) + 3;
    board[x][y] = '*';
    Q.push(make_pair(x,y));
}
void Snake::Show(){
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++) cout<<board[i][j]<<" ";
        cout<<endl;
    }
}
int Snake::Action(){
    switch(move){
        case 72:headx--;break;
        case 75:heady--;break;
        case 78:heady++;break;
        case 80:headx++;break;
    }
    switch(board[headx][heady]){
        case '@':
        case '*':GameOver();return 0;break;
        case '$':Eat();break;
        case ' ':Crawl();break;
    }
    Show();
    Instruct();
}
void Snake::GameOver(){
    cout<<"The game has ended.\nInput an positive integer if you want to restart,and a negative one if you don`t."<<endl;
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
    pair<int,int> tail=Q.front;
    Q.pop();
    board[tail.first][tail.second]=' ';
}
void Instruct(){
    if(kbhit()){
        char c;
        switch (c){
        case /* constant-expression */:/* code */break;
        default:break;
        }
    }
}

int main() {
    int sig;
    while (1) {
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