#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <winsock.h>
#include "prototypes.h"
#include "constants.h"
#include "init.c"


GridSquare board[144];
int bottleCount ;
ImageToDisplay hero ;



void setFire()
{
    fireSprites[0] =  "graphics/Fire1.png" ;
    fireSprites[1] =  "graphics/Fire2.png" ;
    fireSprites[2] =  "graphics/Fire3.png" ;
    fireSprites[3] =  "graphics/Fire4.png" ;
}


void setHeroSprites()
{
    heroLeftSprites[0] = "graphics/GuyLeft1.png";
    heroLeftSprites[1] = "graphics/GuyLeft2.png";
    heroLeftSprites[2] = "graphics/GuyLeft3.png";

    heroUpSprites[0] = "graphics/GuyTop1.png";
    heroUpSprites[1] = "graphics/GuyTop2.png";
    heroUpSprites[2] = "graphics/GuyTop3.png";

    heroRightSprites[0] = "graphics/GuyRight1.png";
    heroRightSprites[1] = "graphics/GuyRight2.png";
    heroRightSprites[2] = "graphics/GuyRight3.png";

    heroDownSprites[0] = "graphics/GuyBot1.png";
    heroDownSprites[1] = "graphics/GuyBot2.png";
    heroDownSprites[2] = "graphics/GuyBot3.png";
}

void setFireLine(SDL_Surface *screen)
{
    int i ;
    setFire() ;
    for(i=36 ; i<=47 ; i++)
    {
        setSprite(screen,i, fireSprites[0], FIRE) ;
    }
}

//Set a sprite on the game grid, arguments: current screen, position, elementType (see constants.h for enumeration)
void setSprite(SDL_Surface *screen, int position, const char *sprite, ElementType elementType)
{
    //grid is 144 squares
    if(position > 144)
    {
        return;
    }

    for(int i=0; i < 144; i++)
    {
        if(i == position)
        {
            board[i].image = IMG_Load(sprite);
            board[i].elementType = elementType;
            SDL_BlitSurface(board[i].image, NULL,screen,&board[i].position);
            SDL_Flip(screen);
            SDL_FreeSurface(board[i].image) ;
            break;
        }
    }
}

//To know what's the next sprite to load
void setNextSprite(int direction)
{
    //==2 because we have 3 sprite in array (0,1,2)
    if(currentDirection != direction
            || currentCharacterSprite == 2)
    {
        currentCharacterSprite = 0;
    }
    else
    {
        currentCharacterSprite++;
    }
}

int getRandomValue(int lower, int upper)
{
    srand(time(0));
    // int i;

    while (1)
    {
        //random entre 0 (min position) et 143 (max position)
        int num = (rand() % (upper - lower + 1)) + lower;
        if(board[num].elementType == TABLE
                || board[num].elementType == HERO
                || board[num].elementType == BOSS
                || board[num].elementType == BOTTLE)
        {
            continue;
        }
        return num;
    }
}

//Generate game grid
void generateGrid(SDL_Surface *screen)
{
    int initialX = 0;
    int incrementalX = initialX;
    int incrementalY = 0;
    int height = 50;
    int width = 50;
    for(int i=0; i < 144; i++)
    {
        board[i].image = IMG_Load("graphics/testGrid.png");
        board[i].position.h = height;
        board[i].position.w = width;
        board[i].position.x = incrementalX;
        board[i].position.y = incrementalY;
        ElementType type = NONE;
        board[i].elementType = type;

        if(incrementalX < 11*width + initialX)
        {
            incrementalX+=width;
        }
        else
        {
            incrementalX = initialX;
            incrementalY += height;
        }
        SDL_BlitSurface(board[i].image, NULL, screen, &board[i].position) ;
        SDL_Flip(screen);
        SDL_FreeSurface(board[i].image) ;
    }
}
void play(SDL_Surface *screen)
{
    generateGrid(screen);

    currentCharacterSprite = 0;
    currentCharacterPosition = 71;
    currentCharacterSprite = 0;

    setHeroSprites();

    getLevels(screen, 1) ;
    setFireLine(screen) ;

}

