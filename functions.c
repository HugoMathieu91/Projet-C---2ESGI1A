#include "init.c"

//To get audio, music as choice
void getAudio(int choice)
{
  //Mix_Music *music ;
  switch(choice)
  {
    case 0:
        music = Mix_LoadMUS("audio/mainMusic.mp3") ;
        break ;

    case 1:
        music = Mix_LoadMUS("audio/gameOver.mp3")  ;
        break ;

    case 2:
        music = Mix_LoadMUS("audio/dead.mp3") ;
        break ;

    default :
        break ;
  }
  //1 to play the music 1 time , -1 for loop
  Mix_PlayMusic(music, -1) ;

}

/*void getSound(int choice)
{

    switch(choice)
    {
    case 0:
        sound = Mix_LoadWAV("audio/pain.wav") ;
        Mix_VolumeChunk(sound, MIX_MAX_VOLUME/2);

        break;

    default:
        break;

    }
      Mix_VolumeChunk(sound, MIX_MAX_VOLUME/2); //Mettre un volume pour ce wav
     Mix_PlayChannel(1, sound, 0);
     Mix_FreeChunk(sound) ;
     //Mix_PlayMusic(sound, 1) ;
}*/

//Set fireSprites
void setFireSprites()
{
    fireSprites[0] =  "graphics/Fire1.png" ;
    fireSprites[1] =  "graphics/Fire2.png" ;
    fireSprites[2] =  "graphics/Fire3.png" ;
    fireSprites[3] =  "graphics/Fire4.png" ;
}

//Set hero sprites
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

//Set a fire line
void setFireLine()
{
    int firePos ;
    setFireSprites() ;
    for(firePos=36 ; firePos<=47 ; firePos++)
    {
        setSprite(firePos, fireSprites[0], FIRE) ;
    }
}

//Set a sprite on the game grid, arguments: current screen, position, elementType
void setSprite(int position, const char *sprite, ElementType elementType)
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
    //Si on change de direction ou qu'on est sur le dernier sprite alors on revient sur le premier sprite
    if(currentDirection != direction
            || currentCharacterSprite == 2)
    {
        currentCharacterSprite = 0;
    }
    else
    {
        //Sinon le projet sprite s'affichera
        currentCharacterSprite++;
    }
}

//Get random int , in a range
int getRandomValue(int lower, int upper)
{
    srand(time(0));

    while (1)
    {
        //random entre 0 (min position) et 143 (max position)
        //Si le nombre choisi correspond a une position dans le tableau qui est déjà occupé alors on regenère un nombre
        int num = (rand() % (upper - lower + 1)) + lower;
        if(board[num].elementType == TABLE
                || board[num].elementType == HERO
                || board[num].elementType == BOSS
                || board[num].elementType == BOTTLE
                || board[num].elementType ==FIRE)
        {
            continue;
        }
        return num;
    }
}

//Generate game grid
void generateGrid()
{
    int initialX = 0;
    int incrementalX = initialX;
    int incrementalY = 0;

    //On rempli board avec des carrés blancs
    for(int i=0; i < 144; i++)
    {
        board[i].image = IMG_Load("graphics/testGrid.png");
        board[i].position.h = height_case;
        board[i].position.w = width_case;
        board[i].position.x = incrementalX;
        board[i].position.y = incrementalY;
        ElementType type = NONE;
        board[i].elementType = type;

        //Pour faire les lignes
        if(incrementalX < 11*width_case + initialX)
        {
            incrementalX+=width_case;
        }
        else
        {
            incrementalX = initialX;
            incrementalY += height_case;
        }
        SDL_BlitSurface(board[i].image, NULL, screen, &board[i].position) ;
        SDL_Flip(screen);
        SDL_FreeSurface(board[i].image) ;
    }
}


