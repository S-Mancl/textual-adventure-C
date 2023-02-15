gcc -o exec_this.exe -I src/headers/headers txt.c src/headers/implementation/NewFunctions.c src/headers/implementation/NewInteractions.c src/headers/implementation/interface.c
cls
exec_this.exe debug
del exec_this.exe