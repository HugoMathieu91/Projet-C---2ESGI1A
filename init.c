#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>


const char *heroLeftSprites[3];
const char *heroUpSprites[3];
const char *heroRightSprites[3];
const char *heroDownSprites[3];
const char *fireSprites[4] ;

int currentDirection;

int currentCharacterPosition;
int currentCharacterSprite;

int currentFireSprite;
int currentFireBallPosition;


int bottleCount ;
//SDL_Surface *screen ;

 Mix_Music *music ;
 SDL_Surface *screen ;









