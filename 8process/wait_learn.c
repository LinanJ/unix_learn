#include "apue.h"
#include <sys/wait.h>

void pr_exit(int status)//使用宏，打印进程终止状态
{
	if(WIFEXITED(status))
		printf("normal termination, exit status= %d\n",WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d%s\n",WTERMSIG(status),"");

	else if(WIFSTOPPED(status))
		printf("child stopped, signal number =%d\n", WSTOPSIG(status));

}

/********
func:获取进程的终止信息
add by jingln
***********/

int main(void)
{
	pid_t pid;
	int status;

	if((pid=fork())<0)//创建一个子进程
		err_sys("fork error!\n");
	else if(pid == 0)//子进程使用exit退出
		exit(7);
	if(wait(&status) != pid)//等待子进程退出并获得退出状态信息
		err_sys("wait error!\n");
	pr_exit(status);		//打印退出状态信息

	if((pid=fork())<0)//创建一个子进程
		err_sys("fork error!\n");
	else if(pid == 0)//子进程使用abort产生signal退出
		abort();
	if(wait(&status) != pid)
		err_sys("wait error!\n");
	pr_exit(status);		

	if((pid=fork())<0)//创建一个子进程
		err_sys("fork error!\n");
	else if(pid == 0)//通过产生SIGFPE退出
		status /= 0;
	if(wait(&status) != pid)
		err_sys("wait error!\n");
	pr_exit(status);

	exit(0);
}

/**************
# ./wait_learn 
normal termination, exit status= 7
abnormal termination, signal number = 6
abnormal termination, signal number = 8

************/