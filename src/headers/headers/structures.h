

typedef enum {fuoco, ghiaccio,forza,necrotico,protezione,teletrasporto,distrazione,cura,manipolazione} element;
typedef enum {normale, bruciata, ghiacciata,devastata} stato;

typedef struct //creates structure named item
{
    char nome[NMLENG];
    char descrizione[DESCRLENG];
    int available;
    char uso[DESCRLENG];
    char fallimento[DESCRLENG];

}item;

typedef struct //creates structure named inv(entory)
{
    item oggetto[NITEM];
}inv;

typedef struct //creates structure named spel(l)
{
    char nome[NMLENG];
    char descrizione[DESCRLENG];
    char effetto[DESCRLENG];
    char fallimento[DESCRLENG];
    element elemento;
    int known;
}spel;

typedef struct //creates structure named spbook(spellbook)
{
    spel spell[NITEM];
}spbook;

typedef struct
{
    char nome[NMLENG];
    int dir[4]; //0=N,1=S,2=E,3=O
    char transition_description[4][DESCRLENG];
    char moves_description[4][DESCRLENG];
    int objAvailable;//0=no,1=yes;2=yes-outOfRange, use mageHand or a ladder
    int availableObjCode;
    stato status; //if they cast fire spells then status=bruciato, ice -> ghiacciato, cure -> normale
    char descrizione[4][DESCRLENG];
    char descrAvailableObj[DESCRLENG];
    int spellAvailable;
    int codeSpell;
    int is_encounter_location;
    int encounter_code;
    int is_there_money;
    int regen_ratio;
}posto;


typedef struct
{
    posto place[NPLACE];
}map;

/*typedef struct{
    char nome[NMLENG];
    unsigned int quantita;
}component;

typedef struct{
    component ingredients[10];
}component_pouch;*/

typedef struct{
    short audioOn;
    short randomEncounters;
}sett;
