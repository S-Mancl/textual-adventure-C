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

void print_life(life life_NPC, life salute){
    int i;
    printLine(17);
    printf("\nSalute NPC: [");
    for(i=0;i<life_NPC;i++) printf("#");
    for(i=life_NPC;i<5;i++) printf(".");
    printf("]");
    printf("\nTua salute: [");
    for(i=0;i<salute;i++) printf("#");
    for(i=salute;i<5;i++) printf(".");
    printf("]");
    printLine(17);
    return;
}

void random_question(int * vite){
    char question[120], answr[4][120];
    int answer, i,q, users_answer, question_number=rand()%NUMQUESTION,exit_=0;
    //fprintf(stdout,"\n%d",question_number);
    FILE * questions = fopen("src/txts/data/questions.txt","r");
    for(i=0;i<NUMQUESTION&&(!exit_);i++){
        fscanf(questions,"%d %d%*c",&q,&answer);
        fgetc(questions);
        clean_fgets(question,120,questions);
        for(int j=0;j<=3;j++)
            clean_fgets(answr[j],120,questions);
        if(q==question_number){
            print_dialogue_box("Rispondi a questa domanda:",100);
            printf("\n\n%s\n",question);
            print_dot_line(100);
            for(int j=0;j<=3;j++){
                printf("\n   %d.  %s",j,answr[j]);
            }
            ask("Inserisci la tua risposta");
            fscanf(stdin,"%d%*c",&users_answer);
            if(answer==users_answer){
                printf("\nEh gia'. Funziona proprio in questo modo. La realta' e' assurda");
            }
            else {
                printf("\nHai sbagliato! PERDI UNA VITA: te ne rimangono %d",--(*vite));
            }
            print_double_dot_line(100);
            exit_=1;
        }
    }
    fclose(questions);
    return;
}
void start_quiz(map * mappa, int * current, inv * inventario, spbook * spb,bestiary * bestiario, int * died){
    printf("\n%s",bestiario->character[mappa->place[*current].encounter_code].descrizione);
    printf("\nEd esso inizia a dire:\n");
    print_dialogue_box("Dato che non ti voglio male ti sottoporro' solo un quiz.Se lo passi buon per te, ti lascero' andare, altrimenti iniziera' una sfida. L'argomento? Teoria dell'arcano, e' ovvio",100);
    int vite=3, counter=8;
    print_dialogue_box("Hai 3 vite, e ti saranno fatte 8 domande. Se sbagli una risposta perdi una vita, altrimenti procedi. Se arrivi in fondo con un numero positivo di vite allora ti lascero' andare",100);
    while((vite!=0)&&(counter>0)){
        random_question(&vite);
        printf("\nDai che te ne mancano: %d",--counter);
    }
    if(vite<=0) fight(mappa,current, inventario, spb,bestiario, died);
    else printf("\nHai superato il quiz!");
    printf("\nComplimenti, giovane arcanista. Non ti disturbero' piu'... in questa localita'");
    mappa->place[*current].is_encounter_location=0;
    return;
}


void newNPC(personaggio * NPC, char * nome, char* descrizione,type categoria, orient orientamento){
    strcpy(NPC->nome,nome);
    strcpy(NPC->descrizione,descrizione);
    NPC->categoria=categoria;
    NPC->orientamento=orientamento;
    printf(".");
    return;
}
void caratteristiche(personaggio *NPC, int inte,int forz, int dex, int vol, int cos){
    NPC->intelligenza=inte;
    NPC->forza=forz;
    NPC->destrezza=dex;
    NPC->volonta=vol;
    NPC->costituzione=cos;
    printf(".");
    return;
}
void vitaResistenze(personaggio *NPC, resistenza fred,resistenza cald,resistenza fisic, resistenza necro, resistenza forz, life sal){
    NPC->iceresist=fred;
    NPC->fisicresist=fisic;
    NPC->fireresist=cald;
    NPC->forceresist=forz;
    NPC->necroresist=necro;
    NPC->salute=sal;
    printf(".");
    return;
}

void trigger_random_encounter(int encounter_code){
    int b=rand()%8,a,c,toexit=0;
    char stringa[200];
    FILE * randenc=fopen("src/txts/data/randenc.txt","r");
    for(int i=0;((i<4)&&(!toexit));i++){
        fscanf(randenc,"%d%*c",&a);
        for(int j=0;((j<8)&&(!toexit));j++){
            fscanf(randenc,"%d%*c",&c);
            clean_fgets(stringa,200,randenc);
            if((i==encounter_code)&&(j==b)){
                print_desc_box(stringa,100);
                toexit=1;
            }
        }
    }
    fclose(randenc);
    return;
}

