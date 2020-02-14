#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "constants.h"
#include "prototypes.h"


//Toutes nos variables globales et les headers dont les fonctions ont besoin sont ici

//Les sprites du hero
const char *heroLeftSprites[3];
const char *heroUpSprites[3];
const char *heroRightSprites[3];
const char *heroDownSprites[3];

//Les sprites du feu
const char *fireSprites[4] ;

//Compteur de bouteilles
int bottleCount ;
char scorePlayer[5] ;

//Compteur de vie
int lifeCount ;
char lives[2] ;

//Orientation du personnage
int currentDirection;


//Position du hero dans le jeu
int currentCharacterPosition;
//Sprite affiché
int currentCharacterSprite;

//Structure représentant notre espace de jeu
GridSquare board[144];

//Tentative de structure au début du projet... a revoir
ImageToDisplay hero ;

//La musique jouée
 Mix_Music *music ;

 //L'écran de jeu
 SDL_Surface *screen ;

 //Couleur du texte
 SDL_Color color ;










