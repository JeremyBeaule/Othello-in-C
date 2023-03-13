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

void initialiser_plateau(Board *board);


void afficher_plateau(SDL_Renderer* renderer, Board* board, SDL_Texture* black_texture, SDL_Texture* white_texture, SDL_Texture* grille_texture,SDL_Texture* contour) ;
void affiche_tour(SDL_Renderer* renderer,Player* current_player);
void afficher_popup(SDL_Renderer* renderer, const char* message);
void wait_two_seconds() ;

void Init_texture(SDL_Texture *black_texture,SDL_Texture *white_texture,SDL_Surface* grille_surface,SDL_Surface* contour_surface,SDL_Window* window,SDL_Renderer *renderer);
Player* creer_joueur(char* nom, PlayerColor couleur) ;
void init_All();
void placer_pion(int x, int y, SDL_Renderer* renderer, SDL_Texture* texture, Board* board);

int afficher_menu(SDL_Renderer* renderer) ;
void start();
SDL_Window* window;
SDL_Renderer *renderer;
// Charger les textures pour les pions noirs et blancs
SDL_Texture *black_texture;
SDL_Texture *white_texture ;
// Charger les textures la grille et le contour de jeu
SDL_Surface* grille_surface;
SDL_Texture* grille_texture ;
SDL_Surface* contour_surface ;
SDL_Texture* contour_texture ;
Player* joueur_noir ;
Player* joueur_blanc;
Player* current_player;
TTF_Font* font; // police d ecriture
