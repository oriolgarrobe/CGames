#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>

using namespace std;

enum eDir
{
	STOP = 0, UP, UPLEFT, UPRIGHT, DOWN, DOWNLEFT, DOWNRIGHT
};


class cBall
{
private:
	int x, y;
	int originalX, originalY;
	eDir direction;
public:
	cBall(int posX, int posY)
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
		direction = STOP;
	}
	void Reset()
	{
		x = originalX;
		y = originalY;
		direction = STOP;
	}
	void changeDirection(eDir d)
	{
		direction = d;
	}
	void randomDirection()
	{
		direction = (eDir)((rand() % 3) + 1);
	}
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline eDir getDirection() { return direction; }
	void Move()
	{
		switch (direction)
		{
		case STOP:
			break;
		case UP:
			y--;
			break;
		case UPLEFT:
			y--; x--;
			break;
		case UPRIGHT:
			y--; x++;
			break;
		case DOWN:
			y++;
			break;
		case DOWNLEFT:
			y++; x--;
			break;
		case DOWNRIGHT:
			y++; x++;
			break;
		default:
			break;
		}
	}
	friend ostream& operator<<(ostream& o, cBall c)
	{
		o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]" << endl;
		return o;
	}
};

class cPaddle
{
private:
	int x, y;
	int originalX, originalY;
public:
	cPaddle()
	{
		x = y = 0;
	}
	cPaddle(int posX, int posY) : cPaddle()
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}
	inline void Reset() { x = originalX; y = originalY; }
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void moveRight() { x += 2; }
	inline void moveLeft() { x -= 2; }

	friend ostream& operator<<(ostream& o, cPaddle c)
	{
		o << "Paddle [" << c.x << "," << c.y << "]";
		return o;
	}
};

class cGameManager
{
private:
	int width, height;
	int score;
	char left, right;
	bool quit;
	cBall * ball;
	cPaddle *player;
public:
	cGameManager(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		left = 'a'; right = 'd';
		score = 0;
		width = w; height = h;
		ball = new cBall(w / 2, h - 2);
		player = new cPaddle(w / 2 - 4, h - 1);
	}
	~cGameManager()
	{
		delete ball, player;
	}
	void ScoreUp(cPaddle * player)
	{
		//go up everytime a brick is broken
		ball->Reset();
		player->Reset();
		Draw();
		Sleep(2000);
	}
	void Draw() // NEXT STEP
	{
		//draw the thingy
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		system("cls");

		// 
		for (int i = 0; i < width + 1; i++)
		{
			SetConsoleTextAttribute(h, 15);
			cout << "\xB2";
		}
		cout << endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int ballx = ball->getX();
				int bally = ball->getY();
				int playerx = player->getX();
				int playery = player->getY();

				if (j == 0)
				{
					SetConsoleTextAttribute(h, 15);
					cout << "\xB2"; //left wall
				}

				if (j == width - 1)
				{
					SetConsoleTextAttribute(h, 15);
					cout << "\xB2"; //right wall
				}

				if (j == ballx - 1 && i == bally)
				{
					SetConsoleTextAttribute(h, 14);
					cout << "\x9B"; //ball
				}

				//Paddle
				else if (j == playerx && i == playery)
				{
					SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					cout << "\xDB";
				}
				else if (j == playerx + 1 && i == playery)
				{
					SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					cout << "\xDB";
				}
				else if (j == playerx + 2 && i == playery)
				{
					SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					cout << "\xDB";
				}
				else if (j == playerx + 3 && i == playery)
				{
					SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					cout << "\xDB";
				}
				else if (j == playerx + 4 && i == playery)
				{
					SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					cout << "\xDB";
				}
				else if (j == playerx + 5 && i == playery)
				{
					SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					cout << "\xDB";
				}
				else if (j == playerx + 6 && i == playery)
				{
					SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					cout << "\xDB";
				}

				else
					cout << " ";
			}

			cout << endl;
		}
		cout << endl;
	}
	void Move()
	{
		ball->Move();

		int ballx = ball->getX();
		int bally = ball->getY();
		int playerx = player->getX();
		int playery = player->getY();

		if (_kbhit())
		{
			char current = _getch();

			if (current == left)
				if (playerx > 0)
					player->moveLeft();

			if (current == right)
				if (playerx + 8 < width)
					player->moveRight();

			if (ball->getDirection() == STOP)
				ball->randomDirection();

			if (current == 'q')
				quit = true;
		}
	}
	void Logic()
	{
		int ballx = ball->getX();
		int bally = ball->getY();
		int playerx = player->getX();
		int playery = player->getY();

		//Paddle
		for (int i = 0; i < 9; i++)
			if (bally == playery - 1 && ball->getDirection() != STOP)
				if (ballx == playerx + i)
					ball->changeDirection((eDir)((rand() % 3) + 1));

		//Top wall
		if (bally == 0)
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

		//Right wall
		if (ballx == width - 1)
			ball->changeDirection(ball->getDirection() == UPRIGHT ? UPLEFT : DOWNLEFT);

		//Left wall
		if (ballx == 1)
			ball->changeDirection(ball->getDirection() == UPLEFT ? UPRIGHT : DOWNRIGHT);

		//Bottom wall
		if (bally == height)
			ScoreUp(player);
	}
	void Run()
	{
		while (!quit)
		{
			Draw();
			Move();
			Logic();
		}
	}
};


int main()
{
	cGameManager c(40, 20);
	c.Run();

	return 0;

}