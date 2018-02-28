#include<stdio.h>
#include<stdlib.h>
#include<syscall.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>
#include<errno.h>
#include<error.h>
#include<assert.h>
#include<sys/wait.h>
#include "shell_prompt.c"

int main()
{
    char arg[1024],cmd[1024],cwd[1024],ch, input[1024],addr[1024],temp[1024];
    char s[2]="/";
    char *file[10];
    char amp[2]="&";
    char cd[5]="cd";
    char pwd[5]="pwd";
    char echo[5]="echo";
    cwd[1023]='\0';
    char home[10]="/home";
    char *tokken;
    addr[1023]='\0';

    while(1)
    {
        int x;
        for (x=0;x<1024;x++)
        {
            arg[x]='\0';
            cmd[x]='\0';
            input[x]='\0';
        }
        //chdir("/");
        prompt();
        int j=0;
        ch='\0';
        while(ch!='\n')
        {
            ch=getchar();
            input[j]=ch;
            j++;
        }
        int m=0,o=0;
        int n=0;
        while (input[n]==' ' || input[n]=='\t')
            n++;
        while(input[n]!=' ' && n<strlen(input) && input[n]!='\n')// || input[n]!='\t')
        {
            cmd[o]=input[n];
            n++;
            o++;
        }
        file[0]=strdup(cmd);
        n++;
        while (input[n]!='\n' && n<strlen(input))
        {
            arg[m]=input[n];
            m++;
            n++;
        }
        if(!strcmp(cmd, cd))
        {
            if(!strcmp(arg,home) || !strcmp(arg,s))
                printf("ERROR\n");
            else
                chdir(arg);
        }
        else if (!strcmp(cmd,pwd))
        {
            char dir[1024];
            getcwd(dir,sizeof(dir));
            printf("%s\n", dir);
        }
        else if(!strcmp(cmd,echo))
        {
            int ind=0;
            while(arg[ind]!='\0')
            {
                while(arg[ind]=='"')
                    ind++;
                printf("%c",arg[ind]);
                ind++;
            }
            printf("\n");
        }
        else
        {
           // printf("going into the else condition\n");
                pid_t pid,wpid;
                int status;
                pid = fork();
                if (pid == 0)
                {
                    //printf("child process\n");
                    execvp(file[0],file);
                    exit(1);
                }
                else 
                {
                   if (strcmp(arg,amp))
                    {
                       // printf("parent process\n");
                        continue;
                    }
                    else
                    {
                        do {
                            wpid=(pid,&status,WUNTRACED);
                        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
                    }
                }
            }   
    }
    return 0;
}
