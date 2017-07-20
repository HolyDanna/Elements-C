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

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "variablesGlobales.h"
#include "affichage.h"
#include "chargementMap.h"

int nmb_red() {
    int i,j;
    int res=0;
    for(i=0;i<MAP_HAUTEUR;i++){
        for(j=0;j<MAP_LARGEUR;j++){
            if (mapMapping[i][j]== 33) {
                res++;
            }
        }
    }
    return res;
}

void script(){
    static int progression = 0;
    static Emplacement checkpoint_air[NB_NUAGE_CHECKPOINT_ROUGE];
    static int debut_parcours_air;
    int i,j;
    if(perso.elementAir == 0){
        if(map.ligne == 5 && map.colonne == 7 && (perso.ligne != 5 || perso.colonne != 7) && progression == 0){
            afficher_texte("Bienvenue à toi aventurier!\nTon périple sera court et facile parce que ça n'arrive pas assez souvent.\nVa voir au sud si j'y suis !\n\nA pour continuer");
            progression++;
        }
        if(map.ligne == 8 && map.colonne == 7 && perso.ligne > 3 && progression == 1){
            afficher_texte("Et il y était!\n\nVois-tu ce magnifique artéfact ?\n\nComme les boissons énergisantes, il donne des ailes!\n\nA pour continuer");
            afficher_texte("Si tu veux l'obtenir il te faudra être rapide!\n\nMarche sur toutes les dalles dans le délai imparti pour pouvoir l'obtenir!\n\nA pour continuer");
            afficher_texte("Appuie sur E quand tu seras devant l'artéfact pour le prendre !\n\n\n\n\n\nA pour continuer");
            progression++;
        }
        if(map.ligne == 8 && map.colonne == 7 && perso.ligne > 5 && progression == 2){
            afficher_texte("C'est parti !\n\n\n\n\n\n\n\n\nA pour continuer");
            debut_parcours_air = SDL_GetTicks();
            progression++;
        }
        if(progression > 2){
            for(i=0;i<NB_NUAGE_CHECKPOINT_ROUGE;i++){
                if(checkpoint_air[i].map_colonne != 0 && checkpoint_air[i].map_colonne == map.colonne && checkpoint_air[i].map_ligne == map.ligne){
                    mapMapping[checkpoint_air[i].ligne][checkpoint_air[i].colonne] = NUAGE_CHECKPOINT_VERT;
                }
            }
        }
        if(progression == 3){
            if(SDL_GetTicks() - debut_parcours_air > 60000){
                afficher_texte("Pas assez rapide !\n\nRetour à la case départ !\n\nEssaye encore ! \n\n\n\nA pour continuer");
                // On teleporte le personnage
                persoMapping[perso.ligne][perso.colonne] = VIDE;
                seDeplace=0;
                perso.colonne = 7;
                perso.ligne = 5;
                perso.positionPerso.x = perso.colonne * TUILE_LARGEUR;
                perso.positionPerso.y = perso.ligne * TUILE_HAUTEUR;
                map.colonne = 7;
                map.ligne = 8;
                persoMapping[perso.ligne][perso.colonne] = FRONT;
                chargerMap(map.ligne,map.colonne);
                // On reset les checkpoints
                for(i=0;i<NB_NUAGE_CHECKPOINT_ROUGE;i++){
                    checkpoint_air[i].colonne = 0;
                    checkpoint_air[i].ligne = 0;
                    checkpoint_air[i].map_colonne = 0;
                    checkpoint_air[i].map_ligne = 0;
                }
                progression--;
            }
            if(mapMapping[perso.ligne][perso.colonne] == NUAGE_CHECKPOINT_ROUGE){
                mapMapping[perso.ligne][perso.colonne] = NUAGE_CHECKPOINT_VERT;
                for(i=0;i<NB_NUAGE_CHECKPOINT_ROUGE;i++){
                    if(checkpoint_air[i].colonne == 0 && checkpoint_air[i].ligne == 0 && checkpoint_air[i].map_colonne == 0 && checkpoint_air[i].map_ligne == 0){
                        checkpoint_air[i].colonne = perso.colonne;
                        checkpoint_air[i].ligne = perso.ligne;
                        checkpoint_air[i].map_colonne = map.colonne;
                        checkpoint_air[i].map_ligne = map.ligne;
                        if(i==NB_NUAGE_CHECKPOINT_ROUGE-1){
                            afficher_texte("Félicitations, tu as été plus rapide qu'un gastéropode enrhumé, tu mérites vraiment cet artéfact\n\n\n\n\nA pour continuer");
                            progression++;
                            if(map.ligne == 8 && map.colonne == 8){
                                mapMapping[5][0] = NUAGE_TRANSIT;
                            }
                        }
                        break;
                    }
                }
            }
            if(map.ligne == 8 && map.colonne == 8 && progression < 4){
                mapMapping[5][0] = NUAGE;
            }
        }
    }else if(perso.elementTerre == 0){
        if(progression == 4){
            afficher_texte("Grace à cet artéfact, tu sais désormais comment courir, il faut maintenir la touche Maj !\n\nC'est magique !\n\n\nA pour continuer");
            afficher_texte("Tu dois maintenant aller chercher l'élément de la terre qui se trouve à l'ouest !\n\n\n\n\nA pour continuer");
            progression++;
        }
    }else if(perso.elementEau == 0){
        if (progression == 5){
            afficher_texte("Le son de la mer résonne dans ta tête. Tu sens au fond de toi que tu dois aller voir à l'est. Oui oui, tu le sens au fond de toi ! Discutes pas, vas-y !\n\nA pour continuer");
            eau=malloc(sizeof(int)*5);
            eau[0]=0;
            eau[1]=1;
            eau[2]=0;
            eau[3]=0;
            eau[4]=0;
            progression++;
        }
        if (map.ligne < 5 && map.colonne > 10){
            switch (eau[0]) {
                case 0:
                    if (perso.ligne == 5 && perso.colonne == 0 && map.colonne == 11 && map.ligne == 4 && avance) {
                        for(i=0;i<MAP_HAUTEUR;i++){
                            for(j=0;j<MAP_LARGEUR;j++){
                                if (mapMapping[i][j]== 34) {
                                    mapMapping[i][j]= 33;
                                }
                            }
                        }
                        eau[1]=nmb_red();
                        mapMapping[5][15]=9;
                        eau[2]=0;
                        eau[3]=map.ligne;
                        eau[4]=map.colonne;
                        avance=0;
                    }
                    break;
                    
                case 1:
                    if (perso.ligne == 5 && perso.colonne == 0 && map.colonne == 12 && map.ligne == 4 && avance) {
                        for(i=0;i<MAP_HAUTEUR;i++){
                            for(j=0;j<MAP_LARGEUR;j++){
                                if (mapMapping[i][j]== 34) {
                                    mapMapping[i][j]= 33;
                                }
                            }
                        }
                        eau[1]=nmb_red();
                        mapMapping[5][15]=9;
                        eau[2]=0;
                        eau[3]=map.ligne;
                        eau[4]=map.colonne;
                        avance=0;
                    }
                    break;
                    
                case 2:
                    if (perso.ligne == 5 && perso.colonne == 0 && map.colonne == 13 && map.ligne == 4 && avance) {
                        for(i=0;i<MAP_HAUTEUR;i++){
                            for(j=0;j<MAP_LARGEUR;j++){
                                if (mapMapping[i][j]== 34) {
                                    mapMapping[i][j]= 33;
                                }
                            }
                        }
                        eau[1]=nmb_red();
                        mapMapping[0][7]=9;
                        eau[2]=0;
                        eau[3]=map.ligne;
                        eau[4]=map.colonne;
                        avance=0;
                    }
                    break;
            }
            if (eau[2]!=eau[1]){
                if(mapMapping[perso.ligne][perso.colonne] == WATER_RED && avance && eau[4]==map.colonne && !(eau[3]-map.ligne)){
                    mapMapping[perso.ligne][perso.colonne] +=1;
                    eau[2]+=1;
                    avance=0;
                } else if(mapMapping[perso.ligne][perso.colonne] == WATER_GREEN && avance && eau[4]==map.colonne && eau[3]==map.ligne){
                    mapMapping[perso.ligne][perso.colonne] -=1;
                    eau[2]-=1;
                    avance=0;
                }
            }
            if (eau[2]==eau[1]){
                if (map.ligne==4 && map.colonne==11) {
                    mapMapping[5][15]=10;
                    eau[0]=1;
                }
                if (map.ligne==4 && map.colonne==12) {
                    mapMapping[5][15]=10;
                    eau[0]=2;
                }
                if (map.ligne==4 && map.colonne==13) {
                    mapMapping[0][7]=10;
                    eau[0]=3;
                }
            }
            if (eau[0] == 0 && progression ==6 && perso.ligne==5 && perso.colonne==1) {
                afficher_texte("Pour faire apparaitre le chemin vers la prochaine zone, il vous faut activer toutes les dalles de la zone. \n\n\n\nA pour continuer");
                afficher_texte("Un passage sur une dalle désactivée l'active, et un passage sur une dalle activée la désactive. \n\nBon courage. \n\n\nA pour continuer");
                afficher_texte("Attention : si vous repassez sur la dalle de départ, toutes les dalles se désactivent \n\n\n\n\n\nA pour continuer");
                progression ++;
            }
        }
        
    }else if(perso.elementFeu == 0){
        if (progression == 7){
            afficher_texte("Félicitations, vous avez obtenu l'élément de l'eau. Vous entendez un feu qui s'éteint, vers le Nord\n\n\n\nA pour continuer");
            progression ++;
            free(eau);
        }
        if(map.ligne == 1 && map.colonne == 6){
            if(progression == 8  && perso.ligne < 8){
                if(question("Qui marche sur quatre pattes le matin, sur 2 pattes à midi et sur trois pattes le soir ?","HOMME")==0){
                    afficher_texte("Vous avez répondu correctement ! \n\n\n\n\n\nAppuyez sur A");
                    progression++;
                }else{
                    afficher_texte("Vous vous êtes trompés, veuillez réessayer ! \n\n\n\n\n\nAppuyez sur A");
                }
            }else if(progression == 9  && perso.ligne < 6){
                if(question("Mieux que le paradis et pire que l'enfer, les richent ont besoin de moi, et les pauvres m'ont. Si tu me manges, tu meurs. Qui suis-je ?","RIEN")==0){
                    afficher_texte("Vous avez répondu correctement ! \n\n\n\n\n\nAppuyez sur A");
                    progression++;
                }else{
                    afficher_texte("Vous vous êtes trompés, veuillez réessayer ! \n\n\n\n\n\nAppuyez sur A");
                }
            }else if(progression == 10  && perso.ligne < 4){
                if(question("Sans voix, je hurle.\nSans ailes, je voltiges.\nSans dents, je mords.\nSans bouche, je murmure.\nQui suis-je ?","VENT")==0){
                    afficher_texte("Vous avez répondu correctement ! \n\n\n\n\n\nAppuyez sur A");
                    progression++;
                }else{
                    afficher_texte("Vous vous êtes trompés, veuillez réessayer ! \n\n\n\n\n\nAppuyez sur A");
                }
            }
        }
    }else{
        if (progression == 11){
            afficher_texte("Bravo, vous avez réuni les quatre éléments ! Allez chercher l'amour au centre de la map !\n\n\n\n\nAppuyez sur A");
            progression ++;
        }
        if(map.ligne == 5 && map.colonne == 7 && perso.ligne > 1 && progression > 11){
            afficher_texte("\n\n\n\n   Vous avez gagné !");
            afficher_texte("    Crédits\n\n Développeur :\n   Florian Calvo\n   Simon Basilien\n   Quentin Rouy\n\n Musique :\n   Rolemusic");
            quitter = 1;
        } 
    }
}
