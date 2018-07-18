#include "apue.h"

static void charatatime(char *);

/**********
func:解决父子进程竞争问题
	父子进程在打印字符串这里存在竞争
	每个字符的打印都要调用write函数，所以一个时间片内，可能无法打印完所有的字符
	那么这个程序会在父子进程之间不停地切换
add by jingln
**********/

int main(void){
	pid_t pid;

	TELL_WAIT();//增加wait，防止竞争

	if((pid=fork())<0)
		err_sys("fork error!\n");
	else if(pid == 0)//子进程
	{
		WAIT_PARENT();//增加wait，防止竞争
		charatatime("outputtttttttttttttff from child!\n");
	}
	else{

		charatatime("outputtttttttttttttff from parent!\n");
		TELL_CHILD(pid);//增加wait，防止竞争
	}
	exit(0);
}

static void charatatime(char *str)//打印字符串
{
	char *ptr;
	int c;

	setbuf(stdout, NULL);//将标准输出设置成不带缓冲，每个字符的输出都要调用一次write
	for(ptr = str;(c=*ptr++)!=0;)
		putc(c,stdout);
}

/********
可见，输出结果是乱七八糟的
# gcc -o process_compete process_compete.c 
# ./process_compete 
ououtputttttttttttttt tfpruotmt tcthtitltdt!t
ttttt from parent!

但是再运行一次就不会了，这是为什么，难道还是有输出缓冲？
# ./process_compete 
outputttttttttttttt from parent!
outputttttttttttttt from child!
********/