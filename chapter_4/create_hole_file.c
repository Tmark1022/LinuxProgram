#include "tlpi_hdr.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

#ifndef OFFSET
#define OFFSET 10000
#endif


int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		usageErr("%s pathname\n", argv[0]);
	}

	int open_flags = O_WRONLY | O_CREAT | O_TRUNC;
	int file_permission = S_IRUSR | S_IWUSR;
	int fd;
	fd = open(argv[1], open_flags, file_permission);
	if (fd == -1)
		errExit("open file");

	char buff[10] = "123456789";

	// write, the begin of the file
	if (write(fd, buff, strlen(buff)) != strlen(buff))
		errExit("write begin");

#ifdef LOOP_NUM
	int num = LOOP_NUM;
#else
	int num = 2;
#endif
	for (int i = 1; i <= num; ++i){
		if (lseek(fd, OFFSET, SEEK_CUR) == -1)
			errExit("seek");

		if (write(fd, buff, strlen(buff)) != strlen(buff))
			errExit("write end");
	}

	// close the file
	close(fd);

	exit(EXIT_SUCCESS);
}

