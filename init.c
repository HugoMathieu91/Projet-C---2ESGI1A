#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


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

pthread_t fireballsThread ;





