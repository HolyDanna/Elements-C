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
 * File:   variablesGlobales.h
 * Author: diz
 *
 * Created on 23 avril 2015, 22:51
 */

#ifndef VARIABLESGLOBALES_H
#define	VARIABLESGLOBALES_H

#define TUILE_HAUTEUR 50
#define TUILE_LARGEUR 50
#define MAP_HAUTEUR 12
#define MAP_LARGEUR 16

// Mappage des touches
#define HAUT SDLK_z
#define GAUCHE SDLK_q
#define BAS SDLK_s
#define DROITE SDLK_d
#define SPEED SDLK_LSHIFT
#define DEV_MODE SDLK_KP_MULTIPLY
#define PRENDRE SDLK_e
#define FERMER_FENETRE SDLK_a
#define TAILLE_POLICE 30

// Vitesses du personnage
#define SPEED_DEV 5
#define SPEED_RUN 15
#define SPEED_WALK 40
#define WATER_RED 33
#define WATER_GREEN 34

// Phase air
#define NB_NUAGE_CHECKPOINT_ROUGE 21
//Phase eau
int avance;
int *eau;
//Phase feu
#define TAILLE_MAX_INPUT 21

SDL_Window* fenetre;
SDL_Surface* ecran;
SDL_Surface* Menu;
SDL_Surface* FlecheMenuG;
SDL_Surface* FlecheMenuD;
SDL_Surface* PersoTileSet;
SDL_Surface* MapTileSet;
SDL_Surface* ObjetsTileSet;
SDL_Surface* Headers;
SDL_Surface* Cadre_texte;
SDL_Surface* Texte;
TTF_Font* Police;
SDL_Color couleur;

int audio_rate;
Uint16 audio_format;
int audio_channels;
int audio_buffers;
//http://content.gpwiki.org/index.php/C:Playing_a_WAV_Sound_File_With_SDL_mixer pour plus d'infos sur les formats possibles/intégration de son
Mix_Chunk *bg_music;
int channel;

typedef struct {
    SDL_Rect positionPerso;
    int ligne;
    int colonne;
    int elementAir;
    int elementTerre;
    int elementEau;
    int elementFeu;
}Perso;
Perso perso;

typedef struct{
    int ligne;
    int colonne;
}Map;
Map map;

typedef struct{
    int map_ligne;
    int map_colonne;
    int ligne;
    int colonne;
}Emplacement;

int quitter;
int seDeplace;
SDL_Keycode direction;

int tempsActuel;
int tempsSave;

//Enum pour le TileSet du personnage
enum {VIDE, 
FRONT, FRONT_MOVE_1, FRONT_MOVE_2, 
SIDE_1, SIDE_1_MOVE_1, SIDE_1_MOVE_2, 
BACK, BACK_MOVE_1, BACK_MOVE_2,
SIDE_2, SIDE_2_MOVE_1, SIDE_2_MOVE_2};

//Enum pour le TileSet de la map
enum {HERBE, HERBE_TRANSIT, 
CIEL, NUAGE, NUAGE_TRANSIT,
TERRE, ROCHER, TERRE_TRANSIT,
EAU, EAU_PONT, EAU_PONT_TRANSIT,
FEU, FEU_TRANSIT,
COUPE, ARBRE, ARBRE_MORT, MUR_TERRE,
NUAGE_CHECKPOINT_ROUGE, NUAGE_CHECKPOINT_VERT,
COUPE_AIR, COUPE_TERRE, COUPE_EAU, COUPE_FEU,
FLAMME};

//Tableau 2D pour le personnage et la map
int persoMapping[MAP_HAUTEUR][MAP_LARGEUR];
int mapMapping[MAP_HAUTEUR][MAP_LARGEUR];

//Position + position du personnage
SDL_Rect position, positionHeaders;
SDL_Rect tile, tilePerso, tileHeaders, TextMenu, TextContent;

#endif	/* VARIABLESGLOBALES_H */

