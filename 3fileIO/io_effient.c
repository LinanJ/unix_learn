#include "apue.h"

#define BUFFERSIZE 4096

//使用read和write复制一个文件的效率
int main(void){

	int n;
	char buf[BUFFERSIZE];

	while((n=read(STDIN_FILENO,buf,BUFFERSIZE))>0)//标准输入
		if(write(STDOUT_FILENO,buf,n) != n)
			err_sys("write error!\n");

	if(n < 0)
		err_sys("read error!\n");

	exit(0);
}

/********
从标准输入读写至标准输出

**********/