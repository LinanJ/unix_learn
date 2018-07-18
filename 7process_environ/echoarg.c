#include "apue.h"

int main(int argc, char const *argv[])
{
	int i;

	for (i = 0; i < argc; i++)
	{
		printf("argv[%d]: %s\n",i, argv[i]);
	}

	for (i = 0; argv[i]!=NULL; i++)//两种方式，argv[argc]是一个空指针
	{
		printf("argv[%d]: %s\n",i, argv[i]);
	}

	return 0;
}

/*******
两种遍历的方式都可以
# gcc -o echoarg echoarg.c 
# ls
atexit_learn  atexit_learn.c  echoarg  echoarg.c
# ./echoarg  arg1 test foo
argv[0]: ./echoarg
argv[1]: arg1
argv[2]: test
argv[3]: foo
argv[0]: ./echoarg
argv[1]: arg1
argv[2]: test
argv[3]: foo


*******/

/*********
使用size 命令查看可执行程序的正文段，数据段，未初始化数据段长度

# size /root/jingln/unix_learn/7process_environ/echoarg
   text	   data	    bss	    dec	    hex	filename
   3991	    620	     24	   4635	   121b	/root/jingln/unix_learn/7process_environ/echoarg

# size /root/jingln/unix_learn/7process_environ/atexit_learn
   text	   data	    bss	    dec	    hex	filename
   4276	    628	     24	   4928	   1340	/root/jingln/unix_learn/7process_environ/atexit_learn

dec 和hex分别是以10进制和16进制表示的3段总长度
*********/