void getLife()
{
    TTF_Font *police = NULL;

    SDL_Surface *heart = NULL ;
    SDL_Surface *remainingLifes = NULL;

    SDL_Rect heartPosition ;
    heartPosition.x  = 125 ;
    heartPosition.y = 25 ;

    SDL_Rect remainingLifesPosition ;
    remainingLifesPosition.x =  150 ;
    remainingLifesPosition.y = 25 ;

    color.r = 255;
    color.g = 0 ;
    color.b = 0 ;

    police = TTF_OpenFont("fonts/sixty.ttf", 20);
    setSprite(3,"graphics/testGrid.png", NONE);

     heart = IMG_Load("graphics/life.png");

     sprintf(lives, "%d", lifeCount) ;
    remainingLifes = TTF_RenderText_Blended(police, lives, color);


    SDL_BlitSurface(heart, NULL, screen, &heartPosition) ;
    SDL_BlitSurface(remainingLifes,NULL,screen,&remainingLifesPosition ) ;

    SDL_Flip(screen) ;

    SDL_FreeSurface(heart) ;
    SDL_FreeSurface(remainingLifes) ;

}
void getScore()
{
    TTF_Font *police = NULL;

    SDL_Surface *champagne = NULL ;
    SDL_Surface *score = NULL ;

    SDL_Rect champagnePosition ;
    champagnePosition.x =  25 ;
    champagnePosition.y = 25 ;

    SDL_Rect scorePosition ;
    scorePosition.x = 50 ;
    scorePosition.y = 25 ;

    color.r = 255;
    color.g = 0 ;
    color.b = 0 ;

    police = TTF_OpenFont("fonts/sixty.ttf", 20);
    setSprite(1,"graphics/testGrid.png", NONE);

    champagne = IMG_Load("graphics/ScoreBottle.png") ;

    sprintf(scorePlayer, "%d", bottleCount) ;
    score = TTF_RenderText_Blended(police, scorePlayer, color);


    SDL_BlitSurface(score, NULL, screen, &scorePosition) ;
    SDL_BlitSurface(champagne, NULL, screen, &champagnePosition) ;

    SDL_Flip(screen);

    SDL_FreeSurface(champagne) ;
    SDL_FreeSurface(score) ;

}

