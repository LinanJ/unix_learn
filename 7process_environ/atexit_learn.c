#include "apue.h"

static void my_exit2(void);
static void my_exit1(void);


int main(void){
	if (atexit(my_exit2)!=0)//成功返回0，出错返回其他值
	{
		/* code */
		err_sys("can't register my_exit2!");
	}
	if (atexit(my_exit1)!=0)//成功返回0，出错返回其他值
	{
		/* code */
		err_sys("can't register my_exit1!");
	}
	if (atexit(my_exit1)!=0)//成功返回0，出错返回其他值
	{
		/* code */
		err_sys("can't register my_exit1!");
	}

	printf("main is done!\n");
	return 0;
}

static void my_exit2(void){
	printf("second exit handler!\n");
}

static void my_exit1(void){
	printf("first exit handler!\n");
}



/*********
# gcc -o atexit_learn atexit_learn.c 
# ls
atexit_learn  atexit_learn.c
# ./atexit_learn 
main is done!
first exit handler!
first exit handler!
second exit handler!

是在return 0的时候调用退出，终止程序登记一次就会被调用1次，不过这个调用的顺序是怎么决定的？
*******/