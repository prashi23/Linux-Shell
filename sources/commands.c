#include "../header.h"

void pinfo(char **tokens)
{
	if(tokens[1] == NULL)
	{
		fprintf(stderr,"Usage : pinfo <pid>\n");
		return ;
	}

	int flag = 0;
	char s[50];
	ssize_t size;

	char path[]="/proc/";
	strcat(path,tokens[1]);
	strcat(path,"/status");

	int fd;
	fd=open(path, O_RDONLY);

	while(1)
	{
		size=read(fd,s,1);
		if(size<=0)
			break;
		write(1,s,1);
		flag = 1;
	}

	close(fd);
	if(flag == 0)
	{
		strcpy(s,"Process Status: N/A\n");
		write(1,s,strlen(s));
		strcpy(s,"Memory: N/A\n");
		write(1,s,strlen(s));
	}

	char path2[]="/proc/";
	strcat(path2,tokens[1]);
	strcat(path2,"/cmdline");
	
	fd=open(path2,O_RDONLY);
	write(1,"Executable File: ",17);
	
	flag = 0;
	while(1)
	{
		size=read(fd,s,1);
		if(size<=0)
			break;
		write(1,s,1);
		flag = 1;
	}
	if(flag == 0)
		write(1,"N/A",3);
	write(1,"\n",1);

	close(fd);
}

void killallbg()
{
	int i;
	for(i=0;joblist[i].pid!=-1;i++)
	{
		printf("Killing %d\n",joblist[i].pid);
		kill(joblist[i].pid,SIGKILL);
	}
	joblist[0].pid=-1;
}

void listjobs()
{
	int i;
	for(i=0;joblist[i].pid!=-1;i++)
	{
		printf("[%d] %s [%d]\n", (i+1),joblist[i].pname,joblist[i].pid);
	}
}

void movetofg(char **tokens)
{
	int i,jno=0,status;
	for(i=0;i<strlen(tokens[1]);i++)
	{
		jno = jno*10 + (tokens[1][i]-48);
	}
	jno--;
	for(i=0;joblist[i].pid!=-1;i++)
	{
		if(i==jno)
			break;
	}
	if(i==jno)
	{
		kill(joblist[jno].pid, SIGCONT);
		waitpid(joblist[jno].pid,&status,0);
	}

	else
		fprintf(stderr,"Job %d doesn not exist", jno+1);
}

void sendsig(char** tokens)
{
	int ret, i, jno=0, signo=0;
	for(i=0;i<strlen(tokens[1]);i++)
	{
		jno = jno*10 + (tokens[1][i]-48);
	}
	jno--;
	for(i=0;i<strlen(tokens[2]);i++)
	{
		signo = signo*10 + (tokens[2][i]-48);
	}
	pid_t pid = joblist[jno].pid;
	ret = kill(pid,signo);
}

