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
 * File:   main.c
 * Author: quentin
 *
 * Created on April 21, 2015, 2:54 PM
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variablesGlobales.h"
#include "menu.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 650;

int init(){
    int success = 1;
    fenetre = SDL_CreateWindow( "Elements", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( fenetre == NULL ){
        printf( "Impossible de créer la fenetre! SDL_Error: %s\n", SDL_GetError() );
        success = 0;
    }else{
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) ){
            printf( "Impossible d'initialiser SDL_image! SDL_image Error: %s\n", IMG_GetError() );
            success = 0;
        }else{
            ecran = SDL_GetWindowSurface( fenetre );
        }
    }
    return success;
}

SDL_Surface* loadSurface( char* path ){
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ){
        printf( "Impossible de charger l'image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }else{
        optimizedSurface = SDL_ConvertSurface( loadedSurface, ecran->format, 0 );
        if( optimizedSurface == NULL ){
            printf( "Impossible d'optimiser l'image %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        SDL_FreeSurface( loadedSurface );
    }
    return optimizedSurface;
}

int loadMedia(){
    int success = 1;
    Menu = loadSurface( "pictures/Menu.png" );
    if( Menu == NULL ){
        printf( "Echec du chargement de l'image Menu!\n" );
        success = 0;
    }
    FlecheMenuG = loadSurface( "pictures/FlecheMenuG.png" );
    if( FlecheMenuG == NULL ){
        printf( "Echec du chargement de l'image FlecheMenuG!\n" );
        success = 0;
    }
    FlecheMenuD = loadSurface( "pictures/FlecheMenuD.png" );
    if( FlecheMenuD == NULL ){
        printf( "Echec du chargement de l'image FlecheMenuD!\n" );
        success = 0;
    }
    PersoTileSet = loadSurface( "pictures/PersoTileSet.png" );
    if( PersoTileSet == NULL ){
        printf( "Echec du chargement de l'image PersoTileSet!\n" );
        success = 0;
    }
    MapTileSet = loadSurface( "pictures/MapTileSet.png" );
    if( MapTileSet == NULL ){
        printf( "Echec du chargement de l'image MapTileSet!\n" );
        success = 0;
    }
    ObjetsTileSet = loadSurface( "pictures/ObjetsTileSet.png" );
    if( ObjetsTileSet == NULL ){
        printf( "Echec du chargement de l'image ObjetsTileSet!\n" );
        success = 0;
    }
    Headers = loadSurface( "pictures/Headers.png" );
    if( Headers == NULL ){
        printf( "Echec du chargement de l'image Headers!\n" );
        success = 0;
    }
    Cadre_texte = loadSurface( "pictures/Fond_texte.png" );
    if( Cadre_texte == NULL ){
        printf( "Echec du chargement de l'image Fond_texte!\n" );
        success = 0;
    }
    Police = TTF_OpenFont("fonts/VCR_OSD_MONO.ttf", TAILLE_POLICE);
    if( !Police){
        printf( "Echec du chargement de la police!:\n%s\n", TTF_GetError());
        success=0;
    }
    bg_music = Mix_LoadWAV("music/Rolemusic_-_She_Is_My_Best_Treasure.wav");
    if(bg_music == NULL) {
	printf("Echec du chargement de l'audio!:\n%s\n" , Mix_GetError());
        success=0;
    }
    return success;
}

void close(){
    SDL_FreeSurface( Menu );
    Menu = NULL;
    SDL_FreeSurface( FlecheMenuG );
    FlecheMenuG = NULL;
    SDL_FreeSurface( FlecheMenuD );
    FlecheMenuD = NULL;
    SDL_FreeSurface( PersoTileSet );
    PersoTileSet = NULL;
    SDL_FreeSurface( MapTileSet );
    MapTileSet = NULL;
    SDL_FreeSurface( ObjetsTileSet );
    ObjetsTileSet = NULL;
    SDL_FreeSurface( Headers );
    Headers = NULL;
    SDL_FreeSurface(Cadre_texte);
    Cadre_texte=NULL;
    SDL_DestroyWindow( fenetre );
    fenetre = NULL;
    TTF_CloseFont(Police);
    Police=NULL;
    TTF_Quit();
    IMG_Quit();
}

int main(){
    quitter = 0;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )    {
        printf( "Problème d'initialisation SDL! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }else{
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            printf("Problème d'initialisation Mixer! SDL_Error: %s\n", TTF_GetError() );
            return 1;
        }

        int audio_rate = 22050;
        Uint16 audio_format = AUDIO_S16SYS;
        int audio_channels = 2;
        int audio_buffers = 4096;

        if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
            printf("Problème d'ouverture audio! SDL_Error: %s\n", Mix_GetError() );
            return 1;
        }
        if( TTF_Init() < 0 )    {
            printf( "Problème d'initialisation TTF! SDL_Error: %s\n", TTF_GetError() );
            return 1;
        }
	if( !init() ){
            printf( "Echec de l'initialisation!\n" );
	}else{
            if( !loadMedia() ){
                printf( "Echec du chargement des images!\n" );
            }else{
                menu();
            }
	}
    }
    close();
    SDL_Quit();
    return (EXIT_SUCCESS);
}
