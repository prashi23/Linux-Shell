#include "../header.h"

void input()
{
	size_t bytes = 100;
	char *args = (char*) malloc((bytes+1)*sizeof(char));
	int size = getline(&args,&bytes,stdin);
	if(size != -1)
	{
		
		tokenize(args);
	}
	else
	{
		printf("\n");
		exit(0);
	}
}