#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

void print_argv(int argc, char ** argv, char * str_temp){
	printf("\n-----------------------print_argv %s-------------------------\n", str_temp);
	for (int index = 0; index < argc; ++index)
		printf("%d -> %s\n", index, argv[index]);
	printf("------------------print_argv end--------------------------------\n\n");
}


int main(int argc,char *argv[]){
	print_argv(argc, argv, "before getopt");		// print the argv list before getopt

	int func_return;
	// begin getopt
	while((func_return = getopt(argc, argv, "h:jk")) != -1)
	{
		printf("func_return = %c(%d), optind = %d, opterr = %d, optopt = %c(%d), optarg = %s\n", 
				(char)func_return, func_return, optind, opterr, (char)optopt, optopt, optarg);

		switch(func_return)
		{
			case 'j': printf("the option char is j\n"); break;
			case 'k': printf("the option char is k\n"); break;
			case 'h': printf("the option char is h, and the argument is %s\n", optarg); break;
			case '?':
			case ':': printf("parse option error, the error option char is %c\n", optopt); 
					  exit(EXIT_FAILURE);
		}
		printf("\n");
	}
	// end getopt	
	print_argv(argc, argv, "after getopt");		// print the argv list after getopt
	exit(EXIT_SUCCESS);
}


