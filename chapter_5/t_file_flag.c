#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char * argv[]){
	int a = 10;
	
	printf("%08x\n",O_RDONLY);
	printf("%08x\n",O_WRONLY);
	printf("%08x\n",O_RDWR);
	printf("%08x\n",O_EXCL);
	printf("%08x\n",O_APPEND);
	printf("%08x\n",O_CREAT);

	printf("%08x\n",F_GETFL);

	exit(EXIT_SUCCESS);
}
