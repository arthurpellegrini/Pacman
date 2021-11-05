<img src="https://i.goopics.net/juw6pg.png" alt="drawing" width="300" heigth="300"/>

Projet Pac-Man
==============================================================

Description
--------------------------------------------------------------

Tout d'abord, ce jeu a été réalisé en binôme dans le cadre de notre premier projet tuteuré de programmation de notre première année de DUT Informatique à l'IUT de Vélizy.
Le jeu est codé en langage C et utilise la librairie SDL_2.
Bien que le projet, de par son nom fasse penser au jeu Pac-Man, notre version n'a pas les mêmes fonctionnalités que le jeu original.

##### Qu'est-ce que Pac-Man? 

* Pac-Man est un ancien jeu, dans lequel nous contrôlons Pac-Man, une boule jaune qui doit manger toutes les gommes d'un niveau pour pouvoir passer au niveau suivant
* Mais 4 fantômes(Blinky, Clyde, Inky et Pinky) sont là pour vous faire perdre
* Pac-Man a trois vies, si le touche, il perd une de ses vies
* C'est pourquoi Pac-Man peut manger une des quatre Pac-gommes présentes sur le niveau, celles-ci figeant les fantômes pendant quelques secondes

Visuel
--------------------------------------------------------------

Voici des captures d'écran du jeu.
![Visuels du jeu][visuals]

Installation
--------------------------------------------------------------

Voici les étapes à suivre pour pouvoir tester notre jeu. 
Le jeu est exécutable sur un système linux en suivant ces étapes, mais il est important de préciser qu'il est aussi exécutable sur un autre type de système moyennant des manipulations pour installer le langage C et la librairie SDL_2.

##### Première étape

Vous devez télécharger le dossier pacman. Pour cela cliquer sur le logo Github ci-dessous.

[<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/91/Octicons-mark-github.svg/2048px-Octicons-mark-github.svg.png" alt="drawing" width="40" heigth="40"/>](https://github.com/arthurpellegrini/pac-man)

Ensuite aller sur le bouton vert "code" et sélectionner "download zip".

##### Deuxième étape

Maintenant, il va falloir extraire le code source du dossier compressé. Pour cela faites la commande suivante dans le terminal : 
 ```sh
 unzip Downloads/pacman.zip -d Downloads/pacman
 ```

##### Troisième étape

Enfin, il faudra exécuter cette commande dans un terminal pour lancer le jeu : 

```sh
$ bash Downloads/pacman/script_pacman.sh
```

Désormais, le jeu doit s'être lancé, il ne vous reste plus qu'à jouer !

Usage
--------------------------------------------------------------

Quand vous lancer le jeu, vous devez presser la touche espace pour lancer une partie, et ensuite utiliser les flèches directionnelles de votre clavier pour jouer.

Support
--------------------------------------------------------------

Si vous avez une question ou un problème, n'hésitez pas à nous contacter à l'adresse mail suivante : projet.pacman@gmail.com

Feuille de route
--------------------------------------------------------------

* Fixer les bugs connus
* Améliorer l'IA des fantômes
* Améliorer les graphismes du jeu en augmentant la taille de la fenêtre
* Ajouter des niveaux différents du jeu original 


Contributions
--------------------------------------------------------------

Nous sommes ouverts à tout type de contributions pour les graphismes et le code du jeu. Les personnes qui le souhaitent peuvent proposer des changements par l'intermédiaire de Github en proposant des "commits".

Auteurs et remerciements
--------------------------------------------------------------

Les auteurs de ce projet sont les suivants : 

* BACAR-MLATAME Samir 
* PELLEGRINI Arthur

Nous remercions aussi les personnes suivantes de nous avoir aidées lors du développement de ce jeu : 

* GARDY Daniele 
* JUSSEAUME Jonathan
* MARSAN Laurent 

Statut du projet 
--------------------------------------------------------------

Le développement de ce projet a été stoppé après la transmission de celui-ci au jury de notre Université. Mais il est possible que le jeu soit amélioré par la suite.

[//]: # (Lien de référence utilisé dans le corps du Markdown)
[visuals]: https://i.goopics.net/89mj9g.png