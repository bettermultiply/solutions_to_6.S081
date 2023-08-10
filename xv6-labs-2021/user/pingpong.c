#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int args, char *argv[]){
	char buffer[64];
	int p_1[2], p_2[2];
	pipe(p_1);
	pipe(p_2);
	
	if(fork() == 0){
		close(p_1[0]);
		close(p_2[1]);
		sleep(1);
		read(p_2[0], buffer ,4);
		printf("%d: received %s\n", getpid(), buffer);
		write(p_1[1], "pong", 4);
		close(p_1[1]);
		close(p_2[0]);
	} else{
		close(p_1[1]);
		close(p_2[0]);
		write(p_2[1], "ping", 4);
		read(p_1[0], buffer, 4);
		printf("%d: received %s\n", getpid(), buffer);
		close(p_1[0]);
		close(p_2[1]);
	}

	exit(0);
}
