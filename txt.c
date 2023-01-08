/*
    Program written by: Samuele Manclossi
    Special thanks to everyone
    Reminder: carica su github
*/
/*Inclusion of useful headers*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
/*Inclusion of my headers*/
#include "src/headers/headers/data.h" //header with constants used to improve readability
#include "src/headers/headers/structures.h" //header with structures to make my life easier
#include "src/headers/headers/characters.h" //header with description of characters
#include "src/headers/headers/NewFunctions.h" //header with basic functions
#include "src/headers/headers/NewInteractions.h" //header with basic interactions
#include "src/headers/headers/interface.h" //improving the aspect
#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
    #define LINUX
#elif defined(__APPLE__) && defined(__MACH__)
    #define MACOS
#elif defined(_WIN32) || defined(_WIN64)
    #define WINDOWS
#endif
//inclusion of more headers of mine
int main(int argc, char * argv[]){
    /*Declaration of variables*/
    int action, subaction, current_location=0, previous_location=-1,i,prevStatus=0,died=0,portafogli=0, we_re_playing=1;
    inv inventario;//declares inventory
    spbook spellbook;//declares spellbook
    map mappa; //declares THE MAP
    bestiary bestiario;
    sett settings;
    settings.audioOn=settings.randomEncounters=1;
    srand(time(NULL));
    printf(ASCIIART);
    setup(&mappa,&bestiario,&inventario,&spellbook); //in this part of the code it loads up literally anything from the files, more specifically: * the map * the items * the spells * the bestiary
    print_intro();/*game explanation*/
    if(argc>=2 && !strcmp(argv[1],"debug")){
        spellbook.spell[14].known=1;
        inventario.oggetto[7].available=1;
        printf("\n\n");
        print_debug();
    }
    mainLoop(&action,&subaction,&inventario,&spellbook,&current_location,&previous_location,&mappa,&prevStatus,&died,&bestiario,&portafogli,&settings);
    print_credits();
    getchar();//wait for user pressing any key
    return 0;//stops the exec
}