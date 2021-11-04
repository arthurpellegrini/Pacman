/******************************************************************************/
/* MAIN.c                                                                     */
/******************************************************************************/
#include "./main.h"

/******************************************************************************/
/* MAIN                                                                       */
/******************************************************************************/
int main(int argc, char **argv)
/* argc indique le nombre d'arguments,
   argv est un tableau de mots contenant ces arguments. */
    {
	srand(time(NULL));
    /* Chargement du plan à partir du fichier fourni en paramètre                 */
    #if DEBUG == 1
	printf("Chargement du plan...\n");
	#endif
	Partie p = charge_plan("./data/official_gomme.txt");
    /* Si problème lors du chargement du plan...                                  */
    if(p.plateau == NULL)
        return 1;

	#if DEBUG == 1 //Ceci est un drapeau à activer/désactiver dans main.h
    /* Affichage du plan lu                                                       */
    printf("Affichage du plan...\n");
    for(int i=0;i!=p.L;i++)
        {
        for(int j=0;j!=p.C;j++)
            printf("%c",p.plateau[i][j]);
        printf("\n");
        }
	//On donne les informations d'avant début de la partie
	printf("Pos départ Pacman : { C %d ; L %d }\n",p.pacman.c,p.pacman.l);
	printf("Pos départ Blinky : { C %d ; L %d }\n",p.blinky.c ,p.blinky.l);
	printf("Pos départ Clyde  : { C %d ; L %d }\n",p.clyde.c ,p.clyde.l);
	printf("Pos départ Inky   : { C %d ; L %d }\n",p.inky.c ,p.inky.l);
	printf("Pos départ Pinky  : { C %d ; L %d }\n",p.pinky.c ,p.pinky.l);
	printf("Nb Gommes au départ : %d\n",p.nbgomme);
	printf("Nb Bonus au départ  : %d\n",p.nbbonus);

	#endif

/******************************************************************************/
/* NOTRE CODE                            				                      */
/******************************************************************************/
	
	/*OUVERTURE FENÊTRE GRAPHIQUE*/
	ouvrir_fenetre(LARG,HAUT);

	p.score = 0;
	p.niveau = 1;
	p.vie = 3;
	int score,niveau,vie; // Variables à récupérer au niveau suivant
	int compteur_tour;	//Compteur du nombre de tour
	int compteur_bonus = 0;	//Compteur qui  permet de savoir le moment de la fin de l'effet du bonus

	creation_acceuil();
	creation_plateau(p);
	while(p.game_over != 1)
		{
		for(compteur_tour = 0;p.nbgomme != 0;compteur_tour ++)
			{
			p=pacman(p);
			p=fantomes(p,compteur_tour);
			if(p.bonus == 1) //Si bonus mangé par pacman
				{
				compteur_bonus += 1;
				if(compteur_bonus == NB_TOUR_ARRET_BONUS)
					{
					p.bonus = 0;
					compteur_bonus = 0;
					compteur_tour -= NB_TOUR_ARRET_BONUS;
					}
				}
			afficher_donnes_partie(p); //Affiche les données de la partie dans le terminal
			}
		if(p.game_over != 1)
			{
			score = p.score;
			niveau = p.niveau;
			vie = p.vie;
			//afficher image level up 
			p = charge_plan("./data/official_gomme.txt"); //Création du niveau suivant
			p.score = score;
			p.niveau = niveau;
			p.vie = vie;
			//On augmente le nombre permettant de svoir dans quel niveau on se situe
			p.niveau += 1;
			dessin_changement_niveau();
			//Création du nouveau plateau
			creation_plateau(p);
			}
		}
	dessin_game_over();
	/*FERMETURE FENÊTRE GRAPHIQUE*/
	attendre_clic();
	fermer_fenetre();
    return 0;
    }

