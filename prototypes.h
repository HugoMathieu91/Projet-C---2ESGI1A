#include "structures.h"

void pause() ;
int menu(SDL_Surface *screen) ;
int settings(SDL_Surface *screen) ;
int enterYourName() ;
int introduction() ;
void getLevels(SDL_Surface *screen, int levelChoice);
void placeCharacter(SDL_Surface *screen, int choice, int x, int y);
void introDialog(SDL_Surface *screen, int dialNumb) ;
void laught(SDL_Surface *screen, int character, int x, int y );
//void startAdventure(SDL_Surface *screen, int level) ;
void generateGrid(SDL_Surface *screen);
int startGame(SDL_Surface *screen);
void setFireLine(SDL_Surface *screen) ;
void setSprite(SDL_Surface *screen, int position, const char *sprite, ElementType elementType) ;

void initControls(SDL_Surface *screen);
void getAudio(int choice);


//void movement(SDL_Surface *screen, int heroDirection, Character hero);
