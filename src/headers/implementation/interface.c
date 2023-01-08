#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include "../../../src/headers/headers/data.h" //header with constants used to improve readability
#include "../../../src/headers/headers/structures.h" //header with structures to make my life easier
#include "../../../src/headers/headers/characters.h"
#include "../../../src/headers/headers/NewFunctions.h"
#include "../../../src/headers/headers/NewInteractions.h"
#include "../../../src/headers/headers/interface.h"
#if defined(__APPLE__) && defined(__MACH__)
    #define MACOS
#elif defined(_WIN32) || defined(_WIN64)
    #define WINDOWS
#else
    #define LINUX
#endif

#ifdef WINDOWS
    #include<windows.h>
#else
    #include<unistd.h>
#endif

void print_desc_box(const char * testo, const int nchar){ //prints text
    int position_counter=0,i;
    while(position_counter+nchar<strlen(testo)){
        printf("\n|");
        i=nchar+1;
        while(testo[i+position_counter]!=' ') --i;
        for(int j=position_counter;j<=position_counter+i && testo[j]!='\0';j++)
            printf("%c",testo[j]);
        for(int j=i;j<nchar+1;j++) printf(" ");
        printf("|");
        position_counter+=i+1;
    };
    if(position_counter<strlen(testo)){
        printf("\n|");
        i=0;
        while(testo[position_counter+i]!='\0'){
            printf("%c",testo[position_counter+i]);
            i++;
        }
        while(nchar-i){
            printf(" ");
            i++;
        }
        printf("  |");
    }
    return;
}

void print_invisible_box(const char * testo, const int nchar){ //prints text
    int position_counter=0,i;
    while(position_counter+nchar<strlen(testo)){
        printf("\n ");
        i=nchar+1;
        while(testo[i+position_counter]!=' ') i--;
        for(int j=position_counter;j<=position_counter+i && testo[j]!='\0';j++)
            printf("%c",testo[j]);
        for(int j=i;j<nchar+1;j++) printf(" ");
        printf(" ");
        position_counter+=i+1;
    };
    if(position_counter<strlen(testo)){
        printf("\n ");
        i=0;
        while(testo[position_counter+i]!='\0'){
            printf("%c",testo[position_counter+i]);
            i++;
        }
        while(nchar-i){
            printf(" ");
            i++;
        }
        printf("   ");
    }
    return;
}

void print_dialogue_box(const char * testo, const int nchar){ //prints text
    int position_counter=0,i;
    while(position_counter+nchar<strlen(testo)){
        printf("\n<< ");
        i=nchar+1;
        while(testo[i+position_counter]!=' ') i--;
        for(int j=position_counter;j<=position_counter+i && testo[j]!='\0';j++)
            printf("%c",testo[j]);
        for(int j=i;j<nchar+1;j++) printf(" ");
        printf(">>");
        position_counter+=i+1;
    };
    if(position_counter<strlen(testo)){
        printf("\n<< ");
        i=0;
        while(testo[position_counter+i]!='\0'){
            printf("%c",testo[position_counter+i]);
            i++;
        }
        while(nchar-i){
            printf(" ");
            i++;
        }
        printf("  >>");
    }
    return;
}
void print_square_box(const char * testo, const int nchar){ //prints text
    int position_counter=0,i;
    while(position_counter+nchar<strlen(testo)){
        printf("\n[ ");
        i=nchar+1;
        while(testo[i+position_counter]!=' ') i--;
        for(int j=position_counter;j<=position_counter+i && testo[j]!='\0';j++)
            printf("%c",testo[j]);
        for(int j=i;j<nchar+1;j++) printf(" ");
        printf("]");
        position_counter+=i+1;
    };
    if(position_counter<strlen(testo)){
        printf("\n[ ");
        i=0;
        while(testo[position_counter+i]!='\0'){
            printf("%c",testo[position_counter+i]);
            i++;
        }
        while(nchar-i){
            printf(" ");
            i++;
        }
        printf("  ]");
    }
    return;
}

void printLine_noStar(int nchar){
    printf("\n ");
    for(;nchar>-2;nchar--) printf("-");
    printf(" ");
    return;
}

void print_intro(void){
    printf("\n\n\n");
    printLine_noStar(100);
    print_square_box(VERSION,100);
    printLine_noStar(100);
    printf("\n");
    printLine_noStar(100);
    print_square_box(HI,100);
    print_square_box(WELCOME,100);
    print_square_box(GAMEPLAY,100);
    print_square_box(NOTA,100);
    printLine_noStar(100);
    return;
}
void print_debug(void){
    printLine_noStar(100);
    print_square_box(DEBUG_STRING,100);
    printLine_noStar(100);
    printf("\n");
    return;
}

