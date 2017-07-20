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
 * File:   affichage.c
 * Author: diz
 *
 * Created on 24 avril 2015, 16:09
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variablesGlobales.h"
#include "affichage.h"

void afficher(){
    tile.w = TUILE_LARGEUR;
    tile.h = TUILE_HAUTEUR;
    tilePerso.w = TUILE_LARGEUR;
    tilePerso.h = TUILE_HAUTEUR;
    tileHeaders.w = 800;
    tileHeaders.h = 50;
    int trouve = 1;
    int coupeCpt = 0;
    int i,j;
    positionHeaders.x = 0;
    positionHeaders.y = 0;
    switch (mapMapping[0][0]){
        case HERBE : 
            tileHeaders.x = 0, tileHeaders.y = 0;
            break;
        case CIEL : 
            tileHeaders.x = 0, tileHeaders.y = 50;
            break;
        case ROCHER : 
            tileHeaders.x = 0, tileHeaders.y = 100;
            break;
        case EAU : 
            tileHeaders.x = 0, tileHeaders.y = 150;
            break;
        case FEU : 
            tileHeaders.x = 0, tileHeaders.y = 200;
            break;
        default:
            break;
    }
    SDL_BlitSurface( Headers, &tileHeaders, ecran, &positionHeaders );
    for(i=0;i<MAP_HAUTEUR;i++){
        for(j=0;j<MAP_LARGEUR;j++){
            position.x = j*TUILE_LARGEUR;
            position.y = i*TUILE_HAUTEUR +50;
            switch (mapMapping[i][j]){
                case HERBE :
                    tile.x = 0, tile.y = 0;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case HERBE_TRANSIT :
                    tile.x = 50, tile.y = 0;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case CIEL :
                    tile.x = 0, tile.y = 50;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case NUAGE :
                    tile.x = 50, tile.y = 50;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case NUAGE_TRANSIT :
                    tile.x = 100, tile.y = 50;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case TERRE :
                    tile.x = 0, tile.y = 100;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case ROCHER :
                    if(i==5 && j==1 && perso.elementAir==1 && mapMapping[5][0] == TERRE_TRANSIT && mapMapping[5][15] == HERBE_TRANSIT){
                        tile.x = 0, tile.y = 100;
                        mapMapping[5][1] = TERRE;
                    }
                    else tile.x = 50, tile.y = 100;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case TERRE_TRANSIT :
                    tile.x = 100, tile.y = 100;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case EAU :
                    if(i==5 && j==13 && perso.elementTerre==1 && mapMapping[5][0] == HERBE_TRANSIT && mapMapping[5][15] == EAU_PONT_TRANSIT){
                        tile.x = 50, tile.y = 150;
                        mapMapping[5][13] = EAU_PONT;
                    }
                    else if(i==5 && j==14 && perso.elementTerre==1 && mapMapping[5][0] == HERBE_TRANSIT && mapMapping[5][15] == EAU_PONT_TRANSIT){
                        tile.x = 50, tile.y = 150;
                        mapMapping[5][14] = EAU_PONT;
                    }
                    else tile.x = 0, tile.y = 150;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case EAU_PONT :
                    tile.x = 50, tile.y = 150;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case EAU_PONT_TRANSIT :
                    tile.x = 100, tile.y = 150;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case FEU :
                    tile.x = 0, tile.y = 200;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case FEU_TRANSIT :
                    tile.x = 50, tile.y = 200;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case FLAMME :
                    if(i==1 && j==7 && perso.elementEau==1 && mapMapping[0][7] == FEU_TRANSIT && mapMapping[11][7] == HERBE_TRANSIT){
                        tile.x = 0, tile.y = 200;
                        mapMapping[1][7] = FEU;
                    }
                    else tile.x = 150, tile.y = 200;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case ARBRE :
                    tile.x = 100, tile.y = 0;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case ARBRE_MORT :
                    tile.x = 100, tile.y = 200;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case MUR_TERRE :
                    tile.x = 150, tile.y = 100;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case NUAGE_CHECKPOINT_ROUGE :
                    tile.x = 150, tile.y = 50;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case NUAGE_CHECKPOINT_VERT :
                    tile.x = 200, tile.y = 50;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case WATER_RED :
                    tile.x = 150, tile.y = 150;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case WATER_GREEN :
                    tile.x = 200, tile.y = 150;
                    SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                    break;
                case COUPE :
                case COUPE_AIR :
                case COUPE_TERRE :
                case COUPE_EAU :
                case COUPE_FEU :
                    switch (mapMapping[0][0]){
                        case HERBE : 
                            tile.x = 0, tile.y = 0;
                            SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                            if(perso.elementAir == 1 && coupeCpt == 0){
                                tile.x = 0, tile.y = 0;
                                coupeCpt++;
                            }
                            else if(perso.elementTerre == 1 && coupeCpt == 1){
                                tile.x = 50, tile.y = 0;
                                coupeCpt++;
                            }
                            else if(perso.elementEau == 1 && coupeCpt == 2){
                                tile.x = 100, tile.y = 0;
                                coupeCpt++;
                            }
                            else if(perso.elementFeu == 1 && coupeCpt == 3){
                                tile.x = 150, tile.y = 0;
                                coupeCpt++;
                            }
                            else
                                tile.x = 200, tile.y = 0;
                            break;
                        case CIEL : 
                            tile.x = 50, tile.y = 50;
                            SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                            if(perso.elementAir == 0)
                                tile.x = 0, tile.y = 0;
                            else
                                tile.x = 200, tile.y = 0;
                            break;
                        case ROCHER : 
                            tile.x = 0, tile.y = 100;
                            SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                            if(perso.elementTerre == 0)
                                tile.x = 50, tile.y = 0;
                            else
                                tile.x = 200, tile.y = 0;
                            break;
                        case EAU : 
                            tile.x = 50, tile.y = 150;
                            SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                            if(perso.elementEau == 0)
                                tile.x = 100, tile.y = 0;
                            else
                                tile.x = 200, tile.y = 0;
                            break;
                        case FEU : 
                            tile.x = 0, tile.y = 200;
                            SDL_BlitSurface( MapTileSet, &tile, ecran, &position );
                            if(perso.elementFeu == 0)
                                tile.x = 150, tile.y = 0;
                            else
                                tile.x = 200, tile.y = 0;
                            break;
                        default:
                            break;
                    }
                    SDL_BlitSurface( ObjetsTileSet, &tile, ecran, &position );
                    break;
                default:
                    break;
            }
        }
    }
    switch (persoMapping[perso.ligne][perso.colonne]){
        case FRONT:
            tilePerso.x = 0, tilePerso.y = 0;
            break;
        case FRONT_MOVE_1:
            tilePerso.x = 50, tilePerso.y = 0;
            break;
        case FRONT_MOVE_2:
            tilePerso.x = 100, tilePerso.y = 0;
            break;
        case SIDE_1:
            tilePerso.x = 0, tilePerso.y = 50;
            break;
        case SIDE_1_MOVE_1:
            tilePerso.x = 50, tilePerso.y = 50;
            break;
        case SIDE_1_MOVE_2:
            tilePerso.x = 100, tilePerso.y = 50;
            break;
        case BACK:
            tilePerso.x = 0, tilePerso.y = 100;
            break;
        case BACK_MOVE_1:
            tilePerso.x = 50, tilePerso.y = 100;
            break;
        case BACK_MOVE_2:
            tilePerso.x = 100, tilePerso.y = 100;
            break;
        case SIDE_2:
            tilePerso.x = 0, tilePerso.y = 150;
            break;
        case SIDE_2_MOVE_1:
            tilePerso.x = 50, tilePerso.y = 150;
            break;
        case SIDE_2_MOVE_2:
            tilePerso.x = 100, tilePerso.y = 150;
            break;
        default:
            trouve=0;
            break;                            
    }
    if(trouve){
        SDL_BlitSurface( PersoTileSet, &tilePerso, ecran, &perso.positionPerso );
    }
    SDL_UpdateWindowSurface( fenetre );
}

