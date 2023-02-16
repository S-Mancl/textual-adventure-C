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


int rolld(int a){//function to roll a die with a possible outputs. For exampe, rolld(10) rolls 1d10
    int b=(rand()%a)+1;
    printf("\n[%d]",b);
    return b;
}
int get_gold_pieces(int portafogli){//function to compute the number of gold pieces in one's inventory
    int gp=portafogli;
    gp-=(gp%100);
    return gp;
}
int get_silver_pieces(int portafogli){//function to compute the number of silver pieces in one's inventory
    int sp=(portafogli);
    sp=sp/10;
    sp=sp%10;
    return sp;
}
int get_copper_pieces(int portafogli){//function to compute the number of copper pieces in one's inventory
    int cp=(portafogli%10);
    return cp;
}
void print_map( const map * mappa){//function to print a list of all the places
    int i;
    for(i=0;i<NPLACE;i++){
        printf("\n>     %d.%s",i,mappa->place[i].nome);
    }
    return;
}
int save_to_file(const map * mappa, const inv * invent, const spbook * spb, const int *current, const int *previous,const int *portafogli){//function to save the current status in a file
    int i;
    char filename[40];
    char file[70]="src/txts/savefiles/";
    printf("\n>Inserisci (senza spazi) il nome del file nel quale vuoi salvare\nSono ammesse solo lettere minuscole\nConsigliato: il tuo nome");
    ask("nome del file");
    scanf("%s",filename);
    clean(filename);
    strcat(file,filename);
    strcat(file,".txt");
    FILE * savefile=fopen(file,"w");
    for(i=0;i<NITEM;i++){
        fprintf(savefile,"%d\n",spb->spell[i].known);
        fprintf(savefile,"%d\n",invent->oggetto[i].available);
    }
    for(i=0;i<NPLACE;i++){
        fprintf(savefile,"%d\n",mappa->place[i].status);
        fprintf(savefile,"%d\n",mappa->place[i].is_encounter_location);
        fprintf(savefile,"%d\n",mappa->place[i].objAvailable);
        fprintf(savefile,"%d\n",mappa->place[i].spellAvailable);
    }
    fprintf(savefile,"%d\n",*current);
    fprintf(savefile,"%d\n",*portafogli);
    fprintf(stdout,"\nSalvataggio avvenuto correttamente");
    return fclose(savefile);;
}
void clean (char * filename){//ensures that the name respects the whitelist
    for(int i=0;i<strlen(filename)-1;i++){
        if(filename[i]<97||filename[i]>122) filename[i]='_';
    }
    printf("\n Il nome che abbiamo accettato e': %s",filename);
    return;
}

