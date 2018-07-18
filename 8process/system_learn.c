#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include "apue.h"

void pr_exit(int status)//使用宏，打印进程终止状态
{
	if(WIFEXITED(status))
		printf("normal termination, exit status= %d\n",WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d%s\n",WTERMSIG(status),"");

	else if(WIFSTOPPED(status))
		printf("child stopped, signal number =%d\n", WSTOPSIG(status));

}

//调用命令行输入执行命令
int system(const char *cmdstring){
	pid_t pid;
	int status;

	if(cmdstring == NULL)
		return (1);
	if((pid=fork())<0){
		status = -1;
	}else if(pid == 0){
		execl("/usr/bin/sh", "sh", "-c", cmdstring, (char*)0);
		_exit(127);
	}else{
		while(waitpid(pid, &status,0)<0){
			if(errno!=EINTR){
				status = -1;
				break;
			}
		}
	}

	return (status);
}

int main(void){
	int status;
	if((status = system("date"))<0)//正常退出状态是0
		err_sys("system() error!\n");
	pr_exit(status);

	if((status = system("nosuchcommanddddddd"))<0)//无此种命令退出状态是127
		err_sys("system() error!\n");
	pr_exit(status);

	if((status = system("who; exit 44"))<0)//exit退出状态是44
		err_sys("system() error!\n");
	pr_exit(status);

	exit(0);
}

/**************

[root@localhost 8process]# ./system_learn 
Tue Jul 17 20:17:28 CST 2018
normal termination, exit status= 0
sh: nosuchcommanddddddd: command not found
normal termination, exit status= 127
root     pts/0        2018-07-17 15:30 (192.168.8.71)
dsp      pts/1        2018-07-17 16:50 (192.168.8.65)
dsp      pts/2        2018-07-17 19:39 (192.168.8.65)
root     pts/3        2018-07-17 19:57 (192.168.8.71)
normal termination, exit status= 44

**************/