/******************************************************************************/
/* DEFINITION FONCTIONS                                                       */
/******************************************************************************/
/*CREATION ACCEUIL********************************************************************************************************************/
void creation_acceuil()
	{
	Point zero = {0,0};
	dessiner_rectangle(zero,LARG,HAUT,noir);
	afficher_image("data/page_acceuil.bmp",zero);
	actualiser();

	int touche;
	while(touche != SDLK_SPACE)
		{
		touche = attendre_touche();
		}
	}

/*CREATION PLATEAU**************************************************************************************************************/
void creation_plateau(Partie p)
	{
	int i,j; //les variables qui permettent de lire de tableau contenant les caractères nécéssaires à la création du plateau
	Point coin;	//le point qui permet de dessiner toutes les cases du plateau
	Point zero = {0,0};
	dessiner_rectangle(zero,LARG,HAUT,noir);

	for(i=0;i<p.L;i++)
		{
		for(j=0;j<p.C;j++)
			{
			coin.x = j*CARRE;
			coin.y = i*CARRE;
			
			//Dessin des Murs
			if(p.plateau[i][j] == '*')
				{
				dessiner_rectangle(coin,CARRE-1,CARRE-1,bleumarine); //dessine un carré bleu marine avec un contour noir
				}

			//Dessin des Bonus
			else if(p.plateau[i][j] == 'B')
				{
				coin.x += CARRE/2;
				coin.y += CARRE/2;
				dessiner_disque(coin,GOMME*3,orange); //dessine un rond orange(Bonus)
				}

			//Dessin de 4 Fantômes différents
			else if(p.plateau[i][j] == 'W')
				afficher_image("data/blinky.bmp",coin);//dessine Blinky
			else if(p.plateau[i][j] == 'X')
				afficher_image("data/clyde.bmp",coin);	//dessine Clyde
			else if(p.plateau[i][j] == 'Y')
				afficher_image("data/inky.bmp",coin);	//dessine Inky
			else if(p.plateau[i][j] == 'Z')
				afficher_image("data/pinky.bmp",coin);	//dessine Pinky
					
			//Dessin du joueur(Player)
			else if(p.plateau[i][j] == 'P')
				{
				afficher_image("data/pacman_droite.bmp",coin);	//dessine Pacman		
				}

			//Dessin des Pac-gommes
			else if(p.plateau[i][j] == '.')
				{
				coin.x += CARRE/2;
				coin.y += CARRE/2;
				dessiner_disque(coin,GOMME,gris);	//dessine une gomme grise
				}
			}
		}
	dessin_level(p);
	dessin_score(p);
	dessin_coeurs(p);
	actualiser();
	}

/*DESSIN LEVEL**********************************************************************************************************************/
void dessin_level(Partie p)
	{
	Point effacement_level = {600,100};
	dessiner_rectangle(effacement_level,200,200,noir);
	char compteur_string[10];
	Point level = {610,100};
	Point numero_niveau;
	if(p.niveau < 10)
		{
		numero_niveau.x = 655;
		numero_niveau.y = 150;
		}
	else if(p.niveau < 100)
		{
		numero_niveau.x = 640;
		numero_niveau.y = 150;
		}
	else if(p.niveau < 1000)
		{
		numero_niveau.x = 630;
		numero_niveau.y = 150;
		}
	sprintf(compteur_string, "LEVEL");
	afficher_texte(compteur_string, 40, level,blanc);
	sprintf(compteur_string, "%d",p.niveau);
	afficher_texte(compteur_string, 40,numero_niveau,blanc);
	actualiser();
	}

/*DESSIN SCORE**********************************************************************************************************************/
void dessin_score(Partie p)
	{
	Point effacement_score = {600,300};
	dessiner_rectangle(effacement_score,200,200,noir);
	char compteur_string[10];
	Point score_texte = {600,350};
	Point score;
	if(p.score < 100)
		{
		score.x = 650;
		score.y = 400;
		}
	else if(p.score < 100)
		{
		score.x = 640;
		score.y = 400;
		}
	else if(p.score < 1000)
		{
		score.x = 630;
		score.y = 400;
		}
	else if(p.score < 10000)
		{
		score.x = 620;
		score.y = 400;
		}
	else if(p.score < 100000)
		{
		score.x = 610;
		score.y = 400;
		}
	sprintf(compteur_string, "SCORE");
	afficher_texte(compteur_string, 40,score_texte,blanc);
	sprintf(compteur_string, "%d",p.score);
	afficher_texte(compteur_string, 40,score,blanc);
	actualiser();
	}

