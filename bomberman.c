#include "bomberman.h"
#include "time.h"
#include <stdio.h>

/*globali*/
extern Bomberman bomberplayer;
extern Bomberman iabomber[BOMBERMAN_IA_MAX];

/*determina tipo di mossa(movimento, posizionamento bomba)*/
int mossaBombermanPlayer(int *move)
{
	if(kbhit())
	{
		*move = getch();
	
		/*mossa movimento*/
		if(*move == 'w' || *move == 's' || *move == 'a' || *move == 'd')
		return 1;
	
		/*mossa arma*/
		else if(*move == 'q' || *move == 'Q')
		return 2;
	
		/*termina*/	
		else if(*move == ' ')
		return 4;
	}
	
	/*nessun tasto premuto*/
	else
	{
		return 0;
	}
	
}

/*effettua il movimento di bomberman*/
void movimentoBombermanPlayer(char mappa[][COLONNA], int *move)
{
	/*elimina vecchia posizione BOMBERMAN*/
	/*ignora se la posizione attuale e sulla bomba*/
	if(mappa[bomberplayer.posx][bomberplayer.posy] != 'Q')
	{
		mappa[bomberplayer.posx][bomberplayer.posy] = ' ';
		posCursore(bomberplayer.posy, bomberplayer.posx);
		printf(" ");
	}
	
	if(*move == 'w')
	{
		if(verificaPosizioneSuccBomberman(move, mappa))
			bomberplayer.posx -= 1;
	}
	else if(*move == 'a')
	{
		if(verificaPosizioneSuccBomberman(move, mappa))
			bomberplayer.posy -= 1;
	}
	else if(*move == 'd')
	{
		if(verificaPosizioneSuccBomberman(move, mappa))
			bomberplayer.posy += 1;
	}
	else if(*move == 's')
	{
		if(verificaPosizioneSuccBomberman(move, mappa))
		bomberplayer.posx += 1;
	}
	
	/*termina*/
	else if(*move == ' ')
	{
		bomberplayer.status = 0;
	}

	mappa[bomberplayer.posx][bomberplayer.posy] = 'B';
}

/*controlla la posizione successiva di bomberman per determinare se sia possibile il movimento*/
int verificaPosizioneSuccBomberman(int *move, char mappa[][COLONNA])
{
	if(*move == 'w')
	{
		if(mappa[bomberplayer.posx - 1][bomberplayer.posy] == ' ')
		return 1;
		return 0;
	}
	else if(*move == 's')
	{
		if(mappa[bomberplayer.posx + 1][bomberplayer.posy] == ' ')
		return 1;
		return 0;
	}
	else if(*move == 'a')
	{
		if(mappa[bomberplayer.posx][bomberplayer.posy - 1] == ' ')
		return 1;
		return 0;
	}
	else if(*move == 'd')
	{
		if(mappa[bomberplayer.posx][bomberplayer.posy + 1] == ' ')
		return 1;
		return 0;
	}
}

/*determina la mossa del bomberman IA*/
int mossaBombermanIa(int *nbomberIA, char mappa[][COLONNA])
{
	/*se il bomberman IA non e in prossimita di un blocco distruttibile oppure di un
	  bomberman player effettua un movimento in una direzione consentita e casuale*/
    
	return 1;
}

/*IA sceglie casualmente una direzione, se la direzione scelta e libera effettua il movimento altrimenti
  sceglie casualmente un'altra direzione finche non viene trovata una posizione libera ed effettuare il movimento*/
void movimentoBombermanIa(int *nbomberIA, char mappa[][COLONNA])
{
	/*se il BIA corrente non ha fatto i passi nella sua direzione*/
	if(iabomber[*nbomberIA].npassiIA != 0)
	{
		/*se la prossima casella in quella direzione e un'ostacolo(blocchi, BIA), genera un'altra posizione 
		  e nuovi passi*/
		if(verificaPosizioneSuccBombermanIa(&iabomber[*nbomberIA].direzioneIA, mappa, nbomberIA) == 0)
		{
			iabomber[*nbomberIA].direzioneIA = cercaDirezioneBombermanIa(mappa, nbomberIA);
			iabomber[*nbomberIA].npassiIA = 1 + rand() % BOMBERMAN_IA_PASS_MAX;
		}
		
		/*se la prossima casella e libera continua**/
		else
		{
			iabomber[*nbomberIA].npassiIA--;
		}
	}
	
	/*se il BIA ha fatto i suoi passi cambia direzione e numero di passi*/
	else
	{
		iabomber[*nbomberIA].direzioneIA = cercaDirezioneBombermanIa(mappa, nbomberIA);
		iabomber[*nbomberIA].npassiIA = 1 + rand() % BOMBERMAN_IA_PASS_MAX;
	}
	
	/*elimina vecchia posizione BOMBERMAN IA*/
	mappa[iabomber[*nbomberIA].posx][iabomber[*nbomberIA].posy] = ' ';
	posCursore(iabomber[*nbomberIA].posy, iabomber[*nbomberIA].posx);
	printf(" ");
	
	/*su*/
	if(iabomber[*nbomberIA].direzioneIA == 0)
	{
		if(verificaPosizioneSuccBombermanIa(&iabomber[*nbomberIA].direzioneIA, mappa, nbomberIA))
		iabomber[*nbomberIA].posx -= 1;
	}
	
	/*giu*/
	else if(iabomber[*nbomberIA].direzioneIA == 2)
	{
		if(verificaPosizioneSuccBombermanIa(&iabomber[*nbomberIA].direzioneIA, mappa, nbomberIA))
		iabomber[*nbomberIA].posx += 1;
	}
	
	/*destra*/
	else if(iabomber[*nbomberIA].direzioneIA == 1)
	{
		if(verificaPosizioneSuccBombermanIa(&iabomber[*nbomberIA].direzioneIA, mappa, nbomberIA))
		iabomber[*nbomberIA].posy += 1;
	}
	
	/*sinistra*/
	else if(iabomber[*nbomberIA].direzioneIA == 3)
	{
		if(verificaPosizioneSuccBombermanIa(&iabomber[*nbomberIA].direzioneIA, mappa, nbomberIA))
		iabomber[*nbomberIA].posy -= 1;
	}
	
	mappa[iabomber[*nbomberIA].posx][iabomber[*nbomberIA].posy] = 'D';
}