void print_possible_distractions(const spbook * spb){
    printf("\nHai deciso di provare a fuggire.\nPer farlo, puoi usare uno dei seguenti incantesimi\nSe non ne compaiono vuol dire che non ne conosci ancora");
        for(int i=0;i<3;i++){
            if (spb->spell[10+i].known) printf("\n    %d. %s",i,spb->spell[i].nome);
        }
    return;
}

int ask_for_distraction(void){
    char choice[100];
    ask("Inserisci la tua azione");
    clean_fgets(choice,100,stdin);
    return decode(choice,escape_);
}

int luci (const personaggio NPC){
    return ((NPC.volonta+rolld(20))>15);
}
int sonno (const personaggio NPC){
    return ((NPC.costituzione+rolld(20))>15);
}
int suggestione(const personaggio NPC){
    return ((NPC.intelligenza+rolld(20))>15);
}

int try_esc(const personaggio NPC, int scelta){
    int exitVar, (*p[3])(const personaggio)={luci,sonno,suggestione};
    exitVar=(*p[scelta])(NPC);
    return exitVar;
}

int try_to_escape(const spbook * spb, const personaggio NPC){
    char choice[100];
    int scelta,returnValue,i;
    printf("\nVuoi provare a fuggire?");
    ask("Inserisci \"si\" per provare");
    clean_fgets(choice,100,stdin);
    scelta=decode(choice,scelta_);
    if(scelta){
        print_possible_distractions(spb);
        if((scelta=ask_for_distraction())>=0&&scelta<=2){
            if((returnValue=try_esc(NPC,scelta)))                printf("\n%s",spb->spell[scelta].effetto);
            else                printf("\n%s",spb->spell[scelta].fallimento);
        }
        else{
            printf("\nMi dispiace, ma cosi' di sicuro non scappi");
            returnValue=0;
        }
    }
    else{
        printf("\nNon ci provi neanche a fuggire\nSprezzante del pericolo, tendi un guanto di sfida");
        returnValue=0;
    }
    if(returnValue) printf("\nRiesci ad allontanarti illeso");
    return returnValue;
}

void print_possible_attacks(const inv * inventario, const spbook * spb){
    printf("\nEcco a te le cose con cui puoi attaccare:");
    for(int c=0;c<5;c++){
        if(spb->spell[c].known) printf("\n      +%d. %s", c, spb->spell[c].nome);
    }
    for(int c=1;c<5;c++){
        if(inventario->oggetto[c].available) printf("\n      +%d. %s", c+4 , inventario->oggetto[c].nome);
    }
    return;
}


int ask_for_attack(void){
    char attack_string[100];
    ask("Inserisci il tuo attacco");
    clean_fgets(attack_string,100,stdin);
    return decode(attack_string,attack_);
}

int dardo(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+NPC->fireresist) < rolld(20)){
        print_invisible_box(spb->spell[0].effetto,100);
        returnValue=1;
    }
    else print_invisible_box(spb->spell[0].fallimento,100);
    return returnValue;
}

int demone_evo(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+NPC->fireresist) < rolld(20)){
        print_invisible_box(spb->spell[4].effetto,100);
        returnValue=1;
    }
    else print_invisible_box(spb->spell[4].fallimento,100);
    return returnValue;
}

int ice(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+NPC->iceresist) < rolld(20)){
        print_invisible_box(spb->spell[1].effetto,100);
        returnValue=1;
    }
    else print_invisible_box(spb->spell[1].fallimento,100);
    return returnValue;
}

int infliggi(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+NPC->necroresist) < rolld(20)){
        print_invisible_box(spb->spell[3].effetto,100);
        returnValue=1;
    }
    else print_invisible_box(spb->spell[3].fallimento,100);
    return returnValue;
}

int missile(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+NPC->forceresist) < rolld(20)){
        print_invisible_box(spb->spell[2].effetto,100);
        returnValue=1;
    }
    else print_invisible_box(spb->spell[2].fallimento,100);
    return returnValue;
}


int pugnale(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+NPC->destrezza) < rolld(20)){
        print_invisible_box(inventario->oggetto[1].uso,100);
        returnValue=1;
    }
    else print_invisible_box(inventario->oggetto[1].fallimento,100);
    return returnValue;
}

