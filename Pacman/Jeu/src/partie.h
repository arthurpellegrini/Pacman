/******************************************************************************/
/* CHARGEMENT.h                                                               */
/******************************************************************************/
#ifndef CHARGEMENT_H
#define CHARGEMENT_H

#include <stdio.h>
#include <stdlib.h>

#define NBFANTOMES  4 // nombres de fantômes dans les plateaux chargés

// STRUCTURES
/* Structure Pos: permet de stocker un couple ligne/colonne                   */
typedef struct pos {
    int     l;
    int     c;
    } Pos;

/* Structure Partie:  permet de stocker les paramètres d'une partie           */
typedef struct partie {
    char ** plateau; // le tableau de caractères contenant le plateau de jeu
    int     L; // le nombre de lignes du plateau de jeu
    int     C; // le nombre de colonne du plateau de jeu
    Pos     pacman; // la position de Pacman dans le plateau
    Pos     blinky; // la position de Blinky dans le plateau
    Pos     clyde;  // la position de Clyde dans le plateau
    Pos     inky;   // la position de Inky dans le plateau
    Pos     pinky;  // la position de Pinky dans le plateau
    int     nbbonus; // le nombre de bonus restants à manger
    int     nbgomme; // le nombre de gommes restantes
    int     score; //le score de la partie
    int     niveau; //le nombre qui nous permet de savoir le niveau actuel
    int     vie;    // le nombre de vie de pacman
    int     bonus; //le nombre qui permet de savoir si un bonus a été pris
    int     game_over; //le nombre qui permet de savoir si on a perdu
    } Partie;

// PROTOTYPES
/* charge_plan : lit un fichier contenant un plateau de jeu et le charge
                    en mémoire, dans le champ 'plateau' d'une Partie */
Partie charge_plan(char *fichier);

#endif
