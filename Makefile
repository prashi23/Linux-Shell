myshell : main.o prompt.o getcommand.o parsing.o commands.o systemCommands.o builtinCommands.o signalhandler.o execute.o pipeHandler.o header.h
		gcc $^ -o myshell

getcommand.o : src/getcommand.c
	gcc -c src/getcommand.c

parsing.o : src/parsing.c
	gcc -c src/parsing.c

prompt.o : src/prompt.c
	gcc -c src/prompt.c

signalhandler.o : src/signalhandler.c
	gcc -c src/signalhandler.c

systemCommands.o : src/systemCommands.c
	gcc -c src/systemCommands.c

execute.o : src/execute.c
	gcc -c src/execute.c

pipeHandler.o : src/pipeHandler.c
	gcc -c src/pipeHandler.c

builtinCommands.o : src/builtinCommands.c
	gcc -c src/builtinCommands.c

commands.o : src/commands.c
	gcc -c src/commands.c

main.o : main.c
	gcc -c main.c

		
clean : 
	rm -f myshell