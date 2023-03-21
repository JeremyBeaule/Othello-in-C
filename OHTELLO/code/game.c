#include "struct.h"
void start(){


// Initialiser le plateau de jeu et l'afficher
Board board;
initialiser_plateau(&board);
afficher_plateau(&board);
current_player=joueur_noir;

// Attendre que l'utilisateur ferme la fenêtre
SDL_Event event;
int quit = 0;
while (!quit) {
    affiche_tour(renderer);

    while (SDL_PollEvent(&event)) {

        //printf("la case est de type : %d", board.cells[3][3].player);

    switch (event.type) {
        case SDL_QUIT:
            quit=1;
            break;
        
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int x = event.button.x;
                int y = event.button.y;
                printf("%d =x et %d = y\n,",x,y);
                //verification_mouvement();
                if(current_player==joueur_blanc){

                if(placer_pion(x, y,white_texture , &board)==1) {// la texture definit la couleur du pion qu'on va placer
                current_player = joueur_noir;
                }
                }
                else{
                    printf("\njoueur noir\n");
                   if(placer_pion(x, y,black_texture , &board)==1){ // la texture definit la couleur du pion qu'on va placer 
                   current_player = joueur_blanc;
                   }
                }
                
            }
            break;
            }
    }
    SDL_RenderPresent(renderer);
}
printf("programme finis");

// Libérer les ressources allouées
SDL_DestroyTexture(black_texture);
SDL_DestroyTexture(white_texture);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
IMG_Quit();
SDL_Quit();
return;
}

