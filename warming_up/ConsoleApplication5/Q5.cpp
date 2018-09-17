#include <iostream>

using namespace std;


class dot {
public:
	int x;
	int y;
};


class shape {
public:
	dot pos1;
	dot pos2;
	int xr;
	int yr;
	dot middle;

};

void _Check(shape first, shape second, int mod);



int main() {
	char mod;
	char command;
	char dust;
	shape first;
	shape second;
	

	cout << "Input Shape Combination: ";
	cin >> mod;

	

	switch (mod) {
	case '1':
		cout << "Shape 1: ";
		cin >> dust >> first.pos1.x >> dust >> first.pos1.y >> dust >> dust >> first.pos2.x >> dust >> first.pos2.y >> dust;
		cout << "Shape 2: ";
		cin >> dust >> second.pos1.x >> dust >> second.pos1.y >> dust >> dust >> second.pos2.x >> dust >> second.pos2.y >> dust;
		break;

	case '2':
		cout << "Shape 1: ";
		cin >> dust >> first.pos1.x >> dust >> first.pos1.y >> dust >> dust >> first.pos2.x >> dust >> first.pos2.y >> dust;
		cout << "Shape 2: ";
		cin >> dust >> second.pos1.x >> dust >> second.pos1.y >> dust >> dust >> second.pos2.x >> dust >> second.pos2.y >> dust;
		break;


	default:
		cout << "올바르지 않은 입력입니다";
	}

	while (1) {

		cout << "Command: ";
		cin >> command;

		switch (command)
		{
		case 'a':
			second.pos1.x -= 60;
			second.pos2.x -= 60;
			_Check(first, second, mod);
			break;

		case 'd':
			second.pos1.x += 60;
			second.pos2.x += 60;
			_Check(first, second, mod);
			break;

		case 's':
			second.pos1.y -= 60;
			second.pos2.y -= 60;
			_Check(first, second, mod);
			break;

		case 'w':
			second.pos1.y += 60;
			second.pos2.y += 60;
			_Check(first, second, mod);
			break;

		}

	}

}

void _Check(shape first, shape second, int mod) {
	
	first.xr = (first.pos2.x - first.pos1.x) / 2;
	first.yr = (first.pos2.y - first.pos1.y) / 2;
	first.middle.x = first.pos1.x + first.xr;
	first.middle.y = first.pos1.y + first.yr;
	cout << "Shape 1: (" << first.pos1.x << ", " << first.pos1.y << ") (" << first.pos2.x << ", " << first.pos2.y << ")\n";


	second.xr = (second.pos2.x - second.pos1.x) / 2;
	second.yr = (second.pos2.y - second.pos1.y) / 2;
	second.middle.x = second.pos1.x + second.xr;
	second.middle.y = second.pos1.y + second.yr;
	cout << "Shape 2: (" << second.pos1.x << ", " << second.pos1.y << ") (" << second.pos2.x << ", " << second.pos2.y << ")\n";

	double length;
	int xtemp = second.middle.x - first.middle.x;
	int ytemp = second.middle.y - first.middle.y;


	switch (mod)
	{
	case '1':
		if (xtemp < 0)
			xtemp *= -1;

		if (ytemp < 0)
			ytemp *= -1;

		if ((first.xr + second.xr) >= xtemp && (first.yr + second.yr) >= ytemp)
			cout << "Rectangle 1 & Rectangle 2 collide!!\n";
		break;

	case '2':
		length = sqrt(pow(xtemp, 2) + pow(ytemp, 2));
		if (length < (first.xr + second.xr))
			cout << "Circle 1 & Circle 2 collide!!\n";
		break;
		

	default:
		cout << "올바르지 않은 입력입니다";
	}
}