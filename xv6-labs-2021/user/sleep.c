#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int args, char *argv[]){
	if(args <= 1){
		printf("Excepted one argument.");
		exit(-1);
	}
	int sleep_time = atoi(argv[1]);
	sleep(sleep_time);
	exit(0);
}
