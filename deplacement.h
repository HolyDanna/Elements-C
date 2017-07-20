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
 * File:   deplacement.h
 * Author: diz
 *
 * Created on 24 avril 2015, 16:47
 */

#ifndef DEPLACEMENT_H
#define	DEPLACEMENT_H

void deplacerPerso();

/*
 * Vérifie si une case est une transition
 */
int estTransition();

/*
 * Change l'orientation du perso (lorsqu'il est au bord de la map)
 */
void changeOrientationPerso(int orientation);

/*
 * Vérifie si le personnage peut marcher sur la tuile
 */
int estAccessible(int tuile);

/*
 * Vérifie si la touche (appuyée) est une touche de déplacemnt
 */
SDL_Keycode estToucheDeDeplacement(SDL_Keycode touche);

int verifEstDevantCoupe();
int verifEstDevantCoupe_2(int ligne, int colonne);//Utilisee dans la premiere (ci dessus/ pour du factoring)

#endif	/* DEPLACEMENT_H */

