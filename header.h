#ifndef headers
#define headers

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

void prompt();
void input();
void tokenize(char *args);
void parse(char** tokens,char *temp);
void piping(char **tokens);
void execute(char **tokens, int cno, int noOfCommands);

void cd(char** tokens);
void pwd();
void echo(char** tokens);
void syscommandsfg(char **tokens, int cno, int noOfCommands);
void syscommandsbg(char **tokens);
void pinfo(char **tokens);
void listjobs();
void sendsig(char** tokens);
void movetofg(char **tokens);
void killallbg();

void signalHandler(int signo, siginfo_t *info, void *ptr);
void ctrlC(int);
void ctrlZ(int);

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char** arr;
char* home;

typedef struct 
{
	pid_t pid;
	char pname[100];
}bgprocs;

bgprocs joblist[1000];
pid_t shellpid;

#endif