void deathAnimation()
{
    int i  ;

    for(i= 0 ; i <= 12 ; i++)
    {
        setSprite(currentCharacterPosition,heroDownSprites[0], HERO) ;
        SDL_Delay(50) ;
        setSprite(currentCharacterPosition, heroLeftSprites[0], HERO) ;
        SDL_Delay(50) ;
        setSprite(currentCharacterPosition, heroUpSprites[0], HERO) ;
        SDL_Delay(50) ;
        setSprite(currentCharacterPosition, heroRightSprites[0] ,HERO) ;
        SDL_Delay(50) ;
    }
}
//To move our hero - a corriger car inutile de prendre le screen
void moveCharacter(SDL_Surface *screen, int direction)
{
    //TODO: replace cases by enum.
    int desiredLeftPosition = 0;
    int desiredRightPosition = 0;
    int desiredUpPosition = 0;
    int desiredDownPosition = 0;

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
            setSprite(currentCharacterPosition, heroLeftSprites[0], HERO);
            return;
        }

        if(board[desiredLeftPosition].elementType == FIRE)
        {
            //setSprite(currentCharacterPosition, heroLeftSprites[currentCharacterSprite], HERO);

            lifeCount-- ;
            //return;
        }

        if(board[desiredLeftPosition].elementType == BOTTLE)
        {
            //TODO Create method (function for noob) to setBottlePosition.
            int value = getRandomValue(48,143);
            setSprite(value, "graphics/bottle.png", BOTTLE);
            bottleCount++ ;
        }

        setSprite(currentCharacterPosition, "graphics/testGrid.png", NONE);

        currentCharacterPosition = desiredLeftPosition;
        setNextSprite(direction);
        setSprite(desiredLeftPosition, heroLeftSprites[currentCharacterSprite], HERO);
        break;

    case 1:
        desiredUpPosition = currentCharacterPosition - 12;
        if(desiredUpPosition < 0)
        {
            return;
        }

        if(board[desiredUpPosition].elementType == TABLE)
        {
            setSprite(currentCharacterPosition, heroUpSprites[currentCharacterSprite], HERO);
            return;
        }


        if(board[desiredUpPosition].elementType == FIRE)
        {
            //setSprite(currentCharacterPosition, heroUpSprites[currentCharacterSprite], HERO);
            lifeCount-- ;

            //return;
        }

        if(board[desiredUpPosition].elementType == BOTTLE)
        {
            int value = getRandomValue(48,143);
            setSprite(value, "graphics/bottle.png", BOTTLE);
            bottleCount++ ;
        }

        setSprite(currentCharacterPosition,"graphics/testGrid.png", NONE);

        currentCharacterPosition = desiredUpPosition;
        setNextSprite(direction);
        setSprite(currentCharacterPosition, heroUpSprites[currentCharacterSprite], HERO);
        break;

    case 2:
        if(((int)currentCharacterPosition + 1) % 12 == 0)
        {
            return;
        }

        desiredRightPosition = currentCharacterPosition +1;
        if(board[desiredRightPosition].elementType == TABLE)
        {
            setSprite(currentCharacterPosition, heroRightSprites[0], HERO);
            return;
        }

        if(board[desiredRightPosition].elementType == FIRE)
        {
            //setSprite(currentCharacterPosition, heroRightSprites[currentCharacterSprite], HERO);
            //return;

            lifeCount-- ;
        }


        if(board[desiredRightPosition].elementType == BOTTLE)
        {
            int value = getRandomValue(48,143);
            setSprite(value, "graphics/bottle.png", BOTTLE);
             bottleCount++ ;
        }

        setSprite(currentCharacterPosition,"graphics/testGrid.png", NONE);
        currentCharacterPosition= (int)desiredRightPosition;
        setNextSprite(direction);
        setSprite(desiredRightPosition, heroRightSprites[currentCharacterSprite], HERO);
        break;

    case 3:
        desiredDownPosition = currentCharacterPosition + 12;
        if(desiredDownPosition > 143)
        {
            return;
        }

        if(board[desiredDownPosition].elementType == TABLE)
        {
            setSprite(currentCharacterPosition, heroDownSprites[0], HERO);
            return;
        }

        if(board[desiredDownPosition].elementType == FIRE)
        {
            //setSprite(currentCharacterPosition, heroDownSprites[currentCharacterSprite], HERO);
            //return;

            lifeCount-- ;
        }

        if(board[desiredDownPosition].elementType == BOTTLE)
        {
            int value = getRandomValue(48,143);
            setSprite(value, "graphics/bottle.png", BOTTLE);
            bottleCount++ ;
        }

        setSprite(currentCharacterPosition,"graphics/testGrid.png", NONE);
        currentCharacterPosition = desiredDownPosition;
        setNextSprite(direction);
        setSprite(currentCharacterPosition, heroDownSprites[currentCharacterSprite], HERO);
        break;
    }
    currentDirection = direction;

    SDL_Flip(screen);
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
                    //run = 0 ;
                    introduction(screen);
                    break;
                case 1:
                    settings(screen);
                    break;

                case 2:

                    SDL_FreeSurface(imageMenu) ;
                    SDL_FreeSurface(champagneSelect) ;
                    //SDL_Quit() ;

                    exit(EXIT_SUCCESS) ;
                    break ;

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
    //Sinon warning control reaches end of non-void function
    return 1 ;
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
    screen = SDL_SetVideoMode(600,600,32,SDL_HWSURFACE|SDL_INIT_TIMER) ;
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
    SDL_FreeSurface(settings) ;
    return EXIT_SUCCESS ;
}

void initAudio()
{
     if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }

   //Mix_AllocateChannels(1) ;
}


