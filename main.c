#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
//#include "functions.c"
#include "constants.h"
#include "prototypes.h"

int main(int argc, char *argv[])
{


    SDL_Surface *screen ;
    screen = NULL ;

    SDL_Init(SDL_INIT_VIDEO) ;

    SDL_WM_SetCaption("ESGI Adventure", NULL) ;
    SDL_WM_SetIcon(IMG_Load("graphics/icon.bmp"), NULL) ; //NULL pour la transparence
    screen = SDL_SetVideoMode(width_window_x,height_window_y,32,SDL_HWSURFACE) ;
    /*SDL_Delay(3000) ;
    return EXIT_SUCCESS ;*/

    menu(screen);


    return 0 ;
}
