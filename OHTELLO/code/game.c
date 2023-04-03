#include "struct.h"
int start(){
// Initialiser le plateau de jeu et l'afficher
Board board;
initialiser_plateau(&board);
afficher_plateau(&board);
current_player=joueur_noir;
int fin=0;
// Attendre que l'utilisateur ferme la fenêtre
SDL_Event event;
int quit = 0;
while (!quit) {
    affiche_tour(renderer);
    afficher_coup_jouable(&board,grey_texture);//afficher les coups jouables pour le joueur en cours
    
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
                if(fin==0){
                    jouer(&board,x,y);
                    fin = Detection_Fin(&board,white_texture);
                }
                if(fin==1){
                    End_game();
                    if (x>350 && x<550 && y>350 && y<550){
                        printf("\n click sur le bouton fin \n");
                        return 1;
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
return 0 ;
}

