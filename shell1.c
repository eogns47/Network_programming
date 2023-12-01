#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t childPid;
    int status;

    childPid = fork();

    if(childPid>0){
        int ret;
        printf("부모 PID : %ld, pid : %d\n",(long)getpid(),childPid);
        ret = waitpid(childPid,&status,0);

        printf("부모종료 %d %d %d\n",ret,WIFEXITED(status),WEXITSTATUS(status),WEXITSTATUS(status));
        exit(0);
    }
    else if(childPid==0){
        printf("자식 시작 PID : %ld\n",(long)getpid());
        sleep(8);

        printf("자식 종료\n");
        exit(0);
    }
    else{
        perror("fork() error\n");
        return -1;
    }
    return 0;
}