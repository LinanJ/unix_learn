#include "apue.h"

int globvar = 6;
char buf[] = "a wirte to stdout\n";

int main(void){
	int var;
	pid_t pid;

	var = 88;
	//写标准输出时，将buf的长度-1输出，是为了避免输出NULL，因为sizeof计算长度包含了最后
	//一个字节null的长度
	if(write(STDOUT_FILENO,buf,sizeof(buf)-1)!=sizeof(buf)-1)
		err_sys("write error!\n");
	printf("before fork\n");

	if((pid = fork())<0){
		err_sys("fork_error!\n");
	}
	else if(pid == 0){//child
		globvar++;
		var++;
	}
	else
		sleep(2);//parent
	printf("pid = %ld, globvar = %d, var = %d\n",(long)getpid(),globvar,var);
	exit(0);
}

/*********
# gcc -o fork_learn fork_learn.c 
# ls
fork_learn  fork_learn.c
# ./fork_learn 
a wirte to stdout
before fork
pid = 19528, globvar = 7, var = 89
pid = 19527, globvar = 6, var = 88

fork创建的子进程数据段父子之间不共享
因为不确定是父进程先执行还是子进程先执行，在父进程中休眠了2秒使子进程先执行
但2s的时间不一定能够，还有其他使父子进程同步的方法

*************/