void moveCharacter(SDL_Surface *screen, int direction)
{
    //TODO: replace cases by enum.
    int desiredLeftPosition = 0;
    int desiredRightPosition = 0;
    int desiredUpPosition = 0;
    int desiredDownPosition = 0;


    char scorePlayer[10] ;

    SDL_Surface *score = NULL ;
    TTF_Font *police = NULL;

    police = TTF_OpenFont("fonts/sixty.ttf", 20);

    SDL_Rect scorePosition ;
    scorePosition.x = 25 ;
    scorePosition.y = 25 ;

    SDL_Color color ;
    color.r = 255;
    color.g = 0 ;
    color.b = 0 ;

    setSprite(screen, 0,"graphics/testGrid.png", NONE);
    switch(direction)
    {

    //left
    case 0:

        if((int)currentCharacterPosition - 1 < 0
                || (int)currentCharacterPosition % 12 == 0)
        {
            return;
        }

        desiredLeftPosition = currentCharacterPosition -1;
        if(board[desiredLeftPosition].elementType == TABLE)
        {
            setSprite(screen, currentCharacterPosition, heroLeftSprites[0], HERO);
            return;
        }

        if(board[desiredLeftPosition].elementType == FIRE)
        {
            setSprite(screen, currentCharacterPosition, heroLeftSprites[0], HERO);
            return;
        }

        if(board[desiredLeftPosition].elementType == BOTTLE)
        {
            //TODO Create method (function for noob) to setBottlePosition.
            int value = getRandomValue(48,143);
            setSprite(screen, value, "graphics/bottle.png", BOTTLE);
            bottleCount++ ;
        }

        setSprite(screen, currentCharacterPosition, "graphics/testGrid.png", NONE);

        currentCharacterPosition = desiredLeftPosition;
        setNextSprite(direction);
        setSprite(screen, desiredLeftPosition, heroLeftSprites[currentCharacterSprite], HERO);
        break;
    case 1:
        desiredUpPosition = currentCharacterPosition - 12;
        if(desiredUpPosition < 0)
        {
            return;
        }

        if(board[desiredUpPosition].elementType == TABLE)
        {
            setSprite(screen, currentCharacterPosition, heroUpSprites[0], HERO);
            return;
        }


        if(board[desiredUpPosition].elementType == FIRE)
        {
            setSprite(screen, currentCharacterPosition, heroUpSprites[0], HERO);
            return;
        }

        if(board[desiredUpPosition].elementType == BOTTLE)
        {
            int value = getRandomValue(48,143);
            setSprite(screen, value, "graphics/bottle.png", BOTTLE);
            bottleCount++ ;



        }

        setSprite(screen, currentCharacterPosition,"graphics/testGrid.png", NONE);

        currentCharacterPosition = desiredUpPosition;
        setNextSprite(direction);
        setSprite(screen, currentCharacterPosition, heroUpSprites[currentCharacterSprite], HERO);
        break;
    case 2:
        if(((int)currentCharacterPosition + 1) % 12 == 0)
        {
            return;
        }

        desiredRightPosition = currentCharacterPosition +1;
        if(board[desiredRightPosition].elementType == TABLE)
        {
            setSprite(screen, currentCharacterPosition, heroRightSprites[0], HERO);
            return;
        }

        if(board[desiredRightPosition].elementType == FIRE)
        {
            setSprite(screen, currentCharacterPosition, heroRightSprites[0], HERO);
            return;
        }


        if(board[desiredRightPosition].elementType == BOTTLE)
        {
            int value = getRandomValue(48,143);
            setSprite(screen, value, "graphics/bottle.png", BOTTLE);
             bottleCount++ ;

            //Technique pour ttf un int

        }

        setSprite(screen, currentCharacterPosition,"graphics/testGrid.png", NONE);
        currentCharacterPosition= (int)desiredRightPosition;
        setNextSprite(direction);
        setSprite(screen, desiredRightPosition, heroRightSprites[currentCharacterSprite], HERO);
        break;
    case 3:
        desiredDownPosition = currentCharacterPosition + 12;
        if(desiredDownPosition > 143)
        {
            return;
        }

        if(board[desiredDownPosition].elementType == TABLE)
        {
            setSprite(screen, currentCharacterPosition, heroDownSprites[0], HERO);
            return;
        }

        if(board[desiredDownPosition].elementType == FIRE)
        {
            setSprite(screen, currentCharacterPosition, heroDownSprites[0], HERO);
            return;
        }

        if(board[desiredDownPosition].elementType == BOTTLE)
        {
            int value = getRandomValue(48,143);
            setSprite(screen, value, "graphics/bottle.png", BOTTLE);
            bottleCount++ ;

            //Technique pour ttf un int

        }
        setSprite(screen, currentCharacterPosition,"graphics/testGrid.png", NONE);
        currentCharacterPosition = desiredDownPosition;
        setNextSprite(direction);
        setSprite(screen, currentCharacterPosition, heroDownSprites[currentCharacterSprite], HERO);
        break;
    }
    currentDirection = direction;
    sprintf(scorePlayer, "%d", bottleCount) ;
            score = TTF_RenderText_Blended(police, scorePlayer, color);

             SDL_BlitSurface(score, NULL, screen, &scorePosition) ;
            SDL_Flip(screen);
            SDL_FreeSurface(score) ;
}

