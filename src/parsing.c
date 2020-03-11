 #include "../header.h"

void tokenize(char *args)
{
	char *list[1000], *tokens[1000];
	int num = 0, i;
	char* token;
	char delimiter1[] = ";\n";
	token = strtok(args, delimiter1);
	while(token!=NULL)
	{
		list[num++]=token;
		token = strtok(NULL,delimiter1);
	}	
	list[num++]=NULL;
	for(i=0;list[i]!=NULL;i++)
	{
		parse(tokens,list[i]);
		piping(tokens);
	}
}

void parse(char **tokens,char *temp)
{
	int num = 0;
	char delimiter2[] = " \t;\n";
	char *token = strtok(temp, delimiter2);
	while(token != NULL)
	{
		tokens[num++] = token;
		token = strtok(NULL,delimiter2);
	}
	tokens[num++]=NULL;
}