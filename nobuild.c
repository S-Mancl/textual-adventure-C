#include <string.h>
#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

#define LIBS "-I./src/headers/headers"
#define FILES "./txt.c", "./src/headers/implementation/NewFunctions.c", "./src/headers/implementation/NewInteractions.c", "./src/headers/implementation/interface.c"

void compile(void){
    #ifdef WIN32
        RM("exec_this.exe");
        CMD("gcc", "-o", "exec_this.exe", LIBS, FILES);
        INFO("Ora esegui exec_this.exe - eventualmente con flag debug");
    #else
        RM("exec_this");
        CMD("gcc", "-o", "exec_this", LIBS, FILES);
        INFO("Ora esegui exec_this - eventualmente con flag debug");
    #endif
}

void debug(void){
    compile();
    #ifdef WIN32
        CMD("exec_this.exe","debug");
        RM("exec_this.exe");
    #else
        CMD("./exec_this","debug");
        RM("exec_this");
    #endif
}

int main(int argc, char **argv){
    GO_REBUILD_URSELF(argc, argv);
    INFO("Hi there, we are creating this file in order to let you build only one file that will compile everything dor you!");
    const char *program = shift_args(&argc, &argv);
    if (argc>0) {
        const char *subcmd = shift_args(&argc, &argv);
        #ifdef WIN32
            if (strcmp(subcmd, "run")==0) {
                CMD("exec_this.exe");
            } else if (strcmp(subcmd, "debug")==0) {
                debug();
            }
        #else
            if (strcmp(subcmd, "run")==0) {
            CMD("./exec_this");
            } else if (strcmp(subcmd, "debug")==0) {
                debug();
            }
        #endif
    } else {
        compile();
    }
    return 0;
}