int menu(SDL_Surface *screen)
{
    SDL_Surface *imageMenu = NULL;
    SDL_Surface *champagneSelect = NULL ;

    SDL_Rect imageMenuPosition;
    SDL_Rect champagneSelectPosition;

    SDL_Event event ;

    int run = 1 ;
    int xPosition = 100;
    int menuYPosition[] = {100, 280,460};
    int currentPosition = 0;

    //TODO: Create a method to set SDLRect
    imageMenuPosition.x = 0;
    imageMenuPosition.y = 0;

    champagneSelectPosition.x = xPosition;
    champagneSelectPosition.y = xPosition;

    //Position du select par rapport aux boutons
    //Play y = 100 x = 100
    //Settings y = 260
    //Quit y = 420charPictures
    imageMenu = IMG_Load("graphics/startmenu.bmp") ; //Alloue taille en mémoire pour la surface qu'on charge
    if ( imageMenu == NULL )
    {
        fprintf( stderr,"Problem with image loading: %s\n", SDL_GetError());
        //Note: Is this method usefull ?!
        //pause() ;
        exit(EXIT_FAILURE);
    }

    SDL_BlitSurface(imageMenu,NULL,screen,&imageMenuPosition) ;

    champagneSelect = IMG_Load("graphics/champagne.png") ;
    if ( champagneSelect == NULL )
    {
        fprintf( stderr,"Problem with image loading: %s\n", SDL_GetError());
        //Note: Is this method usefull ?!
        //pause() ;
        exit(EXIT_FAILURE);
    }
    SDL_BlitSurface(champagneSelect,NULL,screen,&champagneSelectPosition) ;

    while(run)
    {
        SDL_WaitEvent(&event) ;
        //It's possible that a better solution exist...
        switch(event.type)
        {
        case SDL_QUIT:
            exit(EXIT_SUCCESS) ;
            break ;

        case SDL_KEYDOWN://When we push a key
            switch(event.key.keysym.sym)//describe a key
            {
            case SDLK_RETURN: //"Enter" key
                SDL_FreeSurface(champagneSelect) ;
                SDL_FreeSurface(imageMenu);
                switch(currentPosition)
                {
                case 0:
                    introduction(screen);
                    pause() ;
                    break;
                case 1:
                    settings(screen);
                    break;
                default:
                    break;
                }
                break;
            case SDLK_DOWN://Down key

                if(champagneSelectPosition.y == menuYPosition[2])
                {
                    currentPosition = 0;
                }
                else
                {
                    currentPosition += 1;
                }

                champagneSelectPosition.y = menuYPosition[currentPosition];
                break;

            case SDLK_UP://Up key
                if(champagneSelectPosition.y == menuYPosition[0])
                {
                    currentPosition = 2;
                }
                else
                {
                    currentPosition -= 1;
                }
                champagneSelectPosition.y = menuYPosition[currentPosition];
                break;
            default:
                break;
            }

        default:
            break ;
        }

        SDL_BlitSurface(imageMenu,NULL,screen,&imageMenuPosition) ;
        SDL_BlitSurface(champagneSelect,NULL,screen,&champagneSelectPosition) ;
        SDL_Flip(screen) ;

    }
    SDL_Flip(screen) ;
    SDL_FreeSurface(imageMenu) ;
    SDL_FreeSurface(champagneSelect) ;
    SDL_Quit() ;
    return EXIT_SUCCESS ;
}

void pause()
{
    int pause = 1 ;
    SDL_Event event ;

    while(pause)
    {
        SDL_WaitEvent(&event) ;
        switch(event.type)
        {
        case SDL_QUIT:
            pause = 0;
        }
    }
}

