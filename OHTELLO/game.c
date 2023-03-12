#include "struct.h"
void start(){


// Initialiser le plateau de jeu et l'afficher
Board board;
initialiser_plateau(&board);
afficher_plateau(renderer, &board, black_texture, white_texture,grille_texture,contour_texture);


// Attendre que l'utilisateur ferme la fenêtre
SDL_Event event;
int quit = 0;
while (!quit) {
    affiche_tour(renderer,current_player);

    while (SDL_PollEvent(&event)) {

        //printf("la case est de type : %d", board.cells[3][3].player);
        if(event.type == SDL_QUIT){
                quit=1;
            }

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
                    printf("joueur blanc");
                placer_pion(x, y,renderer, white_texture , &board); // la texture definit la couleur du pion qu'on va placer
                current_player = joueur_noir;
                }
                else{
                   placer_pion(x, y,renderer, black_texture , &board); // la texture definit la couleur du pion qu'on va placer 
                   current_player = joueur_blanc;
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

}
