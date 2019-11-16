#include "../header.h"

void cd(char **tokens)
{
	char* destination = (char*)malloc(200*sizeof(char));
	int i, len;
	if(tokens[1][0] == '~')
	{
		strcpy(destination,home);
		len = strlen(destination);

		for(i=1;tokens[1][i]!='\0';i++)
		{
			destination[len++]=tokens[1][i];
		}
	}
	else
		strcpy(destination, tokens[1]);

	int test = chdir(destination);
	if(test == -1)
		perror("Error ");
}
void pwd()
{
	char *dir = (char*)malloc(1000*sizeof(char));
	dir = getcwd(dir,1000);
	if(dir != NULL)
	{
		write(1,dir,strlen(dir));
		write(1,"\n",1);
	}
	else
		perror("Error ");
}
void echo(char **tokens)
{
	
	int i;
	for(i=1;tokens[i]!=NULL;i++)
	{
		write(1,tokens[i],strlen(tokens[i]));
		write(1," ",1);
	}
	write(1,"\n",1);
}

