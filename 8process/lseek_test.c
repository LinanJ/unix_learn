#include "apue.h"

int main(void){
	if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)//标准输入
		printf("can't seek\n");
	else
		printf("seek ok!\n");
	exit(0);
}

/********
# gcc -o lseek_test lseek_test.c 
# ls
fork_learn  fork_learn.c  lseek_test  lseek_test.c
# ./lseek_test < /etc/passwd
seek ok!
# cat <etc/passwd| ./lseek_test 
-bash: etc/passwd: No such file or directory
can't seek
# cat < /etc/passwd| ./lseek_test 
can't seek

***********/