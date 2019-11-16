#include "../header.h"

void execute(char **tokens, int cno, int noOfCommands)
{
	int i, j, flag, fd, pos1 = -1, pos2 = -1, pos, test;

	int in = dup(0);
	int out = dup(1);

	for(i=0;tokens[i]!=NULL;i++)
	{
		if(tokens[i][0] == '<')
		{
			fd=open(tokens[i+1], O_RDONLY);
			test = dup2(fd,0);
			if(test == -1)
			{
				perror("dup error");
				return ;
			}

			close(fd);
			pos1 = i;
		}
		else if(tokens[i][0] == '>')
		{
			if(tokens[i][1] == '>')
				fd=open(tokens[i+1],O_CREAT | O_WRONLY |O_APPEND, 0644);
			
			else
				fd=open(tokens[i+1],O_CREAT | O_WRONLY | O_TRUNC, 0644);
			test = dup2(fd,1);
			if(test == -1)
			{
				perror("dup error");
				return ;
			}

			close(fd);
			pos2 = i;
		}
	}

	if(pos1 != -1 && pos2 != -1)
	{
		pos = (pos1 < pos2) ? pos1 : pos2;
		tokens[pos] = NULL;
	}
	else if(pos1 != -1)
		tokens[pos1]=NULL;
	
	else if(pos2 != -1)
		tokens[pos2] = NULL;

	if(strcmp(tokens[0],"cd") == 0)
	{
		cd(tokens);
	}
	else if(strcmp(tokens[0],"pwd") == 0)
	{
		pwd();
	}
	else if(strcmp(tokens[0],"echo") == 0)
	{
		echo(tokens);
	}
	else if(strcmp(tokens[0],"pinfo") == 0)
	{
		pinfo(tokens);
	}
	else if(strcmp(tokens[0],"listjobs") == 0) 
		listjobs();

	else if(strcmp(tokens[0],"sendsig") == 0) 
		sendsig(tokens);

	else if(strcmp(tokens[0],"killallbg") == 0) 
	{
		killallbg();		
	}
	else if(strcmp(tokens[0],"fg") == 0) 
	{
		movetofg(tokens);		
	}
	else if(strcmp(tokens[0],"quit") == 0) 
		exit(0);
	
	else
	{
		flag = 0;
		for(j=0;tokens[j]!=NULL;j++)
		{
			for(i=0;tokens[j][i]!='\0';i++)
			{
				if(tokens[j][i] == '&')
				{
					flag = 1;
					tokens[j][i]='\0';
					break;
				}
			}
		}

		if(flag == 0)
			syscommandsfg(tokens,cno,noOfCommands);
		else
			syscommandsbg(tokens);

		dup2(in,0);
		dup2(out,1);
	}
}