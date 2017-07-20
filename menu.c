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
 * File:   menu.c
 * Author: diz
 *
 * Created on April 23, 2015, 22:23 PM
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variablesGlobales.h"
#include "maps.h"

static void bougerFleche(SDL_Rect posFlecheMenuG, SDL_Rect posFlecheMenuD);

void menu(){
    SDL_Rect posFlecheMenuG, posFlecheMenuD;
    posFlecheMenuG.x = 249, posFlecheMenuG.y = 445;
    posFlecheMenuD.x = 529, posFlecheMenuD.y = 445;
    SDL_Event e;
    channel = Mix_PlayChannel(-1, bg_music, -1);
    if(channel == -1) {
	printf("Echec de la lecture de l'audio!:\n%s\n" , Mix_GetError());
    }
    while( !quitter ){
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT ){
                quitter = 1;
            }
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_RETURN){
                    bougerFleche(posFlecheMenuG, posFlecheMenuD);
                    jeu();
                }
            }
        }
        if(!quitter){
            SDL_BlitSurface( Menu, NULL, ecran, NULL );
            SDL_BlitSurface( FlecheMenuG, NULL, ecran, &posFlecheMenuG );
            SDL_BlitSurface( FlecheMenuD, NULL, ecran, &posFlecheMenuD );
            SDL_UpdateWindowSurface( fenetre );
        }
    }
}

static void bougerFleche(SDL_Rect posFlecheMenuG, SDL_Rect posFlecheMenuD){
    int i;
    for(i=0;i<40;i++){
        posFlecheMenuG.x++;
        posFlecheMenuD.x--;
        SDL_BlitSurface( Menu, NULL, ecran, NULL );
        SDL_BlitSurface( FlecheMenuG, NULL, ecran, &posFlecheMenuG );
        SDL_BlitSurface( FlecheMenuD, NULL, ecran, &posFlecheMenuD );
        SDL_UpdateWindowSurface( fenetre );
        SDL_Delay(15);
    }
    for(i=0;i<40;i++){
        posFlecheMenuG.x--;
        posFlecheMenuD.x++;
        SDL_BlitSurface( Menu, NULL, ecran, NULL );
        SDL_BlitSurface( FlecheMenuG, NULL, ecran, &posFlecheMenuG );
        SDL_BlitSurface( FlecheMenuD, NULL, ecran, &posFlecheMenuD );
        SDL_UpdateWindowSurface( fenetre );
        SDL_Delay(15);
    }
}