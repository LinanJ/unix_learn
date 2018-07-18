#include <errno.h>
#include <sys/time.h>
#include "apue.h"

#if defined(MACOS)
#include <sys/syslimit.h>
#elif defined(SOLARIS)
#include <limit.h>
#elif defined(BSD)
#include <sys/param.h>
#endif

unsigned long long count;
struct timeval end;

void checktime(char *str){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	if(tv.tv_sec >= end.tv_sec && tv.tv_usec >= end.tv_usec){
		printf("%s count =%lld\n", str, count);
		exit(0);
	}
}

/*******
两个进程并行运行，各自增加自己的计数器，父进程使用默认的nice，子进程用可选命令参数调整nice
运行10s后，两个进程打印各自的计数值并终止
比较不同的nice值的进程的计数值的差异，了解nice值如何影响进程调度

**********/

int main(int argc, char *argv[]){
	pid_t pid;
	char *s;
	int nzero,ret;
	int adj=0;

	setbuf(stdout,NULL);
#if defined(NZERO)
	nzero = NZERO;
#elif defined(_SC_NZERO)
	nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif
	printf("NZERO = %d\n", nzero);//输出默认nice值
	if(argc == 2)  //若输入了调整子进程nice值的参数，则将adj设为该值，否则adj=0
		adj = strtol(argv[1], NULL, 10);

	gettimeofday(&end, NULL);
	end.tv_sec += 10; //运行10s

	if((pid=fork())<0)
		err_sys("fork faild!\n");
	else if(pid == 0){//child
		s = "child";
		printf("current nice value in child is %d adjusting by %d\n",nice(0)+nzero, adj);
		errno = 0;

		if((ret = nice(adj))==-1 && errno !=0 )
			err_sys("child set scheduling priority\n");
		printf("now child nice value is %d\n",ret+nzero);
	}else{//parent
		s = "parent";
		printf("current nice value in parent is %d\n",nice(0)+nzero);
	}

	for(;;){
		if(++count == 0)
			err_quit("%s counter wrap",s);
		checktime(s);
	}

}

/***************
没加调整nice的参数
# ./nice_learn 
NZERO = 20
current nice value in parent is 20
current nice value in child is 20 adjusting by 0
now child nice value is 20
child count =292191966
parent count =292187120

加了调整nice的参数
# ./nice_learn 20
NZERO = 20
current nice value in parent is 20
current nice value in child is 20 adjusting by 20
now child nice value is 39
parent count =292449020
child count =292307809


*******************/