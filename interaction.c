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
 * File:   interaction.h
 * Author: diz
 *
 * Created on 9 mai 2015, 19:15
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interaction.h"
#include "variablesGlobales.h"

void prendre_deposer_Orbe(){
    switch(direction){
        case HAUT:
            prendre_deposer_Orbe_2(perso.ligne-1, perso.colonne);
            break;
        case GAUCHE : 
            prendre_deposer_Orbe_2(perso.ligne, perso.colonne-1);
            break;
        case BAS : 
            prendre_deposer_Orbe_2(perso.ligne+1, perso.colonne);
            break;
        case DROITE : 
            prendre_deposer_Orbe_2(perso.ligne, perso.colonne+1);
            break;
        default:
            break;
    }
}

void prendre_deposer_Orbe_2(int ligne, int colonne){
    if(mapMapping[0][0] != HERBE){
        if(mapMapping[ligne][colonne] == COUPE_AIR){
            perso.elementAir = 1;
            mapMapping[ligne][colonne] = COUPE;
        }                
        else if(mapMapping[ligne][colonne] == COUPE_TERRE){
            perso.elementTerre = 1;
            mapMapping[ligne][colonne] = COUPE;
        }
        else if(mapMapping[ligne][colonne] == COUPE_EAU){
            perso.elementEau = 1;
            mapMapping[ligne][colonne] = COUPE;
        }
        else if(mapMapping[ligne][colonne] == COUPE_FEU){
            perso.elementFeu = 1;
            mapMapping[ligne][colonne] = COUPE;
        }
    }
}