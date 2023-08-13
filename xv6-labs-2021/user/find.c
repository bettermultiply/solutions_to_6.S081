# include "kernel/types.h"
# include "kernel/stat.h"
# include "user/user.h"
# include "kernel/fs.h"

void findFile(char* dir, char* filename);
char* getname(char* path);

int
main(int argc, char* argv[]){
	
	if(argc != 3 && argc != 2){
		printf("Wrong argument number: %d, expected TWO.\n", argc - 1);
		exit(1);
	}
	if(argc == 3){
		findFile(argv[1], argv[2]);
	}else{
		findFile( ".", argv[1]);
	}
	exit(0);
}

void 
findFile(char* path, char* filename){
	char buf[512], *p;
	int fd;
	struct stat st;
	struct dirent de;
	if((fd = open(path, 0)) < 0){
		fprintf(2, "Can't open %s\n", path);
		return ;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "Can't stat %s\n", path);
		close(fd);
		return ;
	}
	
	switch(st.type){
	
	case T_FILE:
		char* s = getname(path);		
		if(!strcmp(s, filename)){
			printf("%s %d %d %d\n", path, st.type, st.ino, st.size);
		}

		break;

	case T_DIR:
	
		if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
			printf("find: the searched path has been too long.");
			break;
		}
		
		strcpy(buf, path);
		p = buf + strlen(buf);
		*p++ = '/';
		while(read(fd, &de, sizeof(de)) == sizeof(de)){
			if(de.inum == 0) continue;
			if(!strcmp(de.name, ".") || !strcmp(de.name, "..")) continue;
			memmove(p, de.name, DIRSIZ);
			p[DIRSIZ] = 0;
			findFile(buf, filename);
		}
	
		break;
	}

	close(fd);
	
}

char*
getname(char* path){
	static char filename[DIRSIZ+1];
	char* p;
	for(p=path+strlen(path); p > path && *p != '/'; p--)
		;
	p++;
	
	memmove(filename, p, strlen(p));
	filename[strlen(p)] = 0;
	return filename;
}