/*DESSIN COEURS**********************************************************************************************************************/
void dessin_coeurs(Partie p)
	{
	Point coeur_1 = {561, 600};
	Point coeur_2 = {638, 600};
	Point coeur_3 = {715, 600};
	if(p.vie == 3)
		{
		afficher_image("data/coeur.bmp",coeur_1);
		afficher_image("data/coeur.bmp",coeur_2);
		afficher_image("data/coeur.bmp",coeur_3);
		}
	else if(p.vie == 2)
		{
		afficher_image("data/coeur.bmp",coeur_1);
		afficher_image("data/coeur.bmp",coeur_2);
		dessiner_rectangle(coeur_3,70,59,noir);
		}
	else if(p.vie == 1)
		{
		afficher_image("data/coeur.bmp",coeur_1);
		dessiner_rectangle(coeur_2,70,59,noir);
		dessiner_rectangle(coeur_3,70,59,noir);
		}
	else if(p.vie == 0)
		{
		dessiner_rectangle(coeur_1,70,59,noir);
		dessiner_rectangle(coeur_2,70,59,noir);
		dessiner_rectangle(coeur_3,70,59,noir);
		}
	actualiser();
	}

/*DESSIN PAGE CHANGEMENT DE NIVEAU************************************************************************************************************************/
void dessin_changement_niveau()
	{
	Point zero = {0,0};
	dessiner_rectangle(zero,LARG,HAUT,noir);
	afficher_image("data/page_level.bmp",zero);
	actualiser();
	attente(1000);
	}

/*DESSIN PAGE CHANGEMENT DE NIVEAU************************************************************************************************************************/
void dessin_game_over()
	{
	Point zero = {0,0};
	dessiner_rectangle(zero,LARG,HAUT,noir);
	afficher_image("data/page_game_over.bmp",zero);
	actualiser();
	printf("Vous avez perdu\n");
	}

/*AFFICHAGE DES DONNES PENDANT LE JEU**********************************************************************************************************************/
void afficher_donnes_partie(Partie p)
	{
	#if DEBUG == 1
	printf("\n");
	printf("Pos Pacman : { C %d ; L %d }\n",p.pacman.c ,p.pacman.l); //Donne la position de Pacman à chaque fin de tour
	printf("Pos Blinky : { C %d ; L %d }\n",p.blinky.c,p.blinky.l);	//Donne la position de Blinky à chaque fin de tour
	printf("Pos Clyde  : { C %d ; L %d }\n",p.clyde.c,p.clyde.l);	//Donne la position de Clyde à chaque fin de tour	
	printf("Pos Inky   : { C %d ; L %d }\n",p.inky.c,p.inky.l);	//Donne la position de Inky à chaque fin de tour
	printf("Pos Pinky  : { C %d ; L %d }\n",p.pinky.c,p.pinky.l);	//Donne la position de Pinky à chaque fin de tour
	printf("Gommes restantes : %d\n", p.nbgomme);	//Donne le nombre de Gommes restantes à chaque fin de tour
	printf("Bonus restants : %d\n", p.nbbonus);		//Donne le nombre de Bonus restants à chaque fin de tour
	printf("Score : %d\n",p.score);	//Donne le score à chaque fin de tour
	printf("Nombre de vies restantes : %d\n",p.vie);	//Donne le nombre de vies à chaque fin de tour
	#endif
	dessin_score(p);
	dessin_coeurs(p);
	}

