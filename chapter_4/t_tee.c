#include "tlpi_hdr.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>

#ifndef BUFFSIZE
#define BUFFSIZE 1024
#endif


int main(int argc, char *argv[]){
	char buff[BUFFSIZE];
	int opt;
	int a_flag = 0;
	int *fd_array;						// fd list pointer

	while((opt = getopt(argc, argv, "a")) != -1){
		switch(opt){
			case 'a': a_flag = 1; break;
			default : usageErr("%s [[-a] pathname]", argv[0]); break;
		}
	}


	printf("optind = %d\n", optind);
	
	// open the file 
	int open_flags = O_WRONLY | O_CREAT | O_TRUNC;
	int file_perms = S_IRUSR | S_IWUSR;
	int fd_temp = -1;
	
	if (a_flag){
		open_flags = open_flags | O_APPEND;
		open_flags = open_flags ^ O_TRUNC;
	}
	
	int fd_array_size = argc - optind;
	if ((fd_array = malloc(fd_array_size * sizeof(int))) == NULL)
		errExit("alloc memory");

	for(int index = optind; index < argc; ++index){
		printf("%d -> %s\n", index, argv[index]);
		// open hte file
		fd_temp = open(argv[index], open_flags, file_perms);
		if (fd_temp == -1)
			errExit("open file");
		*(fd_array + index - optind) = fd_temp;
	}


	while(gets(buff) != NULL){
		fprintf(stdout, "%s\n", buff);
		for (int i = 0; i < fd_array_size; ++i)
			if (write(*(fd_array + i), buff, strlen(buff)) == -1 || write(*(fd_array + i), "\n", 1) == -1)
				errExit("write file, fd = %d\n", *(fd_array + i));
	}
	
	//close the file
	for (int i = 0; i < fd_array_size; ++i)
		close(*(fd_array + i));
	free(fd_array);
	exit(EXIT_SUCCESS);
}

