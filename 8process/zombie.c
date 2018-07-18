#include "apue.h"

int main(void){

	pid_t pid;
	if((pid=fork())<0)
		err_sys("fork error!\n");
	else if(pid == 0)
		exit(0);

	sleep(4);//parent

	system("ps");
	exit(0);
 }