int load_from_file( map * mappa, inv * invent, spbook * spb,int *current,int *previous,int *portafogli){//same as save from file, but in the opposite direction
    int i;
    char filename[40];
    char file[70]="src/txts/savefiles/";
    printf("\n>Inserisci (senza spazi) il nome del file nel quale vuoi salvare\nProbabilmente: il tuo nome\nSE NON HAI ANCORA GIOCATO NON PUOI AVER SALVATO COSE");
    ask("nome del file");
    scanf("%s",filename);
    clean(filename);
    strcat(file,filename);
    strcat(file,".txt");
    FILE * savefile;
    if((savefile=fopen(file,"r"))==NULL){
        printf("\nERROR OPENING FILE");
    }
    else{
        for(i=0;i<NITEM;i++){
            fscanf(savefile,"%d",&(spb->spell[i].known));
            fscanf(savefile,"%d",&(invent->oggetto[i].available));
        }
        for(i=0;i<NPLACE;i++){
            fscanf(savefile,"%d",(int*)&(mappa->place[i].status));
            fscanf(savefile,"%d",&(mappa->place[i].is_encounter_location));
            fscanf(savefile,"%d",&(mappa->place[i].objAvailable));
            fscanf(savefile,"%d",&(mappa->place[i].spellAvailable));
        }
        fscanf(savefile,"%d",current);
        fscanf(savefile,"%d",portafogli);
        fprintf(stdout,"\nCaricamento avvenuto correttamente");
        return fclose(savefile);
    }
    return 0;
}
int regen_money(map * mappa){//regenerates the random copper pieces that can be found. globally.
    int i;
    for(i=0;i<NPLACE;i++){
        if(mappa->place[i].regen_ratio){
            if((rand()%20)>mappa->place[i].regen_ratio){
                mappa->place[i].is_there_money=mappa->place[i].regen_ratio;
            }
        }
    }
    return 0;
}
void learn(spel * spell, char * nome, char * descrizione, char * effetto, element  elemento, char * fallimento){//with this function the game loads a spell
    strcpy(spell->nome,nome);
    strcpy(spell->descrizione,descrizione);
    strcpy(spell->effetto,effetto);
    spell->elemento=elemento;
    strcpy(spell->fallimento,fallimento);
    printf(".");
    return;
}
void load(item * oggetto, char * nome, char * descrizione, char * uso, char * fallimento){//with this function the game loads an item
    strcpy(oggetto->nome,nome);
    strcpy(oggetto->descrizione,descrizione);
    strcpy(oggetto->uso,uso);
    strcpy(oggetto->fallimento,fallimento);
    printf(".");
    return;
}
void createPlace(posto * place, char * nome, char * descrizione, int N, int S, int E, int O, char* desc0, char * desc1, char * desc2, char * desc3, char*move0,char *move1, char*move2, char*move3, int objavail, int objcode){//with this function the game loads a place
    strcpy(place->nome,nome);
    strcpy(place->descrizione[0],descrizione);
    place->dir[0]=N;
    place->dir[1]=S;
    place->dir[2]=E;
    place->dir[3]=O;
    strcpy(place->transition_description[0],desc0);
    strcpy(place->transition_description[1],desc1);
    strcpy(place->transition_description[2],desc2);
    strcpy(place->transition_description[3],desc3);
    strcpy(place->moves_description[0],move0);
    strcpy(place->moves_description[1],move1);
    strcpy(place->moves_description[2],move2);
    strcpy(place->moves_description[3],move3);
    place->objAvailable=objavail;
    place->availableObjCode=objcode;
    return;
}
void altStatus(posto * place, stato current_status, char * firedesc, char * icedesc, char * devdesc,char * availableObjDescr, int spellAvailable, int codeSpell,int money,int regen){//and with this one it completes the place
    strcpy(place->descrizione[1],firedesc);
    strcpy(place->descrizione[2],icedesc);
    strcpy(place->descrizione[3],devdesc);
    place->status=current_status;
    strcpy(place->descrAvailableObj,availableObjDescr);
    place->codeSpell=codeSpell;
    place->spellAvailable=spellAvailable;
    place->is_there_money=money;
    place->regen_ratio=regen;
    printf(".");
    return;
}
void print_item_desc(const inv * invent, int subaction){//this way a description of an item is printed
    if(!(invent->oggetto[subaction].available)){
        print_star_Line(100);
        print_star_box(ECHILOSA,100);
        print_star_Line(100);
    }
    else{
        print_star_Line(100);
        print_star_box(invent->oggetto[subaction].descrizione,100);
        print_star_Line(100);
    }
    return;
}
void print_spell_desc(const spbook * spb, int subaction){//same as above, but with spells
    if(!(spb->spell[subaction].known)){
        print_star_Line(100);
        print_star_box(ECHILOSA,100);
        print_star_Line(100);
    }
    else{
        print_star_Line(100);
        print_star_box(spb->spell[subaction].descrizione,100);
        print_star_Line(100);
    }
    return;
}
void print_spell_name(const spbook * spb, int subaction){//prints the name of a spell
    printf("\n> %d.%s",subaction,spb->spell[subaction].nome);
    return;
}
void print_item_name(const inv * invent, int subaction){//prints the name of an item
    printf("\n> %d.%s",subaction,invent->oggetto[subaction].nome);
    return;
}
void print_inventory(const inv * invent){//prints the inventory
    int i, status=0;
    printf("\n> Scegli l'item da usare");
    for(i=0;i<NITEM;i++)
        if(invent->oggetto[i].available==1){
            print_item_name(invent,i);
            status=1;
        }
    if(!status) printf("\n> Non hai oggetti nell'inventario");
    return;
}
void print_spellbook(const spbook * spb){//prints the contents of the spellbook
    int i, status=0;
    printf("\nScegli l'incantesimo da usare");
    for(i=0;i<NITEM;i++)
        if(spb->spell[i].known){
            print_spell_name(spb, i);
            status=1;
        }
    if(!status) printf("\nNon hai incantesimi nello spellbook");
    return;
}
void print_possibleMoves(const posto * loc){//prints the possible directions
    printf("\n  0.Nord. %s",loc->moves_description[0]);
    printf("\n  1.Sud. %s",loc->moves_description[1]);
    printf("\n  2.Est. %s",loc->moves_description[2]);
    printf("\n  3.Ovest. %s",loc->moves_description[3]);
    return;
}
int ask_for_object(void){//asks for an object
    int subaction;
    char subazione[100];
    ask("Inserisci il numero o il nome dell'oggetto");
    fgets(subazione,100,stdin);
    if(atoi(subazione)) subaction=atoi(subazione);
    else subaction=decode(subazione,oggetto_);
    return subaction;
}