void afficher_texte(char *Texte_A_Afficher){
    static int modeTexte=0;
    SDL_Event e;
    int ecart = 8;
    TextMenu.x=200;
    TextMenu.y=200;
    SDL_BlitSurface( Cadre_texte, NULL, ecran, &TextMenu );
    couleur.r=0;
    couleur.g=0;
    couleur.b=0;
    couleur.a=0;
    TextContent.x=TextMenu.x+ecart;
    TextContent.y=TextMenu.y+ecart;
    Texte = TTF_RenderUTF8_Blended_Wrapped(Police, Texte_A_Afficher, couleur,400-2*ecart);
    SDL_BlitSurface( Texte, NULL, ecran, &TextContent);
    SDL_UpdateWindowSurface( fenetre );
    modeTexte=1-modeTexte;
    while( !quitter && modeTexte){
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT ){
                quitter = 1;
                break;
            }
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == FERMER_FENETRE){
                    modeTexte=1-modeTexte;
                }
            }
        }
    }
}

int question(char* question, char* reponse){
    int saisie_en_cours=1;
    int resultat = 1;
    SDL_Event e;
    
    int ecart = 8;
    TextMenu.x=200;
    TextMenu.y=200;
    couleur.r=0;
    couleur.g=0;
    couleur.b=0;
    couleur.a=0;
    TextContent.x=TextMenu.x+ecart;
    TextContent.y=TextMenu.y+ecart;
    
    char *texte_complet = (char*)malloc(sizeof(char));
    char *saisie = (char*)malloc(sizeof(char));
    strcpy(saisie,"");
    while (!quitter && saisie_en_cours){
        strcpy(texte_complet,"");
        texte_complet = (char*)realloc(texte_complet,(strlen(question)+strlen("\n\n")+strlen(saisie)+1)*sizeof(char));
        strcat(strcat(strcat(texte_complet,question),"\n\n"),saisie);
        SDL_BlitSurface( Cadre_texte, NULL, ecran, &TextMenu );
        Texte = TTF_RenderUTF8_Blended_Wrapped(Police, texte_complet, couleur,400-2*ecart);
        SDL_BlitSurface( Texte, NULL, ecran, &TextContent);
        SDL_UpdateWindowSurface( fenetre );
        while( SDL_PollEvent( &e )){
            if( e.type == SDL_QUIT ){
                quitter = 1;
                break;
            }else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_RETURN2 || e.key.keysym.sym == SDLK_KP_ENTER){
                    saisie_en_cours = 0;
                }else if(e.key.keysym.sym == SDLK_BACKSPACE){
                    if(strlen(saisie) != 0){
                        saisie[strlen(saisie)-1]='\0';
                        saisie = (char*)realloc(saisie,(strlen(saisie)+1)*sizeof(char));
                    }
                }else{
                    if(strlen(SDL_GetKeyName(e.key.keysym.sym))+strlen(saisie)<=TAILLE_MAX_INPUT){
                        saisie = (char*)realloc(saisie,(strlen(SDL_GetKeyName(e.key.keysym.sym))+strlen(saisie)+1)*sizeof(char));
                        strcat(saisie,SDL_GetKeyName(e.key.keysym.sym));
                    }
                }
            }
        }
    }
    if(saisie_en_cours == 0 && strcmp(reponse,saisie) == 0){
        resultat=0;
    }
    free(saisie);
    free(texte_complet);
    return resultat;
}