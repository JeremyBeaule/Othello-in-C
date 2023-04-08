#include "struct.h"
int screen_height = 800;
int screen_width = 800; // a changer dans init et affichage et logique.c si on change
int grid_size = 480;    // 800*0.6
int margin_x = (800 - 480) / 2;
int margin_y = (800 - 480) / 2;
int cell_size = 480 / BOARD_SIZE;
int grid_x = 160; //=margin x
int grid_y = 160; //=margin y
void Init_texture()
{
    if (!black_texture)
    {
        printf("Erreur de chargement de la texture pour les pions noirs: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    if (!white_texture)
    {
        printf("Erreur de chargement de la texture pour les pions blancs: %s\n", IMG_GetError());
        SDL_DestroyTexture(black_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    if (!contour_texture)
    {
        printf("Erreur de chargement de la texture pour le contour: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    if (!grille_texture)
    {
        printf("Erreur de chargement de la texture pour la grille: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    if (!fond_board)
    {
        printf("Erreur de chargement de la texture pour le fond: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    if (!grey_texture)
    {
        printf("Erreur de chargement de la texture pour le fond: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    if (!carre_grille_texture)
    {
        printf("Erreur de chargement de la texture pour le fond: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    if (!renderer)
    {
        printf("Erreur de création du rendu SDL: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    if (!window)
    {
        printf("Erreur de création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }
}
Player *creer_joueur(char *nom, PlayerColor couleur)
{
    Player *joueur = (Player *)malloc(sizeof(Player));
    if (joueur == NULL)
    {
        fprintf(stderr, "Erreur : impossible d'allouer la mémoire pour le joueur.\n");
        exit(EXIT_FAILURE);
    }
    joueur->nom = nom;
    joueur->couleur = couleur;
    joueur->score = 0;
    return joueur;
}

void init_All()
{
    TTF_Init();
    // creation des joueurs
    joueur_noir = creer_joueur("Noir", BLACK);
    joueur_blanc = creer_joueur("Blanc", WHITE);
    current_player = joueur_noir; // Le joueur courant est le joueur 1
    // creation de la fenetre
    window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, BOARD_SIZE * CELL_SIZE + 300, BOARD_SIZE * CELL_SIZE + 300, 0);
    // creation du renderer, ce qu on va mettre a jour pour afficher des choses
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    // Charger les textures pour les pions noirs et blancs
    black_texture = IMG_LoadTexture(renderer, "image/pion_noir.png");  // si on ne choisit aucun theme celui ci est pris par defaut
    white_texture = IMG_LoadTexture(renderer, "image/pion_blanc.png"); // si on ne choisit aucun theme celui ci est pris par defaut
    grey_texture = IMG_LoadTexture(renderer, "image/point_gris.png");  // si on ne choisit aucun theme celui ci est pris par defaut
    carre_grille_texture = IMG_LoadTexture(renderer, "image/carre_grille.png");

    // Charger les textures la grille
    grille_texture = IMG_LoadTexture(renderer, "image/Board.png");  // si on ne choisit aucun theme celui ci est pris par defaut
    fond_board = IMG_LoadTexture(renderer, "image/fond_board.png"); // si on ne choisit aucun theme celui ci est pris par defaut
    // Charger les textures du contour
    contour_texture = IMG_LoadTexture(renderer, "image/contour_board.png");
    // Charger les textures du fond du menu
    Init_texture();
}

void initialiser_plateau(Board *board)
{
    // Calculer les dimensions de la grille
    // a changer dans init et affichage et logique.c si on change

    board->grid_x = grid_x;
    board->grid_y = grid_y;
    board->cell_size = cell_size;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
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
void free_textures(SDL_Texture **textures, int num_textures)
{
    for (int i = 0; i < num_textures; i++)
    {
        SDL_DestroyTexture(textures[i]);
    }
}