/******************************************************************************/
/* PARTIE PACMAN                                                              */
/******************************************************************************/
/*DEPLACEMENT PACMAN***********************************************************************************************************************/
Partie pacman(Partie p)
	{
	int continuation; //la variable qui permet au reste du programme de savoir si la touche touchée permet au pacman de se déplacer
	int touche;	//la variable qui permet de savoir quelle a été la touche pressée
	
	//Initialisation Pacman
	Point pacman;	//Coordonnés de pacman	
	pacman=pos2point_pacman(p);
	Point old_pacman = pacman; // Réatribution des coordonées de l'ancien pacman
	
	/*Partie Déplacement Pacman*/
	continuation = 0; 
	touche = attendre_touche();	// Déplacement Pacman avec les flèches directionnelles
	if (touche==SDLK_LEFT && p.plateau[p.pacman.l][p.pacman.c-1] != '*')
		{
		continuation = 1;
		p.pacman.c -= 1;
		}
	else if (touche==SDLK_RIGHT && p.plateau[p.pacman.l][p.pacman.c+1] != '*')
		{
		continuation = 1;
		p.pacman.c += 1;
		}
	else if (touche==SDLK_UP && p.plateau[p.pacman.l-1][p.pacman.c] != '*')
		{
		continuation = 1;
		p.pacman.l -= 1;
		}
	else if (touche==SDLK_DOWN && p.plateau[p.pacman.l+1][p.pacman.c] != '*')
		{
		continuation = 1;
		p.pacman.l += 1;
		}

	if (continuation == 1)
		{
		//effacement ancien joueur
		dessiner_rectangle(pacman,CARRE,CARRE,noir);
		//Comptage Score
		p=comptage(p);
		}
	
	//Tunnels
	p=tunnels(p);
	pacman=pos2point_pacman(p);
	
	//effets_pacman
	effets_pacman(p,old_pacman);
   	
	actualiser();
	attente(100);
	return p;
	}

/*POS TO POINT(PACMAN)***************************************************************************************************************************/
Point pos2point_pacman(Partie p)
	{
	Point pacman = {p.pacman.c * CARRE,p.pacman.l * CARRE};
	return pacman;
	}

/*TUNNELS(PACMAN)***************************************************************************************************************************/
Partie tunnels(Partie p)
	{
	if(p.pacman.c < 0) //GAUCHE
		p.pacman.c = p.C-1;	
	else if(p.pacman.c > (p.C-1)) //DROITE
		p.pacman.c = 0;
	return p;	
	}

/*EFFETS PACMAN*****************************************************************************************************************************/
void effets_pacman(Partie p,Point old_pacman)
	{
	Point pacman = pos2point_pacman(p);
	//On redessine Pacman seulement si sa position est différente de sa dernière position
    if(pacman.x == old_pacman.x + CARRE || pacman.x == old_pacman.x - (p.C-1)*CARRE)
	  	{
		effet_devoreur(pacman);
		afficher_image("data/pacman_droite.bmp",pacman);
		}	
	else if(pacman.x == old_pacman.x - CARRE || pacman.x == old_pacman.x + (p.C-1)*CARRE)
		{
		effet_devoreur(pacman);
       	afficher_image("data/pacman_gauche.bmp",pacman); 
		}
	else if(pacman.y == old_pacman.y + CARRE || pacman.y == old_pacman.y - (p.L-1)*CARRE)
      	{
		effet_devoreur(pacman);
		afficher_image("data/pacman_bas.bmp",pacman);
		}                    	 	
	else if (pacman.y == old_pacman.y - CARRE || pacman.y == old_pacman.y + (p.L-1)*CARRE)
		{
		effet_devoreur(pacman);
		afficher_image("data/pacman_haut.bmp",pacman);
		}
	}

/*EFFET DEVOREUR****************************************************************************************************************************/
void effet_devoreur(Point pacman)
	{
	//creation de l'effet devoreur de pacman
	afficher_image("data/pacman_ferme.bmp",pacman);
	actualiser();
	attente(40);
	}

