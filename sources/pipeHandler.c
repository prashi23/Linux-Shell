#include "../header.h"

void piping(char **tokens)
{
	int i, k, noOfCommands = 1, cno;

	char** command;
	command = (char**)malloc(200*sizeof(char*));
	for(i = 0; i < 200 ; i++)
	{
		command[i]=(char*)malloc(200*sizeof(char));
	}

	for(i=0;tokens[i]!=NULL;i++)
	{
		if(tokens[i][0] == '|')
		{
			noOfCommands++;
		}
	}
	k = 0; cno = 0;

	for(i=0; ;i++)
	{
		if(tokens[i] != NULL && tokens[i][0] != '|')
		{
			strcpy(command[k++],tokens[i]);
		}
		else if(tokens[i] == NULL || tokens[i][0] == '|')
		{
			command[k]=NULL;
			execute(command, cno, noOfCommands);
			k=0;
			cno++;
		}
		if(tokens[i]== NULL)
			break;
	}
}