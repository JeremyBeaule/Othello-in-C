#include "struct.h"
  extern  int screen_height;
  extern  int screen_width;
void placer_pion(int x, int y, SDL_Texture* texture, Board* board) {
    //permet d'avoir la cellule du tableau ou l'on clique
    int cell_x = (x - board->grid_x) / board->cell_size ;
    int cell_y = (y - board->grid_y) / board->cell_size ;

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
    if(current_player==joueur_blanc){
            cell->player = WHITE;
            }
        else{
                 cell->player = BLACK;  
            }
    current_player->score+=1;
    printf("\n ton score est : %d \n",current_player->score);
    printf("\n ton score est : %d \n",joueur_noir->score);
    printf("\n la case est  : %d  (0=vide, 1=noir,2=blanc)\n",board->cells[2][3].player);//verifie une case en particulier
    // Mettre à jour le plateau
    

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