/*COMPTAGE***************************************************************************************************************************/
Partie comptage(Partie p)
	{
	//Comptage des Gommes
	if(p.plateau[p.pacman.l][p.pacman.c] == '.')
	    {
		p.plateau[p.pacman.l][p.pacman.c] = ' ';
		p.nbgomme -= 1;
		//Comptage Score
		if(p.niveau == 1)
			p.score += 20;
		else if(p.niveau == 2)
			p.score += 30;
		else if(p.niveau >= 3 && p.niveau <= 5)
			p.score += 40;
		else if(p.niveau >= 6 && p.niveau <= 8)
			p.score += 50;
		else if(p.niveau >= 9 && p.niveau <= 11)
			p.score += 60;
		else if(p.niveau >= 12 && p.niveau <= 14)
			p.score += 80;
		else if(p.niveau >= 15 && p.niveau <= 18)
			p.score += 100;
		else if(p.niveau >= 19)
			p.score += 120;
		}
	//Comptage des Bonus
	if(p.plateau[p.pacman.l][p.pacman.c] == 'B')
		{
		p.plateau[p.pacman.l][p.pacman.c] = ' ';
		p.nbbonus -= 1;
		p.bonus = 1;
		}
	
	return p;
	}

/*VERIFIACTION VIE************************************************************************************************************/
Partie verification_vie(Partie p,int compteur_tour)
	{
	//Comptage des vies
	if((p.blinky.c == p.pacman.c && p.blinky.l == p.pacman.l)||(p.clyde.c == p.pacman.c && p.clyde.l == p.pacman.l)||(p.inky.c == p.pacman.c && p.inky.l == p.pacman.l)||(p.pinky.c == p.pacman.c && p.pinky.l == p.pacman.l))
		{
		//On enlève une vie
		p.vie -= 1; 

		//On replace pacman au départ
		p.pacman.c = 10;	
		p.pacman.l = 20;
		Point pacman_coin = {p.pacman.c*CARRE,p.pacman.l*CARRE};
		afficher_image("data/pacman_droite.bmp",pacman_coin);

		if(compteur_tour >= 0)
			{
			effacement_old_fantome(p,p.blinky);
			p.blinky.c = 1;	
			p.blinky.l = 1;
			Point blinky_coin = {p.blinky.c*CARRE,p.blinky.l*CARRE};
			afficher_image("data/blinky.bmp",blinky_coin);
			}
		if(compteur_tour >= SORTIE_CLYDE)
			{
			effacement_old_fantome(p,p.clyde);
			p.clyde.c = 19;	
			p.clyde.l = 1;
			Point clyde_coin = {p.clyde.c*CARRE,p.clyde.l*CARRE};
			afficher_image("data/clyde.bmp",clyde_coin);
			}
		if(compteur_tour >= SORTIE_INKY)
			{
			effacement_old_fantome(p,p.inky);
			p.inky.c = 1;	
			p.inky.l = 25;
			Point inky_coin = {p.inky.c*CARRE,p.inky.l*CARRE};
			afficher_image("data/inky.bmp",inky_coin);
			}
		if(compteur_tour >= SORTIE_PINKY)
			{
			effacement_old_fantome(p,p.pinky);
			p.pinky.c = 19;	
			p.pinky.l = 25;
			Point pinky_coin = {p.pinky.c*CARRE,p.pinky.l*CARRE};
			afficher_image("data/pinky.bmp",pinky_coin);
			}
		}

	if(p.vie == 0)	//Si game_over
		{
		p.nbgomme = 0;
		p.game_over = 1;
		}
	return p;
	}

/******************************************************************************/
/* PARTIE FANTÔMES                                                            */
/******************************************************************************/
char direction_aleatoire()
	{
	char direction;
	switch(rand()%16) 
		{
		case 0 : case 1 : case 2: direction = 'N'; break;
		case 3 : case 4 : case 5: case 6 : case 7: direction = 'O'; break;
		case 8 : case 9 : case 10: case 11 : case 12: direction = 'E'; break;
		case 13 : case 14 : case 15:	direction = 'S'; break;
		}	
		printf("DIR --> %c",direction);
	return direction;
	}

