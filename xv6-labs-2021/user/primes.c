# include "kernel/types.h"
# include "kernel/stat.h"
# include "user/user.h"

int
main (){
	int root_flag = 1, forkable = 1, p = 1, n = 1;
	int pi_1[2] = {0}, pi_2[2] = {0};
	
	loop:
	if(root_flag){
		p = 2;
		n = p;
		printf("prime %d\n", p);
	}else{
 		read(pi_1[0], &p, 1);
		printf("prime %d\n", p);
	}
	
	while(n < 35){
		if(root_flag){
			n++;
		}else{
			if(!read(pi_1[0], &n, 1)){break;}
		}  
		if(n%p != 0){
			if(forkable){pipe(pi_2);}
			if(forkable && fork() == 0){
			 	root_flag = 0;
				close(pi_1[0]);
			 	close(pi_2[1]);
				pi_1[0] = pi_2[0];
				goto loop;
			}else if(forkable){
				forkable = 0;
				close(pi_2[0]);
			}
			write(pi_2[1], &n, 1);
		}	
	}                                                        
	if(pi_2[1]){close(pi_2[1]);close(pi_1[1]);}
	if(!forkable){
		wait(&n);
	}
	if(pi_1[0]){close(pi_1[0]);}
	
	exit(0);
}
