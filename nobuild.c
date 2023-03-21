#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

#define LIBS "-I./src/headers/headers"

void compile(void){
    RM("exec_this");;
    CMD("gcc", "-o", "exec_this", LIBS, "./txt.c", "./src/headers/implementation/NewFunctions.c", "./src/headers/implementation/NewInteractions.c", "./src/headers/implementation/interface.c");
    INFO("Ora esegui exec_this - eventualmente con flag degug");
}

int main(int argc, char **argv){
    GO_REBUILD_URSELF(argc, argv);
    INFO("Hi there, we are creating this file in order to let you build only one file that will compile everything dor you!");
    compile();
    return 0;
}
