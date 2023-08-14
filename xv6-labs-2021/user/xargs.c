# include "kernel/types.h"
# include "kernel/stat.h"
# include "user/user.h"
# include "kernel/param.h"
# include "kernel/fs.h"

char 
getchar(){
	char c;
	read(0, &c, 1);
	return c;
}


int
main(int argc, char* argv[]){

	char argu[64], c;
	char* Args[MAXARG] = {};
	int n = 0, p = 0;
	for(int i = 1; i < argc; i++){
		Args[i-1] = argv[i];
	}
	while((c=getchar())){
		if(c == '\n' || c == 0){
			argu[n] = 0;
			Args[argc-1] = argu;
			Args[argc] = 0;
			n = 0;
			if(fork() == 0){
				exec(Args[0], Args);
			}else{
				wait(&p);
				printf("");
				if(c == 0) break;
				continue;	
			}
			
		}
		argu[n] = c;
		n++;
	}
	exit(0);
}
