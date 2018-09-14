#include <iostream>

using namespace std;

void init(char values[][30]) {
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 30; j++)
			values[i][j] = '.';
}

class dot {
public:
	int x;
	int y;
};

void Draw_(dot, dot);

int main() {
	int coord;
	dot dot1;
	dot dot2;
	char count;

	while (1) {
		dot1.x = 0;
		dot1.y = 0;
		dot2.x = 0;
		dot2.y = 0;

		Draw_(dot1, dot2);
		count = 'z';
		cout << "Input coord value: ";
		cin >> coord >> dot1.x >> dot1.y >> dot2.x >> dot2.y;

		Draw_(dot1,dot2);


		while (1) {

			cout << "input order: ";
			cin >> count;


			switch (count)
			{
			case 'x':
				if (dot2.x < 29) {
					dot1.x += 1;
					dot2.x += 1;
				}
				else
					cout << "¹üÀ§¸¦ ¹þ¾î³µ½À´Ï´Ù.\n";
				break;

			case 'X':
				if (dot1.x >= 0) {
					dot1.x -= 1;
					dot2.x -= 1;
				}
				else
					cout << "¹üÀ§¸¦ ¹þ¾î³µ½À´Ï´Ù.\n";
				break;

			case 'y':
				if (dot2.y < 29) {
					dot1.y += 1;
					dot2.y += 1;
				}
				else
					cout << "¹üÀ§¸¦ ¹þ¾î³µ½À´Ï´Ù.\n";
				break;

			case 'Y':
				if (dot1.y > 0) {
					dot1.y -= 1;
					dot2.y -= 1;
				}
				else
					cout << "¹üÀ§¸¦ ¹þ¾î³µ½À´Ï´Ù.\n";
				break;

			case 's':
				if (dot2.x < 29 && dot2.y < 29) {
					dot2.x += 1;
					dot2.y += 1;
				}
				else
					cout << "¹üÀ§¸¦ ¹þ¾î³µ½À´Ï´Ù.\n";
				break;

			case 'S':
				if (dot2.x - dot1.x > 1 && dot2.x - dot1.y > 1) {
					dot2.x -= 1;
					dot2.y -= 1;
				}
				else
					cout << "¹üÀ§¸¦ ¹þ¾î³µ½À´Ï´Ù.\n";
				break;

			case 'I':
				if (dot2.x < 29) {
					dot2.x += 1;
				}
				else
					cout << "¹üÀ§¸¦ ¹þ¾î³µ½À´Ï´Ù.\n";
				break;

			case 'j':
				if (dot2.x - dot1.x > 1) {
					dot2.x -= 1;
				}
				else
					cout << "¹üÀ§¸¦ ¹þ¾î³µ½À´Ï´Ù.\n";
				break;

			case 'k':
				if (dot2.y < 29) {
					dot2.y += 1;
				}
				else
					cout << "¹üÀ§¸¦ ¹þ¾î³µ½À´Ï´Ù.\n";
				break;

			case 'l':
				if (dot2.y - dot1.y > 1) {
					dot2.y -= 1;
				}
				else
					cout << "¹üÀ§¸¦ ¹þ¾î³µ½À´Ï´Ù.\n";
				break;

			case 'r':
				break;

			default:
				cout << "¿Ã¹Ù¸£Áö ¾ÊÀº ÀÔ·ÂÀÔ´Ï´Ù.\n";
			}

			Draw_(dot1, dot2);



			if (count == 'r')
				break;

		}


	}

}



void Draw_(dot dot1, dot dot2) {
	char Grap[30][30];

	init(Grap);

	for (int i = dot1.y + 1; i < dot2.y + 1; i++)
		for (int j = dot1.x + 1; j < dot2.x + 1; j++)
			Grap[i][j] = '0';

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++)
			cout << Grap[i][j];
		cout << "\n";
	}
}