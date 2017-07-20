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
 * File:   deplacement.c
 * Author: diz
 *
 * Created on 24 avril 2015, 16:47
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deplacement.h"
#include "variablesGlobales.h"
#include "affichage.h"

void deplacerPerso(){
    switch(direction){
        case HAUT:
            switch((seDeplace-1)%3+1){
                case 1:
                    persoMapping[perso.ligne][perso.colonne] = BACK_MOVE_1;
                    perso.positionPerso.y = perso.positionPerso.y - 8;
                    break;
                case 2:
                    persoMapping[perso.ligne][perso.colonne] = BACK_MOVE_2;
                    perso.positionPerso.y = perso.positionPerso.y - 9;
                    break;
                case 3:
                    perso.positionPerso.y = perso.positionPerso.y - 8;
                    if(seDeplace==6){
                        persoMapping[perso.ligne][perso.colonne] = VIDE;
                        perso.ligne--;
                        avance=1;
                    }
                    persoMapping[perso.ligne][perso.colonne] = BACK;
                    break;
                default:
                    break;
            }
            break;
        case GAUCHE:
            switch((seDeplace-1)%3+1){
                case 1:
                    persoMapping[perso.ligne][perso.colonne] = SIDE_2_MOVE_1;
                    perso.positionPerso.x = perso.positionPerso.x - 8;
                    break;
                case 2:
                    persoMapping[perso.ligne][perso.colonne] = SIDE_2_MOVE_2;
                    perso.positionPerso.x = perso.positionPerso.x - 9;
                    break;
                case 3:
                    perso.positionPerso.x = perso.positionPerso.x - 8;
                    if(seDeplace==6){
                        persoMapping[perso.ligne][perso.colonne] = VIDE;
                        perso.colonne--;
                        avance=1;
                    }
                    persoMapping[perso.ligne][perso.colonne] = SIDE_2;
                    break;
                default:
                    break;
            }
            break;
        case BAS:
            switch((seDeplace-1)%3+1){
                case 1:
                    persoMapping[perso.ligne][perso.colonne] = FRONT_MOVE_1;
                    perso.positionPerso.y = perso.positionPerso.y + 8;
                    break;
                case 2:
                    persoMapping[perso.ligne][perso.colonne] = FRONT_MOVE_2;
                    perso.positionPerso.y = perso.positionPerso.y + 9;
                    break;
                case 3:
                    perso.positionPerso.y = perso.positionPerso.y + 8;
                    if(seDeplace==6){
                        persoMapping[perso.ligne][perso.colonne] = VIDE;
                        perso.ligne++;
                        avance=1;
                    }
                    persoMapping[perso.ligne][perso.colonne] = FRONT;
                    break;
                default:
                    break;
            }
            break;
        case DROITE:
            switch((seDeplace-1)%3+1){
                case 1:
                    persoMapping[perso.ligne][perso.colonne] = SIDE_1_MOVE_1;
                    perso.positionPerso.x = perso.positionPerso.x + 8;
                    break;
                case 2:
                    persoMapping[perso.ligne][perso.colonne] = SIDE_1_MOVE_2;
                    perso.positionPerso.x = perso.positionPerso.x + 9;
                    break;
                case 3:
                    perso.positionPerso.x = perso.positionPerso.x + 8;
                    if(seDeplace==6){
                        persoMapping[perso.ligne][perso.colonne] = VIDE;
                        perso.colonne++;
                        avance=1;
                    }
                    persoMapping[perso.ligne][perso.colonne] = SIDE_1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

/*
 * Vérifie si une case est une transition
 */
int estTransition(){
    int resultat;
    switch(mapMapping[perso.ligne][perso.colonne]){
        case HERBE_TRANSIT:
            resultat = 1;
            break;
        case NUAGE_TRANSIT:
            resultat = 1;
            break;
        case TERRE_TRANSIT:
            resultat = 1;
            break;
        case EAU_PONT_TRANSIT:
            resultat = 1;
            break;
        case FEU_TRANSIT:
            resultat = 1;
            break;
        default:
            resultat = 0;
            break;
    }
    return resultat;
}

/*
 * Vérifie si le personnage peut marcher sur la tuile
 */
int estAccessible(int tuile){
    int resultat;
    switch(tuile){
        case HERBE:
            resultat = 1;
            break;
        case HERBE_TRANSIT:
            resultat = 1;
            break;
        case NUAGE:
            resultat = 1;
            break;
        case NUAGE_TRANSIT:
            resultat = 1;
            break;
        case TERRE:
            resultat = 1;
            break;
        case TERRE_TRANSIT:
            resultat = 1;
            break;
        case EAU_PONT:
            resultat = 1;
            break;
        case EAU_PONT_TRANSIT:
            resultat = 1;
            break;
        case FEU:
            resultat = 1;
            break;
        case FEU_TRANSIT:
            resultat = 1;
            break;
        case NUAGE_CHECKPOINT_ROUGE:
            resultat = 1;
            break;
        case NUAGE_CHECKPOINT_VERT:
            resultat = 1;
            break;
        case WATER_RED:
            resultat = 1;
            break;
        case WATER_GREEN:
            resultat = 1;
            break;
        default:
            resultat = 0;
            break;
    }
    return resultat;
}

void changeOrientationPerso(int orientation){
    switch(orientation){
        case HAUT:
            persoMapping[perso.ligne][perso.colonne] = BACK;
            break;
        case BAS:
            persoMapping[perso.ligne][perso.colonne] = FRONT;
            break;
        case GAUCHE:
            persoMapping[perso.ligne][perso.colonne] = SIDE_2;
            break;
        case DROITE:
            persoMapping[perso.ligne][perso.colonne] = SIDE_1;
            break;
        default:
            break;
    }
}

/*
 * Vérifie si la touche (appuyée) est une touche de déplacemnt
 */
SDL_Keycode estToucheDeDeplacement(SDL_Keycode touche){
    SDL_Keycode resultat;
    switch(touche){
        case SDLK_z:
            resultat = SDLK_z;
            break;
        case SDLK_q:
            resultat = SDLK_q;
            break;
        case SDLK_s:
            resultat = SDLK_s;
            break;
        case SDLK_d:
            resultat = SDLK_d;
            break;
        default:
            resultat = SDLK_UNKNOWN;
            break;
    }
    return resultat;
}

int verifEstDevantCoupe(){
    int estDevant = 0;
    switch(direction){
        case HAUT:
            estDevant = verifEstDevantCoupe_2(perso.ligne-1, perso.colonne);
            break;
        case GAUCHE :
            estDevant = verifEstDevantCoupe_2(perso.ligne, perso.colonne-1);
            break;
        case BAS : 
            estDevant = verifEstDevantCoupe_2(perso.ligne+1, perso.colonne);
            break;
        case DROITE : 
            estDevant = verifEstDevantCoupe_2(perso.ligne, perso.colonne+1);
            break;
        default:
            break;
    }
    return estDevant;
}

int verifEstDevantCoupe_2(int ligne, int colonne){
    int estDevant = 0;
    if(mapMapping[0][0] != HERBE){
        if(mapMapping[ligne][colonne] == COUPE_AIR)
            estDevant = 1;                             
        else if(mapMapping[ligne][colonne] == COUPE_TERRE)
            estDevant = 1;                
        else if(mapMapping[ligne][colonne] == COUPE_EAU)
            estDevant = 1;                
        else if(mapMapping[ligne][colonne] == COUPE_FEU)
            estDevant = 1;                
    }
    if(mapMapping[0][0] == HERBE && mapMapping[ligne][colonne] == COUPE){
        if(perso.elementAir == 1)
            estDevant = 1;
        else if(perso.elementTerre == 1)
            estDevant = 1;
        else if(perso.elementEau == 1)
            estDevant = 1;
        else if(perso.elementFeu == 1)
            estDevant = 1;
    }
    return estDevant;
}