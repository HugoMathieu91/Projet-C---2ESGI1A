#include "structures.h"

void connectDB() ;

void deathAnimation() ;

void endGame() ;
int enterYourName() ;

void gamebreak1() ;
void gameOver() ;
void generateGrid();
void generateLife() ;
void getAudio(int choice);
void getLevels(int levelChoice);
void getLife() ;
void getScore() ;
int getRandomValue(int lower, int upper) ;

void initAudio() ;
void initTTF() ;
void introDialog(int dialNumb) ;
int introduction() ;

int menu(SDL_Surface *screen) ;
void moveCharacter(int direction) ;

void pause() ;
void placeCharacter(int choice, int x, int y);
void play() ;

void sananesDestruction() ;
void setFireLine() ;
void setFireSprites() ;
void setHeroSprites() ;
void setNextSprite(int direction) ;
void setSprite(int position, const char *sprite, ElementType elementType) ;
int settings(SDL_Surface *screen) ;
void successScreen() ;


















//void movement(SDL_Surface *screen, int heroDirection, Character hero);
