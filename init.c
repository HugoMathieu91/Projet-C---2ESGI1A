#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <winsock.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "constants.h"
#include "prototypes.h"
#include <pthread.h>


const char *heroLeftSprites[3];
const char *heroUpSprites[3];
const char *heroRightSprites[3];
const char *heroDownSprites[3];
const char *fireSprites[4] ;


int bottleCount ;
char scorePlayer[5] ;

int lifeCount ;
char lives[2] ;

int currentDirection;
GridSquare board[144];

ImageToDisplay hero ;

int currentCharacterPosition;
int currentCharacterSprite;

int currentFireSprite;
int fireBallPosition;





 Mix_Music *music ;
 Mix_Chunk *sound ;
 SDL_Surface *screen ;

 SDL_Color color ;










