#include "../header.h"

void syscommandsfg(char **tokens, int cno, int noOfCommands)
{
	int fd1[2], fd2[2];
	if(noOfCommands != 1)
	{
		if(cno%2==0)
		{
			pipe(fd2);	
		}
		else
		{
			pipe(fd1);
		}
	}
	pid_t pid = fork();
	int status;
	if(pid < 0)
	{
		if(noOfCommands != 1)
		{
			if (cno != noOfCommands - 1)
			{
				if (cno % 2 != 0)
				{
					close(fd1[1]); 
				}
				else
				{
					close(fd2[1]); 
				} 
			}
		} 
		perror("Error ");
	}
	else if(pid == 0)
	{
		
		if(noOfCommands != 1)
		{
			if(cno == 0)
			{

				dup2(fd2[1],1);
			}
			else if(cno == noOfCommands - 1)
			{

				if(cno % 2 == 0)
				{	
					dup2(fd1[0],0);	
				}
				else
				{		
					dup2(fd2[0],0);
				}
			}
			else
			{

				if(cno % 2 == 0)
				{
					dup2(fd2[1],1);	
					dup2(fd1[0],0);		
				}
				else
				{
					dup2(fd1[1],1);
					dup2(fd2[0],0);
				}
			}
		}
		
		int temp = execvp(tokens[0],tokens);
		if(temp == -1)
			fprintf(stderr,"%s : Command not found!\n",tokens[0]);
	}
	else
	{
		int status;
		if(noOfCommands != 1)
		{
			if(cno == 0)
			{
				close(fd2[1]);
			}
			else if(cno == noOfCommands - 1)
			{
				if(cno%2==0)
				{
					close(fd1[0]);
				}
				else
				{
					close(fd2[0]);
				}
			}
			else
			{
				if(cno%2==0)
				{
					close(fd2[1]);
					close(fd1[0]);
				}
				else
				{
					close(fd1[1]);
					close(fd2[0]);
				}
			}
		}
		waitpid(pid, &status, 0);
	}
}
void syscommandsbg(char **tokens)
{
	int i;
	pid_t pid = fork();
	int status;
	if(pid < 0)
	{
		printf("Error\n");
	}
	else if(pid == 0)
	{
		setpgid(0,0);
		int temp=execvp(tokens[0],tokens);
		if(temp == -1)
			fprintf(stderr,"%s : Command not found!\n",tokens[0]);
	}
	else
	{
		strcpy(arr[pid], tokens[0]);
		bgprocs temp;
		temp.pid = pid;
		strcpy(temp.pname, tokens[0]);
		for(i=0;joblist[i].pid!=-1;i++)
		{
		}
		joblist[i]=temp;
		joblist[i+1].pid=-1;
		return ;
	}
}