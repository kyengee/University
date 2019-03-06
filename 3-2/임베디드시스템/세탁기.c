/* Memory Mapped FND Control Example
FILE : mmap_fnd.c
AUTH : Huins, Inc
HOME : www.huins.com
DATE : 2011.10.17 23:40
MENT : Patch mmap error */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <signal.h>

#define MAP_SIZE 0x1000			/* Mapping Size */
#define PHY_ADDR 0x07000000		/* physical address */
#define FND_OFFSET 0x4            /* Fnd Offset from base address (PHY_ADDR)*/
#define LED_OFFSET 0x16              /* LED Offset from base address (PHY_ADDR)*/
#define LCD_OFFSET 0x100              /* LCD Offset from base address (PHY_ADDR)*/
#define DOTMATRIX_OFFSET 0x210              /* DotMatrix Offset from base address (PHY_ADDR)*/
#define BUZZER_OFFSET 0x20              /* Buzzer Offset from base address (PHY_ADDR)*/
#define PUSHSWITCH_OFFSET 0x17              /* PushSwitch Offset from base address (PHY_ADDR)*/
#define STEPMOTOR_OFFSET 0x0c             /* StepMotor Offset from base address (PHY_ADDR)*/

//DOTMATRIX 의 각 라인 접근을 쉽게하기 위해서 미리 정의해놓는다. 
#define line1 0x210
#define line2 0x211
#define line3 0x212
#define line4 0x213
#define line5 0x214
#define line6 0x215
#define line7 0x216
#define line8 0x217
#define line9 0x218
#define line10 0x219

//FND의 주소접근을 미리 정의해 놓는다. 
#define FND (*((volatile unsigned int *)(start_addr + FND_OFFSET)))

//물리주소의 시작주소를 넣기위한 변수 
void * start_addr;

//PushSwitch의 입력으로부터 동작모드를 설정하기위한 제어변수. 
unsigned int value = 0;

//LED의 출력을 쉽게 제어하기위해 미리 배열을 만들어 놓는다.
unsigned int led_val[] = { 0x00, 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f, 0xff};

//한 사이클의 주기를 설정(한사이클마다 1초씩 감소한다.)
float term = 1000000;

// Using Exit signal
int quit = 0;
void quit_signal(int sig) {
		quit = 1;
}

//LED의 깜빡임을 제어하기 위한 변수 (세탁모드)
int led_flag = 0;
//LED가 하나씩 켜지는것을 제어하기위한 변수 (헹굼모드)
int led_default = 0;
//DotMatrix가 한줄씩 채워지는것을 제어하기 위한 변수 (세탁모드)
int dot_flag = 0;
//DotMatrix 세줄이 사라졌다 출력하기를 반복하기위한 변수 (헹굼모드)
int dot_default = 0;
//DotMatrix가 한줄씩 사라지는것을  제어하기 위한 변수(탈수모드)
int dot_fin = 0;

//DotMatrix를 초기화 하는 함수 
void clear_dot() {
	*((unsigned char *)start_addr + line1) = 0x00;
	*((unsigned char *)start_addr + line2) = 0x00;
	*((unsigned char *)start_addr + line3) = 0x00;
	*((unsigned char *)start_addr + line4) = 0x00;
	*((unsigned char *)start_addr + line5) = 0x00;
	*((unsigned char *)start_addr + line6) = 0x00;
	*((unsigned char *)start_addr + line7) = 0x00;
	*((unsigned char *)start_addr + line8) = 0x00;
	*((unsigned char *)start_addr + line9) = 0x00;
	*((unsigned char *)start_addr + line10) = 0x00;
	dot_flag = 0;
}

