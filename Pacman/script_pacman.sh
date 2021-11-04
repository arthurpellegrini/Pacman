#!/bin/bash
cd Jeu

#Installation de la librairie SDL
cd lib
bash INSTALL_PACK_SDL
echo -e "\nLibrairie SDL installée\n" #Chemin d'installation de la librairie --> /usr/share/doc/libsdl-ttf2.0-dev
cd ..

#Lancement du jeu
make clean all
echo -e "\nLancement du jeu\n"
./resultat