#include <iostream>

using namespace std;

enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class cBall
{
private:
	int x, y;
	int originalX, originalY;

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
	inline getX() { return x; }
	inline getY() { return y; }
	inline getDirection() { return direction; }
};

cBall::cBall()
{
}

cBall::~cBall()
{
}

int main() {

	return 0;
}