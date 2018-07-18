#include "apue.h"
#include <sys/times.h>

static void pr_times(clock_t, struct tms *, struct tms*);
static void do_cmd(char *);


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

/**********
func:将每个命令行参数作为shell命令串执行，对每个命令计时并打印从tms结构取得的值


**********/
int main(int argc, char *argv[]){
	int i;
	setbuf(stdout, NULL);
	for(i=1; i<argc; i++)
		do_cmd(argv[i]);
	exit(0);
}

static void do_cmd(char *cmd){
	struct tms tmsstart, tmsend;
	clock_t start, end;
	int status;

	printf("ncommand: %s\n",cmd);

	if((start = times(&tmsstart)) == -1)
		err_sys("times error!\n");
	if((status = system(cmd))<0)
		err_sys("system() error\n");
	if((end = times(&tmsend)) == -1)
		err_sys("times error!\n");

	pr_times(end-start, &tmsstart, &tmsend);
	pr_exit(status);
}

static void pr_times(clock_t real, struct tms *tmsstart, struct tms * tmsend){
	static long clktck = 0;
	if(clktck == 0)
		if((clktck = sysconf(_SC_CLK_TCK))<0)//返回每秒的时钟滴答数
			err_sys("sysconf error!\n");

	printf("real: %7.2f\n", real/(double)clktck);
	printf("user: %7.2f\n", tmsend->tms_utime - tmsstart->tms_utime/(double)clktck);
	printf("sys: %7.2f\n", tmsend->tms_stime - tmsstart->tms_stime/(double)clktck);
	printf("child_user: %7.2f\n", tmsend->tms_cutime - tmsstart->tms_cutime/(double)clktck);
	printf("child_sys: %7.2f\n", tmsend->tms_cstime - tmsstart->tms_cstime/(double)clktck);
}

/***********

执行第一个，第二个命令几乎不占用CPU时间，所以是0
执行第三个命令占用时间比较长，但是，是在system调用子进程内的cpu时间比较长
[root@localhost 8process]# ./process_time "sleep 5" "date" "man bash > /dev/null"
ncommand: sleep 5
real:    5.00
user:    0.00
sys:    0.00
child_user:    0.00
child_sys:    0.00
normal termination, exit status= 0
ncommand: date
Tue Jul 17 21:18:52 CST 2018
real:    0.00
user:    0.00
sys:    0.00
child_user:    0.00
child_sys:    0.00
normal termination, exit status= 0
ncommand: man bash > /dev/null
real:    0.17
user:    0.00
sys:    0.00
child_user:   24.00
child_sys:    3.00
normal termination, exit status= 0


******************/