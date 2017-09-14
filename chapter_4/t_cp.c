#include "tlpi_hdr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#ifndef READ_SIZE
#define READ_SIZE 1024
#endif


int main(int argc, char *argv[]){

	if (argc != 3)
		usageErr("%s source destination", argv[0]);

	int sour_fd, dest_fd;

	// open the source file
	sour_fd = open(argv[1], O_RDONLY);
	if (sour_fd == -1)
		errExit("open source file\n");

	// open the destination file 
	dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (dest_fd == -1)
		errExit("open dest file\n");

	int read_size = 0;
	char buff[READ_SIZE];
	while( (read_size = read(sour_fd, buff, READ_SIZE)) > 0){
		// judge the hole size from buff array
		int judge_size, hole_flag, judge_begin_point;
		judge_begin_point = 0;
		// init the hole flag
		if (buff[0] == 0)
			hole_flag = 1;
		else
			hole_flag = 0;
		judge_size = 1;


		for (int i = 1; i < read_size; ++i)
		{
			if (hole_flag == 1){
				if (buff[i] == 0)
					++judge_size;
				else{
					// move seek point of dest_fd
					if (lseek(dest_fd, judge_size, SEEK_CUR) == -1)
						errExit("lseek\n");
					judge_begin_point = i;
					judge_size = 1;
					hole_flag = 0;
				}
			}
			else if (hole_flag == 0){					// hole_flag == 0
				if (buff[i] == 0){
					//write the data
					if ( write(dest_fd, buff + judge_begin_point, judge_size) != judge_size )
						errExit("write\n");
					judge_begin_point = i;
					judge_size = 1;
					hole_flag = 1;
				}
				else
					++judge_size;
			}
			else
				errExit("hole_flag is not in [0,1]\n");

		}
		
		if (judge_size > 0){
			if (hole_flag == 1){
				if (lseek(dest_fd, judge_size, SEEK_CUR) == -1)
					errExit("lseek\n");
			}
			else{
				if ( write(dest_fd, buff + judge_begin_point, judge_size) != judge_size )
					errExit("write\n");
			}
		}
	}

	if (read_size == -1)
		errExit("read error\n");

	// close the file
	close(sour_fd);
	close(dest_fd);

	exit(EXIT_SUCCESS);
}