int settings(SDL_Surface* screen)
{
    SDL_Surface *settings = NULL ;
    SDL_Event event ;
    SDL_Rect settingsPosition ;

    settingsPosition.x = 0 ;
    settingsPosition.y = 0 ;

    int run = 1 ;

    SDL_WM_SetCaption("ESGI Adventure - Settings", NULL) ; //Nouvelle fenetre
    screen = SDL_SetVideoMode(600,600,32,SDL_HWSURFACE) ;
    settings = IMG_Load("graphics/settings.png") ;
    SDL_BlitSurface(settings,NULL,screen, &settingsPosition) ;
    SDL_Flip(screen) ; //maj de l'écran

    while(run)
    {
        SDL_WaitEvent(&event) ;
        switch(event.type)
        {
        case SDL_QUIT:
            exit(EXIT_SUCCESS) ;
            break ;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            {
                run = 0 ;
                SDL_FreeSurface(settings) ;
                menu(screen) ;
                break ;
            }
            default:
                break ;
            }
        default:
            break ;

        }
    }
    //pause();
    SDL_FreeSurface(settings) ;
    return EXIT_SUCCESS ;
}

int introduction(SDL_Surface *screen)
{
    int repeat = 1 ;
    int dialNumber =  1 ;

    SDL_Event event;
    SDL_WM_SetCaption("ESGI Adventure", NULL) ; //Nouvelle fenetre
    screen = SDL_SetVideoMode(600,600,32,SDL_HWSURFACE) ;
    introDialog(screen, 0) ;
    int run = 1 ;

    while(run)
    {
        SDL_WaitEvent(&event) ;

        switch(event.type)
        {
        case SDL_QUIT:
            exit(EXIT_SUCCESS) ;
            break ;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                run = 0 ;
                menu(screen) ;
                break ;

            case SDLK_RETURN:
                //getLevels(screen,0) ;

                while(repeat)
                {
                    SDL_WaitEvent(&event) ;

                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
                    {
                        if(dialNumber<3)
                        {
                            getLevels(screen,0) ;
                            placeCharacter(screen, 1,550,250) ;
                            placeCharacter(screen, 0,175,50 ) ;
                            introDialog(screen, dialNumber) ;
                            dialNumber++ ;
                        }

                        else if(dialNumber == 3)
                        {
                            getLevels(screen,0) ;
                            placeCharacter(screen,2, 175,50 );
                            placeCharacter(screen, 1,550,250) ;
                            introDialog(screen, dialNumber) ;
                            dialNumber++ ;
                        }

                        else
                        {
                            play(screen) ;
                            initControls(screen) ;
                        }
                    }
                }
                break;

            default:
                break ;
            }
        default:
            break ;
        }
    }
    return EXIT_SUCCESS ;
}

void initControls(SDL_Surface *screen)
{
    int wait = 1 ;
    SDL_Event control;

    while(wait)
    {
        SDL_WaitEvent(&control) ;
        switch(control.type)
        {
        case SDL_QUIT:
            wait = 0 ;
            return EXIT_SUCCESS ;
            break ;
        case SDL_KEYDOWN:
            switch(control.key.keysym.sym)
            {
            case SDLK_LEFT:
                moveCharacter(screen, 0);
                break ;
            case SDLK_UP:
                moveCharacter(screen, 1);
                break ;
            case SDLK_RIGHT:
                moveCharacter(screen, 2);
                break ;
            case SDLK_DOWN:
                moveCharacter(screen, 3);
                break ;
            default:
                break;
            }
            break ;

        default:
            break;
        }
    }

}

