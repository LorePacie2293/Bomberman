#include "armi.h"
#include "bomberman.h"

/*globali*/
extern Bomberman bomberplayer;
int maxtimebombe = 0;

/*usa arma di bomberman*/
void armaBomberman(char mappa[][COLONNA])
{
	/*bomba*/
	if(bomberplayer.arma == 0)
	{
		timerBomb(mappa);
	}
}

/*timerbomb funzione che gestisce l'arma bomba a tempo, la funzione rimane attiva finche le bombe attive sono da 1 a BOMBE_MAX*/
void timerBomb(char mappa[][COLONNA])
{
	clock_t timerend, timerstart, timebombe[BOMBE_MAX] = {0},timerspeedstart = clock() / CLOCKS_PER_SEC, timerspeedend;
	int bombaposx[BOMBE_MAX] = {0}, bombaposy[BOMBE_MAX] = {0}, move, nbomba = 0, nbomberIA;
	
	/*posiziona prima bomba*/
	posizionaTimerBomb(mappa, timebombe, bombaposx, bombaposy);
	aggiornaPosizioni(mappa);
	
	/*prevenzione errore bomba 0 secondi(NON ESPLODE)*/
	if(timebombe[0] == 0)
	timebombe[0] += 1;
	
	while(maxtimebombe > 0)
	{
		timerstart = clock() / CLOCKS_PER_SEC;
		
		/*confronto tempo attuale con tempo di tutte le bombe posizionate*/
		for(nbomba = 0; nbomba < BOMBE_MAX; nbomba++)
		{
			/*se la bomba corrente e posizionata ed esplosa*/
			if(timerstart >= timebombe[nbomba] + TIMERBOMB_EXPLO_START && timebombe[nbomba] != 0)
			{
				esplosioneTimerBomb(1, mappa, bombaposx[nbomba], bombaposy[nbomba]);
				aggiornaPosizioni(mappa);
				
				/*timer bomba fine esplosione(finche l'esplosione e attiva)*/
				timerend = clock() / CLOCKS_PER_SEC;
				do{
					timerstart = clock() / CLOCKS_PER_SEC;
					
					/*mossa player*/
					if(kbhit())
					{
						move = getch();
						if(move == 'q' &&  maxtimebombe <= BOMBE_MAX)
						{
							if(mappa[bomberplayer.posx][bomberplayer.posy] != 'Q')
							posizionaTimerBomb(mappa, timebombe, bombaposx, bombaposy);
						}
						else
						{
							movimentoBombermanPlayer(mappa, &move);
						}
						aggiornaPosizioni(mappa); 
					}
					
					/*mossa IA*/
					/*timer mossa, i bomberman IA si muoveranno ogni tot secondi*/
					if(timerspeedend = clock() / CLOCKS_PER_SEC > timerspeedstart + BOMBERMAN_IA_SPEED)
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
						timerspeedstart = clock() / CLOCKS_PER_SEC;
						aggiornaPosizioni(mappa);
					}					
				}while(timerstart <= timerend + TIMERBOMB_EXPLO_END);	
				esplosioneTimerBomb(2, mappa, bombaposx[nbomba], bombaposy[nbomba]);
				
				/*elimina la posizione della bomba esplosa*/
				bombaposx[nbomba] = 0; 
				bombaposy[nbomba] = 0;
				timebombe[nbomba] = 0;
				maxtimebombe--;
				

			}
			
			/*se la bomba corrente e posizionata ed non esplosa*/
			else if(timerstart < timebombe[nbomba] + TIMERBOMB_EXPLO_START && timebombe[nbomba] != 0)
			{
				/*mossa player*/
				if(kbhit())
				{
					move = getch();
					if(move == 'q' &&  maxtimebombe <= BOMBE_MAX)
					{
						if(mappa[bomberplayer.posx][bomberplayer.posy] != 'Q')
						posizionaTimerBomb(mappa, timebombe, bombaposx, bombaposy);
					}
					else
					{
						movimentoBombermanPlayer(mappa, &move);
					}
					aggiornaPosizioni(mappa);
				}

				/*mossa IA*/
				/*timer mossa, i bomberman IA si muoveranno ogni tot secondi*/
				if((timerspeedend = clock() / CLOCKS_PER_SEC) > timerspeedstart + BOMBERMAN_IA_SPEED)
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
					timerspeedstart = clock() / CLOCKS_PER_SEC;
					aggiornaPosizioni(mappa);
				}
			}
		}
	}
}

