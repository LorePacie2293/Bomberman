/*bomberman*/
#include "bomberman.h"
#include "time.h"

/*globali*/
Bomberman bomberplayer;
Bomberman iabomber[BOMBERMAN_IA_MAX];

main()
{
	clock_t timerstart = clock() / CLOCKS_PER_SEC, timerend;
	int move = 0, nbomberIA; 
	char mappa[RIGA][COLONNA];
	
	generaMappa(mappa);
	while(bomberplayer.status != 0)
	{
		/*mossa player*/
		switch(mossaBombermanPlayer(&move))
		{
			case 1:
				movimentoBombermanPlayer(mappa, &move);
				break;
			case 2:
				armaBomberman(mappa);
			
				break;
			case 4:
				bomberplayer.status = 0;
				break;
			default:
				break;
		}
			
		/*se e stato premuto un tasto aggiorna la posizione del bomberman player altrimenti no(per evitare lo spostamento continuo del cursore*/
		if(move != 0)
		{
			aggiornaPosizioni(mappa);
			move = 0;
		} 
		
		/*mossa IA*/
		/*timer mossa, i bomberman IA si muoveranno ogni tot secondi*/
		if((timerend = clock() / CLOCKS_PER_SEC) > timerstart + BOMBERMAN_IA_SPEED)
		{
			for(nbomberIA = 0; nbomberIA < BOMBERMAN_IA_MAX; nbomberIA++)
			{
				switch(mossaBombermanIa(&nbomberIA, mappa))
				{
					case 1:
						movimentoBombermanIa(&nbomberIA, mappa);
						break;
					default:
						break;
				}
			}
			timerstart = clock() / CLOCKS_PER_SEC;
			aggiornaPosizioni(mappa);
		}
	}
}


