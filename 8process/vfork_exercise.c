#include <apue.h>

static void f1();
static void f2();
/***********
func：测试在函数中调用子进程并返回，看栈地址空间受到的影响

***********/

int main(void){
	
	f1();//创建了一个子进程而且没有exit
	f2();//为一个数据赋值
	_exit(0);
}

static void f1(void){
	pid_t pid;
	if((pid=vfork())<0)//创建了子进程但是没有exit
		err_sys("vfork error!\n");
	if(pid == 0)//加上exit后就不会有段错误了
		_exit(0);
}

static void f2(){
	char buf[1000];
	int i;
	for (i = 0; i < sizeof(buf); i++)//给一个数组赋值
	{
		buf[i] = 0;
	}
}

/***********
结果是段错误了！！！

************/