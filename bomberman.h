/*contiene prototipi delle funzioni che gestiscono bomberman */
#include "mappa.h"
#define BOMBERMAN_IA_MAX 5
#define BOMBERMAN_IA_SPEED 0.01
#define BOMBERMAN_IA_PASS_MAX 10

/*struttura con tutti in parametri di un bomberman*/
typedef struct 
{
	int posx;
	int posy;
	int status;
	int arma;
	
	/*parametri solo IA*/
	int direzioneIA;
	int npassiIA;		
}Bomberman;

/*funzioni bomberman player*/
int mossaBombermanPlayer(int *move);														/*determina il tipo di mossa che effettua bomberman*/
void movimentoBombermanPlayer(char mappa[][COLONNA], int *move);							/*gestisce il movimento*/
int verificaPosizioneSuccBomberman(int *move, char mappa[][COLONNA]);						/*controlla la posizione successiva di bomberman player per determinare se sia possibile il movimento*/
			
/*funzioni bomberman IA*/
int mossaBombermanIa(int *nbomberIA, char mappa[][COLONNA]);								/*determina il tipo di mossa che effettua il bomberman IA*/
int cercaDirezioneBombermanIa(char mappa[][COLONNA], int *nbomberIA);						/*cerca una direzione per il BIA in base alle regole di IA*/								
void movimentoBombermanIa(int *nbomberIA, char mappa[][COLONNA]);							/*gestisce il movimento del bomberman IA*/
int verificaPosizioneSuccBombermanIa(int *direz, char mappa[][COLONNA], int *nbomberIA);	/*controlla la posizione successiva di bomberman IA per determinare se sia possibile il movimento*/

void inizPosBomberman(char mappa[][COLONNA]);												/*inizializza i parametri di un bomberman*/