int ascia(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+NPC->fisicresist) < rolld(20)){
        print_invisible_box(inventario->oggetto[2].uso,100);
        returnValue=1;
    }
    else print_invisible_box(inventario->oggetto[2].fallimento,100);
    return returnValue;
}

int martello(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+NPC->iceresist) < rolld(20)){
        print_invisible_box(inventario->oggetto[3].uso,100);
        returnValue=1;
    }
    else print_invisible_box(inventario->oggetto[3].fallimento,100);
    return returnValue;
}

int lancia(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+NPC->forceresist) < rolld(20)){
        print_invisible_box(inventario->oggetto[4].uso,100);
        returnValue=1;
    }
    else print_invisible_box(inventario->oggetto[4].fallimento,100);
    return returnValue;
}

int attack_successful(const inv * inventario, const spbook * spb, personaggio * NPC,int attack){
    int exitVar,(*p[9])(const inv*, const spbook*,const personaggio*)={dardo,ice,missile,infliggi,demone_evo,pugnale,ascia,martello,lancia};
    if(attack==-1){
        printf("\nL'azione da te selezionata non era valida");
        exitVar=0;
    }
    else exitVar=(*p[attack])(inventario,spb,NPC);
    return exitVar;
}

void attack(const inv * inventario, const spbook * spb, personaggio * NPC){
    int attack;
    printf("\nE' il tuo turno");
    print_possible_attacks(inventario,spb);
    attack=ask_for_attack();
    if(attack_successful(inventario,spb,NPC,attack)){
        printf("\nE hai colpitooo!");
        printf("\nAll'NPC rimangono %d vite", --(NPC->salute));
    }
    else{
        printf("\nIl tuo attacco non e' andato a buon fine\nSperiamo bene...");
    }
    return;
}
void print_possible_defenses(const inv * inventario,const spbook * spb){
    printf("\nScegli con cosa difenderti:");
    for(int c=0;c<3;c++){
        if(spb->spell[c+5].known) printf("\n    %d. %s",c,spb->spell[c+5].nome);
    }
    if(inventario->oggetto[5].available) printf("\n    3. Scudo (oggetto)");
    if(inventario->oggetto[6].available) printf("\n    4. Armatura");
    return;
}

int ask_for_defense(void){
    char defense_string[100];
    ask("Inserisci la tua difesa");
    clean_fgets(defense_string,100,stdin);
    return decode(defense_string,defense_);
}

int armatura_oggetto(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+5*(NPC->categoria==umanoide)) < rolld(20)){
        print_invisible_box(inventario->oggetto[6].uso,100);
        returnValue=1;
    }
    else print_invisible_box(inventario->oggetto[6].fallimento,100);
    return returnValue;
}

int scudo_oggetto(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+5*(NPC->categoria==umanoide)+5*(NPC->categoria==mostro)+5*(NPC->categoria==arcanista)+5*(NPC->categoria==demone)) < rolld(20)){
        print_invisible_box(inventario->oggetto[5].uso,100);
        returnValue=1;
    }
    else print_invisible_box(inventario->oggetto[5].fallimento,100);
    return returnValue;
}

int scudo_spell(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+5*(NPC->categoria==umanoide)+5*(NPC->categoria==demone)+5*(NPC->categoria==arcanista)) < rolld(20)){
        print_invisible_box(spb->spell[7].effetto,100);
        returnValue=1;
    }
    else print_invisible_box(spb->spell[7].fallimento,100);
    return returnValue;
}

int armatura_spell(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+5*(NPC->categoria==arcanista)) < rolld(20)){
        print_invisible_box(spb->spell[5].effetto,100);
        returnValue=1;
    }
    else print_invisible_box(spb->spell[5].fallimento,100);
    return returnValue;
}

int assorbi_elem(const inv * inventario, const spbook * spb, const personaggio * NPC){
    int returnValue=0;
    if((10+5*(NPC->categoria==nonMorto)) < rolld(20)){
        print_invisible_box(spb->spell[6].effetto,100);
        returnValue=1;
    }
    else print_invisible_box(spb->spell[6].fallimento,100);
    return returnValue;
}
int defense_successful(const inv * inventario, const spbook * spb, const personaggio * NPC, int defense){
    int exitVar,(*p[5])(const inv*, const spbook*,const personaggio*)={armatura_spell,assorbi_elem,scudo_spell,scudo_oggetto,armatura_oggetto};
    if(defense==-1){
        printf("\nL'azione da te selezionata non era valida");
        exitVar=0;
    }
    else exitVar=(*p[defense])(inventario,spb,NPC);
    return exitVar;
}


