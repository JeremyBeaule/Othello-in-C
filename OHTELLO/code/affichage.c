
#include "struct.h"

//fonction qui bloque toutes les entrées utilisateurs pendant 2 secondes
void wait_two_seconds() {
    SDL_Event event;
    Uint32 start_time = SDL_GetTicks();
    Uint32 current_time = start_time;
    SDL_PumpEvents();
    SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
    while (current_time - start_time < 2000) {
        SDL_PumpEvents();
        while (SDL_PollEvent(&event)) {
            /* Bloquer les entrées utilisateur */
        }
        SDL_Delay(10);
        current_time = SDL_GetTicks();
    }
    SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
    SDL_PumpEvents();
}


void afficher_plateau(SDL_Renderer* renderer, Board* board, SDL_Texture* black_texture, SDL_Texture* white_texture, SDL_Texture* grille_texture,SDL_Texture* contour) {
    SDL_RenderClear(renderer);

    // Définir la taille de la fenêtre
    int SCREEN_WIDTH = 800;
    int SCREEN_HEIGHT = 800;

    // Calculer les dimensions de la grille
    int grid_size = SCREEN_HEIGHT * 0.6;//taille de la grille comme 70% de la hauteur de la fenetre
    int margin_x = (SCREEN_WIDTH - grid_size) / 2; //pour la marge sur les cotés
    int margin_y = (SCREEN_HEIGHT - grid_size) / 2;//pour la marge haut et bas
    int cell_size = grid_size / BOARD_SIZE ; // taille de chaque case
    int grid_x = margin_x; //pour placer les pions, on aurait pu utiliser margin_x direct mais c est une question de lisibilité
    int grid_y = margin_y;
    // Calculer la taille de la bordure en fonction de la taille de la grille
    int border_size = (int)(grid_size * 0.05); // Par exemple, la bordure peut faire 5% de la taille de la grille
    int border_x = margin_x - border_size;
    int border_y = margin_y - border_size;
    int border_width = grid_size + border_size * 2;
    int border_height = grid_size + border_size * 2;

    // Dessiner le contour du plateau
    SDL_Rect border_rect = {border_x, border_y, border_width, border_height};

   
   
    // Dessiner le fond vert
    SDL_SetRenderDrawColor(renderer, 50, 128, 65, 255);
    SDL_RenderClear(renderer);

    // Dessiner l'image de fond pour la grille et pour le contour de la grille
    SDL_Rect grille_rect = {grid_x, grid_y, grid_size, grid_size};
    SDL_RenderCopy(renderer, contour, NULL, &border_rect);
    SDL_RenderCopy(renderer, grille_texture, NULL, &grille_rect);


    //Dessiner le cadrillage
    SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
    for (int i = 1; i < BOARD_SIZE; i++) {
        SDL_RenderDrawLine(renderer, grid_x + i * cell_size, grid_y, grid_x + i * cell_size, grid_y + grid_size);
        SDL_RenderDrawLine(renderer, grid_x, grid_y + i * cell_size, grid_x + grid_size, grid_y + i * cell_size);
    }

    // Dessiner les pions
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            PlayerColor player = board->cells[i][j].player;
            if (player == BLACK) {
                SDL_Rect rect = board->cells[i][j].rect;
                rect.x = grid_x + i * cell_size+3;
                rect.y = grid_y + j * cell_size+3;
                rect.w = cell_size-5;
                rect.h = cell_size-5;
                SDL_RenderCopy(renderer, black_texture, NULL, &rect);
            } else if (player == WHITE) {
                SDL_Rect rect = board->cells[i][j].rect;
                rect.x = grid_x + i * cell_size+3;
                rect.y = grid_y + j * cell_size+3;
                rect.w = cell_size-5;
                rect.h = cell_size-5;
                SDL_RenderCopy(renderer, white_texture, NULL, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void affiche_tour(SDL_Renderer* renderer,Player* current_player) {
    // Charger la police d'écriture
    
    TTF_Font* font = TTF_OpenFont("image/ASMAN.TTF", 24); 
    if (!font) {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        return;
    }

    // Créer le message
    const char* message;
    message="au noir de commencer";
    if (current_player->couleur == WHITE) {
        message = "Tour du joueur blanc";
    } else {
        message = "Tour du joueur noir";
    }

    // Créer une surface avec le message
    SDL_Color color = { 255, 255, 255 }; // Couleur du texte (blanc)
    SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
    if (!surface) {
        printf("Erreur de création de la surface : %s\n", SDL_GetError());
        TTF_CloseFont(font);
        return;
    }

    // Créer une texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Erreur de création de la texture : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    // Définir la zone d'affichage du texte
    SDL_Rect text_rect;
    text_rect.x = 20; // Position x du texte (20 pixels de marge)
    text_rect.y = 20; // Position y du texte (20 pixels de marge)
    text_rect.w = surface->w +20; // Largeur du texte
    text_rect.h = surface->h; // Hauteur du texte

    // Effacer la zone de texte précédente
    SDL_SetRenderDrawColor(renderer, 50, 128, 65, 255); // Couleur de fond de la zone de texte (noir)
    SDL_RenderFillRect(renderer, &text_rect);
    text_rect.w = surface->w;
    // Dessiner le texte
    SDL_RenderCopy(renderer, texture, NULL, &text_rect);

    // Rafraîchir l'affichage
    SDL_RenderPresent(renderer);

    // Libérer les ressources
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}
void afficher_popup(SDL_Renderer* renderer, const char* message) {
    // Charger la police d'écriture
    
    TTF_Font* font = TTF_OpenFont("image/ASMAN.TTF", 24); 
    if (!font) {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        return;
    }
    
    // Créer une surface avec le message
    SDL_Color color = { 255, 255, 255 }; // Couleur du texte (blanc)
    SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
    if (!surface) {
        printf("Erreur de création de la surface : %s\n", SDL_GetError());
        TTF_CloseFont(font);
        return;
    }
    
    // Créer une texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Erreur de création de la texture : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }
    
    // Créer un rectangle pour la boîte de dialogue
    SDL_Rect rect;
    rect.x = (800 - surface->w - 20) / 2; // Position x de la boîte de dialogue (centrée horizontalement)
    rect.y = 50; // Position y de la boîte de dialogue (en haut de l'écran)
    rect.w = surface->w + 20; // Largeur de la boîte de dialogue (surface + 20 pixels de padding)
    rect.h = surface->h + 20; // Hauteur de la boîte de dialogue (surface + 20 pixels de padding)
    
    // Dessiner la boîte de dialogue
    SDL_SetRenderDrawColor(renderer, 50, 128, 65, 255); // Couleur de fond de la boîte de dialogue (noir)
    SDL_RenderFillRect(renderer, &rect);
    
    // Dessiner le texte
    SDL_Rect text_rect;
    text_rect.x = rect.x + 10; // Position x du texte (10 pixels de padding)
    text_rect.y = rect.y + 10; // Position y du texte (10 pixels de padding)
    text_rect.w = surface->w;
    text_rect.h = surface->h;
    SDL_RenderCopy(renderer, texture, NULL, &text_rect);
    
    // Rafraîchir l'affichage
    SDL_RenderPresent(renderer);
    
    // Attendre 2 secondes
    wait_two_seconds();
    
    // Dessiner un rectangle noir pour effacer le texte
    SDL_SetRenderDrawColor(renderer, 50, 128, 65, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
    
    // Libérer les ressources
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}