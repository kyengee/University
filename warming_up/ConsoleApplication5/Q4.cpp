//검사맡았음


#include <iostream>

using namespace std;

class vec {
public:
	int x;
	int y;
	int z;

	vec() {
		x = 0;
		y = 0;
		z = 0;
	}
};


int main() {

	vec vector1;
	vec vector2;
	vec tempv;
	char temp;
	double root;

	cout << "input vector1:";
	cin >> temp >> vector1.x >> temp >> vector1.y >> temp >> vector1.z >> temp;

	cout << "input vector2:";
	cin >> temp >> vector2.x >> temp >> vector2.y >> temp >> vector2.z >> temp;

	while (1) {

	cout << "\n Input:";

	cin >> temp;


		switch (temp) {
		case '+':
			tempv.x = vector1.x + vector2.x;
			tempv.y = vector1.y + vector2.y;
			tempv.z = vector1.z + vector2.z;
			cout << " +: (" << vector1.x << "," << vector1.y << "," << vector1.z << ") +";
			cout << " (" << vector2.x << "," << vector2.y << "," << vector2.z << ") =";
			cout << " (" << tempv.x << "," << tempv.y << "," << tempv.z << ")\n";
			break;

		case '-':
			tempv.x = vector1.x - vector2.x;
			tempv.y = vector1.y - vector2.y;
			tempv.z = vector1.z - vector2.z;
			cout << " -: (" << vector1.x << "," << vector1.y << "," << vector1.z << ") -";
			cout << " (" << vector2.x << "," << vector2.y << "," << vector2.z << ") =";
			cout << " (" << tempv.x << "," << tempv.y << "," << tempv.z << ")\n";
			break;

		case 'd':
			tempv.x = vector1.x * vector2.x;
			tempv.y = vector1.y * vector2.y;
			tempv.z = vector1.z * vector2.z;
			cout << " d: (" << vector1.x << "," << vector1.y << "," << vector1.z << ") *";
			cout << " (" << vector2.x << "," << vector2.y << "," << vector2.z << ") =";
			cout << tempv.x + tempv.y + tempv.z << "\n";
			break;

		case 'c':
			tempv.x = vector1.y * vector2.z - vector1.z * vector2.y;
			tempv.y = vector1.z * vector2.x - vector1.x * vector2.z;
			tempv.z = vector1.x * vector2.y - vector1.y * vector2.x;
			cout << " c: (" << vector1.x << "," << vector1.y << "," << vector1.z << ") X";
			cout << " (" << vector2.x << "," << vector2.y << "," << vector2.z << ") =";
			cout << " (" << tempv.x << "," << tempv.y << "," << tempv.z << ")\n";
			break;

		case 'l':
			root = pow(vector1.x, 2) + pow(vector1.y, 2) + pow(vector1.z, 2);
			cout << " l: root(" << vector1.x << "," << vector1.y << "," << vector1.z << ") = root(" << root << "), ";
			root = pow(vector2.x, 2) + pow(vector2.y, 2) + pow(vector2.z, 2);
			cout << " root(" << vector2.x << "," << vector2.y << "," << vector2.z << ") = root(" << root << ") \n";
			break;

		default:
			cout << "잘못된 입력입니다\n";
			break;
		}

	}

	return 0;

}



