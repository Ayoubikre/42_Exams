#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

									// Mine:

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    if(!f)
        return -1;
    
    pid_t pid;
    pid=fork();
    if(pid == -1)
        return -1;
    else if(pid == 0)
    {
        f();
        exit(0);
    }

    int status=0;
    unsigned int time=0;
    pid_t tmp;

    while(1)
    {
        tmp = waitpid(pid, &status, WNOHANG);
        if(tmp==-1)
            return -1;
        if(tmp>0)
            break;
            
        sleep(1);
        time++;
        if(time>=timeout)
        {
            kill(pid, SIGKILL);
            waitpid(pid, &status, 0);
            if(verbose)
                printf("Bad function: timed out after %u seconds\n", time);
            return 0;
        }
    }
    
    if(WIFEXITED(status))
    {
        if(WEXITSTATUS(status)==0)
        {
            if(verbose)
                printf("Nice function!\n");
            return 1;
        }
        else
        {
            if(verbose)
                printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
        }
        return 0;
    }
    else if(WIFSIGNALED(status))
    {
        int sig= WTERMSIG(status);
        if(verbose)
            printf("Bad function: %s\n", strsignal(sig));
        return 0;
    }
    return -1;
}

void test()
{
    char *t= NULL;
    t[1]=0;
}

int main()
{
    sandbox(test, 5, 1);
}
