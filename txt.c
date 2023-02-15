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

/*#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
    #define LINUX
#elif defined(__APPLE__) && defined(__MACH__)
    #define MACOS
#elif defined(_WIN32) || defined(_WIN64)
    #define WINDOWS
#endif*/

int main(int argc, char * argv[]){
    /*Declaration of variables*/
    int action, subaction, current_location=0, previous_location=-1,i,prevStatus=0,died=0,portafogli=0, we_re_playing=1;
    inv inventario;//declares inventory
    spbook spellbook;//declares spellbook
    map mappa; //declares THE MAP
    bestiary bestiario;//declares the bestiary
    sett settings;//declares the "settings" struct
    settings.audioOn=settings.randomEncounters=1;//sets the audio and the random encounters "ON"
    srand(time(NULL));//generates the seeds based on time
    printf(ASCIIART);//prints the initial ascii art
    setup(&mappa,&bestiario,&inventario,&spellbook); //in this part of the code the program loads up literally anything from the files, more specifically: * the map * the items * the spells * the bestiary
    print_intro();/*game explanation*/
    if(argc>=2 && !strcmp(argv[1],"debug")){ //if the debug mode is requested
        spellbook.spell[14].known=1; //the character earns teleport
        inventario.oggetto[7].available=1; //and a map
        printf("\n\n");
        print_debug(); //debug acknowledgement
    }
    mainLoop(&action,&subaction,&inventario,&spellbook,&current_location,&previous_location,&mappa,&prevStatus,&died,&bestiario,&portafogli,&settings);//the main game
    print_credits();//final credits
    getchar();//wait for user pressing any key
    return 0;//stops the exec
}