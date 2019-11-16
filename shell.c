#include "header.h"

int main(int argc, char **argv)
{
	int i;
	joblist[0].pid=-1;
	shellpid=getpid();
	struct sigaction sVal;
	sVal.sa_flags = SA_RESTART;
	sVal.sa_sigaction = &signalHandler;

	sigfillset(&sVal.sa_mask);

	if(sigaction(SIGINT, &sVal, NULL)<0)
		perror("Error");
	if(sigaction(SIGCHLD, &sVal, NULL)<0)
		perror("Error");

	signal(SIGINT,ctrlC);


	arr = (char**)malloc(40000*sizeof(char*));
	for(i = 0; i < 40000 ; i++)
		arr[i]=(char*)malloc(20*sizeof(char));

	home = (char*)malloc(1000*sizeof(char));
	home = getcwd(home,1000);	
	do
	{
		prompt();
		input();	
	}
	while(1);

	return 0;
}