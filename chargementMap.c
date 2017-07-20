/*
 *  Elements is an adventure game
 *  Copyright (C) 2015  Basilien Simon, Calvo Florian, Rouy Quentin
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 *  To contact us
 *  Florian.Calvo-Martin@telecomnancy.eu
 *  Simon.Basilien@telecomnancy.eu
 *  Quentin.Rouy@telecomnancy.eu
 * 
 */

/* 
 * File:   chargementMap.c
 * Author: diz
 *
 * Created on 24 avril 2015, 12:09
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variablesGlobales.h"

int chargerFichierMap(int mapMapping[MAP_HAUTEUR][MAP_LARGEUR], char nomFichier[]){
    FILE *fichier = NULL;
    int j = 0;
    
    fichier = fopen(nomFichier, "r");
    if(fichier == NULL)
        return 0;
    
    for(j = 0 ; j < MAP_HAUTEUR ; j++)
    {
        fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &mapMapping[j][0], &mapMapping[j][1], &mapMapping[j][2], &mapMapping[j][3], &mapMapping[j][4], &mapMapping[j][5], &mapMapping[j][6], &mapMapping[j][7], &mapMapping[j][8], &mapMapping[j][9], &mapMapping[j][10], &mapMapping[j][11], &mapMapping[j][12], &mapMapping[j][13], &mapMapping[j][14], &mapMapping[j][15]);
    }
    
    fclose(fichier);
    
    return 1;
}

int chargerMap(int ligne,int colonne){
    if(ligne>=0 && ligne<100 && colonne>=0 && colonne<100){
        char ligneMap[2] = "";
        char colonneMap[2] = "";
        char nomMap[10] = "";
        sprintf(ligneMap, "%d", ligne);
        sprintf(colonneMap, "%d", colonne);
        strcat(strcat(strcat(strcat(nomMap,"map_"), ligneMap),"_"),colonneMap);
        return chargerFichierMap(mapMapping, nomMap);
    }else{
        return 0;
    }
}

void changerMap(int direction){
    switch(direction){
        case HAUT:
            if(chargerMap(--map.ligne,map.colonne)){
                persoMapping[0][7] = VIDE, persoMapping[11][7] = BACK;
                perso.ligne = 11;
                perso.positionPerso.y = perso.ligne * TUILE_HAUTEUR +30;
            }
            break;
        case GAUCHE:
            if(chargerMap(map.ligne,--map.colonne)){
                persoMapping[5][0] = VIDE, persoMapping[5][15] = SIDE_2;
                perso.colonne = 15;
                perso.positionPerso.x = perso.colonne * TUILE_LARGEUR;
            }
            break;
        case BAS:
            if(chargerMap(++map.ligne,map.colonne)){
                persoMapping[11][7] = VIDE, persoMapping[0][7] = FRONT;
                perso.ligne = 0;
                perso.positionPerso.y = 30;
            }
            break;
        case DROITE:
            if(chargerMap(map.ligne,++map.colonne)){
                persoMapping[5][15] = VIDE, persoMapping[5][0] = SIDE_1;
                perso.colonne = 0;
                perso.positionPerso.x = 0;
            }
            break;
    }
}