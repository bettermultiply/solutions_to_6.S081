#include <stdio.h>
#include <time.h>

int main(){
    printf("Begin\n");
    char buffer[1024*1024];
    int ping[2];
    int pong[2];
    int n = 0;
    pipe(ping);
    pipe(pong);
    // close(0);
    printf("Ready\n");
    int start = clock();
    if(fork() == 0){
        // dup(pong[0]);
        // close(pong[0]);
        close(ping[0]);
        do{
            // printf("%d", n);
            // printf("Child\n");
            write(ping[1], "win", 3);
            read(pong[0], buffer, 3);
            // fgets(buffer, )
        } while(n++ < 1000000);
        close(pong[1]);
        close(ping[1]);
        close(pong[0]);
    } else{
        // dup(ping[0]);
        close(pong[0]);
        // close(ping[0]);
        do{
            // printf("%d", n);
            // printf("Parent\n");
            write(pong[1], "win", 3);
            // printf("o");
            read(ping[0], buffer, 3);
        } while(n++ < 1000000);
        close(pong[1]);
        close(ping[1]);
        close(ping[0]);
        int end = clock();
        printf(buffer);
        double times = end - start;
        printf("\n%f", n/(times/CLOCKS_PER_SEC));
    }
    return 0;
}