/*verifica che la posizione successiva sia una casella libera*/
int verificaPosizioneSuccBombermanIa(int *direz, char mappa[][COLONNA], int *nbomberIA)
{
	if(*direz == 0)
	{
		if(mappa[iabomber[*nbomberIA].posx - 1][iabomber[*nbomberIA].posy] == ' ')
		return 1;
		return 0;
	}
	
	else if(*direz == 2)
	{
		if(mappa[iabomber[*nbomberIA].posx + 1][iabomber[*nbomberIA].posy] == ' ')
		return 1;
		return 0;
	}
	
	else if(*direz == 1)
	{
		if(mappa[iabomber[*nbomberIA].posx][iabomber[*nbomberIA].posy + 1] == ' ')
		return 1;
		return 0;
	}
	
	else if(*direz == 3)
	{
		if(mappa[iabomber[*nbomberIA].posx][iabomber[*nbomberIA].posy - 1] == ' ')
		return 1;
		return 0;
	}
}

/*determina la direzione che il BIA dovra prendere*/
int cercaDirezioneBombermanIa(char mappa[][COLONNA], int *nbomberIA)
{
	int direz;
	srand(time(NULL));
	
	/*se il bomberman ha il lato sinistro occupato*/
	/*cerca un'altra direzione qualsiasi*/
	if(mappa[iabomber[*nbomberIA].posx][iabomber[*nbomberIA].posy - 1] != ' ')
	{
		do
		{
			direz = rand() % 4;
			iabomber[*nbomberIA].direzioneIA = direz;
		}while(direz == 3 || iabomber[*nbomberIA].direzioneIA == iabomber[*nbomberIA - 1].direzioneIA);
	}
	
	/*se il bomberman ha il lato destro occupato*/
	/*cerca un'altra direzione qualsiasi*/
	else if(mappa[iabomber[*nbomberIA].posx][iabomber[*nbomberIA].posy + 1] != ' ')
	{
		do
		{
			direz = rand() % 4;
			iabomber[*nbomberIA].direzioneIA = direz;
		}while(direz == 1 || iabomber[*nbomberIA].direzioneIA == iabomber[*nbomberIA - 1].direzioneIA);
	}
	
	/*se il bomberman ha il lato basso occupato*/
	/*cerca un'altra direzione qualsiasi*/
	else if(mappa[iabomber[*nbomberIA].posx + 1][iabomber[*nbomberIA].posy] != ' ')
	{
		do
		{
			direz = rand() % 4;
			iabomber[*nbomberIA].direzioneIA = direz;
		}while(direz == 2 || iabomber[*nbomberIA].direzioneIA == iabomber[*nbomberIA - 1].direzioneIA);
	}
	
	/*se il bomberman ha il lato alto occupato*/
	/*cerca un'altra direzione qualsiasi*/
	else if(mappa[iabomber[*nbomberIA].posx - 1][iabomber[*nbomberIA].posy] != ' ')
	{
		do
		{
			direz = rand() % 4;
			iabomber[*nbomberIA].direzioneIA = direz;
		}while(direz == 0 || iabomber[*nbomberIA].direzioneIA == iabomber[*nbomberIA - 1].direzioneIA);
		
	}
	
	/*se il bomberman ha tutti i lati liberi sceglie una direzione qualsiasi*/
	else
	{
		do
		{
			direz = rand() % 4;
			iabomber[*nbomberIA].direzioneIA = direz;
		}while(iabomber[*nbomberIA].direzioneIA == iabomber[*nbomberIA - 1].direzioneIA);
	}
	return direz;
}

/*inizializza i parametri dei bomberman*/
void inizPosBomberman(char mappa[][COLONNA])
{	
	int nbomberIA;
	
	srand(time(NULL));
	
	/*inizializza bomberman player*/
	/*cerca una posizione libera*/
	do
	{
		bomberplayer.posx = 1 + rand() % RIGA;
		bomberplayer.posy = 1 + rand() % COLONNA;
		bomberplayer.status = 1;
		bomberplayer.arma = 0;
	}while(mappa[bomberplayer.posx][bomberplayer.posy] != ' ');
	
	
	/*inizializza bomberman IA*/
	for(nbomberIA = 0; nbomberIA < BOMBERMAN_IA_MAX; nbomberIA++)
	{
		do
		{
			iabomber[nbomberIA].posx = 1 + rand() % RIGA;
			iabomber[nbomberIA].posy = 1 + rand() % COLONNA;
			iabomber[nbomberIA].arma = 0;
			iabomber[nbomberIA].status = 1;
			iabomber[nbomberIA].npassiIA = 1 + rand() % BOMBERMAN_IA_PASS_MAX;
			iabomber[nbomberIA].direzioneIA = rand() % 4;
		}while(mappa[iabomber[nbomberIA].posx][iabomber[nbomberIA].posy] != ' ');
	}
}
