typedef enum {BAS,HAUT,GAUCHE,DROITE} Direction;

typedef enum {NONE, HERO, BOSS, TABLE, BOTTLE, FIRE, LIFE} ElementType;

typedef struct imageToDiplay
{
    Direction direction;
    SDL_Rect position;
    SDL_Surface *image;
    SDL_Surface *screen;
}ImageToDisplay;


typedef struct gridSquare
{
    SDL_Rect position;
    SDL_Surface *image;
    ElementType elementType;
}GridSquare;
