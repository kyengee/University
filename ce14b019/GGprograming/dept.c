#include <stdio.h>

typedef struct stu_tag{
	int id;
	char name[32];
	int kor, prog;
	}student;
	
typedef struct dept_tag{
	student *freshmen;
	int nfreshmen;

	student *junior;
	int njunior;
	}dept;

dept *get_data();
void display_data(dept *);

int main(){
	dept *test;
	test = get_data();
	display_data(test);

	return 0;
}


dept *get_data(){

	dept *temp = NULL;
	student *fresh = NULL;
	student *junior = NULL;

	
	temp = malloc(sizeof(dept));
	fresh = malloc(sizeof(student)*2);
	junior = malloc(sizeof(student)*2);

	fresh[0].id = 121212;
	strcpy(fresh[0].name,"사람1");
	fresh[0].kor = 1;
	fresh[0].prog = 3;

	fresh[1].id = 343434;
	strcpy(fresh[1].name,"사람2");
	fresh[1].kor = 2;
	fresh[1].prog = 4;

	junior[0].id = 555555;
	strcpy(junior[0].name,"주니어1");
	junior[0].kor = 1;
	junior[0].prog = 3;

	junior[1].id = 77777;
	strcpy(junior[1].name,"주니어2");
	junior[1].kor = 5;
	junior[1].prog = 4;

	temp[0].freshmen = fresh;
	temp[0].junior = junior;
	temp[0].nfreshmen = 2;
	temp[0].njunior = 2;

	return temp;
}
	
void display_data(dept * cDept){

	int i = 0;
	
	printf("freshmen %d명 을 출력하겠습니다.\n",cDept[0].nfreshmen);
	
	for(i=0;i<cDept[0].nfreshmen;i++){
		printf("%d 번째 학생\n",i);
		printf("학번 : %d\n",cDept[0].freshmen[i].id);	
		printf("이름 : %s\n" , cDept[0].freshmen[i].name);
		printf("국어 : %d , 프로그래밍 : %d\n",cDept[0].freshmen[i].kor,cDept[0].freshmen[i].prog);
		}

	printf("junior %d명 을 출력하겠습니다.\n", cDept[0].njunior);
	
	for(i=0; i < cDept[0].njunior;i++){
		printf("%d 번째 학생\n",i);
		printf("학번 : %d\n", cDept[0].junior[i].id);
		printf("이름 : %s\n", cDept[0].junior[i].name);
		printf("국어 : %d, 프로그래밍 : %d\n", cDept[0].junior[i].kor, cDept[0].junior[i].prog);
		}

}
		
	
