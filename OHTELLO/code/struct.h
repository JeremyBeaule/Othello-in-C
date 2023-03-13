#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#define BOARD_SIZE 8
#define CELL_SIZE 64
#define PIECE_SIZE 50 //taille de pion en pixel
typedef enum {
    EMPTY,
    BLACK,
    WHITE
} PlayerColor;

typedef struct {
    PlayerColor player;
    SDL_Rect rect;
} Cell;

typedef struct {
    Cell cells[BOARD_SIZE][BOARD_SIZE];
    int grid_x;
    int grid_y;
    int cell_size;
} Board;
typedef struct {
    char* nom;
    PlayerColor couleur;
    int score;
} Player;

extern void initialiser_plateau(Board *board);


extern void afficher_plateau(SDL_Renderer* renderer, Board* board, SDL_Texture* black_texture, SDL_Texture* white_texture, SDL_Texture* grille_texture,SDL_Texture* contour) ;
extern void affiche_tour(SDL_Renderer* renderer,Player* current_player);
extern void afficher_popup(SDL_Renderer* renderer, const char* message);
extern void wait_two_seconds() ;

extern void Init_texture(SDL_Texture *black_texture,SDL_Texture *white_texture,SDL_Surface* grille_surface,SDL_Surface* contour_surface,SDL_Window* window,SDL_Renderer *renderer);
Player* creer_joueur(char* nom, PlayerColor couleur) ;
extern void init_All();
extern void placer_pion(int x, int y, SDL_Renderer* renderer, SDL_Texture* texture, Board* board);

extern int afficher_menu(SDL_Renderer* renderer) ;
extern void start();
