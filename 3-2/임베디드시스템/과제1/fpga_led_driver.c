/* FPGA LED Ioremap Control
FILE : fpga_led_driver.c 
AUTH : largest@huins.com */
#include <linux/module.h> //모듈에 필요한 헤더 파일
#include <linux/fs.h> //파일 연산 구조체 의 원형 등이 들어가있는 헤더 파일
#include <linux/init.h> //module_init(), exit() 매크로 정의
#include <linux/slab.h>
#include <mach/gpio.h> 
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
 
#include <asm/io.h> //ASM = Android SDK Manager
#include <asm/uaccess.h>
#include <linux/kernel.h> //커널에서 수행될 때 필요한 헤더 파일
#include <linux/ioport.h>
//#include <linux/module.h> 헤더 파일 중복
//#include <linux/fs.h> 헤더 파일 중복
//#include <linux/init.h> 헤더 파일 중복
#include <linux/version.h> 
 
 
#define IOM_LED_MAJOR 260		//ioboard led device의 major 번호 260
#define IOM_LED_NAME "fpga_led"		//ioboard led device의 이름 fpga_led"
 
// SROM Bank3 0x0700_0000
#define IOM_LED_ADDRESS 0x07000016 //ioboard led device의 물리적 주소
//#define IOM_DEMO_ADDRESS 0x04000300 
#define IOM_DEMO_ADDRESS 0x07000300 //사용자 모드를 소프트웨어로 ON/OFF 제어하기 위해서 사용됨
 
#define UON 0x00 // IOM // UON이면 DEMO MODE로, FPGA 단독으로 동작함
#define UOFF 0x01 // IOM //UOFF이면 5250 SROM interface에 의해 동작함
 
 
//사용되는 전역변수 정의
static int ledport_usage = 0; //장치가 사용중인지 아닌지를 알려주고 사용중이 아니라면 0, 사용중이면 1을 리턴
static unsigned char *iom_fpga_led_addr; //define했던 led device의 물리적 주소
static unsigned char *iom_demo_addr;
 
//사용되는 함수 정의
ssize_t iom_led_write(struct file *inode, const char *gdata, size_t length, loff_t *off_what); //device에서 쓰기위해 필요한 함수
ssize_t iom_led_read(struct file *inode, char *gdata, size_t length, loff_t *off_what); //device에서 읽기 위해 필요한 함수
int iom_led_open(struct inode *minode, struct file *mfile); //device에서 open하기 위한 함수
int iom_led_release(struct inode *minode, struct file *mfile); //device에서 release하기 위한 함수   
 
/*파일 연산 구조체로 문자 디바이스 드라이버와 응용 프로그램을 연결시켜줌
응용 프로그램이 저수준 파일 입출력 함수를 사용하여 디바이스 파일에 접근하면
커널은 등록된 문자 디바이스 드라이버의 오퍼레이션 구조체 정보를 참고하여
디바이스 파일에 접근하여 대응하는 함수를 호출*/
struct file_operations iom_led_fops = 
{
	.owner		=	THIS_MODULE, //어떤 모듈로 올라간 device driver와 연관을 가지는지를 나타내는 포인터
	.open		=	iom_led_open, //device를 open
	.write		=	iom_led_write,	//device에서 데이터를 씀
	.read		=	iom_led_read,	//device에서 데이터를 읽음
	.release	=	iom_led_release, //device를 해제 (open의 반대)
};
 
/*응용 프로그램에서 장치 파일을 int open system call을 통해서 열 때, 커널이 호출하는 함수로 장치 파일을 열 때 호출됨*/
int iom_led_open(struct inode *minode, struct file *mfile)  
{	
	if(ledport_usage != 0) return -EBUSY; //장치가 사용중이라면 -EBUSY를 리턴
 
	ledport_usage = 1; //장치를 open한 뒤에 1로 저장해서 사용중이라는 것을 알려줌
 
	return 0;
}
 
/*응용 프로그램에서 장치 파일을 int close system call을 통해서 닫을 때, 커널이 호출하는 함수로 장치 파일을 닫을 떄 호출됨*/
int iom_led_release(struct inode *minode, struct file *mfile) 
{
	ledport_usage = 0; //장치를 닫기 때문에 값을 0으로 저장
 
	return 0;
}

// when write to led device  ,call this function
ssize_t iom_led_write(struct file *inode, const char *gdata, size_t length, loff_t *off_what) 
{
	unsigned char value;//value를 선언한다.
	const char *tmp = gdata;//gdata를 tmp에 복사한다.

	if (copy_from_user(&value, tmp, 1))//tmp가 가리키는 주소의 사용자 메모리 블록 데이터를 
		//value가 가리키는 커널 메모리 블록 데이터에 바이트 크기단위인 1만큼 써넣는다.
		//정상수행 = 0, 그렇지않다면 0의외의 값을 반환한다.
		return -EFAULT;//EFAULT는 14의 값이다. -14를 리턴한다. bad address란 뜻이다.

	printk("LED Value %d in kernel", value);
//커널 메세지 버퍼로 문자열을 출력한다.
	outb(value,(unsigned int)iom_fpga_led_addr);	    
//원하는 포트에 한 바이트(8bit)를 쓰는 함수 outb(value,port)
	
	
	return length;
}