void cure(const spbook * spb, life * life_PG){
    int curAnswer=-1;
    char cureString[100];
    printf("\nPer un colpo di fortuna hai la possibilita' di provare a curarti\nScegli un incantesimo tra i seguenti\nCome sempre, se non compaiono vuol dire che non li conosci ancora");
    if(spb->spell[8].known) printf("\n      0. %s",spb->spell[8].nome);
    if(spb->spell[9].known) printf("\n      1. %s",spb->spell[9].nome);
    ask("Con cosa vuoi curarti?");
    clean_fgets(cureString,100,stdin);
    if((strstr(cureString,"cura")||strstr(cureString,"cure"))&& spb->spell[0].known) curAnswer=0;
    else if((strstr(cureString,"wither")||strstr(cureString,"bloom"))&&spb->spell[1].known) curAnswer=1;
    if((!(curAnswer==-1))&&rolld(20)>15){
        printf("\nOra hai %d vite",++(*life_PG));
    }
    else{
        printf("\nNon ti è andata bene");
    }
    return;
}

void defend(const inv * inventario, const spbook * spb, const personaggio * NPC, life *life_PG){
    int defense;
    printf("\nE' il turno del tuo nemico, che senza esitazione ti attacca");
    print_possible_defenses(inventario,spb);
    defense=ask_for_defense();
    if(!defense_successful(inventario,spb,NPC,defense)){
        printf("\nNon ce l'hai fatta. Ora la tua vita e' di: %d",--(*life_PG));
    }
    else printf("\nFiiiuuuu, l'hai vista brutta stavolta\nMa ora tocca a te");
    print_life(NPC->salute,*life_PG);
    if(rolld(20)>15){
        cure(spb, life_PG);
        print_life(NPC->salute,*life_PG);
    }
    return;
}


void fight(map * mappa, int * current, inv * inventario, spbook * spb, bestiary * bestiario, int * died){
    life life_PG= ottima;
    int turno=1;
    printf("\n%s:",bestiario->character[mappa->place[*current].encounter_code].nome);
    print_invisible_box(bestiario->character[mappa->place[*current].encounter_code].descrizione,100);
    if(!(try_to_escape(spb, bestiario->character[mappa->place[*current].encounter_code])==SUCCESS)){
        printf("\nDato che il nemico e' gentile ti concede il primo attacco");
        while(life_PG && (bestiario->character[mappa->place[*current].encounter_code].salute)){
            if(turno){
                attack(inventario,spb,&(bestiario->character[mappa->place[*current].encounter_code]));
                print_life(bestiario->character[mappa->place[*current].encounter_code].salute,life_PG);
            }
            else{
                defend(inventario,spb,&(bestiario->character[mappa->place[*current].encounter_code]),&life_PG);
            }
            turno=!turno;
            print_dot_line(100);
        }
        if(life_PG<=0){
            printf("\nSfortunatamente anche per i migliori viene la fine");
            *died=1;
        }
        else{
            printf("\nE anche stavolta l'hai scampata");
            if(!bestiario->character[mappa->place[*current].encounter_code].salute) mappa->place[*current].is_encounter_location=0;
        }
    }
    return;
}

void encounter(map * mappa, int * current, inv * inventario, spbook * spb, bestiary * bestiario, int * died,sett*settings){
    printf("\nDinanzi a te, una creatura si manifesta");
    bell(2,settings);
    if(bestiario->character[mappa->place[*current].encounter_code].orientamento==buono){
        start_quiz(mappa,current, inventario, spb,bestiario,died);
    }
    else{
        if(bestiario->character[mappa->place[*current].encounter_code].orientamento==cattivo){
            fight(mappa,current, inventario, spb,bestiario,died);
        }
        else{
            if(rand()%2){
                start_quiz(mappa,current, inventario, spb,bestiario,died);
            }
            else {
                fight(mappa,current, inventario, spb,bestiario,died);
            }
    mappa->place[*current].is_encounter_location=0;
    return;
        }
    }
}

void setEncounter(posto * loc, int is_encounter_location, int encounter_code){
    loc->is_encounter_location=is_encounter_location;
    loc->encounter_code=encounter_code;
    printf(".");
    return;
}