int ask_for_spell(void){//asks for a spell
    int subaction;
    char subazione[100];
    ask("Inserisci il numero o il nome dell'incantesimo");
    fgets(subazione,100,stdin);
    if(atoi(subazione)) subaction=atoi(subazione);
    else subaction=decode(subazione,incantesimo_);
    return subaction;
}

int ask_for_dir(void){//asks for a direction
    int subaction;
    char azione[100];
    ask("Inserisci la direzione in cui vuoi andare");
    fgets(azione,100,stdin);
    if(atoi(azione)) subaction= atoi(azione);
    else subaction=decode(azione,spostamento_);
    return subaction;
}

void print_possibleActions(void){//prints all the possible actions
    printf("\n\n> Ecco alcuni esempi di azioni che puoi fare:");
    printf("\n     1. \tOsserva");
    printf("\n     2. \tUsa [Usa un oggetto]");
    printf("\n     3. \tLancia [un incantesimo]");
    printf("\n     4. \tVai [a]");
    printf("\n     5. \tRaccogli [(eventuali) oggetti]");
    printf("\n     6. \tImpara [(eventuali) incantesimi]");
    printf("\n     7. \tSpiega [un oggetto]");
    printf("\n     8. \tStudia [spiega un incantesimo]");
    printf("\n     9. \tFinanze [Guarda lo stato delle tue finanze]");
    printf("\n     10.\tSalva [lo stato attuale]");
    printf("\n     11.\tCarica [uno dei salvataggi]");
    printf("\n     12.\tEsci [dal gioco]");
    printf("\n     13.\tImpostazioni");
    return;
}
int get_action(void){//gets an action
    int action;
    char azione[100];
    printf("\n\n");
    ask("Inserisci la tua azione");
    scanf("%s%*c",azione);
    if(atoi(azione)) action= atoi(azione);
    else action=decode(azione,azione_);
    return action;
}
int ask_again(void){//asks again
    int action;
    printf("\n>Non e' una mossa valida. Inserire nuovamente:");
    action=get_action();
    return action;
}
int call_sub_prompt(int *action, map * mappa, inv * invent, spbook * spb, int * current){ //function to call sub prompt to get sub action
    int subaction=0;
    switch (*action){
        case 2:
        case 7:
            print_inventory(invent);
            subaction=ask_for_object();
            break;
        case 3:
        case 8:
            print_spellbook(spb);
            subaction=ask_for_spell();
            break;
        case 4:
            print_possibleMoves(&(mappa->place[*current]));
            subaction=ask_for_dir();
            break;
    }
    return subaction;
}
int check_input(int action, int subaction,map * mappa,inv * invent, spbook * spb,int current){//checkes if the input is fine
    int fine=1;//everything is fine
    switch(action){
        case 2:
        case 7:
            if((subaction<0||subaction>8)||!(invent->oggetto[subaction].available)){
                printf(NOTAVAILABLE_OBJ);
                fine=0;
            }
            break;
        case 3:
        case 8:
            if((subaction<0||subaction>14)||!(spb->spell[subaction].known)){
                printf(NOTAVAILABLESP);
                fine=0;
            }
            break;
        case 4:
            if((subaction<0)||(subaction>3)){
                printf(INVALIDMOVE);
                fine=0;
            }
            break;
        case 5:
            if(!(mappa->place[current].objAvailable)){
                printf(NOTAVAILABLEOBJ);
                fine=0;
            }
            break;
        case 6:
            if(!(mappa->place[current].spellAvailable)){
                printf(NOTAVAILABLE_SPELL);
                fine=0;
            }
        break;
    }
    if(fine) trentatre();
    return fine;
}

