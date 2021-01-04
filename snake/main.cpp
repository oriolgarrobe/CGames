#include <iostream>
#include <conio.h>
using namespace std;

// GLobal Variables
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score; //coordinates
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;



/*
int getch();

int getch() {
  static int ch = -1, fd = 0;
  struct termios neu, alt;
  fd = fileno(stdin);
  tcgetattr(fd, &alt);
  neu = alt;
  neu.c_lflag &= ~(ICANON|ECHO);
  tcsetattr(fd, TCSANOW, &neu);
  ch = getchar();
  tcsetattr(fd, TCSANOW, &alt);
  return ch;
}


int kbhit(void);

int kbhit(void) {
  struct termios term, oterm;
  int fd = 0;
  int c = 0;
  tcgetattr(fd, &oterm);
  memcpy(&term, &oterm, sizeof(term));
  term.c_lflag = term.c_lflag & (!ICANON);
  term.c_cc[VMIN] = 0;
  term.c_cc[VTIME] = 1;
  tcsetattr(fd, TCSANOW, &term);
  c = getchar();
  tcsetattr(fd, TCSANOW, &oterm);
  if (c != -1)
  ungetc(c, stdin);
  return ((c != -1) ? 1 : 0);
}
*/


void Setup() {
  gameOver = false;
  dir = STOP;
  x = width / 2; //head position
  y = height / 2; //head position
  fruitX = rand() % width;
  fruitY = rand() % height;
  score = 0;
}

void Draw() {
  system("clear");
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
      else if (i == fruitY && j == fruitX) {
        cout << "F";
      }
      else {
        cout << " ";
      }
    }
    cout << endl;
  }

  for (int i = 0; i < width+1; i++) {
    cout << "#";
  }
  cout << endl;
}

void Input() {
  if (kbhit()) {
    switch (_getche()) {
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
  switch (dir) {
    case UP:
      y++;
      break;
    case DOWN:
      y--;
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
}

int main() {
  Setup();
  while (!gameOver) {
    Draw();
    Input();
    Logic();
  }
  return 0;
}
