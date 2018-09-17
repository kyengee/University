


#include <iostream>

using namespace std;

class dot {
public:
	int x;
	int y;
	int z;

};



int main() {
	char var;
	dot List[10];
	int first = 0;
	int last = -1;
	dot temp;

	while (1) {

		cout << "Input :";

		cin >> var;

		switch (var)
		{
		case '+':
			last++;
			if (last == 10)
				last = 9;
			cin >> temp.x >> temp.y >> temp.z;
			List[last].x = temp.x;
			List[last].y = temp.y;
			List[last].z = temp.z;
			break;

		case '-':
			cout << List[last].x << " " << List[last].y << " " << List[last].z << "\n";
			last--;
			break;

		case 'e':
			cin >> temp.x;
			cin >> temp.y;
			cin >> temp.z;
			last++;
			for (int i = 0; i < (last - first); i++) {
				List[last - i] = List[last - i - 1];
			}
			List[first].x = temp.x;
			List[first].y = temp.y;
			List[first].z = temp.z;
			break;

		case 'd':
			cout << List[first].x << " " << List[first].y << " " << List[first].z<<"\n";
			first++;
			break;

		case 'l':
			cout << "리스트의 길이 =" << (last - first +1 > 0? last - first+1 : 0) << '\n';
			break;

		case 'c':
			first = 0;
			last = -1;
			break;

		case 'm':
			if (last - first + 1 == 0) {
				cout << "비어있습니다\n";
				break;
			}
			temp.x = 0;
			temp.y = 0;
			temp.z = 0;
			for (int i = first; i < last+1; i++) {
				if (pow(temp.x, 2) + pow(temp.y, 2) + pow(temp.z, 2) < pow(List[i].x, 2) + pow(List[i].y, 2) + pow(List[i].z, 2)) {
					temp.x = List[i].x;
					temp.y = List[i].y;
					temp.z = List[i].z;
				}
			}
			cout << "가장 먼거리에 있는 좌표값 =" << temp.x << " " << temp.y << " " << temp.z << " \n";
			break;

		case 'n':
			if (last - first + 1 == 0) {
				cout << "비어있습니다\n";
				break;
			}
			temp.x = List[first].x;
			temp.y = List[first].y;
			temp.z = List[first].z;
			for (int i = first; i < last+1; i++) {
				if (pow(temp.x, 2) + pow(temp.y, 2) + pow(temp.z, 2) > pow(List[i].x, 2) + pow(List[i].y, 2) + pow(List[i].z, 2)) {
					temp.x = List[i].x;
					temp.y = List[i].y;
					temp.z = List[i].z;
				}
			}
			cout << "가장 가까운 거리에 있는 좌표값 =" << temp.x << " " << temp.y << " " << temp.z << " \n";
			break;

		case 'q':
			var = 'q';
			break;

		default:
			cout << "올바른 값을 입력하여주세요";
			break;
		}

		if (var == 'q')
			break;

		for (int i = 9; i > -1; i--) {

			if(i<first | i>last)
				cout << '(' << i << ')' << " |       |\n";
			else
				cout << '(' << i << ')' << " | "<<List[i].x<<" "<< List[i].y<<" "<< List[i].z<<" |\n";

			
				
			}
		}
	return 0;
	}

	