int main (int argc, char *argv[]) {
	int i = 0;
	//LCD에 출력할 문자열을 저장하기 위한 배열 
	char string[17];
	//파일디스크립터를 저장하기 위한 변수
	int fd;
	//남은시간을 저장하기 위한 변수 
	int time;

	/* Mapped Device Open */
	fd = open( "/dev/mem", O_RDWR | O_SYNC );
	if (fd == -1) {
		perror("/dev/mem");
		return -1;
	}

	/* Memory mapping */
	//fd로 지정된 파일(혹은 다른 객체)에서 PHY_ADDR을 시작으로 MAP_SIZE바이트 만큼을 start주소로 대응시키도록 한다.
	//PROT_WRITE|PROT_READ: page는 쓰여지고 읽어질수있다. MAP_SHARED: 대응된 객체를 다른 모든 프로세스와 공유한다. 
	start_addr = mmap((void *)0, MAP_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, fd, PHY_ADDR);
	if (start_addr == NULL) {
		perror("mmap()");
		return -1;
	}
	

	/* Signal Start */
	//인터럽트 시그널이오면 quit_signal() 함수를 호출한다.
	signal(SIGINT, quit_signal );
	printf("\nPress <ctrl+c> to quit.\n\n");

	//LCD 두번째줄을 초기화한다.
	for(i = 0;i < 17;i++)
	*((unsigned char *)start_addr + LCD_OFFSET+i+16) = ' ';

	// Control routine
	while(!quit) {

		//시작 전 모든변수를 초기화한다.
		led_flag = 0;
		led_default = 0;
		dot_flag = 0;
		dot_default = 0;
		dot_fin = 0;

		FND=(unsigned char)0;
		clear_dot();
		*((unsigned char *)start_addr + LED_OFFSET) = (led_val[0]);



		//LCD 첫번째줄에 빨래모드를 선택하라는 문장을 출력한다.
		strcpy(string,"Choice Mod      ");
					for(i = 0;i < sizeof(string);i++)
					*((unsigned char *)start_addr + LCD_OFFSET+i) = string[i];

				
		//LCD 두번째줄에 선택가능한 빨래모드의 갯수를 출력한다.
		strcpy(string,"one two three   ");
					for(i = 0;i < sizeof(string);i++)
					*((unsigned char *)start_addr + LCD_OFFSET+i+16) = string[i];

		//무한루프 시작.
		//0.5초마다 PUSHSWITCH 입력이 왔는지 확인하고 입력이 오면 탈출.
		for(;;){
		if(*((unsigned char *)start_addr + PUSHSWITCH_OFFSET+6) == 1){
			value = 1;
			clear_dot();
			break;
		}
		else if(*((unsigned char *)start_addr + PUSHSWITCH_OFFSET+7) == 1){
			value = 2;
			clear_dot();
			break;
		}
		else if(*((unsigned char *)start_addr + PUSHSWITCH_OFFSET+8) == 1){
			value = 3;
			clear_dot();
			break;
		}
		usleep(50000);
	}

		//value 값에따른 다른 빨래모드(루프) 실행.
		switch(value){
			case 1:
			//표준 빨래모드
			
			//총 시간을 30초로 설정한다.
			time = 30;
			//LCD두번째줄에 standard모드를 표시한다.
			strcpy(string,"        standard");
					for(i = 0;i < sizeof(string);i++)
					*((unsigned char *)start_addr + LCD_OFFSET+i+16) = string[i];
			//time이 0이 될때까지 루프문을 실행한다.
			for(;time > 0;){
				//FND에 분의10의자리,분의1의자리,초의10의자리,초의1의자리 순으로 출력한다.
				FND=(unsigned char)(time/60/10); FND |= (unsigned char)(time/60%10)<<8;	FND|=(unsigned char)(time%60/10)<<16; FND |= (unsigned char)(time%60%10)<<24;	

				//만약 남은초가 15이상이면 Washing모드를 실행한다.
				if(time%60 > 15){
					//LCD의 첫번째줄에 Washing모드를 출력한다.
					strcpy(string,"Washing Mod      ");
					for(i = 0;i < sizeof(string);i++) {
					*((unsigned char *)start_addr + LCD_OFFSET+i) = string[i];
					}

					//led_flag의 변화에 따라 LED전체를 켰다가, 껏다가를 반복한다.
					if(led_flag == 0){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[0]);
						led_flag = 1;}
						else{
					*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[9]);
					led_flag = 0;}

					//dot_flag의 변화에 따라 dot_matrix의 6번째줄까지 순차적으로 채워지게 한다.
					if(dot_flag == 0){
						*((unsigned char *)start_addr + line10) = 0x7f;
						dot_flag = 1;
					}
					else if(dot_flag == 1){
						*((unsigned char *)start_addr + line9) = 0x7f;
						dot_flag = 2;
					}
					else if(dot_flag == 2){
						*((unsigned char *)start_addr + line8) = 0x7f;
						dot_flag = 3;
					}
					else if(dot_flag == 3){
						*((unsigned char *)start_addr + line7) = 0x7f;
						dot_flag = 4;
					}
					else if(dot_flag == 4){
						*((unsigned char *)start_addr + line6) = 0x7f;
						dot_flag = 5;
					}
					else{
						*((unsigned char *)start_addr + line5) = 0x7f;
						dot_flag = -1;}

					//남은초가 짝수이면 시계반대방향으로 속도 10만큼 회전.
				if(time%60%2 == 0){
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+1) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+2) = 10;
				}
				//남은초가 홀수이면 시계방향으로 속도 10만큼 회전.
				if(time%60%2 == 1){
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+1) = 0;
				}

				}
				//만약 남은초가 15이상이 아니면서 10이상이면 Rinsing모드를 실행한다.
				else if(time%60 > 10){
					//LCD의 첫번째줄에 Rinsing모드를 출력한다.
					strcpy(string,"Rinsing Mod      ");
					for(i = 0;i < sizeof(string);i++)
					*((unsigned char *)start_addr + LCD_OFFSET+i) = string[i];
					
					//led_default의 변화에 따라 순차적으로 하나씩 LED가 점등되는 애니메이션.
					if(led_default == 0){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[1]);
						led_default = 1;}
					else if(led_default == 1){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[2]);
						led_default = 2;}
					else if(led_default == 2){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[3]);
						led_default = 3;}
					else if(led_default == 3){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[4]);
						led_default = 4;}
					else if(led_default == 4){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[5]);
						led_default = 5;}
					else if(led_default == 5){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[6]);
						led_default = 6;}
					else if(led_default == 6){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[7]);
						led_default = 7;}
					else{*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[8]);
						led_default = 0;}

					//dot_default 변화에 따라 dot_matrix의 3줄이 사라졌다 생겼다를 순차적으로 반복한다.
					if(dot_default == 0){
						*((unsigned char *)start_addr + line5) = 0x00;
						dot_default = 1;
					}
					else if(dot_default == 1){
						*((unsigned char *)start_addr + line6) = 0x00;
						dot_default = 2;
					}
					else if(dot_default == 2){
						*((unsigned char *)start_addr + line7) = 0x00;
						dot_default = 3;
					}
					else if(dot_default ==3){
						*((unsigned char *)start_addr + line7) = 0x7f;
						dot_default = 4;
					}
					else if(dot_default ==4){
						*((unsigned char *)start_addr + line6) = 0x7f;
						dot_default = 5;
					}
					else{
						*((unsigned char *)start_addr + line5) = 0x7f;
						dot_default = 0;
					}
					//모터의 속도를 50으로 시계반대방향으로 회전.
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+1) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+2) = 50;
			}
				//만약 남은초가 15이상이아니고 10초이상이 아니라면 SpinDry 모드를 실행한다.
				else{
					//LCD 첫번째줄에 Spin Drying 출력.
					strcpy(string,"Spin Drying      ");

					for(i = 0;i < sizeof(string);i++)
					*((unsigned char *)start_addr + LCD_OFFSET+i) = string[i];

					//LED는 항상 켜지도록 출력.
					*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[0]);

					//dot_fin 변수에 따라 dot matrix 를 6줄부터 한줄씩 감소하도록 한다.
					
					
					if(dot_fin == 0){
						*((unsigned char *)start_addr + line5) = 0x00;
						dot_fin = 1;
					}
					else if(dot_fin == 1){
						*((unsigned char *)start_addr + line6) = 0x00;
						dot_fin = 2;
					}
					else if(dot_fin == 2){
						*((unsigned char *)start_addr + line7) = 0x00;
						dot_fin = 3;
					}
					else if(dot_fin == 3){
						*((unsigned char *)start_addr + line8) = 0x00;
						dot_fin = 4;
					}
					else if(dot_fin == 4){
						*((unsigned char *)start_addr + line9) = 0x00;
						dot_fin = 5;
					}
					else{
						*((unsigned char *)start_addr + line10) = 0x00;
						
					}
					//모터를 시계반대방향으로 속도 5만큼 회전
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+1) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+2) = 5;
			}
				//time 을 1씩 감소
				time--;
				//term 만큼 딜레이를 준다.
				usleep(term);
				//만약 취소버튼이 눌렸다면 dot_matrix,motor를 초기화하고 무한루프를 빠져나간다.
				if(*((unsigned char *)start_addr + PUSHSWITCH_OFFSET+2) == 1){
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 0;

					clear_dot();
					break;
				}
				//모터를 끈다.
				*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 0;
			}
				break;
			

			case 2:
			//이불 빨래모드 

			//총 시간을 40초로 설정한다.
			time = 40;
			//LCD두번째줄에 blanket모드를 표시한다.
			strcpy(string,"         blanket");
					for(i = 0;i < sizeof(string);i++)
					*((unsigned char *)start_addr + LCD_OFFSET+i+16) = string[i];
			//time이 0이 될때까지 루프문을 실행한다.
			for(;time > 0;){
				//FND에 분의10의자리,분의1의자리,초의10의자리,초의1의자리 순으로 출력한다.
				FND=(unsigned char)(time/60/10); FND |= (unsigned char)(time/60%10)<<8;	FND|=(unsigned char)(time%60/10)<<16; FND |= (unsigned char)(time%60%10)<<24;	
				//만약 남은초가 20이상이면 Washing모드를 실행한다.
				if(time%60 > 20){
					//LCD의 첫번째줄에 Washing모드를 출력한다.
					strcpy(string,"Washing Mod      ");
					for(i = 0;i < sizeof(string);i++)
					*((unsigned char *)start_addr + LCD_OFFSET+i) = string[i];

					//led_flag의 변화에 따라 LED전체를 켰다가, 껏다가를 반복한다.
					if(led_flag == 0){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[0]);
						led_flag = 1;}
						else{
					*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[9]);
					led_flag = 0;}

					//dot_flag의 변화에 따라 dot_matrix의 8번째줄까지 순차적으로 채워지게 한다.
					if(dot_flag == 0){
						*((unsigned char *)start_addr + line10) = 0x7f;
						dot_flag = 1;
					}
					else if(dot_flag == 1){
						*((unsigned char *)start_addr + line9) = 0x7f;
						dot_flag = 2;
					}
					else if(dot_flag == 2){
						*((unsigned char *)start_addr + line8) = 0x7f;
						dot_flag = 3;
					}
					else if(dot_flag == 3){
						*((unsigned char *)start_addr + line7) = 0x7f;
						dot_flag = 4;
					}
					else if(dot_flag == 4){
						*((unsigned char *)start_addr + line6) = 0x7f;
						dot_flag = 5;
					}
					else if(dot_flag == 5){
						*((unsigned char *)start_addr + line5) = 0x7f;
						dot_flag = 6;
					}
					else if(dot_flag == 6){
						*((unsigned char *)start_addr + line4) = 0x7f;
						dot_flag = 7;
					}
					else{
						*((unsigned char *)start_addr + line3) = 0x7f;
						dot_flag = -1;}

					//남은초가 짝수이면 시계반대방향으로 속도 10만큼 회전.
				if(time%60%2 == 0){
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+1) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+2) = 10;
				}
				//남은초가 홀수이면 시계방향으로 속도 10만큼 회전.
				if(time%60%2 == 1){
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 0;
				}


				}
				//만약 남은초가 20이상이 아니면서 10이상이면 Rinsing모드를 실행한다.
				else if(time%60 > 10){
					//LCD
					strcpy(string,"Rinsing Mod      ");
					for(i = 0;i < sizeof(string);i++)
					*((unsigned char *)start_addr + LCD_OFFSET+i) = string[i];

					//led_default의 변화에 따라 순차적으로 하나씩 LED가 점등되는 애니메이션.
					if(led_default == 0){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[1]);
						led_default = 1;}
					else if(led_default == 1){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[2]);
						led_default = 2;}
					else if(led_default == 2){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[3]);
						led_default = 3;}
					else if(led_default == 3){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[4]);
						led_default = 4;}
					else if(led_default == 4){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[5]);
						led_default = 5;}
					else if(led_default == 5){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[6]);
						led_default = 6;}
					else if(led_default == 6){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[7]);
						led_default = 7;}
					else{*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[8]);
						led_default = 0;}

					//dot_default 변화에 따라 dot_matrix의 3줄이 사라졌다 생겼다를 순차적으로 반복한다.
					if(dot_default == 0){
						*((unsigned char *)start_addr + line3) = 0x00;
						dot_default = 1;
					}
					else if(dot_default == 1){
						*((unsigned char *)start_addr + line4) = 0x00;
						dot_default = 2;
					}
					else if(dot_default == 2){
						*((unsigned char *)start_addr + line5) = 0x00;
						dot_default = 3;
					}
					else if(dot_default ==3){
						*((unsigned char *)start_addr + line5) = 0x7f;
						dot_default = 4;
					}
					else if(dot_default ==4){
						*((unsigned char *)start_addr + line4) = 0x7f;
						dot_default = 5;
					}
					else{
						*((unsigned char *)start_addr + line3) = 0x7f;
						dot_default = 0;
					}

					//모터의 속도를 50으로 시계반대방향으로 회전.
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+1) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+2) = 50;
			}
				else{
					//만약 남은초가 20이상이아니고 10초이상이 아니라면 SpinDry 모드를 실행한다.
					strcpy(string,"Spin Drying      ");
					for(i = 0;i < sizeof(string);i++)
					*((unsigned char *)start_addr + LCD_OFFSET+i) = string[i];

					//LED는 항상 켜지도록 출력.
					*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[0]);

					//dot_fin 변수에 따라 dot matrix 를 8줄부터 한줄씩 감소하도록 한다.
					
					if(dot_fin == 0){
						*((unsigned char *)start_addr + line3) = 0x00;
						dot_fin = 1;
					}
					else if(dot_fin == 1){
						*((unsigned char *)start_addr + line4) = 0x00;
						dot_fin = 2;
					}
					else if(dot_fin == 2){
						*((unsigned char *)start_addr + line5) = 0x00;
						dot_fin = 3;
					}
					else if(dot_fin == 3){
						*((unsigned char *)start_addr + line6) = 0x00;
						dot_fin = 4;
					}
					else if(dot_fin == 4){
						*((unsigned char *)start_addr + line7) = 0x00;
						dot_fin = 5;
					}
					else if(dot_fin == 5) {
						*((unsigned char *)start_addr + line8) = 0x00;
						dot_fin = 6;
					}
					else if(dot_fin ==6) {
						*((unsigned char *)start_addr + line9) = 0x00;
						dot_fin = 7;
					}
					else{
						*((unsigned char *)start_addr + line10) = 0x00;
						
					}
					//모터를 시계반대방향으로 속도 5만큼 회전
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+1) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+2) = 5;
			}
			//time 을 1씩 감소
				time--;
				//term 만큼 딜레이를 준다.
				usleep(term);
				//만약 취소버튼이 눌렸다면 dot_matrix,motor를 초기화하고 무한루프를 빠져나간다.
				if(*((unsigned char *)start_addr + PUSHSWITCH_OFFSET+2) == 1){
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 0;

					clear_dot();
					break;
				}
				//모터를 끈다.
				*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 0;
			}
				break;


			//소량 빨래모드
			case 3:
			//총 시간을 15초로 설정한다.
			time = 15;
			//LCD두번째줄에 handful모드를 표시한다.
			strcpy(string,"         handful");
					for(i = 0;i < sizeof(string);i++)
					*((unsigned char *)start_addr + LCD_OFFSET+i+16) = string[i];
			//time이 0이 될때까지 루프문을 실행한다.
			for(;time > 0;){
				//FND에 분의10의자리,분의1의자리,초의10의자리,초의1의자리 순으로 출력한다.
				FND=(unsigned char)(time/60/10); FND |= (unsigned char)(time/60%10)<<8;	FND|=(unsigned char)(time%60/10)<<16; FND |= (unsigned char)(time%60%10)<<24;	
				//만약 남은초가 10이상이면 Washing모드를 실행한다.
				if(time%60 > 10){
					//LCD의 첫번째줄에 Washing모드를 출력한다.
					strcpy(string,"Washing Mod      ");
					for(i = 0;i < sizeof(string);i++)
					*((unsigned char *)start_addr + LCD_OFFSET+i) = string[i];

					//led_flag의 변화에 따라 LED전체를 켰다가, 껏다가를 반복한다.
					if(led_flag == 0){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[0]);
						led_flag = 1;}
						else{
					*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[9]);
					led_flag = 0;}

					//dot_flag의 변화에 따라 dot_matrix의 3번째줄까지 순차적으로 채워지게 한다.
					if(dot_flag == 0){
						*((unsigned char *)start_addr + line10) = 0x7f;
						dot_flag = 1;
					}
					else if(dot_flag == 1){
						*((unsigned char *)start_addr + line9) = 0x7f;
						dot_flag = 2;
					}
					else{
						*((unsigned char *)start_addr + line8) = 0x7f;
						dot_flag = -1;
					}

					//남은초가 짝수이면 시계반대방향으로 속도 10만큼 회전.
				if(time%60%2 == 0){
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+1) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+2) = 10;
				}
				//남은초가 홀수이면 시계방향으로 속도 10만큼 회전.
				if(time%60%2 == 1){
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 0;
				}


				}
				//만약 남은초가 10이상이 아니면서 5이상이면 Rinsing모드를 실행한다.
				else if(time%60 > 5){
					//LCD의 첫번째줄에 Rinsing모드를 출력한다.
					strcpy(string,"Rinsing Mod      ");
					for(i = 0;i < sizeof(string);i++)
					*((unsigned char *)start_addr + LCD_OFFSET+i) = string[i];

					//led_default의 변화에 따라 순차적으로 하나씩 LED가 점등되는 애니메이션.
					if(led_default == 0){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[1]);
						led_default = 1;}
					else if(led_default == 1){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[2]);
						led_default = 2;}
					else if(led_default == 2){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[3]);
						led_default = 3;}
					else if(led_default == 3){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[4]);
						led_default = 4;}
					else if(led_default == 4){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[5]);
						led_default = 5;}
					else if(led_default == 5){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[6]);
						led_default = 6;}
					else if(led_default == 6){*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[7]);
						led_default = 7;}
					else{*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[8]);
						led_default = 0;}

					//dot_default 변화에 따라 dot_matrix의 3줄이 사라졌다 생겼다를 순차적으로 반복한다.
					if(dot_default == 0){
						*((unsigned char *)start_addr + line8) = 0x00;
						dot_default = 1;
					}
					else if(dot_default == 1){
						*((unsigned char *)start_addr + line9) = 0x00;
						dot_default = 2;
					}
					else if(dot_default == 2){
						*((unsigned char *)start_addr + line10) = 0x00;
						dot_default = 3;
					}
					else if(dot_default ==3){
						*((unsigned char *)start_addr + line10) = 0x7f;
						dot_default = 4;
					}
					else if(dot_default ==4){
						*((unsigned char *)start_addr + line9) = 0x7f;
						dot_default = 5;
					}
					else{
						*((unsigned char *)start_addr + line8) = 0x7f;
						dot_default = 0;
					}
					//모터의 속도를 50으로 시계반대방향으로 회전.
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+1) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+2) = 50;
			}
			//만약 남은초가 15이상이아니고 10초이상이 아니라면 SpinDry 모드를 실행한다.
				else{
					//LCD 첫번째줄에 Spin Drying 출력.
					strcpy(string,"Spin Drying      ");
					for(i = 0;i < sizeof(string);i++)
					*((unsigned char *)start_addr + LCD_OFFSET+i) = string[i];

					//LED는 항상 켜지도록 출력.
					*((unsigned char *)start_addr + LED_OFFSET) = ~(led_val[0]);

					//dot_fin 변수에 따라 dot matrix 를 3줄부터 한줄씩 감소하도록 한다.
					if(dot_fin == 0){
						*((unsigned char *)start_addr + line8) = 0x00;
						dot_fin = 1;
					}
					else if(dot_fin == 1){
						*((unsigned char *)start_addr + line9) = 0x00;
						dot_fin = 2;
					}
					else{
						*((unsigned char *)start_addr + line10) = 0x00;
						
					}
					//모터를 시계반대방향으로 속도 5만큼 회전
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+1) = 1;
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET+2) = 5;
			}
			//time 을 1씩 감소
				time--;
				//term 만큼 딜레이를 준다.
				usleep(term);
				//만약 취소버튼이 눌렸다면 dot_matrix,motor를 초기화하고 무한루프를 빠져나간다.
				if(*((unsigned char *)start_addr + PUSHSWITCH_OFFSET+2) == 1){
					*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 0;

					clear_dot();
					break;
				}
				//모터를 끈다.
				*((unsigned char *)start_addr + STEPMOTOR_OFFSET) = 0;
			}
				break;
		}

	}
	
	//모든 동작이 종료됐을때 LED와 FND를 초기화한다.
	*((unsigned char *)start_addr + FND_OFFSET) = 0xff;
	*((unsigned char *)start_addr + LED_OFFSET) = 0x00;



	/* Memory ummapping (마지막 메모리 반환)*/
	if (munmap(start_addr, MAP_SIZE) == -1) {
		perror("munmap()");
		return -1;
	}
//오픈한 파일 닫기 
	close(fd);
	return 0;
} 