// when read to led device  ,call this function
ssize_t iom_led_read(struct file *inode, char *gdata, size_t length, loff_t *off_what) 
{
	unsigned char value;//value를 선언한다.
	char *tmp = gdata;//gdata를 tmp에 복사한다.

	value = inb((unsigned int)iom_fpga_led_addr);	
	//원하는 포트에서 한 바이트(8bit)를 읽는 함수 inb(port)    

	if (copy_to_user(tmp, &value, 1))//value가 가리키는 주소의 커널 메모리 블록 데이터를
		//tmp가 가리키는 사용자 메모리 블록 데이터에 바이트 크기단위인 1만큼 써넣는다.
		//정상수행 = 0, 그렇지않다면 0의외의 값을 반환한다.
		return -EFAULT;//EFAULT는 14의 값이다. -14를 리턴한다. bad address란 뜻이다.

	return length;
}

int __init iom_led_init(void)
{
	int result;

	result = register_chrdev(IOM_LED_MAJOR, IOM_LED_NAME, &iom_led_fops);
	//모듈이 적재될때 실행되는 init_module()함수 내부에 있어서 커널이 부팅되거나, 모듈로 적재될때
	//커널 내부에 있는 배열 구조체인 chrdev[]에 등록되도록 하는것이다.
	//IOM_LED_MAJOR = 배열 chrdev[]의 순서를 결정하는 major번호.
	//IOM_LED_NAME = 등록될 문자장치의 이름, iom_led_fops = 사용되어질 파일 오퍼레이션을 위한
	//함수포인터. 
	if(result < 0) {
		printk(KERN_WARNING"Can't get any major\n");
		//로그레벨을 KERN_WARNING(경고정보)로 하여 출력한다.
		return result;
	}

	iom_fpga_led_addr = ioremap(IOM_LED_ADDRESS, 0x1);//0x1은 byte, PAGE_SIZE의 배수여야 한다.
	//ioremap() IO주소공간을 가상 주소 공간에 할당한다.
	//IOM_LED_ADDRESS(물리주소)를 가상 주소공간에 할당한다.
	//MMU가 활성화되어 동작하는 커널 모드에서는 물리주소에 접근하면 페이지폴트가 발생하여 
	//처리되지 않는다. 따라서, 디바이스드라이버는 하드웨어를 제어하기위해 물리주소를 
	//가상주소로 매핑해야 한다. 
	iom_demo_addr = ioremap(IOM_DEMO_ADDRESS, 0x1);
	//IOM_DEMO_ADDRESS(물리주소)를 가상 주소공간에 할당한다.

	outb(UON,(unsigned int)iom_demo_addr);	 
	//원하는 포트에 값을 보내는 함수 outb(value,port) 
	//UON 값을 iom_demo_addr 에 보낸다.
	printk("init module, %s major number : %d\n", IOM_LED_NAME, IOM_LED_MAJOR);
	//커널 메세지 버퍼로 문자열을 출력한다.

	return 0;
}

void __exit iom_led_exit(void) 
{
	iounmap(iom_fpga_led_addr);
	//해당 가상주소를 해제한다.
	iounmap(iom_demo_addr);
	//해당 가상주소를 해제한다.
	unregister_chrdev(IOM_LED_MAJOR, IOM_LED_NAME);
	//주번호와 디바이스 이름이 같은 등록된 디바이스를 제거한다.
}

module_init(iom_led_init);
//module_init매크로는 커널에게 모듈이 로딩되었을때 호출되어야 하는 함수를 알려주는 역할을 한다.
module_exit(iom_led_exit);
//module_exit는 드라이버가 모듈 일 때 rmmod와 함께 사용할 때 cleanup_module을 사용하여 
//드라이버 정리 코드를 래핑한다(module_exit가 cleanup_module에 매핑되어있다). 
//드라이버가 정적으로 커널에 컴파일되면 module_exit는 아무 효과가 없다. 
//모듈 당 하나만있을 수 있다.
MODULE_LICENSE("GPL");
//MODULE_LICENSE매크로는 커널에게 모듈이 어떤 라이센스 하에서 커널을 이용하게 되는지를 알려주는 역할
//"GPL"은 GNU Public License v2또는 이상을 의미한다.
//GPL라이센스가 적용된 코드를 수정한 경우 수정된 소스코드를 공개해야 한다.
MODULE_AUTHOR("Huins");
//모듈의 원작자의 이름
