#include "struct.h"

void Init_texture(SDL_Texture *black_texture,SDL_Texture *white_texture,SDL_Surface* grille_surface,SDL_Surface* contour_surface,SDL_Window* window,SDL_Renderer *renderer){
if (!black_texture) {
    printf("Erreur de chargement de la texture pour les pions noirs: %s\n", IMG_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
if (!white_texture) {
    printf("Erreur de chargement de la texture pour les pions blancs: %s\n", IMG_GetError());
    SDL_DestroyTexture(black_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
if (grille_surface == NULL) {
    printf("Erreur de chargement de l'image de fond pour la grille : %s\n", IMG_GetError());

}
if (contour_surface == NULL) {
    printf("Erreur de chargement de l'image de fond pour la grille : %s\n", IMG_GetError());

}
if (!renderer) {
    printf("Erreur de création du rendu SDL: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();

}
if (!window) {
    printf("Erreur de création de la fenêtre: %s\n", SDL_GetError());
    SDL_Quit();

}
}
Player* creer_joueur(char* nom, PlayerColor couleur) {
    Player* joueur = (Player*)malloc(sizeof(Player));
    if (joueur == NULL) {
        fprintf(stderr, "Erreur : impossible d'allouer la mémoire pour le joueur.\n");
        exit(EXIT_FAILURE);
    }
    joueur->nom = nom;
    joueur->couleur = couleur;
    joueur->score = 0;
    return joueur;
}
void init_All(){
    TTF_Init();
    //creation des joueurs
Player* joueur_noir = creer_joueur("Noir", BLACK);
Player* joueur_blanc = creer_joueur("Blanc", WHITE);
Player* scurrent_player = joueur_blanc; // Le joueur courant est le joueur 1
//creation de la fenetre
SDL_Window*  window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, BOARD_SIZE * CELL_SIZE+300, BOARD_SIZE * CELL_SIZE+300,0);
//creation du renderer, ce qu on va mettre a jour pour afficher des choses
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
// Charger les textures pour les pions noirs et blancs
SDL_Texture *black_texture = IMG_LoadTexture(renderer, "image/pion_noir.png");
SDL_Texture *white_texture = IMG_LoadTexture(renderer, "image/pion_blanc.png");
// Charger les textures la grille et le contour de jeu
SDL_Surface* grille_surface = IMG_Load("image/Board.png");
SDL_Texture*grille_texture = SDL_CreateTextureFromSurface(renderer, grille_surface);
SDL_FreeSurface(grille_surface);//on en a plus besoin on peut liberer
SDL_Surface* contour_surface = IMG_Load("image/contour_board.png");
SDL_Texture* contour_texture = SDL_CreateTextureFromSurface(renderer, contour_surface);
SDL_FreeSurface(contour_surface);//on en a plus besoin on peut liberer
Init_texture(black_texture,white_texture,grille_surface,contour_surface,window,renderer);
    
}

void initialiser_plateau(Board *board) {
    // Calculer les dimensions de la grille
    int screen_height=800;
    int screen_width=800;
    int grid_size = screen_height * 0.6;
    int margin_x = (screen_width - grid_size) / 2;
    int margin_y = (screen_height - grid_size) / 2;
    int cell_size = grid_size / BOARD_SIZE;
    int grid_x = margin_x;
    int grid_y = margin_y;

    board->grid_x = grid_x;
    board->grid_y = grid_y;
    board->cell_size = cell_size;
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