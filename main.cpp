#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver; //to end the game
const int weidth=20;
const int height=20; //the dimension of our map
int headX, headY, fruitX, fruitY, score, tailX[100], tailY[100], nTail=0;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup(){
    gameOver = false;
    dir = STOP;
    headX = weidth/2;
    headY = height/2;
    fruitX = rand()%weidth+1;
    fruitY = rand()%height+1;
    score = 0;
}

void Drow(){
    system("cls");
    for(int i=0 ; i<=weidth ; i++){
        for(int j=0 ; j<=height ; j++){
            if((i==0 && j!=height) || j==0 || i==weidth ){
                cout << "#";

            }else if( j==height){                               //printing the bordures
                cout << "#"<< endl;
            }else if(i==headX && j==headY){
                cout << "O";
            }else if(i==fruitX && j==fruitY){
                cout << "F";
            }else{
                bool printBorder = false;
                for(int k=0 ; k<nTail ; k++){
                    if(tailX[k]==i && tailY[k]==j){
                        cout << "o";
                        printBorder = true;
                    }
                }
                if(!printBorder){
                    cout << " ";
                }
            }
        }

    }
    cout << endl;
    cout << "Score : " << score << endl;
}

void Input(){
    if(_kbhit()){
        switch(_getch()){
        case 'q':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'z':
            dir = UP;
            break;
        case 'x':
            gameOver=true;
            break;

        }
    }

}

void Logic(){

    int prevX = tailX[0];
    int prevY = tailY[0];
    int switchX, switchY;
    tailX[0] = headX;
    tailY[0] = headY;
    for(int i=1 ; i<nTail ; i++){
        switchX = tailX[i];
        switchY = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = switchX;
        prevY = switchY;
    }

    switch(dir){
    case LEFT:
        headY--;
        break;
    case DOWN:
        headX++;
        break;
    case RIGHT:
        headY++;
        break;
    case UP:
        headX--;
        break;
    default:
        break;
    }


    if(headX>=weidth) headX=1; else if(headX<=0) headX=weidth-1;
    if(headY>=height) headY=1; else if(headY<=0) headY=height-1;


    for(int i =0 ; i<nTail ; i++){
        if(tailX[i]==headX && tailY[i]==headY){
         gameOver=true;
        }
    }

    if(headX == fruitX && headY == fruitY){
        score +=10;
        fruitX = rand()%weidth+1;
        fruitY = rand()%height+1;
        nTail +=1;
    }
}


int main(){
    Setup();
    while(gameOver==false){
        Drow();
        Input();
        Logic();
    }
    return 0;
}
