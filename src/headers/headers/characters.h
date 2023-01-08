typedef enum {debolezza=-5,no=0,si=+5} resistenza;
typedef enum {umanoide, arcanista, demone, mostro, nonMorto} type;//umanoide danni fisici, arcanista forza, demone fuoco, mostro gelo, non morto necrotici
typedef enum {buono, neutro,cattivo} orient;
typedef enum {unconscious,stunned,grave,ferito,colpito,ottima} life;
typedef struct
{
    char nome[NMLENG];
    char descrizione[DESCRLENG];
    int intelligenza;
    int forza;
    int destrezza;
    int volonta;
    int costituzione;
    resistenza iceresist;
    resistenza fireresist;
    resistenza fisicresist;
    resistenza necroresist;
    resistenza forceresist;
    type categoria;
    orient orientamento;
    life salute;
}personaggio;
typedef struct
{
    personaggio character[100];
}bestiary;

