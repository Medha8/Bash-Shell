void prompt()
{
    char t[1026]="~",cwd[1024],addr[1024],temp[1024],hname[1024];
    char *tokken,*tokken1;
    char s[2]="/", home[10]="/home";
    hname[1203]='\0';
    gethostname(hname,1023);
    getcwd(cwd, sizeof(cwd));
    strcpy(temp,cwd);
    tokken = strtok(cwd,s);
    tokken1=tokken;
    //printf("tok1:%s tok:%s\n", tokken1, tokken);
    int len1 = strlen(tokken)+1;
    // printf("cwd:%s", cwd);
    tokken = strtok(NULL,s);
    len1 += strlen(tokken)+1;
    int len2 = strlen(temp);
    int i,n=0;
    for (i=len1;i<=len2;i++)
    {
        addr[n]=temp[i];
        n++;
    }
    //printf("%d %d", strcmp(temp,home), strcmp(temp,s));
    if( (!strcmp(temp,home) || !strcmp(temp,s)) != 0 )
        strcpy(t,temp);
    else
        strcat(t,addr);

    printf("<%s@%s:%s>",getenv("USER"), hname,t);
}

