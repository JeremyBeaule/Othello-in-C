#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define BOARD_SIZE 8
#define CELL_SIZE 64

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
} Board;

void initialiser_plateau(Board *board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board->cells[i][j].player = EMPTY;
            board->cells[i][j].rect.x = i * CELL_SIZE;
            board->cells[i][j].rect.y = j * CELL_SIZE;
            board->cells[i][j].rect.w = CELL_SIZE;
            board->cells[i][j].rect.h = CELL_SIZE;
        }
    }

    int center = BOARD_SIZE / 2;
    board->cells[center - 1][center - 1].player = WHITE;
    board->cells[center][center].player = WHITE;
    board->cells[center - 1][center].player = BLACK;
    board->cells[center][center - 1].player = BLACK;
}

void afficher_plateau(SDL_Renderer* renderer, Board* board, SDL_Texture* black_texture, SDL_Texture* white_texture) {
    SDL_RenderClear(renderer);

    // Définir la taille de la fenêtre
    int SCREEN_WIDTH = 650;
    int SCREEN_HEIGHT = 500;

    // Calculer les dimensions de la grille
    int grid_size = SCREEN_HEIGHT * 0.7;
    int margin_x = (SCREEN_WIDTH - grid_size) / 2;
    int margin_y = (SCREEN_HEIGHT - grid_size) / 2;
    int cell_size = grid_size / BOARD_SIZE;
    int grid_x = margin_x;
    int grid_y = margin_y;

    // Dessiner le fond vert
    SDL_SetRenderDrawColor(renderer, 50, 128, 65, 255);
    SDL_RenderClear(renderer);

    // Dessiner le cadrillage
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i <= BOARD_SIZE; i++) {
        SDL_RenderDrawLine(renderer, grid_x + i * cell_size, grid_y, grid_x + i * cell_size, grid_y + grid_size-6.5);
        SDL_RenderDrawLine(renderer, grid_x, grid_y + i * cell_size, grid_x + grid_size - 6.5 , grid_y + i * cell_size );//probleme taille
    }

    // Dessiner les pions
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            PlayerColor player = board->cells[i][j].player;
            if (player == BLACK) {
                SDL_Rect rect = board->cells[i][j].rect;
                rect.x = grid_x + i * cell_size;
                rect.y = grid_y + j * cell_size;
                rect.w = cell_size;
                rect.h = cell_size;
                SDL_RenderCopy(renderer, black_texture, NULL, &rect);
            } else if (player == WHITE) {
                SDL_Rect rect = board->cells[i][j].rect;
                rect.x = grid_x + i * cell_size;
                rect.y = grid_y + j * cell_size;
                rect.w = cell_size;
                rect.h = cell_size;
                SDL_RenderCopy(renderer, white_texture, NULL, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}
void init_SDL(){

    
}


int main(int argc, char *argv[]) {
 // Créer la fenêtre et le rendu SDL
SDL_Window* window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, BOARD_SIZE * CELL_SIZE+100, BOARD_SIZE * CELL_SIZE, 0);
if (!window) {
    printf("Erreur de création de la fenêtre: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
}
SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
if (!renderer) {
    printf("Erreur de création du rendu SDL: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}

// Charger les textures pour les pions noirs et blancs
SDL_Texture *black_texture = IMG_LoadTexture(renderer, "pion_noir.png");
if (!black_texture) {
    printf("Erreur de chargement de la texture pour les pions noirs: %s\n", IMG_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}
SDL_Texture *white_texture = IMG_LoadTexture(renderer, "pion_blanc.jpg");
if (!white_texture) {
    printf("Erreur de chargement de la texture pour les pions blancs: %s\n", IMG_GetError());
    SDL_DestroyTexture(black_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}

// Initialiser le plateau de jeu et l'afficher
Board board;
initialiser_plateau(&board);
afficher_plateau(renderer, &board, black_texture, white_texture);

// Attendre que l'utilisateur ferme la fenêtre
SDL_Event event;
int quit = 0;
while (!quit) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = 1;
        }
    }
}

// Libérer les ressources allouées
SDL_DestroyTexture(black_texture);
SDL_DestroyTexture(white_texture);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
IMG_Quit();
SDL_Quit();
return 0;
}