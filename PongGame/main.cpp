#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

enum eDir 
{ 
	STOP = 0, LEFT, UPLEFT, DOWNLEFT, RIGHT, UPRIGHT, DOWNRIGHT
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
		x = posX; y = posY;
		direction = STOP;
	}
	void Reset()
	{
		x = originalX; y = originalY;
		direction = STOP;
	}
	void changeDirection(eDir d)
	{
		direction = d;
	}
	void randomDirection()
	{
		direction = (eDir)((rand() % 6) + 1);
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
		case LEFT:
			x--;
			break;
		case UPLEFT:
			x--; y--;
			break;
		case DOWNLEFT:
			x--; y++;
			break;
		case RIGHT:
			x++;
			break;
		case UPRIGHT:
			x++; y--;
			break;
		case DOWNRIGHT:
			x++; y++;
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
	inline void moveUp() { y--; }
	inline void moveDown() { y++; }

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
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	cBall * ball;
	cPaddle *player1;
	cPaddle *player2;
public:
	cGameManager(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w'; up2 = 'i';	
		down1 = 's'; down2 = 'k';
		score1 = score2 = 0;
		width = w; height = h;
		ball = new cBall(w / 2, h / 2);
		player1 = new cPaddle(1, h / 2 - 3);
		player2 = new cPaddle(w - 2, h / 2 - 3);
	}
	~cGameManager()
	{
		delete ball, player1, player2;
	}
	void ScoreUp(cPaddle * player)
	{
		if (player == player1)
			score1++;
		else if (player == player2)
			score2++;
		ball->Reset();
		player1->Reset();
		player2->Reset();
	}
	void Draw()
	{
		system("cls");
		for (int i = 0; i < width + 1; i++)
			cout << "\xB2";
		cout << endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j  < width; j ++)
			{
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = player1->getX();
				int player1y = player1->getY();
				int player2x = player2->getX();
				int player2y = player2->getY();

				if (j == 0)
					cout << "\xB2"; //top wall
				if (j == width - 1)
					cout << "\xB2"; //bottom wall
				if (j == ballx && i == bally)
					cout << "\x9B"; //ball
				//paddle1
				else if (j == player1x && i == player1y)
					cout << "\xDB"; 
				else if (j == player1x && i == player1y + 1)
					cout << "\xDB"; 
				else if (j == player1x && i == player1y + 2)
					cout << "\xDB"; 
				else if (j == player1x && i == player1y + 3)
					cout << "\xDB";

				//paddle2 width - 1
				else if (j == player2x  && i == player2y)
					cout << "\xDB";
				else if (j == player2x && i == player2y + 1)
					cout << "\xDB";
				else if (j == player2x && i == player2y + 2)
					cout << "\xDB";
				else if (j == player2x && i == player2y + 3)
					cout << "\xDB";

				else
					cout << " ";
					
			}
			cout << endl;

		}

		for (int i = 0; i < width + 1; i++)
			cout << "\xB2";
		cout << endl;

		cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
	}
	void Move()
	{
		ball->Move();

		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		if (_kbhit())
		{
			char current = _getch();

			if (current == up1)
				if (player1y > 0)
					player1->moveUp();
			if (current == down1)
				if (player1y + 4 < height)
					player1->moveDown();
			if (current == up2)
				if (player2y > 0)
					player2->moveUp();
			if (current == down2)
				if (player2y + 4 < height)
					player2->moveDown();

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
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		//Left paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball->changeDirection((eDir)((rand() % 3) + 4));
		//Right paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball->changeDirection((eDir)((rand() % 3) + 1));

		// Bottom wall
		if (bally == height - 1)
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		/*
		if ball->getDirection() == DOWNRIGHT
			ball->changeDirection((eDir)(UPRIGHT))
		else
			ball->changeDirection((eDir)(UPLEFT))
		*/

		//Top wall
		if (bally == 0)
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

		// Right wall
		if (ballx == width - 1)
			ScoreUp(player1);
		if (ballx == 0)
			ScoreUp(player2);
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