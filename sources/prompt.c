#include "../header.h"

void prompt()
{
	char *user = (char*)malloc(100 * sizeof(char));
	int test1 = getlogin_r(user,100);

	char *host = (char*)malloc(100*sizeof(char));
	int test2 = gethostname(host,100);

	char *dir = (char*)malloc(100*sizeof(char));
	dir = getcwd(dir,100);

	char *temp = (char*)malloc(100*sizeof(char));
	int pos = -1, i, k;
	for(i=0;dir[i]!='\0';i++)
	{
		temp[i]=dir[i];
		temp[i+1]='\0';
		if(strcmp (temp,home) == 0)
		{
			pos = i;
			break;
		}
	}
	
	if(pos != -1)
	{
		temp[0]='~';
		k=1;
		for(i=pos+1;dir[i]!='\0';i++)
		{
			temp[k++]=dir[i];
		}
		temp[k++]='\0';
	}
	else
		strcpy(temp,dir);

	printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET,user);
	printf("@");
	printf(ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_RESET,host);
	printf(":");
	printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET,temp);
	printf("$ ");

	
}