Partie fantomes(Partie p,int compteur_tour)
	{
	if(p.bonus == 0)
		{
		if(compteur_tour >= 0)
			{
			if(compteur_tour == 0)
				{
				p=sortie_spawn(p,"blinky");
				}
			p=deplacement_blinky(p);

			if(compteur_tour >= SORTIE_CLYDE)
				{
				if(compteur_tour == SORTIE_CLYDE)
					{
					p=sortie_spawn(p,"clyde");
					}
				p=deplacement_clyde(p);

				if(compteur_tour >= SORTIE_INKY)
					{
					if(compteur_tour == SORTIE_INKY)
						{
						p=sortie_spawn(p,"inky");
						}
					p=deplacement_inky(p);

					if(compteur_tour >= SORTIE_PINKY)
						{
						if(compteur_tour == SORTIE_PINKY)
							{
							p=sortie_spawn(p,"pinky");
							}
						p=deplacement_pinky(p);
						}
					}
				}
			}
		}
	//Vérifiaction vies
	p=verification_vie(p,compteur_tour);
	return p;
	}

/*Sortie spawn Fantome********************************************************************************************************************************/
Partie sortie_spawn(Partie p,char* fantome)
	{
	if(strcmp(fantome,"blinky")==0)
		{
		Point blinky = {p.blinky.c*CARRE,p.blinky.l*CARRE};
		dessiner_rectangle(blinky,CARRE,CARRE,noir);
		p.blinky.c = 10;
		p.blinky.l = 10;
		return p;
		}
	if(strcmp(fantome,"clyde")==0)
		{
		Point clyde = {p.clyde.c*CARRE,p.clyde.l*CARRE};
		dessiner_rectangle(clyde,CARRE,CARRE,noir);
		p.clyde.c = 10;
		p.clyde.l = 10;
		return p;
		}
	if(strcmp(fantome,"inky")==0)
		{
		Point inky = {p.inky.c*CARRE,p.inky.l*CARRE};
		dessiner_rectangle(inky,CARRE,CARRE,noir);
		p.inky.c = 10;
		p.inky.l = 10;
		return p;
		}
	if(strcmp(fantome,"pinky")==0)
		{
		Point pinky = {p.pinky.c*CARRE,p.pinky.l*CARRE};
		dessiner_rectangle(pinky,CARRE,CARRE,noir);
		p.pinky.c = 10;
		p.pinky.l = 10;
		return p;
		}
	return p;
	}	

/*Effacement Fantomes***************************************************************************************************************************/
void effacement_old_fantome(Partie p,Pos old_fantome)
	{
	int gomme = 0;
	int bonus = 0;
	
	Point gomme_bonus = {old_fantome.c*CARRE,old_fantome.l*CARRE};
	if(p.plateau[old_fantome.l][old_fantome.c] == '.')
		gomme = 1;
	else if(p.plateau[old_fantome.l][old_fantome.c] == 'B')
		bonus = 1;

	Point old_fantome_dess={CARRE*old_fantome.c,CARRE*old_fantome.l};
    dessiner_rectangle(old_fantome_dess,CARRE,CARRE,noir);
	if(gomme == 1 || bonus == 1)
		{
		gomme_bonus.x += CARRE/2;
		gomme_bonus.y += CARRE/2;	
		if(gomme == 1)		
			dessiner_disque(gomme_bonus,GOMME,gris);
		else if(bonus == 1)
			dessiner_disque(gomme_bonus,GOMME*3,orange);
		}
	}

/******************************************************************************/
/* 1°)PARTIE BLINKY                                                           */
/******************************************************************************/
/*DEPLACEMENT_BLINKY***************************************************************************************************************************/
Partie deplacement_blinky(Partie p)
	{
	effacement_old_fantome(p,p.blinky);

	if(p.pacman.c > p.blinky.c && p.plateau[p.blinky.l][p.blinky.c+1] != '*')
		{
		p.blinky.c += 1;
		}
    else if(p.pacman.c < p.blinky.c && p.plateau[p.blinky.l][p.blinky.c-1] != '*')
		{
		p.blinky.c -= 1;
		}	 
	else if(p.pacman.l > p.blinky.l && p.plateau[p.blinky.l+1][p.blinky.c] != '*')
		{
		p.blinky.l += 1;
		}
	else if(p.pacman.l < p.blinky.l && p.plateau[p.blinky.l-1][p.blinky.c] != '*')
		{
		p.blinky.l -= 1;
		}
	
	Point new_blinky_dess={CARRE*p.blinky.c,CARRE*p.blinky.l};
	afficher_image("data/blinky.bmp",new_blinky_dess);
	
	actualiser();
	attente(10);
	return p;
	}

