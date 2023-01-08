compile_and_exec: txt.c ./src/headers/implementation/NewFunctions.c ./src/headers/implementation/NewInteractions.c ./src/headers/implementation/interface.c
	gcc -o exec_this -I ./src/headers/headers ./txt.c ./src/headers/implementation/NewFunctions.c ./src/headers/implementation/NewInteractions.c ./src/headers/implementation/interface.c
	clear
	printf "\n\nOra esegui exec_this - eventualmente con flag debug\n"