void print_star_box(const char * testo, const int nchar){ //prints text
    int position_counter=0,i;
    while(position_counter+nchar<strlen(testo)){
        printf("\n* ");
        i=nchar+1;
        while(testo[i+position_counter]!=' ') i--;
        for(int j=position_counter;j<=position_counter+i && testo[j]!='\0';j++)
            printf("%c",testo[j]);
        for(int j=i;j<nchar+1;j++) printf(" ");
        printf("*");
        position_counter+=i+1;
    };
    if(position_counter<strlen(testo)){
        printf("\n* ");
        i=0;
        while(testo[position_counter+i]!='\0'){
            printf("%c",testo[position_counter+i]);
            i++;
        }
        while(nchar-i){
            printf(" ");
            i++;
        }
        printf("  *");
    }
    return;
}
void print_star_Line(int nchar){
    printf("\n*");
    for(;nchar>0;nchar-=5) printf("  *  ");
    printf("*");
    return;
}
void print_dot_line(int nchar){
    printf("\n.");
    for(;nchar>-2;nchar--) printf(".");
    printf(".");
    return;
}
void print_double_dot_line(int nchar){
    printf("\n:");
    for(;nchar>-2;nchar--) printf(":");
    printf(":");
    return;
}
void printLine(int nchar){
    printf("\n*");
    for(;nchar>-2;nchar--) printf("-");
    printf("*");
    return;
}

void clean_fgets(char * stringa, int maxlenght,FILE * filename){
    fgets(stringa,maxlenght,filename);
    stringa[strlen(stringa)-1]='\0';
    return;
}

int oggetto_(char * subazione){
    int risultato;
    if(strstr(subazione,"spellbook")||strstr(subazione,"libro")||strstr(subazione,"0")) risultato= 0;
    else if(strstr(subazione,"pugnale")||strstr(subazione,"daga")) risultato= 1;
    else if(strstr(subazione,"ascia")) risultato= 2;
    else if(strstr(subazione,"martello")) risultato= 3;
    else if(strstr(subazione,"lancia")) risultato= 4;
    else if(strstr(subazione,"scudo")) risultato= 5;
    else if(strstr(subazione,"armatura")) risultato= 6;
    else if(strstr(subazione,"mappa")||strstr(subazione,"cartografo")) risultato= 7;
    else if(strstr(subazione,"scala")) risultato= 8;
    else risultato= -1;
    return risultato;
}

int incantesimo_(char * subazione){
    int risultato;
    if(strstr(subazione,"dardo")||strstr(subazione,"fuoco")||strstr(subazione,"0")) risultato=0;
    else if(strstr(subazione,"ice")||strstr(subazione,"knife")) risultato=1;
    else if(strstr(subazione,"dardo")||strstr(subazione,"missile")) risultato=2;
    else if(strstr(subazione,"infliggi")) risultato=3;
    else if(strstr(subazione,"demone")||strstr(subazione,"evoca")) risultato=4;
    else if(strstr(subazione,"armatura")||strstr(subazione,"mage")) risultato=5;
    else if(strstr(subazione,"assorbi")||strstr(subazione,"elementi")||strstr(subazione,"absorb")) risultato=6;
    else if(strstr(subazione,"scudo")) risultato=7;
    else if(strstr(subazione,"wither")||strstr(subazione,"bloom")) risultato=8;
    else if(strstr(subazione,"cura")||strstr(subazione,"cure")) risultato=9;
    else if(strstr(subazione,"luci")) risultato=10;
    else if(strstr(subazione,"sonno")) risultato=11;
    else if(strstr(subazione,"suggestione")) risultato=12;
    else if(strstr(subazione,"mano")||strstr(subazione,"hand")) risultato=13;
    else if(strstr(subazione,"cerchio")||strstr(subazione,"teletrasporto")) risultato=14;
    else risultato=-1;
    return risultato;
}
int spostamento_(char * dir){
    int risultato=-1;
    if(strstr(dir,"nord")||strstr(dir,"0")) risultato= 0;
    else if(strstr(dir,"sud")) risultato= 1;
    else if(strstr(dir,"est")&&(!strstr(dir,"ovest"))) risultato= 2;
    else if(strstr(dir,"ovest")) risultato= 3;
    else if(strstr(dir,"su")||strstr(dir,"giu")||strstr(dir,"alto")||strstr(dir,"basso")) printf("\nMa stai cercando di viaggiare nella terza dimensione?\nNon hai letto Flatlandia?\n");
    return risultato;
}

int azione_ (char * action){
    int azione;
    if((strstr(action,"guarda"))||strstr(action,"osserva")||strstr(action,"look")||strstr(action,"indaga")||strstr(action,"descrivi")) azione=1;
    else if((strstr(action,"usa")&&!strstr(action,"incantesimo"))||strstr(action,"use")) azione=2;
    else if(strstr(action,"lancia")||strstr(action,"cast")) azione=3;
    else if(strstr(action,"vai")||strstr(action,"move")||strstr(action,"muovi")||strstr(action,"sposta")) azione=4;
    else if(strstr(action,"raccogli")||strstr(action,"prendi")) azione=5;
    else if(strstr(action,"impara")||strstr(action,"scopri")) azione=6;
    else if(strstr(action,"spiega")) azione=7;
    else if(strstr(action,"studia")) azione=8;
    else if(strstr(action,"soldi")||strstr(action,"finanze")||strstr(action,"portafogli")) azione=9;
    else if(strstr(action,"salva")) azione=10;
    else if(strstr(action,"carica")) azione=11;
    else if(strstr(action,"esci")||strstr(action,"exit")) azione=12;
    else if(strstr(action,"setting")||strstr(action,"impostazioni")) azione=13;
    else azione=-1;
    if(strstr(action,"quarantadue")) printf("\nApplausi, sai la risposta alla domanda fondamentale\n");
    if(strstr(action,"ciao")) printf("\nCiao anche a te\n");
    return azione;
}