//Appelle les dialogues durant l'introduction du jeu
void introDialog(SDL_Surface *screen, int dialNumb)
{
    TTF_Init() ;
    if ( TTF_Init() == -1 )
    {
        fprintf( stderr,"Problem with ttf loading: %s\n", SDL_GetError());
        //Note: Is this method usefull ?!
        //pause() ;
        exit(EXIT_FAILURE);
    }
    TTF_Font *police = NULL;
    police = TTF_OpenFont("fonts/sixty.ttf", 20);
    SDL_Surface *dial = NULL ;

    SDL_Rect dialPosition ;

    SDL_Color color ;
    color.r = 255;
    color.g = 0 ;
    color.b = 0 ;




    switch(dialNumb)
    {
    case 0:
        dial = TTF_RenderText_Blended(police, "Tout commence en cours de C avec Monsieur Sananes", color);
        dialPosition.x = 25 ;
        dialPosition.y = 25 ;
        break ;

    case 1:
        dial = TTF_RenderText_Blended(police, "Bonjour Anthony tu arrives pile poil pour l'interro surprise",color);
        dialPosition.x = 25 ;
        dialPosition.y = 25 ;
        break ;

    case 2:
        dial = TTF_RenderText_Blended(police, "Mer** **tain** !!! ", color) ;
        dialPosition.x = 400 ;
        dialPosition.y = 200 ;
        break ;

    case 3:
        dial = TTF_RenderText_Blended(police, "COMMENT ? Allez me chercher du champagne TOUT DE SUITE !!", color);
        dialPosition.x = 25 ;
        dialPosition.y = 25 ;
        break ;

    default:
        break ;
    }
    SDL_BlitSurface(dial, NULL, screen, &dialPosition) ;
    SDL_Flip(screen);
    SDL_FreeSurface(dial) ;
    //TTF_CloseFont(police);
    TTF_Quit();
}

//Placer un personnage sur le screen (utiliser dans l'introduction seulement)
void placeCharacter(SDL_Surface *screen, int choice, int x, int y)
{

    // Character hero ;
    //hero.heroImage = NULL;

    SDL_Rect position ;
    position.x = x  ;
    position.y = y ;
    switch(choice)
    {
    case 0:
        //character = IMG_Load("graphics/boss.png") ;
        hero.image = IMG_Load("graphics/boss.png") ;
        break ;

    case 1:

        hero.image = IMG_Load("graphics/GuyLeft1.png") ;
        break ;

    case 2:
        hero.image = IMG_Load("graphics/angryboss.png") ;
        break ;

    default:
        break ;
    }
    SDL_BlitSurface(hero.image, NULL, screen, &position) ;
    SDL_Flip(screen);
    SDL_FreeSurface(hero.image) ;
}


//Charger le niveau de notre choix
void getLevels(SDL_Surface *screen, int levelChoice)
{
    SDL_Surface *level = NULL ;
    SDL_Rect position ;
    position.x = 0 ;
    position.y = 0 ;
    switch(levelChoice)
    {
    case 0:
        level = IMG_Load("graphics/classroom.png") ;
        SDL_BlitSurface(level,NULL,screen, &position) ;
        SDL_Flip(screen);
        break;

//case 1:
//charger les sprites ici
    case 1 :
        // setHeroSprites();

        setSprite(screen, currentCharacterPosition, heroLeftSprites[currentCharacterSprite], HERO);
        setSprite(screen, 111, "graphics/bottle.png", BOTTLE);

        //LEFT TABLE RANK
        setSprite(screen, 61, "graphics/TableLeft.png", TABLE);
        setSprite(screen, 62, "graphics/TableRight.png", TABLE);
        setSprite(screen, 85, "graphics/TableLeft.png", TABLE);
        setSprite(screen, 86, "graphics/TableRight.png", TABLE);
        setSprite(screen, 109, "graphics/TableLeft.png", TABLE);
        setSprite(screen, 110, "graphics/TableRight.png", TABLE);

        //CENTER TABLE RANK
        setSprite(screen, 65, "graphics/TableLeft.png", TABLE);
        setSprite(screen, 66, "graphics/TableRight.png", TABLE);
        setSprite(screen, 89, "graphics/TableLeft.png", TABLE);
        setSprite(screen, 90, "graphics/TableRight.png", TABLE);
        setSprite(screen, 113, "graphics/TableLeft.png", TABLE);
        setSprite(screen, 114, "graphics/TableRight.png", TABLE);

        //RIGHT TABLE RANK
        setSprite(screen, 69, "graphics/TableLeft.png", TABLE);
        setSprite(screen, 70, "graphics/TableRight.png", TABLE);
        setSprite(screen, 93, "graphics/TableLeft.png", TABLE);
        setSprite(screen, 94, "graphics/TableRight.png", TABLE);
        setSprite(screen, 117, "graphics/TableLeft.png", TABLE);
        setSprite(screen, 118, "graphics/TableRight.png", TABLE);

        //BOSS
        setSprite(screen, 5, "graphics/angryboss.png", BOSS);


    default:
        break ;
    }
}

