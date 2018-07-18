#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
	int fd;

	if((fd=creat("file.hole",FILE_MODE))<0){//创建一个文件
		err_sys("creat_error\n");
	}

	if(write(fd, buf1, 10) != 10)//offset 10 now
		err_sys("buf1 write  error!\n");

	if(lseek(fd,16384,SEEK_SET) == -1)//将偏移量设置成文件开始后的16384处
		err_sys("lseek error\n");

	if(write(fd, buf2, 10)!=10)
		err_sys("buf2 write error!\n");//offset现在应该是16394
	
	exit(0);
}

/***********
# gcc -o kongdong kongdong.c 
# ls
fork_learn  fork_learn.c  kongdong  kongdong.c  lseek_test  lseek_test.c
# ./kongdong 
# ls
file.hole   fork_learn.c  kongdong.c  lseek_test.c
fork_learn  kongdong      lseek_test
# ls -l file.hole 
-rw-r--r-- 1 root root 16394 Jul 13 14:29 file.hole

检查生成的文件的长度确实是16394

查看文件的实际内容
# od -c file.hole 
0000000   a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
*
0040000   A   B   C   D   E   F   G   H   I   J
0040012
************/