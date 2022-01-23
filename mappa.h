/*funzioni che si occupano della creazione e aggiornamento della mappa di gioco*/

#define RIGA 25
#define COLONNA 45

void generaMappa(char mappa[][COLONNA]);			/*inizializza la mappa di gioco*/
void posCursore(int x, int y);						/*sposta il cursore del prompt*/	
void aggiornaPosizioni(char mappa[][COLONNA]);		/*aggiorna le singole posizioni degli elementi di gioco*/

