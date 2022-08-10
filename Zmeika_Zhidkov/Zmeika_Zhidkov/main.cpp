#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool GameOver;
const int widht = 20;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100];
int nTail;
enum eDirecrion { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecrion dir;

void Setup() {
	GameOver = false;
	dir = STOP;
	x = widht / 2 - 1;
	y = height / 2 - 1;
	fruit_x = rand() % widht;
	fruit_y = rand() % height;
	score = 0;
}

void Draw() {
	system("cls");
	for (int i = 0; i < widht + 1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < widht; j++) {
			if (j == 0 || j == widht - 1)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruit_y && j == fruit_x)
				cout << "*";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tail_x[k] == j && tail_y[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if (!print)
					cout << " ";
			}
			
		}
		cout << endl; //выход на новую строку
	}

	for (int i = 0; i < widht + 1; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			GameOver = true;
			break;
		}
	}

}

void Logic() {
	int prev_x = tail_x[0];
	int prev_y = tail_y[0];
	int prev2x, prev2y;
	tail_x[0] = x;
	tail_y[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2x = tail_x[i];
		prev2y = tail_y[i];
		tail_x[i] = prev_x;
		tail_y[i] = prev_y;
		prev_x = prev2x;
		prev_y = prev2y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	//if (x > widht || x < 0 || y > height || y < 0)
		//GameOver = true;
	if (x >= widht - 1)
		x = 0;
	else if (x < 0)
		x = widht - 2;

	if (y >= height)
		y= 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < nTail; i++) {
		if (tail_x[i] == x && tail_y[i] == y)
			GameOver = true;
	}

	if (x == fruit_x && y == fruit_y) {
		score += 1;
		fruit_x = rand() % widht;
		fruit_y = rand() % height;
		nTail++;
	}
}

int main() {
	Setup();
	while (!GameOver) {
		Draw();
		Input();
		Logic();
		Sleep(300);
	}

	return 0;
}