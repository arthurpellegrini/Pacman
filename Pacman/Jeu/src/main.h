/******************************************************************************/
/* MAIN.h                                                                     */
/******************************************************************************/
#ifndef MAIN_H
#define MAIN_H

/******************************************************************************/
/* DIRECTIVES PREPROCESSEUR                                                   */
/******************************************************************************/
#include "../lib/libgraphique.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./partie.h" // on a besoin de connaître la structure Partie

#define DEBUG 1

#define LARG	800 //Largeur de la fenêtre graphique
#define HAUT	702 //Hauteur de la fenêtre graphique
#define CARRE 	26	//Taille de chaque case(ne pas changer car utilisation de la fonction afficher_image)
#define GOMME	3   //Taille de chaque gomme
#define NB_TOUR_ARRET_BONUS 7   //Nombre de tours pendant lequel le bonus fait effet
#define SORTIE_CLYDE     15 //Nombre de tours attendu par Clyde avant de sortir du spawn
#define SORTIE_INKY     30  //Nombre de tours attendu par Inky avant de sortir du spawn
#define SORTIE_PINKY    60  //Nombre de tours attendu par Pinky avant de sortir du spawn

/******************************************************************************/
/* PROTOTYPES FONCTIONS (Rangées dans l'ordre du programme)                   */
/******************************************************************************/

void creation_acceuil();    //Cette fonction crée une page d'acceuil
void creation_plateau(Partie p);    //Cette fonction dessine le plateau
void dessin_level(Partie p);    //Cette fonction dessine la partie graphique qui nous montre à quel niveau on est
void dessin_score(Partie p);    //Cette fonction dessine la partie graphique qui nous montre à quel score on est
void dessin_coeurs(Partie p);   //Cette fonction dessine la partie graphique qui nous montre à combien de vies on est
void dessin_changement_niveau();    //Cette fonction dessine la page de changement de niveau
void dessin_game_over();    //Cette fonction dessine la page de game over
void afficher_donnes_partie(Partie p); //Cette fonction affiche les données de la partie dans le terminal

Partie pacman(Partie p);    //Cette fonction permet le fonctionnement de Pacman
Point pos2point_pacman(Partie p);  //Cette fonction traduit Pos Pacman en Point
Partie tunnels(Partie p);   //Cette fonction permet à pacman d'utiliser les tunnels présents sur le plateau
void effets_pacman(Partie p,Point old_pacman); //Cette fonction crée les effets de Pacman lors de la partie
void effet_devoreur(Point pacman);  //Cette fonction donne l'impression que Pacman mange
Partie comptage(Partie p);  //Cette fonction détermine le score de la partie
Partie verification_vie(Partie p,int compteur_tour);  //Cette fonction vérifie le nombre de vies

char direction_aleatoire();
Partie fantomes(Partie p,int compteur_tour);    //Cette fonction permet le fonctionnement des fantômes
Partie deplacement_blinky(Partie p); //Cette fonction permet le déplacment de Blinky
Partie deplacement_clyde(Partie p); //Cette fonction permet le déplacment de Clyde
Partie deplacement_inky(Partie p);  //Cette fonction permet le déplacment de Inky
Partie deplacement_pinky(Partie p); //Cette fonction permet le déplacment de Pinky
Partie sortie_spawn(Partie p,char* fantome);   //Cette fonction fait sortir un fantome de son spawn
void effacement_old_fantome(Partie p,Pos old_fantome);

#endif