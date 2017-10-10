#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"tlpi_hdr.h"
#include<stdio.h>
#include<stdlib.h>


#ifndef BUFF_SIZE
#define BUFF_SIZE 1024
#endif



// fcntl F_GETFL 只能用于检测访问标志和状态标记，不能用于检测创建标记（O_CREAT O_TRUNC等）
int main(int argc, char *argv[]){
	if (argc < 2){
		usageErr("%s filepath\n", argv[0]);
	}
	
	int fd, openflags;
	mode_t file_perms;
	openflags = O_CREAT | O_WRONLY | O_TRUNC | O_SYNC;
	file_perms = S_IRUSR | S_IWUSR;
	fd = open(argv[1], openflags, file_perms);
	if (-1 == fd)
		errExit("open file");


	int flags;
	flags = fcntl(fd, F_GETFL);
	if (-1 == flags)
		errExit("fcntl");

	printf("flags %08x\n", flags);
	printf("%d\n", sizeof(int));

	
	printf("%08x\n", openflags);


	printf("%08x\n", O_CREAT);
	printf("%08x\n", O_TRUNC);
	printf("%08x\n", O_SYNC);


	if(flags & O_CREAT)
		printf("O_CREAT flag is open\n");
	else
		printf("O_CREAT flag is not open\n");

	if(flags & O_TRUNC)
		printf("O_TRUNC flag is open\n");	
	else
		printf("O_TRUNC flag is not open\n");

	if(flags & O_SYNC)
		printf("O_SYNC FLAG is open\n");
	else
		printf("O_SYNC flag is not open\n");
	
	return 0;
}
