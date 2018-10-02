//검사 맡았음


#include <iostream>

using namespace std;




void init(int recived[][3]) {
	int i;
	int j;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			recived[i][j] = rand() % 2;
		}
	}
}

int main() {

	int first[3][3];
	int second[3][3];
	int result[4][4] = { 0, };
	char input;
	int mix1, mix2, mix3;
	int add1, add2;
	int min1, min2;
	int h1, h2;
	int resul1, resul2;
	int res;



	while (1) {

		init(first);
		init(second);


		printf("input:");
		scanf(" %c", &input);

		switch (input) {

		case 'M':
		case 'm':
			for (mix1 = 0; mix1 < 3; mix1++) {
				for (mix2 = 0; mix2 < 3; mix2++) {
					for (mix3 = 0; mix3 < 3; mix3++) {
						result[mix1][mix2] += first[mix1][mix3] * second[mix2][mix3];
					}
				}
			}
			break;

		case 'A':
		case 'a':
			for (add1 = 0; add1 < 3; add1++) {
				for (add2 = 0; add2 < 3; add2++) {
					result[add1][add2] = first[add1][add2] + second[add1][add2];
				}
			}
			break;

		case 'D':
		case 'd':
			for (min1 = 0; min1 < 3; min1++) {
				for (min2 = 0; min2 < 3; min2++) {
					result[min1][min2] = first[min1][min2] - second[min1][min2];
				}
			}
			break;

		case 'R':
		case 'r':
			res = (first[0][0]) * (first[1][1]) * (first[2][2]) -
				(first[0][0]) * (first[1][2]) * (first[2][1]) +
				(first[0][1]) * (first[1][2]) * (first[2][0]) -
				(first[0][1]) * (first[1][0]) * (first[2][2]) +
				(first[0][2]) * (first[1][0]) * (first[2][1]) -
				(first[0][2]) * (first[1][1]) * (first[2][0]);
			cout << res << "\n\n";
			result[3][3] = 2;

			for (resul1 = 0; resul1 < 3; resul1++) {
				for (resul2 = 0; resul2 < 3; resul2++) {
					cout<<first[resul1][resul2];
				}
				printf("\n");
			}
			break;




		case 'H':
		case 'h':
			result[3][3] = 1;
			for (h1 = 0; h1 < 3; h1++) {
				for (h2 = 0; h2 < 3; h2++) {
					result[h1][h2] = first[h1][h2];
				}
			}
			break;

		default:
			cout<<"올바르지 않은 입력입니다.\n";
			result[3][3] = 2;



		}

		if (result[3][3] == 1) {

			cout<<"첫번째 행렬\n";
			for (resul1 = 0; resul1 < 3; resul1++) {
				for (resul2 = 0; resul2 < 3; resul2++) {
					cout <<first[resul1][resul2];
				}
				cout << "\n";
			}


			cout << "두번째 행렬\n";
			for (resul1 = 0; resul1 < 3; resul1++) {
				for (resul2 = 0; resul2 < 3; resul2++) {
					cout <<second[resul1][resul2];
				}
				cout << "\n";
			}


			cout << "결과\n";
			for (resul1 = 0; resul1 < 4; resul1++) {
				for (resul2 = 0; resul2 < 4; resul2++) {
					cout << result[resul1][resul2];
				}
				cout << "\n";
			}


		}
		else if (result[3][3] == 0) {

			cout << "첫번째 행렬\n";
			for (resul1 = 0; resul1 < 3; resul1++) {
				for (resul2 = 0; resul2 < 3; resul2++) {
					cout << first[resul1][resul2];
				}
				cout << "\n";
			}


			cout << "두번째 행렬\n";
			for (resul1 = 0; resul1 < 3; resul1++) {
				for (resul2 = 0; resul2 < 3; resul2++) {
					cout << second[resul1][resul2];
				}
				cout << "\n";
			}

			cout << "결과\n";
			for (resul1 = 0; resul1 < 3; resul1++) {
				for (resul2 = 0; resul2 < 3; resul2++) {
					cout << result[resul1][resul2];
				}
				cout << "\n";
			}
		}


		for (resul1 = 0; resul1 < 4; resul1++) {
			for (resul2 = 0; resul2 < 4; resul2++) {
				result[resul1][resul2] = 0;
			}

		}
	}


	return 0;

}