void prompt(int* action, int * subaction, map * mappa, inv * invent, spbook * spb, int * current){//asks for an action
    int i=0;
    print_possibleActions();
    (*action)=get_action();
    while((*action<1||*action>13)&&(i++<5)){
        *action=ask_again();
    }
    *subaction=call_sub_prompt(action, mappa, invent, spb, current);
    return;
}
void cast_spell(int action, int subaction, map * mappa, inv * invent, spbook * spb, int * current, int * previous){//executes the "cast a spell" command
    int a;
    int b;
    b=rolld(20);
    switch (subaction)
    {
    case 0:
        print_invisible_box(spb->spell[subaction].effetto,100);
        mappa->place[*current].status=bruciata;
        piromane();
        break;
    case 1:
        print_invisible_box(spb->spell[subaction].effetto,100);
        mappa->place[*current].status=ghiacciata;
        break;
    case 2:
        print_invisible_box(spb->spell[subaction].effetto,100);
        mappa->place[*current].status=devastata;
        break;
    case 3:
        print_invisible_box(spb->spell[subaction].effetto,100);
        mappa->place[*current].status=devastata;
        break;
    case 4:
        print_invisible_box(spb->spell[subaction].effetto,100);
        mappa->place[*current].status=bruciata;
        break;
    case 5:
        print_invisible_box(spb->spell[subaction].effetto,100);
        break;
    case 6:
        print_invisible_box(spb->spell[subaction].effetto,100);
        break;
    case 7:
        print_invisible_box(spb->spell[subaction].effetto,100);
        break;
    case 8:
        print_invisible_box(spb->spell[subaction].effetto,100);
        mappa->place[*current].status=devastata;
        break;
    case 9:
        print_invisible_box(spb->spell[subaction].effetto,100);
        mappa->place[*current].status=normale;
        break;
    case 10:
        print_invisible_box(spb->spell[subaction].effetto,100);
        break;
    case 11:
        print_invisible_box(spb->spell[subaction].effetto,100);
        break;
    case 12:
        print_invisible_box(spb->spell[subaction].effetto,100);
        break;
    case 13:
       if(mappa->place[*current].objAvailable!=2) print_invisible_box(spb->spell[13].fallimento,100);
       else {
            print_invisible_box(spb->spell[subaction].effetto,100);
            mappa->place[*current].objAvailable=1;
       }
        break;
    case 14:
        ask("Insert code of target destination");
        scanf("%d%*c",&a);
        if(b>=3){
            if(((*current)==a)||((a)<0)||((a)>NPLACE)){
                print_invisible_box(spb->spell[subaction].fallimento,100);
            }
            else{
                teletrasporto_();
                print_invisible_box(spb->spell[subaction].effetto,100);
                (*current)=a;
            }
        }else printf(DICENOTAPPROVED);
        break;
    }
}
void use_item(int action, int subaction, map *mappa, inv *invent, spbook * spb, int current, int previous){//executes the "use an item" command
    int a,b;
    b=rolld(20);
    switch (subaction)
    {
        case 0:
            print_invisible_box(invent->oggetto[subaction].uso,100);
            break;
        case 1:
            print_invisible_box(invent->oggetto[subaction].fallimento,100);
            break;
        case 2:
            print_invisible_box(invent->oggetto[subaction].uso,100);
            mappa->place[current].status=devastata;
            break;
        case 3:
            print_invisible_box(invent->oggetto[subaction].uso,100);
            mappa->place[current].status=ghiacciata;
            break;
        case 4:
            print_invisible_box(invent->oggetto[subaction].uso,100);
            mappa->place[current].status=devastata;
            break;
        case 5:
            print_invisible_box(invent->oggetto[subaction].uso,100);
            break;
        case 7:
            print_invisible_box(invent->oggetto[subaction].uso,100);
            if(b>5) {
                print_map(mappa);
                printf("\n");
                printf(MAPPA_ASCII_ART);
            }
            else print_invisible_box(invent->oggetto[subaction].fallimento,100);
            break;
        case 8:
            if(mappa->place[current].objAvailable!=2) print_invisible_box(invent->oggetto[subaction].fallimento,100);
            else {
                print_invisible_box(invent->oggetto[subaction].uso,100);
                mappa->place[current].objAvailable=1;
            }
        break;
        default:
            break;
    }
    return;
}
void try_get_item(map * mappa, int current,inv * invent){
    if(mappa->place[current].objAvailable==2){
        printf(TOOFAR);
    }
    else{
        invent->oggetto[mappa->place[current].availableObjCode].available=1;
        mappa->place[current].objAvailable=0;
        printf("\n> Hai preso un oggetto! Guardane la descrizione e prova a usarlo!");
    }
    return;
}
void try_get_spell(map* mappa, int current, spbook* spb){
    if(mappa->place[current].spellAvailable){
            spb->spell[mappa->place[current].codeSpell].known=1;
            mappa->place[current].spellAvailable=0;
            printf("\n> Hai imparato un incantesimo! Guardane la descrizione e prova a usarlo!");
    }
    return;
}
void move(int *current, map * mappa, int subaction){
    printf("\n%s",mappa->place[*current].transition_description[subaction]);
    if((*current)==mappa->place[*current].dir[subaction]) cento_posti();
    *current=mappa->place[*current].dir[subaction];
    return;
}
void print_financial_status(const int* portafogli){
    printf("\nIl tuo portafoglio e' costituito da quanto segue:");
    printf("\n  Monete d'oro: %d",get_gold_pieces(*portafogli));
    printf("\n  Monete d'argento: %d",get_silver_pieces(*portafogli));
    printf("\n  Monete di rame: %d",get_copper_pieces(*portafogli));
    return;
}
void exec_input(int action, int subaction, map* mappa, inv * invent, spbook * spb,int * current, int * previous, int * portafogli,int* we_re_playing,sett*settings){
    *previous=*current;
    if(action==12) *we_re_playing=0;
    else{ switch(action){
        case 1:
            *previous=-1;
            break;
        case 2:
            use_item(action,subaction,mappa,invent,spb,*current,*previous);
            break;
        case 3:
            cast_spell(action,subaction,mappa,invent,spb,current,previous);
            break;
        case 4:
            move(current,mappa,subaction);
            break;
        case 5:
            try_get_item(mappa,*current,invent);
            break;
        case 6:
            try_get_spell(mappa,*current,spb);
            break;
        case 7:
            print_item_desc(invent,subaction);
            break;
        case 8:
            print_spell_desc(spb,subaction);
            break;
        case 9:
            print_financial_status(portafogli);
            break;
        case 10:
            save_to_file(mappa, invent, spb, current, previous, portafogli);
            break;
        case 11:
            load_from_file(mappa, invent, spb, current, previous,portafogli);
            break;
        case 13:
            change_settings(settings);
            break;
    }
    *we_re_playing=1;}
    return;
}
void describe_desc_status(int * current, map * mappa){
    print_desc_box(mappa->place[*current].descrizione[mappa->place[*current].status],100);
    return;
}
int is_to_tell(int * current, int * previous, map * mappa, int * prevStatus){
    return ((*previous!=*current)||(*prevStatus!=mappa->place[*current].status));
}
int there_is_obj(map* mappa,int * current){
    return mappa->place[*current].objAvailable;
}
int there_is_spell(map* mappa, int * current){
    return mappa->place[*current].spellAvailable;
}
void describe_presence_obj(map* mappa,int current,sett* settings){
    bell(1,settings);
    print_desc_box(mappa->place[current].descrAvailableObj,100);
    return;
}
void describe_presence_spell(sett*settings){
    bell(1,settings);
    print_desc_box(SPELLTOLEARN,100);
    return;
}
int is_random_enc_loc(map * mappa, int current){
    int returnValue;
    if(mappa->place[current].is_encounter_location == -1) returnValue=1;
    else returnValue=0;
    return returnValue;
}
int encCode(map* mappa, int current){
    return mappa->place[current].encounter_code;
}
void print_local_money(map * mappa, int current){
    char q[300];
    sprintf(q,"Trovi: %d pezzi di rame, %d pezzi d'argento e %d pezzi d'oro",get_copper_pieces(mappa->place[current].is_there_money),get_silver_pieces(mappa->place[current].is_there_money),get_gold_pieces(mappa->place[current].is_there_money));
    print_desc_box(q,100);
    return;
}
void describe(int * current, int * previous, map * mappa, int * prevStatus, inv * invent, spbook * spb,sett* settings){
    printLine(100);
    print_desc_box(mappa->place[*current].nome,100);
    if(is_to_tell(current, previous, mappa, prevStatus))    describe_desc_status(current, mappa);
    if(there_is_obj(mappa,current))                         describe_presence_obj(mappa,*current,settings);
    if(there_is_spell(mappa, current))                      describe_presence_spell(settings);
    if(is_random_enc_loc(mappa,*current)&&((rand()%20>12))&&(settings->randomEncounters))   trigger_random_encounter(encCode(mappa, *current));
    if(mappa->place[*current].is_there_money)               print_local_money(mappa,*current);
    printLine(100);
    return;
}
void get_local_money(int * portafogli, map * mappa, int current){
    (*portafogli)+=mappa->place[current].is_there_money;
    mappa->place[current].is_there_money=0;
    return;
}
int is_encounter_location(map * mappa, int current){
    int a=0;
    if(mappa->place[current].is_encounter_location==1) a=1;
    return a;
}
void mainLoop(int * action, int * subaction, inv * invent, spbook * spb, int * current, int * previous, map * mappa, int * prevStatus, int * died, bestiary * bestiario, int * portafogli, sett * settings){
    int we_re_playing=1;
    while(we_re_playing){
        describe(current, previous, mappa, prevStatus, invent, spb,settings);
        *prevStatus=mappa->place[*current].status;
        get_local_money(portafogli, mappa, *current);
        regen_money(mappa);
        if(is_encounter_location(mappa,*current)) encounter(mappa,current,invent,spb,bestiario,died,settings);
        if(!(*died)){
            getchar();
            prompt(action,subaction, mappa, invent, spb,current);
            if(check_input(*action, *subaction,mappa, invent,spb, *current)==1) exec_input(*action,*subaction,mappa, invent, spb, current, previous, portafogli,&we_re_playing,settings);
        }
        else{
            we_re_playing=0;
            bell(3,settings);
        } 
    }
}
void setup_item_spells(inv* inventario, spbook* spellbook){
    printf("\nPreparing objects and spells:  [");
    int i;
    for(i=0;i<NITEM;i++) {
        spellbook->spell[i].known=inventario->oggetto[i].available=0; //sets all possible spells as NOT KNOWN & //sets all possible objects as NOT AVAILABLE = NOT IN POSSESSION
        printf("...");
    }
    printf("..............]");
    return;
}

