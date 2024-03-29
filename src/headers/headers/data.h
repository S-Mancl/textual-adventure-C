/*DEFINE numeric constants*/
#define NITEM 16
#define NMLENG 100
#define DESCRLENG 300
#define NPLACE 62
#define NUMQUESTION 9
#define SUCCESS 1
#define FAILURE 0

#define ASCIIART ".-.   .-.                               .-.                        .-. _    .--.    \n: :  .'.'                              .' `.                       : ::_;  : .--'   \n: :  `-' .--.  .-..-..-..-. .--. ,-.,-.`. .'.-..-..--.  .--.     .-' :.-.  `. `.    \n: :__   ' .; ; : `; :: `; :' '_.': ,. : : : : :; :: ..'' .; ;   ' .; :: :   _`, : _ \n:___.'  `.__,_;`.__.'`.__.'`.__.':_;:_; :_; `.__.':_;  `.__,_;  `.__.':_;  `.__.':_;\n\n\n"
#define MAPPA_ASCII_ART "\n\n\n*****************\nMappa: ASCII art.\n*****************\n\n                         *---------------*-------------*\n*--------------*         | Grande        | Antico      |\n|Oscura torre  *---------* valle         | Vulcano     |\n| (24)         | Piccola | (28)          | Attivo      |\n*----|---------* valle   |               | (32)        |\n|Catena Arcana | (26)    |               |             |\n|(23)*----|----*---|---*-*---|-----------*---|---------*\n|    | Strada  | Strada|Strada           | Antico      |\n|    | Monti   - Monti -Monti            - vulcano     |\n|    | 3 (22)  | 4(25) |5 (27)           | spento (31) |\n*----*-----|---*-------*-----------*----|*---*----|----*\n           |                       |Strada   -Strada   |\n*-------*--|---------*-----------* |Monti    |Monti    |\n|       -Strada      -Strada     | |6 (29)   |7 (30)   | \n| Monti |Monti2(20)  |Monti 1(19)| *---------*------|--*--*------*\n| occid *-*----|-----*----|------*---------------* |Strada|Strada|\n| entali| |Collina   -Collina    - Collina della | |Monti -Monti |\n| (21)  | |Grande(18)|Piccola(17)| citta (16)    | |8 (33)|9 (34)|\n*-------* *----------*-----------*-------|-------* *----- *----*|*-----*\n                     *-------------------|-------*             |Strada |\n                     | Tangenziale Nord-Est (15) |             |Monti  |                         *------------*\n          *----------*----|----*-----*--------*  |             |10 (35)|                         |            |\n          | Piazza   |         |     |        |  |             *-----*|*-----------*-------------* Bosco      |\n          | del      | Porta   | Via | Palazzo|  |                   |    Strada   |     Strada  | Pubblico   |\n          | Castello - Nord    - C   - X de C |  |                   |    Pianura  -     Pianura -  (40)      |\n          | (12)     | (11)    | (13)| (14)   |  |                   |    3 (36)   |      4 (39) |            |\n          |          |         |     |        |  |                   *-----*|-----*----------*-|-----*----|---*\n          *----|-----*----|----*--|--*--------*  |                         |Strada |Fattoria |Strada |Casa    |\n          | Porta    - Caserma - Porta        |  |                         |Pianura-di (41)  -Pianura-Curatore|\n          | Sud (8)  |  (9)    | Est (10)     -  -------------*            |2(37)  |Eustachio|5 (42) |(43)    |\n          *----|-----*---------*--------------*--*            |            *---|---*--|------*---|---*-----*--*\n          |          |                                        *-------------Strada |Campi di |Piazza del   *------*\n          |          | *-----------------------------------------*         |Pianura-Eustachio-quartiere    -Uffici|\n          |          | |   Parco Xalgygs (4)                     |         |1 (38) |(44)     |agricolo (45)|(46)  |\n          |          | | *---|----------------*----------------* |*--*-----*-------*---*-*---*--*---|----*-*--------*\n          |    (7)   | | |                    |                | ||   \\    Campo      /  |vicolo|Via     |Bottega   |\n          |          | | |     Biblioteca (2) |  Archivio (5)  | ||    \\   Nord      /   |cieco |Fattorie-del       |\n          |strada    | | |                    |                | ||Campo\\  (47)     /    |(59)  |(58)    |fabbro(60)|\n          |accademia --- *-----|------*------------*-----------* ||Ovest *---|-----*     *-|----*------*|*----------*---*\n          |citta     | | |            |            | Corridoio | || (49) |Campo    |Campo|Piazza       -Via             |\n          *----------* | - Corridoio  - Stanza di S- Est       | ||      -Centro   -Est  |Centrale (56)|residenziale(57)|\n                       | |   ovest(1) |       (0)  |           | ||      | (48)    |(50  *-----|-------*-----------*----*\n                       | *-----|------*------------*    (6)    | |*------*---|-----*-----* Strada      - Via       |\n                       | |                         |           | ||   Campo sud (51)     |Centrale (55)|Chiusa (61)|\n                       | | Aula delle lezioni(3)   -           | |*------------|---------*-----|-----*-*--------*--*\n                       | |                         |           | || Via campi (52)       - Via       |Casa      |\n                       | *-------------------------*-----|-----* |*----------------------* Cartografi-Cartografo|\n                       *-----------------------------------------*                       | (53)      |(54)      |\n                                                                                         *-----------*----------*"

/*DEFINE strings to increase readability*/
//intro
#define VERSION "                                           Version: 8.2"
#define HI "Salve!"
#define WELCOME "Benvenuti in un gioco che ancora non so come si chiama e che dato che sono matto ho deciso di realizzare in C."
#define GAMEPLAY "Come si gioca? Una domanda molto interessante. Da questa versione e' possibile non solo inserire i numeri corrispondenti alle azioni, ma anche i comandi come parole!"
#define NOTA "Nota: al momento nei fight non e' possibile utilizzare i numeri: assicurarsi SEMPRE di scrivere i nomi per intero, per sicurezza."
#define DEBUG_STRING "                                        ACTIVATED DEBUG MODE"
//useful
#define NOTAVAILABLEOBJ "\n> Non ci sono oggetti da raccogliere"
#define NOTAVAILABLE_OBJ "\n> Non ci sono oggetti con questo ID"
#define NOTAVAILABLESP "\n> Non (ancora) conosciuto"
#define NOTAVAILABLE_SPELL "\n> Non ci sono spell da imparare"
#define SPELLTOLEARN "Strani arcani simboli ti fanno presagire che c'e' qualcosa da imparare, se lo vuoi"
#define TOOFAR "\n> Quell'oggetto e' decisamente troppo lontano... usa un incantesimo o un oggetto per avvicinarlo"
#define DICENOTAPPROVED "\n> I dadi non hanno approvato la tua mossa.\n> Capita, dai, riprova, non buttarti giù, vedrai che andra' meglio"
#define INVALIDMOVE "\nNon puoi andare in quella direzione: non esiste."

//general
#define ECHILOSA "> Lo devi ancora scoprire!"
#define CREDITS1 "Programma realizzato da: Samuele Manclossi"
#define CREDITS2 "Si ringraziano tutti i beta tester"