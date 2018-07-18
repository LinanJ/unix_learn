#include <stdio.h>

int f1(int val);
int main(void){
	int val1,val2;
	puts("we call f1(1)\n");
	val1 = f1(1);
	puts("we call f1(0)\n");
	val2 = f1(0);

	printf("after call f1(1):%d, f1(0):%d\n",val1,val2    );
	return 0;
}

int f1(int val){
	int num = 0;
	int *ptr = &num;

	if(val == 0){
		int val;
		val = 5;
		ptr = &val;
	}

	return (*ptr+1);
}