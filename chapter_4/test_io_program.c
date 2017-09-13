#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include"tlpi_hdr.h"

#include<stdio.h>


int main(int argc, char *argv[]){
	if (argc < 3)
	{
		usageErr("%s filepath\n", argv[0]);
	}
	
	printf("hello world\n");

	return 0;
}
