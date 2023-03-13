#include "struct.h"

void placer_pion(int x, int y, SDL_Renderer* renderer, SDL_Texture* texture, Board* board) {
    //permet d'avoir la cellule du tableau ou l'on clique
    int cell_x = (x - board->grid_x) / board->cell_size ;
    int cell_y = (y - board->grid_y) / board->cell_size ;
    int screen_height=800; // a changer dans init et affichage et logique.c si on change
  int screen_width=800; // a changer dans init et affichage et logique.c si on change
    printf("\nboard->grid %d\n",board->grid_y);
    printf("\ncell_x:%d et celle_y:%d\n",cell_x,cell_y);

    if (cell_x < 0  ||cell_x >= BOARD_SIZE ||x<screen_width*0.19|| cell_y < 0 || cell_y >= BOARD_SIZE||y<screen_height*0.2) {
        afficher_popup(renderer,"vous etes en dehors de la grille ");
        return;
    }

    Cell* cell = &board->cells[cell_x][cell_y];

    if (cell->player != EMPTY) {
        // Case déjà occupée
        afficher_popup(renderer,"vous ne pouvez pas jouer le coup ");
        return;
    }

    // Mettre à jour le plateau
    cell->player = BLACK;

    // Afficher le pion
 
    SDL_Rect dest_rect = {
        board->grid_x + cell_x * board->cell_size+3,
        board->grid_y + cell_y * board->cell_size+3,
        board->cell_size-5,
        board->cell_size-5
    };
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    SDL_RenderPresent(renderer);
}
