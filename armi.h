/*funzioni che utilizzano i diversi tipi di armi*/
#include "mappa.h"
#include "time.h"

/*costanti simboliche timerbomb*/
#define BOMBE_MAX 3
#define TIMERBOMB_EXPLO_START 2
#define TIMERBOMB_EXPLO_END 0.01

/*determina il tipo di arma*/
void armaBomberman(char mappa[][COLONNA]);

/*funzioni timerbomb*/
void timerBomb(char mappa[][COLONNA]);			
void posizionaTimerBomb(char mappa[][COLONNA], clock_t statbombe[], int bombaposx[], int bombaposy[]);
void esplosioneTimerBomb(int mod, char mappa[][COLONNA], int bposx, int bposy);
