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
joueur_noir = creer_joueur("Noir", BLACK);
joueur_blanc = creer_joueur("Blanc", WHITE);
current_player = joueur_blanc; // Le joueur courant est le joueur 1
//creation de la fenetre
window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, BOARD_SIZE * CELL_SIZE+300, BOARD_SIZE * CELL_SIZE+300,0);
//creation du renderer, ce qu on va mettre a jour pour afficher des choses
renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
// Charger les textures pour les pions noirs et blancs
black_texture = IMG_LoadTexture(renderer, "pion_noir.png");
white_texture = IMG_LoadTexture(renderer, "pion_blanc.png");
// Charger les textures la grille et le contour de jeu
grille_surface = IMG_Load("Board.png");
grille_texture = SDL_CreateTextureFromSurface(renderer, grille_surface);
contour_surface = IMG_Load("contour_board.png");
contour_texture = SDL_CreateTextureFromSurface(renderer, contour_surface);
Init_texture(black_texture,white_texture,grille_surface,contour_surface,window,renderer);
    
}