void gameOver()
{

    getAudio(1)  ;


    SDL_Surface *gameOver = NULL ;
    SDL_Rect gameOverPos ;

    gameOverPos.x = 0 ;
    gameOverPos.y = 0 ;

    gameOver = IMG_Load("graphics/gameOver.jpg") ;
     SDL_BlitSurface(gameOver, NULL, screen, &gameOverPos) ;

     SDL_Flip(screen) ;

     SDL_FreeSurface(gameOver) ;
     SDL_Delay(7000) ;



}
int introduction()
{
    initAudio() ;

    int dialNumber =  1 ;
    int run = 1 ;

    SDL_Event event;
    //Nouvelle fenetre
     screen = SDL_SetVideoMode(600,600,32,SDL_HWSURFACE) ;
    SDL_WM_SetCaption("ESGI Adventure", NULL) ;

    getLevels(0) ;
     introDialog(0) ;
    while(run)
    {
        SDL_WaitEvent(&event) ;

        switch(event.type)
        {
        case SDL_QUIT:

            exit(EXIT_SUCCESS) ;
            run =0 ;
            break ;


        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:

                menu(screen) ;
                run = 0 ;
                break ;

            case SDLK_RETURN:

                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
                    {
                        if(dialNumber<3)
                        {
                            getLevels(0) ;
                            placeCharacter(1,550,250) ;
                            placeCharacter(0,175,50 ) ;
                            introDialog(dialNumber) ;
                            dialNumber++ ;
                        }

                        else if(dialNumber == 3)
                        {
                            getAudio(0) ;
                            getLevels(0) ;
                            placeCharacter(2, 175,50 );
                            placeCharacter(1,550,250) ;
                            introDialog(dialNumber) ;
                            dialNumber++ ;
                        }

                        else
                        {
                            play() ;
                            run =0 ;
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

    //On est encore dans le while du menu à ce niveau là. Sans réappeler le menu le jeu se termine ici et on ne peux pas refaire une partie sans relancer le jeu.
    //Une erreur apparait quand on quitte le jeu après plusieurs parties enchainées, je pense que cela vient d'ici car on ne quitte pas certaines boucles proprement.
    menu(screen) ;
    //Sinon warning control reaches end of non-void function
    return 1 ;
}

void play()
{
     generateGrid();
     int i ;

    setHeroSprites();
    currentCharacterSprite = 0;
    currentCharacterPosition = 71;
    bottleCount = 0 ;
    lifeCount = 3 ;


    getLevels(1) ;
    setFireLine() ;

    int firePos[5]  = {145} ; //En dehors du tableau pour commencer la boucle plus bas
    int wait = 1 ;
    SDL_Event control;

    while(wait)
    {
        SDL_WaitEvent(&control) ;

        if(bottleCount %2 == 1 && bottleCount< 25)
        {
            for(i = 0 ; i<5 ; i++)
            {
                setSprite(firePos[i],"graphics/testGrid.png", NONE);
                firePos[i] = getRandomValue(38,143);
                setSprite(firePos[i], fireSprites[0], FIRE) ;
            }
        }


        switch(control.type)
        {
        case SDL_QUIT:
            exit(EXIT_SUCCESS) ;
            wait = 0 ;
            break ;


        case SDL_KEYDOWN:
            switch(control.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                Mix_FreeMusic(music) ;
                Mix_CloseAudio();
                menu(screen) ;

                break ;
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
        getLife();
        getScore() ;

         if(lifeCount == 0 )
        {
            getAudio(2) ;
            deathAnimation() ;
            break ;
       }


    }
     gameOver() ;
     Mix_FreeMusic(music) ;
     Mix_CloseAudio();
    // menu(screen) ;
}

void initTTF()
{
     TTF_Init() ;
     if ( TTF_Init() == -1 )
    {
        fprintf( stderr,"Problem with ttf loading: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

}


//Appelle les dialogues durant l'introduction du jeu
void introDialog(int dialNumb)
{
    initTTF() ;
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
void placeCharacter(int choice, int x, int y)
{
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
void getLevels(int levelChoice)
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

        setSprite(currentCharacterPosition, heroLeftSprites[currentCharacterSprite], HERO);
        setSprite(111, "graphics/bottle.png", BOTTLE);

        //LEFT TABLE RANK
        setSprite(61, "graphics/TableLeft.png", TABLE);
        setSprite(62, "graphics/TableRight.png", TABLE);
        setSprite(85, "graphics/TableLeft.png", TABLE);
        setSprite(86, "graphics/TableRight.png", TABLE);
        setSprite(109, "graphics/TableLeft.png", TABLE);
        setSprite(110, "graphics/TableRight.png", TABLE);

        //CENTER TABLE RANK
        setSprite(65, "graphics/TableLeft.png", TABLE);
        setSprite(66, "graphics/TableRight.png", TABLE);
        setSprite(89, "graphics/TableLeft.png", TABLE);
        setSprite(90, "graphics/TableRight.png", TABLE);
        setSprite(113, "graphics/TableLeft.png", TABLE);
        setSprite(114, "graphics/TableRight.png", TABLE);

        //RIGHT TABLE RANK
        setSprite(69, "graphics/TableLeft.png", TABLE);
        setSprite(70, "graphics/TableRight.png", TABLE);
        setSprite(93, "graphics/TableLeft.png", TABLE);
        setSprite(94, "graphics/TableRight.png", TABLE);
        setSprite(117, "graphics/TableLeft.png", TABLE);
        setSprite(118, "graphics/TableRight.png", TABLE);

        //BOSS
        setSprite(5, "graphics/angryboss.png", BOSS);


    default:
        break ;
    }
}