void piromane(void){
    static int i;
    i++;
    if(i==10) {
        print_invisible_box("SESSION ACHIEVEMENT UNLOCKED",100);
        print_invisible_box("Hai sbloccato l'achievement di sessione (ovvero la prossima volta che chiudi, anche se fai il load, lo perdi) di:",100);
        print_invisible_box("PIROMANE: Hai lanciato con successo Dardo di fuoco 10 volte",100);
    }
    return;
}

void teletrasporto_(void){
    static int i;
    i++;
    if(i==5) {
        print_invisible_box("SESSION ACHIEVEMENT UNLOCKED",100);
        print_invisible_box("Hai sbloccato l'achievement di sessione (ovvero la prossima volta che chiudi, anche se fai il load, lo perdi) di:",100);
        print_invisible_box("TELETRASPORTO: Ti sei teletrasportato con successo 5 volte",100);
    }
    return;
}


void trentatre(void){
    static int i;
    i++;
    if(i==33) {
        print_invisible_box("SESSION ACHIEVEMENT UNLOCKED",100);
        print_invisible_box("Hai sbloccato l'achievement di sessione (ovvero la prossima volta che chiudi, anche se fai il load, lo perdi) di:",100);
        print_invisible_box("AZIONI: Hai eseguito 33 azioni",100);
    }
    return;
}


