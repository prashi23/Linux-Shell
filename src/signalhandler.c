#include "../header.h"

void signalHandler(int sig, siginfo_t *si, void *context)
{
	int status, pid, i, pos;
	switch(sig)	
	{
		/*case SIGINT:
		fprintf(stderr, "\nControl-C was pressed\n");
		break;
*/
		case SIGQUIT:
		exit(0);
		break;

		case SIGTERM:
		pid = waitpid(-1, NULL, WNOHANG);
		if(pid>0)
			kill(pid , SIGTERM);
		break;
		
		case SIGCHLD:
		pid = waitpid(-1, NULL, WNOHANG);
		if(pid>0)
		{
			
			kill(pid , SIGTERM);
			if(arr[pid][0]!=0)
			{
				fprintf(stderr, "\n%s with pid %d exited!\n" ,arr[pid], pid);
				for(i=0;joblist[i].pid!=-1;i++)
				{
					if(joblist[i].pid == pid)
						pos = i;
				}
				for(i=pos;joblist[i+1].pid!=-1;i++)
				{
					joblist[i]=joblist[i+1];
				}
				joblist[i].pid = -1;

			}
			arr[pid][0]=0;
		}
		break;
	}
}

void ctrlC(int signo)
{
	if(signo == SIGINT)
	{
		if(getpid() != shellpid)
			kill(getpid(),9);
		else
		{
			printf("\n");
		}
	}
	// printf("\n");
}

void ctrlZ(int signo)
{
	if(signo == SIGTSTP)
	{
		printf("Detected Ctrl+Z\n");
	}

}