#include "structures.h"

void pause() ;
int menu(SDL_Surface *screen) ;
int settings(SDL_Surface *screen) ;
int enterYourName() ;
int introduction() ;//Prenait screen avant
void getLevels(int levelChoice);
void placeCharacter(int choice, int x, int y);
void introDialog(int dialNumb) ;
void generateGrid();
//int startGame(SDL_Surface *screen);
void setFireLine() ;
void setSprite(int position, const char *sprite, ElementType elementType) ;

void initControls();
void getAudio(int choice);

void sananesAttacks();

//void movement(SDL_Surface *screen, int heroDirection, Character hero);
