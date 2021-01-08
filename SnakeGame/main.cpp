#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

// GLobal Variables
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score; //coordinates
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

// Game options

//The snake can go through the walls
bool through;
// Candy
int candyX, candyY, nfruit;



void Setup() {
  gameOver = false;
  through = true;
  dir = STOP;
  x = width / 2; //head position
  y = height / 2; //head position
  fruitX = rand() % width;
  fruitY = rand() % height;
  candyX = rand() % width;
  candyY = rand() % height;
  score = 0;
  nfruit = 0;
}

void Draw() {
  system("cls");
  for (int i = 0; i < width+1; i++) {
    cout << "#";
  }
  cout << endl;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (j == 0) {
        cout << "#";
      }
      if (j == width-1) {
        cout << "#";
      }
      if (i == y && j == x) {
        cout << "O";
      }
      else if (i == candyY && j == candyX) {
          if (score != 0 && nfruit % 4 == 0)
          {
              cout << "C";
          }
          else
          {
              cout << " ";
          }
      }
      else if (i == fruitY && j == fruitX) {
        cout << "F";
      }
      else {
          bool print = false;
          for (int k = 0; k < nTail; k++)
          {
              if (tailX[k] == j && tailY[k] == i)
              {
                  cout << "o";
                  print = true;
              }
          }
          if (!print)
          {
              cout << " ";
          }
      }
    }
    cout << endl;
  }

  for (int i = 0; i < width+1; i++) {
    cout << "#";
  }
  cout << endl;
  cout << "Score: " << score  << endl;
}

void Input() {
  if (_kbhit()) {
    switch (_getch()) {
      case 'a':
        dir = LEFT;
        break;
      case 's':
        dir = DOWN;
        break;
      case 'd':
        dir = RIGHT;
        break;
      case 'w':
        dir = UP;
        break;
      case 'x':
        gameOver = true;
        break;
    }
  }

}

void Logic() {

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        default:
            break;
    }

    // Snake goes theough walls or not
    if (!through)
    {
        if (x > width - 2 || x < 0 || y > height || y < 0)
            gameOver = true;
    }
    else
    {
        if (x >= width - 1) x = 0; else if (x < 0) x = width - 2;
        if (y >= height) y = 0; else if (y < 0) y = height - 1;
    }
    
    for (int i = 0; i < nTail; i++)
    {
        if (x == tailX[i] && y == tailY[i])
        {
            gameOver = true;
        }
    }
    if (x == fruitX && y == fruitY) {
        score += 10;
        nfruit += 1;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
    else if (x == candyX && y == candyY) {
        score += 40;
        candyX = rand() % width;
        candyY = rand() % height;
        nTail++;
    }
      
}

int main() {
  Setup();
  while (!gameOver) {
    Draw();
    Input();
    Logic();
    Sleep(10);
  }
  return 0;
}
