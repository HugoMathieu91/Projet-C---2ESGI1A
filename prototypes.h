#include "structures.h"

int enterYourName() ;
void generateGrid();
void getAudio(int choice);
void getLevels(int levelChoice);
int getRandomValue(int lower, int upper) ;
void initAudio() ;
void initTTF() ;
void introDialog(int dialNumb) ;
int introduction() ;
int menu(SDL_Surface *screen) ;
void pause() ;
void placeCharacter(int choice, int x, int y);
void play() ;
void setFireLine() ;
void setSprite(int position, const char *sprite, ElementType elementType) ;
int settings(SDL_Surface *screen) ;
void successScreen() ;


















//void movement(SDL_Surface *screen, int heroDirection, Character hero);
