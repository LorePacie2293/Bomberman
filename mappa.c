#include "bomberman.h"
#include <windows.h>
#include <stdio.h>

/*globali*/
extern Bomberman bomberplayer;
extern Bomberman iabomber[BOMBERMAN_IA_MAX];
extern int maxtimebombe;

void generaMappa(char mappa[][COLONNA])
{
	int riga, colonna, nbomberIA;
	
	/*inizializza mappa*/
	for(riga = 0; riga < RIGA; riga++)
	{
		for(colonna = 0; colonna < COLONNA; colonna++)
		{
			/*confini*/
			if(riga == 0 || riga == RIGA - 1)
			{
				mappa[riga][colonna] = '#';
			}
			if(colonna == 0 || colonna == COLONNA - 1);
			{
				mappa[riga][colonna] = '#';
			}
			
			/*interno*/
			if(riga > 0 && riga < RIGA - 1 && colonna < COLONNA - 1 && colonna > 0)
			{
				/*blocchi*/
				if(riga % 2 == 0)
				{
					if(colonna % 4 == 0)
					{
						mappa[riga][colonna] = 127;
					}
					else
					{ 
						mappa[riga][colonna] = ' ';
					}
				}
				else
				{
					mappa[riga][colonna] = ' ';
				}
			}
			
			printf("%c", mappa[riga][colonna]);
		  	if(riga == 0 && colonna == COLONNA - 1)
			{
				posCursore(COLONNA + 2, riga);
				printf(" %d", maxtimebombe);
			}
		}
		printf("\n");
	}
	
	/*inizializza posizioni bomberman*/
	inizPosBomberman(mappa);
	
	for(riga = 0; riga < RIGA; riga++)
	{
		for(colonna = 0; colonna < COLONNA; colonna++)
		{
			/*posizione bomberman player*/
			if(riga == bomberplayer.posx && colonna == bomberplayer.posy)
			{
				mappa[riga][colonna] = 'B';
				posCursore(bomberplayer.posy, bomberplayer.posx);
				printf("B");
			}
			
			/*posizione bomberman IA*/
			for(nbomberIA = 0; nbomberIA < BOMBERMAN_IA_MAX; nbomberIA++)
			{					
				if(riga == iabomber[nbomberIA].posx && colonna == iabomber[nbomberIA].posy)
				{
					mappa[riga][colonna] = 'D';
					posCursore(iabomber[nbomberIA].posy, iabomber[nbomberIA].posx);
					printf("D");
				}
			} 
		}
	}
	posCursore(COLONNA, RIGA);
}

/*gestisce la posizione del cursore*/
void posCursore(int x, int y)
{
	COORD CursorPos = {x, y};
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, CursorPos);
}

/*aggiorna le singole posizioni degli elementi di gioco*/
void aggiornaPosizioni(char mappa[][COLONNA])
{
	int riga, colonna;
	for(riga = 0; riga < RIGA; riga++)
	{
		for(colonna = 0; colonna < COLONNA; colonna++)
		{
			if(riga == 0 && colonna == COLONNA - 1)
			{
				posCursore(COLONNA + 2, riga);
				printf(" %d", maxtimebombe);
			}
			if(mappa[riga][colonna] == 'B')
			{
				posCursore(colonna, riga);
				printf("B");
			}
			else if(mappa[riga][colonna] == 'Q')
			{
				posCursore(colonna, riga);
				printf("Q");
			}
			else if(mappa[riga][colonna] == '*')
			{
				posCursore(colonna, riga);
				printf("*");
			}
			
			/*posizioni di esplosione(per evitare di spostare il
			  cursore per ogni posizione vuota*/
			else if(mappa[riga][colonna] == '1')
			{
				posCursore(colonna, riga);
				printf(" ");
			}
			
			/*le posizioni dei bomberman IA vanno aggiornate ogni tot secondi*/
			else if(mappa[riga][colonna] == 'D')
			{
				posCursore(colonna, riga);
				printf("D");
			}
		}
	}
	posCursore(COLONNA, RIGA);
}


