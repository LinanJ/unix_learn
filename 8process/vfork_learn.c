#include "apue.h"

int globvar = 6;

/***********
func：通过设置全局变量，局部变量，测试使用vfork创建子进程对父进程的影响

***********/

int main(void){
	int var;
	pid_t pid;
	var = 88;
	printf("before vfork\n");

	if((pid=vfork())<0)
		err_sys("vfork error!\n");
	else if(pid == 0)//子进程
	{
		globvar ++;
		var --;
		//_exit(0);//这里要使用_exit避免结束时清除栈空间，这样会把父进程的空间也清除掉
		exit(0);//如果使用exit会什么样,父进程还是正常输出了,因为exit使用的是标准i/o流，但是printf不是
	}
	//in parent process
	printf("pid = %ld, glob=%d, var=%d\n", (long)getpid(), globvar, var);
	int i = printf("pid = %ld, glob=%d, var=%d\n", (long)getpid(), globvar, var);
	char buf[] = "";
	sprintf(buf,"%d\n",i);
	write(STDOUT_FILENO,buf,strlen(buf));
	exit(0);
}

/************
子进程中修改变量值影响了父进程
# ./vfork_learn 
before vfork
pid = 16535, glob=7, var=87

******************/