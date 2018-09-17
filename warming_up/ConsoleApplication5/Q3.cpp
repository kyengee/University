


#include <iostream>

using namespace std;


class dot {
public:
	int x;
	int y;
	dot() {
		x = 0;
		y = 0;
	}

	void init(int a, int b) {
		x = a;
		y = b;
	}
};



int maze[25][25];

void Line(dot start, dot end) {
	dot send;
	int horizental = end.x - start.x;
	int vertical = end.y - start.y;
	int rands;
	int temp;
	int i,x,y;
	if (horizental > 0)
		x = 1;
	else
		x = -1;
	if (vertical > 0)
		y = 1;
	else
		y = -1;

	

		while ((horizental*x) + (vertical*y) != 0) {
			rands = rand() % 3 + 2;

			if (horizental*x != 0) {
				temp = (horizental*x % rands);
				for (i = 0; i < temp + 1; i++) {
					maze[start.x + (i * x)][start.y] = 0;
				}
				horizental -= (temp * x);
				start.x += (temp * x);
			}
			if (vertical*y != 0) {
				temp = (vertical*y % rands);
				for (i = 0; i < temp + 1; i++) {
					maze[start.x][start.y + (i * y)] = 0;
				}
				vertical -= (temp * y);
				start.y += (temp * y);
			}


		}

	

	
		

}


int main()
{

	dot first;
	dot end;
	char flag;


	while (1) {

		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 25; j++)
				maze[i][j] = 1;
		}

		

		first.init(0, 0);
		end.init(5, 5);
		Line(first, end);

		first.init(5, 5);
		end.init(10, 0);
		Line(first, end);

		first.init(10, 0);
		end.init(15, 5);
		Line(first, end);

		first.init(15, 5);
		end.init(10, 10);
		Line(first, end);

		first.init(10, 10);
		end.init(15, 15);
		Line(first, end);

		first.init(15, 15);
		end.init(20, 10);
		Line(first, end);

		first.init(20, 10);
		end.init(24, 15);
		Line(first, end);

		first.init(24, 15);
		end.init(20, 20);
		Line(first, end);

		first.init(20, 20);
		end.init(24, 24);
		Line(first, end);

		


		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 25; j++)
				cout << maze[i][j];
			cout << "\n";
		}

		cout << "Input :";
		cin >> flag;
		if (flag == 'q')
			break;
	}
	

}



	