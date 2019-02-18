#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

enum EnumDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class Ball
{
private:
	int x, y;
	int originalX, originalY;
	EnumDir direction;

public:
	Ball(int posX, int posY) {
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
		direction = STOP;
	}

	inline int GetX() { return x; }
	inline int GetY() { return y; }
	inline EnumDir GetDirection() { return direction; }

	void Reset() {
		x = originalX;
		y = originalY;
		direction = STOP;
	}

	void ChangeDirection(EnumDir d) {
		direction = d;
	}

	void RandomDirection() {
		direction = (EnumDir)((rand() % 6) + 1);
	}

	void Move() {
		switch (direction) {
			case STOP:
				break;
			case LEFT:
				x--;
				break;
			case RIGHT:
				x++;
				break;
			case UPLEFT:
				x--;
				y--;
				break;
			case DOWNLEFT:
				x--;
				y++;
				break;
			case UPRIGHT:
				x++;
				y--;
				break;
			case DOWNRIGHT:
				x++;
				y++;
				break;
			default:
				break;
		}
	}

	friend ostream & operator<<(ostream & o, Ball c) {
		o << "Ball [" << c.x << ", " << c.y << "][" << c.direction << "]";
		return o;
	}
};

class Paddle
{
private:
	int x, y;
	int originalX, originalY;
public:
	Paddle()
	{
		x = 0;
		y = 0;
	}

	Paddle(int posX, int posY)
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}
	inline void Reset(){
		x = originalX;
		y = originalY;
	}
	inline int GetX() { return x; }
	inline int GetY() { return y; }
	inline void MoveUp() { y--; }
	inline void MoveDown() { y++; }

	friend ostream & operator<<(ostream & o, Paddle c) {
		o << "Paddle [" << c.x << ", " << c.y << "]";
		return o;
	}
};

class GameManager
{
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	Ball *ball;
	Paddle *player1;
	Paddle *player2;
public:
	GameManager(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w';
		up2 = 'i';
		down1 = 's';
		down2 = 'k';
		score1 = 0;
		score2 = 0;
		width = w;
		height = h;
		ball = new Ball(w/2, h/2);
		player1 = new Paddle(1, h/2 -3);
		player2 = new Paddle(w - 2, h/2 - 3);

	}

	~GameManager()
	{
		delete player1, player2, ball;
	}

	void ScoreUp(Paddle *player)
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
		system("cls"); // in linux c type "clear"
		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int ballx = ball->GetX();
				int bally = ball->GetY();
				int player1x = player1->GetX();
				int player2x = player2->GetX();
				int player1y = player1->GetY();
				int player2y = player2->GetY();

				if (j == 0)
					cout << "\xB2";

				if (ballx == j && bally == i)
					cout << "O";
				else if (player1x == j && player1y == i)
					cout << "\xDB";
				else if (player1x == j && player1y + 1 == i)
					cout << "\xDB";
				else if (player1x == j && player1y + 2 == i)
					cout << "\xDB";
				else if (player1x == j && player1y + 3 == i)
					cout << "\xDB";
				else if (player2x == j && player2y == i)
					cout << "\xDB";
				else if (player2x == j && player2y + 1 == i)
					cout << "\xDB";
				else if (player2x == j && player2y + 2 == i)
					cout << "\xDB";
				else if (player2x == j && player2y + 3 == i)
					cout << "\xDB";
				else
					cout << " ";

				if (j == width - 1)
					cout << "\xB2";
			}
			cout << endl;
		}

		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		cout << score1 << " - " << score2 << endl;
	}

	void Input()
	{
		ball->Move();
		int ballx = ball->GetX();
		int bally = ball->GetY();
		int player1x = player1->GetX();
		int player2x = player2->GetX();
		int player1y = player1->GetY();
		int player2y = player2->GetY();

		if (_kbhit()) {
			char current = _getch();

			// Player 1 input
			if (current == up1)
				if (player1y > 0)
					player1->MoveUp();

			if (current == down1)
				if (player1y + 4 < height)
					player1->MoveDown();

			//Player 2 input
			if (current == up2)
				if (player2y > 0)
					player2->MoveUp();

			if (current == down2)
				if (player2y + 4 < height)
					player2->MoveDown();

			if (ball->GetDirection() == STOP)
				ball->RandomDirection();

			if (current == 'q')
				quit = true;
		}
	}

	void Logic()
	{
		int ballx = ball->GetX();
		int bally = ball->GetY();
		int player1x = player1->GetX();
		int player2x = player2->GetX();
		int player1y = player1->GetY();
		int player2y = player2->GetY();

		//Player 1 collision
		for (int i = 0; i < 4; i++)
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball->ChangeDirection((EnumDir)((rand() % 3) + 4));

		//Player 2 collision
		for (int i = 0; i < 4; i++)
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball->ChangeDirection((EnumDir)((rand() % 3) + 1));

		//Ball collision
		if (bally == height - 1) // bottom wall
			ball->ChangeDirection(ball->GetDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		if (bally == 0) // top wall
			ball->ChangeDirection(ball->GetDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		if (ballx == width - 1) // right wall
			ScoreUp(player1);
		if (ballx == 0) // left wall
			ScoreUp(player2);
	}

	void Run()
	{
		while (!quit) {
			Draw();
			Input();
			Logic();
			Sleep(100);
		}
	}
};

int main() {
	
	GameManager gm(40, 20);
	gm.Run();
	return 0;
}