void cento_posti(void){
    static int i;
    i++;
    if(i==100) {
        print_invisible_box("SESSION ACHIEVEMENT UNLOCKED",100);
        print_invisible_box("Hai sbloccato l'achievement di sessione (ovvero la prossima volta che chiudi, anche se fai il load, lo perdi) di:",100);
        print_invisible_box("GIRAMONDO: Hai viaggiato 100 volte",100);
    }
    return;
}

void setup(map * mappa, bestiary * bestiario, inv * inventario, spbook * spellbook){
    FILE * data=fopen("src/txts/data/data.txt","r");
    char stringhe[10][DESCRLENG];
    int num,a[10],b[10],v[10],i;
    /*Creation of places*/
    fprintf(stdout,"\n\nLoading map:                   [");
    for(i=0;i<NPLACE;i++){
        fscanf(data,"%d%*c",&num);
        clean_fgets(stringhe[0],NMLENG,data);
        clean_fgets(stringhe[1],DESCRLENG,data);
        fscanf(data,"%d %d %d %d%*c",&a[0],&a[1],&a[2],&a[3]);
        clean_fgets(stringhe[2],DESCRLENG,data);
        clean_fgets(stringhe[3],DESCRLENG,data);
        clean_fgets(stringhe[4],DESCRLENG,data);
        clean_fgets(stringhe[5],DESCRLENG,data);
        clean_fgets(stringhe[6],DESCRLENG,data);
        clean_fgets(stringhe[7],DESCRLENG,data);
        clean_fgets(stringhe[8],DESCRLENG,data);
        clean_fgets(stringhe[9],DESCRLENG,data);
        fscanf(data,"%d %d%*c",&v[0],&v[1]);
        createPlace(&(mappa->place[i]),stringhe[0],stringhe[1],a[0],a[1],a[2],a[3],stringhe[2],stringhe[3],stringhe[4],stringhe[5],stringhe[6],stringhe[7],stringhe[8],stringhe[9],v[0],v[1]);
        fscanf(data,"%d%*c",&a[0]);
        clean_fgets(stringhe[0],DESCRLENG,data);
        clean_fgets(stringhe[1],DESCRLENG,data);
        clean_fgets(stringhe[2],DESCRLENG,data);
        clean_fgets(stringhe[3],DESCRLENG,data);
        fscanf(data,"%d %d %d %d%*c",&a[1],&a[2],&a[3],&a[4]);
        altStatus(&(mappa->place[i]),a[0],stringhe[0],stringhe[1],stringhe[2],stringhe[3],a[1],a[2],a[3],a[4]);
    }
    fprintf(stdout,"]");
    /*Creation of encounters*/
    printf("\nCreating encounters:           [");
    for(i=0;i<NPLACE;i++){
        fscanf(data,"%d %d%*c",&a[0],&a[1]);
        setEncounter(&(mappa->place[i]),a[0],a[1]);
    }
    printf("]");
    /*Creation of bestiary*/
    printf("\nLoading bestiary:              ["); 
    for(i=0;i<4;i++){
        clean_fgets(stringhe[0],NMLENG,data);
        clean_fgets(stringhe[1],DESCRLENG,data);
        fscanf(data,"%d %d%*c%d %d %d %d %d%*c%d %d %d %d %d %d%*c",&v[0],&v[1],&a[0],&a[1],&a[2],&a[3],&a[4],&b[0],&b[1],&b[2],&b[3],&b[4],&b[5]);
        newNPC(&(bestiario->character[i]),stringhe[0],stringhe[1],v[0],v[1]);
        caratteristiche(&(bestiario->character[i]),a[0],a[1],a[2],a[3],a[4]);
        vitaResistenze(&(bestiario->character[i]),b[0],b[1],b[2],b[3],b[4],b[5]);
    }
    printf("]");
    /*Creation of items*/
    printf("\nLoading items:                 [");
    for(i=0;i<9;i++){
        clean_fgets(stringhe[0],NMLENG,data);
        clean_fgets(stringhe[1],DESCRLENG,data);
        clean_fgets(stringhe[2],DESCRLENG,data);
        clean_fgets(stringhe[3],DESCRLENG,data);
        load(&(inventario->oggetto[i]),stringhe[0],stringhe[1],stringhe[2],stringhe[3]);
    }
    printf("]");
    /*Creation of spells*/
    printf("\nLoading spells:                [");
    for(i=0;i<15;i++){
        clean_fgets(stringhe[0],NMLENG,data);
        clean_fgets(stringhe[1],DESCRLENG,data);
        clean_fgets(stringhe[2],DESCRLENG,data);
        fscanf(data,"%d%*c",&a[0]);
        clean_fgets(stringhe[3],DESCRLENG,data);
        learn(&(spellbook->spell[i]),stringhe[0],stringhe[1],stringhe[2],a[0],stringhe[3]);
    }
    printf("]");
    fclose(data);
    /*setup of inventory and spellbook*/
    setup_item_spells(inventario,spellbook);
}