/*crea o elimina i segmenti di un'esplosione*/
void esplosioneTimerBomb(int mod, char mappa[][COLONNA], int bposx, int bposy)
{
	int segm;
	
	/*creazione segmenti esplosione*/
	if(mod == 1)
	{
		/*giu*/
		for(segm = 1; segm <= 5; segm++)
		{
			if(mappa[bposx + segm][bposy] != 127 && mappa[bposx + segm][bposy]!= '#' && mappa[bposx + segm][bposy] != 'Q')
			{
				mappa[bposx + segm][bposy] = '*';
			}
			else
			{
				break;
			}
		}
		
		/*su*/
		for(segm = 1; segm <= 5; segm++)
		{
			if(mappa[bposx - segm][bposy]!= 127 && mappa[bposx - segm][bposy]!= '#' && mappa[bposx - segm][bposy] != 'Q')
			{
				mappa[bposx - segm][bposy] = '*';
			}
			else
			{
				break;
			}
		}
			
		/*destra*/
		for(segm = 1; segm <= 5; segm++)
		{
			if(mappa[bposx][bposy + segm]!= 127 && mappa[bposx][bposy + segm]!= '#' && mappa[bposx][bposy + segm] != 'Q')
			{
				mappa[bposx][bposy + segm] = '*';
			}
			else
			{
				break;
			}
		}
			
		/*sinistra*/
		for(segm = 1; segm <= 5; segm++)
		{
			if(mappa[bposx][bposy - segm]!= 127 && mappa[bposx][bposy - segm]!= '#' && mappa[bposx][bposy - segm] != 'Q')
			{
				mappa[bposx][bposy - segm] = '*';
			}
			else
			{
				break;
			}
		}
	}
	
	/*eliminazione segmenti esplosione(1 serve per evitare di aggiornare ogni casella vuota)*/
	else if(mod == 2)
	{
		mappa[bposx][bposy] = '1';
		
		/*giu*/
		for(segm = 1; segm <= 5; segm++)
		{
			if(mappa[bposx + segm][bposy] == '*')
			{
				mappa[bposx + segm][bposy] = '1';
			}
			else
			{
				break;
			}
		}
		
		/*su*/
		for(segm = 1; segm <= 5; segm++)
		{
			if(mappa[bposx - segm][bposy] == '*')
			{
				mappa[bposx - segm][bposy] = '1';
			}
			else
			{
				break;
			}
		}
		
		/*sinistra*/
		for(segm = 1; segm <= 5; segm++)
		{
			if(mappa[bposx][bposy - segm] == '*')
			{
				mappa[bposx][bposy - segm] = '1';
			}
			else
			{
				break;
			}
		}
		
		/*destra*/
		for(segm = 1; segm <= 5; segm++)
		{
			if(mappa[bposx][bposy + segm] == '*')
			{
				mappa[bposx][bposy + segm] = '1';
			}
			else
			{
				break;
			}
		}
		aggiornaPosizioni(mappa);
		
		/*azzera posizioni esplosione '1' a ' '*/
		/*giu*/
		for(segm = 1; segm <= 5; segm++)
		{
			if(mappa[bposx + segm][bposy] == '1')
			{
				mappa[bposx + segm][bposy] = ' ';
			}
			else
			{
				break;
			}
		}
		
		/*su*/
		for(segm = 1; segm <= 5; segm++)
		{
			if(mappa[bposx - segm][bposy] == '1')
			{
				mappa[bposx - segm][bposy] = ' ';
			}
			else
			{
				break;
			}
		}
		
		/*sinistra*/
		for(segm = 1; segm <= 5; segm++)
		{
			if(mappa[bposx][bposy - segm] == '1')
			{
				mappa[bposx][bposy - segm] = ' ';
			}
			else
			{
				break;
			}
		}
		
		/*destra*/
		for(segm = 1; segm <= 5; segm++)
		{
			if(mappa[bposx][bposy + segm] == '1')
			{
				mappa[bposx][bposy + segm] = ' ';
			}
			else
			{
				break;
			}
		}
		mappa[bposx][bposy] = ' ';
		
	}
}

/*posiziona la timerbomb nella posizione specificata ed ne imposta il timer*/
 void posizionaTimerBomb(char mappa[][COLONNA], clock_t statbombe[], int bombaposx[], int bombaposy[])
{
		int cont;
		
		/*cerca una posizione libera nel vettore dei timer delle bombe, ed imposta un tempo in quella posizione*/
		for(cont = 0; cont < BOMBE_MAX; cont++)
		{
			if(statbombe[cont] == 0)
			{
				/*posizione bomba*/
				bombaposx[cont] = bomberplayer.posx;
				bombaposy[cont] = bomberplayer.posy;
					
				/*avvio timer bomba*/
				statbombe[cont] = clock() / CLOCKS_PER_SEC;
				maxtimebombe++;
				mappa[bombaposx[cont]][bombaposy[cont]] = 'Q';
				break;
			}
		}
		
}
