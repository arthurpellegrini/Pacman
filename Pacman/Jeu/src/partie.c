/******************************************************************************/
/* CHARGEMENT.c                                                               */
/******************************************************************************/
#include "./partie.h"


/******************************************************************************/
/* CHARGE PLAN                                                                */
/******************************************************************************/
Partie charge_plan(char *fichier)
    {
    Partie  p;
    FILE    *f = fopen(fichier,"r"); // Ouverture en lecture du fichier
    p.plateau = NULL;   // Le futur plan, à allouer dynamiquement.
    int     res, l, c;
    int     nbb;        // Nb de bonus trouvés sur le plan
    int     nbg;        // Nb de gommes trouvés sur le plan
    char    ch;

    if(!f) // Si f== NULL, ouverture ratée
        {
        printf("Impossible d'ouvrir '%s'\n",fichier);
        exit(0);
        }
    
/* Lecture des dimensions du plan en en-tête                                  */
    res = fscanf(f,"%d %d\n",&p.L,&p.C); // Lecture de deux entiers

// Si on n'a pas pu lire deux entiers ou s'ils sont incorrects
    if(res !=2 || p.C<2 || p.L<2 || p.C >800 || p.L>600) 
        {
        printf("Dimensions du tableau lues dans '%s' incorrectes\n",fichier);
        fclose(f);
        exit(0);
        }
    #if DEBUG == 1
    printf("Dimensions lues: %d x %d\n",p.L,p.C);
    #endif

/* ALLOCATION DYNAMIQUE                                                       */
/* Allocation du tableau de *L pointeurs sur lignes                           */
    p.plateau = (char **) malloc(p.L * sizeof(char *));
    if(p.plateau == NULL)
        {
        printf("Allocation dynamique impossible\n");
        fclose(f);
        exit(0);
        }
    
/* Allocation des tableaux de *C caractères                                   */
    for(l=0;l!=p.L;l++)
        {
        p.plateau[l] = (char *) malloc(p.C * sizeof(char));
        if(p.plateau[l] == NULL)
            {
            printf("Allocation dynamique impossible\n");
            fclose(f);
            exit(0);
            }
        }
    

/* LECTURE DES LIGNES DU PLAN                                                 */
    l = 0;
    res = 0;
    nbb = 0; //nombre de bonus 
    nbg = 0;    //nombre de gommes
    while(res != EOF) // Lecture de chaque ligne
        {
        c=0;
        while(1)
            {
            res = fscanf(f,"%c",&ch); // Lecture d'un caractère
            if (res == EOF) // Si fin de fichier
                break; // Quittons la boucle interne
    
            if(c>p.C) // Si trop de colonnes...
                {
                printf("Ligne %d colonne %d: trop de colonnes\n",l,c);
                fclose(f);
                exit(0);
                }
    
            if(c==p.C) // Si fin de ligne supposée...
                {
                if(ch=='\n') // Si fin de ligne réelle, on quitte la boucle
                    {
                    break;
                    }
                else // Sinon trop de caractères
                    {
                    printf("Ligne %d: trop de caractères\n",l);
                    fclose(f);
                    exit(0);
                    }
                }
/* ...sinon, nous ne sommes pas à la fin de la ligne.                         */
/* Si on lit un caractère interdit...                                         */
            if(ch!='.' && ch!=' ' && ch!= '*' && ch!='P' && ch!='W' && ch!='X'&& ch!='Y'&& ch!='Z'&& ch!='B')
                {
                if(ch=='\n') // Si c'est un saut de ligne
                    printf("Ligne %d: trop peu de caractères\n",l);
                else
                    printf("Ligne %d: caractère '%c' incorrect\n",l,ch);
    
                fclose(f);
                exit(0);
                }
            
            if(ch=='.')
                nbg++;

            else if(ch=='P')
                {
                p.pacman.l = l;
                p.pacman.c = c;
                }

            else if(ch=='W')
                {
                p.blinky.l = l;
                p.blinky.c = c;
                }

            else if(ch=='X')
                {
                p.clyde.l = l;
                p.clyde.c = c;
                }

            else if(ch=='Y')
                {
                p.inky.l = l;
                p.inky.c = c;
                }

            else if(ch=='Z')
                {
                p.pinky.l = l;
                p.pinky.c = c;
                }

            else if(ch=='B')
                nbb++;

            p.plateau[l][c] = ch; // Ecriture dans le plan
    
            c++; // caractère suivant
            }
        l++; // ligne suivante
        }
    
    fclose(f); // Fermeture du flux de lecture du fichier
    
/* Si à la lecture de EOF on n'est pas sur la *V+1 ème ligne...               */
    if(l != p.L+1)
        {
        printf("Ligne %d: nb de lignes incorrect\n",l);
        exit(0);
        }

/* Si pas de bonus....                                                       */
    if(nbb==0)
        {
        printf("Aucun bonus sur le plan!\n");
        fclose(f);
        exit(0);
        }
    p.nbbonus = nbb;
    p.nbgomme = nbg - 1; //Nombre de gommes sur dans le tableau
    p.bonus = 0;    //Bonus non-utilisés lors de lancement de partie donc 0
    p.game_over = 0;    //Aucunes vies perdus au début du jeu donc 0

    return p;
    }