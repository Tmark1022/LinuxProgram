#include<stdio.h>

int main()
{
	#ifdef __GNUC__
	printf("use gcc compiler, __GNUC__ marco is %d\n", __GNUC__);
	#else
	printf("no gcc\n");
	#endif
	return 0;
}
