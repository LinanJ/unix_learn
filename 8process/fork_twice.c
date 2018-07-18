#include "apue.h"
#include <sys/wait.h>

/********
func:既不调用wait也能不产生僵尸进程
add by jingln
***********/

int main(void)
{
	pid_t pid;
	int status;

	if((pid=fork())<0)//创建一个子进程
		err_sys("fork error!\n");
	else if(pid == 0)//子进程
	{
		if((pid=fork())<0)
			err_sys("fork error!\n");
		else if(pid > 0)
		{
			printf("second child, pid = %ld\n", (long)getpid());
			exit(0);//第二次创建的子进程的父进程是第一次创建的子进程
		}

		sleep(2);
		printf("second child, parent pid = %ld\n", (long)getpid());
		exit(0);
	}

	//这里不加等待结果是一样的
	//if(waitpid(pid,NULL,0)!=pid) //等待第一个子进程
		//err_sys("wait error!\n");

	exit(0);
}