/******************************************************************************/
/* 2°)PARTIE CLYDE                                                            */
/******************************************************************************/
/*DEPLACEMENT_CLYDE***************************************************************************************************************************/
Partie deplacement_clyde(Partie p)
	{
	effacement_old_fantome(p,p.clyde);
	char direction = direction_aleatoire();
		
	if(direction == 'E' && p.plateau[p.clyde.l][p.clyde.c+1] != '*')
		p.clyde.c += 1;
    else if(direction == 'O' && p.plateau[p.clyde.l][p.clyde.c-1] != '*')
		p.clyde.c -= 1;
	else if(direction == 'S' && p.plateau[p.clyde.l+1][p.clyde.c] != '*')
		p.clyde.l += 1;
	else if(direction == 'N' && p.plateau[p.clyde.l-1][p.clyde.c] != '*')
		p.clyde.l -= 1;
			
	Point new_clyde_dess={CARRE*p.clyde.c,CARRE*p.clyde.l};
	afficher_image("data/clyde.bmp",new_clyde_dess);
	
	actualiser();
	attente(10);
	return p;
	}

/******************************************************************************/
/* 3°)PARTIE INKY                                                             */
/******************************************************************************/
/*DEPLACEMENT_INKY***************************************************************************************************************************/
Partie deplacement_inky(Partie p)
	{
	effacement_old_fantome(p,p.inky);

	if(p.pacman.c > p.inky.c && p.plateau[p.inky.l][p.inky.c+1] != '*')
		{
		p.inky.c += 1;
		}
    else if(p.pacman.c < p.inky.c && p.plateau[p.inky.l][p.inky.c-1] != '*')
		{
		p.inky.c -= 1;
		}	 
	else if(p.pacman.l > p.inky.l && p.plateau[p.inky.l+1][p.inky.c] != '*')
		{
		p.inky.l += 1;
		}
	else if(p.pacman.l < p.inky.l && p.plateau[p.inky.l-1][p.inky.c] != '*')
		{
		p.inky.l -= 1;
		}
	
	Point new_inky_dess={CARRE*p.inky.c,CARRE*p.inky.l};
	afficher_image("data/inky.bmp",new_inky_dess);
	
	actualiser();
	attente(10);
	return p;
	}

/******************************************************************************/
/* 4°)PARTIE PINKY                                                            */
/******************************************************************************/
/*DEPLACEMENT_PINKY***************************************************************************************************************************/
Partie deplacement_pinky(Partie p)
	{
	effacement_old_fantome(p,p.pinky);

	if(p.pacman.c > p.pinky.c && p.plateau[p.pinky.l][p.pinky.c+1] != '*')
		{
		p.pinky.c += 1;
		}
    else if(p.pacman.c < p.pinky.c && p.plateau[p.pinky.l][p.pinky.c-1] != '*')
		{
		p.pinky.c -= 1;
		}	 
	else if(p.pacman.l > p.pinky.l && p.plateau[p.pinky.l+1][p.pinky.c] != '*')
		{
		p.pinky.l += 1;
		}
	else if(p.pacman.l < p.pinky.l && p.plateau[p.pinky.l-1][p.pinky.c] != '*')
		{
		p.pinky.l -= 1;
		}
	
	Point new_pinky_dess={CARRE*p.pinky.c,CARRE*p.pinky.l};
	afficher_image("data/pinky.bmp",new_pinky_dess);
	
	actualiser();
	attente(10);
	return p;
	}
