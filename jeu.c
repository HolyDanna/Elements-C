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
 * File:   map_7_5.c
 * Author: diz
 *
 * Created on April 24, 2015, 11:23 PM
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variablesGlobales.h"
#include "chargementMap.h"
#include "affichage.h"
#include "deplacement.h"
#include "interaction.h"
#include "maps.h"
#include "script.h"

void jeu(){
    seDeplace = 0;
    int vitesse = SPEED_WALK;
    perso.elementAir = 0;
    perso.elementTerre = 0;
    perso.elementEau = 0;
    perso.elementFeu = 0;
    const Uint8 *etatTouches = SDL_GetKeyboardState(NULL);
    SDL_Keycode nouvelleDirection = SDLK_UNKNOWN;
    
    tile.w = TUILE_LARGEUR;
    tile.h = TUILE_HAUTEUR;
    tilePerso.w = TUILE_LARGEUR;
    tilePerso.h = TUILE_HAUTEUR;
    
    perso.ligne = 5;
    perso.colonne = 7;
    persoMapping[perso.ligne][perso.colonne] = FRONT;
    perso.positionPerso.x = perso.colonne * TUILE_LARGEUR;
    perso.positionPerso.y = perso.ligne * TUILE_HAUTEUR +30;
    
    map.ligne = 5;
    map.colonne = 7;
    chargerMap(map.ligne,map.colonne);
    SDL_Event e;
    tempsSave = SDL_GetTicks();
    while( !quitter ){
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT ){
                quitter = 1;
                break;
            }
            if(e.type == SDL_KEYDOWN){
                if(estToucheDeDeplacement(e.key.keysym.sym)){
                    nouvelleDirection = e.key.keysym.sym;
                }
                else if((perso.elementAir == 1 && e.key.keysym.sym == SPEED) || e.key.keysym.sym == DEV_MODE){
                    if(vitesse == SPEED_WALK && e.key.keysym.sym == SPEED)
                        vitesse = SPEED_RUN;
                    else if(vitesse == SPEED_WALK && e.key.keysym.sym == DEV_MODE)
                        vitesse = SPEED_DEV;
                    else vitesse = SPEED_WALK;
                }
                else if(e.key.keysym.sym == PRENDRE && verifEstDevantCoupe()){
                    prendre_deposer_Orbe();
                }
            }
            if(e.type == SDL_KEYUP){
                if(nouvelleDirection == e.key.keysym.sym){
                    nouvelleDirection = SDLK_UNKNOWN;
                }
                else if(e.key.keysym.sym == SPEED){
                    vitesse=SPEED_WALK;
                }
            }
        }
        if(!quitter){
            if(seDeplace == 0){
                if(nouvelleDirection != SDLK_UNKNOWN && etatTouches[SDL_GetScancodeFromKey(nouvelleDirection)] == 0){
                    nouvelleDirection = SDLK_UNKNOWN;
                }
                if(nouvelleDirection == HAUT){
                    if(perso.ligne!=0){
                        if(estAccessible(mapMapping[perso.ligne-1][perso.colonne]))
                            seDeplace = 1;
                        else
                            changeOrientationPerso(HAUT);
                        direction = HAUT;
                    }
                    else if(estTransition()){
                        changerMap(HAUT);
                    }
                    else changeOrientationPerso(HAUT);
                }
                if(nouvelleDirection == GAUCHE){
                    if(perso.colonne!=0){
                        if(estAccessible(mapMapping[perso.ligne][perso.colonne-1]))
                            seDeplace = 1;
                        else
                            changeOrientationPerso(GAUCHE);
                        direction = GAUCHE;
                    }
                    else if(estTransition()){
                        changerMap(GAUCHE);                        
                    }
                    else changeOrientationPerso(GAUCHE);
                }
                if(nouvelleDirection == BAS){
                    if(perso.ligne!=11){
                        if(estAccessible(mapMapping[perso.ligne+1][perso.colonne]))
                            seDeplace = 1;
                        else
                            changeOrientationPerso(BAS);
                        direction = BAS;
                    }
                    else if(estTransition()){
                        changerMap(BAS);
                    }                    
                    else changeOrientationPerso(BAS);
                }
                if(nouvelleDirection == DROITE){
                    if(perso.colonne!=15){
                        if(estAccessible(mapMapping[perso.ligne][perso.colonne+1]))
                            seDeplace = 1;
                        else
                            changeOrientationPerso(DROITE);
                        direction = DROITE;
                    }
                    else if(estTransition()){
                        changerMap(DROITE);                        
                    }
                    else changeOrientationPerso(DROITE);
                }
            }
            script();
            tempsActuel = SDL_GetTicks();
            if(etatTouches[SDL_SCANCODE_LSHIFT] == 0){
                if(vitesse == SPEED_RUN){
                    vitesse = SPEED_WALK;
                }
            }
            if(seDeplace!=0 && tempsActuel - tempsSave > vitesse){
                deplacerPerso(seDeplace, direction);
                if(seDeplace==6)
                    seDeplace=0;
                else
                    seDeplace++;
                tempsSave = tempsActuel;
            }
            afficher();
        }
    }
}