#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "constants.h"
#include "prototypes.h"


int main(int argc, char *argv[])
{
    SDL_Surface *firstScreen ;
    firstScreen = NULL ;

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) ;

    SDL_WM_SetCaption("ESGI Adventure", NULL) ;
    SDL_WM_SetIcon(IMG_Load("graphics/icon.bmp"), NULL) ; //NULL pour la transparence
    firstScreen = SDL_SetVideoMode(width_window_x,height_window_y,32,SDL_HWSURFACE) ;
    menu(firstScreen);


    return 0 ;
}