int scelta_(char * s){
    int returnValue=0;
    if(strstr(s,"si")) returnValue=1;
    return returnValue;
}
int attack_(char * s){
    int returnValue;
    if(strstr(s,"dardo")||strstr(s,"fuoco")) returnValue= 0;
    else if (strstr(s,"evoca")||strstr(s,"demone")) returnValue=4;
    else if(strstr(s,"ice")) returnValue=1;
    else if(strstr(s,"martello")||strstr(s,"nord")) returnValue=7;
    else if(strstr(s,"dardo")||strstr(s,"missile")) returnValue=2;
    else if(strstr(s,"lancia")||strstr(s,"devastazione")) returnValue=8;
    else if(strstr(s,"infliggi")||strstr(s,"feri")) returnValue=3;
    else if(strstr(s,"pugnale")||strstr(s,"daga")) returnValue=5;
    else if(strstr(s,"ascia")) returnValue=6;
    else returnValue=-1;
    return returnValue;
}

int defense_(char * stringa){
    int returnValue=-1;
    if(strstr(stringa, "scudo")&&strstr(stringa,"incantesimo")) returnValue=2;
    else if(strstr(stringa,"scudo")&&strstr(stringa, "oggetto")) returnValue= 3;
    else if(strstr(stringa,"armatura")&&strstr(stringa,"magica")) returnValue=0;
    else if(strstr(stringa,"assorbi")||strstr(stringa, "elementi")) returnValue=1;
    else if(strstr(stringa,"armatura")&&strstr(stringa,"oggetto")) returnValue=4;
    return returnValue;
}

int escape_(char * scelta){
    int returnValue=-1;
    if(atoi(scelta)) returnValue=atoi(scelta);
    else if (strstr(scelta, "luci")||strstr(scelta, "danzanti")) returnValue=0;
    else if(strstr(scelta,"sonno")) returnValue=1;
    else if(strstr(scelta,"suggestione")) returnValue=2;
    return returnValue;
}

int decode (char * string, int (*mode)(char *)){
    for(int i=0;i<strlen(string);i++) string[i]=tolower(string[i]);
    return (*mode)(string);
}
void ask(char * testo){
    printf("\n$ ");
    printf("%s",testo);
    printf(" > ");
    return;
}
void print_credits(void){
    printLine_noStar(100);
    print_square_box(CREDITS1,100);
    print_square_box(CREDITS2,100);
    printLine_noStar(100);
    return;
}
void printSettings(sett* settings){
    printf("\n********** IMPOSTAZIONI **********");
    printSet("Audio           :",settings->audioOn);
    printSet("Incontri Casuali:",settings->randomEncounters);
    //STILL TO COMPLETE
    return;
}
void printSet(char* setting, short isOn){
    char stringa[100]="";
    strcat(stringa,"\n>>\t");
    strcat(stringa,setting);
    if(isOn) strcat(stringa,"\ton[#]\toff[.]\t<<");
    else strcat(stringa,"\ton[.]\toff[#]\t<<");
    printf("%s",stringa);
    return;
}

void bell(int times, sett* settings){
    if(settings->audioOn){
        printf("\a");
        fflush(stdout);
        for(int i=0;(settings->audioOn)&&(i<times-1);i++){
            #ifdef WINDOWS
                Sleep(1000);
            #else
                sleep(1);
                //printf("\nBEEP");
            #endif
            printf("\a");
            fflush(stdout);
        }
    }
    return;
}
void change_settings(sett*settings){
    printSettings(settings);
    short exit=0;
    char stringa[100];
    while(!exit){
        ask("Inserisci cosa vuoi cambiare (\"esci\" per uscire)");
        scanf("%s",stringa);
        for(int i=0;i<strlen(stringa);i++){
            stringa[i]=tolower(stringa[i]);
        }
        if(strstr(stringa,"audio")) settings->audioOn=(settings->audioOn?0:1);
        else if(strstr(stringa,"esci")||strstr(stringa,"exit")) exit=1;
        else if(strstr(stringa,"incontri")||strstr(stringa,"casuali")) settings->randomEncounters=(settings->randomEncounters?0:1);
        else printf("\nNON RICONOSCIUTO.\nInserisci \"esci\" per uscire dalle impostazioni");
        printSettings(settings);
    }
}