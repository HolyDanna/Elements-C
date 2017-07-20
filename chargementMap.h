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
 * File:   chargementMap.h
 * Author: diz
 *
 * Created on 24 avril 2015, 12:09
 */

#ifndef CHARGEMENTMAP_H
#define	CHARGEMENTMAP_H

/*
 * Charge la map selon le nom de fichier
 */
int chargerFichierMap(int mapMapping[MAP_HAUTEUR][MAP_LARGEUR], char nomFichier[]);
/*
 * Charge la Map selon ses coordonnées
 */
int chargerMap(int ligne,int colonne);
/*
 * Détermine selon la direction et charge la Map suivante
 */
void changerMap(int direction);

#endif	/* CHARGEMENTMAP_H */

